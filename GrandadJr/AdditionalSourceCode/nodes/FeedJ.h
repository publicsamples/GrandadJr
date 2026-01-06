#pragma once

// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace FeedJ_impl
{
// =====================| Node & Parameter type declarations |=====================

using stereo_cable = cable::block<2>;

namespace FeedJ_t_parameters
{
// Parameter list for FeedJ_impl::FeedJ_t ----------------------------------------

DECLARE_PARAMETER_RANGE_SKEW(lpRange, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using lp = parameter::from0To1<filters::one_pole<NV>, 
                               0, 
                               lpRange>;

DECLARE_PARAMETER_RANGE(pan_InputRange, 
                        -1., 
                        1.);
DECLARE_PARAMETER_RANGE(pan_0Range, 
                        -1., 
                        1.);

template <int NV>
using pan_0 = parameter::from0To1<jdsp::jpanner<NV>, 
                                  0, 
                                  pan_0Range>;

DECLARE_PARAMETER_RANGE_SKEW(pan_1Range, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using pan_1 = parameter::from0To1<fx::phase_delay<NV>, 
                                  0, 
                                  pan_1Range>;

template <int NV>
using pan = parameter::chain<pan_InputRange, 
                             pan_0<NV>, 
                             pan_1<NV>>;

template <int NV>
using del = parameter::plain<jdsp::jdelay<NV>, 1>;
using fb = parameter::plain<routing::receive<stereo_cable>, 
                            0>;
template <int NV>
using FeedJ_t_plist = parameter::list<del<NV>, 
                                      fb, 
                                      lp<NV>, 
                                      pan<NV>>;
}

template <int NV>
using FeedJ_t_ = container::chain<FeedJ_t_parameters::FeedJ_t_plist<NV>, 
                                  wrap::fix<2, routing::receive<stereo_cable>>, 
                                  jdsp::jdelay<NV>, 
                                  fx::phase_delay<NV>, 
                                  filters::one_pole<NV>, 
                                  routing::send<stereo_cable>, 
                                  jdsp::jpanner<NV>>;

// ========================| Root node initialiser class |========================

template <int NV> struct instance: public FeedJ_impl::FeedJ_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(FeedJ);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(58)
		{
			0x005B, 0x0000, 0x6400, 0x6C65, 0x0000, 0x0000, 0x0000, 0x7A00, 
            0x0044, 0x0000, 0x9B00, 0x9A20, 0x003E, 0x0000, 0x5B00, 0x0001, 
            0x0000, 0x6266, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 0x706C, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x393F, 0x0234, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x6170, 0x006E, 0x0000, 
            0xBF80, 0x0000, 0x3F80, 0x1893, 0xBD34, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------
		
		auto& receive = this->getT(0);     // routing::receive<stereo_cable>
		auto& jdelay = this->getT(1);      // jdsp::jdelay<NV>
		auto& phase_delay = this->getT(2); // fx::phase_delay<NV>
		auto& one_pole = this->getT(3);    // filters::one_pole<NV>
		auto& send = this->getT(4);        // routing::send<stereo_cable>
		auto& jpanner = this->getT(5);     // jdsp::jpanner<NV>
		
		// Parameter Connections -------------------------------------------------
		
		this->getParameterT(0).connectT(0, jdelay); // del -> jdelay::DelayTime
		
		this->getParameterT(1).connectT(0, receive); // fb -> receive::Feedback
		
		this->getParameterT(2).connectT(0, one_pole); // lp -> one_pole::Frequency
		
		auto& pan_p = this->getParameterT(3);
		pan_p.connectT(0, jpanner);     // pan -> jpanner::Pan
		pan_p.connectT(1, phase_delay); // pan -> phase_delay::Frequency
		
		// Send Connections ------------------------------------------------------
		
		send.connect(receive);
		
		// Default Values --------------------------------------------------------
		
		; // receive::Feedback is automated
		
		jdelay.setParameterT(0, 1000.); // jdsp::jdelay::Limit
		;                               // jdelay::DelayTime is automated
		
		; // phase_delay::Frequency is automated
		
		;                                // one_pole::Frequency is automated
		one_pole.setParameterT(1, 1.);   // filters::one_pole::Q
		one_pole.setParameterT(2, 0.);   // filters::one_pole::Gain
		one_pole.setParameterT(3, 0.01); // filters::one_pole::Smoothing
		one_pole.setParameterT(4, 0.);   // filters::one_pole::Mode
		one_pole.setParameterT(5, 1.);   // filters::one_pole::Enabled
		
		;                             // jpanner::Pan is automated
		jpanner.setParameterT(1, 1.); // jdsp::jpanner::Rule
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 0.);
		this->setParameterT(2, 0.508609);
		this->setParameterT(3, -0.0439688);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// =============================| Public Definition |=============================

namespace project
{
// polyphonic template declaration

template <int NV>
using FeedJ = wrap::node<FeedJ_impl::instance<NV>>;
}


