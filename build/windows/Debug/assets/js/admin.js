function OpenMenuAdmin(){
    $(".fon").removeClass("none");
    $(".admin_menu").removeClass("none");
}
function CloseMenuAdmin(){
    $(".fon").addClass("none");
    $(".admin_menu").addClass("none");
}
function Auth(){
   let pass=document.getElementById("password");
  
    AuthAdmin(pass.value);
}