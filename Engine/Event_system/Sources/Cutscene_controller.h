#pragma once
#include "Sources/IEvSource.h"

[event_source(native)]
class ENGINE_API Cutscene_src :public CSource {
public:
    __event void OnTrigger(int &tet);

    __event void OnMusicStop(Obj* ref, int& points);

};

[event_receiver(native)]
class ENGINE_API Cutscene_rec : public CReceiver {
public:
    void MyHandler1(int &tet) {
        tet++;
    }

    void MyHandler2(Obj* ref, int& points) {
        printf_s("MyHandler2 was called with value %d.\n", points);
    }

    void hookEvent(Cutscene_src* pSource) {
        __hook(&Cutscene_src::OnTrigger, pSource, &Cutscene_rec::MyHandler1);
        __hook(&Cutscene_src::OnMusicStop, pSource, &Cutscene_rec::MyHandler2);
    }

    void unhookEvent(Cutscene_src* pSource) {
        __unhook(&Cutscene_src::OnTrigger, pSource, &Cutscene_rec::MyHandler1);
        __unhook(&Cutscene_src::OnMusicStop, pSource, &Cutscene_rec::MyHandler2);
    }
};