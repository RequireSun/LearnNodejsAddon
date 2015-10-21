#include <node.h>

using namespace v8;

void MyFunction (const FunctionCallbackInfo<Value>& args) {
    // ���������������, �������ظ���
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    // ��������������Ƿ���һ���ַ���
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world"));
}

void CreateFunction (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    // ��������ģ��, ����ȡһ��������ʵ��
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyFunction);
    Local<Function> fn = tpl->GetFunction();
    // Ϊ������
    fn->SetName(String::NewFromUtf8(isolate, "theFunction"));
    // ���ظú���
    args.GetReturnValue().Set(fn);
}

void Init(Handle<Object> exports, Handle<Object> module) {
    NODE_SET_METHOD(module, "exports", CreateFunction);
}

NODE_MODULE(addon, Init)