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
    site service;
    service.namesite="services.html";
    site admin;
    admin.namesite="admin.html";
    admin.LoadSite=funjs::LoadSiteAdmin;
    funjs::RegistrAdminFunction(&service);
    funjs::RegistrMenuFunction(&index);
    funjs::RegistrMenuFunction(&admin);
    funjs::RegistrAdminFunction(&admin);
    sites.push_back(index);
    sites.push_back(service);
    sites.push_back(admin);
    vs.AddSites(sites);
}
int main() {
    //AZS azs;
    std::cout << "STARt\n";
    try {
    DataBase db;
    db.Connection("tcp://192.168.0.103:3307", "user", "0958532122m","azs");
    Tovar tv(&db,1);
    } catch (sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
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
    vs.~VServClient();
	return 0;
}