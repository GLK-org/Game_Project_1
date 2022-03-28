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
	
}

void Level1::AddObj(SHORT key)
{

}

void Level1::Unload() {

}

void Level1::Render(Graphics* gfx)
{
	
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	this->eli->Render(gfx);
	for (Obj* button : this->buttons) {
		button->Render(gfx);
	}
	//Czy to nie powtórka rysowania ramki z render?!
	buttons[1]->Fill(gfx);
}

void Level1::Update() {
	//Zbiera informacje o pozycji myszy
	GetCursorPos(&p);
	// GetKeyState zbiera wciœniêcia przycisku, a "& 0x8000" to operacja bitowa na wyniku zbieraj¹ca ze s³owa bitowego flagi, czy przycisk jest teraz wciœniêty
	if (GetKeyState(VK_SPACE) & 0x8000) {
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
			xSpeed = 5.0f;
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
	int temp[2] = { x,y };

	this->eli->Update(temp);
	
}