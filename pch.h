#pragma once
#include <Windows.h>
#define MAX_NAME_STRING 256
//definicja handlerów dla łatwiejszego przekazywania w funkcji WinMain
#define HInstance() GetModuleHandle(NULL)
