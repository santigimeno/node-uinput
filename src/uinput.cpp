#include <nan.h>

#include "input-consts.h"

using namespace v8;
using namespace node;

void InputEvent (const Nan::FunctionCallbackInfo<v8::Value>& info) {
    Nan::HandleScope scope;

    int type;
    int code;
    int value;

    assert(info.Length() == 3);
    type = info[0]->Int32Value(Nan::GetCurrentContext()).FromJust();
    code = info[1]->Int32Value(Nan::GetCurrentContext()).FromJust();
    value = info[2]->Int32Value(Nan::GetCurrentContext()).FromJust();

    struct input_event ev;
    memset(&ev, 0, sizeof(ev));
    gettimeofday(&ev.time, NULL);
    ev.type = type;
    ev.code = code;
    ev.value = value;

    const char* ev_buf = reinterpret_cast<const char*>(
                             const_cast<const input_event*>(&ev));
    info.GetReturnValue().Set(
        Nan::CopyBuffer(ev_buf, sizeof(ev)).ToLocalChecked());
}

void Initialize(Local<v8::Object> input) {
    v8::Local<v8::Object> target = Nan::New<v8::Object>();

    Nan::Set(input, Nan::New("events").ToLocalChecked(), target);
    Nan::Set(input, Nan::New("input_event").ToLocalChecked(),
                Nan::GetFunction(Nan::New<FunctionTemplate>(InputEvent)).ToLocalChecked());

    for (unsigned int i = 0; i < sizeof(kInputConsts) / sizeof(kInputConsts[0]); i++) {
        Nan::Set(target, Nan::New(kInputConsts[i].name).ToLocalChecked(),
                Nan::New(kInputConsts[i].value));
    }
}

NODE_MODULE(uinput, Initialize)
