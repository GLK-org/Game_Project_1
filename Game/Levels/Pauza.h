#pragma once
#include "Level_control\GameLevel.h"

class Pauza : public GameLevel {

public:
	void Load() override;
	void Unload() override;
	void Render(Graphics* gfx) override;
	void Update() override;

};