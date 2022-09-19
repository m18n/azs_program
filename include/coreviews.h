#pragma once
#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>
#include <AppCore/JSHelpers.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <iostream>
#include<vector>
using namespace std;
using namespace ultralight;
struct functionjs {
    std::string namefunction;
    JSObjectCallAsFunctionCallback fun;

};
struct site{
    void(*LoadSite)(std::vector<std::string>*data)=NULL;
    std::string namefile;
    std::string url;
    std::vector<functionjs>funs;

};
class IFunctionJS {
public:
    IFunctionJS() {

    }
    void RegistrFunctionJs(site* s,std::string namefunction, JSObjectCallAsFunctionCallback fun);
    void CallFunctionJs(std::string namefunction, std::string val);
    void CallFunctionJs(std::string namefunction, double val);
    std::string ArgumentToStr(JSContextRef ctx ,JSValueRef arg,JSValueRef* exception);
    void SetCtx(JSContextRef ctx,std::string newsite) {
        this->localsite=newsite;
        this->ctx = ctx;
        int index=-1;
        for (int i = 0; i < sites.size(); i++) {
            if(sites[i].namefile==newsite){
                
                index=i;
                break;
            }
        }
        if(index!=-1){
            for(int i=0;i<sites[index].funs.size();i++){
                RegistrFunctionJs(&sites[index],sites[index].funs[i].namefunction,sites[index].funs[i].fun);
            }
            if(sites[index].LoadSite!=NULL){
                    local=&sites[index];
                    sites[index].LoadSite(&lastargument);
            }
        }
        
    }
    std::vector<std::string>& GetArguments(){
		return lastargument;
	}
    site* GetLocal(){
        return local;
    }
    JSContextRef GetCtx() {
        return ctx;
    }
    std::vector<site>* GetAllSite(){
        return &sites;
    }
protected:
    std::string localsite;
    site* local;
    std::vector<site>sites;
    std::vector<std::string>lastargument;
private:
    JSContextRef ctx = NULL;
};
namespace details {
    std::string GetString(String8 str);
};
