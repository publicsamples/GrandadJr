#pragma once

#include "gransect.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace PolyGrain_impl
{
// ==============================| Node & Parameter type declarations |==============================

using global_mod_t_index = runtime_target::indexers::fix_hash<1>;
using global_mod_t_config = modulation::config::dynamic;

template <int NV>
using global_mod_t = wrap::mod<parameter::plain<project::gransect<NV>, 1>, 
                               wrap::no_data<core::global_mod<NV, global_mod_t_index, global_mod_t_config>>>;

template <int NV>
using chain5_t = container::chain<parameter::empty, 
                                  wrap::fix<1, global_mod_t<NV>>>;
using global_mod1_t_index = global_mod_t_index;
using global_mod1_t_config = global_mod_t_config;

DECLARE_PARAMETER_RANGE_SKEW(xfader3_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using xfader3_c0 = parameter::from0To1<core::gain<NV>, 
                                       0, 
                                       xfader3_c0Range>;

template <int NV> using xfader3_c1 = xfader3_c0<NV>;

template <int NV>
using xfader3_multimod = parameter::list<xfader3_c0<NV>, xfader3_c1<NV>>;

template <int NV>
using xfader3_t = control::xfader<xfader3_multimod<NV>, faders::rms>;
template <int NV>
using global_mod1_t = wrap::mod<parameter::plain<xfader3_t<NV>, 0>, 
                                wrap::no_data<core::global_mod<NV, global_mod1_t_index, global_mod1_t_config>>>;

template <int NV>
using chain7_t = container::chain<parameter::empty, 
                                  wrap::fix<1, global_mod1_t<NV>>>;
using global_mod2_t_index = global_mod_t_index;
using global_mod2_t_config = global_mod_t_config;

template <int NV>
using tempo_sync_t = wrap::mod<parameter::plain<project::gransect<NV>, 4>, 
                               control::tempo_sync<NV>>;
DECLARE_PARAMETER_RANGE_STEP(global_mod2_modRange, 
                             0., 
                             18., 
                             1.);

template <int NV>
using global_mod2_mod = parameter::from0To1<tempo_sync_t<NV>, 
                                            0, 
                                            global_mod2_modRange>;

template <int NV>
using global_mod2_t = wrap::mod<global_mod2_mod<NV>, 
                                wrap::no_data<core::global_mod<NV, global_mod2_t_index, global_mod2_t_config>>>;

template <int NV>
using chain8_t = container::chain<parameter::empty, 
                                  wrap::fix<1, global_mod2_t<NV>>>;
using global_mod3_t_index = global_mod_t_index;
using global_mod3_t_config = global_mod_t_config;

DECLARE_PARAMETER_RANGE_STEP(global_mod3_modRange, 
                             0., 
                             1000., 
                             0.1);

template <int NV>
using global_mod3_mod = parameter::from0To1<tempo_sync_t<NV>, 
                                            3, 
                                            global_mod3_modRange>;

template <int NV>
using global_mod3_t = wrap::mod<global_mod3_mod<NV>, 
                                wrap::no_data<core::global_mod<NV, global_mod3_t_index, global_mod3_t_config>>>;

template <int NV>
using chain14_t = container::chain<parameter::empty, 
                                   wrap::fix<1, global_mod3_t<NV>>>;
using global_mod4_t_index = global_mod_t_index;
using global_mod4_t_config = global_mod_t_config;

DECLARE_PARAMETER_RANGE_STEP(global_mod4_modRange, 
                             -24., 
                             24., 
                             0.1);

template <int NV>
using global_mod4_mod = parameter::from0To1<project::shift<NV>, 
                                            0, 
                                            global_mod4_modRange>;

template <int NV>
using global_mod4_t = wrap::mod<global_mod4_mod<NV>, 
                                wrap::no_data<core::global_mod<NV, global_mod4_t_index, global_mod4_t_config>>>;

template <int NV>
using chain15_t = container::chain<parameter::empty, 
                                   wrap::fix<1, global_mod4_t<NV>>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, chain5_t<NV>>, 
                                 chain7_t<NV>, 
                                 chain8_t<NV>, 
                                 chain14_t<NV>, 
                                 chain15_t<NV>>;

template <int NV>
using modchain2_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, split_t<NV>>>;

template <int NV>
using modchain2_t = wrap::control_rate<modchain2_t_<NV>>;

template <int NV>
using chain10_t = container::chain<parameter::empty, 
                                   wrap::fix<2, core::gain<NV>>>;

template <int NV>
using modchain1_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, tempo_sync_t<NV>>>;

template <int NV>
using modchain1_t = wrap::control_rate<modchain1_t_<NV>>;
template <int NV>
using stereo_cable = cable::block<NV, 2>;
template <int NV>
using oversample_t_ = container::chain<parameter::empty, 
                                       wrap::fix<2, routing::receive<NV, stereo_cable<NV>>>, 
                                       project::gransect<NV>, 
                                       project::shift<NV>, 
                                       filters::one_pole<NV>, 
                                       routing::send<NV, stereo_cable<NV>>>;

template <int NV>
using oversample_t = wrap::oversample<0, oversample_t_<NV>>;

template <int NV>
using chain2_t = container::chain<parameter::empty, 
                                  wrap::fix<2, oversample_t<NV>>>;
using oscilloscope_t = wrap::data<analyse::oscilloscope, 
                                  data::external::displaybuffer<0>>;

template <int NV>
using chain11_t = container::chain<parameter::empty, 
                                   wrap::fix<2, modchain1_t<NV>>, 
                                   chain2_t<NV>, 
                                   oscilloscope_t, 
                                   core::gain<NV>>;

template <int NV>
using split3_t = container::split<parameter::empty, 
                                  wrap::fix<2, chain10_t<NV>>, 
                                  chain11_t<NV>>;

template <int NV>
using chain9_t = container::chain<parameter::empty, 
                                  wrap::fix<2, xfader3_t<NV>>, 
                                  split3_t<NV>>;

template <int NV>
using chain6_t = container::chain<parameter::empty, 
                                  wrap::fix<2, chain9_t<NV>>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, chain6_t<NV>>>;

namespace PolyGrain_t_parameters
{
// Parameter list for PolyGrain_impl::PolyGrain_t --------------------------------------------------

DECLARE_PARAMETER_RANGE_SKEW(lpRange, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using lp = parameter::from0To1<filters::one_pole<NV>, 
                               0, 
                               lpRange>;

DECLARE_PARAMETER_RANGE_STEP(GrainSizeTempo_InputRange, 
                             0., 
                             18., 
                             1.);

template <int NV>
using GrainSizeTempo = parameter::chain<GrainSizeTempo_InputRange, 
                                        parameter::plain<PolyGrain_impl::global_mod2_t<NV>, 1>>;

DECLARE_PARAMETER_RANGE_STEP(GranUnsync_InputRange, 
                             0., 
                             2000., 
                             0.1);

template <int NV>
using GranUnsync = parameter::chain<GranUnsync_InputRange, 
                                    parameter::plain<PolyGrain_impl::global_mod3_t<NV>, 1>>;

DECLARE_PARAMETER_RANGE(FBRange, 
                        0., 
                        0.8);

template <int NV>
using FB = parameter::from0To1<routing::receive<NV, stereo_cable<NV>>, 
                               0, 
                               FBRange>;

DECLARE_PARAMETER_RANGE_STEP(PosSrc_InputRange, 
                             1., 
                             17., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(PosSrc_0Range, 
                             0., 
                             16., 
                             1.);

template <int NV>
using PosSrc_0 = parameter::from0To1<PolyGrain_impl::global_mod_t<NV>, 
                                     0, 
                                     PosSrc_0Range>;

template <int NV>
using PosSrc = parameter::chain<PosSrc_InputRange, PosSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(MixSrx_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using MixSrx_0 = parameter::from0To1<PolyGrain_impl::global_mod1_t<NV>, 
                                     0, 
                                     PosSrc_0Range>;

template <int NV>
using MixSrx = parameter::chain<MixSrx_InputRange, MixSrx_0<NV>>;

template <int NV>
using GsizeMod = parameter::chain<ranges::Identity, 
                                  parameter::plain<PolyGrain_impl::global_mod2_t<NV>, 4>, 
                                  parameter::plain<PolyGrain_impl::global_mod3_t<NV>, 4>>;

DECLARE_PARAMETER_RANGE_STEP(GsizeSrc_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using GsizeSrc_0 = parameter::from0To1<PolyGrain_impl::global_mod2_t<NV>, 
                                       0, 
                                       PosSrc_0Range>;

template <int NV>
using GsizeSrc_1 = parameter::from0To1<PolyGrain_impl::global_mod3_t<NV>, 
                                       0, 
                                       PosSrc_0Range>;

template <int NV>
using GsizeSrc = parameter::chain<GsizeSrc_InputRange, 
                                  GsizeSrc_0<NV>, 
                                  GsizeSrc_1<NV>>;

DECLARE_PARAMETER_RANGE_STEP(Pitch_InputRange, 
                             -24., 
                             24., 
                             1.);

template <int NV>
using Pitch = parameter::chain<Pitch_InputRange, 
                               parameter::plain<PolyGrain_impl::global_mod4_t<NV>, 1>>;

DECLARE_PARAMETER_RANGE_STEP(PitchSrc_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using PitchSrc_0 = parameter::from0To1<PolyGrain_impl::global_mod4_t<NV>, 
                                       0, 
                                       PosSrc_0Range>;

template <int NV>
using PitchSrc = parameter::chain<PitchSrc_InputRange, PitchSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(win_InputRange, 
                             50., 
                             10000., 
                             1.);
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
using win = parameter::chain<win_InputRange, 
                             win_0<NV>, 
                             win_1<NV>>;

template <int NV>
using IntLength = parameter::plain<project::gransect<NV>, 0>;
template <int NV>
using Position = parameter::plain<PolyGrain_impl::global_mod_t<NV>, 
                                  1>;
template <int NV>
using Freeze = parameter::plain<project::gransect<NV>, 2>;
template <int NV>
using PosMod = parameter::plain<PolyGrain_impl::global_mod_t<NV>, 
                                4>;
template <int NV>
using GranMix = parameter::plain<PolyGrain_impl::global_mod1_t<NV>, 
                                 1>;
template <int NV>
using GrainDiv = parameter::plain<PolyGrain_impl::tempo_sync_t<NV>, 
                                  1>;
template <int NV>
using GrainSync = parameter::plain<PolyGrain_impl::tempo_sync_t<NV>, 
                                   2>;
template <int NV>
using g1vol = parameter::plain<project::gransect<NV>, 3>;
template <int NV>
using os = parameter::plain<PolyGrain_impl::oversample_t<NV>, 
                            0>;
template <int NV>
using MixMod = parameter::plain<PolyGrain_impl::global_mod1_t<NV>, 
                                4>;
template <int NV>
using PitchMod = parameter::plain<PolyGrain_impl::global_mod4_t<NV>, 
                                  4>;
template <int NV>
using PolyGrain_t_plist = parameter::list<IntLength<NV>, 
                                          Position<NV>, 
                                          Freeze<NV>, 
                                          lp<NV>, 
                                          PosMod<NV>, 
                                          GranMix<NV>, 
                                          GrainSizeTempo<NV>, 
                                          GrainDiv<NV>, 
                                          GrainSync<NV>, 
                                          GranUnsync<NV>, 
                                          g1vol<NV>, 
                                          FB<NV>, 
                                          os<NV>, 
                                          PosSrc<NV>, 
                                          MixMod<NV>, 
                                          MixSrx<NV>, 
                                          GsizeMod<NV>, 
                                          GsizeSrc<NV>, 
                                          Pitch<NV>, 
                                          PitchMod<NV>, 
                                          PitchSrc<NV>, 
                                          win<NV>>;
}

template <int NV>
using PolyGrain_t_ = container::chain<PolyGrain_t_parameters::PolyGrain_t_plist<NV>, 
                                      wrap::fix<2, modchain2_t<NV>>, 
                                      chain_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public PolyGrain_impl::PolyGrain_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 1;
		
		SNEX_METADATA_ID(PolyGrain);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(382)
		{
			0x005C, 0x0000, 0x0000, 0x6E49, 0x4C74, 0x6E65, 0x7467, 0x0068, 
            0x0000, 0x8000, 0x0040, 0x8000, 0x0042, 0x8000, 0x0040, 0x8000, 
            0x003F, 0x8000, 0x5C3F, 0x0100, 0x0000, 0x5000, 0x736F, 0x7469, 
            0x6F69, 0x006E, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x0000, 0x5C00, 0x0200, 0x0000, 0x4600, 
            0x6572, 0x7A65, 0x0065, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x5C3F, 0x0300, 0x0000, 
            0x6C00, 0x0070, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x0000, 0x5C00, 0x0400, 0x0000, 0x5000, 
            0x736F, 0x6F4D, 0x0064, 0x0000, 0x8000, 0x00BF, 0x8000, 0x003F, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x5C00, 0x0500, 0x0000, 
            0x4700, 0x6172, 0x4D6E, 0x7869, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x005C, 
            0x0006, 0x0000, 0x7247, 0x6961, 0x536E, 0x7A69, 0x5465, 0x6D65, 
            0x6F70, 0x0000, 0x0000, 0x0000, 0x0000, 0x4190, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x005C, 0x0007, 0x0000, 0x7247, 
            0x6961, 0x446E, 0x7669, 0x0000, 0x0000, 0x3F80, 0x0000, 0x4180, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x005C, 0x0008, 
            0x0000, 0x7247, 0x6961, 0x536E, 0x6E79, 0x0063, 0x0000, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x5C3F, 0x0900, 0x0000, 0x4700, 0x6172, 0x556E, 0x736E, 0x6E79, 
            0x0063, 0x0000, 0x0000, 0x0000, 0xFA00, 0x0044, 0x8000, 0x003F, 
            0x8000, 0xCD3F, 0xCCCC, 0x5C3D, 0x0A00, 0x0000, 0x6700, 0x7631, 
            0x6C6F, 0x0000, 0x0000, 0x0000, 0x0000, 0x3F80, 0x851F, 0x3F6B, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x005C, 0x000B, 0x0000, 0x4246, 
            0x0000, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x005C, 0x000C, 0x0000, 0x736F, 0x0000, 
            0x0000, 0x0000, 0x0000, 0x4080, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x005C, 0x000D, 0x0000, 0x6F50, 0x5373, 0x6372, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x4188, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x005C, 0x000E, 0x0000, 0x694D, 0x4D78, 
            0x646F, 0x0000, 0x0000, 0xBF80, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x005C, 0x000F, 0x0000, 0x694D, 
            0x5378, 0x7872, 0x0000, 0x0000, 0x3F80, 0x0000, 0x4188, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x005C, 0x0010, 0x0000, 
            0x7347, 0x7A69, 0x4D65, 0x646F, 0x0000, 0x0000, 0xBF80, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x005C, 
            0x0011, 0x0000, 0x7347, 0x7A69, 0x5365, 0x6372, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x4188, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x005C, 0x0012, 0x0000, 0x6950, 0x6374, 0x0068, 0x0000, 
            0xC000, 0x00C1, 0xC000, 0x0041, 0xC000, 0x00C0, 0x8000, 0x003F, 
            0x8000, 0x5C3F, 0x1300, 0x0000, 0x5000, 0x7469, 0x6863, 0x6F4D, 
            0x0064, 0x0000, 0x8000, 0x00BF, 0x8000, 0x003F, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x5C00, 0x1400, 0x0000, 0x5000, 0x7469, 
            0x6863, 0x7253, 0x0063, 0x0000, 0x8000, 0x003F, 0x8800, 0x0041, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x5C3F, 0x1500, 0x0000, 
            0x7700, 0x6E69, 0x0000, 0x0000, 0x4248, 0x4000, 0x461C, 0x0000, 
            0x4248, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000
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
		
		auto& modchain2 = this->getT(0);                                                  // PolyGrain_impl::modchain2_t<NV>
		auto& split = this->getT(0).getT(0);                                              // PolyGrain_impl::split_t<NV>
		auto& chain5 = this->getT(0).getT(0).getT(0);                                     // PolyGrain_impl::chain5_t<NV>
		auto& global_mod = this->getT(0).getT(0).getT(0).getT(0);                         // PolyGrain_impl::global_mod_t<NV>
		auto& chain7 = this->getT(0).getT(0).getT(1);                                     // PolyGrain_impl::chain7_t<NV>
		auto& global_mod1 = this->getT(0).getT(0).getT(1).getT(0);                        // PolyGrain_impl::global_mod1_t<NV>
		auto& chain8 = this->getT(0).getT(0).getT(2);                                     // PolyGrain_impl::chain8_t<NV>
		auto& global_mod2 = this->getT(0).getT(0).getT(2).getT(0);                        // PolyGrain_impl::global_mod2_t<NV>
		auto& chain14 = this->getT(0).getT(0).getT(3);                                    // PolyGrain_impl::chain14_t<NV>
		auto& global_mod3 = this->getT(0).getT(0).getT(3).getT(0);                        // PolyGrain_impl::global_mod3_t<NV>
		auto& chain15 = this->getT(0).getT(0).getT(4);                                    // PolyGrain_impl::chain15_t<NV>
		auto& global_mod4 = this->getT(0).getT(0).getT(4).getT(0);                        // PolyGrain_impl::global_mod4_t<NV>
		auto& chain = this->getT(1);                                                      // PolyGrain_impl::chain_t<NV>
		auto& chain6 = this->getT(1).getT(0);                                             // PolyGrain_impl::chain6_t<NV>
		auto& chain9 = this->getT(1).getT(0).getT(0);                                     // PolyGrain_impl::chain9_t<NV>
		auto& xfader3 = this->getT(1).getT(0).getT(0).getT(0);                            // PolyGrain_impl::xfader3_t<NV>
		auto& split3 = this->getT(1).getT(0).getT(0).getT(1);                             // PolyGrain_impl::split3_t<NV>
		auto& chain10 = this->getT(1).getT(0).getT(0).getT(1).getT(0);                    // PolyGrain_impl::chain10_t<NV>
		auto& gain6 = this->getT(1).getT(0).getT(0).getT(1).getT(0).getT(0);              // core::gain<NV>
		auto& chain11 = this->getT(1).getT(0).getT(0).getT(1).getT(1);                    // PolyGrain_impl::chain11_t<NV>
		auto& modchain1 = this->getT(1).getT(0).getT(0).getT(1).getT(1).getT(0);          // PolyGrain_impl::modchain1_t<NV>
		auto& tempo_sync = this->getT(1).getT(0).getT(0).getT(1).getT(1).getT(0).getT(0); // PolyGrain_impl::tempo_sync_t<NV>
		auto& chain2 = this->getT(1).getT(0).getT(0).getT(1).getT(1).getT(1);             // PolyGrain_impl::chain2_t<NV>
		auto& oversample = this->getT(1).getT(0).getT(0).getT(1).getT(1).getT(1).getT(0); // PolyGrain_impl::oversample_t<NV>
		auto& receive1 = this->getT(1).getT(0).getT(0).getT(1).                           // routing::receive<NV, stereo_cable<NV>>
                         getT(1).getT(1).getT(0).getT(0);
		auto& gransect = this->getT(1).getT(0).getT(0).getT(1).                     // project::gransect<NV>
                         getT(1).getT(1).getT(0).getT(1);
		auto& faust = this->getT(1).getT(0).getT(0).getT(1).                        // project::shift<NV>
                      getT(1).getT(1).getT(0).getT(2);
		auto& one_pole = this->getT(1).getT(0).getT(0).getT(1).                     // filters::one_pole<NV>
                         getT(1).getT(1).getT(0).getT(3);
		auto& send1 = this->getT(1).getT(0).getT(0).getT(1).                        // routing::send<NV, stereo_cable<NV>>
                      getT(1).getT(1).getT(0).getT(4);
		auto& oscilloscope = this->getT(1).getT(0).getT(0).getT(1).getT(1).getT(2); // PolyGrain_impl::oscilloscope_t
		auto& gain7 = this->getT(1).getT(0).getT(0).getT(1).getT(1).getT(3);        // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, gransect); // IntLength -> gransect::Int
		
		this->getParameterT(1).connectT(0, global_mod); // Position -> global_mod::Value
		
		this->getParameterT(2).connectT(0, gransect); // Freeze -> gransect::Freeze
		
		this->getParameterT(3).connectT(0, one_pole); // lp -> one_pole::Frequency
		
		this->getParameterT(4).connectT(0, global_mod); // PosMod -> global_mod::Intensity
		
		this->getParameterT(5).connectT(0, global_mod1); // GranMix -> global_mod1::Value
		
		this->getParameterT(6).connectT(0, global_mod2); // GrainSizeTempo -> global_mod2::Value
		
		this->getParameterT(7).connectT(0, tempo_sync); // GrainDiv -> tempo_sync::Multiplier
		
		this->getParameterT(8).connectT(0, tempo_sync); // GrainSync -> tempo_sync::Enabled
		
		this->getParameterT(9).connectT(0, global_mod3); // GranUnsync -> global_mod3::Value
		
		this->getParameterT(10).connectT(0, gransect); // g1vol -> gransect::Vol
		
		this->getParameterT(11).connectT(0, receive1); // FB -> receive1::Feedback
		
		this->getParameterT(12).connectT(0, oversample); // os -> oversample::Oversampling
		
		this->getParameterT(13).connectT(0, global_mod); // PosSrc -> global_mod::Index
		
		this->getParameterT(14).connectT(0, global_mod1); // MixMod -> global_mod1::Intensity
		
		this->getParameterT(15).connectT(0, global_mod1); // MixSrx -> global_mod1::Index
		
		auto& GsizeMod_p = this->getParameterT(16);
		GsizeMod_p.connectT(0, global_mod2); // GsizeMod -> global_mod2::Intensity
		GsizeMod_p.connectT(1, global_mod3); // GsizeMod -> global_mod3::Intensity
		
		auto& GsizeSrc_p = this->getParameterT(17);
		GsizeSrc_p.connectT(0, global_mod2); // GsizeSrc -> global_mod2::Index
		GsizeSrc_p.connectT(1, global_mod3); // GsizeSrc -> global_mod3::Index
		
		this->getParameterT(18).connectT(0, global_mod4); // Pitch -> global_mod4::Value
		
		this->getParameterT(19).connectT(0, global_mod4); // PitchMod -> global_mod4::Intensity
		
		this->getParameterT(20).connectT(0, global_mod4); // PitchSrc -> global_mod4::Index
		
		auto& win_p = this->getParameterT(21);
		win_p.connectT(0, faust); // win -> faust::windowsamples
		win_p.connectT(1, faust); // win -> faust::xfadesamples
		
		// Modulation Connections ------------------------------------------------------------------
		
		global_mod.getParameter().connectT(0, gransect); // global_mod -> gransect::Pos
		auto& xfader3_p = xfader3.getWrappedObject().getParameter();
		xfader3_p.getParameterT(0).connectT(0, gain6);      // xfader3 -> gain6::Gain
		xfader3_p.getParameterT(1).connectT(0, gain7);      // xfader3 -> gain7::Gain
		global_mod1.getParameter().connectT(0, xfader3);    // global_mod1 -> xfader3::Value
		tempo_sync.getParameter().connectT(0, gransect);    // tempo_sync -> gransect::g
		global_mod2.getParameter().connectT(0, tempo_sync); // global_mod2 -> tempo_sync::Tempo
		global_mod3.getParameter().connectT(0, tempo_sync); // global_mod3 -> tempo_sync::UnsyncedTime
		global_mod4.getParameter().connectT(0, faust);      // global_mod4 -> faust::shiftsemitones
		
		// Send Connections ------------------------------------------------------------------------
		
		send1.connect(receive1);
		
		// Default Values --------------------------------------------------------------------------
		
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
		
		;                                 // global_mod3::Index is automated
		;                                 // global_mod3::Value is automated
		global_mod3.setParameterT(2, 0.); // core::global_mod::ProcessSignal
		global_mod3.setParameterT(3, 1.); // core::global_mod::Mode
		;                                 // global_mod3::Intensity is automated
		
		;                                 // global_mod4::Index is automated
		;                                 // global_mod4::Value is automated
		global_mod4.setParameterT(2, 0.); // core::global_mod::ProcessSignal
		global_mod4.setParameterT(3, 1.); // core::global_mod::Mode
		;                                 // global_mod4::Intensity is automated
		
		; // xfader3::Value is automated
		
		;                              // gain6::Gain is automated
		gain6.setParameterT(1, 20.);   // core::gain::Smoothing
		gain6.setParameterT(2, -100.); // core::gain::ResetValue
		
		; // tempo_sync::Tempo is automated
		; // tempo_sync::Multiplier is automated
		; // tempo_sync::Enabled is automated
		; // tempo_sync::UnsyncedTime is automated
		
		;                                // oversample::Oversampling is automated
		oversample.setParameterT(1, 0.); // container::chain::FilterType
		
		; // receive1::Feedback is automated
		
		; // gransect::Int is automated
		; // gransect::Pos is automated
		; // gransect::Freeze is automated
		; // gransect::Vol is automated
		; // gransect::g is automated
		
		; // faust::shiftsemitones is automated
		; // faust::windowsamples is automated
		; // faust::xfadesamples is automated
		
		;                                // one_pole::Frequency is automated
		one_pole.setParameterT(1, 1.);   // filters::one_pole::Q
		one_pole.setParameterT(2, 0.);   // filters::one_pole::Gain
		one_pole.setParameterT(3, 0.01); // filters::one_pole::Smoothing
		one_pole.setParameterT(4, 0.);   // filters::one_pole::Mode
		one_pole.setParameterT(5, 1.);   // filters::one_pole::Enabled
		
		;                              // gain7::Gain is automated
		gain7.setParameterT(1, 20.);   // core::gain::Smoothing
		gain7.setParameterT(2, -100.); // core::gain::ResetValue
		
		this->setParameterT(0, 4.);
		this->setParameterT(1, 0.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 1.);
		this->setParameterT(4, 1.);
		this->setParameterT(5, 1.);
		this->setParameterT(6, 0.);
		this->setParameterT(7, 1.);
		this->setParameterT(8, 1.);
		this->setParameterT(9, 1);
		this->setParameterT(10, 0.92);
		this->setParameterT(11, 1.);
		this->setParameterT(12, 1.);
		this->setParameterT(13, 1.);
		this->setParameterT(14, 1.);
		this->setParameterT(15, 1.);
		this->setParameterT(16, 1.);
		this->setParameterT(17, 1.);
		this->setParameterT(18, -6.);
		this->setParameterT(19, 0.);
		this->setParameterT(20, 1.);
		this->setParameterT(21, 50.);
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
		
		this->getT(0).getT(0).getT(0).getT(0).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_mod_t<NV>
		this->getT(0).getT(0).getT(1).getT(0).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_mod1_t<NV>
		this->getT(0).getT(0).getT(2).getT(0).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_mod2_t<NV>
		this->getT(0).getT(0).getT(3).getT(0).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_mod3_t<NV>
		this->getT(0).getT(0).getT(4).getT(0).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_mod4_t<NV>
	}
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(0).getT(0).getT(0).setExternalData(b, index);                 // PolyGrain_impl::global_mod_t<NV>
		this->getT(0).getT(0).getT(1).getT(0).setExternalData(b, index);                 // PolyGrain_impl::global_mod1_t<NV>
		this->getT(0).getT(0).getT(2).getT(0).setExternalData(b, index);                 // PolyGrain_impl::global_mod2_t<NV>
		this->getT(0).getT(0).getT(3).getT(0).setExternalData(b, index);                 // PolyGrain_impl::global_mod3_t<NV>
		this->getT(0).getT(0).getT(4).getT(0).setExternalData(b, index);                 // PolyGrain_impl::global_mod4_t<NV>
		this->getT(1).getT(0).getT(0).getT(1).getT(1).getT(2).setExternalData(b, index); // PolyGrain_impl::oscilloscope_t
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
using PolyGrain = wrap::node<PolyGrain_impl::instance<NV>>;
}


