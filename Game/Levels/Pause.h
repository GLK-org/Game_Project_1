#pragma once
//#include "..\Engine\Level_control\GameController.h"
#include "GameLevel.h"
#include "Level_controls.h"
#include "Level_includes.h"
#include <map>

struct Buttonsp : public BaseButton {
	int id;
	Buttonsp(Obj* ob, float r, float g, float b, float a, int id = -1, std::string text = "0") : BaseButton(ob, r, g, b, a, text) {
		this->id = id;
	};
	virtual ~Buttonsp() {};

	void OnTrig() override {
		if (id == 0) {

			GameController::SwitchLevel(new Level1());

		}
		else if (id == 1) {


		}
		else if (id == 2) {
			GameController::Unload();

		}
		else {

		}


	};

};


class PauseCl : public GameLevel {

	std::vector<Buttonsp*> buttons;
	std::map<std::string, D2D1_RECT_F> text_boxes;

public:
	 void Load(Graphics* gfx, Writer* wrt=nullptr) override;
	 char GetID() override;
	 void Unload() override;
	 void AddObj(SHORT key = 0) override;
	 void Render(Graphics* gfx = nullptr, Writer* wrt=nullptr) override;
	 void Update() override;
};