#include "myobject.h"

using namespace v8;

Persistent<Function> MyObject::constructor;

MyObject::MyObject (double value) : _value(value) {}

MyObject::~MyObject () {}

void MyObject::Init (Handle<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	// ���� New �����½�һ�����ģ��
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	// ����Ϊ MyObject
    tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));
	// �����ֶ���
    tpl->InstanceTemplate()->SetInternalFieldCount(3);
	// ����ԭ�ͷ���
    NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getValue", GetValue);
	NODE_SET_PROTOTYPE_METHOD(tpl, "multiply", Multiply);
	// �ٰѹ�����Ҳ������
    constructor.Reset(isolate, tpl->GetFunction());
	// ���õ����� MyObject Ϊ���캯��
    exports->Set(String::NewFromUtf8(isolate, "MyObject"), tpl->GetFunction());
}

void MyObject::New (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
	
    if (args.IsConstructCall()) {
		// ����� new ����
		// ȡ����ֵ
        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		// �½�һ����ǰ����
        MyObject* obj = new MyObject(value);
		// ����ǰ����������������(ʵ�ڲ�֪����ô˵��)
        obj->Wrap(args.This());
		// ���ش����Ķ���
        args.GetReturnValue().Set(args.This());
    } else {
		// ���� new ����
		// ������������
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
		// ��������ʵ��
        Local<Function> cons = Local<Function>::New(isolate, constructor);
		// ������ֵ����Ϊһ����������������ʵ�� (ͨ�� c++ ���ù��캯��)
        args.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}

void MyObject::GetValue (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
	// ���
    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
	// ����ֵ
    args.GetReturnValue().Set(Number::New(isolate, obj->_value));
}

void MyObject::PlusOne (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
	// ��ȡ��ʵ���� c++ ���Ͷ���
    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
    obj->_value += 1;
	// ��ֵ����
    args.GetReturnValue().Set(Number::New(isolate, obj->_value));
}

void MyObject::Multiply(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	// ���
	MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
	// ��ȡ����
	double multiple = args[0]->IsUndefined() ? 1 : args[0]->NumberValue();
	// �������
	const int argc = 1;
	Local<Value> argv[argc] = { Number::New(isolate, obj->_value * multiple) };
	// ֱ�ӹ����µĶ��󷵻� (���� c++ ���ͷŶ���ô?)
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	args.GetReturnValue().Set(cons->NewInstance(argc, argv));
}