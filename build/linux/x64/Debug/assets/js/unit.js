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
String.prototype.replaceAt = function(index, replacement) {
    return this.substring(0, index) + replacement + this.substring(index + replacement.length);
}
let c_number=-1;
function OnCal(th){
   
    if(c_number>2){
        c_number=1;
    }
    
    console.log("C_NUMBER: "+c_number);
    let val=$(th).text();
   
    let par=$(th).parent().parent();
    let id=par.attr('id');
    if(val=='.'){
        
       
        if(c_number!=-1){
            val="";
            c_number=-1;
            return;
        }else{
            val+="00";
        }
    }
    let cal=par.parent().children(".input_des");
    if(id ==="cl_red"){
        
        console.log("RED");
        let valmany=cal.children("#many").val();
        
        console.log("DO VALMANY: "+valmany);
        let newval;
        let index=-1;
        for(let i=0;i<valmany.length;i++){
            if(valmany[i]=="."){
                index=i;
                
                break;
            }
        }
        if(c_number==-1){
            if(index!=-1){//search
                
                newval=valmany.slice(0,index)+val;
                console.log("POSLE VALMANY: "+newval);
                if(val!=".00")
                    newval+=valmany.slice(index);
                // console.log("POSLE VALMANY: "+newval);
            }else{//none search
                newval=valmany+val;
            }
        }else{
            console.log("C_ VAL: "+val+" INDEx: "+index);
            newval=valmany;
           
            newval=newval.replaceAt(index+c_number,val);
            c_number++;
        }
        console.log("POSLE VALMANY: "+newval);
        cal.children("#many").val(newval);
        CalGasolineMany(cal.children("#many").get(0));
    }else{
       
        console.log("BLUE");
        let valliter=cal.children("#liter").val();
        console.log("DO VALLITER: "+valliter);
        let newval;
        let index=-1;
        for(let i=0;i<valliter.length;i++){
            if(valliter[i]=="."){
                index=i;
                
                break;
            }
        }
        if(c_number==-1){
            if(index!=-1){
                newval=valliter.slice(0,index)+val;
                console.log("POSLE VALMANY: "+newval);
                if(val!=".00")
                    newval+=valliter.slice(index);
            }else{
                newval=valliter+val;
            }
        }else{
            console.log("C_ VAL: "+val);
            newval=valliter;
            newval=newval.replaceAt(index+c_number,val);
            c_number++;
        }
        console.log("POSLE VALLITER: "+newval);
        cal.children("#liter").val(newval);
        CalGasolineLiter(cal.children("#liter").get(0));
    }
   if(val==".00"){
       c_number=1;
   }
   
  };
function checkBack(event){
    console.log("EVENT: "+event);
}
function OpenClavaRed(el){
    let cal=$(el).parent().parent();
    cal.children(".input_des").children("#many").addClass("focus");
    cal.children(".input_des").children("#liter").removeClass("focus");
    cal.children("#cl_blue").addClass("none");
    cal.children("#out_des").addClass("none");
    cal.children("#cl_red").removeClass("none");
    // $("#cl_blue").addClass("none");
    // $("#out_des").addClass("none");
    // $("#cl_red").removeClass("none");
}
function OpenClavaBlue(el){
    let cal=$(el).parent().parent();
    cal.children(".input_des").children("#many").removeClass("focus");
    cal.children(".input_des").children("#liter").addClass("focus");
    cal.children("#cl_red").addClass("none");
    cal.children("#out_des").addClass("none");
    cal.children("#cl_blue").removeClass("none");
   
}
function StartDes(th){
    $(th).parent().find(".clava").addClass("none");
    $(th).parent().find(".out_des").removeClass("none");
}