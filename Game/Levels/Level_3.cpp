#include "pch.h"
#include "windowsx.h"
#include <vector>


Level3::Level3()
{
}

Level3::~Level3()
{
}

char Level3::GetID()
{
	return id;
}

void Level3::Load(Graphics* gfx) {
	x = xSpeed = 0.0f;
	y = ySpeed = 0.0f;
	mode = false;
	GetCursorPos(&p);
	//eli = new Eli(this->x, this->y, 50.0f, 40.0f, 52.0f, gfx);
//	rect = new Recta(100.0f,300.0f, 1066.0f, 200, 200 ,300, gfx);
	player = new Player(gfx, 200.0f,150.0f,50.0f, 100.0f,50.0f);
	doors = new Doors(gfx, new Level2(), new Level4());
//	buttons[0] = new Recta(this->x, this->y, 700.0f, 550.0f, 1366.0f, 600.0f, gfx);
//	buttons[1] = new Recta(this->x, this->y, 1.0f, 600.0f, 1365.0f, 768.0f, gfx);
	HRESULT hr;
	hr = gfx->LoadBMP(nullptr, nullptr, L".\Content\Caffle.bmp", (UINT)100, (UINT)100, rect->GetBmp());
	if (hr) {
		r = 0.2f;
		g = 0.1f;
		b = 0.5f;
	}
	else {
		r = g = b = 0;
	}
	change = 0.0;
	a = 1;
	asc = true;
	
}

void Level3::AddObj(SHORT key)
{
	

}

void Level3::Unload() {
	delete eli;
//	rect->~Recta();
	delete doors;
//	for (int i = 0; i < 2; i++) {
//		delete buttons[i];
	
}

void Level3::Render(Graphics* gfx)
{
	
	gfx->ClearScreen(r,g, b);
	if (asc == true) {
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
	float e[4] = { r, g, 0.1f + b, a };
//	rect->Render(gfx, r, 0.1f + g, b, a);
	doors->Render(gfx, p, r, 0.1f + g, b, a);
	player->Render(gfx, p);
  /*	
	this->eli->Render(gfx, r, g, b, a);
	for (Obj* button : this->buttons) {
		button->Render(gfx, rand() % 2, rand() % 2, rand() % 2, 1.0f);
	}
	//Czy to nie powtórka rysowania ramki z render?!
	if (buttons[1]->CheckTrigg(p)) {
		float e[1];
		e[0] = (float)p.x;
		buttons[1]->Fill(gfx, e);
	}
	else {
		buttons[1]->Fill(gfx);
	}

	if (asc == true) {
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

	}*/
}

void Level3::Update() {
	//Zbiera informacje o pozycji myszy
	
	this->MouseLocUpdate();
//	rect->Update();
	if (doors->UpdateTrig(p, *player)) {
		return;
	};
	if(player->character->ttl>2.0f)
		player->Move(p, MEDIUM_FAST);
	// GetKeyState zbiera wciœniêcia przycisku, a "& 0x8000" to operacja bitowa na wyniku zbieraj¹ca ze s³owa bitowego flagi, czy przycisk jest teraz wciœniêty
	if (GetKeyState(VK_SPACE) & 0x8000) {
		mode = !mode;
	}
	if (GetKeyState('L') & 0x8000) {
		player->character->ToggleDebug();
	}
	/*if (mode) {
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
	}*/
	float temp[2] = { x,y };


}