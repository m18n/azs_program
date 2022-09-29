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
function decimalToHexString(number)
{
  if (number < 0)
  {
    number = 0xFFFFFFFF + number + 1;
  }

  return number.toString(16).toUpperCase();
}
function LoadSettingTank(str){
    let tovar=GetVar(str);
    let sett=$(".settings_tank");
    sett.attr("id",tovar[0].value);
    sett.find("#nn").val(tovar[1].value);
    
    for(let i=1;i<arguments.length;i++){
        let val=GetVar(arguments[i]);
        if(val[0].value==tovar[2].value){
            sett.find("#id_tovar").append('<option value="'+val[0].value+'" selected>'+val[1].value+'</option>');
        }else{
            sett.find("#id_tovar").append('<option value="'+val[0].value+'">'+val[1].value+'</option>');
        }
    }
    let s=parseInt(tovar[3].value).toString(16);
    let size=6-s.length;
    let n="";
    for(let i=0;i<size;i++){
        n+="0";
    }
    s=n+s;
    LOG("PARSE "+s);
    let txt=$('#color option[value="#'+s+'"]').text()
    LOG("FIND");
    LOG("TEXT: "+txt);
    if(txt!=""){
        $("#color").css('background-color',"#"+s);
        $('#color option[value="#'+s+'"]').prop('selected', true);
    }
}
function LoadSettingAzs(str){
    let azs=GetVar(str);
    let sett=$("#sett_azs");
    sett.find("#host").val(azs[0].value);
    sett.find("#user").val(azs[1].value);
    sett.find("#pass").val(azs[2].value);
    sett.find("#database").val(azs[3].value);
}