#pragma once
#include "GameController.h"
#include "Level_controls.h"
#include "windowsx.h"

#define BUTTON_START_LOC (WNDWIDTH * 3 / 4.0f), (WNDHEIGHT * 67 / 100.0f)
#define SQUARE_START_LOC WNDWIDTH  / 4.0f, WNDHEIGHT * 57 / 100.0f
#define RECT_START_LOC WNDWIDTH * 3 / 4.0f, WNDHEIGHT * 20 / 100.0f
#define PLAYER_START_LOC WNDWIDTH / 4, WNDHEIGHT *56/100
class Level3 : public GameLevel {
	//Mysz do przeniesienia

	
	char id = '3';
	bool mode;
	double change;
	bool asc;
	double r, g, b, a;

	Graphics* gfx;
	Player* player;
	Doors* doors;
	Inanimate* bg;
	Panel* panel;
	Itemsys *inventory;
	BaseUnknown* target;
	FloatingText* floater;
	std::vector<Inanimate*> map_el;
	std::vector<BaseUnknown*> list;
	std::vector<Animate*> anim_map_el;
	std::vector<Item*> collectibles;
	std::vector<Ball*> flock;
	bool grav;

	

public:

	Level3();
	virtual ~Level3();
	char GetID() override;
	void Load(Graphics* gfx, Writer* wrt = nullptr) override;
	void AddObj(SHORT key = 0) override;
	void Unload() override;
	void Render(Graphics* gfx = nullptr, Writer* wrt = nullptr) override;
	void Update() override;

};


