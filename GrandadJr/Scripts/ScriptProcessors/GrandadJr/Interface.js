Content.makeFrontInterface(620, 700);

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



inline function onMODEControl(component, value)
{
		for(s in GranCont1)
      s.showControl(value-1);
     
     for(s in GranCont2)
       s.showControl(value);
      
      Gthng.setAttribute(Gthng.MODE, value);    
};

Content.getComponent("MODE").setControlCallback(onMODEControl);


const var Presets = Content.getComponent("Presets");


inline function onPRESETSControl(component, value)
{
	Presets.showControl(value);
};

Content.getComponent("PRESETS").setControlCallback(onPRESETSControl);

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
 