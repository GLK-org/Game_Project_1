#pragma once
#include "Level_control\GameLevel.h"
#include "Level_controls.h"
#include "Obj.h"

class Level5 : public GameLevel {
	//Mysz do przeniesienia

	char id = '5';
	Doors* doors;
	double r, g, b, a;
public:
	Level5();
	virtual ~Level5();
	char GetID() override;
	void Load(Graphics* gfx, Writer* wrt = nullptr) override;
	void AddObj(SHORT key = 0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr) override;
	void Update() override;
};