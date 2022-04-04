#pragma once
#include "GameLevel.h"
class ENGINE_API GameController {
	GameController();
	static Graphics* gfx;
	static GameLevel* currentLevel;
	
	~GameController();
public:
	static bool loading;
	static void Init(Graphics* gfx);
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);
	static void Render(Graphics* gfx);
	static void Update();
};

