#pragma once
#include <Windows.h>
#include "Engine.h"
#define MAX_NAME_STRING 256
//definicja handlerów dla ³atwiejszego przekazywania w funkcji WinMain
#define HInstance() GetModuleHandle(NULL)
