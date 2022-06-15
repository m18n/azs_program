#include"include/funjs.h"
VServClient* funjs::viewsc = NULL;
JSValueRef RestartProgram(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception) {
      system("./RESTART");
  return JSValueMakeNull(ctx);
}
JSValueRef AuthAdmin(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception){
    std::string password=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
    std::cout<<"PASSWORD:"<<password<<"\n";
    bool check=CheckPassword(password);
    if(check){
        std::cout<<"OKEY ADMIN PASS\n";
    }else{
        std::cout<<"ERROR ADMIN PASS\n";
    }
    return JSValueMakeNull(ctx);
}
void funjs::RegistrFunVServClient(VServClient* vs) {
    viewsc = vs;
    vs->RegistrFunctionJs("RestartProgram",RestartProgram);
    vs->RegistrFunctionJs("AuthAdmin",AuthAdmin);
}