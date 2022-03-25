#pragma once
#include "GameLevel.h"
class ENGINE_API GameController {

	
	GameController();
	static GameLevel* currentLevel;
	~GameController();
public:
	
	static bool loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);
	static void Render(Graphics* gfx);
	static void Update();
};