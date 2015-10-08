// hello.cc
#include <node.h>
#include <v8.h>

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
//  Isolate* isolate = args.GetIsolate();
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Local<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
    exports->Set(String::NewFromUtf8(isolate, "hello"),
                 FunctionTemplate::New(isolate, Method)->GetFunction());
}

NODE_MODULE(hello, init)