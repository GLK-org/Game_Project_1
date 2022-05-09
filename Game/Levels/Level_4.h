#pragma once
#include "Level_control\GameLevel.h"
#include "Primitives.h"
#include "Level_controls.h"
#include <vector>

class Level4 : public GameLevel {
	//Mysz do przeniesienia
	std::vector<Obj*> ammo;
	float limits[3][3][3];
	char id = '4';
	Doors* doors;
	Player* player;
	Eli* eli;
	double r, g, b, a;
public:
	Level4();
	virtual ~Level4();
	char GetID() override;
	void Load(Graphics* gfx, Writer* wrt = nullptr) override;
	void AddObj(SHORT key = 0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr) override;
	void Update() override;
};