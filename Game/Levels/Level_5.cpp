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

void Level5::Load(Graphics* gfx, Writer* wrt)
{
	doors = new Doors(gfx, new Level4(), new Level6());
	r = g = b = 0.6f;
	player = new Player(gfx, 200.0f, 500.0f, 50.0f, 100.0f, 50.0f);
}

void Level5::AddObj(SHORT key)
{
}

void Level5::Unload()
{
}

void Level5::Render(Graphics* gfx, Writer* wrt)
{
	gfx->ClearScreen(r, g, b);
	doors->Render(gfx, p, r, 0.1f + g, b, a);
	player->Render(gfx, p);
}

void Level5::Update()
{
	this->MouseLocUpdate();
	player->Move(p, FAST);
	if (doors->UpdateTrig(p)) {
		return;
	};
}
