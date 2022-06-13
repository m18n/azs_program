#include"include/views.h"
VServClient::VServClient() {

}
VServClient::~VServClient() {

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
void VServClient::OnDOMReady(View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const String& url)
{
	Ref<JSContext> context = caller->LockJSContext();
	SetCtx(context.get());
}
void VServClient::OnClose() {}
void VServClient::OnResize(uint32_t width, uint32_t height) {
	ov->Resize(width, height);
}

void VServClient::OnChangeCursor(ultralight::View* caller,
	Cursor cursor) {
	win->SetCursor(cursor);
}