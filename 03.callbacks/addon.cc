#include <node.h>

using namespace v8;

void RunCallback (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    // 获取放在第一个参数上的回调函数
    Local<Function> cb = Local<Function>::Cast(args[0]);
    // 构造传入回调函数的参数
    const unsigned argc = 1;
    Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "Hello world") };
    // 调用回调函数
    cb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}

void Init (Handle<Object> exports, Handle<Object> module) {
    // 直接覆盖掉 exports
    NODE_SET_METHOD(module, "exports", RunCallback);
}

NODE_MODULE(addon, Init);