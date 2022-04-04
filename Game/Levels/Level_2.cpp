#include "pch.h"
#include "Level_control/GameController.h"
#include <ctime>
#include <numbers>
#include <math.h>
#include <typeinfo>

void Level2::Load(Graphics* gfx ) {
	srand(time(NULL));
	r = g = b = 0.0f;
	x = 0.0f;
	y = 0.0f;
	ySpeed = 1.0f;
	xSpeed = 1.0f;
	objects.push_back(new Eli(123.2f,452.9f,52.2f,50.0f,66.8f, gfx));
	doors = new Doors(gfx, new Level1(), new Level3());
}

char Level2::GetID()
{
	return id;
}

void Level2::Unload() {
	delete doors;
}



void Level2::AddObj(SHORT key ){
	if (objects.size() >50) {
		return;
	}
		if (rand() % 2==0 ) {
			float width = (rand() % 101 )+ 1.0f;
			float height = (rand() % 101) + 1.0f;
			objects.push_back(new Recta((rand()%1265)+100.0f, (rand()%300)+1.0f,width, height,width+rand()% (int)width,height+rand()% (int)height, gfx));
		}
		else {
			int maxsize = (rand() % 200)+1;
			objects.push_back(new Eli((rand() % 1265) + 100.0f, (rand() % 300) + 1.0f, (rand()%maxsize) + 1.0f, (rand() % maxsize) + 1.0f, (rand() % maxsize) + 1.0f, gfx));
		}
		int timer = 0;
		while (objects.size() > 50) {
			
			for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
				if ((*it)->GetY() >= 768) {
					objects.erase(it);
					break;
				}
				else if ((*it)->GetX() <= 0 || (*it)->GetX() >= 1366) {
					objects.erase(it);
					break;
				}
				
			}
			timer++;
			if (timer > 5000) {
				break;
			}
		}
		
}

void Level2::Render(Graphics* gfx)
{
	gfx->ClearScreen(0.0f, 0.5f, 0.5f);
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->Render(gfx, rand() % 2, rand() % 2, rand() % 2, 1.0f);
	}
	doors->Render(gfx, p, r, 0.1f + g, b, 1.0f);
}

void Level2::Update() {
	MouseLocUpdate();
	if (doors->UpdateTrig(p)) {
		return;
	};
	this->AddObj(); 
	if (ySpeed < 10.0f) {
		ySpeed += 0.1f;
	}
	else {
		ySpeed = 1.0f;
	}
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		y = log10((*it)->GetY() + ySpeed + rand() % 3);
		x= xSpeed+xSpeed  * (sin((rand() % 180) * std::numbers::pi) / 180.0);
		
	
	if (GetKeyState('A')) {
		xSpeed += 0.1f;
	}
	else if (GetKeyState('D')) {
		xSpeed -= 0.1f;
	}

	if ((*it)->GetY() >= 768) {
		(*it)->SetY(768);
		//ySpeed = -0.5f;
	}
	if ((*it)->GetX() <= 0) {
		(*it)->SetX(0);
		//xSpeed = 5.0f;
	}
	else if ((*it)->GetX() >= 1366) {
		(*it)->SetX(1366);
		//xSpeed = -5.0f;
	}
	float tab[2] = { x,y };
	(*it)->Update(p,tab);
	}
	
}
