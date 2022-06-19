#pragma once
#include "../pch/Engine.h"
#include "d2d1_1.h"
#include <wincodec.h>
#include <vector>
#include <string>
enum Speed {
	F_SLOWEST,
	F_SLOW,
	F_MEDIUM,
	F_FAST,
	F_IMMEDIATE
};

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

	ID2D1Factory* getFac() { return factory; }

	ID2D1RenderTarget& getRTg() { return *rendertarget; }

	bool Init(HWND windowHandle);

	void BeginDraw() { rendertarget->BeginDraw(); }

	void EndDraw() { rendertarget->EndDraw(); }

	void ClearScreen(float r, float g, float b, float a=1.0f);
	
	void DrawBg(float width = WNDWIDTH, float height = WNDHEIGHT);
	void StopDrawBg();

	void DrawChar(float width = WNDWIDTH, float height = WNDHEIGHT);
	void EndDrawChar();
	
	void DrawUI(float width = WNDWIDTH, float height = WNDHEIGHT);
	void StopDrawUI();

	void DrawElse(float width=WNDWIDTH, float height=WNDHEIGHT);
	void StopDrawElse();

	void DrawEllipse(D2D1_ELLIPSE * eli, float r, float g, float b, float a);
	
	void DrawRect(D2D1_RECT_F* rect, float r, float g, float b, float a);
	void FillRect(D2D1_RECT_F* rect, float e[] = {0});
	void FillRect(D2D1_RECT_F* rect, float r, float g, float b, float a);

	void DrawLine(D2D1_POINT_2F& p1, D2D1_POINT_2F& p2, float length, D2D1_POINT_2F& angle, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void DrawLine(D2D1_POINT_2F& p1, D2D1_POINT_2F& p2, float length, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void DrawLine(D2D1_POINT_2F& p1, D2D1_POINT_2F& p2, float r=0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void CreateEllipseGeometry(D2D1_ELLIPSE * eli, ID2D1EllipseGeometry ** ElipseGeo);
	void Mirror(const D2D1_POINT_2F &p);
	void Scale(const D2D1_SIZE_F size, const D2D1_POINT_2F& p);
	void Rotate(float dg, const D2D1_POINT_2F& p);
	void ClearTransforms();

	HRESULT LoadBmpFromRes(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		int resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap);

	void Drawbmp(ID2D1Bitmap* bitmap,
		const D2D1_RECT_F& destinationRectangle,
		FLOAT                          opacity,
		D2D1_BITMAP_INTERPOLATION_MODE interpolationMode,
		const D2D1_RECT_F& sourceRectangle,
		int& frame,
		float& frametime,
		Speed& spd,
		bool anim = false,
		int starting_frame=0
		);
	HRESULT LoadBMP(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);
	void DrawGeo(ID2D1EllipseGeometry* EllipseGeo);
	bool Cooldown(float& _frametime, int& _frame, Speed spd,int starting_frame=0);
};

