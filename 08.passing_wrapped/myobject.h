#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <node_object_wrap.h>

class MyObject : public node::ObjectWrap {
public:
	// �� static
	inline double value() const { return _value; }
	// static
	static void Init();
	static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
private:
	// �� static
	double _value;

	explicit MyObject(double value = 0);
	~MyObject();
	// static
	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Persistent<v8::Function> constructor;
};

#endif