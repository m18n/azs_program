#include"include/views.h"
VServClient::VServClient() {
	create_local_database(&loc_db);
	conf=conf_table_getconfig(&loc_db);
	printf("CONFIGURE: %s %s %s\n",conf.host,conf.name,conf.password);
	create_database(&db);
	database_connect(&db,conf.host,conf.name,conf.password);
	 
	init_db_table(&tb_tovar,&db,"tovar");
	tovars=NULL;
}
VServClient::~VServClient() {
	if(tovars!=NULL){
		free(tovars);
		tovars=NULL;
	}
	destroy_database(&db);
	destroy_local_database(&loc_db);
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
void VServClient::LoadSite(std::string url){
	this->lastargument.clear();
	int index=-1;
	for(int i=0;i<sites.size();i++){
		if(sites[i].url==url){
			index=i;
			break;
		}
	}
	if(index!=-1)
		ov->view()->LoadURL(("file:///"+sites[index].namefile).c_str());
}
void VServClient::LoadSite(std::string url,std::vector<std::string>arg){
	this->lastargument=std::move(arg);
	int index=-1;
	for(int i=0;i<sites.size();i++){
		if(sites[i].url==url){
			index=i;
			break;
		}
	}
	if(index!=-1)
		ov->view()->LoadURL(("file:///"+sites[index].namefile).c_str());
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