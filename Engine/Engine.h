#pragma once



#ifdef WIN32

#include <Windows.h>

#endif

#ifdef BUILD_DLL
#define ENGINE_API _declspec(dllexport)
#else
#define ENGINE_API _declspec(dllimport)
#endif