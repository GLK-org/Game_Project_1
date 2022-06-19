#include "pch.h"
#include "Level_3.h"
#include"Outro.h"

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

void Level3::Load(Graphics* gfx, Writer* wrt) {
	GetCursorPos(&p);
	r = g = b = 0;
	change = 0.0;
	a = 1;
	asc = true;
	mode = false;
	grav = false;
	GameController::gravity = true;
	this->gfx = gfx;
	

	bg = new Inanimate(gfx, WNDWIDTH / 2, WNDHEIGHT * 3 / 10, WNDWIDTH, WNDHEIGHT * 75 / 100, IDB_PNG6);
	//bg->LoadBmp(gfx, L"tet", true);

	panel = new Panel(gfx);
	floater = new FloatingText(gfx, FLOATER_PARAMS, "BASE");

	player = new Player(gfx, STANDARD_PLAYER_POS);
	player->LoadBmpRes(gfx, IDB_PNG17,true);

	doors = new Doors(gfx, new Level2(), new Outro());

	//map_el
	{
	map_el.push_back(new Inanimate(gfx, WNDWIDTH/ 6, WNDHEIGHT * 72 / 100, WNDWIDTH / 2, Lvlb, IDB_PNG11, true, true));
	map_el.push_back(new Inanimate(gfx, WNDWIDTH * 5 / 6, WNDHEIGHT * 72 / 100, WNDWIDTH / 3, Lvlb, IDB_PNG11, true, true));
	map_el.push_back(new Inanimate(gfx, BUTTON_START_LOC, WNDWIDTH / 10, WNDHEIGHT / 20, IDB_PNG9, true, true, "Button"));

	anim_map_el.push_back(new Animate(gfx, SQUARE_START_LOC, WNDWIDTH / 10, WNDHEIGHT / 5, IDB_PNG11, false, true,"Square",2.0f));
	}

	collectibles.push_back(new Launcher(gfx, WNDWIDTH * 38 / 100, (WNDHEIGHT * 63 / 100), WNDWIDTH / 16, WNDHEIGHT / 9));

	for (Item* el : collectibles) {
		el->LoadBmpRes(gfx);
	}

	inventory = new Itemsys(panel->spaces,collectibles);
}

void Level3::AddObj(SHORT key)
{	}

void Level3::Unload() {
	//	rect->~Recta();
	gfx = nullptr;
	delete doors;
	delete player;
	delete bg;
	delete panel;
	delete inventory;
	delete floater;
	map_el.~vector();
	anim_map_el.~vector();
	collectibles.~vector();
	flock.~vector();
	
}

void Level3::Render(Graphics* gfx, Writer* wrt)
{

	
	gfx->DrawBg(); {
		gfx->ClearScreen(r, g, b);
		bg->RenderBmpBG(gfx, 1.0f);
		for (Inanimate* el : map_el) {
			if (!asc && el->name == "Button") {
				el->RenderBmp(gfx, 1.0f,false,1);
			}
			else {
				el->RenderBmp(gfx, 1.0f);
			}
				
			
		}
		for (Animate* el : anim_map_el) {
			el->Render(gfx,p);
			el->RenderBmp(gfx, 1.0f);
		}

		doors->Render(gfx, p, r, 0.1f + g, b, a);
		gfx->StopDrawBg();
	}

	gfx->DrawChar();{
		if (mode) {
			D2D1_POINT_2F angle = Angle(p, player->drawtarget->GetCenter());
			if (angle.x < 0.0f ? player->drawtarget->direction = LEFT : player->drawtarget->direction = RIGHT);
			if (player->drawtarget->direction == LEFT) {
				
				if (angle.y<=0.7f) {
					gfx->Mirror(player->drawtarget->GetCenter());
					player->drawtarget->actionframe = 1;
					player->RenderSpecialBmp(gfx, 1.0f, L"Stuff");
					gfx->ClearTransforms();
				
				}
				else{
					player->drawtarget->actionframe = 0;
					gfx->Mirror(player->drawtarget->GetCenter());
					player->RenderSpecialBmp(gfx, 1.0f, L"Stuff");
					gfx->ClearTransforms();
				}

			}
			else {
				if (angle.y <= 0.7f) {
					player->drawtarget->actionframe = 1;
					player->RenderSpecialBmp(gfx, 1.0f, L"Stuff");

				}
				else {
					player->drawtarget->actionframe = 0;
					player->RenderSpecialBmp(gfx, 1.0f, L"Stuff");
				}
			}
			
			panel->SetText("Find a way out!", 2);
		}
		else {
			player->RenderBmp(gfx, 1.0f);
		}
	gfx->EndDrawChar();
	}
	
	gfx->DrawElse(); {
		for (Item* el : collectibles) {
			el->RenderBmp(gfx, 1.0f, el->drawtarget->GetRect());
		}

	gfx->StopDrawElse();
	}

	gfx->DrawUI(); {
	panel->Render(gfx);
	panel->LoadTextOnStuff(gfx, wrt, 2);
	inventory->Draw(gfx,p);
	for (Item* el : collectibles) {
		if (el->CheckTrigg(p) && el->taggable) {
			floater->SetText(el->name);
			floater->Render(gfx, p, wrt);
		}

	}
	gfx->StopDrawUI();
	}
}

void Level3::Update() {
	//Zbiera informacje o pozycji myszy

	this->MouseLocUpdate();
	//	rect->Update();

	if (doors->UpdateTrig(p, *player)) {
		return;
	};
	int ind = -1;
	ind = inventory->CheckTrigs(p);

	D2D1_RECT_F lim = D2D1::RectF(0, 0, 0, 0);

	//Reakcje na wciœniêcie myszy
	if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) {
		for (Inanimate* el : map_el) {
			if (el->CheckTrigg(p)) {
				if (el->traversible == true) {
					lim = el->drawtarget->GetRect();
					lim.bottom = lim.bottom - (lim.bottom - lim.top) / 2.0f;
				}

			}
		}

		for (std::vector<Item*>::iterator it = collectibles.begin(); it != collectibles.end(); it++) {
			if ((*it)->CheckTrigg(p)) {
				inventory->Add(new Launcher(gfx, -200, -200, 200, 200));
				collectibles.erase(it);
				break;
			}

		}
	}

	if (GameController::PressButton('E')) {
		if (ind == I_Launcher) {

			player->condition = true;
			mode = !mode;

		}

	}
	
	if (player->drawtarget->GetCenter().y > WNDHEIGHT * 0.7f) {
		POINT e(PLAYER_START_LOC);
		player->Update(e);
	}


	(mode ? player->Update(0,0,true) : player->Move(p, MEDIUM_FAST, &lim,true));

	//things that happen after collision is registered
	for (Inanimate* el : map_el) {
		if (el->CheckTrigg(player->drawtarget->GetRect()) && el->solid) {
			player->drawtarget->phsx->ClearSpeed(player->drawtarget->GetCenter());
			player->Update(0, -GRAV * player->drawtarget->phsx->mass,grav);

		}

		for (Animate* el1 : anim_map_el) {
			if (el->CheckTrigg(el1->drawtarget->GetRect()) && el->solid) {
				el1->Update(0, -GRAV * el1->drawtarget->phsx->mass * 3.0f);
				
				if (el->name == "Button" && asc == true) {
					anim_map_el.push_back(new Animate(gfx, RECT_START_LOC, WNDWIDTH / 4, Lvlb, IDB_PNG11, true, true, "Lower", false, 2.0f));
					asc = false;
				}
			}
			else {
				el1->Update();
			}
			if (mode) {
				if (target) {


					target->Update(p);


				}
			}
			if (el1->CheckTrigg(player->drawtarget->GetRect()) && el1->solid) {

				player->drawtarget->phsx->ClearSpeed(player->drawtarget->GetCenter());
				player->Update(0.0f, -GRAV * player->drawtarget->phsx->mass,grav);
			}

			if (el1->drawtarget->GetCenter().y > WNDHEIGHT * 0.9) {
				if (el1->name == "Square") {
					POINT e(SQUARE_START_LOC);
					el1->Update(e);
				}
				else if (el1->name == "Lower") {
					POINT e(RECT_START_LOC);
					el1->Update(e);
				}
			}


			
		}
	}

	int i=0;

	for (Animate* el2 : anim_map_el) {
		
		for (std::vector<Animate*>::iterator it = anim_map_el.begin() + i; it != anim_map_el.end(); it++) {
			
			if (el2->CheckTrigg((*it)->drawtarget->GetRect()) && (*it)->solid && el2!=(*it)) {
				
				float res = el2->drawtarget->GetCenter().y - (*it)->drawtarget->GetCenter().y;
				
				if (res >= 0 && el2->drawtarget->GetRect().bottom >(*it)->drawtarget->GetRect().top) {
					(*it)->Update(0, -GRAV * (*it)->drawtarget->phsx->mass * 4.0f);
				}
				else if((*it)->drawtarget->GetRect().bottom > el2->drawtarget->GetRect().top) {
					el2->Update(0, -GRAV * el2->drawtarget->phsx->mass * 4.0f);
				}
				
				
			}
		
		}
	}
		if (mode) {
			if (GameController::PressButton(RI_MOUSE_LEFT_BUTTON_DOWN)) {
				for (Animate* el1 : anim_map_el) {
					if (el1->CheckTrigg(p) && el1->solid == true) {
						target = el1;

					}

				}

			}
		}
		else {
			(player->condition ? panel->SetText("Use the gravity gun to make a way to the exit!", 2) : panel->SetText("Use the gravity weapon to make a way to the exit!\n Equip and select, then press E to change modes", 2));
			panel->SetText("Gravity!", 1);
			target = nullptr;
		}
	
}