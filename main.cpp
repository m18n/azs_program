#include"include/funjs.h"

using namespace ultralight;
#define WINDOW_WIDTH    1150
#define WINDOW_HEIGHT   700
int main() {
    std::cout << "STARt\n";
    auto app = App::Create();
    auto window = Window::Create(app->main_monitor(),WINDOW_WIDTH,WINDOW_HEIGHT,false,
        kWindowFlags_Titled | kWindowFlags_Resizable | kWindowFlags_Maximizable);
    app->set_window(window);
    window->is_fullscreen();
    
    VServClient vs;
    vs.SetWin(window);
    funjs::RegistrFunVServClient(&vs);
    vs.SetTitle("AZS\n");
    app->Run();

	return 0;
}