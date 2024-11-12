
return {
	egba={
    description = "EGBA functions.",
	 	type = "lib",
	 	version = "a1.8-1"
 	},
  EGBA={
    args="()",
    description="loop function, update 60/secs",
    returns="()",
    type="function"
  },
  trace={
    args="(s:string)",
    description="log string in console",
    returns="()",
    type="function"
  },
  pal={
    args="(id:number)",
    description="palette swap id 0 -> 4",
    returns="()",
    type="function"
  },
  cls={
    args="(idcolor:number)",
    description="clear screen with idcolor of currant palette",
    returns="()",
    type="function"
  },
  text={
    args="(text:string,x:number,y:number,idcolor:number,fontsize:number)",
    description="print text in x y with idcolor and fontsize",
    returns="()",
    type="function"
  },
  rect={
    args="(x:number,y:number,width:number,height:number,idcolor:number)",
    description="draw fill rectangle in x y with size width/height and idcolor",
    returns="()",
    type="function"
  },
  rectb={
    args="(x:number,y:number,width:number,height:number,idcolor:number)",
    description="draw line rectangle in x y with size width/height and idcolor",
    returns="()",
    type="function"
  },
  
  pix={
    args="(x:number,y:number,idcolor:number)",
    description="draw pixel in x y with idcolor",
    returns="()",
    type="function"
  },
  
  spr={
    args="(idspr:number,x:number,y:number,scale:number,rot:number)",
    description="idspr 0->31\n rot 0=0° 1=90° 2=180° 3=270°",
    returns="()",
    type="function"
  },
  
  btn={
    args="(idbtn:number)",
    description="if key down\n0 : up\n1 : down\n2 : left\n3 : right\n4 : x\n5 : c",
    returns="()",
    type="function"
  },
  
  btnp={
    args="(idbtn:number)",
    description="if key press\n0 : up\n1 : down\n2 : left\n3 : right\n4 : x\n5 : c",
    returns="()",
    type="function"
  },
  
  mouse={
    args="()",
    description="get mouse pos and btn bool",
    returns="(x,y,btnl,btnm,btnr)",
    type="function"
  },
  
  wsave_numb={
    args="(id:number,value:number)",
    description="write save-state number\nid 0 -> 50",
    returns="()",
    type="function"
  }
  
  wsave_string={
    args="(id:number,value:string)",
    description="write save-state string\nid 0 -> 50",
    returns="()",
    type="function"
  },
  
  wsave_bool={
    args="(id:number,value:bool)",
    description="write save-state bool\nid 0 -> 100",
    returns="()",
    type="function"
  },
  
  rsave_numb={
    args="(id:number)",
    description="read save-state number\nid 0 -> 50",
    returns="(value:number)",
    type="function"
  },
  
  rsave_string={
    args="(id:number)",
    description="read save-state string\nid 0 -> 50",
    returns="(value:string)",
    type="function"
  },
  
  rsave_bool={
    args="(id:number)",
    description="read save-state bool\nid 0 -> 100",
    returns="(value:bool)",
    type="function"
  },
  
  run={
    args="(path:string)",
    description="run game with path = .lua/.egba file",
    returns="()",
    type="function"
  },
  
  rsave_numb_ext={
    args="(path:string,id:number)",
    description="read extern save-state\npath=.sav file\nid 0 -> 50",
    returns="(value:number)",
    type="function"
  },
  
  rsave_string_ext={
    args="(path:string,id:number)",
    description="read extern save-state\npath=.sav file\nid 0 -> 50",
    returns="(value:string)",
    type="function"
  },
  
  rsave_bool_ext={
    args="(path:string,id:number)",
    description="read extern save-state\npath=.sav file\nid 0 -> 100",
    returns="(value:bool)",
    type="function"
  },
  
  music_loaddir={
    args="(pathdir:string)",
    description="load all .wav .mp3 .ogg in dir",
    returns="()",
    type="function"
  },
  
  music_playsound={
    args="(path:string)",
    description="play extern .wav file",
    returns="()",
    type="function"
  },
  
  music_playmusic={
    args="(path:string)",
    description="play extern .mp3 .ogg file",
    returns="()",
    type="function"
  },
  
  music_pausemusic={
    args="(path:string)",
    description="pause extern .mp3 .ogg file",
    returns="()",
    type="function"
  },
  
  music_stopmusic={
    args="(path:string)",
    description="stop extern .mp3 .ogg file",
    returns="()",
    type="function"
  },
  
  deltatime={
    args="()",
    description="get time between 2 frame",
    returns="(dt:number)",
    type="function"
  }
}
 
