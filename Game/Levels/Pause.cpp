#include "pch.h"
#include "Pause.h"


void PauseCl::Load(Graphics* gfx, Writer* wrt)
{
	buttons.push_back(new Buttonsp(new Recta(WNDWIDTH / 2, (2 * WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f, 0.2f, 0.4f, 1.0f, 0, "Restart"));
	buttons.push_back(new Buttonsp(new Recta(WNDWIDTH / 2, (4 * WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f, 0.2f, 0.4f, 1.0f, 1, "Time attack"));
	buttons.push_back(new Buttonsp(new Recta(WNDWIDTH / 2, (6 * WNDHEIGHT) / 7, WNDWIDTH / 4, 100.0f, gfx), 0.6f, 0.2f, 0.4f, 1.0f, 2, "Exit"));
	for (std::vector<Buttonsp*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
	}
}

char PauseCl::GetID()
{
	return 0;
}

void PauseCl::Unload()
{
}

void PauseCl::AddObj(SHORT key)
{
}

void PauseCl::Render(Graphics* gfx, Writer* wrt)
{
	for (std::vector<Buttonsp*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		(*it)->Render(gfx, (*it)->r, (*it)->g, (*it)->b, (*it)->a, true, wrt, true);

	}
}

void PauseCl::Update()
{

	this->MouseLocUpdate();

	for (std::vector<Buttonsp*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		if ((*it)->CheckTrg(p)) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) {
				(*it)->OnTrig();
				return;
			}
		}
		//	(*it)->ob->Update();
	}
}
