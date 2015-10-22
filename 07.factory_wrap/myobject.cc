#include <node.h>
#include "myobject.h"

using namespace v8;

Persistent<Function> MyObject::constructor;

MyObject::MyObject(double value) : _value(value) {}
MyObject::~MyObject() {}

void MyObject::Init() {
	Isolate* isolate = Isolate::GetCurrent();
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);

	constructor.Reset(isolate, tpl->GetFunction());
}

void MyObject::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.IsConstructCall()) {
		double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		MyObject* obj = new MyObject(value);
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	}
	else {
		const int argc = 1;
		Local<Value> argv[argc] = { args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

void MyObject::NewInstance(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}

void MyObject::PlusOne(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
	obj->_value += 1;

	args.GetReturnValue().Set(Number::New(isolate, obj->_value));
}