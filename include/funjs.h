#pragma once
#include"views.h"
#include<coreazs.h>
JSValueRef RestartProgram(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception);
JSValueRef AuthAdmin(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception);
  JSValueRef SaveResize(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception);
  JSValueRef SaveMove(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception);
   JSValueRef LOG(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception);
namespace funjs {
    extern VServClient* viewsc;
    void SetView(VServClient* view);
    void RegistrStandartFunction(site* s);
    void RegistrAdminFunction(site* s);
    void RegistrMenuFunction(site* s);
    void LoadSiteIndex();
    void LoadSiteAdmin();

}
