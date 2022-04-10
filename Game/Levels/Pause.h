#pragma once
#include "Level_control\GameLevel.h"
#include "Primitives.h"
#include  <vector>

class PauseCl : GameLevel {
	struct with {
		Obj* ob;
		bool fill;
		with(Recta* rec) {
			ob = rec;
			fill = false;
		}
		bool GSfill(bool cfill = false) { if (cfill) { fill = !fill; } return fill; };
	};
	std::vector<with*> buttons;
	

public:
	 void Load(Graphics* gfx) override;
	 char GetID() override;
	 void Unload() override;
	 void AddObj(SHORT key = 0) override;
	 void Render(Graphics* gfx = nullptr) override;
	 void Update() override;
};