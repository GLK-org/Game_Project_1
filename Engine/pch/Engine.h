#pragma once



#ifdef WIN32
#define UNICODE
#include <Windows.h>

#endif


// Makro u¿ywane do eksportowania/importowania klas/funkcji/parametrów poprzez dodanie przy definicji s³owa kluczowego ENGINE_API
#ifdef BUILD_DLL
#define ENGINE_API _declspec(dllexport)
#else
#define ENGINE_API _declspec(dllimport)
#endif

#ifdef STATIC_RES
#define WNDWIDTH 1280.0f
#define WNDHEIGHT 720.0f
#else
#define WNDHEIGHT (float)GetSystemMetrics(SM_CYSCREEN)
#define WNDWIDTH (float)GetSystemMetrics(SM_CXSCREEN)
#endif
#define FLOATER_PARAMS 0, 0, WNDWIDTH / 10.0f, WNDHEIGHT / 5.0f
#define KEY_PRESSED 0x8000
#define MAX_NAME_STRING 256

#define HInstance() GetModuleHandle(NULL)