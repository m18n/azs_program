function Colors(){
    console.log("COLOR");
    $(".coisecolor").removeClass("none");
}
function SelectColors(th){
    console.log("SELECT");
    $(".coisecolor").addClass("none");
}
$(document).ready(function() {

    $('#color').change(function() {
       var current = $('#color').val();
       
       if (current != 'null') {
           $('#color').css('background-color',current);
       } else {
           $('#color').css('background-color','none');
       }
    });
    
 });