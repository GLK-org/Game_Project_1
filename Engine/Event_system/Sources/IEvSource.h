#pragma once
#include "Level_controls.h"

[event_source(native)]
class ENGINE_API CSource {
public:
    __event virtual void OnTrigger1(Obj* ref, int& points);
    __event virtual void OnTrigger2(bool & trig);
};

[event_receiver(native)]
class ENGINE_API CReceiver {
public:
    void MyHandler1(Obj* ref, int& nValue) {
        printf_s("MyHandler1 was called with value %d.\n", nValue);
    }

    void MyHandler2(bool& trig) {
        trig = true;
    }

    void hookEvent(CSource* pSource) {
        __hook(&CSource::OnTrigger1, pSource, &CReceiver::MyHandler1);
        __hook(&CSource::OnTrigger2, pSource, &CReceiver::MyHandler2);
    }

    void unhookEvent(CSource* pSource) {
        __unhook(&CSource::OnTrigger1, pSource, &CReceiver::MyHandler1);
        __unhook(&CSource::OnTrigger2, pSource, &CReceiver::MyHandler2);
    }
};
