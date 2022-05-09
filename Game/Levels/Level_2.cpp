#include "pch.h"
#include "Level_control/GameController.h"
#include <ctime>
#include <numbers>
#include <math.h>
#include <typeinfo>

void Level2::Load(Graphics* gfx, Writer* wrt) {
	srand(time(NULL));
	r = g = b = 0.0f;
	inc = true;
	x = 0.0f;
	y = 0.0f;
	ySpeed = 1.0f;
	xSpeed = 1.0f;
	objects.push_back(new Eli(123.2f,452.9f,52.2f,50.0f,66.8f, gfx));
	doors = new Doors(gfx, new Level1(), new Level3());
	 r = rand() % 2 / 2.0;
	g = rand() % 2 / 2.0;
	b = rand() % 2 / 2.0;
}

char Level2::GetID()
{
	return id;
}

void Level2::Unload() {
	objects.clear();
	delete doors;
}



void Level2::AddObj(SHORT key ){
		if (rand() % 2==0 ) {
			float width = (rand() % 101 )+ 1.0f;
			float height = (rand() % 101) + 1.0f;
			float x1= (rand() % 1265) + 100.0f;
			float y1 = (rand() % 300) + 1.0f ;
			objects.push_back(new Recta(x1, y1 , width, height, gfx));
		}
		else {
			int maxsize = (rand() % 200)+1;
			objects.push_back(new Eli((rand() % 1265) + 100.0f, (rand() % 300) + 1.0f, (rand()%maxsize) + 1.0f, (rand() % maxsize) + 1.0f, (rand() % maxsize) + 1.0f, gfx));
		}
		int timer = 0;
		while (objects.size() > 100) {
			
			for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
				if ((*it)->GetY() >= 768) {
					objects.erase(it);
					break;
				}
				else if ((*it)->GetX() <= 0 || (*it)->GetX() >= 1366) {
					objects.erase(it);
					break;
				}
				else if ((*it)->ttl > 10.0f) {
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

void Level2::Render(Graphics* gfx, Writer* wrt)
{
	gfx->ClearScreen(0.0f, 0.5f, 0.5f);
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((int)(GameController::time) % 2 == 0) {
			r = sin((GameController::time *  std::numbers::pi) / 180);
			g = cos((GameController::time * std::numbers::pi) / 180);
			b = -atan((GameController::time * std::numbers::pi) / 180);
		}
		
		(*it)->Render(gfx, r, g, b, 1);
	}
	doors->Render(gfx, p, r, 0.1f + g, b, 1.0f);
}

void Level2::Update() {
	float ty = y;
	MouseLocUpdate();
	if (doors->UpdateTrig(p)) {
		return;
	};

	this->AddObj(); 
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		y = log2((double)(*it)->ttl + ySpeed*10.0);
		x =   20.0 * sin((double)(*it)->ttl * (90 - (rand() % 180) * std::numbers::pi) / 180.0);
		
	
	if (GetKeyState('A')) {
		xSpeed += 10.0f;
	}
	else if (GetKeyState('D')) {
		xSpeed -= 10.0f;
	}
	float peek = (*it)->GetY();
	if ((*it)->GetY() > 768.0) {
		(*it)->SetY(767);
	}
	if ((*it)->GetX() < 0.0) {
		(*it)->SetX(1);
	}
	else if ((*it)->GetX() > 1366.0) {
		(*it)->SetX(1365);
	}
	if ((*it)->CheckTrigg(p) && (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000)) {
		objects.erase(it);
		return;
	}
	(*it)->Update(x,y);
	}
	
}
