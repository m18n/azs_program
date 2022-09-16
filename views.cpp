#include"include/views.h"
VServClient::VServClient() {
	create_database(&db);
	database_connect(&db);
	init_db_table(&tb_tovar,&db,"tovar");
	tovars=NULL;
}
VServClient::~VServClient() {
	if(tovars!=NULL){
		free(tovars);
		tovars=NULL;
	}
	destroy_database(&db);
	std::cout<<"END VSERV\n";
}
void VServClient::SetWin(RefPtr<Window> win) {
	this->win = win;
	win->SetTitle(title.c_str());
	ov = Overlay::Create(*win, win->width(), win->height(), 0, 0);
	ov->view()->LoadURL("file:///index.html");
	ov->view()->set_view_listener(this);
	ov->view()->set_load_listener(this);
   

	win->set_listener(this);
}
void VServClient::LoadSite(std::string name,std::string argument){
	this->argument=argument;
	ov->view()->LoadURL(("file:///"+name).c_str());
}
void VServClient::OnDOMReady(View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const String& url)
{

	Ref<JSContext> context = caller->LockJSContext();
	std::string strurl=url.utf8().data()+8;
	SetCtx(context.get(),strurl);
	std::cout<<"URL: "<<url.utf8().data()<<"\n";
}
void VServClient::OnClose() {}
void VServClient::OnResize(uint32_t width, uint32_t height) {
	ov->Resize(width, height);
}

void VServClient::OnChangeCursor(ultralight::View* caller,
	Cursor cursor) {
	win->SetCursor(cursor);
}