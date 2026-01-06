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

namespace gransect_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using converter_mod = parameter::chain<ranges::Identity, 
                                       parameter::plain<project::shift<NV>, 1>, 
                                       parameter::plain<project::shift<NV>, 2>>;

template <int NV>
using converter_t = control::converter<converter_mod<NV>, 
                                       conversion_logic::ms2samples>;

namespace gransect_t_parameters
{
// Parameter list for gransect_impl::gransect_t ----------------------------------------------------

template <int NV>
using g = parameter::chain<ranges::Identity, 
                           parameter::plain<project::gr1<NV>, 1>, 
                           parameter::plain<gransect_impl::converter_t<NV>, 0>>;

template <int NV>
using Int = parameter::plain<project::gr1<NV>, 0>;
template <int NV>
using Pos = parameter::plain<project::gr1<NV>, 2>;
template <int NV>
using Freeze = parameter::plain<project::gr1<NV>, 9>;
template <int NV>
using Vol = parameter::plain<project::gr1<NV>, 10>;
template <int NV>
using pitch = parameter::plain<project::shift<NV>, 0>;
template <int NV>
using gransect_t_plist = parameter::list<Int<NV>, 
                                         Pos<NV>, 
                                         Freeze<NV>, 
                                         Vol<NV>, 
                                         g<NV>, 
                                         pitch<NV>>;
}

template <int NV>
using gransect_t_ = container::chain<gransect_t_parameters::gransect_t_plist<NV>, 
                                     wrap::fix<2, project::gr1<NV>>, 
                                     converter_t<NV>, 
                                     project::shift<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public gransect_impl::gransect_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(gransect);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(90)
		{
			0x005B, 0x0000, 0x4900, 0x746E, 0x0000, 0x8000, 0x0040, 0x8000, 
            0x0042, 0x1000, 0x0041, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0001, 
            0x0000, 0x6F50, 0x0073, 0x0000, 0x0000, 0x0000, 0x3F80, 0x2C84, 
            0x3EA3, 0x0000, 0x3F80, 0x37BD, 0x3586, 0x025B, 0x0000, 0x4600, 
            0x6572, 0x7A65, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x035B, 0x0000, 0x5600, 
            0x6C6F, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 
            0x8000, 0xBD3F, 0x8637, 0x5B35, 0x0004, 0x0000, 0x0067, 0x0000, 
            0x3F80, 0x0000, 0x45C8, 0xDA5F, 0x440C, 0x0000, 0x3F80, 0x126F, 
            0x3A83, 0x055B, 0x0000, 0x7000, 0x7469, 0x6863, 0x0000, 0xC000, 
            0x00C1, 0xC000, 0x3341, 0xA333, 0x00C0, 0x8000, 0xCD3F, 0xCCCC, 
            0x003D, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& faust = this->getT(0);     // project::gr1<NV>
		auto& converter = this->getT(1); // gransect_impl::converter_t<NV>
		auto& faust1 = this->getT(2);    // project::shift<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, faust); // Int -> faust::Interpolationlengthsamples
		
		this->getParameterT(1).connectT(0, faust); // Pos -> faust::Bufferposition
		
		this->getParameterT(2).connectT(0, faust); // Freeze -> faust::Freezebuffer
		
		this->getParameterT(3).connectT(0, faust); // Vol -> faust::Volume
		
		auto& g_p = this->getParameterT(4);
		g_p.connectT(0, faust);     // g -> faust::Grainlengthms
		g_p.connectT(1, converter); // g -> converter::Value
		
		this->getParameterT(5).connectT(0, faust1); // pitch -> faust1::shiftsemitones
		
		// Modulation Connections ------------------------------------------------------------------
		
		converter.getWrappedObject().getParameter().connectT(0, faust1); // converter -> faust1::windowsamples
		converter.getWrappedObject().getParameter().connectT(1, faust1); // converter -> faust1::xfadesamples
		
		// Default Values --------------------------------------------------------------------------
		
		;                            // faust::Interpolationlengthsamples is automated
		;                            // faust::Grainlengthms is automated
		;                            // faust::Bufferposition is automated
		faust.setParameterT(3, 0.4); // core::faust::Timetransposition
		faust.setParameterT(4, 0.);  // core::faust::Timeasyncdegree
		faust.setParameterT(5, 0.);  // core::faust::Timeasyncdepth
		faust.setParameterT(6, 1);   // core::faust::Pitchtransposition
		faust.setParameterT(7, 0.);  // core::faust::Pitchasyncdegree
		faust.setParameterT(8, 0.);  // core::faust::Pitchasyncdepth
		;                            // faust::Freezebuffer is automated
		;                            // faust::Volume is automated
		
		; // converter::Value is automated
		
		; // faust1::shiftsemitones is automated
		; // faust1::windowsamples is automated
		; // faust1::xfadesamples is automated
		
		this->setParameterT(0, 9.);
		this->setParameterT(1, 0.318699);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 1);
		this->setParameterT(4, 563.412);
		this->setParameterT(5, -5.1);
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
using gransect = wrap::node<gransect_impl::instance<NV>>;
}


