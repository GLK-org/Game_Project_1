#pragma once
#include "../pch/Engine.h"
#include "d2d1.h"
#include "d2d1_1.h"
#include <vector>

class ENGINE_API Graphics {
	//Baza do tworzenia zasobów graficznych
	std::vector<ID2D1Layer*> layers;
	HWND* currentwindow;
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);
	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float rad, float r, float g, float b, float a);
	void CreateEllipseGeometry(D2D1_ELLIPSE &eli, ID2D1EllipseGeometry ** EllipseGeo);
	void DrawBG();
	void DrawGeo(ID2D1EllipseGeometry* EllipseGeo);

};
