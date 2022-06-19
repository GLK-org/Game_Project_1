#include "pch.h"
#include "Menu.h"
#include ".\resources\resource.h"

Menu::Menu() : GameLevel() {};
Menu::~Menu() {};
void Menu::Load(Graphics* gfx, Writer* wrt)
{
	srand(time(NULL));
	buttons.push_back(new Buttons(new Recta(WNDWIDTH /2, (3*WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f,0.2f,0.4f,1.0f, 0, "Play"));
	buttons.push_back(new Buttons(new Recta(WNDWIDTH /2, (4*WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f, 0.2f, 0.4f, 1.0f, 1,"Time attack (Soon)"));
	buttons.push_back(new Buttons(new Recta(WNDWIDTH /2, (5*WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f, 0.2f, 0.4f, 1.0f, 2, "Exit"));
	for (std::vector<Buttons*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
	}
	bg = new Inanimate(gfx, WNDWIDTH/2, WNDHEIGHT/2, WNDWIDTH, WNDHEIGHT, IDB_PNG21, true);
	//bg->LoadBmpRes(gfx, L"tet", true);
	title = new Inanimate(gfx, WNDWIDTH / 2, WNDHEIGHT / 5, WNDWIDTH/2, WNDHEIGHT/4, IDB_PNG35, true);
	//title->LoadBmpRes(gfx, L"tet", true);

	rec.hookEvent(&src);

	vc = {};
	snd = nullptr;
	buff = { 0 };
	GameController::audioc->LoadFromRes(L"Game.exe",137, L"WAVE");
	GameController::audioc->Init_Source(buff, vc, &snd);

}

char Menu::GetID()
{

	return -1;

}

void Menu::Unload()
{
	delete bg;
	buttons.~vector();
	text_boxes.~map();
	rec.unhookEvent(&src);
//	snd->DestroyVoice();
}

void Menu::AddObj(SHORT key)
{

}

void Menu::Render(Graphics* gfx , Writer* wrt)
{
	gfx->DrawBg();
	bg->RenderBmpBG(gfx,1.0f,animch);
	title->RenderBmpBG(gfx, 1.0f);
	gfx->StopDrawBg();
	gfx->DrawUI();
	for (std::vector<Buttons*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			(*it)->Render(gfx, (*it)->r, (*it)->g, (*it)->b, (*it)->a, true,wrt, true);
		
	}
	gfx->StopDrawUI();
}

void Menu::Update()
{
	this->MouseLocUpdate();
	if(rand() % 1000 < 1 && bg->drawtarget->frame==0) {
		animch = true;
	}
	else if(animch==true && bg->drawtarget->frame == 0) {
		animch = false;
	}
	for (std::vector<Buttons*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		if ((*it)->CheckTrg(p)) {
			if (GameController::PressButton(RI_MOUSE_LEFT_BUTTON_DOWN)) {
//				GameController::audioc->Init_Source(buff, vc, &snd);
//				GameController::audioc->PlayAudio(snd);
				
				(*it)->OnTrig();
				
				return;
			}
		}
	//	(*it)->ob->Update();
	}
}
