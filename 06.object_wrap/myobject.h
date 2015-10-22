#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <node_object_wrap.h>
// 要继承 ObjectWrap 才能打包自身对象的
class MyObject : public node::ObjectWrap {
public:
    static void Init (v8::Handle<v8::Object> exports);
private:
	// 非 static
	double _value;

    explicit MyObject (double value = 0);
    ~MyObject();
	// static
    static v8::Persistent<v8::Function> constructor;

    static void New (const v8::FunctionCallbackInfo<v8::Value>& args);
    static void GetValue (const v8::FunctionCallbackInfo<v8::Value>& args);
    static void PlusOne (const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Multiply (const v8::FunctionCallbackInfo<v8::Value>& args);
};

#endif