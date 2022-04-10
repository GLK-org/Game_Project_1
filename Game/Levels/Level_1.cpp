#include "pch.h"
#include "Level_control/GameController.h"
#include "windowsx.h"
#include <vector>

Level1::Level1() {
}

Level1::~Level1()
{
}

char Level1::GetID()
{
	return id;
}

void Level1::Load(Graphics* gfx) {
	x =  0.0f;
	xSpeed = 10.0f;
	y =0.0f;
	ySpeed = 10.0f;
	mode = false;
	GetCursorPos(&p);
	eli = new Eli(this->x, this->y,50.0f,40.0f,52.0f, gfx);
	buttons[0] = new Recta(this->x, this->y, 700.0f, 550.0f, 1366.0f,600.0f, gfx);
	buttons[1] = new Recta(this->x, this->y, 1.0f, 600.0f, 1365.0f, 768.0f, gfx);
	doors = new Doors(gfx, nullptr, new Level2());
	change = 0.0;
	a = 1;
	asc = true;
	r = g = b = 0;
}

void Level1::AddObj(SHORT key)
{

}

void Level1::Unload() {

	eli->~Eli();
	for (int i = 0; i < 2; i++) {
		delete buttons[i];
	}
}

void Level1::Render(Graphics* gfx)
{
		r = log(change + 0.24)+1;
		g = log(-change + 0.175)+1;
		b = log(-change + 0.15)+1;

	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	this->eli->Render(gfx, r,g,b,a);
	for (Obj* button : this->buttons) {
		button->Render(gfx, rand() % 2, rand() % 2, rand() % 2, 1.0f);
	}
	//Czy to nie powtórka rysowania ramki z render?!
	if (buttons[1]->CheckTrigg(p)) {
		float e[1];
		e[0]=(float)p.x;
		buttons[1]->Fill(gfx, e);
	}
	else {
		buttons[1]->Fill(gfx);
	}
	
	if (asc==true) {
		if (change >= 1.0) {
			asc = !asc;
		}
		change += 0.02;
	}
	else {
		if (change < 0.00) {
			asc = !asc;
		}
			change -= 0.02;
		
	}
}



void Level1::Update() {
	//Zbiera informacje o pozycji myszy
	this->MouseLocUpdate();

	if (doors->UpdateTrig(p)) {
		return;
	};
	// GetKeyState zbiera wciœniêcia przycisku, a "& 0x8000" to operacja bitowa na wyniku zbieraj¹ca ze s³owa bitowego flagi, czy przycisk jest teraz wciœniêty
	if (GetKeyState(VK_SPACE) & 0x8000 || eli->CheckTrigg(p)) {
		mode = !mode;
	}
	if (mode) {
		x  = p.x;
		xSpeed = ySpeed = 0;
		y = p.y;
		if (eli->GetY() > 600) {
			eli->SetY(600);
		//	ySpeed = -30.0f;
		}
		else if (eli->GetY() < 300) {
			eli->SetY(300);

		}
		if (eli->GetX() < 0) {
			eli->SetX(0);
		//	xSpeed = 5.0f;
		}
		else if (eli->GetX() > 1366) {
			eli->SetX(1366);
		//	xSpeed = -5.0f;
		}
	}
	else {

		y = ySpeed;
		x = xSpeed;
		if (GetKeyState('A') & 0x8000) {
			xSpeed -= 1.0f;
		}
		if (GetKeyState('D') & 0x8000) {
			xSpeed += 1.0f;
		}if (GetKeyState('W') & 0x8000) {
			ySpeed -= 1.0f;
		}
		if (GetKeyState('S') & 0x8000) {
			ySpeed += 1.0f;
		}
		float peek = eli->EGetPoint(0.0f).y;
		OutputDebugStringA(MakeLPCSTR({ &peek }));

		if (eli->EGetPoint(0.0f).y > 600.0f) {
			//eli->Getpshx().collidey = true;
	//		MakeMesBoxA({ &eli->Getpshx().vVect->angle.y }, "Test");
			eli->Getpshx().vVect->angle.y = -1.0f;
		//	this->eli->Update(x, y);
		}
		else
		{
			eli->Getpshx().collidey = false;
		}
		if (eli->EGetPoint(0.0f).x < 0.0f) {
		//	eli->Getpshx().collidex = true;
			eli->Getpshx().vVect->angle.x = 1.0f;
		//	xSpeed = 5.0f;
	//		this->eli->Update(x, y);
		}
		else if (eli->EGetPoint(0.0f).x > 1366.0f) {
			//eli->Getpshx().collidex = true;
			eli->Getpshx().vVect->angle.x = -1.0f;
		//	xSpeed = 5.0f;
		//	this->eli->Update(x, y);
		}
		else {
			eli->Getpshx().collidex = false;
		}
	}
	y = ySpeed;
	x = xSpeed;
	//Wybór trybów miêdzy update'owaniem lokalizacji przez pozycjê myszy albo obliczenia
	if (mode) {
		this->eli->Update(p);
	}
	else {
		this->eli->Update(x, y);
	}
	
	
}