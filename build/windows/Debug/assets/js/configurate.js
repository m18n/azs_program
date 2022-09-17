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
function LoadConteiner(str){
    // id:value|name:value|link:value|
    let unis=GetVar(str);
    let obj=$("#shab").clone();
    obj.removeClass("none");
    $(obj).find(".h").text(unis[1].value);
    obj.appendTo(".services");
   
}