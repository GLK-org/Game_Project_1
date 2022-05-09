#pragma once
#include "Level_control\GameLevel.h"
#include "Level_controls.h"
#include "Primitives.h"
class Level3 : public GameLevel {
	//Mysz do przeniesienia

	char id = '3';
	Obj* eli;
	Player* player;
	Recta* rect;
	Doors* doors;
	//Obj* buttons;
	float y;
	float x;
	float ySpeed;
	float xSpeed;
	bool mode;
	double change;
	bool asc;
	double r, g, b, a;
public:

	Level3();
	virtual ~Level3();
	char GetID() override;
	void Load(Graphics* gfx, Writer* wrt = nullptr) override;
	void AddObj(SHORT key = 0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr) override;
	void Update() override;

};


