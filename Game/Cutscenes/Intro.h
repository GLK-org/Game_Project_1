#pragma once
#include "Gamelevel.h"

#include "Converter.h"
#include ".\Event_system\Sources\Cutscene_controller.h"


class Intro : public GameLevel {

public:
	int next;
	int cooldown = 0.0f;
	std::vector<Inanimate*> panels;
	Cutscene_rec rec;
	Cutscene_src src;
    void Load(Graphics* gfx, Writer* wrt = nullptr) override {


		for (int i = 128; i < 132; i++) {

			panels.push_back(new Inanimate(gfx, WNDWIDTH / 2.0f, WNDHEIGHT / 2.0f, WNDWIDTH / 3.0f, WNDHEIGHT / 3.0f, i));
			next = 0;
		};
		rec.hookEvent(&src);
	};
	char GetID() override { return '- 2'; };
	void Unload()  override {};
	void AddObj(SHORT key = 0) override {};
	void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr)  override {
		cooldown++;
		if (next > 3) {
			GameController::SwitchLevel(new Level1());
			return;
		}
		else {
			gfx->ClearScreen(1.0f, 1.0f, 1.0f, 1.0f);
				panels[next]->RenderBmpBG(gfx, 1.0f);
			

			if (GameController::PressButton(RI_MOUSE_LEFT_BUTTON_DOWN) && cooldown >= 20) {
				__raise src.OnTrigger(next);

			}
		}
			
			
			
		
	
	};
	void Update() override {};
};