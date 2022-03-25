#pragma once
#include "Level_control/GameLevel.h"

class Level2 : public GameLevel {
	float y;
	float x;
	float ySpeed;
	float xSpeed;
public:
	Level2();
	virtual ~Level2();
	void Load() override;
	void Unload() override;
	void Render(Graphics* gfx) override;
	void Update() override;

};

