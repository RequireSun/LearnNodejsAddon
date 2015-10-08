#include "stdstring.h"

v8::Persistent STDStringWrapper::constructor;

STDStringWrapper::STDStringWrapper (std::string s) {
    this->_s = new std::string(s);
}

STDStringWrapper::~STDStringWrapper () {
    delete this->_s;
}

v8::Handle<v8::Value> STDStringWrapper::New(const v8::Arguments args) {
    v8::HandleScope scope;
    // 如果是构造函数
    if (args.IsConstructCall()) {
        // 将参数转化为字符串
        v8::String::Utf8Value str(args[0]->ToString());
        std::string s(*str);
        STDStringWrapper* obj = new STDStringWrapper(s);
        // 将现在的对象附到 this 上?
        obj->Wrap(args.This());
        return args.This();
    } else {
        const int argc = 1;
        v8::Local argv[argc] = { args[0] };
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

v8::Handle<v8::Value> STDStringWrapper::add(const v8::Arguments args) {
    v8::HandleScope scope;

    v8::String::Utf8Value str(args[0]->ToString());
    std::string s(*str);
    STDStringWrapper* obj = ObjectWrap::Unwrap(args.This());
    obj->_s->append(s);
    return scope.Close(v8::String::New(obj->_s->c_str()));
}

v8::Handle<v8::Value> STDStringWrapper::toString(const v8::Arguments args) {
    v8::HandleScope scope;
    STDStringWrapper* obj = ObjectWrap::Unwrap(args.This());
    return scope.Close(v8::String::New(obj->_s->c_str()));
}

// 初始化函数
void STDStringWrapper::Init (v8::Handle exports) {
    v8::Local tpl = v8::FunctionTemplate::New(this->New);
    // 构造函数命名
    tpl->SetClassName(v8::String::NewSymbol("STDString"));
    // 设定类的实例包含的字段数
    tpl->InstanceTemplate()->SetInternalFieldCount(2);
    // 将两个函数添加到原型上
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("add"), v8::FunctionTemplate::New(this->add)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("toString"), v8::FunctionTemplate::New(this->toString)->GetFunction());
    // 将构造函数设置为刚才构造出来的函数
    constructor = v8::Persistent::New(tpl->GetFunction());
    // 将构造函数设置为导出项
    exports->Set(v8::String::NewSymbol("STDString"), constructor);
}