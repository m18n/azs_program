#pragma once
#include"coreazs.h"
#include"coreviews.h" 

class VServClient :public WindowListener, public ViewListener, public LoadListener, public IFunctionJS {
public:

	VServClient();
	void SetWin(RefPtr<Window> win);
	void OnDOMReady(View* caller,
		uint64_t frame_id,
		bool is_main_frame,
		const String& url) override;
	virtual void OnClose() override;
	virtual void OnResize(uint32_t width, uint32_t height) override;
	virtual void OnChangeCursor(ultralight::View* caller,
		Cursor cursor);
	void LoadSite(std::string name);
	void SetTitle(std::string title) {
		this->title = title;
		win->SetTitle(title.c_str());
	}
	void AddSite(site* s){
		this->sites.push_back(s);
	}
	void AddSites(std::vector<site>&v){
		this->sites.resize(v.size());
		for(int i=0;i<sites.size();i++){
			sites[i]=&v[i];
		}
	}
	void SetAZS(AZS* azs){
		this->azs=azs;
	}
	AZS* GetAZS(){
		return azs;
	}
	~VServClient();

private:
	std::string title;
	RefPtr<Window> win;
	RefPtr<Overlay> ov;
	AZS* azs;
};