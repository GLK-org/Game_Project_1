#pragma once
#include "../pch/Engine.h"
#include "d2d1.h"
#include <vector>
#include <dwrite.h>
#include <string>
 
class ENGINE_API Writer{
	static const WCHAR msc_fontName[];
	static const FLOAT msc_fontSize;
	ID2D1RenderTarget * reftarget;
public:
	
	 HRESULT hr;
	 ID2D1Factory* m_pD2DFactory;
	 IDWriteFactory* m_pDWriteFactory;
	 IDWriteTextFormat* m_pTextFormat;

	 HRESULT Initialize(ID2D1Factory* factory, ID2D1RenderTarget & target);
	 void Draw_Text(std::string text, D2D1_RECT_F rect );


};