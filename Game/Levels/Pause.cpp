#include "pch.h"
#include "Pause.h"


void PauseCl::Load(Graphics* gfx)
{
	buttons.push_back(new with(new Recta(100.0f, 300.0f, 500.0f, 200, 800, 280, gfx)));
	buttons.push_back(new with(new Recta(100.0f, 300.0f, 500.0f, 400, 800, 580, gfx)));
	buttons.push_back(new with(new Recta(100.0f, 300.0f, 500.0f, 600, 800, 780, gfx)));
	for (std::vector<with*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
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

void PauseCl::Render(Graphics* gfx)
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

void PauseCl::Update()
{

	for (std::vector<with*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		
		(*it)->ob->Update();
	}
}
