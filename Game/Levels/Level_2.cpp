#include "pch.h"
#include "Level_2.h"




void Level2::Load(Graphics* gfx) {

	this->gfx = gfx;
	objects.push_back(new Eli(100,100, 50, 50, 25, gfx));
//	elip = new Eli(100, 100, 50, 50, 25, new Graphics());
	srand(time(NULL));
	r = g = b = 0.0f;
	x = 0.0f;
	xSpeed = 10.0f;
	y = ySpeed = 0.0f;
	wind = 0;
	gfx->ClearScreen(0.0f, 0.5f, 0.5f);
//	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
//		(*it)->Init(gfx);
//}
}

char Level2::GetID()
{
	return id;
}

void Level2::AddObj(SHORT key)
{
	//if (obj != nullptr) {
	//	objects.push_back(obj);
//	}
//	if ((GetKeyState(key) & 0x8000) == (GetKeyState('P') & 0x8000) ) {
	if (rand() % 2 == 1) {
		objects.push_back(new Eli(rand() % 1364 + 1.0f, rand() % 766 + 1.0f, rand() % 49 + 1.0f, rand() % 49 + 1.0f, rand() % 49 + 1.0f, gfx));
	}
	else {
		float width= rand() % 1364 + 1.0f;
		float height= rand() % 766 + 1.0f;
		objects.push_back(new Recta(width, height, rand() % 1364 + 1.0f, rand() % 766 + 1.0f, rand() % 49 + 1.0f, rand() % 49 + 1.0f, gfx));
	}
//	}
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

void Level2::Update() 
{
	//Tworzenie i usuwanie p³atków
	if (objects.size()<100) {
		AddObj();
	}
	else {
		if (objects.size() > 25) {
			for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
				if ((*it)->GetY()==768) {
					objects.erase(it);
					break;
				}

			}
		}
	}
	//Logika 
	wind += 1;
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		ySpeed += 0.5f;
		if (((*it)->GetY()) > 768) {
			(*it)->SetY(768);
			ySpeed = 0.0f;
			
		}
		if (((*it)->GetX()) < 0) {
			(*it)->SetX(0);
			xSpeed = 5.0f;
		}
		else if (((*it)->GetX()) > 1366) {
			(*it)->SetX(1366);
			xSpeed = -5.0f;
		}
		(*it)->SetY(((*it)->GetY()) + ySpeed);
		(*it)->SetX(((*it)->GetX()) + 5 * sin(((*it)->GetY()*std::numbers::pi / 180))+rand()%10/100.0);
		if (GetKeyState('A') & 0x8000) {
			(*it)->SetX(((*it)->GetX()) + xSpeed);
		}
		else if (GetKeyState('D') & 0x8000) {
			(*it)->SetX(((*it)->GetX()) - xSpeed);
		}
		else if (GetKeyState('W') & 0x8000) {
			ySpeed = 1.0f;
			(*it)->SetY(((*it)->GetY()) - ySpeed);
		}
		else if (GetKeyState(VK_F1) & 0x8000) {
			float temp[2] = { ((*it)->GetX() - ySpeed), ((*it)->GetX() - xSpeed) };
			(*it)->Transform(gfx, temp );
		}

		
	
		(*it)->Update(p);
		
	}
}
