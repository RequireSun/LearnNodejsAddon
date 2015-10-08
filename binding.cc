#include <node.h>
#include <v8.h>

//using namespace v8;

v8::Handle<v8::Value> Method(const v8::Arguments& args) {
  v8::HandleScope scope;
  return scope.Close(v8::String::New("world"));
}

void init(v8::Handle<v8::Object> target) {
  NODE_SET_METHOD(target, "hello", Method);
}

NODE_MODULE(binding, init);