#pragma once
#include "Level_control\GameLevel.h"
class Level1: public GameLevel {
	char id = '1';
	float y;
	float x;
	float ySpeed;
	float xSpeed;
public:
	 Level1();
	 virtual ~Level1();
	 char GetID();
	 void Load(Graphics* gfx) override;
	 void Unload() override;
	 void Render(Graphics* gfx) override;
	 void Update() override;

};


