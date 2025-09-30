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

namespace delStage_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using stereo_cable = cable::block<NV, 2>;

template <int NV>
using tempo_sync_t = wrap::mod<parameter::plain<jdsp::jdelay_cubic<NV>, 1>, 
                               control::tempo_sync<NV>>;

template <int NV>
using converter_mod = parameter::chain<ranges::Identity, 
                                       parameter::plain<project::shift<NV>, 1>, 
                                       parameter::plain<project::shift<NV>, 2>>;

template <int NV>
using converter_t = control::converter<converter_mod<NV>, 
                                       conversion_logic::samples2ms>;
template <int NV>
using tempo_sync1_t = wrap::mod<parameter::plain<converter_t<NV>, 0>, 
                                control::tempo_sync<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, tempo_sync_t<NV>>, 
                                 jdsp::jdelay_cubic<NV>, 
                                 tempo_sync1_t<NV>, 
                                 converter_t<NV>, 
                                 project::shift<NV>>;

namespace delStage_t_parameters
{
// Parameter list for delStage_impl::delStage_t ----------------------------------------------------

template <int NV>
using feed = parameter::plain<routing::receive<NV, stereo_cable<NV>>, 
                              0>;
template <int NV>
using sync = parameter::plain<delStage_impl::tempo_sync_t<NV>, 
                              2>;
template <int NV>
using time = parameter::plain<delStage_impl::tempo_sync_t<NV>, 
                              3>;
template <int NV>
using tempo = parameter::plain<delStage_impl::tempo_sync_t<NV>, 
                               0>;
template <int NV>
using div = parameter::plain<delStage_impl::tempo_sync_t<NV>, 
                             1>;
template <int NV>
using WinSync = parameter::plain<delStage_impl::tempo_sync1_t<NV>, 
                                 2>;
template <int NV>
using WinTime = parameter::plain<delStage_impl::tempo_sync1_t<NV>, 
                                 3>;
template <int NV>
using WinDiv = parameter::plain<delStage_impl::tempo_sync1_t<NV>, 
                                1>;
template <int NV>
using WinTempo = parameter::plain<delStage_impl::tempo_sync1_t<NV>, 
                                  0>;
template <int NV>
using tanh = parameter::plain<math::tanh<NV>, 0>;
template <int NV>
using delStage_t_plist = parameter::list<feed<NV>, 
                                         sync<NV>, 
                                         time<NV>, 
                                         tempo<NV>, 
                                         div<NV>, 
                                         WinSync<NV>, 
                                         WinTime<NV>, 
                                         WinDiv<NV>, 
                                         WinTempo<NV>, 
                                         tanh<NV>>;
}

template <int NV>
using delStage_t_ = container::chain<delStage_t_parameters::delStage_t_plist<NV>, 
                                     wrap::fix<2, routing::receive<NV, stereo_cable<NV>>>, 
                                     chain_t<NV>, 
                                     math::tanh<NV>, 
                                     routing::send<NV, stereo_cable<NV>>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public delStage_impl::delStage_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(delStage);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(168)
		{
			0x005C, 0x0000, 0x0000, 0x6566, 0x6465, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x5E35, 0x3F2D, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x005C, 0x0001, 0x0000, 0x7973, 0x636E, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x005C, 0x0002, 0x0000, 0x6974, 0x656D, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x447A, 0x0000, 0x0000, 0x0000, 0x3F80, 0xCCCD, 0x3DCC, 
            0x005C, 0x0003, 0x0000, 0x6574, 0x706D, 0x006F, 0x0000, 0x0000, 
            0x0000, 0x9000, 0x0041, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x5C3F, 0x0400, 0x0000, 0x6400, 0x7669, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x4180, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x005C, 0x0005, 0x0000, 0x6957, 0x536E, 0x6E79, 0x0063, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x8000, 0x5C3F, 0x0600, 0x0000, 0x5700, 0x6E69, 0x6954, 0x656D, 
            0x0000, 0x0000, 0x0000, 0x0000, 0x44FA, 0x0000, 0x4348, 0x0000, 
            0x3F80, 0xCCCD, 0x3DCC, 0x005C, 0x0007, 0x0000, 0x6957, 0x446E, 
            0x7669, 0x0000, 0x0000, 0x3F80, 0x0000, 0x4180, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x005C, 0x0008, 0x0000, 0x6957, 
            0x546E, 0x6D65, 0x6F70, 0x0000, 0x0000, 0x0000, 0x0000, 0x4190, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x005C, 0x0009, 
            0x0000, 0x6174, 0x686E, 0x0000, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000
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
		
		auto& receive = this->getT(0);              // routing::receive<NV, stereo_cable<NV>>
		auto& chain = this->getT(1);                // delStage_impl::chain_t<NV>
		auto& tempo_sync = this->getT(1).getT(0);   // delStage_impl::tempo_sync_t<NV>
		auto& jdelay_cubic = this->getT(1).getT(1); // jdsp::jdelay_cubic<NV>
		auto& tempo_sync1 = this->getT(1).getT(2);  // delStage_impl::tempo_sync1_t<NV>
		auto& converter = this->getT(1).getT(3);    // delStage_impl::converter_t<NV>
		auto& faust = this->getT(1).getT(4);        // project::shift<NV>
		auto& tanh = this->getT(2);                 // math::tanh<NV>
		auto& send = this->getT(3);                 // routing::send<NV, stereo_cable<NV>>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, receive); // feed -> receive::Feedback
		
		this->getParameterT(1).connectT(0, tempo_sync); // sync -> tempo_sync::Enabled
		
		this->getParameterT(2).connectT(0, tempo_sync); // time -> tempo_sync::UnsyncedTime
		
		this->getParameterT(3).connectT(0, tempo_sync); // tempo -> tempo_sync::Tempo
		
		this->getParameterT(4).connectT(0, tempo_sync); // div -> tempo_sync::Multiplier
		
		this->getParameterT(5).connectT(0, tempo_sync1); // WinSync -> tempo_sync1::Enabled
		
		this->getParameterT(6).connectT(0, tempo_sync1); // WinTime -> tempo_sync1::UnsyncedTime
		
		this->getParameterT(7).connectT(0, tempo_sync1); // WinDiv -> tempo_sync1::Multiplier
		
		this->getParameterT(8).connectT(0, tempo_sync1); // WinTempo -> tempo_sync1::Tempo
		
		this->getParameterT(9).connectT(0, tanh); // tanh -> tanh::Value
		
		// Modulation Connections ------------------------------------------------------------------
		
		tempo_sync.getParameter().connectT(0, jdelay_cubic);            // tempo_sync -> jdelay_cubic::DelayTime
		converter.getWrappedObject().getParameter().connectT(0, faust); // converter -> faust::windowsamples
		converter.getWrappedObject().getParameter().connectT(1, faust); // converter -> faust::xfadesamples
		tempo_sync1.getParameter().connectT(0, converter);              // tempo_sync1 -> converter::Value
		
		// Send Connections ------------------------------------------------------------------------
		
		send.connect(receive);
		
		// Default Values --------------------------------------------------------------------------
		
		; // receive::Feedback is automated
		
		; // tempo_sync::Tempo is automated
		; // tempo_sync::Multiplier is automated
		; // tempo_sync::Enabled is automated
		; // tempo_sync::UnsyncedTime is automated
		
		jdelay_cubic.setParameterT(0, 1000.); // jdsp::jdelay_cubic::Limit
		;                                     // jdelay_cubic::DelayTime is automated
		
		; // tempo_sync1::Tempo is automated
		; // tempo_sync1::Multiplier is automated
		; // tempo_sync1::Enabled is automated
		; // tempo_sync1::UnsyncedTime is automated
		
		; // converter::Value is automated
		
		faust.setParameterT(0, 1.78814e-07); // core::faust::shiftsemitones
		;                                    // faust::windowsamples is automated
		;                                    // faust::xfadesamples is automated
		
		; // tanh::Value is automated
		
		this->setParameterT(0, 0.677219);
		this->setParameterT(1, 0.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 1.);
		this->setParameterT(5, 0.);
		this->setParameterT(6, 200.);
		this->setParameterT(7, 1.);
		this->setParameterT(8, 0.);
		this->setParameterT(9, 1.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool isProcessingHiseEvent() { return true; };
	
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
using delStage = wrap::node<delStage_impl::instance<NV>>;
}


