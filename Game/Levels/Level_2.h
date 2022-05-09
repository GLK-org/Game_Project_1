#pragma once
#include "Level_control\GameLevel.h"
#include "Level_controls.h"
#include <vector>
#include "Primitives.h"
#include <ctime>
#include <math.h>
#include <numbers>
#include <stdio.h>
#define _USE_MATH_DEFINES



class Level2 : public GameLevel {
	//EReciever reciever;

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
	void Load(Graphics* gfx=nullptr, Writer* wrt = nullptr) override;
	char GetID() override;
	void AddObj(SHORT key=0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr) override;
	void Update() override;

};

