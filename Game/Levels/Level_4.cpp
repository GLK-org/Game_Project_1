#include "pch.h"

Level4::Level4()
{
}

Level4::~Level4()
{
}

char Level4::GetID()
{
	return id;
}

void Level4::Load(Graphics* gfx)
{
	doors = new Doors(gfx, new Level3(), new Level5());
	r = g = b = 0.4f;
}

void Level4::AddObj(SHORT key)
{
}

void Level4::Unload()
{
	delete doors;
}

void Level4::Render(Graphics* gfx)
{
	gfx->ClearScreen(r, g, b);
	doors->Render(gfx, p, r, 0.1f + g, b, a);


}

void Level4::Update()
{
	this->MouseLocUpdate();
	if (doors->UpdateTrig(p)) {
		return;
	};
}
