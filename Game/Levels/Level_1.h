#pragma once
#include "Level_control\GameLevel.h"
#include "Level_controls.h"
#include "Primitives.h"
#include <vector>
struct Doors1 : public Doors {


	Doors1(Graphics* gfx, GameLevel* prev = nullptr, GameLevel* next = nullptr) : Doors(gfx, prev, next) { Doors::lopen = false; Doors::ropen = false; };
	void Checkconl() {

	}
	void Checkconr(int points) {
		if (points > 10) ropen=true;

	}
};

class Level1: public GameLevel {
	//Mysz do przeniesienia
	//EReciever reci;
	//lvl1Ev ev;
	Player* player;
	float floorx, floory, width, height;
	char id = '1';
    Eli* eli;
	std::vector<Obj*> goal;
	Obj* buttons[2];
	Doors1* doors;
	float y;
	float x;
	float ySpeed;
	float xSpeed;
	int points;
	bool mode;
	double change;
	bool asc;
	double r, g, b, a;
	D2D1_POINT_2F postab[6];
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


