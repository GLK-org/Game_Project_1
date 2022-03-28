#include "pch.h"
#include "Level_3.h"
#include <ctime>




void Level3::Load() {
	srand(time(NULL));
	r = g = b = 0;
	x = 683;
	y = 384;
}

void Level3::Unload() {}

void Level3::Render(Graphics* gfx)
{
	gfx->ClearScreen(0.8f, 0.8f, 0);
	gfx->DrawCircle(x, y, 500, r, g, b, 1);
}

void Level3::Update() {

	r += 0.01f;
	g += 0.02f;
	b += 0.03f;
	
	if (GetKeyState(16)) {
		r = g = b = 0;
	}
}
