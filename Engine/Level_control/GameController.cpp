#include "Engine.h"
#include "GameController.h"


GameLevel* GameController::currentLevel;
bool GameController::loading;
float GameController::time;
float GameController::increment;

Graphics* GameController::gfx;
GameController::~GameController()
{
}

void GameController::Init(Graphics* gfx1)
{
	time = 0.0f;
	increment = 0.1f;
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
	time += increment;
	currentLevel->Render(gfx);
}



void GameController::Update()
{

	if (loading) return;
	time += increment;
	currentLevel->Update();
}