Content.makeFrontInterface(822, 790);
//Settings.setZoomLevel(0.85);
include("GeneralLAF.js");
include("Rect.js");
include("KnobLAF1.js");
include("KnobLAF2.js");
//include("KnobLAF3.js");

Engine.loadFontAs("{PROJECT_FOLDER}standard-bold-italic-webfont.ttf", "ital");
Engine.loadFontAs("{PROJECT_FOLDER}standard-bold-webfont.ttf", "bold");
Engine.loadFontAs("{PROJECT_FOLDER}standard-book-webfont.ttf", "std");

const var GranCont1 = [Content.getComponent("IntLength"),
                       Content.getComponent("G1label1"),
                       Content.getComponent("G1label2"),
                       Content.getComponent("G1label3"),
                       Content.getComponent("Time"),
                       Content.getComponent("Pitch"),
                       Content.getComponent("Freeze")];

const var GranCont2 = [Content.getComponent("G2label1"),
                       Content.getComponent("G2label2"),
                       Content.getComponent("G2label5"),
                       Content.getComponent("G2label3"),
                       Content.getComponent("G2label6"),
                       Content.getComponent("RecTempo"),
                       Content.getComponent("RecDiv"),
                       Content.getComponent("TrigGain"),
                       Content.getComponent("Trig"),
                       Content.getComponent("Note"),
                       Content.getComponent("ModIn"),
                       Content.getComponent("REC"),
                       Content.getComponent("Dense")];

                           
const var Gthng = Synth.getEffect("Gthng");


inline function onGranularControl(component, value)
{
	Gthng.setAttribute(Gthng.Os, 4.0);   
};

Content.getComponent("Granular").setControlCallback(onGranularControl);



const var Presets = Content.getComponent("Presets");


inline function onPRESETSControl(component, value)
{
	Presets.showControl(value);
};

Content.getComponent("PRESETS").setControlCallback(onPRESETSControl);


const var GrainSize = Content.getComponent("GrainSize");
const var GrainSize1 = Content.getComponent("GrainSize1");



inline function onMODE1Control(component, value)
{
	GrainSize.showControl(value-1);
	GrainSize1.showControl(value);
	
	Gthng.setAttribute(Gthng.GrainSync, value);   
	
};

Content.getComponent("MODE1").setControlCallback(onMODE1Control);

//mod

const var Table1 = Content.getComponent("Table1");
const var Table2 = Content.getComponent("Table2");
const var Table3 = Content.getComponent("Table3");
const var Table4 = Content.getComponent("Table4");

const var ScriptSliderPack1 = Content.getComponent("ScriptSliderPack1");
const var ScriptSliderPack2 = Content.getComponent("ScriptSliderPack2");
const var ScriptSliderPack3 = Content.getComponent("ScriptSliderPack3");
const var ScriptSliderPack4 = Content.getComponent("ScriptSliderPack4");

const var Mod1 = Synth.getModulator("Mod1");
const var Mod2 = Synth.getModulator("Mod2");
const var Mod3 = Synth.getModulator("Mod3");
const var Mod4 = Synth.getModulator("Mod4");


inline function onModMode1Control(component, value)
{
	Table1.showControl(value-1);
	ScriptSliderPack1.showControl(value);
	
	Mod1.setAttribute(Mod1.MODE, value); 
};

Content.getComponent("ModMode1").setControlCallback(onModMode1Control);



inline function onModMode2Control(component, value)
{
	Table2.showControl(value-1);
	ScriptSliderPack2.showControl(value);
	
	Mod2.setAttribute(Mod2.MODE, value); 
};

Content.getComponent("ModMode2").setControlCallback(onModMode2Control);


inline function onModMode3Control(component, value)
{
	Table3.showControl(value-1);
	ScriptSliderPack3.showControl(value);
	
	Mod3.setAttribute(Mod3.MODE, value); 
};

Content.getComponent("ModMode3").setControlCallback(onModMode3Control);


inline function onModMode4Control(component, value)
{
	Table4.showControl(value-1);
	ScriptSliderPack4.showControl(value);
	
	Mod4.setAttribute(Mod4.MODE, value); 
};

Content.getComponent("ModMode4").setControlCallback(onModMode4Control);



const var dp = Synth.getDisplayBufferSource("Gthng");


const var rb = dp.getDisplayBuffer(0);

const var BUFFER_LENGTH = 16384;

const var properties = {
  "BufferLength": BUFFER_LENGTH,
  "NumChannels": 1
};


rb.setRingBufferProperties(properties);

const var P1 = Content.getComponent("P1");


P1.setTimerCallback(function()
{

	this.data.buffer = rb.createPath(this.getLocalBounds(0),
									 [0, BUFFER_LENGTH, 0, 1.0], 
									 0.0 
									 );
	this.repaint();
});

P1.startTimer(30);

P1.setPaintRoutine(function(g)
{
	g.fillAll(0x22FFFFFF);
	g.setColour(Colours.white);
	g.fillPath(this.data.buffer, this.getLocalBounds(0));
});







function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{
	
}
 