#pragma once
#include "Level_control\GameLevel.h"
#include <vector>
#include "Obj.h"

class Level2 : public GameLevel {
	char id = '2';
	std::vector<Obj*> objects;
	float r, g, b;
	float y, x;
	float ySpeed, xSpeed;
public:
	void Load(Graphics* gfx) override;
	char GetID();
	void Unload() override;
	void Render(Graphics* gfx) override;
	void Update() override;

};

