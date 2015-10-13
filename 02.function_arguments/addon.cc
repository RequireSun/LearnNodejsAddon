#include <node.h>

using namespace v8;

void Add (const FunctionCallbackInfo<Value>& args) {
    // 获取域
    Isolate* isolate = Isolate::GetCurrent();
    // 分配内存管理
    HandleScope scope(isolate);

    if (2 > args.Length()) {
        // 参数个数判断
        // 返回的字符串也需要包入域中进行内存管理
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return ;
    }

    if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
        // 参数类型判断
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong type of arguments")));
        return ;
    }
    // 求结果
    double value = args[0]->NumberValue() + args[1]->NumberValue();
    // 将结果包装入内存管理中
    Local<Number> num = Number::New(isolate, value);
    // 将包装好的值返回回去
    args.GetReturnValue().Set(num);
}

void Init (Handle<Object> exports) {
    // 宏: 将函数附到 exports 上
    NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon, Init)
