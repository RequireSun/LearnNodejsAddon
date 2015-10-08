#ifndef STDSTRING_H
#define STDSTRING_H

#include <node.h>
#include <v8.h>
#include <string>

class STDStringWrapper : public node::ObjectWrap {
private:
    std::string* _s;

    explicit STDStringWrapper(std::string s = "");
    ~STDStringWrapper();

    static v8::Persistent constructor;
    static v8::Handle<v8::Value> New (const v8::Arguments& args);
    static v8::Handle<v8::Value> add (const v8::Arguments& args);
    static v8::Handle<v8::Value> toString (const v8::Arguments& args);
public:
    static void Init (v8::Handle exports);
};

#endif