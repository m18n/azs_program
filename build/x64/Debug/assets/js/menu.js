$( ".item" ).click(function() {
    $(".mark").addClass("disable");
    console.log("CLICK");
    let s;
    if(s=$(this).children(".mark")){
        s.removeClass("disable");
    }
  });
