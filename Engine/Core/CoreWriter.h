#pragma once
#include "../pch/Engine.h"
#include "d2d1.h"
#include "d2d1_1.h"
#include <vector>
#include "CoreMinimal.h"

class Writer {


	static  WCHAR msc_fontName[];
	static FLOAT msc_fontSize;
	static HRESULT hr;
	static ID2D1Factory* m_pD2DFactory;

	void Do() {

	
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

		if (SUCCEEDED(hr)) {

		}
	}
};