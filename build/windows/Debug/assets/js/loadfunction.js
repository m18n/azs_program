function GetVar(data){
    let variable=data.split('\r');
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
function LoadConteiner(str,indexlable,link){
    // id:value|name:value|link:value|
    let unis=GetVar(str);
    let obj=$("#shab").clone();
    obj.removeClass("none");
    
    $(obj).find(".h").text(unis[parseInt(indexlable)].value);
    obj.appendTo(".services");
    obj.attr('onClick', 'LoadSite("'+link+'","'+unis[0].value+'");');
    
    
}
function LoadSettingTovar(str){
    let tovar=GetVar(str);
    let sett=$(".settings_tovar");
    sett.attr("id",tovar[0].value);
    sett.find("#name").val(tovar[1].value);
    sett.find("#name_p").val(tovar[2].value);
    sett.find("#name_p_f").val(tovar[3].value);
    sett.find("#nd_code").val(tovar[4].value);
    sett.find("#wog_code").val(tovar[5].value);

}
function LoadSettingTank(str,ids){
    let arr=ids.split('\r');
    

    let tovar=GetVar(str);
    let sett=$(".settings_tank");
    sett.attr("id",tovar[0].value);
    sett.find("#nn").val(tovar[1].value);
    for(let i=0;i<arr.length-1;i++){
        if(arr[i]===tovar[2].value){
            LOG("I");
            sett.find("#id_tovar").append('<option selected>'+arr[i]+'</option>');
        }else{
            sett.find("#id_tovar").append('<option>'+arr[i]+'</option>');
        }
    }
    
    sett.find("#color").val(tovar[3].value);

}
function LoadSettingAzs(str){
    let azs=GetVar(str);
    let sett=$("#sett_azs");
    sett.find("#host").val(azs[0].value);
    sett.find("#user").val(azs[1].value);
    sett.find("#pass").val(azs[2].value);
    sett.find("#database").val(azs[3].value);
}