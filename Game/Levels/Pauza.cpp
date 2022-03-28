#include "pch.h"
#include "Pauza.h"
#include <ctime>

void Pauza::Load() {
	srand(time(NULL));
}

void Pauza::Unload() {}

void Pauza::Render(Graphics* gfx)
{
	gfx->ClearScreen(1, 1, 1);
	gfx->DrawCircle(653, 254, 20, 0, 0, 0, 1);
	gfx->DrawCircle(693, 254, 20, 0, 0, 0, 1);
}

void Pauza::Update() {

}
