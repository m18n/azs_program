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
    void(*LoadSite)()=NULL;
    std::string namesite;
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
            if(sites[i]->namesite==newsite){
                
                index=i;
                break;
            }
        }
        if(index!=-1){
            for(int i=0;i<sites[index]->funs.size();i++){
                RegistrFunctionJs(sites[index],sites[index]->funs[i].namefunction,sites[index]->funs[i].fun);
            }
            if(sites[index]->LoadSite!=NULL)
                    sites[index]->LoadSite();
        }
        
    }
    JSContextRef GetCtx() {
        return ctx;
    }
protected:
    std::string localsite;
    std::vector<site*>sites;
private:
    JSContextRef ctx = NULL;
};
namespace details {
    std::string GetString(String8 str);
};
