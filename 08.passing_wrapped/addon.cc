#include <node.h>
#include <node_object_wrap.h>
#include "myobject.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
	// 这个函数的作用就是直接构造一个对象返回
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	MyObject::NewInstance(args);
}
// 将两个参数解包相加然后返回
void Add(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	MyObject* obj1 = node::ObjectWrap::Unwrap<MyObject>(args[0]->ToObject());
	MyObject* obj2 = node::ObjectWrap::Unwrap<MyObject>(args[1]->ToObject());

	double sum = obj1->value() + obj2->value();
	args.GetReturnValue().Set(Number::New(isolate, sum));
}

void InitAll(Handle<Object> exports) {
	MyObject::Init();

	NODE_SET_METHOD(exports, "createObject", CreateObject);
	NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon, InitAll)