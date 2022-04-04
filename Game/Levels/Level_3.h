#pragma once
#include "Level_control\GameLevel.h"
#include "Obj.h"
class Level3 : public GameLevel {
	//Mysz do przeniesienia

	char id = '3';
	Obj* eli;
	Recta* rect;
	Recta* left;
	Recta* right;
	//Obj* buttons;
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
	Level3();
	virtual ~Level3();
	char GetID() override;
	void Load(Graphics* gfx) override;
	void AddObj(SHORT key = 0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr) override;
	void Update() override;

};


