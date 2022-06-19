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
	player = new Player(gfx, 200.0f, 500.0f, 50.0f, 100.0f, 50.0f);
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
	player->Render(gfx, p);
}

void Level6::Update()
{
	this->MouseLocUpdate();
	player->Move(p, FAST);
	if (doors->UpdateTrig(p)) {
		return;
	};
}
