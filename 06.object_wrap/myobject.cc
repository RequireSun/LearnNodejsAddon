#include "myobject.h"

using namespace v8;

Persistent<Function> MyObject::constructor;

MyObject::MyObject (double value) : _value(value) {}

MyObject::~MyObject () {}

void MyObject::Init (Handle<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	// 根据 New 函数新建一个类的模板
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	// 命名为 MyObject
    tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));
	// 设置字段数
    tpl->InstanceTemplate()->SetInternalFieldCount(3);
	// 设置原型方法
    NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getValue", GetValue);
	NODE_SET_PROTOTYPE_METHOD(tpl, "multiply", Multiply);
	// 再把构造器也给改了
    constructor.Reset(isolate, tpl->GetFunction());
	// 设置导出项 MyObject 为构造函数
    exports->Set(String::NewFromUtf8(isolate, "MyObject"), tpl->GetFunction());
}

void MyObject::New (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
	
    if (args.IsConstructCall()) {
		// 如果是 new 调用
		// 取参数值
        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		// 新建一个当前对象
        MyObject* obj = new MyObject(value);
		// 将当前对象打包入上下文中(实在不知道怎么说了)
        obj->Wrap(args.This());
		// 返回打包后的对象
        args.GetReturnValue().Set(args.This());
    } else {
		// 不是 new 调用
		// 构建参数数组
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
		// 创建函数实例
        Local<Function> cons = Local<Function>::New(isolate, constructor);
		// 将返回值设置为一个构建函数构建的实例 (通过 c++ 调用构造函数)
        args.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}

void MyObject::GetValue (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
	// 拆包
    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
	// 返回值
    args.GetReturnValue().Set(Number::New(isolate, obj->_value));
}

void MyObject::PlusOne (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
	// 获取到实例的 c++ 类型对象
    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
    obj->_value += 1;
	// 将值返回
    args.GetReturnValue().Set(Number::New(isolate, obj->_value));
}

void MyObject::Multiply(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	// 拆包
	MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
	// 获取参数
	double multiple = args[0]->IsUndefined() ? 1 : args[0]->NumberValue();
	// 构造参数
	const int argc = 1;
	Local<Value> argv[argc] = { Number::New(isolate, obj->_value * multiple) };
	// 直接构建新的对象返回 (能在 c++ 里释放对象么?)
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	args.GetReturnValue().Set(cons->NewInstance(argc, argv));
}