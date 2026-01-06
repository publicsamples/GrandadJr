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

using global_cable_t_index = runtime_target::indexers::fix_hash<3357039>;

template <int NV>
using global_cable_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<math::add<NV>, 0>, 
                                          parameter::plain<math::add<NV>, 0>, 
                                          parameter::plain<math::add<NV>, 0>>;

template <int NV>
using global_cable_t = routing::global_cable<global_cable_t_index, global_cable_mod<NV>>;
using global_cable1_t_index = runtime_target::indexers::fix_hash<3357040>;

template <int NV> using global_cable1_mod = global_cable_mod<NV>;

template <int NV>
using global_cable1_t = routing::global_cable<global_cable1_t_index, global_cable1_mod<NV>>;
using global_cable3_t_index = runtime_target::indexers::fix_hash<3357041>;

template <int NV> using global_cable3_mod = global_cable_mod<NV>;

template <int NV>
using global_cable3_t = routing::global_cable<global_cable3_t_index, global_cable3_mod<NV>>;
using global_cable2_t_index = global_cable3_t_index;

template <int NV> using global_cable2_mod = global_cable_mod<NV>;

template <int NV>
using global_cable2_t = routing::global_cable<global_cable2_t_index, global_cable2_mod<NV>>;

template <int NV>
using split3_t = container::split<parameter::empty, 
                                  wrap::fix<1, global_cable_t<NV>>, 
                                  global_cable1_t<NV>, 
                                  global_cable3_t<NV>, 
                                  global_cable2_t<NV>>;
template <int NV>
using branch_t = container::branch<parameter::empty, 
                                   wrap::fix<1, math::add<NV>>, 
                                   math::add<NV>, 
                                   math::add<NV>, 
                                   math::add<NV>>;

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
using pma_t = control::pma<NV, 
                           parameter::plain<xfader_t<NV>, 0>>;
template <int NV>
using peak_t = wrap::mod<parameter::plain<pma_t<NV>, 0>, 
                         wrap::no_data<core::peak>>;

template <int NV>
using chain9_t = container::chain<parameter::empty, 
                                  wrap::fix<1, branch_t<NV>>, 
                                  peak_t<NV>, 
                                  math::clear<NV>>;

template <int NV>
using chain2_t = container::chain<parameter::empty, 
                                  wrap::fix<1, chain9_t<NV>>, 
                                  pma_t<NV>>;
template <int NV> using branch1_t = branch_t<NV>;

template <int NV>
using clone_pack_t = wrap::data<control::clone_pack<parameter::cloned<parameter::plain<project::Pshift<NV>, 3>>>, 
                                data::external::sliderpack<0>>;
template <int NV>
using pma1_t = control::pma<NV, 
                            parameter::plain<clone_pack_t<NV>, 1>>;
template <int NV>
using peak1_t = wrap::mod<parameter::plain<pma1_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain10_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch1_t<NV>>, 
                                   peak1_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain3_t = container::chain<parameter::empty, 
                                  wrap::fix<1, chain10_t<NV>>, 
                                  pma1_t<NV>>;
template <int NV> using branch3_t = branch_t<NV>;

DECLARE_PARAMETER_RANGE_STEP(pma2_mod_0Range, 
                             0., 
                             100., 
                             0.01);

template <int NV>
using pma2_mod_0 = parameter::from0To1<project::comb<NV>, 
                                       1, 
                                       pma2_mod_0Range>;

template <int NV>
using pma2_mod = parameter::chain<ranges::Identity, 
                                  pma2_mod_0<NV>, 
                                  parameter::plain<project::bpf<NV>, 1>, 
                                  parameter::plain<project::Hpf<NV>, 1>, 
                                  parameter::plain<project::Lpf<NV>, 1>>;

template <int NV>
using pma2_t = control::pma<NV, pma2_mod<NV>>;
template <int NV>
using peak2_t = wrap::mod<parameter::plain<pma2_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain11_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch3_t<NV>>, 
                                   peak2_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain6_t = container::chain<parameter::empty, 
                                  wrap::fix<1, chain11_t<NV>>, 
                                  pma2_t<NV>>;

template <int NV>
using split4_t = container::split<parameter::empty, 
                                  wrap::fix<1, chain2_t<NV>>, 
                                  chain3_t<NV>, 
                                  chain6_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split3_t<NV>>, 
                                     math::clear<NV>, 
                                     split4_t<NV>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>>;

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
using chain4_t = container::chain<parameter::empty, 
                                  wrap::fix<2, project::Lpf<NV>>>;

template <int NV>
using chain7_t = container::chain<parameter::empty, 
                                  wrap::fix<2, project::Hpf<NV>>>;

template <int NV>
using chain8_t = container::chain<parameter::empty, 
                                  wrap::fix<2, project::bpf<NV>>>;

template <int NV>
using chain12_t = container::chain<parameter::empty, 
                                   wrap::fix<2, project::comb<NV>>>;
template <int NV>
using branch2_t = container::branch<parameter::empty, 
                                    wrap::fix<2, chain4_t<NV>>, 
                                    chain7_t<NV>, 
                                    chain8_t<NV>, 
                                    chain12_t<NV>>;

template <int NV>
using chain5_t = container::chain<parameter::empty, 
                                  wrap::fix<2, clone_pack_t<NV>>, 
                                  split1_t<NV>, 
                                  clone1_t<NV>, 
                                  branch2_t<NV>, 
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

template <int NV>
using deltime = parameter::from0To1<spacer2_impl::clone_cable_t<NV>, 
                                    1, 
                                    spacer2_impl::clone_cable3_modRange>;

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

DECLARE_PARAMETER_RANGE_STEP(fb_1Range, 
                             0., 
                             3., 
                             1.);

template <int NV>
using fb_1 = parameter::from0To1<spacer2_impl::branch1_t<NV>, 
                                 0, 
                                 fb_1Range>;

template <int NV>
using fb = parameter::chain<ranges::Identity, 
                            parameter::plain<spacer2_impl::clone_cable8_t<NV>, 1>, 
                            fb_1<NV>>;

DECLARE_PARAMETER_RANGE_STEP(MixSrc_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using MixSrc_0 = parameter::from0To1<spacer2_impl::branch_t<NV>, 
                                     0, 
                                     fb_1Range>;

template <int NV>
using MixSrc = parameter::chain<MixSrc_InputRange, MixSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(q_0Range, 
                             0.5, 
                             10., 
                             0.01);

template <int NV>
using q_0 = parameter::from0To1<project::Lpf<NV>, 
                                0, 
                                q_0Range>;

template <int NV>
using q_1 = parameter::from0To1<project::Hpf<NV>, 
                                0, 
                                q_0Range>;

template <int NV>
using q_2 = parameter::from0To1<project::bpf<NV>, 
                                0, 
                                q_0Range>;

template <int NV>
using q = parameter::chain<ranges::Identity, 
                           q_0<NV>, 
                           q_1<NV>, 
                           q_2<NV>, 
                           parameter::plain<project::comb<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(CutSrc_InputRange, 
                             1., 
                             4., 
                             1.);
template <int NV>
using CutSrc_0 = parameter::from0To1<spacer2_impl::branch3_t<NV>, 
                                     0, 
                                     fb_1Range>;

template <int NV>
using CutSrc = parameter::chain<CutSrc_InputRange, CutSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(FilterMode_InputRange, 
                             1., 
                             4., 
                             1.);
template <int NV>
using FilterMode_0 = parameter::from0To1<spacer2_impl::branch2_t<NV>, 
                                         0, 
                                         fb_1Range>;

template <int NV>
using FilterMode = parameter::chain<FilterMode_InputRange, FilterMode_0<NV>>;

template <int NV>
using Harm = parameter::plain<spacer2_impl::pma1_t<NV>, 
                              2>;
template <int NV>
using pan = parameter::plain<spacer2_impl::clone_cable3_t<NV>, 
                             1>;
using gain = parameter::empty;
template <int NV>
using Mix = parameter::plain<spacer2_impl::pma_t<NV>, 
                             2>;
using HarmSrc = gain;
template <int NV>
using HarmMod = parameter::plain<spacer2_impl::pma1_t<NV>, 
                                 1>;
template <int NV>
using MixMod = parameter::plain<spacer2_impl::pma_t<NV>, 
                                1>;
using delMod = gain;
using delSrc = gain;
template <int NV>
using Cut = parameter::plain<spacer2_impl::pma2_t<NV>, 
                             2>;
template <int NV>
using CutMod = parameter::plain<spacer2_impl::pma2_t<NV>, 
                                1>;
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
                                        HarmSrc, 
                                        HarmMod<NV>, 
                                        MixMod<NV>, 
                                        MixSrc<NV>, 
                                        delMod, 
                                        delSrc, 
                                        q<NV>, 
                                        Cut<NV>, 
                                        CutMod<NV>, 
                                        CutSrc<NV>, 
                                        FilterMode<NV>>;
}

template <int NV>
using spacer2_t_ = container::chain<spacer2_t_parameters::spacer2_t_plist<NV>, 
                                    wrap::fix<2, modchain_t<NV>>, 
                                    chain_t<NV>>;

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
		SNEX_METADATA_ENCODED_PARAMETERS(324)
		{
			0x005B, 0x0000, 0x4800, 0x7261, 0x006D, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x015B, 
            0x0000, 0x6400, 0x6C65, 0x6974, 0x656D, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x523F, 0x6AB8, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0002, 0x0000, 0x6977, 0x006E, 0xCCCD, 0x3DCC, 0x0000, 0x3F80, 
            0xC28F, 0x3F35, 0x0000, 0x3F80, 0x0000, 0x0000, 0x035B, 0x0000, 
            0x7000, 0x6E61, 0x0000, 0x8000, 0x00BF, 0x8000, 0x9A3F, 0x1999, 
            0x003E, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 0x6167, 
            0x6E69, 0x0000, 0x0000, 0x0000, 0x8000, 0x593F, 0xFBC8, 0x003E, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0005, 0x0000, 0x694D, 0x0078, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x065B, 0x0000, 0x6D00, 0x6E69, 0x0000, 0xC000, 
            0x00C1, 0xC000, 0x0041, 0x4000, 0x00C0, 0x8000, 0x003F, 0x8000, 
            0x5B3F, 0x0007, 0x0000, 0x616D, 0x0078, 0x0000, 0xC1C0, 0x0000, 
            0x41C0, 0x0000, 0x4080, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x085B, 
            0x0000, 0x7300, 0x6574, 0x0070, 0x0000, 0x0000, 0x0000, 0x4140, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x095B, 0x0000, 
            0x6600, 0x0062, 0x0000, 0x0000, 0x0000, 0x3F80, 0xCCCD, 0x3F01, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0A5B, 0x0000, 0x4800, 0x7261, 
            0x536D, 0x6372, 0x0000, 0x8000, 0x003F, 0x8800, 0x0041, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x000B, 0x0000, 0x6148, 
            0x6D72, 0x6F4D, 0x0064, 0x0000, 0xBF80, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0C5B, 0x0000, 0x4D00, 
            0x7869, 0x6F4D, 0x0064, 0x0000, 0xBF80, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0D5B, 0x0000, 0x4D00, 
            0x7869, 0x7253, 0x0063, 0x0000, 0x3F80, 0x0000, 0x4188, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0E5B, 0x0000, 0x6400, 
            0x6C65, 0x6F4D, 0x0064, 0x0000, 0xBF80, 0x0000, 0x3F80, 0xA164, 
            0x3F12, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0F5B, 0x0000, 0x6400, 
            0x6C65, 0x7253, 0x0063, 0x0000, 0x3F80, 0x0000, 0x4188, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x105B, 0x0000, 0x7100, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x2A3F, 0x86D1, 0x003E, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0011, 0x0000, 0x7543, 0x0074, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x8833, 0x3F0D, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x125B, 0x0000, 0x4300, 0x7475, 0x6F4D, 0x0064, 0x0000, 
            0xBF80, 0x0000, 0x3F80, 0xFDB2, 0x3E3A, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x135B, 0x0000, 0x4300, 0x7475, 0x7253, 0x0063, 0x0000, 
            0x3F80, 0x0000, 0x4080, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x145B, 0x0000, 0x4600, 0x6C69, 0x6574, 0x4D72, 0x646F, 
            0x0065, 0x0000, 0x3F80, 0x0000, 0x4080, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& modchain = this->getT(0);                                       // spacer2_impl::modchain_t<NV>
		auto& split3 = this->getT(0).getT(0);                                 // spacer2_impl::split3_t<NV>
		auto& global_cable = this->getT(0).getT(0).getT(0);                   // spacer2_impl::global_cable_t<NV>
		auto& global_cable1 = this->getT(0).getT(0).getT(1);                  // spacer2_impl::global_cable1_t<NV>
		auto& global_cable3 = this->getT(0).getT(0).getT(2);                  // spacer2_impl::global_cable3_t<NV>
		auto& global_cable2 = this->getT(0).getT(0).getT(3);                  // spacer2_impl::global_cable2_t<NV>
		auto& clear = this->getT(0).getT(1);                                  // math::clear<NV>
		auto& split4 = this->getT(0).getT(2);                                 // spacer2_impl::split4_t<NV>
		auto& chain2 = this->getT(0).getT(2).getT(0);                         // spacer2_impl::chain2_t<NV>
		auto& chain9 = this->getT(0).getT(2).getT(0).getT(0);                 // spacer2_impl::chain9_t<NV>
		auto& branch = this->getT(0).getT(2).getT(0).getT(0).getT(0);         // spacer2_impl::branch_t<NV>
		auto& add = this->getT(0).getT(2).getT(0).getT(0).getT(0).getT(0);    // math::add<NV>
		auto& add3 = this->getT(0).getT(2).getT(0).getT(0).getT(0).getT(1);   // math::add<NV>
		auto& add2 = this->getT(0).getT(2).getT(0).getT(0).getT(0).getT(2);   // math::add<NV>
		auto& add1 = this->getT(0).getT(2).getT(0).getT(0).getT(0).getT(3);   // math::add<NV>
		auto& peak = this->getT(0).getT(2).getT(0).getT(0).getT(1);           // spacer2_impl::peak_t<NV>
		auto& clear1 = this->getT(0).getT(2).getT(0).getT(0).getT(2);         // math::clear<NV>
		auto& pma = this->getT(0).getT(2).getT(0).getT(1);                    // spacer2_impl::pma_t<NV>
		auto& chain3 = this->getT(0).getT(2).getT(1);                         // spacer2_impl::chain3_t<NV>
		auto& chain10 = this->getT(0).getT(2).getT(1).getT(0);                // spacer2_impl::chain10_t<NV>
		auto& branch1 = this->getT(0).getT(2).getT(1).getT(0).getT(0);        // spacer2_impl::branch1_t<NV>
		auto& add4 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(0);   // math::add<NV>
		auto& add5 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(1);   // math::add<NV>
		auto& add6 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(2);   // math::add<NV>
		auto& add7 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(3);   // math::add<NV>
		auto& peak1 = this->getT(0).getT(2).getT(1).getT(0).getT(1);          // spacer2_impl::peak1_t<NV>
		auto& clear2 = this->getT(0).getT(2).getT(1).getT(0).getT(2);         // math::clear<NV>
		auto& pma1 = this->getT(0).getT(2).getT(1).getT(1);                   // spacer2_impl::pma1_t<NV>
		auto& chain6 = this->getT(0).getT(2).getT(2);                         // spacer2_impl::chain6_t<NV>
		auto& chain11 = this->getT(0).getT(2).getT(2).getT(0);                // spacer2_impl::chain11_t<NV>
		auto& branch3 = this->getT(0).getT(2).getT(2).getT(0).getT(0);        // spacer2_impl::branch3_t<NV>
		auto& add8 = this->getT(0).getT(2).getT(2).getT(0).getT(0).getT(0);   // math::add<NV>
		auto& add9 = this->getT(0).getT(2).getT(2).getT(0).getT(0).getT(1);   // math::add<NV>
		auto& add10 = this->getT(0).getT(2).getT(2).getT(0).getT(0).getT(2);  // math::add<NV>
		auto& add11 = this->getT(0).getT(2).getT(2).getT(0).getT(0).getT(3);  // math::add<NV>
		auto& peak2 = this->getT(0).getT(2).getT(2).getT(0).getT(1);          // spacer2_impl::peak2_t<NV>
		auto& clear3 = this->getT(0).getT(2).getT(2).getT(0).getT(2);         // math::clear<NV>
		auto& pma2 = this->getT(0).getT(2).getT(2).getT(1);                   // spacer2_impl::pma2_t<NV>
		auto& chain = this->getT(1);                                          // spacer2_impl::chain_t<NV>
		auto& xfader = this->getT(1).getT(0);                                 // spacer2_impl::xfader_t<NV>
		auto& split = this->getT(1).getT(1);                                  // spacer2_impl::split_t<NV>
		auto& chain1 = this->getT(1).getT(1).getT(0);                         // spacer2_impl::chain1_t<NV>
		auto& gain = this->getT(1).getT(1).getT(0).getT(0);                   // core::gain<NV>
		auto& chain5 = this->getT(1).getT(1).getT(1);                         // spacer2_impl::chain5_t<NV>
		auto& clone_pack = this->getT(1).getT(1).getT(1).getT(0);             // spacer2_impl::clone_pack_t<NV>
		auto& split1 = this->getT(1).getT(1).getT(1).getT(1);                 // spacer2_impl::split1_t<NV>
		auto& clone_cable = this->getT(1).getT(1).getT(1).getT(1).getT(0);    // spacer2_impl::clone_cable_t<NV>
		auto& clone_cable3 = this->getT(1).getT(1).getT(1).getT(1).getT(1);   // spacer2_impl::clone_cable3_t<NV>
		auto& clone_cable4 = this->getT(1).getT(1).getT(1).getT(1).getT(2);   // spacer2_impl::clone_cable4_t<NV>
		auto& clone_cable6 = this->getT(1).getT(1).getT(1).getT(1).getT(3);   // spacer2_impl::clone_cable6_t<NV>
		auto& clone_cable5 = this->getT(1).getT(1).getT(1).getT(1).getT(4);   // spacer2_impl::clone_cable5_t<NV>
		auto& clone_cable8 = this->getT(1).getT(1).getT(1).getT(1).getT(5);   // spacer2_impl::clone_cable8_t<NV>
		auto& clone_cable7 = this->getT(1).getT(1).getT(1).getT(1).getT(6);   // spacer2_impl::clone_cable7_t<NV>
		auto& clone1 = this->getT(1).getT(1).getT(1).getT(2);                 // spacer2_impl::clone1_t<NV>                 // spacer2_impl::clone1_child_t<NV>
		auto jdelay_cubic = this->getT(1).getT(1).getT(1).getT(2).getT(0);    // jdsp::jdelay_cubic<NV>
		auto Pshift = this->getT(1).getT(1).getT(1).getT(2).getT(1);          // project::Pshift<NV>
		auto jpanner1 = this->getT(1).getT(1).getT(1).getT(2).getT(2);        // jdsp::jpanner<NV>
		auto gain3 = this->getT(1).getT(1).getT(1).getT(2).getT(3);           // core::gain<NV>
		auto& branch2 = this->getT(1).getT(1).getT(1).getT(3);                // spacer2_impl::branch2_t<NV>
		auto& chain4 = this->getT(1).getT(1).getT(1).getT(3).getT(0);         // spacer2_impl::chain4_t<NV>
		auto& faust = this->getT(1).getT(1).getT(1).getT(3).getT(0).getT(0);  // project::Lpf<NV>
		auto& chain7 = this->getT(1).getT(1).getT(1).getT(3).getT(1);         // spacer2_impl::chain7_t<NV>
		auto& faust1 = this->getT(1).getT(1).getT(1).getT(3).getT(1).getT(0); // project::Hpf<NV>
		auto& chain8 = this->getT(1).getT(1).getT(1).getT(3).getT(2);         // spacer2_impl::chain8_t<NV>
		auto& faust2 = this->getT(1).getT(1).getT(1).getT(3).getT(2).getT(0); // project::bpf<NV>
		auto& chain12 = this->getT(1).getT(1).getT(1).getT(3).getT(3);        // spacer2_impl::chain12_t<NV>
		auto& faust3 = this->getT(1).getT(1).getT(1).getT(3).getT(3).getT(0); // project::comb<NV>
		auto& gain1 = this->getT(1).getT(1).getT(1).getT(4);                  // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, pma1); // Harm -> pma1::Add
		
		this->getParameterT(1).connectT(0, clone_cable); // deltime -> clone_cable::Value
		
		this->getParameterT(2).connectT(0, clone_cable7); // win -> clone_cable7::Value
		
		this->getParameterT(3).connectT(0, clone_cable3); // pan -> clone_cable3::Value
		
		this->getParameterT(5).connectT(0, pma); // Mix -> pma::Add
		
		this->getParameterT(6).connectT(0, clone_cable4); // min -> clone_cable4::Value
		
		this->getParameterT(7).connectT(0, clone_cable6); // max -> clone_cable6::Value
		
		this->getParameterT(8).connectT(0, clone_cable5); // step -> clone_cable5::Value
		
		auto& fb_p = this->getParameterT(9);
		fb_p.connectT(0, clone_cable8); // fb -> clone_cable8::Value
		fb_p.connectT(1, branch1);      // fb -> branch1::Index
		
		this->getParameterT(11).connectT(0, pma1); // HarmMod -> pma1::Multiply
		
		this->getParameterT(12).connectT(0, pma); // MixMod -> pma::Multiply
		
		this->getParameterT(13).connectT(0, branch); // MixSrc -> branch::Index
		
		auto& q_p = this->getParameterT(16);
		q_p.connectT(0, faust);  // q -> faust::Q
		q_p.connectT(1, faust1); // q -> faust1::Q
		q_p.connectT(2, faust2); // q -> faust2::Q
		q_p.connectT(3, faust3); // q -> faust3::aN
		
		this->getParameterT(17).connectT(0, pma2); // Cut -> pma2::Add
		
		this->getParameterT(18).connectT(0, pma2); // CutMod -> pma2::Multiply
		
		this->getParameterT(19).connectT(0, branch3); // CutSrc -> branch3::Index
		
		this->getParameterT(20).connectT(0, branch2); // FilterMode -> branch2::Index
		
		// Modulation Connections ------------------------------------------------------------------
		
		global_cable.getWrappedObject().getParameter().connectT(0, add);    // global_cable -> add::Value
		global_cable.getWrappedObject().getParameter().connectT(1, add4);   // global_cable -> add4::Value
		global_cable.getWrappedObject().getParameter().connectT(2, add8);   // global_cable -> add8::Value
		global_cable1.getWrappedObject().getParameter().connectT(0, add3);  // global_cable1 -> add3::Value
		global_cable1.getWrappedObject().getParameter().connectT(1, add5);  // global_cable1 -> add5::Value
		global_cable1.getWrappedObject().getParameter().connectT(2, add9);  // global_cable1 -> add9::Value
		global_cable3.getWrappedObject().getParameter().connectT(0, add2);  // global_cable3 -> add2::Value
		global_cable3.getWrappedObject().getParameter().connectT(1, add6);  // global_cable3 -> add6::Value
		global_cable3.getWrappedObject().getParameter().connectT(2, add10); // global_cable3 -> add10::Value
		global_cable2.getWrappedObject().getParameter().connectT(0, add1);  // global_cable2 -> add1::Value
		global_cable2.getWrappedObject().getParameter().connectT(1, add7);  // global_cable2 -> add7::Value
		global_cable2.getWrappedObject().getParameter().connectT(2, add11); // global_cable2 -> add11::Value
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);                             // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1);                            // xfader -> gain1::Gain
		pma.getWrappedObject().getParameter().connectT(0, xfader);               // pma -> xfader::Value
		peak.getParameter().connectT(0, pma);                                    // peak -> pma::Value
		clone_pack.getWrappedObject().getParameter().connectT(0, Pshift);        // clone_pack -> Pshift::value
		pma1.getWrappedObject().getParameter().connectT(0, clone_pack);          // pma1 -> clone_pack::Value
		peak1.getParameter().connectT(0, pma1);                                  // peak1 -> pma1::Value
		pma2.getWrappedObject().getParameter().connectT(0, faust3);              // pma2 -> faust3::del
		pma2.getWrappedObject().getParameter().connectT(1, faust2);              // pma2 -> faust2::freq
		pma2.getWrappedObject().getParameter().connectT(2, faust1);              // pma2 -> faust1::freq
		pma2.getWrappedObject().getParameter().connectT(3, faust);               // pma2 -> faust::freq
		peak2.getParameter().connectT(0, pma2);                                  // peak2 -> pma2::Value
		clone_cable.getWrappedObject().getParameter().connectT(0, jdelay_cubic); // clone_cable -> jdelay_cubic::DelayTime
		clone_cable3.getWrappedObject().getParameter().connectT(0, jpanner1);    // clone_cable3 -> jpanner1::Pan
		clone_cable4.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable4 -> Pshift::min
		clone_cable6.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable6 -> Pshift::max
		clone_cable5.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable5 -> Pshift::step
		clone_cable8.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable8 -> Pshift::feed
		clone_cable7.getWrappedObject().getParameter().connectT(0, Pshift);      // clone_cable7 -> Pshift::win
		
		// Default Values --------------------------------------------------------------------------
		
		global_cable.setParameterT(0, 1.); // routing::global_cable::Value
		
		global_cable1.setParameterT(0, 1.); // routing::global_cable::Value
		
		global_cable3.setParameterT(0, 1.); // routing::global_cable::Value
		
		global_cable2.setParameterT(0, 1.); // routing::global_cable::Value
		
		clear.setParameterT(0, 0.); // math::clear::Value
		
		; // branch::Index is automated
		
		; // add::Value is automated
		
		; // add3::Value is automated
		
		; // add2::Value is automated
		
		; // add1::Value is automated
		
		clear1.setParameterT(0, 0.); // math::clear::Value
		
		; // pma::Value is automated
		; // pma::Multiply is automated
		; // pma::Add is automated
		
		; // branch1::Index is automated
		
		; // add4::Value is automated
		
		; // add5::Value is automated
		
		; // add6::Value is automated
		
		; // add7::Value is automated
		
		clear2.setParameterT(0, 0.); // math::clear::Value
		
		; // pma1::Value is automated
		; // pma1::Multiply is automated
		; // pma1::Add is automated
		
		; // branch3::Index is automated
		
		; // add8::Value is automated
		
		; // add9::Value is automated
		
		; // add10::Value is automated
		
		; // add11::Value is automated
		
		clear3.setParameterT(0, 0.); // math::clear::Value
		
		; // pma2::Value is automated
		; // pma2::Multiply is automated
		; // pma2::Add is automated
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
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
		
		; // branch2::Index is automated
		
		; // faust::Q is automated
		; // faust::freq is automated
		
		; // faust1::Q is automated
		; // faust1::freq is automated
		
		; // faust2::Q is automated
		; // faust2::freq is automated
		
		; // faust3::aN is automated
		; // faust3::del is automated
		
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
		this->setParameterT(16, 0.263315);
		this->setParameterT(17, 0.552859);
		this->setParameterT(18, 0.182608);
		this->setParameterT(19, 1.);
		this->setParameterT(20, 1.);
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
		
		this->getT(0).getT(0).getT(0).connectToRuntimeTarget(addConnection, c); // spacer2_impl::global_cable_t<NV>
		this->getT(0).getT(0).getT(1).connectToRuntimeTarget(addConnection, c); // spacer2_impl::global_cable1_t<NV>
		this->getT(0).getT(0).getT(2).connectToRuntimeTarget(addConnection, c); // spacer2_impl::global_cable3_t<NV>
		this->getT(0).getT(0).getT(3).connectToRuntimeTarget(addConnection, c); // spacer2_impl::global_cable2_t<NV>
	}
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(2).getT(0).getT(0).getT(1).setExternalData(b, index); // spacer2_impl::peak_t<NV>
		this->getT(0).getT(2).getT(1).getT(0).getT(1).setExternalData(b, index); // spacer2_impl::peak1_t<NV>
		this->getT(0).getT(2).getT(2).getT(0).getT(1).setExternalData(b, index); // spacer2_impl::peak2_t<NV>
		this->getT(1).getT(1).getT(1).getT(0).setExternalData(b, index);         // spacer2_impl::clone_pack_t<NV>
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


