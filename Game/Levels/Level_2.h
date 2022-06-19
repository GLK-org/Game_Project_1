#pragma once
#include "Level_controls.h"
#include "GameController.h"
#include "../Game/Item_system/Item_system.h"
#include <ctime>
#include "Sources\IEvSource.h"
#define _USE_MATH_DEFINES

struct Doors2 : public Doors {

	bool crafted;
	Doors2(Graphics* gfx, GameLevel* prev = nullptr, GameLevel* next = nullptr) : Doors(gfx, prev, next) { Doors::lopen = false; Doors::ropen = false; crafted = false; };
	void Checkconl() {
	}
	void Checkconr() {
		if (crafted) {
			ropen = true;
		}


	}
};

class Level2 : public GameLevel {
	//EReciever reciever;

	bool inc;
	char id = '2';
	float r, g, b;
	float y, x;
	float ySpeed, xSpeed;
	float wind;
	float cooldown;
	std::string basictxt;
	
	Graphics* gfx;
	Doors2* doors;
	Player* pl;
	Inanimate* bg;
	Panel* panel;
	FloatingText* floater;
	Itemsys* inventory;
	Inanimate* map_el[4];
	VoiceCallback vc;
	IXAudio2SourceVoice* snd;
	XAUDIO2_BUFFER buff;
	CSource src;
	CReceiver rec;

	std::vector<Obj*> objects;
	std::vector<Item*> collectibles;

public:
	void Load(Graphics* gfx=nullptr, Writer* wrt = nullptr) override;
	char GetID() override;
	void AddObj(SHORT key=0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr) override;
	void Update() override;

};

