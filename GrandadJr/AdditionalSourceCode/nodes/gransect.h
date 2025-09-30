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
// ============================| Node & Parameter type declarations |============================

namespace gransect_t_parameters
{
// Parameter list for gransect_impl::gransect_t -------------------------------------------------

DECLARE_PARAMETER_RANGE(Pitch_InputRange, 
                        -1., 
                        1.);
DECLARE_PARAMETER_RANGE(Pitch_0Range, 
                        0., 
                        2.);

template <int NV>
using Pitch_0 = parameter::from0To1<project::gr1<NV>, 
                                    6, 
                                    Pitch_0Range>;

template <int NV>
using Pitch = parameter::chain<Pitch_InputRange, Pitch_0<NV>>;

template <int NV>
using Int = parameter::plain<project::gr1<NV>, 0>;
template <int NV>
using Grain = parameter::plain<project::gr1<NV>, 1>;
template <int NV>
using Pos = parameter::plain<project::gr1<NV>, 2>;
template <int NV>
using TimeTranspose = parameter::plain<project::gr1<NV>, 3>;
template <int NV>
using TimeDepth = parameter::plain<project::gr1<NV>, 5>;
template <int NV>
using Freeze = parameter::plain<project::gr1<NV>, 9>;
template <int NV>
using Vol = parameter::plain<project::gr1<NV>, 10>;
template <int NV>
using gransect_t_plist = parameter::list<Int<NV>, 
                                         Grain<NV>, 
                                         Pos<NV>, 
                                         TimeTranspose<NV>, 
                                         TimeDepth<NV>, 
                                         Freeze<NV>, 
                                         Vol<NV>, 
                                         Pitch<NV>>;
}

template <int NV>
using gransect_t_ = container::chain<gransect_t_parameters::gransect_t_plist<NV>, 
                                     wrap::fix<2, project::gr1<NV>>>;

// ================================| Root node initialiser class |================================

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
		SNEX_METADATA_ENCODED_PARAMETERS(136)
		{
			0x005C, 0x0000, 0x0000, 0x6E49, 0x0074, 0x0000, 0x8000, 0x0040, 
            0x8000, 0x0042, 0x1000, 0x0041, 0x8000, 0x003F, 0x8000, 0x5C3F, 
            0x0100, 0x0000, 0x4700, 0x6172, 0x6E69, 0x0000, 0x126F, 0x3A83, 
            0xCCCD, 0x404C, 0x13D3, 0x3EFE, 0x0000, 0x3F80, 0x37BD, 0x3586, 
            0x005C, 0x0002, 0x0000, 0x6F50, 0x0073, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0xBD3F, 0x8637, 0x5C35, 
            0x0300, 0x0000, 0x5400, 0x6D69, 0x5465, 0x6172, 0x736E, 0x6F70, 
            0x6573, 0x0000, 0x0000, 0xC180, 0x0000, 0x4180, 0xFFFF, 0x3F7F, 
            0x0000, 0x3F80, 0x37BD, 0x3586, 0x005C, 0x0004, 0x0000, 0x6954, 
            0x656D, 0x6544, 0x7470, 0x0068, 0x0000, 0x0000, 0x0000, 0xEA60, 
            0x0049, 0x0000, 0x0000, 0x8000, 0xBD3F, 0x8637, 0x5C35, 0x0500, 
            0x0000, 0x4600, 0x6572, 0x7A65, 0x0065, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x5C3F, 
            0x0600, 0x0000, 0x5600, 0x6C6F, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x37BD, 0x3586, 0x005C, 
            0x0007, 0x0000, 0x6950, 0x6374, 0x0068, 0x0000, 0x8000, 0x00BF, 
            0x8000, 0x2F3F, 0x8785, 0x003E, 0x8000, 0xBD3F, 0x8637, 0x0035
		};
		SNEX_METADATA_ENCODED_MOD_INFO(17)
		{
			0x003A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x0000
		};
	};
	
	instance()
	{
		// Node References ----------------------------------------------------------------------
		
		auto& faust1 = this->getT(0); // project::gr1<NV>
		
		// Parameter Connections ----------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, faust1); // Int -> faust1::Interpolationlengthsamples
		
		this->getParameterT(1).connectT(0, faust1); // Grain -> faust1::Grainlengths
		
		this->getParameterT(2).connectT(0, faust1); // Pos -> faust1::Bufferposition
		
		this->getParameterT(3).connectT(0, faust1); // TimeTranspose -> faust1::Timetransposition
		
		this->getParameterT(4).connectT(0, faust1); // TimeDepth -> faust1::Timeasyncdepth
		
		this->getParameterT(5).connectT(0, faust1); // Freeze -> faust1::Freezebuffer
		
		this->getParameterT(6).connectT(0, faust1); // Vol -> faust1::Volume
		
		this->getParameterT(7).connectT(0, faust1); // Pitch -> faust1::Pitchtransposition
		
		// Default Values -----------------------------------------------------------------------
		
		;                            // faust1::Interpolationlengthsamples is automated
		;                            // faust1::Grainlengths is automated
		;                            // faust1::Bufferposition is automated
		;                            // faust1::Timetransposition is automated
		faust1.setParameterT(4, 0.); // core::faust::Timeasyncdegree
		;                            // faust1::Timeasyncdepth is automated
		;                            // faust1::Pitchtransposition is automated
		faust1.setParameterT(7, 0.); // core::faust::Pitchasyncdegree
		faust1.setParameterT(8, 0.); // core::faust::Pitchasyncdepth
		;                            // faust1::Freezebuffer is automated
		;                            // faust1::Volume is automated
		
		this->setParameterT(0, 9.);
		this->setParameterT(1, 0.496245);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 1);
		this->setParameterT(4, 0.);
		this->setParameterT(5, 0.);
		this->setParameterT(6, 0.);
		this->setParameterT(7, 0.264688);
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
// =====================================| Public Definition |=====================================

namespace project
{
// polyphonic template declaration

template <int NV>
using gransect = wrap::node<gransect_impl::instance<NV>>;
}


