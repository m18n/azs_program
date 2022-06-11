
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