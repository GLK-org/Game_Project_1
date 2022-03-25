#pragma once
#include "Level_control\GameLevel.h"

class Level2 : public GameLevel {
	float r, g, b;
	float y, x;
	float ySpeed, xSpeed;
public:
	void Load() override;
	void Unload() override;
	void Render(Graphics* gfx) override;
	void Update() override;

};

