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
class IFunctionJS {
public:
    IFunctionJS() {

    }
    void RegistrFunctionJs(std::string namefunction, JSObjectCallAsFunctionCallback fun);
    void CallFunctionJs(std::string namefunction, std::string val);
    void CallFunctionJs(std::string namefunction, double val);
    std::string ArgumentToStr(JSContextRef ctx ,JSValueRef arg,JSValueRef* exception);
    void SetCtx(JSContextRef ctx) {
        this->ctx = ctx;
        for (int i = 0; i < js.size(); i++) {
            RegistrFunctionJs(js[i].namefunction, js[i].fun);
        }
    }
    JSContextRef GetCtx() {
        return ctx;
    }
protected:
    std::vector<functionjs>js;
private:
    JSContextRef ctx = NULL;
};
namespace details {
    std::string GetString(String8 str);
};
