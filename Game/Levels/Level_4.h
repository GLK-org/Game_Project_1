#pragma once
#include "Level_control\GameLevel.h"
#include "Level_controls.h"
#include "Obj.h"

class Level4 : public GameLevel {
	//Mysz do przeniesienia

	char id = '4';
	Doors* doors;
	double r, g, b, a;
public:
	Level4();
	virtual ~Level4();
	char GetID() override;
	void Load(Graphics* gfx) override;
	void AddObj(SHORT key = 0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr) override;
	void Update() override;
};