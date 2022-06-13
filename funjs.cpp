#include"include/funjs.h"
VServClient* funjs::viewsc = NULL;
JSValueRef RestartProgram(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception) {
      system("./RESTART");
  return JSValueMakeNull(ctx);
}

void funjs::RegistrFunVServClient(VServClient* vs) {
    viewsc = vs;
    vs->RegistrFunctionJs("RestartProgram",RestartProgram);
}