#pragma once
#include "Level_control\GameLevel.h"
class Level1: public GameLevel {
	float y;
	float x;
	float ySpeed;
	float xSpeed;
public:
	 Level1();
	 virtual ~Level1();
	 void Load() override;
	 void Unload() override;
	 void Render(Graphics* gfx) override;
	 void Update() override;

};


