#include "pch.h"
#include "Level_2.h"



Level2::Level2() {
	x = xSpeed = 0.0f;
	y = ySpeed = 0.0f;
}

Level2::~Level2()
{
}


void Level2::Load() {
	x = xSpeed = 0.0f;
	y = ySpeed = 0.0f;

}

void Level2::Unload() {}

void Level2::Render(Graphics* gfx)
{
	gfx->ClearScreen(0.0f, 0.5f, 0.5f);
	gfx->DrawCircle(x, y, 100, 1.0f, 0.0f, 0.0f, 1.0f);
}

void Level2::Update() {

	ySpeed += 0.5f;
	y += ySpeed;
	x += xSpeed;
	if (GetKeyState('A')) {
		xSpeed += 0.1f;
	}
	if (GetKeyState('D')) {
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
