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
    
    //bool check = funjs::viewsc->GetAZS()->CheckPassword(password);
    // if (check)
    // {
    //     std::cout << "OKEY ADMIN PASS\n";
    //     funjs::viewsc->LoadSite("admin.html");
    // }
    // else
    // {
    //     funjs::viewsc->CallFunctionJs("ErrorAdminPass", "");
    //     std::cout << "ERROR ADMIN PASS\n";
    // }
    funjs::viewsc->LoadSite("/admin","");
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
    // AZS* azs=funjs::viewsc->GetAZS();
    // Dispens_Unit* disp=azs->GetUnitbyId(id);
    //disp->Resize(width,heigth);
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
    // AZS* azs=funjs::viewsc->GetAZS();
    // Dispens_Unit* disp=azs->GetUnitbyId(id);
    //disp->Move(x,y);
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
JSValueRef LoadSite(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception)
{
    std::string url=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
    std::string argument=funjs::viewsc->ArgumentToStr(ctx,arguments[1],exception);
    funjs::viewsc->LoadSite(url,argument);
return JSValueMakeNull(ctx);
}
void funjs::LoadBaseSite(){
   // RegistrAllFunction(viewsc->GetLocal());
}
void funjs::LoadSiteIndex(std::vector<std::string>*data){
    LoadBaseSite();
    std::cout<<"LOAD INDEX\n";
//    AZS* azs=funjs::viewsc->GetAZS();
//    int size=azs->GetSizeUnit();
//    for(int i=0;i<size;i++){
//        Dispens_Unit* disp=azs->GetUnit(i);
//        std::string js=disp->GetParamDispens_Unit();
//        funjs::viewsc->CallFunctionJs("LoadUnit",js);
//    }
}
void funjs::LoadSiteAdmin(std::vector<std::string>*data){
    
 std::cout<<"LOAD ADMIN\n";
   LoadSiteIndex(data);
}
void funjs::LoadSiteTypeGas(std::vector<std::string>*data){
    LoadBaseSite();
    std::cout<<"LOAD TYPE GAS\n";
    
    
    tovar_node_t tovar;
    init_tovar_node(&tovar,&viewsc->db);
    int size=0;
    tovar_node_t* tovars=(tovar_node_t*)db_table_get_all(&viewsc->tb_tovar,(db_node_t*)&tovar,sizeof(tovar_node_t),&size);
    for(int i=0;i<size;i++){
        tovars[i].node.show(&tovars[i].node);
    }
    if(viewsc->tovars!=NULL)
        free(viewsc->tovars);
    viewsc->tovars=tovars;
    
    
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
    viewsc->RegistrFunctionJs(s,"LoadSite",LoadSite);
}
void funjs::RegistrStandartFunction(site* s){
    
    viewsc->RegistrFunctionJs(s,"LOG",LOG);
}
void funjs::RegistrAllFunction(site*s){
    RegistrStandartFunction(s);
    viewsc->RegistrFunctionJs(s,"AuthAdmin", AuthAdmin);
    viewsc->RegistrFunctionJs(s,"SaveResize", SaveResize);
    viewsc->RegistrFunctionJs(s,"SaveMove", SaveMove);
    viewsc->RegistrFunctionJs(s,"LoadSite",LoadSite);
    viewsc->RegistrFunctionJs(s,"RestartProgram", RestartProgram);
}
void funjs::RegistrAllSites(){
    std::vector<site>* sites=viewsc->GetAllSite();
    for(int i=0;i<sites->size();i++){
        RegistrAllFunction(&(*sites)[i]);
    }
}