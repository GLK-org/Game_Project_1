#pragma once
#include "GameLevel.h"
class ENGINE_API GameController {
	GameController();
	static Graphics* gfx;
	static Writer* wrt;
	static GameLevel* currentLevel;
	
	~GameController();
public:
	static bool exit;
	static bool gravity;
	static bool paused;
	static float increment;
	static float time;
	static bool loading;
	static void Init(Graphics* gfx, Writer* wrt);
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);
	static void Pause();
	static void Play(Graphics* gfx, Writer* wrt=nullptr);
	static void Render(Graphics* gfx, Writer* wrt=nullptr);
	static void PUpdate();
	static void Update();
	static void Unload();
};

