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

namespace Filter_impl
{
// ==============================| Node & Parameter type declarations |==============================

using global_cable_t_index = runtime_target::indexers::fix_hash<3357039>;

template <int NV>
using global_cable_mod = parameter::chain<ranges::Identity, 
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
using xfader_t = control::xfader<xfader_multimod<NV>, faders::linear>;
template <int NV>
using pma_t = control::pma<NV, 
                           parameter::plain<xfader_t<NV>, 0>>;
template <int NV>
using peak_t = wrap::mod<parameter::plain<pma_t<NV>, 0>, 
                         wrap::no_data<core::peak>>;

template <int NV>
using chain6_t = container::chain<parameter::empty, 
                                  wrap::fix<1, branch_t<NV>>, 
                                  peak_t<NV>, 
                                  math::clear<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<1, chain6_t<NV>>, 
                                 pma_t<NV>>;
template <int NV> using branch1_t = branch_t<NV>;

DECLARE_PARAMETER_RANGE_SKEW(pma1_modRange, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using pma1_mod = parameter::from0To1<filters::svf<NV>, 
                                     0, 
                                     pma1_modRange>;

template <int NV>
using pma1_t = control::pma<NV, pma1_mod<NV>>;
template <int NV>
using peak1_t = wrap::mod<parameter::plain<pma1_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using chain7_t = container::chain<parameter::empty, 
                                  wrap::fix<1, branch1_t<NV>>, 
                                  peak1_t<NV>, 
                                  math::clear<NV>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<1, chain7_t<NV>>, 
                                  pma1_t<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, chain_t<NV>>, 
                                 chain1_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split2_t<NV>>, 
                                     math::clear<NV>, 
                                     split_t<NV>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV>
using chain3_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>>;

template <int NV>
using chain4_t = container::chain<parameter::empty, 
                                  wrap::fix<2, filters::svf<NV>>, 
                                  math::tanh<NV>, 
                                  core::gain<NV>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<2, chain3_t<NV>>, 
                                  chain4_t<NV>>;

namespace Filter_t_parameters
{
// Parameter list for Filter_impl::Filter_t --------------------------------------------------------

DECLARE_PARAMETER_RANGE_STEP(MixSrc_InputRange, 
                             1., 
                             4., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(MixSrc_0Range, 
                             0., 
                             3., 
                             1.);

template <int NV>
using MixSrc_0 = parameter::from0To1<Filter_impl::branch_t<NV>, 
                                     0, 
                                     MixSrc_0Range>;

template <int NV>
using MixSrc = parameter::chain<MixSrc_InputRange, MixSrc_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(Mode_InputRange, 
                             1., 
                             3., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(Mode_0Range, 
                             0., 
                             4., 
                             1.);

template <int NV>
using Mode_0 = parameter::from0To1<filters::svf<NV>, 
                                   4, 
                                   Mode_0Range>;

template <int NV>
using Mode = parameter::chain<Mode_InputRange, Mode_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(CutSrc_InputRange, 
                             1., 
                             4., 
                             1.);
template <int NV>
using CutSrc_0 = parameter::from0To1<Filter_impl::branch1_t<NV>, 
                                     0, 
                                     MixSrc_0Range>;

template <int NV>
using CutSrc = parameter::chain<CutSrc_InputRange, CutSrc_0<NV>>;

template <int NV>
using Mix = parameter::plain<Filter_impl::pma_t<NV>, 2>;
template <int NV>
using MixMod = parameter::plain<Filter_impl::pma_t<NV>, 1>;
template <int NV>
using Res = parameter::plain<filters::svf<NV>, 1>;
template <int NV>
using Cut = parameter::plain<Filter_impl::pma1_t<NV>, 
                             2>;
template <int NV>
using CutMod = parameter::plain<Filter_impl::pma1_t<NV>, 
                                1>;
template <int NV>
using Filter_t_plist = parameter::list<Mix<NV>, 
                                       MixMod<NV>, 
                                       MixSrc<NV>, 
                                       Mode<NV>, 
                                       Res<NV>, 
                                       Cut<NV>, 
                                       CutMod<NV>, 
                                       CutSrc<NV>>;
}

template <int NV>
using Filter_t_ = container::chain<Filter_t_parameters::Filter_t_plist<NV>, 
                                   wrap::fix<2, modchain_t<NV>>, 
                                   xfader_t<NV>, 
                                   split1_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Filter_impl::Filter_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Filter);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(124)
		{
			0x005B, 0x0000, 0x4D00, 0x7869, 0x0000, 0x0000, 0x0000, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0001, 
            0x0000, 0x694D, 0x4D78, 0x646F, 0x0000, 0x8000, 0x00BF, 0x8000, 
            0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0002, 
            0x0000, 0x694D, 0x5378, 0x6372, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x0040, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0003, 
            0x0000, 0x6F4D, 0x6564, 0x0000, 0x8000, 0x003F, 0x4000, 0x0040, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0004, 0x0000, 
            0x6552, 0x0073, 0x999A, 0x3E99, 0x6666, 0x411E, 0x999A, 0x3E99, 
            0x8918, 0x3E87, 0x0000, 0x0000, 0x055B, 0x0000, 0x4300, 0x7475, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0006, 0x0000, 0x7543, 0x4D74, 0x646F, 
            0x0000, 0x8000, 0x00BF, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0007, 0x0000, 0x7543, 0x5374, 0x6372, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x0040, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& modchain = this->getT(0);                                     // Filter_impl::modchain_t<NV>
		auto& split2 = this->getT(0).getT(0);                               // Filter_impl::split2_t<NV>
		auto& global_cable = this->getT(0).getT(0).getT(0);                 // Filter_impl::global_cable_t<NV>
		auto& global_cable1 = this->getT(0).getT(0).getT(1);                // Filter_impl::global_cable1_t<NV>
		auto& global_cable3 = this->getT(0).getT(0).getT(2);                // Filter_impl::global_cable3_t<NV>
		auto& global_cable2 = this->getT(0).getT(0).getT(3);                // Filter_impl::global_cable2_t<NV>
		auto& clear = this->getT(0).getT(1);                                // math::clear<NV>
		auto& split = this->getT(0).getT(2);                                // Filter_impl::split_t<NV>
		auto& chain = this->getT(0).getT(2).getT(0);                        // Filter_impl::chain_t<NV>
		auto& chain6 = this->getT(0).getT(2).getT(0).getT(0);               // Filter_impl::chain6_t<NV>
		auto& branch = this->getT(0).getT(2).getT(0).getT(0).getT(0);       // Filter_impl::branch_t<NV>
		auto& add = this->getT(0).getT(2).getT(0).getT(0).getT(0).getT(0);  // math::add<NV>
		auto& add3 = this->getT(0).getT(2).getT(0).getT(0).getT(0).getT(1); // math::add<NV>
		auto& add2 = this->getT(0).getT(2).getT(0).getT(0).getT(0).getT(2); // math::add<NV>
		auto& add1 = this->getT(0).getT(2).getT(0).getT(0).getT(0).getT(3); // math::add<NV>
		auto& peak = this->getT(0).getT(2).getT(0).getT(0).getT(1);         // Filter_impl::peak_t<NV>
		auto& clear1 = this->getT(0).getT(2).getT(0).getT(0).getT(2);       // math::clear<NV>
		auto& pma = this->getT(0).getT(2).getT(0).getT(1);                  // Filter_impl::pma_t<NV>
		auto& chain1 = this->getT(0).getT(2).getT(1);                       // Filter_impl::chain1_t<NV>
		auto& chain7 = this->getT(0).getT(2).getT(1).getT(0);               // Filter_impl::chain7_t<NV>
		auto& branch1 = this->getT(0).getT(2).getT(1).getT(0).getT(0);      // Filter_impl::branch1_t<NV>
		auto& add4 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(0); // math::add<NV>
		auto& add5 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(1); // math::add<NV>
		auto& add6 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(2); // math::add<NV>
		auto& add7 = this->getT(0).getT(2).getT(1).getT(0).getT(0).getT(3); // math::add<NV>
		auto& peak1 = this->getT(0).getT(2).getT(1).getT(0).getT(1);        // Filter_impl::peak1_t<NV>
		auto& clear2 = this->getT(0).getT(2).getT(1).getT(0).getT(2);       // math::clear<NV>
		auto& pma1 = this->getT(0).getT(2).getT(1).getT(1);                 // Filter_impl::pma1_t<NV>
		auto& xfader = this->getT(1);                                       // Filter_impl::xfader_t<NV>
		auto& split1 = this->getT(2);                                       // Filter_impl::split1_t<NV>
		auto& chain3 = this->getT(2).getT(0);                               // Filter_impl::chain3_t<NV>
		auto& gain = this->getT(2).getT(0).getT(0);                         // core::gain<NV>
		auto& chain4 = this->getT(2).getT(1);                               // Filter_impl::chain4_t<NV>
		auto& svf = this->getT(2).getT(1).getT(0);                          // filters::svf<NV>
		auto& tanh = this->getT(2).getT(1).getT(1);                         // math::tanh<NV>
		auto& gain1 = this->getT(2).getT(1).getT(2);                        // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, pma); // Mix -> pma::Add
		
		this->getParameterT(1).connectT(0, pma); // MixMod -> pma::Multiply
		
		this->getParameterT(2).connectT(0, branch); // MixSrc -> branch::Index
		
		this->getParameterT(3).connectT(0, svf); // Mode -> svf::Mode
		
		this->getParameterT(4).connectT(0, svf); // Res -> svf::Q
		
		this->getParameterT(5).connectT(0, pma1); // Cut -> pma1::Add
		
		this->getParameterT(6).connectT(0, pma1); // CutMod -> pma1::Multiply
		
		this->getParameterT(7).connectT(0, branch1); // CutSrc -> branch1::Index
		
		// Modulation Connections ------------------------------------------------------------------
		
		global_cable.getWrappedObject().getParameter().connectT(0, add);   // global_cable -> add::Value
		global_cable.getWrappedObject().getParameter().connectT(1, add4);  // global_cable -> add4::Value
		global_cable1.getWrappedObject().getParameter().connectT(0, add3); // global_cable1 -> add3::Value
		global_cable1.getWrappedObject().getParameter().connectT(1, add5); // global_cable1 -> add5::Value
		global_cable3.getWrappedObject().getParameter().connectT(0, add2); // global_cable3 -> add2::Value
		global_cable3.getWrappedObject().getParameter().connectT(1, add6); // global_cable3 -> add6::Value
		global_cable2.getWrappedObject().getParameter().connectT(0, add1); // global_cable2 -> add1::Value
		global_cable2.getWrappedObject().getParameter().connectT(1, add7); // global_cable2 -> add7::Value
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);               // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1);              // xfader -> gain1::Gain
		pma.getWrappedObject().getParameter().connectT(0, xfader); // pma -> xfader::Value
		peak.getParameter().connectT(0, pma);                      // peak -> pma::Value
		pma1.getWrappedObject().getParameter().connectT(0, svf);   // pma1 -> svf::Frequency
		peak1.getParameter().connectT(0, pma1);                    // peak1 -> pma1::Value
		
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
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                           // svf::Frequency is automated
		;                           // svf::Q is automated
		svf.setParameterT(2, 0.);   // filters::svf::Gain
		svf.setParameterT(3, 0.01); // filters::svf::Smoothing
		;                           // svf::Mode is automated
		svf.setParameterT(5, 1.);   // filters::svf::Enabled
		
		tanh.setParameterT(0, 1.); // math::tanh::Value
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 1.);
		this->setParameterT(1, 0.);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 1.);
		this->setParameterT(4, 0.3);
		this->setParameterT(5, 0.);
		this->setParameterT(6, 0.);
		this->setParameterT(7, 1.);
		this->setExternalData({}, -1);
	}
	~instance() override
	{
		// Cleanup external data references --------------------------------------------------------
		
		this->setExternalData({}, -1);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
	
	void connectToRuntimeTarget(bool addConnection, const runtime_target::connection& c)
	{
		// Runtime target Connections --------------------------------------------------------------
		
		this->getT(0).getT(0).getT(0).connectToRuntimeTarget(addConnection, c); // Filter_impl::global_cable_t<NV>
		this->getT(0).getT(0).getT(1).connectToRuntimeTarget(addConnection, c); // Filter_impl::global_cable1_t<NV>
		this->getT(0).getT(0).getT(2).connectToRuntimeTarget(addConnection, c); // Filter_impl::global_cable3_t<NV>
		this->getT(0).getT(0).getT(3).connectToRuntimeTarget(addConnection, c); // Filter_impl::global_cable2_t<NV>
	}
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(2).getT(0).getT(0).getT(1).setExternalData(b, index); // Filter_impl::peak_t<NV>
		this->getT(0).getT(2).getT(1).getT(0).getT(1).setExternalData(b, index); // Filter_impl::peak1_t<NV>
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
using Filter = wrap::node<Filter_impl::instance<NV>>;
}


