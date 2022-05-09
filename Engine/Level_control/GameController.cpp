#include "Engine.h"
#include "GameController.h"


GameLevel* GameController::currentLevel;
bool GameController::gravity = false;
bool GameController::loading;
bool GameController::paused;
bool GameController::exit = false;
float GameController::time;
float GameController::increment;
Graphics* GameController::gfx;
Writer* GameController::wrt;
GameController::~GameController()
{

}

void GameController::Init(Graphics* gfx1, Writer* wrt1)
{
	time = 0.0f;
	increment = 0.1f;
	gfx = gfx1;
	wrt = wrt1;
	loading = true;
	currentLevel = nullptr;
}

void GameController::LoadInitialLevel(GameLevel* level)
{
	loading = true;
	currentLevel = level;
	currentLevel->Load(gfx,wrt);
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

void GameController::Pause()
{
	//Do obudowania render i interakcja z pauz¹
	if (gfx == nullptr) return;
	GameController::PUpdate();
	GameController::Render(gfx);
	
}

void GameController::Play(Graphics* gfx, Writer* wrt1)
{
	if (gfx == nullptr) return;

	if(paused) {
		GameController::Pause();
	}
	else {

	
	GameController::Update();
	GameController::Render(gfx,wrt);
	}
}

void GameController::Render(Graphics* gfx, Writer* wrt1)
{

	if (loading) return;
	time += increment;
	currentLevel->Render(gfx, wrt);
}

void GameController::PUpdate()
{

}



void GameController::Update()
{

	if (loading) return;
	time += increment;
	currentLevel->Update();
}

void GameController::Unload() {
	loading = true;
	currentLevel->Unload();
	GameController::exit = true;
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);

}