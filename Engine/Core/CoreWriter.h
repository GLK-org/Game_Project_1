#pragma once
#include "../pch/Engine.h"
#include "d2d1.h"
#include "d2d1_1.h"
#include <vector>
#include "CoreMinimal.h"
#include <dwrite.h>
#include <string>

class ENGINE_API Writer {
	static const WCHAR msc_fontName[];
	static const FLOAT msc_fontSize;
public:
	
	 HRESULT hr;
	 ID2D1Factory* m_pD2DFactory;
	 IDWriteFactory* m_pDWriteFactory;
	 IDWriteTextFormat* m_pTextFormat;
	 void Do();
};