#include "GameController.h"
#include "Engine.h"

GameLevel* GameController::currentLevel;
bool GameController::loading;

void GameController::Init()
{
	loading = true;
	currentLevel = nullptr;
}

void GameController::LoadInitialLevel(GameLevel* level)
{
	loading = true;
	currentLevel = level;
	currentLevel->Load();
	loading = false;

}

void GameController::SwitchLevel(GameLevel* level)
{
	loading = true;
	currentLevel->Unload();
	delete currentLevel;
	currentLevel = level;
	currentLevel->Load();
	loading = false;
}

void GameController::Render(Graphics* gfx)
{
	if (loading) return;
	currentLevel->Render(gfx);
}

void GameController::Update()
{
	currentLevel->Update();
}