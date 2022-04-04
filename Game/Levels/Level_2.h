#pragma once
#include "Level_control\GameLevel.h"
#include "Level_controls.h"
#include <vector>
#include "Obj.h"
#include <ctime>
#include <math.h>
#include <numbers>
#define _USE_MATH_DEFINES

class Level2 : public GameLevel {
	bool inc;
	char id = '2';
	std::vector<Obj*> objects;
	Graphics* gfx;
	Doors* doors;
	float r, g, b;
	float y, x;
	float ySpeed, xSpeed;
	double wind;
public:
	void Load(Graphics* gfx=nullptr) override;
	char GetID() override;
	void AddObj(SHORT key=0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr) override;
	void Update() override;

};

