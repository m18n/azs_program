#include "include/funjs.h"
VServClient *funjs::viewsc = NULL;
JSValueRef RestartProgram(JSContextRef ctx, JSObjectRef function,
                          JSObjectRef thisObject, size_t argumentCount,
                          const JSValueRef arguments[], JSValueRef *exception)
{
    system("./RESTART");
    return JSValueMakeNull(ctx);
}
JSValueRef AuthAdmin(JSContextRef ctx, JSObjectRef function,
                     JSObjectRef thisObject, size_t argumentCount,
                     const JSValueRef arguments[], JSValueRef *exception)
{
    std::string password = funjs::viewsc->ArgumentToStr(ctx, arguments[0], exception);
    std::cout << "PASSWORD:" << password << "\n";
    
    bool check = funjs::viewsc->GetAZS()->CheckPassword(password);
    if (check)
    {
        std::cout << "OKEY ADMIN PASS\n";
        funjs::viewsc->LoadSite("admin.html");
    }
    else
    {
        funjs::viewsc->CallFunctionJs("ErrorAdminPass", "");
        std::cout << "ERROR ADMIN PASS\n";
    }
    return JSValueMakeNull(ctx);
}
JSValueRef SaveResize(JSContextRef ctx, JSObjectRef function,
                      JSObjectRef thisObject, size_t argumentCount,
                      const JSValueRef arguments[], JSValueRef *exception)
{
    std::string strwidth=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
    std::string strheigth=funjs::viewsc->ArgumentToStr(ctx,arguments[1],exception);
    int width=atoi(strwidth.c_str());
    int heigth=atoi(strheigth.c_str());

}
JSValueRef SaveMove(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception)
{

}
void funjs::LoadSiteIndex(){
   std::cout<<"LOAD INDEX\n";
}
void funjs::RegistrSiteIndex(VServClient *vs,site* s)
{
    viewsc = vs;
    s->namesite="index.html";
    s->LoadSite=funjs::LoadSiteIndex;
    vs->RegistrFunctionJs(s,"RestartProgram", RestartProgram);
    vs->RegistrFunctionJs(s,"AuthAdmin", AuthAdmin);
    vs->RegistrFunctionJs(s,"SaveResize", SaveMove);
    vs->RegistrFunctionJs(s,"SaveMove", SaveResize);
    vs->AddSite(s);
}