#pragma once
#include "CoreMinimal.h"
#include "CoreWriter.h"
class ENGINE_API GameLevel {
	//Ka¿dy poziom niech ma zmienn¹ id do porównania poziomu
	
public:
	POINT p;
	virtual void Load(Graphics* gfx, Writer* wrt=nullptr)=0;
	virtual char GetID()=0;
	virtual void Unload() = 0;
	virtual void AddObj(SHORT key=0) = 0;
	virtual void Render(Graphics* gfx = nullptr, Writer* wrt=nullptr) = 0;
	virtual void Update() = 0;
	void MouseLocUpdate() {
		GetCursorPos(&p);
		ScreenToClient(FindWindowA("TutorialOneClass", "TutorialOneTitle"), &p);
	};
};