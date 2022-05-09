#include "pch.h"




void Menu::Load(Graphics* gfx, Writer* wrt)
{
	buttons.push_back(new Buttons(new Recta(WNDWIDTH /2, (2*WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f,0.2f,0.4f,1.0f, 0, "Play"));
	buttons.push_back(new Buttons(new Recta(WNDWIDTH /2, (4*WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f, 0.2f, 0.4f, 1.0f, 1,"Time attack"));
	buttons.push_back(new Buttons(new Recta(WNDWIDTH /2, (6*WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f, 0.2f, 0.4f, 1.0f, 2, "Exit"));
	for (std::vector<Buttons*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
	}
}

char Menu::GetID()
{

	return -1;

}

void Menu::Unload()
{

}

void Menu::AddObj(SHORT key)
{

}

void Menu::Render(Graphics* gfx , Writer* wrt)
{

	gfx->ClearScreen(0.8f,0.9f,0.5f);
	for (std::vector<Buttons*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			(*it)->Render(gfx, (*it)->r, (*it)->g, (*it)->b, (*it)->a, true,wrt, true);
		
	}
}

void Menu::Update()
{
	this->MouseLocUpdate();

	for (std::vector<Buttons*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		if ((*it)->CheckTrg(p)) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) {
				(*it)->OnTrig();
				return;
			}
		}
	//	(*it)->ob->Update();
	}
}
