 const var rm = Engine.getGlobalRoutingManager();
 
 const cable1 = rm.getCable("trig1");
 const var Note = Content.getComponent("Note");
 
 
 
 inline function onSync(value)
  {
  
 local note = Note.getValue();
 //local vel = cable2.getValue()-1;
 
  	
  	if (value == 1){
   Synth.playNote(note, 127);
  //	 Synth.playNote(note, 64+127);
 
  		 
 	 	Console.print("on"); 
 
  	 	}		
  	 	else{	
  	   Console.print("off"); 
  	 	
  		Engine.allNotesOff();
  	 	} 
  };
 
 cable1.registerCallback(onSync, SyncNotification);  
 
function onNoteOn()
{
	Message.sendToMidiOut();
//	Message.ignoreEvent(1);
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
 