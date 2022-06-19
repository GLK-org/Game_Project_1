#pragma once
#include "Level_controls.h"
#include "GameController.h"
#include "windowsx.h"
#include <map>



#define Lvla 10.0f
#define Lvlb (WNDHEIGHT - 0.9 * WNDHEIGHT)
#define OFFSET 70.0f

static int lvlgoal = 11;
struct Doors1 : public Doors {


	Doors1(Graphics* gfx, GameLevel* prev = nullptr, GameLevel* next = nullptr) : Doors(gfx, prev, next) { Doors::lopen = false; Doors::ropen = false; };
	void Checkconl() {
	}
	void Checkconr(int points) {
		if (points >= lvlgoal) ropen=true;


	}
};


class Level1: public GameLevel {

	//Mysz do przeniesienia
	//EReciever reci;
	//lvl1Ev ev;
	
	
	float floorx, floory;
	char id = '1';
	float y, x;
	float ySpeed, xSpeed;
	int points;
	bool asc, mode;
	double r, g, b, a, change;


	Player* player;
    Ball* eli;
	Inanimate* buttons[3];
	Inanimate* controller;
	Graphics* gfx;
	Inanimate* bg;
	Panel* panel;
	Doors1* doors;
	FloatingText* text;
	std::vector<Obj*> goal;
	std::vector<Inanimate*> list;
	std::map<std::string, D2D1_RECT_F> text_boxes;
	D2D1_POINT_2F postab[6];

	
	

public:
	 Level1();
	 virtual ~Level1();
	 char GetID() override;
	 void Load(Graphics* gfx, Writer* wrt = nullptr) override;
	 void AddObj(SHORT key=0) override;
	 void Unload() override;
	 void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr) override;
	 void Update() override;
};


