#include "pch.h"
#include "Level_control/GameController.h"
#include "windowsx.h"


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

	for (int i = 0; i < 6; i++) {
		postab[i].x = 30 + 200 * i;
		postab[i].y = 30 + 100 * i;

	}
	floorx = 682.5f;
	floory = 700.0f;
	width = WNDWIDTH - 1.0f;
	height = WNDHEIGHT - 0.9 * WNDHEIGHT;
	player = new Player(gfx, 200.0f, 500.0f, 50.0f, 100.0f, 50.0f);
	points = 0;
	x = 0.0f;
	xSpeed = 10.0f;
	y = 0.0f;
	ySpeed = -10.0f;
	mode = false;
	GetCursorPos(&p);
	eli = new Eli(this->x, this->y, 50.0f, 40.0f, 52.0f, gfx);
	D2D1_POINT_2F point = postab[rand() % 6];
	text_boxes.insert( { std::string("Goal"), D2D1::RectF(5, WNDHEIGHT - 110, 155, WNDHEIGHT - 10)});
	text_boxes.insert({ std::string("Points"), D2D1::RectF(5, 5, 155, 105) });
	text_boxes.insert({ std::string("Time"), D2D1::RectF(WNDWIDTH-175, 5, WNDWIDTH-35, 105) });
	goal.push_back(new Eli(point.x,point.y, 50.0f, 40.0f, 52.0f, gfx));
	buttons[0] = new Recta(682.5f, 600.0f, 666.0f,50.f, gfx);
	buttons[1] = new Recta(floorx, floory, width,height, gfx);
	doors = new Doors1(gfx, nullptr, new Level2());
	change = 0.0;
	a = 1;
	asc = true;
	r = g = b = 0;
//	reci.hookEvent(&ev);

}

void Level1::AddObj(SHORT key)
{

}

void Level1::Unload() {
//	reci.unhookEvent(&ev);
	eli->~Eli();
	for (int i = 0; i < 2; i++) {
		delete buttons[i];
	}
	delete doors;
}

void Level1::Render(Graphics* gfx, Writer* wrt)
{
	if (doors->ropen) {
		text_boxes.insert({ std::string("Move Right ->"), D2D1::RectF(WNDWIDTH/4, WNDHEIGHT/4, (3*WNDWIDTH)/4, (3*WNDHEIGHT)/4) });
	}
		r = log(change + 0.24)+1;
		g = log(-change + 0.175)+1;
		b = log(-change + 0.15)+1;

	gfx->ClearScreen(0.0f, 0.0f, 0.9f);
	doors->Render(gfx,p,0.2,0.4,0.1,1.0);
	player->Render(gfx, p);
	this->eli->Render(gfx, r,g,b,a);
	if(!doors->ropen){
	
	if (goal.size() == 1) {
		goal[0]->Render(gfx, r, g, b, a);
	}
	else if(goal.size()==0){
		D2D1_POINT_2F point = postab[rand() % 6];
		goal.push_back( new Eli(point.x, point.y, 50.0f, 40.0f, 52.0f, gfx));
	}
	}
	for (Obj* button : this->buttons) {
		button->Render(gfx, rand() % 2, rand() % 2, rand() % 2, 1.0f);
	}
	//Czy to nie powtórka rysowania ramki z render?!
	/*if (buttons[1]->CheckTrigg(p)) {
		float e[1];
		e[0]=(float)p.x;
		buttons[1]->Fill(gfx, e);
	}
	else {*/
		buttons[1]->Fill(gfx);
//	}
	
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
	for (const auto& [key, value] : text_boxes) {
		
		if (key == "Points") {
			float e[4] = { 0.8f,0.6f,0.5f,0.9f };
			D2D1_RECT_F temp = value;
			gfx->FillRect(&temp,e);
			wrt->Draw_Text(key + ": " +std::to_string(points), value);
			
		}
		 if (key == "Time") {
			 float e[4] = { 0.8f,0.6f,0.5f,0.9f };
			 D2D1_RECT_F temp = value;
			 gfx->FillRect(&temp, e);
			wrt->Draw_Text(key +": " + std::to_string((int)GameController::time / 60), value);
			
		}
		if (key == "Goal") {
			float e[4] = { 0.8f,0.7f,0.5f,0.9f };
			D2D1_RECT_F temp = value;
			gfx->FillRect(&temp,e);
			wrt->Draw_Text(key + ": "+std::to_string(lvlgoal), value);
			
		}
		if (key == "Move Right ->") {
			if ((int)GameController::time % 20 != 0) {
				wrt->Draw_Text(key, value);
			}

		
		}
	}
	
}



void Level1::Update() {

	//Zbiera informacje o pozycji myszy
	if (goal.size() != 0) {
		D2D1_POINT_2F temp;
		temp.x = goal[0]->GetX();
		temp.y = goal[0]->GetY();
		if (eli->CheckTrigg(temp)) {
			goal.clear();
			points++;
			//__raise ev.OnTriggerDelete(goal,points);
		}
	}
	
	this->MouseLocUpdate();
	float limit[2][2]; //682.5f, 100.0f
	limit[0][0]=floorx - width / 2.0;
	limit[1][0] = floorx + width / 2.0;
	limit[0][1] = floory - height / 2.0-100.0;
	limit[1][1] = floory + height / 2.0-100.0;
	player->Move(p,SLOW,limit);
	doors->Checkconl();
	doors->Checkconr(points);
	if (doors->UpdateTrig(p,*player)) {
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
			xSpeed -= 0.1f;
		}
		if (GetKeyState('D') & 0x8000) {
			xSpeed += 0.1f;
		}if (GetKeyState('W') & 0x8000) {
			ySpeed -= 0.1f;
		}
		if (GetKeyState('S') & 0x8000) {
			ySpeed += 0.1f;
		}
		if (GetKeyState('L') & 0x8000) {
			eli->ToggleDebug();
		}
		if (GetKeyState('H') & 0x8000) {
			eli->Getpshx().ClearSpeed();
		}
		float peek = eli->EGetPoint(0.0f).y;
		OutputDebugStringA(MakeLPCSTR({ &peek }));

		if (eli->EGetPoint(0.0f).y > 760.0f) {
			//eli->Getpshx().collidey = true;
	//		MakeMesBoxA({ &eli->Getpshx().vVect->angle.y }, "Test");
		//	eli->Getpshx().vVect->angle.y = -1.0f;
		ySpeed = -5.0f;
		//	this->eli->Update(x, y);
		}
		if (eli->EGetPoint(0.0f).y < 0.0f) {
			//eli->Getpshx().collidey = true;
	//		MakeMesBoxA({ &eli->Getpshx().vVect->angle.y }, "Test");
		//	eli->Getpshx().vVect->angle.y = -1.0f;
			ySpeed = 5.0f;
			//	this->eli->Update(x, y);
		}
		else
		{
			eli->Getpshx().collidey = false;
		}
		if (eli->EGetPoint(0.0f).x < 0.0f) {
		//	eli->Getpshx().collidex = true;
		//	eli->Getpshx().vVect->angle.x = 1.0f;
			xSpeed = 5.0f;
	//		this->eli->Update(x, y);
		}
		else if (eli->EGetPoint(0.0f).x > 1366.0f) {
			//eli->Getpshx().collidex = true;
			//eli->Getpshx().vVect->angle.x = -1.0f;
			xSpeed = -5.0f;
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