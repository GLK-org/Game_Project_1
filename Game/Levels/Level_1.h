#pragma once
#include "Level_control/GameLevel.h"
#include "Core/CoreMinimal.h"

class Level1: public GameLevel {
	float y;
	float x;
	float ySpeed;
	float xSpeed;
	Graphics* gtx;
public:

	 void Load() override;
	 void Unload() override;
	 void Render(Graphics* gfx) override;
	 void Update() override;

};


