#pragma once
#include "Game_controller\GameLevel.h"
#include "Level_controls.h"
#include "Obj.h"

class Level6 : public GameLevel {
	//Mysz do przeniesienia

	char id = '6';
	Doors* doors;
	Player* player;
	double r, g, b, a;
public:
	Level6();
	virtual ~Level6();
	char GetID() override;
	void Load(Graphics* gfx, Writer* wrt=nullptr) override;
	void AddObj(SHORT key = 0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr) override;
	void Update() override;
};