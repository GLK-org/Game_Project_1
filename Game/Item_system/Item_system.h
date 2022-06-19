#pragma once
#include "Items.h"


enum Item_list {
	I_Battery = 1, I_Gyro = 2, I_Launcher = 3, I_Shield = 4, I_ActiveShield = 5, I_Keycard = 6
};

const Objs CombineTab[1][2]{ {Obj1, Obj2} };

class Itemsys {
public:

	Item* curritem;
	Item* previtem;
	std::vector<Item*> items;
	std::vector<Item*>* ref;
	D2D1_RECT_F _spaces[4];
	int cooldown;
	bool combiner;
	Itemsys(Recta* spaces[4], std::vector < Item*>& _items);
	virtual ~Itemsys();

	void Use();
	int Combine();
	bool Add(Item* item);
	bool Add(Item_list item);
	bool Checkstate(const Item* it);
	bool Checksize();
	void UpdateBmps(Graphics * gfx);
	void ToggleCombining();
	int GetCurrentId();
	Item* GetCurrentIt();
	int GetPrevIt();
	void Nxtob();
	void Prevob();
	void Delete(int id);
	void Delete();
	int CheckTrigs(POINT& p);
	void Draw(Graphics* gfx, const POINT & p);
	void Reposition();

};