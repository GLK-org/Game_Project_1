#pragma once
#include "Level_control\GameLevel.h"
#include "Level_controls.h"
#include "Obj.h"

class Level6 : public GameLevel {
	//Mysz do przeniesienia

	char id = '6';
	Doors* doors;
	double r, g, b, a;
public:
	Level6();
	virtual ~Level6();
	char GetID() override;
	void Load(Graphics* gfx) override;
	void AddObj(SHORT key = 0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr) override;
	void Update() override;
};