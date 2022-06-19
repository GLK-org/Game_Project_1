#include "pch.h"
#include "Level_4.h"
Level4::Level4()
{
}

Level4::~Level4()
{
}

char Level4::GetID()
{
	return id;
}

void Level4::Load(Graphics* gfx, Writer* wrt)
{
	GameController::gravity = false;
	bg = new Inanimate(gfx, WNDWIDTH / 2, WNDHEIGHT * 3 / 10, WNDWIDTH, WNDHEIGHT * 75 / 100, IDB_PNG6);
	bg->LoadBmp(gfx, L"tet", true);
	//Tops
	limits[0][0][1] = 0.0f;
	limits[1][0][1] = WNDHEIGHT - 299;
	limits[2][0][1] = WNDHEIGHT-100;
	//Bottoms
	limits[0][1][1] = WNDHEIGHT - 300;
	limits[1][1][1] = WNDHEIGHT - 99;
	limits[2][1][1] = WNDHEIGHT;
	//Left
	limits[0][0][0] = 50.0f;
	limits[1][0][0] = 50.0f;
	limits[2][0][0] = 50.0f;
	//Right
	limits[0][1][0] = WNDWIDTH - 50.0f;
	limits[1][1][0] = WNDWIDTH - 50.0f;
	limits[2][1][0] = WNDWIDTH - 50.0f;
	eli = new Eli(123.2f, 452.9f, 52.2f, 50.0f, 66.8f, gfx);
	player = new Player(gfx, WNDWIDTH / 4, 150.0f, 100.0f, 200.0f);
	player->LoadBmp(gfx);
	panel = new Panel(gfx);


	doors = new Doors(gfx, new Level3());
	doors->LoadBmp(gfx);
	r = g = b = 0.4f;
	
}

void Level4::AddObj(SHORT key)
{


}

void Level4::Unload()
{
	ammo.clear();
	delete player;
	
}

void Level4::Render(Graphics* gfx, Writer* wrt)
{

	gfx->DrawBg();{
	for (std::vector<Obj*>::iterator it = ammo.begin(); it != ammo.end(); ++it) {
		if ((*it)->ttl >= 10.0f) {
			ammo.erase(it);
			break;
		}
	}
	if (p.x >= limits[0][0][0] && p.x <= limits[0][1][0]) {
		if (p.y >= limits[0][0][1] && p.y <= limits[0][1][1]) {
			if (ammo.size() < 1 && (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000)) {
				D2D1_POINT_2F temp = player->drawtarget->GetCenter();
				ammo.push_back(new Eli(temp.x, temp.y-150,10.0f, 20.0f, 20.0f, gfx));
				float temp1 = ammo.back()->GetX() - p.x;
				float temp2 = ammo.back()->GetY() - p.y;
				ammo.back()->Update(-temp1,-temp2);

			}

		}
	}

	gfx->ClearScreen(r, g, b);
	bg->RenderBmpBG(gfx, 1.0f);
	eli->Render(gfx, 0.2, 0.5, 0.3, 1.0);
	doors->Render(gfx, p, r, 0.1f + g, b, a);

	gfx->StopDrawBg();
	}
	gfx->DrawChar();{
	player->RenderBmp(gfx, 1.0f);
	
	for (std::vector<Obj*>::iterator it = ammo.begin(); it != ammo.end(); ++it) {
		(*it)->Render(gfx, 0.2f, 0.4f, 0.2f, 1.0f);
	}
	gfx->EndDrawChar();
	}
	gfx->DrawUI();{
	panel->Render(gfx);
	gfx->StopDrawUI();
	}
}

void Level4::Update()
{
	float lim[2][2];
	auto lam = [&] (int index) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				lim[i][j] = limits[index][i][j];
			}
		}
		;
	};
	this->MouseLocUpdate();
	if (doors->UpdateTrig(p)) {
		return;
	};
	lam(1);
	player->Move(p,FAST,lim);
	//OutputDebugStringA("Stan\n");
	for (std::vector<Obj*>::iterator it = ammo.begin(); it != ammo.end(); ++it) {
		(*it)->Update(0.0f,0.0f);
		
	}

}
