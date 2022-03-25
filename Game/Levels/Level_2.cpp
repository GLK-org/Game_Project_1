#include "pch.h"
#include "Level_2.h"
#include <ctime>




void Level2::Load() {
	objects.push_back(new Eli(100,100, 50, 50, 25, new Graphics()));
	srand(time(NULL));
	r = g = b = 0.0f;
	x = xSpeed = 0.0f;
	y = ySpeed = 0.0f;

}

void Level2::Unload() {}

void Level2::Render(Graphics* gfx)
{
	gfx->ClearScreen(0.0f, 0.5f, 0.5f);
	for(std::vector<Obj*>::iterator it; it!+)
}

void Level2::Update() {

	ySpeed += 0.5f;
	y += ySpeed;
	x += xSpeed;
	if (GetKeyState('A')) {
		xSpeed += 0.1f;
	}
	else if (GetKeyState('D')) {
		xSpeed -= 0.1f;
	}

	if (y > 768) {
		y = 768;
		ySpeed = -30.0f;
	}
	if (x < 0) {
		x = 0;
		xSpeed = 5.0f;
	}
	else if (x > 1366) {
		x = 1366;
		xSpeed = -5.0f;
	}
}
