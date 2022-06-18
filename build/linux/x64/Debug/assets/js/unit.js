const Regim = { Resize: 0, Move: 1,ResizeState:2,State:3};
function CreateUnit(){
    var unit={
        'id':0,
        'width':0,
        'heigth':0,
        'x':0,
        'y':0,
    }
    return unit;
}
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
        LOG("OBJ ID:"+obj.iddata);
        SaveResize(obj.iddata,obj.offsetWidth,obj.offsetHeight);
        const domRect = obj.getBoundingClientRect();
        console.log(domRect);
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
    }else if(obj.Regim==Regim.Move){
        let cord = obj.getBoundingClientRect();
        
            LOG("SAVE MOVE");
            SaveMove(obj.iddata,cord.left,cord.top);
        
        obj.Regim=Regim.State;
        obj.style.borderColor="grey";
        StopMoveObj(event,obj);
        
        
        
    }
    
    console.log("REGIME END: "+obj.Regim);
}
function CalGasolineMany(input){
    //let price=document.getElementById("price").value;
    let price=input.parentNode.parentNode.querySelector("#price");
    let liter=input.parentNode.querySelector('#liter');
    console.log("LITER VALUE: "+liter.value+" PRICE: "+price.value);
    liter.value=(input.value/price.value).toFixed(2);
}
function CalGasolineLiter(input){
    //let price=document.getElementById("price").value;
    let price=input.parentNode.parentNode.querySelector("#price");
    let liter=input.parentNode.querySelector('#liter');
    let many=input.parentNode.querySelector('#many');
    console.log("LITER VALUE: "+liter.value+" PRICE: "+price.value);
    many.value=(input.value*price.value).toFixed(2);
}

function GetVar(data){
    let variable=data.split('|');
    var arr=[];
    for(let i=0;i<variable.length;i++){
        let vare=variable[i].split(':');
        
        var v={
            'name':vare[0],
            'value':vare[1],
        };
        arr.push(v);
    }
    return arr;
}

function LoadUnit(unit){
    let df=GetVar(unit);
    let obj=$("#unit_shab").clone();
    obj.attr("id",df[0].value);
    obj.removeClass("none");
    //LOG("LEFT: "+df[3].value+" TOP: "+df[4].value);
    obj.css("width",df[1].value+"px");
    obj.css("height",df[2].value+"px");
    obj.css("left",df[3].value+"px");
    obj.css("top",df[4].value+"px");
    

    console.log("VALUE: "+df[0].value);
    obj.appendTo(".content");
    let domelem=obj.get(0);
    domelem.iddata=df[0].value;
}