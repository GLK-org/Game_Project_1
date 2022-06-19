#include "pch.h"
#include "Level_1.h"


Level1::Level1() {
}

Level1::~Level1()
{
	
}

char Level1::GetID()
{
	return id;
}

void Level1::Load(Graphics* gfx, Writer* wrt) {
	GameController::gravity = false;
	this->gfx = gfx;
	points = 0;
	x = y = change = 0.0f;
	xSpeed = 2.0f;
	ySpeed = -2.0f;
	a = 1;
	asc = true;
	r = g = b = 0;
	mode = false;
	GetCursorPos(&p);

    //BG stuff
	bg = new Inanimate(gfx, WNDWIDTH /2, WNDHEIGHT *3/10, WNDWIDTH, WNDHEIGHT*75/100, IDB_PNG6);
//	bg->LoadBmpRes(gfx, L"tet", true);
	panel = new Panel(gfx);

	player = new Player(gfx,STANDARD_PLAYER_POS);
	player->LoadBmpRes(gfx,IDB_PNG22,true);

	
	
	

//	text_boxes.insert( { std::string("Goal"), D2D1::RectF(10, WNDHEIGHT - 110, 105, WNDHEIGHT - 10)});
	//text_boxes.insert({ std::string("Points"), D2D1::RectF(10, 5, 105, 105) });
	//text_boxes.insert({ std::string("Time"), D2D1::RectF(WNDWIDTH-100, 5, WNDWIDTH-5, 105) });


	list.push_back(controller = new Inanimate(gfx, WNDWIDTH / 4, WNDHEIGHT * 56 / 100, WNDWIDTH/16.0f, WNDHEIGHT/4.5f, IDB_PNG31,false,true,"Controller",true));
	list.push_back(buttons[0] = new Inanimate(gfx,WNDWIDTH/2, WNDHEIGHT*4/10, WNDWIDTH/5.3f,WNDHEIGHT/3.0f, IDB_PNG15,false, true));
	list.push_back(buttons[1] = new Inanimate(gfx, WNDWIDTH/2, WNDHEIGHT*7/10, WNDWIDTH,Lvlb*2/3.0f, IDB_PNG12, true,true));
	list.push_back(buttons[2] = new Inanimate(gfx, WNDWIDTH / 2, WNDHEIGHT * 4 / 10, WNDWIDTH / 2, WNDHEIGHT * 3 / 10, IDB_PNG4));
	buttons[0]->LoadBmpRes(gfx, IDB_PNG15);
	buttons[1]->LoadBmpRes(gfx, IDB_PNG12);
	buttons[2]->LoadBmpRes(gfx, IDB_PNG4);


	doors = new Doors1(gfx, nullptr, new Level2());
	
	for (int i = 0, j = i + 1; i < 6; i++, j++) {
		postab[i].x = buttons[2]->drawtarget->GetRect().left + 100 * j;
		postab[i].y = buttons[2]->drawtarget->GetRect().top + 30 * j;

	}
	D2D1_POINT_2F point = postab[rand() % 6];
	goal.push_back(new Eli(point.x, point.y, WNDWIDTH/50.0f, WNDWIDTH / 100.0f, WNDHEIGHT / 50.0f, gfx));
	eli = new Ball(gfx, WNDWIDTH / 2, WNDHEIGHT /2, WNDWIDTH / 50.0f, WNDWIDTH / 50.0f, WNDHEIGHT / 30.0f);

	player->drawtarget->phsx->SetVLim(SLOW);
	controller->SetSpd(F_SLOW);
//	reci.hookEvent(&ev);
	panel->SetText("Points: " + std::to_string(points), 1);
	text = new FloatingText(gfx, FLOATER_PARAMS, "NULL");
	eli->SetSpd(F_IMMEDIATE);
}

void Level1::AddObj(SHORT key)
{

}

void Level1::Unload() {
//	reci.unhookEvent(&ev);

	delete player;
	delete panel;
	delete eli;
	delete controller;
	for (Inanimate* el : buttons)
		delete el;
	delete bg;
	delete doors;
	delete text;
	goal.clear();
	goal.~vector();
	text_boxes.clear();
	text_boxes.~map();
	list.clear();
	list.~vector();
	gfx = nullptr;
}

void Level1::Render(Graphics* gfx, Writer* wrt)
{
	//kolejnoœæ rysowania
	if (!mode) {


	gfx->DrawBg();{

	if (int(GameController::time) % 1 > 0) { return; }
	if (doors->ropen) {
		text_boxes.insert({ std::string("Move Right ->"), D2D1::RectF(WNDWIDTH/4, WNDHEIGHT/4, (3*WNDWIDTH)/4, (3*WNDHEIGHT)/4) });
	}
		r = log(change + 0.24)+1;
		g = log(-change + 0.175)+1;
		b = log(-change + 0.15)+1;

	gfx->ClearScreen(0.0f, 0.0f, 0.9f);

	bg->RenderBmpBG(gfx, 1.0f);


	doors->Render(gfx,p,0.2,0.4,0.1,1.0);

	
	if(!doors->ropen){
	
		if (goal.size() == 1) {
			goal[0]->Render(gfx, r, g, b, a);
		}
		else if(goal.size()==0){
			D2D1_POINT_2F point = postab[rand() % 6];
			goal.push_back( new Eli(point.x, point.y, 50.0f, 15.0f, 25.0f, gfx));

		}
	}
	gfx->Scale(D2D1::Size(0.5f,0.5f),buttons[0]->drawtarget->GetCenter());
	buttons[0]->RenderBmp(gfx, 1.0f,true);
	eli->RenderBmp(gfx, 1.0f, true);
	gfx->ClearTransforms();
	buttons[1]->RenderBmp(gfx, 1.0f);
	buttons[2]->RenderBmpBG(gfx, 0.9f);
	controller->RenderBmp(gfx, 1.0f,true);
	
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
	gfx->StopDrawBg();
	}

	gfx->DrawChar();{
	if (!mode) {
		player->RenderBmp(gfx, 1.0f, false);
	}
	else {
		player->RenderSpecialBmp(gfx, 1.0f, L"Operating.png");
	}
	gfx->EndDrawChar();
	}
	}

	else {
		
		text_boxes.insert({ std::string("To exit, press E \n press R to reposition the ball"), D2D1::RectF(0, 0, WNDWIDTH * 4 / 10, WNDHEIGHT * 2 / 10 )});
		gfx->DrawBg();{



		gfx->Scale(D2D1::Size(1.0f, 1.3f), buttons[2]->drawtarget->GetCenter());
		bg->RenderBmpBG(gfx, 1.0f);
		gfx->ClearTransforms();
		

		buttons[0]->RenderBmp(gfx, 1.0f, true);
		gfx->Scale(D2D1::Size(1.5f, 1.5f), eli->drawtarget->GetCenter());
		eli->RenderBmp(gfx, 1.0f, true);
		gfx->ClearTransforms();

		if (!doors->ropen) {

			if (goal.size() == 1) {
				
				goal[0]->Render(gfx, r, g, b, a);
			}
			else if (goal.size() == 0) {
				D2D1_POINT_2F point = postab[rand() % 6];
				
				goal.push_back(new Eli(point.x, point.y, 50.0f, 40.0f, 52.0f, gfx));

			}
		}

		gfx->Scale(D2D1::Size(WNDWIDTH, WNDHEIGHT), buttons[2]->drawtarget->GetCenter());
		buttons[2]->RenderBmp(gfx, 0.5f);
		gfx->ClearTransforms();

		for (const auto& [key, value] : text_boxes) {
			if (key == "To exit, press E \n press R to reposition the ball") {
				D2D1_RECT_F temp = value;
				wrt->Draw_Text(key, value);
			}
		}
		gfx->StopDrawBg();
		}
		text_boxes.erase(--text_boxes.end());
	}

	gfx->DrawUI();{
	if (!mode) {
		for (std::vector<Inanimate*>::iterator it = list.begin(); it != list.end(); it++) {

			if ((*it)->taggable == true && (*it)->CheckTrigg(p)) {
				text->SetText((*it)->name);
				text->Render(gfx, p, wrt);
			}
		}
	}
	
	//float vals[5] = {eli->drawtarget->Getpshx().vVect->angle.x,eli->drawtarget->Getpshx().vVect->angle.y,eli->drawtarget->Getpshx().vVect->len, eli->drawtarget->Getpshx().vVect->v_0.x,eli->drawtarget->Getpshx().vVect->v_0.y, };

	panel->Render(gfx);
	panel->LoadTextOnStuff(gfx, wrt, 2);
	panel->LoadTextOnStuff(gfx, wrt, 1);
	
	gfx->StopDrawUI();
	}

}



void Level1::Update() {
	panel->SetText("Points: " + std::to_string(points), 1);
	//Zbiera informacje o pozycji myszy
	if (goal.size() != 0) {
		D2D1_POINT_2F temp;
		temp.x = goal[0]->GetX();
		temp.y = goal[0]->GetY();
		if (eli->drawtarget->CheckTrigg(temp)) {
			goal.clear();
			points++;
			//__raise ev.OnTriggerDelete(goal,points);
		}
	}

	this->MouseLocUpdate();
	text->Update(p);

	D2D1_RECT_F lim = D2D1::RectF(0, 0, 0, 0);

	if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) {
		for (Inanimate* el : list) {
			if (el->CheckTrigg(p)) {
				if (el->traversible == true) {
					lim = (el->drawtarget->GetRect());
				}

			}
		}
	}
	player->Move(p, SLOW, &lim);
	doors->Checkconl();
	doors->Checkconr(points);


	if (doors->UpdateTrig(p,*player)) {
		return;
	};
	// GetKeyState zbiera wciœniêcia przycisku, a "& 0x8000" to operacja bitowa na wyniku zbieraj¹ca ze s³owa bitowego flagi, czy przycisk jest teraz wciœniêty
	

	if ((GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) && controller->drawtarget->CheckTrigg(p) && !mode) {
		if (std::abs(player->drawtarget->GetX() - controller->drawtarget->GetX()) < WNDWIDTH/12.0f) {
			if (std::abs(player->drawtarget->GetY() - controller->drawtarget->GetY()) < WNDHEIGHT / 7.0f) {
				mode = !mode;
				goal.clear();
				eli->drawtarget->UpdateCenter(WNDWIDTH / 2, WNDHEIGHT * 4 / 10);
				eli->drawtarget->phsx->ClearSpeed();
				buttons[0]->setTrav(!(buttons[1]->getTrav()));
			}
		}
		
	}
	else if (mode) {
		if (GetKeyState('E') & 0x8000) {
			mode = !mode;
			goal.clear();
			eli->drawtarget->UpdateCenter(WNDWIDTH / 2, WNDHEIGHT * 4 / 10);
			eli->drawtarget->phsx->ClearSpeed();
			buttons[0]->setTrav(!(buttons[1]->getTrav()));
		}
	}
	//textupdate
	
	
	if ( points < lvlgoal) {
		if (mode) {
			panel->SetText("Controls: \n W - up, S - down \n A - left, D - right", 2);
		}
		else {
			panel->SetText("Score 11 points by helping the energy ball reach the targets!", 2);
		}
	}
	else {
		panel->SetText("Move to the right door ->", 2);
	}
	
	if (mode) {
		
		y = ySpeed;
		x = xSpeed;
		
		if (GetKeyState('A') & 0x8000) {
			xSpeed = xSpeed -0.5f;
		}
		if (GetKeyState('D') & 0x8000) {
			xSpeed = xSpeed+ 0.5f;
		}
		if (GetKeyState('W') & 0x8000) {
			ySpeed = ySpeed - 0.5f;
		}
		if (GetKeyState('S') & 0x8000) {
			ySpeed = ySpeed+ 0.5f;
		}
		if (GetKeyState('L') & 0x8000) {
			eli->drawtarget->ToggleDebug();
		}
		if (GetKeyState('H') & 0x8000) {
			eli->drawtarget->Getpshx().ClearSpeed();
		}
		if (GetKeyState('R') & 0x8000) {
			eli->drawtarget->UpdateCenter(WNDWIDTH / 5, WNDHEIGHT * 4 / 10);
			 eli->drawtarget->phsx->ClearSpeed(eli->drawtarget->GetCenter());
			 return;

		}
		
	


	if (eli->drawtarget->GetCenter().y < 0) {
	//	eli->drawtarget->UpdateCenter(eli->drawtarget->GetCenter().x,5);
	//	eli->drawtarget->phsx->ClearSpeed();
		ySpeed = -ySpeed/2.0f+2.0f;
	}else if(eli->drawtarget->GetCenter().y > WNDHEIGHT * 75 / 100)
	{
	//	eli->drawtarget->UpdateCenter(eli->drawtarget->GetCenter().x, WNDHEIGHT * 6 / 10);
	//	eli->drawtarget->UpdateCenter(eli->drawtarget->GetCenter().x, (WNDHEIGHT * 75 / 100)-20);
	//	eli->drawtarget->phsx->ClearSpeed();
		ySpeed = -ySpeed / 2.0f -2.0f;

	}
	else if (eli->drawtarget->GetCenter().x < 0) {
//	eli->drawtarget->UpdateCenter(1, eli->drawtarget->GetCenter().y);
	//	eli->drawtarget->UpdateCenter(5, eli->drawtarget->GetCenter().y);
	//	eli->drawtarget->phsx->ClearSpeed();
		xSpeed = -xSpeed / 2.0f + 2.0f;
	}
	else if (eli->drawtarget->GetCenter().x > WNDWIDTH)
	{
	//	eli->drawtarget->UpdateCenter(500-1, eli->drawtarget->GetCenter().y);
	//	eli->drawtarget->UpdateCenter(WNDWIDTH-5, eli->drawtarget->GetCenter().y);
	//	eli->drawtarget->phsx->ClearSpeed();
		xSpeed = -xSpeed / 2.0f -2.0f;

	}

	float peek = eli->drawtarget->GetCenter().y;

		if (buttons[0]->drawtarget->CheckTrigg(eli->drawtarget->GetCenter())) {
			D2D1_RECT_F boundary = buttons[0]->drawtarget->GetRect();
			if (eli->drawtarget->GetCenter().x >= boundary.left && eli->drawtarget->GetCenter().x < boundary.right-30.0f) {
				xSpeed = -xSpeed / 1.2f + 2.0f;
			}
			else if (eli->drawtarget->GetCenter().x <= boundary.right && eli->drawtarget->GetCenter().x < boundary.left + 30.0f) {
				xSpeed = -xSpeed / 1.2f - 2.0f;
			}
			else if (eli->drawtarget->GetCenter().y >= boundary.top && eli->drawtarget->GetCenter().y <= boundary.bottom - 30.0f) {
				ySpeed = -ySpeed / 1.2f - 2.0f;
			}

			else if (eli->drawtarget->GetCenter().y <= boundary.bottom && eli->drawtarget->GetCenter().y < boundary.top-30.0f) {
				ySpeed = -ySpeed / 1.2f + 2.0f;
			}

		}
		//Wybór trybów miêdzy update'owaniem lokalizacji przez pozycjê myszy albo obliczenia
		this->eli->drawtarget->phsx->SetVLim(FAST);


	}
	else {
	
		
		if(buttons[0]->drawtarget->CheckTrigg(eli->drawtarget->GetCenter())) {
			D2D1_RECT_F boundary = buttons[0]->drawtarget->GetRect();
			if (eli->drawtarget->GetCenter().x >= boundary.left && eli->drawtarget->GetCenter().x < boundary.right - OFFSET) {
				xSpeed = -xSpeed / 1.2f + 2.0f;
			}
			else if (eli->drawtarget->GetCenter().x <= boundary.right && eli->drawtarget->GetCenter().x < boundary.left + OFFSET) {
				xSpeed = -xSpeed / 1.2f - 2.0f;
			}
			else if (eli->drawtarget->GetCenter().y >= boundary.top && eli->drawtarget->GetCenter().y <= boundary.bottom - OFFSET) {
				ySpeed = -ySpeed / 1.2f - 2.0f;
			}

			else if (eli->drawtarget->GetCenter().y <= boundary.bottom && eli->drawtarget->GetCenter().y < boundary.top - OFFSET) {
				ySpeed = -ySpeed / 1.2f + 2.0f;
			}

		}
		float Offsetplus = OFFSET + 20.0f;
		if (eli->drawtarget->GetCenter().y <= buttons[2]->drawtarget->GetRect().top - Offsetplus) {
		//	eli->drawtarget->UpdateCenter(eli->drawtarget->GetCenter().x, buttons[2]->drawtarget->GetRect().top+10);
		//	eli->drawtarget->phsx->ClearSpeed();
			ySpeed = 2.0f;
		}
		else if (eli->drawtarget->GetCenter().y >= buttons[2]->drawtarget->GetRect().bottom + Offsetplus)
		{
		//	eli->drawtarget->UpdateCenter(eli->drawtarget->GetCenter().x, buttons[2]->drawtarget->GetRect().bottom-10);
		//	eli->drawtarget->phsx->ClearSpeed();
			ySpeed = -2.0f;


		}
		else if (eli->drawtarget->GetCenter().x <= buttons[2]->drawtarget->GetRect().left - Offsetplus*4) {
	//		eli->drawtarget->UpdateCenter( buttons[2]->drawtarget->GetRect().left+10, eli->drawtarget->GetCenter().y);
		//	eli->drawtarget->phsx->ClearSpeed();
			xSpeed = 2.0f;
		}
		else if (eli->drawtarget->GetCenter().x >= buttons[2]->drawtarget->GetRect().right + Offsetplus*4)
		{
		//	eli->drawtarget->UpdateCenter(buttons[2]->drawtarget->GetRect().right - 10, eli->drawtarget->GetCenter().y);
		//	eli->drawtarget->phsx->ClearSpeed();
			xSpeed = -2.0f;

		}

		
		//Wybór trybów miêdzy update'owaniem lokalizacji przez pozycjê myszy albo obliczenia
		this->eli->drawtarget->phsx->SetVLim(SLOW);
		
	}

	y = ySpeed/10.0f;
	x = xSpeed / 10.0f;
	(y < 5.0f ? y : y=5.0f);
	(y > -5.0f ? y : y = -5.0f);
	(x < 5.0f ? x : x = 5.0f);
	(x > -5.0f ? x : x = -5.0f);
	eli->Update(x, y);
	
}