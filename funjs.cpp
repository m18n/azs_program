#include "include/funjs.h"
VServClient *funjs::viewsc = NULL;
JSValueRef RestartProgram(JSContextRef ctx, JSObjectRef function,
                          JSObjectRef thisObject, size_t argumentCount,
                          const JSValueRef arguments[], JSValueRef *exception)
{
   #ifdef _WIN32
    system("RESTART.exe");
#else
    system("./RESTART");
#endif
   
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
    std::string strid=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
    std::string strwidth=funjs::viewsc->ArgumentToStr(ctx,arguments[1],exception);
    std::string strheigth=funjs::viewsc->ArgumentToStr(ctx,arguments[2],exception);
    int id=atoi(strid.c_str());
    int width=atoi(strwidth.c_str());
    int heigth=atoi(strheigth.c_str());
    AZS* azs=funjs::viewsc->GetAZS();
    Dispens_Unit* disp=azs->GetUnitbyId(id);
    disp->Resize(width,heigth);
    std::cout<<"ID:"<<id<<"WIDTH: "<<width<<" HEIGTH: "<<heigth<<"\n";
    return JSValueMakeNull(ctx);
}
JSValueRef SaveMove(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception)
{
    std::string strid=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
    std::string strx=funjs::viewsc->ArgumentToStr(ctx,arguments[1],exception);
    std::string stry=funjs::viewsc->ArgumentToStr(ctx,arguments[2],exception);
    int id=atoi(strid.c_str());
    int x=atoi(strx.c_str());
    int y=atoi(stry.c_str());
    AZS* azs=funjs::viewsc->GetAZS();
    Dispens_Unit* disp=azs->GetUnitbyId(id);
    disp->Move(x,y);
    std::cout<<"ID:"<<id<<"X: "<<x<<" Y: "<<y<<"\n";
    return JSValueMakeNull(ctx);
}
   JSValueRef LOG(JSContextRef ctx, JSObjectRef function,
  JSObjectRef thisObject, size_t argumentCount, 
  const JSValueRef arguments[], JSValueRef* exception){
      std::string mess=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
      std::cout<<"MESSAGE: "<<mess<<"\n";
      return JSValueMakeNull(ctx);
  }
void funjs::LoadSiteIndex(){
   std::cout<<"LOAD INDEX\n";
   AZS* azs=funjs::viewsc->GetAZS();
   int size=azs->GetSizeUnit();
   for(int i=0;i<size;i++){
       Dispens_Unit* disp=azs->GetUnit(i);
       std::string js=disp->GetParamDispens_Unit();
       funjs::viewsc->CallFunctionJs("LoadUnit",js);
   }
}
void funjs::LoadSiteAdmin(){
 std::cout<<"LOAD ADMIN\n";
   LoadSiteIndex();
}
 void funjs::SetView(VServClient* view){
     viewsc=view;
 }
void funjs::RegistrMenuFunction(site* s){
    RegistrStandartFunction(s);
    viewsc->RegistrFunctionJs(s,"RestartProgram", RestartProgram);
    
}
void funjs::RegistrAdminFunction(site* s)
{
    RegistrStandartFunction(s);
    viewsc->RegistrFunctionJs(s,"AuthAdmin", AuthAdmin);
    viewsc->RegistrFunctionJs(s,"SaveResize", SaveResize);
    viewsc->RegistrFunctionJs(s,"SaveMove", SaveMove);
}
void funjs::RegistrStandartFunction(site* s){
    
    viewsc->RegistrFunctionJs(s,"LOG",LOG);
}