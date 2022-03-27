#include "Engine.h"
#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::loading;
Graphics* GameController::gfx;
GameController::~GameController()
{
}

void GameController::Init(Graphics* gfx1)
{
	gfx = gfx1;
	loading = true;
	currentLevel = nullptr;
}

void GameController::LoadInitialLevel(GameLevel* level)
{
	loading = true;
	currentLevel = level;
	currentLevel->Load(gfx);
	loading = false;

}

void GameController::SwitchLevel(GameLevel* level)
{
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

void GameController::Render(Graphics* gfx)
{
	if (loading) return;
	currentLevel->Render(gfx);
}



void GameController::Update()
{
	currentLevel->Update();
}