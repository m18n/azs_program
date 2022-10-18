#include"coreazs.h"
#include"include/funjs.h"

using namespace ultralight;
#define WINDOW_WIDTH    1150
#define WINDOW_HEIGHT   700
VServClient vs;

void InitSites(){
    funjs::SetView(&vs);
    vs.AddSite("/login","login.html",funjs::LoadSiteLogin);
    //vs.AddSite("/service","services.html",NULL);
    vs.AddSite("/serv","serv.html",funjs::LoadSiteAdmin);
    vs.AddSite("/serv/service","services_serv.html",funjs::LoadSiteAdmin);
    vs.AddSite("/serv/service/configure","configurationazs.html",NULL);    
    vs.AddSite("/serv/service/configure/azs","settingsazs.html",funjs::LoadSiteSettingsAzs);    
    vs.AddSite("/serv/service/configure/tovar/settings","settingstovar.html",funjs::LoadSiteSettingsTovar);
    vs.AddSite("/serv/service/configure/tank/settings","settingstank.html",funjs::LoadSiteSettingsTank);
    vs.AddSite("/serv/service/configure/tovar","confnode.html",funjs::LoadSiteTypeGas);
    vs.AddSite("/serv/service/configure/tank","confnode.html",funjs::LoadSiteTank);
    vs.AddSite("/serv/service/configure/colon","confnode.html",funjs::LoadSiteTypeGas);
    vs.AddSite("/serv/service/configure/operr","confnode.html",funjs::LoadSiteTypeGas);

    funjs::RegistrAllSites();
}
int main() {
    //AZS azs;
    std::cout << "OKEY START\n";
    GetDT();
    
	
   
    
    // tovar_node_t tovar;
    // init_tovar_node(&tovar,&db);
    // tovar.node.id=10003;
    // tovar.node.download_param(&tovar.node);
    
    auto app = App::Create();
    auto window = Window::Create(app->main_monitor(),WINDOW_WIDTH,WINDOW_HEIGHT,false,
        kWindowFlags_Titled | kWindowFlags_Resizable | kWindowFlags_Maximizable);
    app->set_window(window);
    window->is_fullscreen();
    
    InitSites();
    //vs.SetAZS(&azs);
    vs.SetWin(window);
    
    vs.SetTitle("AZS\n");
    app->Run();
    
	return 0;
}