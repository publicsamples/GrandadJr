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

namespace spacer2_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(xfader_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using xfader_c0 = parameter::from0To1<core::gain<NV>, 
                                      0, 
                                      xfader_c0Range>;

template <int NV> using xfader_c1 = xfader_c0<NV>;

template <int NV>
using xfader_multimod = parameter::list<xfader_c0<NV>, xfader_c1<NV>>;

template <int NV>
using xfader_t = control::xfader<xfader_multimod<NV>, faders::rms>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>>;
using pack_resizer_t = wrap::data<control::pack_resizer, 
                                  data::external::sliderpack<0>>;

DECLARE_PARAMETER_RANGE_STEP(clone_pack_modRange, 
                             0., 
                             24., 
                             1.);

template <int NV>
using clone_pack_mod = parameter::from0To1<project::shift<NV>, 
                                           0, 
                                           clone_pack_modRange>;

template <int NV>
using clone_pack_t = wrap::data<control::clone_pack<parameter::cloned<clone_pack_mod<NV>>>, 
                                data::external::sliderpack<0>>;

DECLARE_PARAMETER_RANGE_STEP(clone_cable1_0Range, 
                             50., 
                             10000., 
                             1.);

template <int NV>
using clone_cable1_0 = parameter::from0To1<project::shift<NV>, 
                                           1, 
                                           clone_cable1_0Range>;

DECLARE_PARAMETER_RANGE_STEP(clone_cable1_1Range, 
                             1., 
                             10000., 
                             1.);

template <int NV>
using clone_cable1_1 = parameter::from0To1<project::shift<NV>, 
                                           2, 
                                           clone_cable1_1Range>;

template <int NV> using clone_cable1_2 = clone_cable1_0<NV>;

template <int NV> using clone_cable1_3 = clone_cable1_1<NV>;

template <int NV>
using clone_cable1_cc = parameter::clonechain<parameter::cloned<clone_cable1_0<NV>>, 
                                              parameter::cloned<clone_cable1_1<NV>>, 
                                              parameter::cloned<clone_cable1_2<NV>>, 
                                              parameter::cloned<clone_cable1_3<NV>>>;
template <int NV>
using clone_cable1_t = control::clone_cable<clone_cable1_cc<NV>, duplilogic::fixed>;

template <int NV> using clone_cable2_mod = xfader_c0<NV>;

template <int NV>
using clone_cable2_t = control::clone_cable<parameter::cloned<clone_cable2_mod<NV>>, 
                                            duplilogic::fixed>;

DECLARE_PARAMETER_RANGE_SKEW(clone_cable_modRange, 
                             0., 
                             1000., 
                             0.30103);

template <int NV>
using clone_cable_mod = parameter::from0To1<jdsp::jdelay_cubic<NV>, 
                                            1, 
                                            clone_cable_modRange>;

template <int NV>
using clone_cable_t = control::clone_cable<parameter::cloned<clone_cable_mod<NV>>, 
                                           duplilogic::spread>;

DECLARE_PARAMETER_RANGE(clone_cable3_modRange, 
                        -1., 
                        1.);

template <int NV>
using clone_cable3_mod = parameter::from0To1<jdsp::jpanner<NV>, 
                                             0, 
                                             clone_cable3_modRange>;

template <int NV>
using clone_cable3_t = control::clone_cable<parameter::cloned<clone_cable3_mod<NV>>, 
                                            duplilogic::spread>;

DECLARE_PARAMETER_RANGE_STEP(clone_cable4_modRange, 
                             -12., 
                             12., 
                             1.);

template <int NV>
using clone_cable4_mod = parameter::from0To1<project::shift<NV>, 
                                             0, 
                                             clone_cable4_modRange>;

template <int NV>
using clone_cable4_t = control::clone_cable<parameter::cloned<clone_cable4_mod<NV>>, 
                                            duplilogic::fixed>;

template <int NV>
using clone1_child_t = container::chain<parameter::empty, 
                                        wrap::fix<2, jdsp::jdelay_cubic<NV>>, 
                                        project::shift<NV>, 
                                        project::shift<NV>, 
                                        jdsp::jpanner<NV>, 
                                        core::gain<NV>>;
template <int NV>
using clone1_t = wrap::clonecopy<clone1_child_t<NV>, 32>;
template <int NV>
using stereo_cable = cable::block<NV, 2>;

template <int NV>
using chain5_t = container::chain<parameter::empty, 
                                  wrap::fix<2, pack_resizer_t>, 
                                  clone_pack_t<NV>, 
                                  clone_cable1_t<NV>, 
                                  clone_cable2_t<NV>, 
                                  clone_cable_t<NV>, 
                                  clone_cable3_t<NV>, 
                                  clone_cable4_t<NV>, 
                                  clone1_t<NV>, 
                                  routing::send<NV, stereo_cable<NV>>, 
                                  core::gain<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, chain1_t<NV>>, 
                                 chain5_t<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, xfader_t<NV>>, 
                                 split_t<NV>>;

namespace spacer2_t_parameters
{
// Parameter list for spacer2_impl::spacer2_t ------------------------------------------------------

DECLARE_PARAMETER_RANGE_STEP(Clones_InputRange, 
                             1., 
                             32., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(Clones_0Range, 
                             1., 
                             32., 
                             1.);

template <int NV>
using Clones_0 = parameter::from0To1<spacer2_impl::clone1_t<NV>, 
                                     0, 
                                     Clones_0Range>;

template <int NV>
using Clones_1 = parameter::from0To1<spacer2_impl::clone_cable1_t<NV>, 
                                     0, 
                                     Clones_0Range>;

template <int NV>
using Clones_2 = parameter::from0To1<spacer2_impl::clone_cable2_t<NV>, 
                                     0, 
                                     Clones_0Range>;

template <int NV>
using Clones_3 = parameter::from0To1<spacer2_impl::clone_pack_t<NV>, 
                                     0, 
                                     Clones_0Range>;

template <int NV>
using Clones_4 = parameter::from0To1<spacer2_impl::clone_cable_t<NV>, 
                                     0, 
                                     Clones_0Range>;

template <int NV>
using Clones_5 = parameter::from0To1<spacer2_impl::clone_cable3_t<NV>, 
                                     0, 
                                     Clones_0Range>;

template <int NV>
using Clones_6 = parameter::from0To1<spacer2_impl::clone_cable4_t<NV>, 
                                     0, 
                                     Clones_0Range>;

DECLARE_PARAMETER_RANGE_STEP(Clones_7Range, 
                             0., 
                             32., 
                             1.);

using Clones_7 = parameter::from0To1<spacer2_impl::pack_resizer_t, 
                                     0, 
                                     Clones_7Range>;

template <int NV>
using Clones = parameter::chain<Clones_InputRange, 
                                Clones_0<NV>, 
                                Clones_1<NV>, 
                                Clones_2<NV>, 
                                Clones_3<NV>, 
                                Clones_4<NV>, 
                                Clones_5<NV>, 
                                Clones_6<NV>, 
                                Clones_7>;

template <int NV>
using deltime = parameter::from0To1<spacer2_impl::clone_cable_t<NV>, 
                                    1, 
                                    spacer2_impl::clone_cable3_modRange>;

DECLARE_PARAMETER_RANGE_STEP(Oct_InputRange, 
                             0., 
                             2., 
                             1.);

template <int NV>
using Oct = parameter::chain<Oct_InputRange, 
                             parameter::plain<spacer2_impl::clone_cable4_t<NV>, 1>>;

template <int NV>
using Harm = parameter::plain<spacer2_impl::clone_pack_t<NV>, 
                              1>;
template <int NV>
using win = parameter::plain<spacer2_impl::clone_cable1_t<NV>, 
                             1>;
template <int NV>
using pan = parameter::plain<spacer2_impl::clone_cable3_t<NV>, 
                             1>;
template <int NV>
using gain = parameter::plain<spacer2_impl::clone_cable2_t<NV>, 
                              1>;
template <int NV>
using Mix = parameter::plain<spacer2_impl::xfader_t<NV>, 
                             0>;
template <int NV>
using spacer2_t_plist = parameter::list<Clones<NV>, 
                                        Harm<NV>, 
                                        deltime<NV>, 
                                        win<NV>, 
                                        pan<NV>, 
                                        gain<NV>, 
                                        Mix<NV>, 
                                        Oct<NV>>;
}

template <int NV>
using spacer2_t_ = container::chain<spacer2_t_parameters::spacer2_t_plist<NV>, 
                                    wrap::fix<2, chain_t<NV>>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public spacer2_impl::spacer2_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 1;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(spacer2);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(130)
		{
			0x005C, 0x0000, 0x0000, 0x6C43, 0x6E6F, 0x7365, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x4200, 0x0000, 0x4200, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x005C, 0x0001, 0x0000, 0x6148, 0x6D72, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x005C, 0x0002, 0x0000, 0x6564, 0x746C, 0x6D69, 0x0065, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5C00, 0x0300, 0x0000, 0x7700, 0x6E69, 0x0000, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x6666, 0x3F26, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x005C, 0x0004, 0x0000, 0x6170, 0x006E, 0x0000, 
            0x8000, 0x00BF, 0x8000, 0x8F3F, 0x75C2, 0x003F, 0x8000, 0x003F, 
            0x0000, 0x5C00, 0x0500, 0x0000, 0x6700, 0x6961, 0x006E, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x7A3F, 0xBCD3, 0x003E, 0x8000, 0x003F, 
            0x0000, 0x5C00, 0x0600, 0x0000, 0x4D00, 0x7869, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x3216, 0x3F51, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x005C, 0x0007, 0x0000, 0x634F, 0x0074, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x0040, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x0000
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
		
		auto& chain = this->getT(0);                                       // spacer2_impl::chain_t<NV>
		auto& xfader = this->getT(0).getT(0);                              // spacer2_impl::xfader_t<NV>
		auto& split = this->getT(0).getT(1);                               // spacer2_impl::split_t<NV>
		auto& chain1 = this->getT(0).getT(1).getT(0);                      // spacer2_impl::chain1_t<NV>
		auto& gain = this->getT(0).getT(1).getT(0).getT(0);                // core::gain<NV>
		auto& chain5 = this->getT(0).getT(1).getT(1);                      // spacer2_impl::chain5_t<NV>
		auto& pack_resizer = this->getT(0).getT(1).getT(1).getT(0);        // spacer2_impl::pack_resizer_t
		auto& clone_pack = this->getT(0).getT(1).getT(1).getT(1);          // spacer2_impl::clone_pack_t<NV>
		auto& clone_cable1 = this->getT(0).getT(1).getT(1).getT(2);        // spacer2_impl::clone_cable1_t<NV>
		auto& clone_cable2 = this->getT(0).getT(1).getT(1).getT(3);        // spacer2_impl::clone_cable2_t<NV>
		auto& clone_cable = this->getT(0).getT(1).getT(1).getT(4);         // spacer2_impl::clone_cable_t<NV>
		auto& clone_cable3 = this->getT(0).getT(1).getT(1).getT(5);        // spacer2_impl::clone_cable3_t<NV>
		auto& clone_cable4 = this->getT(0).getT(1).getT(1).getT(6);        // spacer2_impl::clone_cable4_t<NV>
		auto& clone1 = this->getT(0).getT(1).getT(1).getT(7);              // spacer2_impl::clone1_t<NV>              // spacer2_impl::clone1_child_t<NV>
		auto jdelay_cubic = this->getT(0).getT(1).getT(1).getT(7).getT(0); // jdsp::jdelay_cubic<NV>
		auto faust = this->getT(0).getT(1).getT(1).getT(7).getT(1);        // project::shift<NV>
		auto faust32 = this->getT(0).getT(1).getT(1).getT(7).getT(2);      // project::shift<NV>
		auto jpanner1 = this->getT(0).getT(1).getT(1).getT(7).getT(3);     // jdsp::jpanner<NV>
		auto gain3 = this->getT(0).getT(1).getT(1).getT(7).getT(4);        // core::gain<NV>
		auto& send63 = this->getT(0).getT(1).getT(1).getT(8);              // routing::send<NV, stereo_cable<NV>>
		auto& gain1 = this->getT(0).getT(1).getT(1).getT(9);               // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& Clones_p = this->getParameterT(0);
		Clones_p.connectT(0, clone1);       // Clones -> clone1::NumClones
		Clones_p.connectT(1, clone_cable1); // Clones -> clone_cable1::NumClones
		Clones_p.connectT(2, clone_cable2); // Clones -> clone_cable2::NumClones
		Clones_p.connectT(3, clone_pack);   // Clones -> clone_pack::NumClones
		Clones_p.connectT(4, clone_cable);  // Clones -> clone_cable::NumClones
		Clones_p.connectT(5, clone_cable3); // Clones -> clone_cable3::NumClones
		Clones_p.connectT(6, clone_cable4); // Clones -> clone_cable4::NumClones
		Clones_p.connectT(7, pack_resizer); // Clones -> pack_resizer::NumSliders
		
		this->getParameterT(1).connectT(0, clone_pack); // Harm -> clone_pack::Value
		
		this->getParameterT(2).connectT(0, clone_cable); // deltime -> clone_cable::Value
		
		this->getParameterT(3).connectT(0, clone_cable1); // win -> clone_cable1::Value
		
		this->getParameterT(4).connectT(0, clone_cable3); // pan -> clone_cable3::Value
		
		this->getParameterT(5).connectT(0, clone_cable2); // gain -> clone_cable2::Value
		
		this->getParameterT(6).connectT(0, xfader); // Mix -> xfader::Value
		
		this->getParameterT(7).connectT(0, clone_cable4); // Oct -> clone_cable4::Value
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);                             // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1);                            // xfader -> gain1::Gain
		clone_pack.getWrappedObject().getParameter().connectT(0, faust);         // clone_pack -> faust::shiftsemitones
		clone_cable1.getWrappedObject().getParameter().connectT(0, faust);       // clone_cable1 -> faust::windowsamples
		clone_cable1.getWrappedObject().getParameter().connectT(1, faust);       // clone_cable1 -> faust::xfadesamples
		clone_cable1.getWrappedObject().getParameter().connectT(2, faust32);     // clone_cable1 -> faust32::windowsamples
		clone_cable1.getWrappedObject().getParameter().connectT(3, faust32);     // clone_cable1 -> faust32::xfadesamples
		clone_cable2.getWrappedObject().getParameter().connectT(0, gain3);       // clone_cable2 -> gain3::Gain
		clone_cable.getWrappedObject().getParameter().connectT(0, jdelay_cubic); // clone_cable -> jdelay_cubic::DelayTime
		clone_cable3.getWrappedObject().getParameter().connectT(0, jpanner1);    // clone_cable3 -> jpanner1::Pan
		clone_cable4.getWrappedObject().getParameter().connectT(0, faust32);     // clone_cable4 -> faust32::shiftsemitones
		
		// Send Connections ------------------------------------------------------------------------
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // pack_resizer::NumSliders is automated
		
		; // clone_pack::NumClones is automated
		; // clone_pack::Value is automated
		
		;                                  // clone_cable1::NumClones is automated
		;                                  // clone_cable1::Value is automated
		clone_cable1.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable2::NumClones is automated
		;                                  // clone_cable2::Value is automated
		clone_cable2.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                 // clone_cable::NumClones is automated
		;                                 // clone_cable::Value is automated
		clone_cable.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable3::NumClones is automated
		;                                  // clone_cable3::Value is automated
		clone_cable3.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable4::NumClones is automated
		;                                  // clone_cable4::Value is automated
		clone_cable4.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                            // clone1::NumClones is automated
		clone1.setParameterT(1, 2.); // container::clone::SplitSignal
		
		jdelay_cubic.setParameterT(0, 1000.); // jdsp::jdelay_cubic::Limit
		;                                     // jdelay_cubic::DelayTime is automated
		
		; // faust::shiftsemitones is automated
		; // faust::windowsamples is automated
		; // faust::xfadesamples is automated
		
		; // faust32::shiftsemitones is automated
		; // faust32::windowsamples is automated
		; // faust32::xfadesamples is automated
		
		;                              // jpanner1::Pan is automated
		jpanner1.setParameterT(1, 1.); // jdsp::jpanner::Rule
		
		;                            // gain3::Gain is automated
		gain3.setParameterT(1, 20.); // core::gain::Smoothing
		gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 32.);
		this->setParameterT(1, 0.);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 0.65);
		this->setParameterT(4, 0.96);
		this->setParameterT(5, 0.368801);
		this->setParameterT(6, 0.817171);
		this->setParameterT(7, 1.);
		this->setExternalData({}, -1);
	}
	~instance() override
	{
		// Cleanup external data references --------------------------------------------------------
		
		this->setExternalData({}, -1);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool isProcessingHiseEvent() { return true; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(1).getT(1).getT(0).setExternalData(b, index); // spacer2_impl::pack_resizer_t
		this->getT(0).getT(1).getT(1).getT(1).setExternalData(b, index); // spacer2_impl::clone_pack_t<NV>
	}
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
using spacer2 = wrap::node<spacer2_impl::instance<NV>>;
}


