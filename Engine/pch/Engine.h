#pragma once



#ifdef WIN32

#include <Windows.h>

#endif


// Makro u¿ywane do eksportowania/importowania klas/funkcji/parametrów poprzez dodanie przy definicji s³owa kluczowego ENGINE_API
#ifdef BUILD_DLL
#define ENGINE_API _declspec(dllexport)
#else
#define ENGINE_API _declspec(dllimport)
#endif
#define WNDHEIGHT 768.0f
#define WNDWIDTH 1366.0f
#define KEY_PRESSED 0x8000
#define MAX_NAME_STRING 256

#define HInstance() GetModuleHandle(NULL)