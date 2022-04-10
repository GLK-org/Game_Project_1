#pragma once
#include "../pch/Engine.h"
#include "d2d1_1.h"
#include <wincodec.h>
#include <vector>

class ENGINE_API Graphics {
	//Baza do tworzenia zasobów graficznych
	HWND* currentwindow;
	std::vector<ID2D1Layer*> layers;
	ID2D1Factory* factory;
	IWICImagingFactory* WICfactory;
	ID2D1HwndRenderTarget* rendertarget;

public:
	Graphics();
	~Graphics();
	
	bool Init(HWND windowHandle);
	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void DrawEllipse(D2D1_ELLIPSE * eli, float r, float g, float b, float a);
	void DrawRect(D2D1_RECT_F* rect, float r, float g, float b, float a);
	void FillRect(D2D1_RECT_F* rect, float e[] = {0});
	void DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, float length, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, float r=0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void CreateEllipseGeometry(D2D1_ELLIPSE * eli, ID2D1EllipseGeometry ** ElipseGeo);
	HRESULT LoadBMP(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);
	void DrawBG(D2D1_POINT_2F point, float tab[2]);
	void DrawGeo(ID2D1EllipseGeometry* EllipseGeo);
};
