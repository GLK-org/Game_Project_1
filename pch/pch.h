#pragma once
#include <Windows.h>
#include "Engine.h"
#define MAX_NAME_STRING 256
//definicja handler�w dla �atwiejszego przekazywania w funkcji WinMain
#define HInstance() GetModuleHandle(NULL)
