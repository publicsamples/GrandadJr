#pragma once

#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
#include "FeedJ.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace spacer1_impl
{
// ==============================| Node & Parameter type declarations |==============================

using global_cable_t_index = runtime_target::indexers::fix_hash<3357039>;

template <int NV>
using global_cable_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<math::add<NV>, 0>, 
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
using split2_t = container::split<parameter::empty, 
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

DECLARE_PARAMETER_RANGE(clone_cable5_modRange, 
                        -1., 
                        1.);

template <int NV>
using clone_cable5_mod = parameter::from0To1<project::FeedJ<NV>, 
                                             3, 
                                             clone_cable5_modRange>;

template <int NV>
using clone_cable5_t = control::clone_cable<parameter::cloned<clone_cable5_mod<NV>>, 
                                            duplilogic::spread>;
template <int NV>
using pma1_mod = parameter::from0To1<clone_cable5_t<NV>, 
                                     1, 
                                     clone_cable5_modRange>;

template <int NV>
using pma1_t = control::pma<NV, pma1_mod<NV>>;
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

template <int NV>
using clone_cable7_t = control::clone_cable<parameter::cloned<parameter::plain<project::FeedJ<NV>, 2>>, 
                                            duplilogic::fixed>;
template <int NV>
using pma3_t = control::pma<NV, 
                            parameter::plain<clone_cable7_t<NV>, 1>>;
template <int NV>
using peak3_t = wrap::mod<parameter::plain<pma3_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain14_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch3_t<NV>>, 
                                   peak3_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain13_t = container::chain<parameter::empty, 
                                   wrap::fix<1, chain14_t<NV>>, 
                                   pma3_t<NV>>;
template <int NV> using branch2_t = branch_t<NV>;

DECLARE_PARAMETER_RANGE_SKEW(clone_cable4_modRange, 
                             0., 
                             1000., 
                             0.30103);

template <int NV>
using clone_cable4_mod = parameter::from0To1<project::FeedJ<NV>, 
                                             0, 
                                             clone_cable4_modRange>;

template <int NV>
using clone_cable4_t = control::clone_cable<parameter::cloned<clone_cable4_mod<NV>>, 
                                            duplilogic::spread>;
template <int NV>
using smoothed_parameter32_mod = parameter::from0To1<clone_cable4_t<NV>, 
                                                     1, 
                                                     clone_cable5_modRange>;

template <int NV>
using smoothed_parameter32_t = wrap::mod<smoothed_parameter32_mod<NV>, 
                                         control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using pma2_t = control::pma<NV, 
                            parameter::plain<smoothed_parameter32_t<NV>, 0>>;
template <int NV>
using peak2_t = wrap::mod<parameter::plain<pma2_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain12_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch2_t<NV>>, 
                                   peak2_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain11_t = container::chain<parameter::empty, 
                                   wrap::fix<1, chain12_t<NV>>, 
                                   pma2_t<NV>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, chain2_t<NV>>, 
                                  chain3_t<NV>, 
                                  chain13_t<NV>, 
                                  chain11_t<NV>>;

template <int NV>
using modchain2_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, split2_t<NV>>, 
                                      math::clear<NV>, 
                                      split1_t<NV>>;

template <int NV>
using modchain2_t = wrap::control_rate<modchain2_t_<NV>>;

template <int NV>
using chain6_t = container::chain<parameter::empty, 
                                  wrap::fix<1, math::clear<NV>>, 
                                  xfader_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, chain6_t<NV>>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>>;

template <int NV>
using chain4_t = container::chain<parameter::empty, 
                                  wrap::fix<1, math::clear<NV>>, 
                                  clone_cable5_t<NV>>;

template <int NV>
using clone_cable6_t = control::clone_cable<parameter::cloned<parameter::plain<project::FeedJ<NV>, 1>>, 
                                            duplilogic::fixed>;

template <int NV>
using chain7_t = container::chain<parameter::empty, 
                                  wrap::fix<1, math::clear<NV>>, 
                                  clone_cable7_t<NV>>;

template <int NV>
using chain8_t = container::chain<parameter::empty, 
                                  wrap::fix<1, math::clear<NV>>, 
                                  smoothed_parameter32_t<NV>, 
                                  clone_cable4_t<NV>>;

template <int NV>
using split3_t = container::split<parameter::empty, 
                                  wrap::fix<1, chain4_t<NV>>, 
                                  clone_cable6_t<NV>, 
                                  chain7_t<NV>, 
                                  chain8_t<NV>>;

template <int NV>
using modchain1_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, split3_t<NV>>>;

template <int NV>
using modchain1_t = wrap::control_rate<modchain1_t_<NV>>;

template <int NV>
using clone_child_t = container::chain<parameter::empty, 
                                       wrap::fix<2, project::FeedJ<NV>>, 
                                       core::gain<NV>>;
template <int NV>
using clone_t = wrap::fix_clonecopy<clone_child_t<NV>, 32>;

template <int NV>
using fix8_block_t_ = container::chain<parameter::empty, 
                                       wrap::fix<2, modchain1_t<NV>>, 
                                       clone_t<NV>>;

template <int NV>
using fix8_block_t = wrap::fix_block<8, fix8_block_t_<NV>>;

template <int NV>
using chain5_t = container::chain<parameter::empty, 
                                  wrap::fix<2, fix8_block_t<NV>>, 
                                  core::gain<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, chain1_t<NV>>, 
                                 chain5_t<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, modchain2_t<NV>>, 
                                 modchain_t<NV>, 
                                 split_t<NV>>;

namespace spacer1_t_parameters
{
// Parameter list for spacer1_impl::spacer1_t ------------------------------------------------------

DECLARE_PARAMETER_RANGE(deltime_InputRange, 
                        -1., 
                        1.);

template <int NV>
using deltime = parameter::chain<deltime_InputRange, 
                                 parameter::plain<spacer1_impl::pma2_t<NV>, 2>>;

DECLARE_PARAMETER_RANGE(pan_InputRange, 
                        -1., 
                        1.);

template <int NV>
using pan = parameter::chain<pan_InputRange, 
                             parameter::plain<spacer1_impl::pma1_t<NV>, 2>>;

DECLARE_PARAMETER_RANGE_STEP(PanSrc_InputRange, 
                             1., 
                             4., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(PanSrc_0Range, 
                             0., 
                             3., 
                             1.);

template <int NV>
using PanSrc_0 = parameter::from0To1<spacer1_impl::branch1_t<NV>, 
                                     0, 
                                     PanSrc_0Range>;

template <int NV>
using PanSrc = parameter::chain<PanSrc_InputRange, PanSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(MixSrc_InputRange, 
                             1., 
                             4., 
                             1.);
template <int NV>
using MixSrc_0 = parameter::from0To1<spacer1_impl::branch_t<NV>, 
                                     0, 
                                     PanSrc_0Range>;

template <int NV>
using MixSrc = parameter::chain<MixSrc_InputRange, MixSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(LpSrc_InputRange, 
                             1., 
                             4., 
                             1.);
template <int NV>
using LpSrc_0 = parameter::from0To1<spacer1_impl::branch3_t<NV>, 
                                    0, 
                                    PanSrc_0Range>;

template <int NV>
using LpSrc = parameter::chain<LpSrc_InputRange, LpSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(delSrc_InputRange, 
                             1., 
                             4., 
                             1.);
template <int NV>
using delSrc_0 = parameter::from0To1<spacer1_impl::branch2_t<NV>, 
                                     0, 
                                     PanSrc_0Range>;

template <int NV>
using delSrc = parameter::chain<delSrc_InputRange, delSrc_0<NV>>;

template <int NV>
using Mix = parameter::plain<spacer1_impl::pma_t<NV>, 
                             2>;
template <int NV>
using LP = parameter::plain<spacer1_impl::pma3_t<NV>, 
                            2>;
template <int NV>
using feed = parameter::plain<spacer1_impl::clone_cable6_t<NV>, 
                              1>;
template <int NV>
using PanMod = parameter::plain<spacer1_impl::pma1_t<NV>, 
                                1>;
template <int NV>
using MixMod = parameter::plain<spacer1_impl::pma_t<NV>, 
                                1>;
template <int NV>
using LpMod = parameter::plain<spacer1_impl::pma3_t<NV>, 
                               1>;
template <int NV>
using delMod = parameter::plain<spacer1_impl::pma2_t<NV>, 
                                1>;
template <int NV>
using spacer1_t_plist = parameter::list<deltime<NV>, 
                                        pan<NV>, 
                                        Mix<NV>, 
                                        LP<NV>, 
                                        feed<NV>, 
                                        PanMod<NV>, 
                                        PanSrc<NV>, 
                                        MixMod<NV>, 
                                        MixSrc<NV>, 
                                        LpMod<NV>, 
                                        LpSrc<NV>, 
                                        delMod<NV>, 
                                        delSrc<NV>>;
}

template <int NV>
using spacer1_t_ = container::chain<spacer1_t_parameters::spacer1_t_plist<NV>, 
                                    wrap::fix<2, chain_t<NV>>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public spacer1_impl::spacer1_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(spacer1);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(202)
		{
			0x005B, 0x0000, 0x6400, 0x6C65, 0x6974, 0x656D, 0x0000, 0x8000, 
            0x00BF, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0001, 0x0000, 0x6170, 0x006E, 0x0000, 0xBF80, 0x0000, 
            0x3F80, 0xEB85, 0x3ED1, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 
            0x0000, 0x4D00, 0x7869, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 
            0x504C, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 0x6566, 0x6465, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x143F, 0x07AE, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0005, 0x0000, 0x6150, 0x4D6E, 0x646F, 
            0x0000, 0x8000, 0x00BF, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0006, 0x0000, 0x6150, 0x536E, 0x6372, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x0040, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x5B3F, 0x0007, 0x0000, 0x694D, 0x4D78, 0x646F, 
            0x0000, 0x8000, 0x00BF, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0008, 0x0000, 0x694D, 0x5378, 0x6372, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x0040, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x5B3F, 0x0009, 0x0000, 0x704C, 0x6F4D, 0x0064, 
            0x0000, 0xBF80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0A5B, 0x0000, 0x4C00, 0x5370, 0x6372, 0x0000, 
            0x8000, 0x003F, 0x8000, 0x0040, 0x4000, 0x0040, 0x8000, 0x003F, 
            0x8000, 0x5B3F, 0x000B, 0x0000, 0x6564, 0x4D6C, 0x646F, 0x0000, 
            0x8000, 0x00BF, 0x8000, 0x0A3F, 0x23D7, 0x00BC, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x000C, 0x0000, 0x6564, 0x536C, 0x6372, 0x0000, 
            0x8000, 0x003F, 0x8000, 0x0040, 0x4000, 0x0040, 0x8000, 0x003F, 
            0x8000, 0x003F
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& chain = this->getT(0);                                                        // spacer1_impl::chain_t<NV>
		auto& modchain2 = this->getT(0).getT(0);                                            // spacer1_impl::modchain2_t<NV>
		auto& split2 = this->getT(0).getT(0).getT(0);                                       // spacer1_impl::split2_t<NV>
		auto& global_cable = this->getT(0).getT(0).getT(0).getT(0);                         // spacer1_impl::global_cable_t<NV>
		auto& global_cable1 = this->getT(0).getT(0).getT(0).getT(1);                        // spacer1_impl::global_cable1_t<NV>
		auto& global_cable3 = this->getT(0).getT(0).getT(0).getT(2);                        // spacer1_impl::global_cable3_t<NV>
		auto& global_cable2 = this->getT(0).getT(0).getT(0).getT(3);                        // spacer1_impl::global_cable2_t<NV>
		auto& clear4 = this->getT(0).getT(0).getT(1);                                       // math::clear<NV>
		auto& split1 = this->getT(0).getT(0).getT(2);                                       // spacer1_impl::split1_t<NV>
		auto& chain2 = this->getT(0).getT(0).getT(2).getT(0);                               // spacer1_impl::chain2_t<NV>
		auto& chain9 = this->getT(0).getT(0).getT(2).getT(0).getT(0);                       // spacer1_impl::chain9_t<NV>
		auto& branch = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0);               // spacer1_impl::branch_t<NV>
		auto& add = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0).getT(0);          // math::add<NV>
		auto& add3 = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0).getT(1);         // math::add<NV>
		auto& add2 = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0).getT(2);         // math::add<NV>
		auto& add1 = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0).getT(3);         // math::add<NV>
		auto& peak = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(1);                 // spacer1_impl::peak_t<NV>
		auto& clear5 = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(2);               // math::clear<NV>
		auto& pma = this->getT(0).getT(0).getT(2).getT(0).getT(1);                          // spacer1_impl::pma_t<NV>
		auto& chain3 = this->getT(0).getT(0).getT(2).getT(1);                               // spacer1_impl::chain3_t<NV>
		auto& chain10 = this->getT(0).getT(0).getT(2).getT(1).getT(0);                      // spacer1_impl::chain10_t<NV>
		auto& branch1 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0);              // spacer1_impl::branch1_t<NV>
		auto& add4 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0).getT(0);         // math::add<NV>
		auto& add5 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0).getT(1);         // math::add<NV>
		auto& add6 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0).getT(2);         // math::add<NV>
		auto& add7 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0).getT(3);         // math::add<NV>
		auto& peak1 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(1);                // spacer1_impl::peak1_t<NV>
		auto& clear6 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(2);               // math::clear<NV>
		auto& pma1 = this->getT(0).getT(0).getT(2).getT(1).getT(1);                         // spacer1_impl::pma1_t<NV>
		auto& chain13 = this->getT(0).getT(0).getT(2).getT(2);                              // spacer1_impl::chain13_t<NV>
		auto& chain14 = this->getT(0).getT(0).getT(2).getT(2).getT(0);                      // spacer1_impl::chain14_t<NV>
		auto& branch3 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0);              // spacer1_impl::branch3_t<NV>
		auto& add12 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0).getT(0);        // math::add<NV>
		auto& add13 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0).getT(1);        // math::add<NV>
		auto& add14 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0).getT(2);        // math::add<NV>
		auto& add15 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0).getT(3);        // math::add<NV>
		auto& peak3 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(1);                // spacer1_impl::peak3_t<NV>
		auto& clear8 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(2);               // math::clear<NV>
		auto& pma3 = this->getT(0).getT(0).getT(2).getT(2).getT(1);                         // spacer1_impl::pma3_t<NV>
		auto& chain11 = this->getT(0).getT(0).getT(2).getT(3);                              // spacer1_impl::chain11_t<NV>
		auto& chain12 = this->getT(0).getT(0).getT(2).getT(3).getT(0);                      // spacer1_impl::chain12_t<NV>
		auto& branch2 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0);              // spacer1_impl::branch2_t<NV>
		auto& add8 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0).getT(0);         // math::add<NV>
		auto& add9 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0).getT(1);         // math::add<NV>
		auto& add10 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0).getT(2);        // math::add<NV>
		auto& add11 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0).getT(3);        // math::add<NV>
		auto& peak2 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(1);                // spacer1_impl::peak2_t<NV>
		auto& clear7 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(2);               // math::clear<NV>
		auto& pma2 = this->getT(0).getT(0).getT(2).getT(3).getT(1);                         // spacer1_impl::pma2_t<NV>
		auto& modchain = this->getT(0).getT(1);                                             // spacer1_impl::modchain_t<NV>
		auto& chain6 = this->getT(0).getT(1).getT(0);                                       // spacer1_impl::chain6_t<NV>
		auto& clear1 = this->getT(0).getT(1).getT(0).getT(0);                               // math::clear<NV>
		auto& xfader = this->getT(0).getT(1).getT(0).getT(1);                               // spacer1_impl::xfader_t<NV>
		auto& split = this->getT(0).getT(2);                                                // spacer1_impl::split_t<NV>
		auto& chain1 = this->getT(0).getT(2).getT(0);                                       // spacer1_impl::chain1_t<NV>
		auto& gain = this->getT(0).getT(2).getT(0).getT(0);                                 // core::gain<NV>
		auto& chain5 = this->getT(0).getT(2).getT(1);                                       // spacer1_impl::chain5_t<NV>
		auto& fix8_block = this->getT(0).getT(2).getT(1).getT(0);                           // spacer1_impl::fix8_block_t<NV>
		auto& modchain1 = this->getT(0).getT(2).getT(1).getT(0).getT(0);                    // spacer1_impl::modchain1_t<NV>
		auto& split3 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(0);               // spacer1_impl::split3_t<NV>
		auto& chain4 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(0).getT(0);       // spacer1_impl::chain4_t<NV>
		auto& clear = this->getT(0).getT(2).getT(1).getT(0).                                // math::clear<NV>
                      getT(0).getT(0).getT(0).getT(0);
		auto& clone_cable5 = this->getT(0).getT(2).getT(1).getT(0).                         // spacer1_impl::clone_cable5_t<NV>
                             getT(0).getT(0).getT(0).getT(1);
		auto& clone_cable6 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(0).getT(1); // spacer1_impl::clone_cable6_t<NV>
		auto& chain7 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(0).getT(2);       // spacer1_impl::chain7_t<NV>
		auto& clear2 = this->getT(0).getT(2).getT(1).getT(0).                               // math::clear<NV>
                       getT(0).getT(0).getT(2).getT(0);
		auto& clone_cable7 = this->getT(0).getT(2).getT(1).getT(0).                   // spacer1_impl::clone_cable7_t<NV>
                             getT(0).getT(0).getT(2).getT(1);
		auto& chain8 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(0).getT(3); // spacer1_impl::chain8_t<NV>
		auto& clear3 = this->getT(0).getT(2).getT(1).getT(0).                         // math::clear<NV>
                       getT(0).getT(0).getT(3).getT(0);
		auto& smoothed_parameter32 = this->getT(0).getT(2).getT(1).getT(0).   // spacer1_impl::smoothed_parameter32_t<NV>
                                     getT(0).getT(0).getT(3).getT(1);
		auto& clone_cable4 = this->getT(0).getT(2).getT(1).getT(0).           // spacer1_impl::clone_cable4_t<NV>
                             getT(0).getT(0).getT(3).getT(2);
		auto& clone = this->getT(0).getT(2).getT(1).getT(0).getT(1);          // spacer1_impl::clone_t<NV>          // spacer1_impl::clone_child_t<NV>
		auto FeedJ = this->getT(0).getT(2).getT(1).getT(0).getT(1).getT(0);   // project::FeedJ<NV>
		auto gain221 = this->getT(0).getT(2).getT(1).getT(0).getT(1).getT(1); // core::gain<NV>
		auto& gain1 = this->getT(0).getT(2).getT(1).getT(1);                  // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, pma2); // deltime -> pma2::Add
		
		this->getParameterT(1).connectT(0, pma1); // pan -> pma1::Add
		
		this->getParameterT(2).connectT(0, pma); // Mix -> pma::Add
		
		this->getParameterT(3).connectT(0, pma3); // LP -> pma3::Add
		
		this->getParameterT(4).connectT(0, clone_cable6); // feed -> clone_cable6::Value
		
		this->getParameterT(5).connectT(0, pma1); // PanMod -> pma1::Multiply
		
		this->getParameterT(6).connectT(0, branch1); // PanSrc -> branch1::Index
		
		this->getParameterT(7).connectT(0, pma); // MixMod -> pma::Multiply
		
		this->getParameterT(8).connectT(0, branch); // MixSrc -> branch::Index
		
		this->getParameterT(9).connectT(0, pma3); // LpMod -> pma3::Multiply
		
		this->getParameterT(10).connectT(0, branch3); // LpSrc -> branch3::Index
		
		this->getParameterT(11).connectT(0, pma2); // delMod -> pma2::Multiply
		
		this->getParameterT(12).connectT(0, branch2); // delSrc -> branch2::Index
		
		// Modulation Connections ------------------------------------------------------------------
		
		global_cable.getWrappedObject().getParameter().connectT(0, add);    // global_cable -> add::Value
		global_cable.getWrappedObject().getParameter().connectT(1, add4);   // global_cable -> add4::Value
		global_cable.getWrappedObject().getParameter().connectT(2, add12);  // global_cable -> add12::Value
		global_cable.getWrappedObject().getParameter().connectT(3, add8);   // global_cable -> add8::Value
		global_cable1.getWrappedObject().getParameter().connectT(0, add3);  // global_cable1 -> add3::Value
		global_cable1.getWrappedObject().getParameter().connectT(1, add5);  // global_cable1 -> add5::Value
		global_cable1.getWrappedObject().getParameter().connectT(2, add13); // global_cable1 -> add13::Value
		global_cable1.getWrappedObject().getParameter().connectT(3, add9);  // global_cable1 -> add9::Value
		global_cable3.getWrappedObject().getParameter().connectT(0, add2);  // global_cable3 -> add2::Value
		global_cable3.getWrappedObject().getParameter().connectT(1, add6);  // global_cable3 -> add6::Value
		global_cable3.getWrappedObject().getParameter().connectT(2, add14); // global_cable3 -> add14::Value
		global_cable3.getWrappedObject().getParameter().connectT(3, add10); // global_cable3 -> add10::Value
		global_cable2.getWrappedObject().getParameter().connectT(0, add11); // global_cable2 -> add11::Value
		global_cable2.getWrappedObject().getParameter().connectT(1, add15); // global_cable2 -> add15::Value
		global_cable2.getWrappedObject().getParameter().connectT(2, add7);  // global_cable2 -> add7::Value
		global_cable2.getWrappedObject().getParameter().connectT(3, add1);  // global_cable2 -> add1::Value
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);                              // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1);                             // xfader -> gain1::Gain
		pma.getWrappedObject().getParameter().connectT(0, xfader);                // pma -> xfader::Value
		peak.getParameter().connectT(0, pma);                                     // peak -> pma::Value
		clone_cable5.getWrappedObject().getParameter().connectT(0, FeedJ);        // clone_cable5 -> FeedJ::pan
		pma1.getWrappedObject().getParameter().connectT(0, clone_cable5);         // pma1 -> clone_cable5::Value
		peak1.getParameter().connectT(0, pma1);                                   // peak1 -> pma1::Value
		clone_cable7.getWrappedObject().getParameter().connectT(0, FeedJ);        // clone_cable7 -> FeedJ::lp
		pma3.getWrappedObject().getParameter().connectT(0, clone_cable7);         // pma3 -> clone_cable7::Value
		peak3.getParameter().connectT(0, pma3);                                   // peak3 -> pma3::Value
		clone_cable4.getWrappedObject().getParameter().connectT(0, FeedJ);        // clone_cable4 -> FeedJ::del
		smoothed_parameter32.getParameter().connectT(0, clone_cable4);            // smoothed_parameter32 -> clone_cable4::Value
		pma2.getWrappedObject().getParameter().connectT(0, smoothed_parameter32); // pma2 -> smoothed_parameter32::Value
		peak2.getParameter().connectT(0, pma2);                                   // peak2 -> pma2::Value
		clone_cable6.getWrappedObject().getParameter().connectT(0, FeedJ);        // clone_cable6 -> FeedJ::fb
		
		// Default Values --------------------------------------------------------------------------
		
		global_cable.setParameterT(0, 1.); // routing::global_cable::Value
		
		global_cable1.setParameterT(0, 1.); // routing::global_cable::Value
		
		global_cable3.setParameterT(0, 1.); // routing::global_cable::Value
		
		global_cable2.setParameterT(0, 1.); // routing::global_cable::Value
		
		clear4.setParameterT(0, 0.); // math::clear::Value
		
		; // branch::Index is automated
		
		; // add::Value is automated
		
		; // add3::Value is automated
		
		; // add2::Value is automated
		
		; // add1::Value is automated
		
		clear5.setParameterT(0, 0.); // math::clear::Value
		
		; // pma::Value is automated
		; // pma::Multiply is automated
		; // pma::Add is automated
		
		; // branch1::Index is automated
		
		; // add4::Value is automated
		
		; // add5::Value is automated
		
		; // add6::Value is automated
		
		; // add7::Value is automated
		
		clear6.setParameterT(0, 0.); // math::clear::Value
		
		; // pma1::Value is automated
		; // pma1::Multiply is automated
		; // pma1::Add is automated
		
		; // branch3::Index is automated
		
		; // add12::Value is automated
		
		; // add13::Value is automated
		
		; // add14::Value is automated
		
		; // add15::Value is automated
		
		clear8.setParameterT(0, 0.); // math::clear::Value
		
		; // pma3::Value is automated
		; // pma3::Multiply is automated
		; // pma3::Add is automated
		
		; // branch2::Index is automated
		
		; // add8::Value is automated
		
		; // add9::Value is automated
		
		; // add10::Value is automated
		
		; // add11::Value is automated
		
		clear7.setParameterT(0, 0.); // math::clear::Value
		
		; // pma2::Value is automated
		; // pma2::Multiply is automated
		; // pma2::Add is automated
		
		clear1.setParameterT(0, 0.); // math::clear::Value
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		clear.setParameterT(0, 0.); // math::clear::Value
		
		;                                  // clone_cable5::NumClones is deactivated
		;                                  // clone_cable5::Value is automated
		clone_cable5.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		;                                  // clone_cable6::NumClones is deactivated
		;                                  // clone_cable6::Value is automated
		clone_cable6.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		clear2.setParameterT(0, 0.); // math::clear::Value
		
		;                                  // clone_cable7::NumClones is deactivated
		;                                  // clone_cable7::Value is automated
		clone_cable7.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		clear3.setParameterT(0, 0.); // math::clear::Value
		
		;                                             // smoothed_parameter32::Value is automated
		smoothed_parameter32.setParameterT(1, 482.4); // control::smoothed_parameter::SmoothingTime
		smoothed_parameter32.setParameterT(2, 1.);    // control::smoothed_parameter::Enabled
		
		;                                  // clone_cable4::NumClones is deactivated
		;                                  // clone_cable4::Value is automated
		clone_cable4.setParameterT(2, 0.); // control::clone_cable::Gamma
		
		clone.setParameterT(0, 32.); // container::clone::NumClones
		clone.setParameterT(1, 2.);  // container::clone::SplitSignal
		
		; // FeedJ::del is automated
		; // FeedJ::fb is automated
		; // FeedJ::lp is automated
		; // FeedJ::pan is automated
		
		gain221.setParameterT(0, -23.); // core::gain::Gain
		gain221.setParameterT(1, 20.);  // core::gain::Smoothing
		gain221.setParameterT(2, 0.);   // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 1.);
		this->setParameterT(1, 0.41);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 1.);
		this->setParameterT(4, 0.53);
		this->setParameterT(5, 0.);
		this->setParameterT(6, 1.);
		this->setParameterT(7, 0.);
		this->setParameterT(8, 1.);
		this->setParameterT(9, 0.);
		this->setParameterT(10, 3.);
		this->setParameterT(11, -0.01);
		this->setParameterT(12, 3.);
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
		
		this->getT(0).getT(0).getT(0).getT(0).connectToRuntimeTarget(addConnection, c); // spacer1_impl::global_cable_t<NV>
		this->getT(0).getT(0).getT(0).getT(1).connectToRuntimeTarget(addConnection, c); // spacer1_impl::global_cable1_t<NV>
		this->getT(0).getT(0).getT(0).getT(2).connectToRuntimeTarget(addConnection, c); // spacer1_impl::global_cable3_t<NV>
		this->getT(0).getT(0).getT(0).getT(3).connectToRuntimeTarget(addConnection, c); // spacer1_impl::global_cable2_t<NV>
	}
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(1).setExternalData(b, index); // spacer1_impl::peak_t<NV>
		this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(1).setExternalData(b, index); // spacer1_impl::peak1_t<NV>
		this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(1).setExternalData(b, index); // spacer1_impl::peak3_t<NV>
		this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(1).setExternalData(b, index); // spacer1_impl::peak2_t<NV>
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
using spacer1 = wrap::node<spacer1_impl::instance<NV>>;
}


