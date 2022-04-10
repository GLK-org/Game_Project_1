#pragma once
#include "Level_control\GameLevel.h"
#include "Primitives.h"
#include "Level_controls.h"

class Level4 : public GameLevel {
	//Mysz do przeniesienia

	char id = '4';
	Doors* doors;
	Eli* eli;
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