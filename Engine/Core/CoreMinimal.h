#pragma once
#include "../pch/Engine.h"
#include "d2d1.h"
#include "d2d1_1.h"
#include <vector>

class ENGINE_API Graphics {
	//Baza do tworzenia zasobów graficznych
	HWND* currentwindow;
	std::vector<ID2D1Layer*> layers;
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;

public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);
	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void DrawEllipse(D2D1_ELLIPSE * eli, float r, float g, float b, float a);
	void DrawRect(D2D1_RECT_F* rect, float , float g, float b, float a);
	void FillRect(D2D1_RECT_F* rect);
	void CreateEllipseGeometry(D2D1_ELLIPSE * eli, ID2D1EllipseGeometry ** ElipseGeo);
	void DrawBG(D2D1_POINT_2F point, float tab[2]);
	void DrawGeo(ID2D1EllipseGeometry* EllipseGeo);
};
