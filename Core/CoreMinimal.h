#pragma once
//tu wrzuci� p�niej loggery i podobne
#include "CoreDefinitions.h"
#include "d2d1.h"
#include "d2d1_1.h"
#include "wincodec.h"


class ENGINE_API Graphics {
	//Baza do tworzenia zasob�w graficznych
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;
public:
	Graphics();
	~Graphics();

public:
	bool Init(HWND windowHandle);
	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float rad, float r, float g, float b, float a);
};