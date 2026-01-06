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

namespace PolyGrain_impl
{
// ==============================| Node & Parameter type declarations |==============================

using global_cable_t_index = runtime_target::indexers::fix_hash<3357039>;

template <int NV>
using global_cable_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<math::add<NV>, 0>, 
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

template <int NV>
using pma_t = control::pma<NV, 
                           parameter::plain<project::gr1<NV>, 2>>;
template <int NV>
using peak_t = wrap::mod<parameter::plain<pma_t<NV>, 0>, 
                         wrap::no_data<core::peak>>;

template <int NV>
using chain12_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch_t<NV>>, 
                                   peak_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<1, chain12_t<NV>>, 
                                  pma_t<NV>>;
template <int NV> using branch1_t = branch_t<NV>;

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
using pma1_t = control::pma<NV, 
                            parameter::plain<xfader3_t<NV>, 0>>;
template <int NV>
using peak1_t = wrap::mod<parameter::plain<pma1_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain13_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch1_t<NV>>, 
                                   peak1_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain3_t = container::chain<parameter::empty, 
                                  wrap::fix<1, chain13_t<NV>>, 
                                  pma1_t<NV>>;
template <int NV> using branch3_t = branch_t<NV>;

template <int NV>
using tempo_sync_t = wrap::mod<parameter::plain<project::gr1<NV>, 1>, 
                               control::tempo_sync<NV>>;
DECLARE_PARAMETER_RANGE_STEP(pma3_modRange, 
                             0., 
                             6400., 
                             0.1);

template <int NV>
using pma3_mod = parameter::from0To1<tempo_sync_t<NV>, 
                                     3, 
                                     pma3_modRange>;

template <int NV>
using pma3_t = control::pma<NV, pma3_mod<NV>>;
template <int NV>
using peak3_t = wrap::mod<parameter::plain<pma3_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain18_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch3_t<NV>>, 
                                   peak3_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain17_t = container::chain<parameter::empty, 
                                   wrap::fix<1, chain18_t<NV>>, 
                                   pma3_t<NV>>;
template <int NV> using branch2_t = branch_t<NV>;

DECLARE_PARAMETER_RANGE_STEP(pma2_modRange, 
                             0., 
                             18., 
                             1.);

template <int NV>
using pma2_mod = parameter::from0To1<tempo_sync_t<NV>, 
                                     0, 
                                     pma2_modRange>;

template <int NV>
using pma2_t = control::pma<NV, pma2_mod<NV>>;
template <int NV>
using peak2_t = wrap::mod<parameter::plain<pma2_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain16_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch2_t<NV>>, 
                                   peak2_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain4_t = container::chain<parameter::empty, 
                                  wrap::fix<1, chain16_t<NV>>, 
                                  pma2_t<NV>>;
template <int NV> using branch4_t = branch_t<NV>;

template <int NV>
using peak4_t = wrap::mod<parameter::plain<control::pma<NV, parameter::empty>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain20_t = container::chain<parameter::empty, 
                                   wrap::fix<1, branch4_t<NV>>, 
                                   peak4_t<NV>, 
                                   math::clear<NV>>;

template <int NV>
using chain19_t = container::chain<parameter::empty, 
                                   wrap::fix<1, chain20_t<NV>>, 
                                   control::pma<NV, parameter::empty>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, chain1_t<NV>>, 
                                  chain3_t<NV>, 
                                  chain17_t<NV>, 
                                  chain4_t<NV>, 
                                  chain19_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split2_t<NV>>, 
                                     math::clear<NV>, 
                                     split1_t<NV>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV>
using chain10_t = container::chain<parameter::empty, 
                                   wrap::fix<2, core::gain<NV>>>;

template <int NV>
using modchain1_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, tempo_sync_t<NV>>, 
                                      control::tempo_sync<NV>>;

template <int NV>
using modchain1_t = wrap::control_rate<modchain1_t_<NV>>;
using stereo_cable = cable::block<2>;
template <int NV>
using oversample_t_ = container::chain<parameter::empty, 
                                       wrap::fix<2, routing::receive<stereo_cable>>, 
                                       project::gr1<NV>, 
                                       filters::one_pole<NV>, 
                                       routing::send<stereo_cable>>;

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
                                 wrap::fix<2, modchain_t<NV>>, 
                                 chain6_t<NV>>;

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
                                        parameter::plain<PolyGrain_impl::pma2_t<NV>, 2>>;

DECLARE_PARAMETER_RANGE_STEP(GranUnsync_InputRange, 
                             0., 
                             6400., 
                             0.1);

template <int NV>
using GranUnsync = parameter::chain<GranUnsync_InputRange, 
                                    parameter::plain<PolyGrain_impl::pma3_t<NV>, 2>>;

DECLARE_PARAMETER_RANGE_STEP(PosSrc_InputRange, 
                             1., 
                             17., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(PosSrc_0Range, 
                             0., 
                             3., 
                             1.);

template <int NV>
using PosSrc_0 = parameter::from0To1<PolyGrain_impl::branch_t<NV>, 
                                     0, 
                                     PosSrc_0Range>;

template <int NV>
using PosSrc = parameter::chain<PosSrc_InputRange, PosSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(MixSrx_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using MixSrx_0 = parameter::from0To1<PolyGrain_impl::branch1_t<NV>, 
                                     0, 
                                     PosSrc_0Range>;

template <int NV>
using MixSrx = parameter::chain<MixSrx_InputRange, MixSrx_0<NV>>;

template <int NV>
using GsizeMod = parameter::chain<ranges::Identity, 
                                  parameter::plain<PolyGrain_impl::pma3_t<NV>, 1>, 
                                  parameter::plain<PolyGrain_impl::pma2_t<NV>, 1>>;

DECLARE_PARAMETER_RANGE_STEP(GsizeSrc_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using GsizeSrc_0 = parameter::from0To1<PolyGrain_impl::branch3_t<NV>, 
                                       0, 
                                       PosSrc_0Range>;

template <int NV>
using GsizeSrc_1 = parameter::from0To1<PolyGrain_impl::branch2_t<NV>, 
                                       0, 
                                       PosSrc_0Range>;

template <int NV>
using GsizeSrc = parameter::chain<GsizeSrc_InputRange, 
                                  GsizeSrc_0<NV>, 
                                  GsizeSrc_1<NV>>;

DECLARE_PARAMETER_RANGE_STEP(PitchSrc_InputRange, 
                             1., 
                             17., 
                             1.);
template <int NV>
using PitchSrc_0 = parameter::from0To1<PolyGrain_impl::branch4_t<NV>, 
                                       0, 
                                       PosSrc_0Range>;

template <int NV>
using PitchSrc = parameter::chain<PitchSrc_InputRange, PitchSrc_0<NV>>;

template <int NV>
using IntLength = parameter::plain<project::gr1<NV>, 0>;
template <int NV>
using Position = parameter::plain<PolyGrain_impl::pma_t<NV>, 
                                  2>;
template <int NV>
using Freeze = parameter::plain<project::gr1<NV>, 9>;
template <int NV>
using PosMod = parameter::plain<PolyGrain_impl::pma_t<NV>, 
                                1>;
template <int NV>
using GranMix = parameter::plain<PolyGrain_impl::pma1_t<NV>, 
                                 2>;
template <int NV>
using GrainDiv = parameter::plain<PolyGrain_impl::tempo_sync_t<NV>, 
                                  1>;
template <int NV>
using GrainSync = parameter::plain<PolyGrain_impl::tempo_sync_t<NV>, 
                                   2>;
template <int NV>
using g1vol = parameter::plain<project::gr1<NV>, 10>;
using FB = parameter::plain<routing::receive<stereo_cable>, 
                            0>;
template <int NV>
using os = parameter::plain<PolyGrain_impl::oversample_t<NV>, 
                            0>;
template <int NV>
using MixMod = parameter::plain<PolyGrain_impl::pma1_t<NV>, 
                                1>;
template <int NV>
using Pitch = parameter::plain<control::pma<NV, parameter::empty>, 
                               2>;
template <int NV>
using PitchMod = parameter::plain<control::pma<NV, parameter::empty>, 
                                  1>;
using win = parameter::empty;
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
                                          FB, 
                                          os<NV>, 
                                          PosSrc<NV>, 
                                          MixMod<NV>, 
                                          MixSrx<NV>, 
                                          GsizeMod<NV>, 
                                          GsizeSrc<NV>, 
                                          Pitch<NV>, 
                                          PitchMod<NV>, 
                                          PitchSrc<NV>, 
                                          win>;
}

template <int NV>
using PolyGrain_t_ = container::chain<PolyGrain_t_parameters::PolyGrain_t_plist<NV>, 
                                      wrap::fix<2, chain_t<NV>>>;

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
		SNEX_METADATA_ENCODED_PARAMETERS(360)
		{
			0x005B, 0x0000, 0x4900, 0x746E, 0x654C, 0x676E, 0x6874, 0x0000, 
            0x8000, 0x0040, 0x8000, 0x0042, 0x8000, 0x0040, 0x8000, 0x003F, 
            0x8000, 0x5B3F, 0x0001, 0x0000, 0x6F50, 0x6973, 0x6974, 0x6E6F, 
            0x0000, 0x0000, 0x0000, 0x8000, 0xCD3F, 0x0CCC, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 0x7246, 0x6565, 0x657A, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 
            0x003F, 0x8000, 0x5B3F, 0x0003, 0x0000, 0x706C, 0x0000, 0x0000, 
            0x0000, 0x8000, 0x523F, 0x1EB8, 0x003F, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0004, 0x0000, 0x6F50, 0x4D73, 0x646F, 0x0000, 0x8000, 
            0x00BF, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0005, 0x0000, 0x7247, 0x6E61, 0x694D, 0x0078, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x065B, 0x0000, 0x4700, 0x6172, 0x6E69, 0x6953, 0x657A, 
            0x6554, 0x706D, 0x006F, 0x0000, 0x0000, 0x0000, 0x4190, 0x0000, 
            0x4140, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x075B, 0x0000, 0x4700, 
            0x6172, 0x6E69, 0x6944, 0x0076, 0x0000, 0x3F80, 0x0000, 0x4180, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x085B, 0x0000, 
            0x4700, 0x6172, 0x6E69, 0x7953, 0x636E, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x5B3F, 
            0x0009, 0x0000, 0x7247, 0x6E61, 0x6E55, 0x7973, 0x636E, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0045, 0x0000, 0x0000, 0x8000, 0xCD3F, 
            0xCCCC, 0x5B3D, 0x000A, 0x0000, 0x3167, 0x6F76, 0x006C, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0B5B, 0x0000, 0x4600, 0x0042, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0C5B, 
            0x0000, 0x6F00, 0x0073, 0x0000, 0x0000, 0x0000, 0x4080, 0x0000, 
            0x4080, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0D5B, 0x0000, 0x5000, 
            0x736F, 0x7253, 0x0063, 0x0000, 0x3F80, 0x0000, 0x4188, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0E5B, 0x0000, 0x4D00, 
            0x7869, 0x6F4D, 0x0064, 0x0000, 0xBF80, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0F5B, 0x0000, 0x4D00, 
            0x7869, 0x7253, 0x0078, 0x0000, 0x3F80, 0x0000, 0x4188, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x105B, 0x0000, 0x4700, 
            0x6973, 0x657A, 0x6F4D, 0x0064, 0x0000, 0xBF80, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x115B, 0x0000, 
            0x4700, 0x6973, 0x657A, 0x7253, 0x0063, 0x0000, 0x3F80, 0x0000, 
            0x4188, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x125B, 
            0x0000, 0x5000, 0x7469, 0x6863, 0x0000, 0xC000, 0x00C1, 0xC000, 
            0x6F41, 0x097A, 0x00C0, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0013, 
            0x0000, 0x6950, 0x6374, 0x4D68, 0x646F, 0x0000, 0x8000, 0x00BF, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0014, 0x0000, 0x6950, 0x6374, 0x5368, 0x6372, 0x0000, 0x8000, 
            0x003F, 0x8800, 0x0041, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x5B3F, 0x0015, 0x0000, 0x6977, 0x006E, 0x0000, 0x4248, 0x4000, 
            0x461C, 0x6000, 0x4510, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& chain = this->getT(0);                                                       // PolyGrain_impl::chain_t<NV>
		auto& modchain = this->getT(0).getT(0);                                            // PolyGrain_impl::modchain_t<NV>
		auto& split2 = this->getT(0).getT(0).getT(0);                                      // PolyGrain_impl::split2_t<NV>
		auto& global_cable = this->getT(0).getT(0).getT(0).getT(0);                        // PolyGrain_impl::global_cable_t<NV>
		auto& global_cable1 = this->getT(0).getT(0).getT(0).getT(1);                       // PolyGrain_impl::global_cable1_t<NV>
		auto& global_cable3 = this->getT(0).getT(0).getT(0).getT(2);                       // PolyGrain_impl::global_cable3_t<NV>
		auto& global_cable2 = this->getT(0).getT(0).getT(0).getT(3);                       // PolyGrain_impl::global_cable2_t<NV>
		auto& clear = this->getT(0).getT(0).getT(1);                                       // math::clear<NV>
		auto& split1 = this->getT(0).getT(0).getT(2);                                      // PolyGrain_impl::split1_t<NV>
		auto& chain1 = this->getT(0).getT(0).getT(2).getT(0);                              // PolyGrain_impl::chain1_t<NV>
		auto& chain12 = this->getT(0).getT(0).getT(2).getT(0).getT(0);                     // PolyGrain_impl::chain12_t<NV>
		auto& branch = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0);              // PolyGrain_impl::branch_t<NV>
		auto& add = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0).getT(0);         // math::add<NV>
		auto& add3 = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0).getT(1);        // math::add<NV>
		auto& add2 = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0).getT(2);        // math::add<NV>
		auto& add1 = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(0).getT(3);        // math::add<NV>
		auto& peak = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(1);                // PolyGrain_impl::peak_t<NV>
		auto& clear1 = this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(2);              // math::clear<NV>
		auto& pma = this->getT(0).getT(0).getT(2).getT(0).getT(1);                         // PolyGrain_impl::pma_t<NV>
		auto& chain3 = this->getT(0).getT(0).getT(2).getT(1);                              // PolyGrain_impl::chain3_t<NV>
		auto& chain13 = this->getT(0).getT(0).getT(2).getT(1).getT(0);                     // PolyGrain_impl::chain13_t<NV>
		auto& branch1 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0);             // PolyGrain_impl::branch1_t<NV>
		auto& add4 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0).getT(0);        // math::add<NV>
		auto& add5 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0).getT(1);        // math::add<NV>
		auto& add6 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0).getT(2);        // math::add<NV>
		auto& add7 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(0).getT(3);        // math::add<NV>
		auto& peak1 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(1);               // PolyGrain_impl::peak1_t<NV>
		auto& clear2 = this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(2);              // math::clear<NV>
		auto& pma1 = this->getT(0).getT(0).getT(2).getT(1).getT(1);                        // PolyGrain_impl::pma1_t<NV>
		auto& chain17 = this->getT(0).getT(0).getT(2).getT(2);                             // PolyGrain_impl::chain17_t<NV>
		auto& chain18 = this->getT(0).getT(0).getT(2).getT(2).getT(0);                     // PolyGrain_impl::chain18_t<NV>
		auto& branch3 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0);             // PolyGrain_impl::branch3_t<NV>
		auto& add12 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0).getT(0);       // math::add<NV>
		auto& add13 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0).getT(1);       // math::add<NV>
		auto& add14 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0).getT(2);       // math::add<NV>
		auto& add15 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(0).getT(3);       // math::add<NV>
		auto& peak3 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(1);               // PolyGrain_impl::peak3_t<NV>
		auto& clear4 = this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(2);              // math::clear<NV>
		auto& pma3 = this->getT(0).getT(0).getT(2).getT(2).getT(1);                        // PolyGrain_impl::pma3_t<NV>
		auto& chain4 = this->getT(0).getT(0).getT(2).getT(3);                              // PolyGrain_impl::chain4_t<NV>
		auto& chain16 = this->getT(0).getT(0).getT(2).getT(3).getT(0);                     // PolyGrain_impl::chain16_t<NV>
		auto& branch2 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0);             // PolyGrain_impl::branch2_t<NV>
		auto& add8 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0).getT(0);        // math::add<NV>
		auto& add9 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0).getT(1);        // math::add<NV>
		auto& add10 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0).getT(2);       // math::add<NV>
		auto& add11 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(0).getT(3);       // math::add<NV>
		auto& peak2 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(1);               // PolyGrain_impl::peak2_t<NV>
		auto& clear3 = this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(2);              // math::clear<NV>
		auto& pma2 = this->getT(0).getT(0).getT(2).getT(3).getT(1);                        // PolyGrain_impl::pma2_t<NV>
		auto& chain19 = this->getT(0).getT(0).getT(2).getT(4);                             // PolyGrain_impl::chain19_t<NV>
		auto& chain20 = this->getT(0).getT(0).getT(2).getT(4).getT(0);                     // PolyGrain_impl::chain20_t<NV>
		auto& branch4 = this->getT(0).getT(0).getT(2).getT(4).getT(0).getT(0);             // PolyGrain_impl::branch4_t<NV>
		auto& add16 = this->getT(0).getT(0).getT(2).getT(4).getT(0).getT(0).getT(0);       // math::add<NV>
		auto& add17 = this->getT(0).getT(0).getT(2).getT(4).getT(0).getT(0).getT(1);       // math::add<NV>
		auto& add18 = this->getT(0).getT(0).getT(2).getT(4).getT(0).getT(0).getT(2);       // math::add<NV>
		auto& add19 = this->getT(0).getT(0).getT(2).getT(4).getT(0).getT(0).getT(3);       // math::add<NV>
		auto& peak4 = this->getT(0).getT(0).getT(2).getT(4).getT(0).getT(1);               // PolyGrain_impl::peak4_t<NV>
		auto& clear5 = this->getT(0).getT(0).getT(2).getT(4).getT(0).getT(2);              // math::clear<NV>
		auto& pma4 = this->getT(0).getT(0).getT(2).getT(4).getT(1);                        // control::pma<NV, parameter::empty>
		auto& chain6 = this->getT(0).getT(1);                                              // PolyGrain_impl::chain6_t<NV>
		auto& chain9 = this->getT(0).getT(1).getT(0);                                      // PolyGrain_impl::chain9_t<NV>
		auto& xfader3 = this->getT(0).getT(1).getT(0).getT(0);                             // PolyGrain_impl::xfader3_t<NV>
		auto& split3 = this->getT(0).getT(1).getT(0).getT(1);                              // PolyGrain_impl::split3_t<NV>
		auto& chain10 = this->getT(0).getT(1).getT(0).getT(1).getT(0);                     // PolyGrain_impl::chain10_t<NV>
		auto& gain6 = this->getT(0).getT(1).getT(0).getT(1).getT(0).getT(0);               // core::gain<NV>
		auto& chain11 = this->getT(0).getT(1).getT(0).getT(1).getT(1);                     // PolyGrain_impl::chain11_t<NV>
		auto& modchain1 = this->getT(0).getT(1).getT(0).getT(1).getT(1).getT(0);           // PolyGrain_impl::modchain1_t<NV>
		auto& tempo_sync = this->getT(0).getT(1).getT(0).getT(1).getT(1).getT(0).getT(0);  // PolyGrain_impl::tempo_sync_t<NV>
		auto& tempo_sync1 = this->getT(0).getT(1).getT(0).getT(1).getT(1).getT(0).getT(1); // control::tempo_sync<NV>
		auto& chain2 = this->getT(0).getT(1).getT(0).getT(1).getT(1).getT(1);              // PolyGrain_impl::chain2_t<NV>
		auto& oversample = this->getT(0).getT(1).getT(0).getT(1).getT(1).getT(1).getT(0);  // PolyGrain_impl::oversample_t<NV>
		auto& receive1 = this->getT(0).getT(1).getT(0).getT(1).                            // routing::receive<stereo_cable>
                         getT(1).getT(1).getT(0).getT(0);
		auto& faust1 = this->getT(0).getT(1).getT(0).getT(1).                       // project::gr1<NV>
                       getT(1).getT(1).getT(0).getT(1);
		auto& one_pole = this->getT(0).getT(1).getT(0).getT(1).                     // filters::one_pole<NV>
                         getT(1).getT(1).getT(0).getT(2);
		auto& send1 = this->getT(0).getT(1).getT(0).getT(1).                        // routing::send<stereo_cable>
                      getT(1).getT(1).getT(0).getT(3);
		auto& oscilloscope = this->getT(0).getT(1).getT(0).getT(1).getT(1).getT(2); // PolyGrain_impl::oscilloscope_t
		auto& gain7 = this->getT(0).getT(1).getT(0).getT(1).getT(1).getT(3);        // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, faust1); // IntLength -> faust1::Interpolationlengthsamples
		
		this->getParameterT(1).connectT(0, pma); // Position -> pma::Add
		
		this->getParameterT(2).connectT(0, faust1); // Freeze -> faust1::Freezebuffer
		
		this->getParameterT(3).connectT(0, one_pole); // lp -> one_pole::Frequency
		
		this->getParameterT(4).connectT(0, pma); // PosMod -> pma::Multiply
		
		this->getParameterT(5).connectT(0, pma1); // GranMix -> pma1::Add
		
		this->getParameterT(6).connectT(0, pma2); // GrainSizeTempo -> pma2::Add
		
		this->getParameterT(7).connectT(0, tempo_sync); // GrainDiv -> tempo_sync::Multiplier
		
		this->getParameterT(8).connectT(0, tempo_sync); // GrainSync -> tempo_sync::Enabled
		
		this->getParameterT(9).connectT(0, pma3); // GranUnsync -> pma3::Add
		
		this->getParameterT(10).connectT(0, faust1); // g1vol -> faust1::Volume
		
		this->getParameterT(11).connectT(0, receive1); // FB -> receive1::Feedback
		
		this->getParameterT(12).connectT(0, oversample); // os -> oversample::Oversampling
		
		this->getParameterT(13).connectT(0, branch); // PosSrc -> branch::Index
		
		this->getParameterT(14).connectT(0, pma1); // MixMod -> pma1::Multiply
		
		this->getParameterT(15).connectT(0, branch1); // MixSrx -> branch1::Index
		
		auto& GsizeMod_p = this->getParameterT(16);
		GsizeMod_p.connectT(0, pma3); // GsizeMod -> pma3::Multiply
		GsizeMod_p.connectT(1, pma2); // GsizeMod -> pma2::Multiply
		
		auto& GsizeSrc_p = this->getParameterT(17);
		GsizeSrc_p.connectT(0, branch3); // GsizeSrc -> branch3::Index
		GsizeSrc_p.connectT(1, branch2); // GsizeSrc -> branch2::Index
		
		this->getParameterT(18).connectT(0, pma4); // Pitch -> pma4::Add
		
		this->getParameterT(19).connectT(0, pma4); // PitchMod -> pma4::Multiply
		
		this->getParameterT(20).connectT(0, branch4); // PitchSrc -> branch4::Index
		
		// Modulation Connections ------------------------------------------------------------------
		
		global_cable.getWrappedObject().getParameter().connectT(0, add);    // global_cable -> add::Value
		global_cable.getWrappedObject().getParameter().connectT(1, add4);   // global_cable -> add4::Value
		global_cable.getWrappedObject().getParameter().connectT(2, add12);  // global_cable -> add12::Value
		global_cable.getWrappedObject().getParameter().connectT(3, add8);   // global_cable -> add8::Value
		global_cable.getWrappedObject().getParameter().connectT(4, add16);  // global_cable -> add16::Value
		global_cable1.getWrappedObject().getParameter().connectT(0, add3);  // global_cable1 -> add3::Value
		global_cable1.getWrappedObject().getParameter().connectT(1, add5);  // global_cable1 -> add5::Value
		global_cable1.getWrappedObject().getParameter().connectT(2, add13); // global_cable1 -> add13::Value
		global_cable1.getWrappedObject().getParameter().connectT(3, add9);  // global_cable1 -> add9::Value
		global_cable1.getWrappedObject().getParameter().connectT(4, add17); // global_cable1 -> add17::Value
		global_cable3.getWrappedObject().getParameter().connectT(0, add2);  // global_cable3 -> add2::Value
		global_cable3.getWrappedObject().getParameter().connectT(1, add6);  // global_cable3 -> add6::Value
		global_cable3.getWrappedObject().getParameter().connectT(2, add14); // global_cable3 -> add14::Value
		global_cable3.getWrappedObject().getParameter().connectT(3, add10); // global_cable3 -> add10::Value
		global_cable3.getWrappedObject().getParameter().connectT(4, add18); // global_cable3 -> add18::Value
		global_cable2.getWrappedObject().getParameter().connectT(0, add1);  // global_cable2 -> add1::Value
		global_cable2.getWrappedObject().getParameter().connectT(1, add7);  // global_cable2 -> add7::Value
		global_cable2.getWrappedObject().getParameter().connectT(2, add15); // global_cable2 -> add15::Value
		global_cable2.getWrappedObject().getParameter().connectT(3, add11); // global_cable2 -> add11::Value
		global_cable2.getWrappedObject().getParameter().connectT(4, add19); // global_cable2 -> add19::Value
		pma.getWrappedObject().getParameter().connectT(0, faust1);          // pma -> faust1::Bufferposition
		peak.getParameter().connectT(0, pma);                               // peak -> pma::Value
		auto& xfader3_p = xfader3.getWrappedObject().getParameter();
		xfader3_p.getParameterT(0).connectT(0, gain6);                  // xfader3 -> gain6::Gain
		xfader3_p.getParameterT(1).connectT(0, gain7);                  // xfader3 -> gain7::Gain
		pma1.getWrappedObject().getParameter().connectT(0, xfader3);    // pma1 -> xfader3::Value
		peak1.getParameter().connectT(0, pma1);                         // peak1 -> pma1::Value
		tempo_sync.getParameter().connectT(0, faust1);                  // tempo_sync -> faust1::Grainlengthms
		pma3.getWrappedObject().getParameter().connectT(0, tempo_sync); // pma3 -> tempo_sync::UnsyncedTime
		peak3.getParameter().connectT(0, pma3);                         // peak3 -> pma3::Value
		pma2.getWrappedObject().getParameter().connectT(0, tempo_sync); // pma2 -> tempo_sync::Tempo
		peak2.getParameter().connectT(0, pma2);                         // peak2 -> pma2::Value
		peak4.getParameter().connectT(0, pma4);                         // peak4 -> pma4::Value
		
		// Send Connections ------------------------------------------------------------------------
		
		send1.connect(receive1);
		
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
		
		; // add12::Value is automated
		
		; // add13::Value is automated
		
		; // add14::Value is automated
		
		; // add15::Value is automated
		
		clear4.setParameterT(0, 0.); // math::clear::Value
		
		; // pma3::Value is automated
		; // pma3::Multiply is automated
		; // pma3::Add is automated
		
		; // branch2::Index is automated
		
		; // add8::Value is automated
		
		; // add9::Value is automated
		
		; // add10::Value is automated
		
		; // add11::Value is automated
		
		clear3.setParameterT(0, 0.); // math::clear::Value
		
		; // pma2::Value is automated
		; // pma2::Multiply is automated
		; // pma2::Add is automated
		
		; // branch4::Index is automated
		
		; // add16::Value is automated
		
		; // add17::Value is automated
		
		; // add18::Value is automated
		
		; // add19::Value is automated
		
		clear5.setParameterT(0, 0.); // math::clear::Value
		
		; // pma4::Value is automated
		; // pma4::Multiply is automated
		; // pma4::Add is automated
		
		; // xfader3::Value is automated
		
		;                              // gain6::Gain is automated
		gain6.setParameterT(1, 20.);   // core::gain::Smoothing
		gain6.setParameterT(2, -100.); // core::gain::ResetValue
		
		; // tempo_sync::Tempo is automated
		; // tempo_sync::Multiplier is automated
		; // tempo_sync::Enabled is automated
		; // tempo_sync::UnsyncedTime is automated
		
		tempo_sync1.setParameterT(0, 0.); // control::tempo_sync::Tempo
		tempo_sync1.setParameterT(1, 0.); // control::tempo_sync::Multiplier
		tempo_sync1.setParameterT(2, 1.); // control::tempo_sync::Enabled
		tempo_sync1.setParameterT(3, 0.); // control::tempo_sync::UnsyncedTime
		
		;                                // oversample::Oversampling is automated
		oversample.setParameterT(1, 0.); // container::chain::FilterType
		
		; // receive1::Feedback is automated
		
		;                                      // faust1::Interpolationlengthsamples is automated
		;                                      // faust1::Grainlengthms is automated
		;                                      // faust1::Bufferposition is automated
		faust1.setParameterT(3, -4.03961e-08); // core::faust::Timetransposition
		faust1.setParameterT(4, 0.);           // core::faust::Timeasyncdegree
		faust1.setParameterT(5, 0.);           // core::faust::Timeasyncdepth
		faust1.setParameterT(6, 1);            // core::faust::Pitchtransposition
		faust1.setParameterT(7, 0.);           // core::faust::Pitchasyncdegree
		faust1.setParameterT(8, 0.);           // core::faust::Pitchasyncdepth
		;                                      // faust1::Freezebuffer is automated
		;                                      // faust1::Volume is automated
		
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
		this->setParameterT(1, 0.55);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.62);
		this->setParameterT(4, 0.);
		this->setParameterT(5, 1.);
		this->setParameterT(6, 12.);
		this->setParameterT(7, 1.);
		this->setParameterT(8, 0.);
		this->setParameterT(9, 0.);
		this->setParameterT(10, 1.);
		this->setParameterT(11, 1.);
		this->setParameterT(12, 4.);
		this->setParameterT(13, 1.);
		this->setParameterT(14, 0.);
		this->setParameterT(15, 1.);
		this->setParameterT(16, 0.);
		this->setParameterT(17, 1.);
		this->setParameterT(18, -2.1481);
		this->setParameterT(19, 0.);
		this->setParameterT(20, 1.);
		this->setParameterT(21, 2310.);
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
		
		this->getT(0).getT(0).getT(0).getT(0).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_cable_t<NV>
		this->getT(0).getT(0).getT(0).getT(1).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_cable1_t<NV>
		this->getT(0).getT(0).getT(0).getT(2).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_cable3_t<NV>
		this->getT(0).getT(0).getT(0).getT(3).connectToRuntimeTarget(addConnection, c); // PolyGrain_impl::global_cable2_t<NV>
	}
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(0).getT(2).getT(0).getT(0).getT(1).setExternalData(b, index); // PolyGrain_impl::peak_t<NV>
		this->getT(0).getT(0).getT(2).getT(1).getT(0).getT(1).setExternalData(b, index); // PolyGrain_impl::peak1_t<NV>
		this->getT(0).getT(0).getT(2).getT(2).getT(0).getT(1).setExternalData(b, index); // PolyGrain_impl::peak3_t<NV>
		this->getT(0).getT(0).getT(2).getT(3).getT(0).getT(1).setExternalData(b, index); // PolyGrain_impl::peak2_t<NV>
		this->getT(0).getT(0).getT(2).getT(4).getT(0).getT(1).setExternalData(b, index); // PolyGrain_impl::peak4_t<NV>
		this->getT(0).getT(1).getT(0).getT(1).getT(1).getT(2).setExternalData(b, index); // PolyGrain_impl::oscilloscope_t
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


