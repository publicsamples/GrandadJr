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
// ===========================| Node & Parameter type declarations |===========================

namespace gransect_t_parameters
{
// Parameter list for gransect_impl::gransect_t -----------------------------------------------

template <int NV>
using Int = parameter::plain<project::gr1<NV>, 0>;
template <int NV>
using Pos = parameter::plain<project::gr1<NV>, 2>;
template <int NV>
using Freeze = parameter::plain<project::gr1<NV>, 9>;
template <int NV>
using Vol = parameter::plain<project::gr1<NV>, 10>;
template <int NV>
using g = parameter::plain<project::gr1<NV>, 1>;
template <int NV>
using gransect_t_plist = parameter::list<Int<NV>, 
                                         Pos<NV>, 
                                         Freeze<NV>, 
                                         Vol<NV>, 
                                         g<NV>>;
}

template <int NV>
using gransect_t_ = container::chain<gransect_t_parameters::gransect_t_plist<NV>, 
                                     wrap::fix<2, project::gr1<NV>>>;

// ===============================| Root node initialiser class |===============================

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
		SNEX_METADATA_ENCODED_PARAMETERS(80)
		{
			0x005C, 0x0000, 0x0000, 0x6E49, 0x0074, 0x0000, 0x8000, 0x0040, 
            0x8000, 0x0042, 0x8000, 0x0040, 0x8000, 0x003F, 0x8000, 0x5C3F, 
            0x0100, 0x0000, 0x5000, 0x736F, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x37BD, 0x3586, 0x005C, 
            0x0002, 0x0000, 0x7246, 0x6565, 0x657A, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x005C, 0x0003, 0x0000, 0x6F56, 0x006C, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0xBD3F, 0x8637, 0x5C35, 
            0x0400, 0x0000, 0x6700, 0x0000, 0x0000, 0x3F80, 0x0000, 0x45C8, 
            0x7DEC, 0x4564, 0x0000, 0x3F80, 0x126F, 0x3A83, 0x0000, 0x0000
		};
		SNEX_METADATA_ENCODED_MOD_INFO(25)
		{
			0x003A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x0000
		};
	};
	
	instance()
	{
		// Node References --------------------------------------------------------------------
		
		auto& faust = this->getT(0); // project::gr1<NV>
		
		// Parameter Connections --------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, faust); // Int -> faust::Interpolationlengthsamples
		
		this->getParameterT(1).connectT(0, faust); // Pos -> faust::Bufferposition
		
		this->getParameterT(2).connectT(0, faust); // Freeze -> faust::Freezebuffer
		
		this->getParameterT(3).connectT(0, faust); // Vol -> faust::Volume
		
		this->getParameterT(4).connectT(0, faust); // g -> faust::Grainlengthms
		
		// Default Values ---------------------------------------------------------------------
		
		;                                     // faust::Interpolationlengthsamples is automated
		;                                     // faust::Grainlengthms is automated
		;                                     // faust::Bufferposition is automated
		faust.setParameterT(3, -4.03961e-08); // core::faust::Timetransposition
		faust.setParameterT(4, 0.000953);     // core::faust::Timeasyncdegree
		faust.setParameterT(5, 0.);           // core::faust::Timeasyncdepth
		faust.setParameterT(6, 1);            // core::faust::Pitchtransposition
		faust.setParameterT(7, 0.);           // core::faust::Pitchasyncdegree
		faust.setParameterT(8, 0.);           // core::faust::Pitchasyncdepth
		;                                     // faust::Freezebuffer is automated
		;                                     // faust::Volume is automated
		
		this->setParameterT(0, 4.);
		this->setParameterT(1, 0.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 1);
		this->setParameterT(4, 3655.87);
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
// ====================================| Public Definition |====================================

namespace project
{
// polyphonic template declaration

template <int NV>
using gransect = wrap::node<gransect_impl::instance<NV>>;
}


