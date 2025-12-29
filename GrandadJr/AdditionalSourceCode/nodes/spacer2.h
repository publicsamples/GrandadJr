#pragma once

#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
#include "Pshift.h"
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
using global_mod_t_index = runtime_target::indexers::fix_hash<1>;
using global_mod_t_config = modulation::config::dynamic;

template <int NV>
using clone_pack_t = wrap::data<control::clone_pack<parameter::cloned<parameter::plain<project::Pshift<NV>, 3>>>, 
                                data::external::sliderpack<0>>;
template <int NV>
using global_mod_t = wrap::mod<parameter::plain<clone_pack_t<NV>, 1>, 
                               wrap::no_data<core::global_mod<NV, global_mod_t_index, global_mod_t_config>>>;

template <int NV>
using chain6_t = container::chain<parameter::empty, 
                                  wrap::fix<1, global_mod_t<NV>>>;
using global_mod1_t_index = global_mod_t_index;
using global_mod1_t_config = global_mod_t_config;

template <int NV>
using global_mod1_t = wrap::mod<parameter::plain<xfader_t<NV>, 0>, 
                                wrap::no_data<core::global_mod<NV, global_mod1_t_index, global_mod1_t_config>>>;

template <int NV>
using chain7_t = container::chain<parameter::empty, 
                                  wrap::fix<1, global_mod1_t<NV>>>;
using global_mod2_t_index = global_mod_t_index;
using global_mod2_t_config = global_mod_t_config;

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
DECLARE_PARAMETER_RANGE(global_mod2_modRange, 
                        -1., 
                        1.);

template <int NV>
using global_mod2_mod = parameter::from0To1<clone_cable_t<NV>, 
                                            1, 
                                            global_mod2_modRange>;

template <int NV>
using global_mod2_t = wrap::mod<global_mod2_mod<NV>, 
                                wrap::no_data<core::global_mod<NV, global_mod2_t_index, global_mod2_t_config>>>;

template <int NV>
using chain8_t = container::chain<parameter::empty, 
                                  wrap::fix<1, global_mod2_t<NV>>>;
using global_mod3_t_index = global_mod_t_index;
using global_mod3_t_config = global_mod_t_config;
template <int NV>
using global_mod3_t = wrap::no_data<core::global_mod<NV, global_mod3_t_index, global_mod3_t_config>>;

template <int NV>
using chain14_t = container::chain<parameter::empty, 
                                   wrap::fix<1, global_mod3_t<NV>>>;

template <int NV>
using split2_t = container::split<parameter::empty, 
                                  wrap::fix<1, chain6_t<NV>>, 
                                  chain7_t<NV>, 
                                  chain8_t<NV>, 
                                  chain14_t<NV>>;

template <int NV>
using modchain2_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, split2_t<NV>>>;

template <int NV>
using modchain2_t = wrap::control_rate<modchain2_t_<NV>>;

template <int NV>
using clone_cable3_mod = parameter::from0To1<jdsp::jpanner<NV>, 
                                             0, 
                                             global_mod2_modRange>;

template <int NV>
using clone_cable3_t = control::clone_cable<parameter::cloned<clone_cable3_mod<NV>>, 
                                            duplilogic::spread>;

DECLARE_PARAMETER_RANGE_STEP(clone_cable4_modRange, 
                             -24., 
                             24., 
                             1.);

template <int NV>
using clone_cable4_mod = parameter::from0To1<project::Pshift<NV>, 
                                             0, 
                                             clone_cable4_modRange>;

template <int NV>
using clone_cable4_t = control::clone_cable<parameter::cloned<clone_cable4_mod<NV>>, 
                                            duplilogic::fixed>;

template <int NV>
using clone_cable6_mod = parameter::from0To1<project::Pshift<NV>, 
                                             1, 
                                             clone_cable4_modRange>;

template <int NV>
using clone_cable6_t = control::clone_cable<parameter::cloned<clone_cable6_mod<NV>>, 
                                            duplilogic::fixed>;

DECLARE_PARAMETER_RANGE_STEP(clone_cable5_modRange, 
                             0., 
                             12., 
                             1.);

template <int NV>
using clone_cable5_mod = parameter::from0To1<project::Pshift<NV>, 
                                             2, 
                                             clone_cable5_modRange>;

template <int NV>
using clone_cable5_t = control::clone_cable<parameter::cloned<clone_cable5_mod<NV>>, 
                                            duplilogic::fixed>;

template <int NV>
using clone_cable8_t = control::clone_cable<parameter::cloned<parameter::plain<project::Pshift<NV>, 4>>, 
                                            duplilogic::fixed>;

template <int NV>
using clone_cable7_t = control::clone_cable<parameter::cloned<parameter::plain<project::Pshift<NV>, 5>>, 
                                            duplilogic::fixed>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<2, clone_cable_t<NV>>, 
                                  clone_cable3_t<NV>, 
                                  clone_cable4_t<NV>, 
                                  clone_cable6_t<NV>, 
                                  clone_cable5_t<NV>, 
                                  clone_cable8_t<NV>, 
                                  clone_cable7_t<NV>>;

template <int NV>
using clone1_child_t = container::chain<parameter::empty, 
                                        wrap::fix<2, jdsp::jdelay_cubic<NV>>, 
                                        project::Pshift<NV>, 
                                        jdsp::jpanner<NV>, 
                                        core::gain<NV>>;
template <int NV>
using clone1_t = wrap::fix_clonecopy<clone1_child_t<NV>, 32>;

template <int NV>
using chain5_t = container::chain<parameter::empty, 
                                  wrap::fix<2, modchain2_t<NV>>, 
                                  clone_pack_t<NV>, 
                                  split1_t<NV>, 
                                  clone1_t<NV>, 
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

DECLARE_PARAMETER_RANGE(win_InputRange, 
                        0.1, 
                        1.);

template <int NV>
using win = parameter::chain<win_InputRange, 
                             parameter::plain<spacer2_impl::clone_cable7_t<NV>, 1>>;

DECLARE_PARAMETER_RANGE_STEP(min_InputRange, 
                             -24., 
                             24., 
                             1.);

template <int NV>
using min = parameter::chain<min_InputRange, 
                             parameter::plain<spacer2_impl::clone_cable4_t<NV>, 1>>;

DECLARE_PARAMETER_RANGE_STEP(max_InputRange, 
                             -24., 
                             24., 
                             1.);

template <int NV>
using max = parameter::chain<max_InputRange, 
                             parameter::plain<spacer2_impl::clone_cable6_t<NV>, 1>>;

DECLARE_PARAMETER_RANGE_STEP(step_InputRange, 
                             0., 
                             12., 
                             1.);

template <int NV>
using step = parameter::chain<step_InputRange, 
                              parameter::plain<spacer2_impl::clone_cable5_t<NV>, 1>>;

DECLARE_PARAMETER_RANGE_STEP(HarmSrc_InputRange, 
                             1., 
                             17., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(HarmSrc_0Range, 
                             0., 
                             16., 
                             1.);

template <int NV>
using HarmSrc_0 = parameter::from0To1<spacer2_impl::global_mod_t<NV>, 
                                      0, 
                                      HarmSrc_0Range>;

template <int NV>
using HarmSrc = parameter::chain<HarmSrc_InputRange, HarmSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(MixSrc_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using MixSrc_0 = parameter::from0To1<spacer2_impl::global_mod1_t<NV>, 
                                     0, 
                                     HarmSrc_0Range>;

template <int NV>
using MixSrc = parameter::chain<MixSrc_InputRange, MixSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(delSrc_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using delSrc_0 = parameter::from0To1<spacer2_impl::global_mod2_t<NV>, 
                                     0, 
                                     HarmSrc_0Range>;

template <int NV>
using delSrc = parameter::chain<delSrc_InputRange, delSrc_0<NV>>;

template <int NV>
using Harm = parameter::plain<spacer2_impl::global_mod_t<NV>, 
                              1>;
template <int NV>
using deltime = parameter::plain<spacer2_impl::global_mod2_t<NV>, 
                                 1>;
template <int NV>
using pan = parameter::plain<spacer2_impl::clone_cable3_t<NV>, 
                             1>;
using gain = parameter::empty;
template <int NV>
using Mix = parameter::plain<spacer2_impl::global_mod1_t<NV>, 
                             1>;
template <int NV>
using fb = parameter::plain<spacer2_impl::clone_cable8_t<NV>, 
                            1>;
template <int NV>
using HarmMod = parameter::plain<spacer2_impl::global_mod_t<NV>, 
                                 4>;
template <int NV>
using MixMod = parameter::plain<spacer2_impl::global_mod1_t<NV>, 
                                4>;
template <int NV>
using delMod = parameter::plain<spacer2_impl::global_mod2_t<NV>, 
                                4>;
template <int NV>
using spacer2_t_plist = parameter::list<Harm<NV>, 
                                        deltime<NV>, 
                                        win<NV>, 
                                        pan<NV>, 
                                        gain, 
                                        Mix<NV>, 
                                        min<NV>, 
                                        max<NV>, 
                                        step<NV>, 
                                        fb<NV>, 
                                        HarmSrc<NV>, 
                                        HarmMod<NV>, 
                                        MixMod<NV>, 
                                        MixSrc<NV>, 
                                        delMod<NV>, 
                                        delSrc<NV>>;
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
		SNEX_METADATA_ENCODED_PARAMETERS(262)
		{
			0x005C, 0x0000, 0x0000, 0x6148, 0x6D72, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x005C, 0x0001, 0x0000, 0x6564, 0x746C, 0x6D69, 0x0065, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x523F, 0x6AB8, 0x003F, 0x8000, 0x003F, 
            0x0000, 0x5C00, 0x0200, 0x0000, 0x7700, 0x6E69, 0x0000, 0xCCCD, 
            0x3DCC, 0x0000, 0x3F80, 0xC28F, 0x3F35, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x005C, 0x0003, 0x0000, 0x6170, 0x006E, 0x0000, 0x8000, 
            0x00BF, 0x8000, 0x9A3F, 0x1999, 0x003E, 0x8000, 0x003F, 0x0000, 
            0x5C00, 0x0400, 0x0000, 0x6700, 0x6961, 0x006E, 0x0000, 0x0000, 
            0x0000, 0x8000, 0x593F, 0xFBC8, 0x003E, 0x8000, 0x003F, 0x0000, 
            0x5C00, 0x0500, 0x0000, 0x4D00, 0x7869, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x005C, 0x0006, 0x0000, 0x696D, 0x006E, 0x0000, 0xC000, 0x00C1, 
            0xC000, 0x0041, 0x4000, 0x00C0, 0x8000, 0x003F, 0x8000, 0x5C3F, 
            0x0700, 0x0000, 0x6D00, 0x7861, 0x0000, 0x0000, 0xC1C0, 0x0000, 
            0x41C0, 0x0000, 0x4080, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x005C, 
            0x0008, 0x0000, 0x7473, 0x7065, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x4140, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x005C, 
            0x0009, 0x0000, 0x6266, 0x0000, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0xCCCD, 0x3F01, 0x0000, 0x3F80, 0x0000, 0x0000, 0x005C, 0x000A, 
            0x0000, 0x6148, 0x6D72, 0x7253, 0x0063, 0x0000, 0x8000, 0x003F, 
            0x8800, 0x0041, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x5C3F, 
            0x0B00, 0x0000, 0x4800, 0x7261, 0x4D6D, 0x646F, 0x0000, 0x0000, 
            0xBF80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x005C, 0x000C, 0x0000, 0x694D, 0x4D78, 0x646F, 0x0000, 
            0x0000, 0xBF80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x005C, 0x000D, 0x0000, 0x694D, 0x5378, 0x6372, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x4188, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x005C, 0x000E, 0x0000, 0x6564, 0x4D6C, 
            0x646F, 0x0000, 0x0000, 0xBF80, 0x0000, 0x3F80, 0xA164, 0x3F12, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x005C, 0x000F, 0x0000, 0x6564, 
            0x536C, 0x6372, 0x0000, 0x0000, 0x3F80, 0x0000, 0x4188, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000
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
		// Node References -------------------------------------------------------------------------
		
		auto& chain = this->getT(0);                                                       // spacer2_impl::chain_t<NV>
		auto& xfader = this->getT(0).getT(0);                                              // spacer2_impl::xfader_t<NV>
		auto& split = this->getT(0).getT(1);                                               // spacer2_impl::split_t<NV>
		auto& chain1 = this->getT(0).getT(1).getT(0);                                      // spacer2_impl::chain1_t<NV>
		auto& gain = this->getT(0).getT(1).getT(0).getT(0);                                // core::gain<NV>
		auto& chain5 = this->getT(0).getT(1).getT(1);                                      // spacer2_impl::chain5_t<NV>
		auto& modchain2 = this->getT(0).getT(1).getT(1).getT(0);                           // spacer2_impl::modchain2_t<NV>
		auto& split2 = this->getT(0).getT(1).getT(1).getT(0).getT(0);                      // spacer2_impl::split2_t<NV>
		auto& chain6 = this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(0);              // spacer2_impl::chain6_t<NV>
		auto& global_mod = this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(0).getT(0);  // spacer2_impl::global_mod_t<NV>
		auto& chain7 = this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(1);              // spacer2_impl::chain7_t<NV>
		auto& global_mod1 = this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(1).getT(0); // spacer2_impl::global_mod1_t<NV>
		auto& chain8 = this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(2);              // spacer2_impl::chain8_t<NV>
		auto& global_mod2 = this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(2).getT(0); // spacer2_impl::global_mod2_t<NV>
		auto& chain14 = this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(3);             // spacer2_impl::chain14_t<NV>
		auto& global_mod3 = this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(3).getT(0); // spacer2_impl::global_mod3_t<NV>
		auto& clone_pack = this->getT(0).getT(1).getT(1).getT(1);                          // spacer2_impl::clone_pack_t<NV>
		auto& split1 = this->getT(0).getT(1).getT(1).getT(2);                              // spacer2_impl::split1_t<NV>
		auto& clone_cable = this->getT(0).getT(1).getT(1).getT(2).getT(0);                 // spacer2_impl::clone_cable_t<NV>
		auto& clone_cable3 = this->getT(0).getT(1).getT(1).getT(2).getT(1);                // spacer2_impl::clone_cable3_t<NV>
		auto& clone_cable4 = this->getT(0).getT(1).getT(1).getT(2).getT(2);                // spacer2_impl::clone_cable4_t<NV>
		auto& clone_cable6 = this->getT(0).getT(1).getT(1).getT(2).getT(3);                // spacer2_impl::clone_cable6_t<NV>
		auto& clone_cable5 = this->getT(0).getT(1).getT(1).getT(2).getT(4);                // spacer2_impl::clone_cable5_t<NV>
		auto& clone_cable8 = this->getT(0).getT(1).getT(1).getT(2).getT(5);                // spacer2_impl::clone_cable8_t<NV>
		auto& clone_cable7 = this->getT(0).getT(1).getT(1).getT(2).getT(6);                // spacer2_impl::clone_cable7_t<NV>
		auto& clone1 = this->getT(0).getT(1).getT(1).getT(3);                              // spacer2_impl::clone1_t<NV>                              // spacer2_impl::clone1_child_t<NV>
		auto jdelay_cubic = this->getT(0).getT(1).getT(1).getT(3).getT(0);                 // jdsp::jdelay_cubic<NV>
		auto Pshift = this->getT(0).getT(1).getT(1).getT(3).getT(1);                       // project::Pshift<NV>
		auto jpanner1 = this->getT(0).getT(1).getT(1).getT(3).getT(2);                     // jdsp::jpanner<NV>
		auto gain3 = this->getT(0).getT(1).getT(1).getT(3).getT(3);                        // core::gain<NV>
		auto& gain1 = this->getT(0).getT(1).getT(1).getT(4);                               // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, global_mod); // Harm -> global_mod::Value
		
		this->getParameterT(1).connectT(0, global_mod2); // deltime -> global_mod2::Value
		
		this->getParameterT(2).connectT(0, clone_cable7); // win -> clone_cable7::Value
		
		this->getParameterT(3).connectT(0, clone_cable3); // pan -> clone_cable3::Value
		
		this->getParameterT(5).connectT(0, global_mod1); // Mix -> global_mod1::Value
		
		this->getParameterT(6).connectT(0, clone_cable4); // min -> clone_cable4::Value
		
		this->getParameterT(7).connectT(0, clone_cable6); // max -> clone_cable6::Value
		
		this->getParameterT(8).connectT(0, clone_cable5); // step -> clone_cable5::Value
		
		this->getParameterT(9).connectT(0, clone_cable8); // fb -> clone_cable8::Value
		
		this->getParameterT(10).connectT(0, global_mod); // HarmSrc -> global_mod::Index
		
		this->getParameterT(11).connectT(0, global_mod); // HarmMod -> global_mod::Intensity
		
		this->getParameterT(12).connectT(0, global_mod1); // MixMod -> global_mod1::Intensity
		
		this->getParameterT(13).connectT(0, global_mod1); // MixSrc -> global_mod1::Index
		
		this->getParameterT(14).connectT(0, global_mod2); // delMod -> global_mod2::Intensity
		
		this->getParameterT(15).connectT(0, global_mod2); // delSrc -> global_mod2::Index
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);                             // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1);                            // xfader -> gain1::Gain
		clone_pack.getWrappedObject().getParameter().connectT(0, Pshift);        // clone_pack -> Pshift::value
		global_mod.getParameter().connectT(0, clone_pack);                       // global_mod -> clone_pack::Value
		global_mod1.getParameter().connectT(0, xfader);                          // global_mod1 -> xfader::Value
		clone_cable.getWrappedObject().getParameter().connectT(0, jdelay_cubic); // clone_cable -> jdelay_cubic::DelayTime
		global_mod2.getParameter().connectT(0, clone_cable);                     // global_mod2 -> clone_cable::Value
		clone_cable3.getWrappedObject().getParameter().connectT(0, jpanner1);    // clone_cable3 -> jpanner1::Pan
		clone_cable4.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable4 -> Pshift::min
		clone_cable6.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable6 -> Pshift::max
		clone_cable5.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable5 -> Pshift::step
		clone_cable8.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable8 -> Pshift::feed
		clone_cable7.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable7 -> Pshift::win
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                // global_mod::Index is automated
		;                                // global_mod::Value is automated
		global_mod.setParameterT(2, 0.); // core::global_mod::ProcessSignal
		global_mod.setParameterT(3, 1.); // core::global_mod::Mode
		;                                // global_mod::Intensity is automated
		
		;                                 // global_mod1::Index is automated
		;                                 // global_mod1::Value is automated
		global_mod1.setParameterT(2, 0.); // core::global_mod::ProcessSignal
		global_mod1.setParameterT(3, 1.); // core::global_mod::Mode
		;                                 // global_mod1::Intensity is automated
		
		;                                 // global_mod2::Index is automated
		;                                 // global_mod2::Value is automated
		global_mod2.setParameterT(2, 0.); // core::global_mod::ProcessSignal
		global_mod2.setParameterT(3, 1.); // core::global_mod::Mode
		;                                 // global_mod2::Intensity is automated
		
		global_mod3.setParameterT(0, 0.); // core::global_mod::Index
		global_mod3.setParameterT(1, 1.); // core::global_mod::Value
		global_mod3.setParameterT(2, 0.); // core::global_mod::ProcessSignal
		global_mod3.setParameterT(3, 1.); // core::global_mod::Mode
		global_mod3.setParameterT(4, 1.); // core::global_mod::Intensity
		
		clone_pack.setParameterT(0, 32.); // control::clone_pack::NumClones
		;                                 // clone_pack::Value is automated
		
		;                                 // clone_cable::NumClones is deactivated
		;                                 // clone_cable::Value is automated
		clone_cable.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable3::NumClones is deactivated
		;                                  // clone_cable3::Value is automated
		clone_cable3.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable4::NumClones is deactivated
		;                                  // clone_cable4::Value is automated
		clone_cable4.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable6::NumClones is deactivated
		;                                  // clone_cable6::Value is automated
		clone_cable6.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable5::NumClones is deactivated
		;                                  // clone_cable5::Value is automated
		clone_cable5.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable8::NumClones is deactivated
		;                                  // clone_cable8::Value is automated
		clone_cable8.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable7::NumClones is deactivated
		;                                  // clone_cable7::Value is automated
		clone_cable7.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		clone1.setParameterT(0, 32.); // container::clone::NumClones
		clone1.setParameterT(1, 2.);  // container::clone::SplitSignal
		
		jdelay_cubic.setParameterT(0, 1000.); // jdsp::jdelay_cubic::Limit
		;                                     // jdelay_cubic::DelayTime is automated
		
		; // Pshift::min is automated
		; // Pshift::max is automated
		; // Pshift::step is automated
		; // Pshift::value is automated
		; // Pshift::feed is automated
		; // Pshift::win is automated
		
		;                              // jpanner1::Pan is automated
		jpanner1.setParameterT(1, 1.); // jdsp::jpanner::Rule
		
		gain3.setParameterT(0, -23.); // core::gain::Gain
		gain3.setParameterT(1, 20.);  // core::gain::Smoothing
		gain3.setParameterT(2, 0.);   // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 0.916875);
		this->setParameterT(2, 0.71);
		this->setParameterT(3, 0.15);
		this->setParameterT(4, 0.491763);
		this->setParameterT(5, 1.);
		this->setParameterT(6, -3.);
		this->setParameterT(7, 4.);
		this->setParameterT(8, 0.);
		this->setParameterT(9, 0.507031);
		this->setParameterT(10, 1.);
		this->setParameterT(11, 0.);
		this->setParameterT(12, 0.);
		this->setParameterT(13, 1.);
		this->setParameterT(14, 0.572775);
		this->setParameterT(15, 1.);
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
	
	void connectToRuntimeTarget(bool addConnection, const runtime_target::connection& c)
	{
		// Runtime target Connections --------------------------------------------------------------
		
		this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(0).getT(0).connectToRuntimeTarget(addConnection, c); // spacer2_impl::global_mod_t<NV>
		this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(1).getT(0).connectToRuntimeTarget(addConnection, c); // spacer2_impl::global_mod1_t<NV>
		this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(2).getT(0).connectToRuntimeTarget(addConnection, c); // spacer2_impl::global_mod2_t<NV>
		this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(3).getT(0).connectToRuntimeTarget(addConnection, c); // spacer2_impl::global_mod3_t<NV>
	}
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(0).getT(0).setExternalData(b, index); // spacer2_impl::global_mod_t<NV>
		this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(1).getT(0).setExternalData(b, index); // spacer2_impl::global_mod1_t<NV>
		this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(2).getT(0).setExternalData(b, index); // spacer2_impl::global_mod2_t<NV>
		this->getT(0).getT(1).getT(1).getT(0).getT(0).getT(3).getT(0).setExternalData(b, index); // spacer2_impl::global_mod3_t<NV>
		this->getT(0).getT(1).getT(1).getT(1).setExternalData(b, index);                         // spacer2_impl::clone_pack_t<NV>
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


