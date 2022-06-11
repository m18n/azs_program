const Regim = { Resize: 0, Move: 1,ResizeState:2,State:3};
function RegimeResizeUnit(obj){
    
    if(obj.Regim==undefined){
        obj.Regim=Regim.State;
    }
    console.log("OBJ REGIM "+ obj.Regim);
    if(obj.Regim==Regim.State){
        obj.Regim=Regim.ResizeState;
        obj.style.borderColor="green"; 
    }else if(obj.Regim==Regim.ResizeState){
        obj.Regim=Regim.State;
        obj.style.borderColor="grey";
    }
}
function MoveMouse(event,obj){
 
    if(obj.Regim==Regim.Resize){
        let cord = obj.getBoundingClientRect();
        let x=event.clientX-cord.left;
        let y=event.clientY-cord.top;
        console.log("OLXDW: "+obj.startsizex);
        obj.style.width=obj.startsizex+(x-obj.xstart)+"px";
        obj.style.height=obj.startsizey+(y-obj.ystart)+"px";
        console.log("EDIT SIZE X: +"+(x-obj.xstart)+" Y: "+(y-obj.ystart)+" ID: "+obj.id);
    }else if(obj.Regim==Regim.Move){
        MoveObj(event,obj);
    }
    
}
function StartMoveObj(event,obj){
    if(obj.brs==undefined){
        obj.brs=false;
    }
    let cord = obj.getBoundingClientRect();
    obj.xstartmove=event.clientX;
    obj.ystartmove=event.clientY;
    obj.locx=cord.left;
    obj.locy=cord.top;
    console.log("START MOVE X: "+obj.xstartmove+" MOVE Y: "+obj.ystartmove+" ID: "+obj.id);
    obj.Regim=Regim.Move;
    obj.style.cursor='move';
}
function StopMoveObj(event,obj){
    let x=event.clientX;
    let y=event.clientY;
    console.log("STOP MOVE X: "+x+" MOVE Y: "+y+" ID: "+obj.id);
    obj.Regim=Regim.State;
    obj.style.cursor="default";
}
function MoveObj(event,obj){
   
        let cord = obj.getBoundingClientRect();
        let x=event.clientX;
        let y=event.clientY;
        console.log("LOC X: "+obj.locx+" LOC Y: "+obj.locy);
        console.log("CLIENT X: "+x+" CLINET Y: "+y);
        obj.style.top=obj.locy+(y-obj.ystartmove)+"px";
        obj.style.left=obj.locx+(x-obj.xstartmove)+"px";
    
}
let boolmouse;
function RegimMove(event,obj){
    if(obj.Regim==Regim.State&&boolmouse==true){
       
            obj.style.borderColor="red";
            StartMoveObj(event,obj);
        
    }
}
function ResizeStartUnit(event,obj){
    boolmouse=true;
    if(obj.Regim==undefined){
        obj.Regim=Regim.State;
    }
    console.log("REGIM :"+obj.Regim);
    if(obj.Regim==Regim.ResizeState){
        obj.Regim=Regim.Resize;
        let cord = obj.getBoundingClientRect();
        obj.xstart=event.clientX-cord.left;
        obj.ystart=event.clientY-cord.top;
        obj.startsizex=obj.clientWidth;
        obj.startsizey=obj.clientHeight;
        obj.style.cursor="all-scroll";        
    }else if(obj.Regim==Regim.State){
        setTimeout(RegimMove, 3000,event,obj); 
    }else if(obj.Regim==Regim.Move){
       
        obj.style.borderColor="grey";
        StopMoveObj(event,obj);
    }
}
function ResizeStopUnit(event,obj){
    
    boolmouse=false;
    obj.style.cursor="default";
    console.log("REGIME START: "+obj.Regim);
    if(obj.Regim==Regim.Resize){
        obj.Regim=Regim.ResizeState;
    }else{
        obj.Regim=Regim.State;
        obj.style.borderColor="grey";
        StopMoveObj(event,obj);
    }
    
    console.log("REGIME END: "+obj.Regim);
}
function ItemVisible(items){
    items.parentNode.style.overflowX='visible';
    items.parentNode.style.overflowY='visible';
}
function ShowMenu(obj){
    console.log("SHOW MENU");
    obj.style.animationName='border_rev';
    obj.style.animationDuration='1s';
    obj.style.animationDirection='normal';
    obj.style.borderRadius='0px';
    let items=obj.parentNode.querySelector(".items");
    items.style.left='0px';
    items.style.animationName='menuslider';
    items.style.animationDuration='1s';
    items.style.animationDirection='normal';
    setTimeout(ItemVisible, 1000,items);
    

}
function ShowMiniMenu(obj){
    console.log("SHOW MINI MENU");
    let items=obj.parentNode.querySelector(".min_menu");
    
}
function HideMenu(obj){
    let listmark=$(obj).find(".mark");
    for(let i=0;i<listmark.length;i++){
        $(listmark[i]).addClass("disable");
    }
    console.log("HID MENU");
    
   
    //obj.style.overflowX='hidden';
    //obj.style.overflowY='hidden';
    obj=obj.querySelector(".items");
    obj.style.left='-100%';
    obj.style.animationName='menuslider_rev';
    obj.style.animationDuration='0.8s';
    obj.style.animationDirection='normal';
    let items=obj.parentNode.parentNode.querySelector("#min_menu");
    items.style.borderRadius='15px';
    items.style.animationName='border';
    items.style.animationDuration='0.8s';
    items.style.animationDirection='normal';
    $(obj).parent().css("overflow-x","hidden");
    $(obj).parent().css("overflow-y","hidden");

}
