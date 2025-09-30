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

namespace gransect2_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using input_toggle_t = control::input_toggle<NV, 
                                             parameter::plain<project::gr1<NV>, 2>>;

template <int NV>
using input_toggle2_t = control::input_toggle<NV, 
                                              parameter::plain<project::gr1<NV>, 1>>;

template <int NV>
using input_toggle1_t = control::input_toggle<NV, 
                                              parameter::plain<project::gr1<NV>, 6>>;

namespace gransect2_t_parameters
{
// Parameter list for gransect2_impl::gransect2_t --------------------------------------------------

template <int NV>
using Int = parameter::plain<project::gr1<NV>, 0>;
template <int NV>
using Grain = parameter::plain<gransect2_impl::input_toggle2_t<NV>, 
                               1>;
template <int NV>
using Pos = parameter::plain<gransect2_impl::input_toggle_t<NV>, 
                             1>;
template <int NV>
using TimeTranspose = parameter::plain<project::gr1<NV>, 3>;
template <int NV>
using TimeDepth = parameter::plain<project::gr1<NV>, 5>;
template <int NV>
using Freeze = parameter::plain<project::gr1<NV>, 9>;
template <int NV>
using Vol = parameter::plain<project::gr1<NV>, 10>;
template <int NV>
using Pitch = parameter::plain<gransect2_impl::input_toggle1_t<NV>, 
                               1>;
template <int NV>
using pos2 = parameter::plain<gransect2_impl::input_toggle_t<NV>, 
                              2>;
template <int NV>
using posmode = parameter::plain<gransect2_impl::input_toggle_t<NV>, 
                                 0>;
template <int NV>
using grain2 = parameter::plain<gransect2_impl::input_toggle2_t<NV>, 
                                2>;
template <int NV>
using grainmode = parameter::plain<gransect2_impl::input_toggle2_t<NV>, 
                                   0>;
template <int NV>
using pitch2 = parameter::plain<gransect2_impl::input_toggle1_t<NV>, 
                                2>;
template <int NV>
using pitchmode = parameter::plain<gransect2_impl::input_toggle1_t<NV>, 
                                   0>;
template <int NV>
using gransect2_t_plist = parameter::list<Int<NV>, 
                                          Grain<NV>, 
                                          Pos<NV>, 
                                          TimeTranspose<NV>, 
                                          TimeDepth<NV>, 
                                          Freeze<NV>, 
                                          Vol<NV>, 
                                          Pitch<NV>, 
                                          pos2<NV>, 
                                          posmode<NV>, 
                                          grain2<NV>, 
                                          grainmode<NV>, 
                                          pitch2<NV>, 
                                          pitchmode<NV>>;
}

template <int NV>
using gransect2_t_ = container::chain<gransect2_t_parameters::gransect2_t_plist<NV>, 
                                      wrap::fix<2, input_toggle_t<NV>>, 
                                      input_toggle2_t<NV>, 
                                      input_toggle1_t<NV>, 
                                      project::gr1<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public gransect2_impl::gransect2_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(gransect2);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(242)
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
            0x0007, 0x0000, 0x6950, 0x6374, 0x0068, 0x0000, 0x8000, 0x00C1, 
            0x8000, 0xFF41, 0x7FFF, 0x003F, 0x8000, 0xBD3F, 0x8637, 0x5C35, 
            0x0800, 0x0000, 0x7000, 0x736F, 0x0032, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5C00, 
            0x0900, 0x0000, 0x7000, 0x736F, 0x6F6D, 0x6564, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x005C, 0x000A, 0x0000, 0x7267, 0x6961, 0x326E, 0x0000, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x005C, 0x000B, 0x0000, 0x7267, 0x6961, 0x6D6E, 
            0x646F, 0x0065, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x5C3F, 0x0C00, 0x0000, 0x7000, 
            0x7469, 0x6863, 0x0032, 0x0000, 0x8000, 0x00C1, 0x8000, 0x0041, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5C00, 0x0D00, 0x0000, 
            0x7000, 0x7469, 0x6863, 0x6F6D, 0x6564, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x0000
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
		// Node References -------------------------------------------------------------------------
		
		auto& input_toggle = this->getT(0);  // gransect2_impl::input_toggle_t<NV>
		auto& input_toggle2 = this->getT(1); // gransect2_impl::input_toggle2_t<NV>
		auto& input_toggle1 = this->getT(2); // gransect2_impl::input_toggle1_t<NV>
		auto& faust1 = this->getT(3);        // project::gr1<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, faust1); // Int -> faust1::Interpolationlengthsamples
		
		this->getParameterT(1).connectT(0, input_toggle2); // Grain -> input_toggle2::Value1
		
		this->getParameterT(2).connectT(0, input_toggle); // Pos -> input_toggle::Value1
		
		this->getParameterT(3).connectT(0, faust1); // TimeTranspose -> faust1::Timetransposition
		
		this->getParameterT(4).connectT(0, faust1); // TimeDepth -> faust1::Timeasyncdepth
		
		this->getParameterT(5).connectT(0, faust1); // Freeze -> faust1::Freezebuffer
		
		this->getParameterT(6).connectT(0, faust1); // Vol -> faust1::Volume
		
		this->getParameterT(7).connectT(0, input_toggle1); // Pitch -> input_toggle1::Value1
		
		this->getParameterT(8).connectT(0, input_toggle); // pos2 -> input_toggle::Value2
		
		this->getParameterT(9).connectT(0, input_toggle); // posmode -> input_toggle::Input
		
		this->getParameterT(10).connectT(0, input_toggle2); // grain2 -> input_toggle2::Value2
		
		this->getParameterT(11).connectT(0, input_toggle2); // grainmode -> input_toggle2::Input
		
		this->getParameterT(12).connectT(0, input_toggle1); // pitch2 -> input_toggle1::Value2
		
		this->getParameterT(13).connectT(0, input_toggle1); // pitchmode -> input_toggle1::Input
		
		// Modulation Connections ------------------------------------------------------------------
		
		input_toggle.getWrappedObject().getParameter().connectT(0, faust1);  // input_toggle -> faust1::Bufferposition
		input_toggle2.getWrappedObject().getParameter().connectT(0, faust1); // input_toggle2 -> faust1::Grainlengths
		input_toggle1.getWrappedObject().getParameter().connectT(0, faust1); // input_toggle1 -> faust1::Pitchtransposition
		
		// Default Values --------------------------------------------------------------------------
		
		; // input_toggle::Input is automated
		; // input_toggle::Value1 is automated
		; // input_toggle::Value2 is automated
		
		; // input_toggle2::Input is automated
		; // input_toggle2::Value1 is automated
		; // input_toggle2::Value2 is automated
		
		; // input_toggle1::Input is automated
		; // input_toggle1::Value1 is automated
		; // input_toggle1::Value2 is automated
		
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
		this->setParameterT(7, 1);
		this->setParameterT(8, 0.);
		this->setParameterT(9, 0.);
		this->setParameterT(10, 0.);
		this->setParameterT(11, 0.);
		this->setParameterT(12, 0.);
		this->setParameterT(13, 0.);
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
using gransect2 = wrap::node<gransect2_impl::instance<NV>>;
}


