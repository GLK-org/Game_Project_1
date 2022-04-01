#include "pch.h"
#include "Level_1.h"
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
	x = xSpeed = 0.0f;
	y = ySpeed = 0.0f;
	mode = false;
	GetCursorPos(&p);
	eli = new Eli(this->x, this->y,50.0f,40.0f,52.0f, gfx);
	buttons[0] = new Recta(this->x, this->y, 700.0f, 550.0f, 1366.0f,600.0f, gfx);
	buttons[1] = new Recta(this->x, this->y, 1.0f, 600.0f, 1365.0f, 768.0f, gfx);
	change = 0.0;
	a = 1;
	asc = true;
	r = g = b = 0;
}

void Level1::AddObj(SHORT key)
{

}

void Level1::Unload() {

}

void Level1::Render(Graphics* gfx)
{
		r = log(change + 0.24)+1;
		g = log(change + 0.175)+1;
		b = log(change + 0.15)+1;

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
	GetCursorPos(&p);
	ScreenToClient(FindWindowA("TutorialOneClass","TutorialOneTitle" ), &p);
	// GetKeyState zbiera wciœniêcia przycisku, a "& 0x8000" to operacja bitowa na wyniku zbieraj¹ca ze s³owa bitowego flagi, czy przycisk jest teraz wciœniêty
	if (GetKeyState(VK_SPACE) & 0x8000 || eli->CheckTrigg(p)) {
		mode = !mode;
	}
	if (mode) {
		x = p.x;
		y = p.y;
		if (p.y > 600) {
			y = 600;
		//	ySpeed = -30.0f;
		}
		else if (p.y < 300) {
			y = 300;

		}
		if (p.x < 0) {
			x = 0;
		//	xSpeed = 5.0f;
		}
		else if (p.x > 1366) {
			x = 1366;
		//	xSpeed = -5.0f;
		}
	}
	else {

		ySpeed += 1.0f;
		y += ySpeed;
		x += xSpeed;
		if (GetKeyState('A') & 0x8000) {
			xSpeed -= 0.1f;
		}
		if (GetKeyState('D') & 0x8000) {
			xSpeed += 0.1f;
		}


		if (y > 600) {
			y = 600;
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
	float temp[2] = { x,y };

	this->eli->Update(p, temp);
	
}