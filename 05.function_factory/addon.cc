#include <node.h>

using namespace v8;

void MyFunction (const FunctionCallbackInfo<Value>& args) {
    // 这个函数的作用域, 不用再重复了
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    // 这个函数的作用是返回一个字符串
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world"));
}

void CreateFunction (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    // 创建函数模板, 并获取一个函数的实例
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyFunction);
    Local<Function> fn = tpl->GetFunction();
    // 为他命名
    fn->SetName(String::NewFromUtf8(isolate, "theFunction"));
    // 返回该函数
    args.GetReturnValue().Set(fn);
}

void Init(Handle<Object> exports, Handle<Object> module) {
    NODE_SET_METHOD(module, "exports", CreateFunction);
}

NODE_MODULE(addon, Init)