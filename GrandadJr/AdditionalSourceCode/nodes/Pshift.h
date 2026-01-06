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

namespace Pshift_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<project::shift<NV>, 0>>;
using stereo_cable = cable::block<2>;

template <int NV>
using chain2_t = container::chain<parameter::empty, 
                                  wrap::fix<2, minmax_t<NV>>, 
                                  routing::receive<stereo_cable>, 
                                  project::shift<NV>, 
                                  routing::send<stereo_cable>>;

namespace Pshift_t_parameters
{
// Parameter list for Pshift_impl::Pshift_t --------------------------------------------------------

DECLARE_PARAMETER_RANGE_STEP(win_0Range, 
                             50., 
                             10000., 
                             1.);

template <int NV>
using win_0 = parameter::from0To1<project::shift<NV>, 
                                  1, 
                                  win_0Range>;

DECLARE_PARAMETER_RANGE_STEP(win_1Range, 
                             1., 
                             10000., 
                             1.);

template <int NV>
using win_1 = parameter::from0To1<project::shift<NV>, 
                                  2, 
                                  win_1Range>;

template <int NV>
using win = parameter::chain<ranges::Identity, 
                             win_0<NV>, 
                             win_1<NV>>;

template <int NV>
using min = parameter::plain<Pshift_impl::minmax_t<NV>, 
                             1>;
template <int NV>
using max = parameter::plain<Pshift_impl::minmax_t<NV>, 
                             2>;
template <int NV>
using step = parameter::plain<Pshift_impl::minmax_t<NV>, 
                              4>;
template <int NV>
using value = parameter::plain<Pshift_impl::minmax_t<NV>, 
                               0>;
using feed = parameter::plain<routing::receive<stereo_cable>, 
                              0>;
template <int NV>
using Pshift_t_plist = parameter::list<min<NV>, 
                                       max<NV>, 
                                       step<NV>, 
                                       value<NV>, 
                                       feed, 
                                       win<NV>>;
}

template <int NV>
using Pshift_t_ = container::chain<Pshift_t_parameters::Pshift_t_plist<NV>, 
                                   wrap::fix<2, chain2_t<NV>>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Pshift_impl::Pshift_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Pshift);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(90)
		{
			0x005B, 0x0000, 0x6D00, 0x6E69, 0x0000, 0xC000, 0x00C1, 0xC000, 
            0x0041, 0xC000, 0x00C1, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0001, 
            0x0000, 0x616D, 0x0078, 0x0000, 0xC1C0, 0x0000, 0x41C0, 0x0000, 
            0x41C0, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x025B, 0x0000, 0x7300, 
            0x6574, 0x0070, 0x0000, 0x0000, 0x0000, 0x4140, 0x0000, 0x4140, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x035B, 0x0000, 0x7600, 0x6C61, 
            0x6575, 0x0000, 0x0000, 0x0000, 0x8000, 0xAE3F, 0xD70F, 0x003D, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 0x6566, 0x6465, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x483F, 0xF4C3, 0x003E, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0005, 0x0000, 0x6977, 0x006E, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& chain2 = this->getT(0);          // Pshift_impl::chain2_t<NV>
		auto& minmax = this->getT(0).getT(0);  // Pshift_impl::minmax_t<NV>
		auto& receive = this->getT(0).getT(1); // routing::receive<stereo_cable>
		auto& faust = this->getT(0).getT(2);   // project::shift<NV>
		auto& send = this->getT(0).getT(3);    // routing::send<stereo_cable>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, minmax); // min -> minmax::Minimum
		
		this->getParameterT(1).connectT(0, minmax); // max -> minmax::Maximum
		
		this->getParameterT(2).connectT(0, minmax); // step -> minmax::Step
		
		this->getParameterT(3).connectT(0, minmax); // value -> minmax::Value
		
		this->getParameterT(4).connectT(0, receive); // feed -> receive::Feedback
		
		auto& win_p = this->getParameterT(5);
		win_p.connectT(0, faust); // win -> faust::windowsamples
		win_p.connectT(1, faust); // win -> faust::xfadesamples
		
		// Modulation Connections ------------------------------------------------------------------
		
		minmax.getWrappedObject().getParameter().connectT(0, faust); // minmax -> faust::shiftsemitones
		
		// Send Connections ------------------------------------------------------------------------
		
		send.connect(receive);
		
		// Default Values --------------------------------------------------------------------------
		
		;                            // minmax::Value is automated
		;                            // minmax::Minimum is automated
		;                            // minmax::Maximum is automated
		minmax.setParameterT(3, 1.); // control::minmax::Skew
		;                            // minmax::Step is automated
		minmax.setParameterT(5, 0.); // control::minmax::Polarity
		
		; // receive::Feedback is automated
		
		; // faust::shiftsemitones is automated
		; // faust::windowsamples is automated
		; // faust::xfadesamples is automated
		
		this->setParameterT(0, -24.);
		this->setParameterT(1, 24.);
		this->setParameterT(2, 12.);
		this->setParameterT(3, 0.10501);
		this->setParameterT(4, 0.478052);
		this->setParameterT(5, 1.);
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
// ======================================| Public Definition |======================================

namespace project
{
// polyphonic template declaration

template <int NV>
using Pshift = wrap::node<Pshift_impl::instance<NV>>;
}


