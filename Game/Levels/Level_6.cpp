#include "pch.h"

Level6::Level6()
{
}

Level6::~Level6()
{
}

char Level6::GetID()
{
	return id;
}

void Level6::Load(Graphics* gfx, Writer* wrt)
{
	doors = new Doors(gfx, new Level5(), new Level1());
	r = g = b = 0.8f;
}

void Level6::AddObj(SHORT key)
{
}

void Level6::Unload()
{
}

void Level6::Render(Graphics* gfx, Writer* wrt)
{
	gfx->ClearScreen(r, g, b);
	doors->Render(gfx, p, r, 0.1f + g, b, a);
}

void Level6::Update()
{
	this->MouseLocUpdate();
	if (doors->UpdateTrig(p)) {
		return;
	};
}
