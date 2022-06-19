#pragma once
#include "Engine.h"
#include "GameController.h"
#include "E:\VS_projects\Game_engine_1\resources\resource.h"

GameLevel* GameController::currentLevel;
GameLevel* GameController::previousLevel;
GameLevel* GameController::menu;
AudioController* GameController::audioc;
XAUDIO2_VOICE_STATE state;
bool GameController::gravity = false;
bool GameController::loading;
bool GameController::paused;
bool GameController::exit = false;
float GameController::time;
std::chrono::steady_clock::time_point GameController::start;
std::time_t GameController::tp;
float GameController::increment;
float GameController::frametime = 16.6f;
float GameController::cooldown=0.0f;
Graphics* GameController::gfx;
Writer* GameController::wrt;

void GameController::Init(Graphics* gfx1, Writer* wrt1,AudioController * audioc1)
{
	start = std::chrono::steady_clock::now();
	increment = 0.1f;
	gfx = gfx1;
	wrt = wrt1;
	audioc = audioc1;
	loading = true;
	currentLevel = nullptr;
	audioc->PlaySimple("Game.exe",IDR_WAVE3);
}

void GameController::LoadInitialLevel(GameLevel* level)
{
	loading = true;
	menu = level;
	currentLevel = level;
	currentLevel->Load(gfx,wrt);
	loading = false;

}

void GameController::SwitchLevel(GameLevel* level)
{
	cooldown += increment;
	time += increment;
	Transition();
	loading = true;
	if (level->GetID() == currentLevel->GetID()) {
		loading = false;
		return;
	}

	
	currentLevel->Unload();
	delete currentLevel;
	currentLevel = level;
	currentLevel->Load(gfx);
	loading = false;
}

void GameController::Play(Graphics* gfx)
{

	if (gfx == nullptr) return;
	GameController::Update();
	GameController::Render(gfx, wrt);
}

void GameController::Play(Graphics* gfx, Writer* wrt1, GameLevel * level)
{

	if (gfx == nullptr) return;

	if (paused && currentLevel->GetID()!=-1) {
		previousLevel = currentLevel;
		currentLevel = level;
		level->Load(gfx,wrt1);
	}
	else {
		if (previousLevel != nullptr) {
			currentLevel->Unload();
			delete currentLevel;
			currentLevel = previousLevel;
			previousLevel = nullptr;

		}

		GameController::Update();
		GameController::Render(gfx, wrt);
	}
	GameController::Update();
	GameController::Render(gfx, wrt);
}

void GameController::Render(Graphics* gfx, Writer* wrt1)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	float frame = 0;
	
	if (loading) return;
	cooldown += increment;
	time += increment;
	
	currentLevel->Render(gfx, wrt);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	using FpMilliseconds =
		std::chrono::duration<float, std::chrono::milliseconds::period>;
	auto f_diff = FpMilliseconds(end - start);
	while (f_diff < std::chrono::milliseconds(166)) {
		f_diff++;
	}
}

void GameController::Update()
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	float frame = 0;
	if (loading) return;
	cooldown += increment;
	time += increment;
	currentLevel->Update();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	using FpMilliseconds =
		std::chrono::duration<float, std::chrono::milliseconds::period>;
	auto f_diff = FpMilliseconds(end - start);
	//GameController::ReplayAudio();
	while (f_diff < std::chrono::milliseconds(166)) {
		f_diff++;
	}
}

void GameController::Unload() {
	loading = true;
	currentLevel->Unload();
	GameController::exit = true;

}

bool GameController::PressButton(char c, bool immediate)
{

	if (immediate) {
		if (GetKeyState(c) & 0x8000) {
			cooldown = 0.0f;
			return true;

		}
	}
	if (cooldown > 3.0f) {
		if (GetKeyState(c) & 0x8000) {
			cooldown = 0.0f;
			return true;
			
		}
		
	}
	return false;
}

void GameController::Transition() {
	cooldown += increment;
	time += increment;
	for (int i = 0; i < 10; i++) {
		gfx->DrawBg();
		gfx->ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);
		gfx->StopDrawBg();
	}
	
}

HRESULT GameController::ReplayAudio()
{
	if(WaitForSingleObjectEx(audioc->GetCallback().hBufferEnd, 10, TRUE));
	return E_NOTIMPL;
}
