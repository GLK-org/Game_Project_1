#pragma once
#include "Obj.h"
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
	 void Load(Graphics* gfx);
	 char GetID();
	 void Unload();
	 void AddObj(SHORT key = 0);
	 void Render(Graphics* gfx = nullptr);
	 void Update();
};