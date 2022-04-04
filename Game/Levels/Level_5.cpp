#include "pch.h"

Level5::Level5()
{
}

Level5::~Level5()
{
}

char Level5::GetID()
{
	return id;
}

void Level5::Load(Graphics* gfx)
{
	doors = new Doors(gfx, new Level4(), new Level6());
	r = g = b = 0.6f;
}

void Level5::AddObj(SHORT key)
{
}

void Level5::Unload()
{
}

void Level5::Render(Graphics* gfx)
{
	gfx->ClearScreen(r, g, b);
	doors->Render(gfx, p, r, 0.1f + g, b, a);
}

void Level5::Update()
{
	this->MouseLocUpdate();
	if (doors->UpdateTrig(p)) {
		return;
	};
}
