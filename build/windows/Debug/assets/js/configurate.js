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
function LoadUnits(str){
    // id:name:link|
    
}