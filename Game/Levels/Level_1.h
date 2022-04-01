#pragma once
#include "Level_control\GameLevel.h"
#include "Obj.h"
class Level1: public GameLevel {
	//Mysz do przeniesienia
	
	char id = '1';
    Obj* eli;
	Obj* buttons[2];
	float y;
	float x;
	float ySpeed;
	float xSpeed;
	POINT p;
	bool mode;
	double change;
	bool asc;
	double r, g, b, a;
public:
	 Level1();
	 virtual ~Level1();
	 char GetID() override;
	 void Load(Graphics* gfx) override;
	 void AddObj(SHORT key=0) override;
	 void Unload() override;
	 void Render(Graphics* gfx = nullptr) override;
	 void Update() override;

};


