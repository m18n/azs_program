#include"coreazs.h"
#include"include/funjs.h"

using namespace ultralight;
#define WINDOW_WIDTH    1150
#define WINDOW_HEIGHT   700
VServClient vs;

void InitSites(){
    funjs::SetView(&vs);
    vs.AddSite("/index","index.html",funjs::LoadSiteIndex);
    vs.AddSite("/service","services.html",NULL);
    vs.AddSite("/admin","admin.html",funjs::LoadSiteAdmin);
    vs.AddSite("/admin/service","servicesadmin.html",funjs::LoadSiteAdmin);
    vs.AddSite("/admin/service/configure","configurationazs.html",NULL);    
    vs.AddSite("/admin/service/configure/azs","settingsazs.html",funjs::LoadSiteSettingsAzs);    
    vs.AddSite("/admin/service/configure/tank","confnode.html",funjs::LoadSiteTypeGas);
    vs.AddSite("/admin/service/configure/tank/settings","settingstovar.html",funjs::LoadSiteSettingsTovar);
    vs.AddSite("/admin/service/configure/tovar","confnode.html",funjs::LoadSiteTypeGas);
    vs.AddSite("/admin/service/configure/colon","confnode.html",funjs::LoadSiteTypeGas);
    vs.AddSite("/admin/service/configure/oper","confnode.html",funjs::LoadSiteTypeGas);

    funjs::RegistrAllSites();
}
int main() {
    //AZS azs;
    std::cout << "STARt\n";
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