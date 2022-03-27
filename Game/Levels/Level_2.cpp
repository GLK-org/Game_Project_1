#include "pch.h"
#include "Level_2.h"
#include <ctime>




void Level2::Load(Graphics* gfx) {
	objects.push_back(new Eli(100,100, 50, 50, 25, gfx));
//	elip = new Eli(100, 100, 50, 50, 25, new Graphics());
	srand(time(NULL));
	r = g = b = 0.0f;
	x = xSpeed = 0.0f;
	y = ySpeed = 0.0f;
	gfx->ClearScreen(0.0f, 0.5f, 0.5f);
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->Init(gfx);
	}
}

char Level2::GetID()
{
	return id;
}

void Level2::Unload() {
	objects.clear();
}

void Level2::Render(Graphics* gfx)

{
	gfx->ClearScreen(0.0f, 0.5f, 0.5f);
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->Render(gfx);
	}
	

	//elip->Render(gfx);
}

void Level2::Update() {
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		ySpeed += 0.5f;
		(*it)->SetY(((*it)->GetY()) + ySpeed);
		(*it)->SetY(y);
		
		(*it)->SetX(x);
		if (GetKeyState('a')) {
			(*it)->SetX(((*it)->GetX()) + xSpeed);
		}
		else if (GetKeyState('d')) {
			(*it)->SetX(((*it)->GetX()) - xSpeed);
		}
		else if (GetKeyState('w')) {
			(*it)->SetY(((*it)->GetY()) - xSpeed);
		}
		if (((*it)->GetY()) > 768) {
			(*it)->SetY(768);
			ySpeed = -30.0f;
		}
		if (((*it)->GetX()) < 0) {
			(*it)->SetX(0);
			xSpeed = 5.0f;
		}
		else if (x > 1366) {
			(*it)->SetX(1366);
			xSpeed = -5.0f;
		}
		(*it)->Update();
	}
}
