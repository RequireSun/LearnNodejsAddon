#include <node.h>
#include "myobject.h"

using namespace v8;

Persistent<Function> MyObject::constructor;

MyObject::MyObject(double value) : _value(value) {}
MyObject::~MyObject(){}

void MyObject::Init() {
	// 做的只是把 constructor 构造函数替换成了 New
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor.Reset(isolate, tpl->GetFunction());
}

void MyObject::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.IsConstructCall()) {
		// 采用 new 的时候
		// 构造新对象并打包, 最后返回给用户
		double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		MyObject* obj = new MyObject(value);
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	} else {
		// 如果是普通调用
		// 使用第一个参数构造一个对象返回
		const int argc = 1;
		Local<Value> argv[argc] = { args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

void MyObject::NewInstance(const FunctionCallbackInfo<Value>& args) {
	// 使用第一个参数构造一个对象返回回去
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}