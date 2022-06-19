#pragma once
#include "Sources/IEvSource.h"

[event_source(native)]
class ENGINE_API SourceLv1 :public CSource {
public:
    __event void OnTrigger(bool tet);

    __event void OnMusicStop(Obj* ref, int& points);

};

[event_receiver(native)]
class ENGINE_API RecLv : public CReceiver {
public:
    void MyHandler1(bool tet) {
        printf_s("MyHandler1 was called with value %d.\n");
    }

    void MyHandler2(bool tet) {
        printf_s("MyHandler2 was called with value %d.\n");
    }

    void hookEvent(SourceLv1* pSource) {
        __hook(&SourceLv1::OnTrigger, pSource, &RecLv::MyHandler1);
        __hook(&SourceLv1::OnTrigger, pSource, &RecLv::MyHandler2);
    }

    void unhookEvent(SourceLv1* pSource) {
        __unhook(&SourceLv1::OnTrigger, pSource, &RecLv::MyHandler1);
        __unhook(&SourceLv1::OnTrigger, pSource, &RecLv::MyHandler2);
    }
};