#pragma once
#include"views.h"

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
  JSValueRef LoadSite(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception);
JSValueRef SaveTovar(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception);
JSValueRef SaveAZS(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception);
JSValueRef LoginAZS(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception);
namespace funjs {
    extern VServClient* viewsc;
    void SetView(VServClient* view);
    void RegistrStandartFunction(site* s);
    void RegistrAdminFunction(site* s);
    void RegistrMenuFunction(site* s);
    void RegistrAllFunction(site*s);
    void RegistrAllSites();
    void LoadBaseSite();
    void LoadSiteIndex(std::vector<std::string>*data);
    void LoadSiteAdmin(std::vector<std::string>*data);
    void LoadSiteTypeGas(std::vector<std::string>*data);
    void LoadSiteSettingsTovar(std::vector<std::string>*data);
    void LoadSiteSettingsAzs(std::vector<std::string>*data);
    void LoadSiteLogin(std::vector<std::string>*data);
    void LoadSiteTank(std::vector<std::string>*data);
}
