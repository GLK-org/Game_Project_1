#include "pch.h"




void Menu::Load(Graphics* gfx, Writer* wrt)
{
//	buttons.push_back(new with(new Recta(100.0f, 300.0f, 500.0f, 200, 800, 280, gfx)));
//	buttons.push_back(new with(new Recta(100.0f, 300.0f, 500.0f, 400, 800, 580, gfx)));
//	buttons.push_back(new with(new Recta(100.0f, 300.0f, 500.0f, 600, 800, 780, gfx)));
	for (std::vector<with*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
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
	for (std::vector<with*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		float r, g, b;
		r = g = b = 0.2f;
		if ((*it)->fill) {
			float t[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
			(*it)->ob->Fill(gfx, t);
		}
		else {
			(*it)->ob->Render(gfx, r, g, b, 1);
		}
	}
}

void Menu::Update()
{
	for (std::vector<with*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {

		(*it)->ob->Update();
	}
}
