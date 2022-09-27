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
    init_tovar_node(&t,&funjs::viewsc->db,"tovar");
    char* data=&tovar[0];
    t.node.string_to_param(&t.node,data,tovar.size());
    t.node.upload_param(&t.node);
    return JSValueMakeNull(ctx);
}
JSValueRef SaveAZS(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception){
        std::string azs=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
        
        char* azsstr=&azs[0];
        int sizeres=0;
        char* temp=GetValueParam(azsstr,azs.size(),"host",&sizeres);
        memcpy(funjs::viewsc->conf.host,temp,sizeres);
        free(temp);
        temp=GetValueParam(azsstr,azs.size(),"user",&sizeres);
        memcpy(funjs::viewsc->conf.name,temp,sizeres);
        free(temp);
        temp=GetValueParam(azsstr,azs.size(),"password",&sizeres);
        memcpy(funjs::viewsc->conf.password,temp,sizeres);
        free(temp);
        temp=GetValueParam(azsstr,azs.size(),"database",&sizeres);
        memcpy(funjs::viewsc->conf.database,temp,sizeres);
        free(temp);
        conf_table_setconfig(&funjs::viewsc->loc_db,&funjs::viewsc->conf);
        funjs::viewsc->CallFunctionJs("ConnectStatus", "PROCESS");
        int res=database_connect(&funjs::viewsc->db,funjs::viewsc->conf.host,funjs::viewsc->conf.name,funjs::viewsc->conf.password,funjs::viewsc->conf.database);
        if(funjs::viewsc->db.isconnect==true){
             funjs::viewsc->CallFunctionJs("ConnectStatus", "CONNECT");
             funjs::viewsc->LoadSite("/serv/service/configure");
        }else{
            funjs::viewsc->CallFunctionJs("ConnectStatus", "ERORR CONNECT");
            int id=funjs::viewsc->conf.id;
            create_conf_table(&funjs::viewsc->conf);
            funjs::viewsc->conf.id=id;
            conf_table_setconfig(&funjs::viewsc->loc_db,&funjs::viewsc->conf);
        }
return JSValueMakeNull(ctx);
                    }
JSValueRef LoginAZS(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception){
        std::string name=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
        std::string password=funjs::viewsc->ArgumentToStr(ctx,arguments[1],exception);
        if(name=="service"){
            if(password=="123"){
                if(funjs::viewsc->conf.id==-1||funjs::viewsc->db.con==NULL){
                    funjs::viewsc->LoadSite("/serv/service/configure/azs");
                }else{
                    funjs::viewsc->LoadSite("/serv/service/configure");
                }
            }else{
                funjs::viewsc->CallFunctionJs("ErrorAUTH", "ERROR PASSWORD");
            }
        }else{
            funjs::viewsc->CallFunctionJs("ErrorAUTH", "ERROR USER");
        }
        return JSValueMakeNull(ctx);
}
JSValueRef SaveTank(JSContextRef ctx, JSObjectRef function,
                    JSObjectRef thisObject, size_t argumentCount,
                    const JSValueRef arguments[], JSValueRef *exception){
             std::string tank=funjs::viewsc->ArgumentToStr(ctx,arguments[0],exception);
             tank_node_t t;
            init_tank_node(&t,&funjs::viewsc->db,"tank");
            char* data=&tank[0];
            t.node.string_to_param(&t.node,data,tank.size());
            t.node.upload_param(&t.node);
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
void funjs::LoadSiteSettingsAzs(std::vector<std::string>*data){
    std::cout<<"SettingsAZS\n";
    char buffer[400];
    int index=0;

    strcpy(&buffer[index],"host:");
    index=strlen(buffer);
     strcpy(&buffer[index],funjs::viewsc->conf.host);
    index=strlen(buffer);
     strcpy(&buffer[index],"\r");
    index=strlen(buffer);
     strcpy(&buffer[index],"user:");
    index=strlen(buffer);
    strcpy(&buffer[index],funjs::viewsc->conf.name);
    index=strlen(buffer);
    strcpy(&buffer[index],"\r");
    index=strlen(buffer);
    strcpy(&buffer[index],"password:");
    index=strlen(buffer);
    strcpy(&buffer[index],funjs::viewsc->conf.password);
    index=strlen(buffer);
    strcpy(&buffer[index],"\r");
    index=strlen(buffer);
    strcpy(&buffer[index],"database:");
    index=strlen(buffer);
    strcpy(&buffer[index],funjs::viewsc->conf.database);
    index=strlen(buffer);
    strcpy(&buffer[index],"\r");
    index=strlen(buffer);
    funjs::viewsc->CallFunctionJs("LoadSettingAzs",buffer);
    if(funjs::viewsc->db.isconnect){
        funjs::viewsc->CallFunctionJs("ConnectStatus", "CONNECT");
    }else{
        funjs::viewsc->CallFunctionJs("ConnectStatus", "ERORR CONNECT");
    }
}
void funjs::LoadSiteTypeGas(std::vector<std::string>*data){
    LoadBaseSite();
    std::cout<<"LOAD TYPE GAS\n";
    
    
    tovar_node_t tovar;
    init_tovar_node(&tovar,&viewsc->db,"tovar");
    int size=0;
    tovar_node_t* tovars=(tovar_node_t*)db_table_get_all((db_node_t*)&tovar,sizeof(tovar_node_t),&size);
     std::vector<std::string>args;
     args.resize(3);
    for(int i=0;i<size;i++){
        char* str=tovars[i].node.get_string(&tovars[i].node);
        args[0]=str;
        args[1]="1";
        args[2]="/serv/service/configure/tovar/settings";
        printf("STRING: %s\n",str);
        funjs::viewsc->CallFunctionJs("LoadConteiner",args);
        free(str);
    }
    if(viewsc->tovars!=NULL)
        free(viewsc->tovars);
    viewsc->tovars=tovars;
    
    
    
}
void funjs::LoadSiteTank(std::vector<std::string>*data){
    printf("LOAD TANK\n");
    tank_node_t tank;
    init_tank_node(&tank,&viewsc->db,"tank");
    int size=0;
    tank_node_t* tanks=(tank_node_t*)db_table_get_all((db_node_t*)&tank,sizeof(tank_node_t),&size);
    std::vector<std::string>args;
    args.resize(3);
    for(int i=0;i<size;i++){
        char* str=tanks[i].node.get_string(&tanks[i].node);
        printf("STRING: %s\n",str);
        args[0]=str;
        args[1]="0";
        args[2]="/serv/service/configure/tank/settings";
        funjs::viewsc->CallFunctionJs("LoadConteiner",args);
        free(str);
    }
    if(viewsc->tanks!=NULL)
        free(viewsc->tanks);
    viewsc->tanks=tanks;

}
void funjs::LoadSiteSettingsTank(std::vector<std::string>*data){
    std::cout<<"SettingsTank\n";
     if(data->size()!=0){
        int size=0;
        tovar_node_t tovar;
        init_tovar_node(&tovar,&viewsc->db,"tovar");
        char* ids=db_table_get_allid((db_node_t*)&tovar,sizeof(tovar_node_t),&size);

        tank_node_t tank;
        init_tank_node(&tank,&viewsc->db,"tank");
        tank.node.id=atoi((*data)[0].c_str());
        tank.node.download_param(&tank.node);
        char* str=tank.node.get_string(&tank.node);
        std::vector<std::string>arg;
        arg.resize(2);
        arg[0]=str;
        arg[1]=ids;
        free(ids);
        funjs::viewsc->CallFunctionJs("LoadSettingTank",arg);
        free(str);
    }
}

void funjs::LoadSiteLogin(std::vector<std::string>*data){
    std::cout<<"LOGIN\n";
}
void funjs::LoadSiteSettingsTovar(std::vector<std::string>*data){
    std::cout<<"SettingsTovar\n";
    if(data->size()!=0){
        tovar_node_t tovar;
        init_tovar_node(&tovar,&viewsc->db,"tovar");
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
    viewsc->RegistrFunctionJs(s,"SaveTank",SaveTank);
    viewsc->RegistrFunctionJs(s,"LoginAZS",LoginAZS);
    viewsc->RegistrFunctionJs(s,"RestartProgram", RestartProgram);
    viewsc->RegistrFunctionJs(s,"LOG", LOG);
}
void funjs::RegistrAllSites(){
    std::vector<site>* sites=viewsc->GetAllSite();
    for(int i=0;i<sites->size();i++){
        RegistrAllFunction(&(*sites)[i]);
    }
}

