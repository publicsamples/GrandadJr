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

namespace mod_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using ramp_t = wrap::no_data<core::ramp<NV, false>>;
template <int NV>
using tempo_sync_t = wrap::mod<parameter::plain<ramp_t<NV>, 0>, 
                               control::tempo_sync<NV>>;

template <int NV>
using chain3_t = container::chain<parameter::empty, 
                                  wrap::fix<1, tempo_sync_t<NV>>, 
                                  ramp_t<NV>>;
template <int NV>
using clock_ramp_t = wrap::no_data<core::clock_ramp<NV, false>>;

template <int NV>
using chain2_t = container::chain<parameter::empty, 
                                  wrap::fix<1, clock_ramp_t<NV>>>;
template <int NV>
using branch1_t = container::branch<parameter::empty, 
                                    wrap::fix<1, chain3_t<NV>>, 
                                    chain2_t<NV>>;

template <int NV>
using cable_table_t = wrap::data<control::cable_table<parameter::plain<math::add<NV>, 0>>, 
                                 data::external::table<0>>;

template <int NV>
using cable_pack_t = wrap::data<control::cable_pack<parameter::plain<math::add<NV>, 0>>, 
                                data::external::sliderpack<0>>;

template <int NV>
using peak_mod = parameter::chain<ranges::Identity, 
                                  parameter::plain<cable_table_t<NV>, 0>, 
                                  parameter::plain<cable_pack_t<NV>, 0>>;

template <int NV>
using peak_t = wrap::mod<peak_mod<NV>, 
                         wrap::no_data<core::peak>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<1, cable_table_t<NV>>, 
                                 math::add<NV>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<1, cable_pack_t<NV>>, 
                                  math::add<NV>>;
template <int NV>
using branch_t = container::branch<parameter::empty, 
                                   wrap::fix<1, chain_t<NV>>, 
                                   chain1_t<NV>>;

using global_cable_t_index = runtime_target::indexers::fix_hash<3357039>;
using peak1_mod = parameter::plain<routing::global_cable<global_cable_t_index, parameter::empty>, 
                                   0>;
using peak1_t = wrap::mod<peak1_mod, 
                          wrap::no_data<core::peak>>;

using chain4_t = container::chain<parameter::empty, 
                                  wrap::fix<1, peak1_t>, 
                                  routing::global_cable<global_cable_t_index, parameter::empty>>;

using global_cable3_t_index = runtime_target::indexers::fix_hash<3357040>;
using peak4_mod = parameter::plain<routing::global_cable<global_cable3_t_index, parameter::empty>, 
                                   0>;
using peak4_t = wrap::mod<peak4_mod, 
                          wrap::no_data<core::peak>>;

using chain7_t = container::chain<parameter::empty, 
                                  wrap::fix<1, peak4_t>, 
                                  routing::global_cable<global_cable3_t_index, parameter::empty>>;

using global_cable2_t_index = runtime_target::indexers::fix_hash<3357041>;
using peak3_mod = parameter::plain<routing::global_cable<global_cable2_t_index, parameter::empty>, 
                                   0>;
using peak3_t = wrap::mod<peak3_mod, 
                          wrap::no_data<core::peak>>;

using chain6_t = container::chain<parameter::empty, 
                                  wrap::fix<1, peak3_t>, 
                                  routing::global_cable<global_cable2_t_index, parameter::empty>>;

using global_cable1_t_index = runtime_target::indexers::fix_hash<3357042>;
using peak2_mod = parameter::plain<routing::global_cable<global_cable1_t_index, parameter::empty>, 
                                   0>;
using peak2_t = wrap::mod<peak2_mod, 
                          wrap::no_data<core::peak>>;

using chain5_t = container::chain<parameter::empty, 
                                  wrap::fix<1, peak2_t>, 
                                  routing::global_cable<global_cable1_t_index, parameter::empty>>;
using branch2_t = container::branch<parameter::empty, 
                                    wrap::fix<1, chain4_t>, 
                                    chain7_t, 
                                    chain6_t, 
                                    chain5_t>;

namespace mod_t_parameters
{
// Parameter list for mod_impl::mod_t --------------------------------------------------------------

template <int NV>
using Tempo = parameter::chain<ranges::Identity, 
                               parameter::plain<mod_impl::clock_ramp_t<NV>, 0>, 
                               parameter::plain<mod_impl::tempo_sync_t<NV>, 0>>;

template <int NV>
using DIV = parameter::chain<ranges::Identity, 
                             parameter::plain<mod_impl::clock_ramp_t<NV>, 1>, 
                             parameter::plain<mod_impl::tempo_sync_t<NV>, 1>>;

template <int NV>
using MODE = parameter::plain<mod_impl::branch_t<NV>, 0>;
template <int NV>
using DawSync = parameter::plain<mod_impl::branch1_t<NV>, 
                                 0>;
using modOut = parameter::plain<mod_impl::branch2_t, 0>;
template <int NV>
using mod_t_plist = parameter::list<Tempo<NV>, 
                                    DIV<NV>, 
                                    MODE<NV>, 
                                    DawSync<NV>, 
                                    modOut>;
}

template <int NV>
using mod_t_ = container::chain<mod_t_parameters::mod_t_plist<NV>, 
                                wrap::fix<1, branch1_t<NV>>, 
                                peak_t<NV>, 
                                math::clear<NV>, 
                                branch_t<NV>, 
                                branch2_t>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public mod_impl::mod_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 1;
		static const int NumSliderPacks = 1;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(mod);
		SNEX_METADATA_NUM_CHANNELS(1);
		SNEX_METADATA_ENCODED_PARAMETERS(78)
		{
			0x005B, 0x0000, 0x5400, 0x6D65, 0x6F70, 0x0000, 0x0000, 0x0000, 
            0x9000, 0x0041, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x5B3F, 
            0x0001, 0x0000, 0x4944, 0x0056, 0x0000, 0x3F80, 0x0000, 0x4180, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x025B, 0x0000, 
            0x4D00, 0x444F, 0x0045, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x035B, 0x0000, 0x4400, 
            0x7761, 0x7953, 0x636E, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0004, 0x0000, 
            0x6F6D, 0x4F64, 0x7475, 0x0000, 0x0000, 0x0000, 0x4000, 0x0040, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& branch1 = this->getT(0);                       // mod_impl::branch1_t<NV>
		auto& chain3 = this->getT(0).getT(0);                // mod_impl::chain3_t<NV>
		auto& tempo_sync = this->getT(0).getT(0).getT(0);    // mod_impl::tempo_sync_t<NV>
		auto& ramp = this->getT(0).getT(0).getT(1);          // mod_impl::ramp_t<NV>
		auto& chain2 = this->getT(0).getT(1);                // mod_impl::chain2_t<NV>
		auto& clock_ramp = this->getT(0).getT(1).getT(0);    // mod_impl::clock_ramp_t<NV>
		auto& peak = this->getT(1);                          // mod_impl::peak_t<NV>
		auto& clear = this->getT(2);                         // math::clear<NV>
		auto& branch = this->getT(3);                        // mod_impl::branch_t<NV>
		auto& chain = this->getT(3).getT(0);                 // mod_impl::chain_t<NV>
		auto& cable_table = this->getT(3).getT(0).getT(0);   // mod_impl::cable_table_t<NV>
		auto& add = this->getT(3).getT(0).getT(1);           // math::add<NV>
		auto& chain1 = this->getT(3).getT(1);                // mod_impl::chain1_t<NV>
		auto& cable_pack = this->getT(3).getT(1).getT(0);    // mod_impl::cable_pack_t<NV>
		auto& add1 = this->getT(3).getT(1).getT(1);          // math::add<NV>
		auto& branch2 = this->getT(4);                       // mod_impl::branch2_t
		auto& chain4 = this->getT(4).getT(0);                // mod_impl::chain4_t
		auto& peak1 = this->getT(4).getT(0).getT(0);         // mod_impl::peak1_t
		auto& global_cable = this->getT(4).getT(0).getT(1);  // routing::global_cable<global_cable_t_index, parameter::empty>
		auto& chain7 = this->getT(4).getT(1);                // mod_impl::chain7_t
		auto& peak4 = this->getT(4).getT(1).getT(0);         // mod_impl::peak4_t
		auto& global_cable3 = this->getT(4).getT(1).getT(1); // routing::global_cable<global_cable3_t_index, parameter::empty>
		auto& chain6 = this->getT(4).getT(2);                // mod_impl::chain6_t
		auto& peak3 = this->getT(4).getT(2).getT(0);         // mod_impl::peak3_t
		auto& global_cable2 = this->getT(4).getT(2).getT(1); // routing::global_cable<global_cable2_t_index, parameter::empty>
		auto& chain5 = this->getT(4).getT(3);                // mod_impl::chain5_t
		auto& peak2 = this->getT(4).getT(3).getT(0);         // mod_impl::peak2_t
		auto& global_cable1 = this->getT(4).getT(3).getT(1); // routing::global_cable<global_cable1_t_index, parameter::empty>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& Tempo_p = this->getParameterT(0);
		Tempo_p.connectT(0, clock_ramp); // Tempo -> clock_ramp::Tempo
		Tempo_p.connectT(1, tempo_sync); // Tempo -> tempo_sync::Tempo
		
		auto& DIV_p = this->getParameterT(1);
		DIV_p.connectT(0, clock_ramp); // DIV -> clock_ramp::Multiplier
		DIV_p.connectT(1, tempo_sync); // DIV -> tempo_sync::Multiplier
		
		this->getParameterT(2).connectT(0, branch); // MODE -> branch::Index
		
		this->getParameterT(3).connectT(0, branch1); // DawSync -> branch1::Index
		
		this->getParameterT(4).connectT(0, branch2); // modOut -> branch2::Index
		
		// Modulation Connections ------------------------------------------------------------------
		
		tempo_sync.getParameter().connectT(0, ramp);                    // tempo_sync -> ramp::PeriodTime
		cable_table.getWrappedObject().getParameter().connectT(0, add); // cable_table -> add::Value
		cable_pack.getWrappedObject().getParameter().connectT(0, add1); // cable_pack -> add1::Value
		peak.getParameter().connectT(0, cable_table);                   // peak -> cable_table::Value
		peak.getParameter().connectT(1, cable_pack);                    // peak -> cable_pack::Value
		peak1.getParameter().connectT(0, global_cable);                 // peak1 -> global_cable::Value
		peak4.getParameter().connectT(0, global_cable3);                // peak4 -> global_cable3::Value
		peak3.getParameter().connectT(0, global_cable2);                // peak3 -> global_cable2::Value
		peak2.getParameter().connectT(0, global_cable1);                // peak2 -> global_cable1::Value
		
		// Default Values --------------------------------------------------------------------------
		
		; // branch1::Index is automated
		
		;                                  // tempo_sync::Tempo is automated
		;                                  // tempo_sync::Multiplier is automated
		tempo_sync.setParameterT(2, 1.);   // control::tempo_sync::Enabled
		tempo_sync.setParameterT(3, 200.); // control::tempo_sync::UnsyncedTime
		
		;                          // ramp::PeriodTime is automated
		ramp.setParameterT(1, 0.); // core::ramp::LoopStart
		ramp.setParameterT(2, 1.); // core::ramp::Gate
		
		;                                // clock_ramp::Tempo is automated
		;                                // clock_ramp::Multiplier is automated
		clock_ramp.setParameterT(2, 1.); // core::clock_ramp::AddToSignal
		clock_ramp.setParameterT(3, 1.); // core::clock_ramp::UpdateMode
		clock_ramp.setParameterT(4, 0.); // core::clock_ramp::Inactive
		
		clear.setParameterT(0, 0.); // math::clear::Value
		
		; // branch::Index is automated
		
		; // cable_table::Value is automated
		
		; // add::Value is automated
		
		; // cable_pack::Value is automated
		
		; // add1::Value is automated
		
		; // branch2::Index is automated
		
		; // global_cable::Value is automated
		
		; // global_cable3::Value is automated
		
		; // global_cable2::Value is automated
		
		; // global_cable1::Value is automated
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 0.);
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
		
		this->getT(4).getT(0).getT(1).connectToRuntimeTarget(addConnection, c); // routing::global_cable<global_cable_t_index, parameter::empty>
		this->getT(4).getT(1).getT(1).connectToRuntimeTarget(addConnection, c); // routing::global_cable<global_cable3_t_index, parameter::empty>
		this->getT(4).getT(2).getT(1).connectToRuntimeTarget(addConnection, c); // routing::global_cable<global_cable2_t_index, parameter::empty>
		this->getT(4).getT(3).getT(1).connectToRuntimeTarget(addConnection, c); // routing::global_cable<global_cable1_t_index, parameter::empty>
	}
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(0).getT(1).setExternalData(b, index); // mod_impl::ramp_t<NV>
		this->getT(0).getT(1).getT(0).setExternalData(b, index); // mod_impl::clock_ramp_t<NV>
		this->getT(1).setExternalData(b, index);                 // mod_impl::peak_t<NV>
		this->getT(3).getT(0).getT(0).setExternalData(b, index); // mod_impl::cable_table_t<NV>
		this->getT(3).getT(1).getT(0).setExternalData(b, index); // mod_impl::cable_pack_t<NV>
		this->getT(4).getT(0).getT(0).setExternalData(b, index); // mod_impl::peak1_t
		this->getT(4).getT(1).getT(0).setExternalData(b, index); // mod_impl::peak4_t
		this->getT(4).getT(2).getT(0).setExternalData(b, index); // mod_impl::peak3_t
		this->getT(4).getT(3).getT(0).setExternalData(b, index); // mod_impl::peak2_t
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
using mod = wrap::node<mod_impl::instance<NV>>;
}


