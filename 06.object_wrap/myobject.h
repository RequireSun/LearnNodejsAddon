#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <node_object_wrap.h>

class MyObject : public node::ObjectWrap {
public:
    static void Init (v8::Handle<v8::Object> exports);
private:
	// �� static
	double _value;

    explicit MyObject (double value = 0);
    ~MyObject();
	// static
    static void New (const v8::FunctionCallbackInfo<v8::Value>& args);
    static void GetValue (const v8::FunctionCallbackInfo<v8::Value>& args);
    static void PlusOne (const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Multiply (const v8::FunctionCallbackInfo<v8::Value>& args);
    static v8::Persistent<v8::Function> constructor;
};

#endif