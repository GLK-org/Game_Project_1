#pragma once
#include "GameLevel.h"
#include <chrono>
class ENGINE_API GameController {
	
	
	static GameLevel* currentLevel;
	static GameLevel* previousLevel;
	static GameLevel* menu;
	static float cooldown;
	GameController();
	~GameController();
public:
	static Graphics* gfx;
	static Writer* wrt;
	static AudioController* audioc;
	static bool exit;
	static bool gravity;
	static bool paused;
	static float increment;
	static std::chrono::steady_clock::time_point start;
	static std::time_t tp;
	static float time;
	static float frametime;
	static bool loading;
	

	static void Init(Graphics* gfx, Writer* wrt,AudioController*audioc1);
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);
	static void Play(Graphics* gfx, Writer* wrt , GameLevel* level = nullptr);
	static void Play(Graphics* gfx);
	static void Render(Graphics* gfx, Writer* wrt=nullptr);
	static void Update();
	static void Unload();
	static bool PressButton(char c, bool immediate=false);
	static void Transition();
	static HRESULT ReplayAudio();
};

