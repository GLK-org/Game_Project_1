#pragma once
#include "GameLevel.h"
class ENGINE_API GameController {
	GameController();
	static Graphics* gfx;
	static GameLevel* currentLevel;
	~GameController();
public:
	static bool gravity;
	static bool paused;
	static float increment;
	static float time;
	static bool loading;
	static void Init(Graphics* gfx);
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);
	static void Pause();
	static void Play(Graphics* gfx);
	static void Render(Graphics* gfx);
	static void PUpdate();
	static void Update();
};

