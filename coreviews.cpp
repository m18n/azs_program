#include"include/coreviews.h"
void  IFunctionJS::RegistrFunctionJs(std::string namefunction, JSObjectCallAsFunctionCallback fun)
{
    if (ctx != NULL) {
        JSStringRef name = JSStringCreateWithUTF8CString(namefunction.c_str());

        // Create a garbage-collected JavaScript function that is bound to our
        // native C callback 'OnButtonClick()'.'

        JSObjectRef func = JSObjectMakeFunctionWithCallback(ctx, name,
            fun);

        // Get the global JavaScript object (aka 'window')
        JSObjectRef globalObj = JSContextGetGlobalObject(ctx);

        // Store our function in the page's global JavaScript object so that it
        // accessible from the page as 'OnButtonClick()'.
        JSObjectSetProperty(ctx, globalObj, name, func, 0, 0);

        // Release the JavaScript String we created earlier.
        JSStringRelease(name);
    }
    else {
        functionjs df;
        df.fun = fun;
        df.namefunction = namefunction;
        js.push_back(df);
    }
}
 std::string IFunctionJS::ArgumentToStr(JSContextRef ctx ,JSValueRef arg,JSValueRef* exception){
     JSStringRef arg1=JSValueToStringCopy(ctx,arg,exception);
    JSString str=arg1;
    String str2=str;
    std::string res=str2.utf8().data();
    return res;
 }
void  IFunctionJS::CallFunctionJs(std::string namefunction, std::string val)
{
    JSRetainPtr<JSStringRef> str = adopt(
        JSStringCreateWithUTF8CString(namefunction.c_str()));

    // Evaluate the string "ShowMessage"
    JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

    // Check if 'func' is actually an Object and not null
    if (JSValueIsObject(ctx, func))
    {

        // Cast 'func' to an Object, will return null if typecast failed.
        JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

        // Check if 'funcObj' is a Function and not null
        if (funcObj && JSObjectIsFunction(ctx, funcObj))
        {

            // Create a JS string from null-terminated UTF8 C-string, store it
            // in a smart pointer to release it when it goes out of scope.
            JSRetainPtr<JSStringRef> msg =
                adopt(JSStringCreateWithUTF8CString(val.c_str()));

            // Create our list of arguments (we only have one)
            const JSValueRef args[] = { JSValueMakeString(ctx, msg.get()) };

            // Count the number of arguments in the array.
            size_t num_args = sizeof(args) / sizeof(JSValueRef*);

            // Create a place to store an exception, if any
            JSValueRef exception = 0;

            // Call the ShowMessage() function with our list of arguments.
            JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0,
                num_args, args,
                &exception);

            if (exception)
            {
                // Handle any exceptions thrown from function here.
            }

            if (result)
            {
                // Handle result (if any) here.
            }
        }
    }
}
void  IFunctionJS::CallFunctionJs(std::string namefunction, double val)
{
    JSRetainPtr<JSStringRef> str = adopt(
        JSStringCreateWithUTF8CString(namefunction.c_str()));

    // Evaluate the string "ShowMessage"
    JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

    // Check if 'func' is actually an Object and not null
    if (JSValueIsObject(ctx, func))
    {

        // Cast 'func' to an Object, will return null if typecast failed.
        JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

        // Check if 'funcObj' is a Function and not null
        if (funcObj && JSObjectIsFunction(ctx, funcObj))
        {

            // Create a JS string from null-terminated UTF8 C-string, store it
            // in a smart pointer to release it when it goes out of scope.


            // Create our list of arguments (we only have one)
            const JSValueRef args[] = { JSValueMakeNumber(ctx,val) };

            // Count the number of arguments in the array.
            size_t num_args = sizeof(args) / sizeof(JSValueRef*);

            // Create a place to store an exception, if any
            JSValueRef exception = 0;

            // Call the ShowMessage() function with our list of arguments.
            JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0,
                num_args, args,
                &exception);

            if (exception)
            {
                // Handle any exceptions thrown from function here.
            }

            if (result)
            {
                // Handle result (if any) here.
            }
        }
    }
}
std::string details::GetString(String8 str) {
    char* w = str.data();
    w[str.length() - 1] = '\0';
    std::string string(&w[1]);


    return std::move(string);
}