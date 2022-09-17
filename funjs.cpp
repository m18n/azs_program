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
    funjs::viewsc->LoadSite("/admin");
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
    std::vector<std::string>arrarg;
    arrarg.resize(argumentCount-1);
    for(int i=1;i<argumentCount;i++){
        arrarg[i-1]=funjs::viewsc->ArgumentToStr(ctx,arguments[i],exception);
    }
    
    funjs::viewsc->LoadSite(url,std::move(arrarg));
    return JSValueMakeNull(ctx);
}
JSValueRef SaveTovar(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception){
    std::string tovar=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
    tovar_node_t t;
    init_tovar_node(&t,&funjs::viewsc->db);
    char* data=&tovar[0];
    t.node.string_to_param(&t.node,data,tovar.size());
    t.node.upload_param(&t.node);
    return JSValueMakeNull(ctx);
}
JSValueRef SaveAZS(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception){
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
        char* str=tovars[i].node.get_string(&tovars[i].node);
        printf("STRING: %s\n",str);
        funjs::viewsc->CallFunctionJs("LoadConteiner",str);
        free(str);
    }
    if(viewsc->tovars!=NULL)
        free(viewsc->tovars);
    viewsc->tovars=tovars;
    
    
    
}
void funjs::LoadSiteSettingsAzs(std::vector<std::string>*data){
    std::cout<<"SettingsAZS\n";
}
void funjs::LoadSiteSettingsTovar(std::vector<std::string>*data){
    std::cout<<"SettingsTovar\n";
    if(data->size()!=0){
        tovar_node_t tovar;
        init_tovar_node(&tovar,&viewsc->db);
        tovar.node.id=atoi((*data)[0].c_str());
        tovar.node.download_param(&tovar.node);
        char* str=tovar.node.get_string(&tovar.node);
        funjs::viewsc->CallFunctionJs("LoadSettingTovar",str);
        free(str);
    }
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
    viewsc->RegistrFunctionJs(s,"SaveTovar",SaveTovar);
    viewsc->RegistrFunctionJs(s,"SaveAZS",SaveAZS);
    viewsc->RegistrFunctionJs(s,"RestartProgram", RestartProgram);
}
void funjs::RegistrAllSites(){
    std::vector<site>* sites=viewsc->GetAllSite();
    for(int i=0;i<sites->size();i++){
        RegistrAllFunction(&(*sites)[i]);
    }
}