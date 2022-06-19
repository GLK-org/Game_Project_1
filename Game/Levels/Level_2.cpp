#include "pch.h"
#include "Level_2.h"


void Level2::Load(Graphics* gfx, Writer* wrt) {
	
	GameController::gravity = false;
	srand(time(NULL));
	r = g = b = 0.0f;
	inc = true;
	x = 0.0f;
	y = 0.0f;
	ySpeed = 1.0f;
	xSpeed = 1.0f;
	this->gfx = gfx;
	cooldown = 1.1f;
	basictxt = "Create an item in order to become able to reach the end \n press c for combine mode";
	//bg
	{
	bg = new Inanimate(gfx, WNDWIDTH / 2, WNDHEIGHT * 3 / 10, WNDWIDTH, WNDHEIGHT * 75 / 100, IDB_PNG6);
	//bg->LoadBmp(gfx, L"tet", true);
	}

	//panel
	{
	panel = new Panel(gfx);
	panel->SetText("Combine!", 1);
	panel->SetText(basictxt, 2);
	}

	floater = new FloatingText(gfx, FLOATER_PARAMS, "BASE");
	inventory = new Itemsys(panel->spaces, collectibles);

	//collectibles
	{

		collectibles.push_back(new Battery(gfx, WNDWIDTH * 38 / 100, (WNDHEIGHT * 43 / 100), WNDWIDTH/16, WNDHEIGHT/9));
		collectibles.push_back(new Gyro(gfx, WNDWIDTH * 38 / 100, (WNDHEIGHT * 52 / 100), WNDWIDTH / 16, WNDHEIGHT / 9));
		collectibles.push_back(new Shield(gfx, WNDWIDTH * 38 / 100, (WNDHEIGHT * 63 / 100), WNDWIDTH / 16, WNDHEIGHT / 9));
	}

	//player
	{
	pl = new Player(gfx, STANDARD_PLAYER_POS);
	pl->LoadBmpRes(gfx, IDB_PNG34,true);
	}
	objects.push_back(new Eli(123.2f,452.9f,52.2f,50.0f,66.8f, gfx));
	doors = new Doors2(gfx, new Level1(), new Level3());

	//map_els
	{
	map_el[0] = new Inanimate(gfx, WNDWIDTH / 4, WNDHEIGHT * 72 / 100, WNDWIDTH/2, Lvlb, IDB_PNG11, true,true);
	map_el[1] = new Inanimate(gfx, WNDWIDTH * 3 / 4, WNDHEIGHT * 72 / 100, WNDWIDTH/2 , Lvlb, IDB_PNG11, true,true);
	map_el[2] = new Inanimate(gfx, WNDWIDTH / 4, WNDHEIGHT * 1 / 4, WNDWIDTH / 2, Lvlb+100, IDB_PNG11);
	map_el[3] = new Inanimate(gfx, WNDWIDTH *38/ 100, (WNDHEIGHT * 51 / 100), WNDWIDTH/8.0f, WNDHEIGHT/3.0f, IDB_PNG32);

	}

	r = rand() % 2 / 2.0;
	g = rand() % 2 / 2.0;
	b = rand() % 2 / 2.0;

	rec.hookEvent(&src);
//	GameController::audioc->LoadFromFile( GetLPSTR_Path(L"Shield_effect.wav").c_str(), buff);
//	GameController::audioc->Init_Source(buff, vc, &snd);
}

char Level2::GetID()
{
	return id;
}

void Level2::Unload() {
	
	delete doors;
	delete pl;
	delete bg;
	delete panel;
	delete floater;
	for (Inanimate* el : map_el) {
		delete el;
	}

	objects.clear();
	objects.~vector();
	collectibles.clear();
	collectibles.~vector();
	gfx = nullptr;
//	snd->DestroyVoice();
}



void Level2::AddObj(SHORT key ){
		if (rand() % 2==0 ) {
			float width = (rand() % (int)WNDWIDTH/100.0f )+ 1.0f;
			float height = (rand() % (int)WNDHEIGHT/100.0f) + 1.0f;
			float x1= (rand() % (int)WNDWIDTH) + 100.0f;
			float y1 = (rand() % (int)WNDHEIGHT/4.0f) + 1.0f ;
			objects.push_back(new Recta(x1, y1 , width, height, gfx));
		}
		else {
			int maxsize = (rand() % (int)WNDWIDTH/WNDHEIGHT)*15+1;
			objects.push_back(new Eli((rand() % (int)WNDWIDTH), (rand() % (int)(WNDHEIGHT/6)) + 1.0f, (rand()%maxsize) + 1.0f, (rand() % maxsize) + 1.0f, (rand() % maxsize) + 1.0f, gfx));
		}
		int timer = 0;
		while (objects.size() > 15) {
			
			
			start_loop:
			for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
				for (Inanimate* el : map_el) {
				 POINT tet((*it)->GetX(), (*it)->GetY());
				if (el->drawtarget->CheckTrigg(tet)) {
					objects.erase(it);
					goto start_loop;
				}
				else if ((*it)->GetX() <= 0 || (*it)->GetX() >= WNDWIDTH) {
					objects.erase(it);
					goto start_loop;
				}
				else if ((*it)->ttl > 100.0f) {
					objects.erase(it);
					goto start_loop;
				}
				}
			}
			timer++;
			if (timer > 16) {
				break;
			}
		}
		
}

void Level2::Render(Graphics* gfx, Writer* wrt)
{
	gfx->DrawBg(); {
	gfx->ClearScreen(0.0f, 0.5f, 0.5f);
	bg->RenderBmpBG(gfx, 1.0f);
	
	for (Obj* it : objects) {
		if ((int)(GameController::time) % 2 == 0) {
			r = sin((GameController::time * std::numbers::pi) / 180);
			g = cos((GameController::time * std::numbers::pi) / 180);
			b = -atan((GameController::time * std::numbers::pi) / 180);
		}
		gfx->Rotate(5.0f*(it->ttl), it->GetCenter());
		it->ttl +=rand() % 2;
		it->Render(gfx, r, g, b, 1);
		gfx->ClearTransforms();
	}
	for (Inanimate* el : map_el) {
		el->RenderBmp(gfx, 1.0f);
	}
	doors->Render(gfx, p, r, 0.1f + g, b, 1.0f);

	for (Item* el : collectibles) {
		if (el->id == 5 && el->state == not_earned) {
			continue;
		}
		el->RenderBmp(gfx, 1.0f,el->drawtarget->GetRect());
	}
	gfx->StopDrawBg();
	}

	gfx->DrawChar();{
		pl->RenderBmp(gfx, 1.0f);
		gfx->Scale(D2D1::Size(1.0f, 1.1f), pl->drawtarget->GetCenter());
		pl->RenderSpecialBmp(gfx,1.0f,L"Active",true);
		gfx->ClearTransforms();
		gfx->EndDrawChar();
	}
	
	gfx->DrawUI();{
		panel->Render(gfx);
		panel->LoadTextOnStuff(gfx, wrt, 1);
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

void Level2::Update() {
	cooldown += GameController::increment;
	MouseLocUpdate();
	//mechanizm do dynamicznego dobierania powierzchni do chodzenia
	D2D1_RECT_F lim = D2D1::RectF(0, 0, 0, 0);
	if (GameController::PressButton('C')) {
		inventory->ToggleCombining();
		
	}
	if (inventory->combiner == true) {
		panel->SetText("Combiner mode!", 2);
	}
	else if (doors->crafted) {
		panel->SetText("Great!\n Press E to activate the shield",2);
	}
	else{
		panel->SetText(basictxt, 2);
	}
	if (GameController::PressButton(RI_MOUSE_LEFT_BUTTON_DOWN)) {
		for (Inanimate* el : map_el) {
			if (el->drawtarget->CheckTrigg(p)) {
				if (el->traversible == true) {
				 lim = (el->drawtarget->GetRect());
				}
			}
		}
		if (inventory->combiner == true) {
			panel->SetText("Combiner mode!", 2);
			for (Item* el : collectibles) {
				if (el->drawtarget==nullptr) {
					continue;
				}
				if (el->drawtarget->CheckTrigg(p) && el->state == earned) {

						
						if (inventory->Combine()==I_ActiveShield) 
						{
							inventory->Add(new ActiveShield(gfx, -200, -200, 200, 200));
							inventory->UpdateBmps(gfx);
							doors->crafted = true;

						}
					
					

				}
			}
		}
		else {
			
			for (Item* el : collectibles) {
				if ((el->drawtarget->CheckTrigg(p) && el->state == not_earned) && el->interactable==true) {
					
					if (std::abs(pl->drawtarget->GetX() - el->drawtarget->GetX()) < WNDWIDTH / 12.0f) {
						if (std::abs(pl->drawtarget->GetY() - el->drawtarget->GetY()) < WNDHEIGHT / 3.5f) {
							inventory->Add(el);
						}


					}
				}
		
			}
		
		}
	}
	leave:
	pl->Move(p, SLOW,&lim);
	//tu siê koñczy

	int ind = inventory->CheckTrigs(p);

	

	if (doors->UpdateTrig(p, *pl)) {
		return;
	};
	if (GameController::PressButton('E')) {
		if (inventory->GetCurrentId() == I_ActiveShield) {
			if (cooldown > 10.0f) {
//				GameController::audioc->Init_Source(buff, vc, &snd);
//				GameController::audioc->PlayAudio(snd);
				cooldown = 0.0f;
			}
			pl->condition = !(pl->condition);
			
		}
	}
	


	this->AddObj(); 
	for (std::vector<Obj*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		int y1 = log2(rand() %50+ ySpeed * BASIC_SPEED);
		int x1 =  BASIC_SPEED*sin(rand() %10* ((rand() % 180) * std::numbers::pi) / 180.0);

		D2D1_POINT_2F temp((*it)->GetX(),(*it)->GetY());
		if (pl->drawtarget->CheckTrigg(temp) && pl->condition == false) {
			POINT pe(WNDWIDTH / 4, WNDHEIGHT * 2 / 3);
			pl->Move(pe,FAST,true);
		}
	if ((*it)->GetY() > WNDHEIGHT) {
		(*it)->SetY(WNDHEIGHT);
	}
	if ((*it)->GetX() < 0.0) {
		(*it)->SetX(1);
	}
	else if ((*it)->GetX() > WNDWIDTH) {
		(*it)->SetX(WNDWIDTH);
	}
	if (pl->drawtarget->CheckTrigg((*it)->GetCenter()) && pl->condition==true) {
		int t = rand()%2+1;
				x1 = pow(-1.0, (double)t) * WNDWIDTH / 12 + pow(-1.0, (double)t) * x1 + xSpeed;
				y1 -= WNDHEIGHT/12+y1+ySpeed;
		
	}
	y1 += ySpeed;
	x1 += xSpeed;
	(*it)->Update(x1,y1);
	}
	
	doors->Checkconr();
}
