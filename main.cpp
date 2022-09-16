#include"coreazs.h"
#include"include/funjs.h"

using namespace ultralight;
#define WINDOW_WIDTH    1150
#define WINDOW_HEIGHT   700
std::vector<site>sites;
VServClient vs;
void InitSites(){
    funjs::SetView(&vs);
    site index;
    index.namesite="index.html";
    index.LoadSite=funjs::LoadSiteIndex;
    funjs::RegistrMenuFunction(&index);
    site service;
    service.namesite="services.html";
    funjs::RegistrAdminFunction(&service);
    site admin;
    admin.namesite="admin.html";
    admin.LoadSite=funjs::LoadSiteAdmin;
     funjs::RegistrMenuFunction(&admin);
    funjs::RegistrAdminFunction(&admin);
    site confnode;
    confnode.namesite="confnode.html";
    confnode.LoadSite=funjs::LoadSiteTypeGas;
    funjs::RegistrAdminFunction(&confnode);
    site configure;
    configure.namesite="configurationazs.html";
    funjs::RegistrAdminFunction(&configure);
    sites.push_back(configure);
    sites.push_back(index);
    sites.push_back(service);
    sites.push_back(admin);
    sites.push_back(confnode);
    vs.AddSites(sites);
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