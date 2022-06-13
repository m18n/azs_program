#pragma once
#include"views.h"
JSValueRef RestartProgram(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception);
namespace funjs {
    extern VServClient* viewsc;
    void RegistrFunVServClient(VServClient* vs);
}
