#include "pch.h"
#include "Item_system.h"



Itemsys::Itemsys(Recta* spaces[4], std::vector < Item*>& _items) {
	
	for (int i = 0; i < 4;i++) {
		_spaces[i] = spaces[i]->GetRect();

	}
	previtem = nullptr;
	curritem = nullptr;
	cooldown = 0;
	combiner = false;
	ref = &_items;
};

Itemsys::~Itemsys()
{
	items.clear();
	items.~vector();

}

void Itemsys::Use()
{

	if (curritem->state == earned && curritem->state != used) {
		curritem->Use();
		curritem->state = in_use;
	}
}

int Itemsys::Combine()
{
	if (((GetPrevIt()==I_Battery) && (GetCurrentId() == I_Shield)) || ((GetCurrentId() == I_Battery) && (GetPrevIt() == I_Shield))) {
		int i = 0;
		while (i < 2) {

		
			for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
				if (((*it)->id == I_Battery) || (*it)->id == I_Shield)
					(*it)->state = used;
				
			
				break;
			}
			i++;
		}
		
		Delete(I_Battery);
		Delete(I_Shield);
		return 5;
		
	}
	return -1;
}

bool Itemsys::Add(Item* item)
{
	if (Checksize()) {
		items.push_back(item);
		item->state = earned;
		Reposition();
		return true;
	}
	return false;
}

bool Itemsys::Add(Item_list item)
{
	if (Checksize()) {
		for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if ((*it)->id == item) {
				items.push_back(new ActiveShield(( * it)));;
				items.back()->state = earned;
				Reposition();
				
				return true;
			}
			
		}
	}
	return false;
}

bool Itemsys::Checksize()
{
	if (items.size() < 4) {
		return true;
	}
	return false;
}

void Itemsys::UpdateBmps(Graphics* gfx)
{
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
		if (!((*it)->drawtarget->bmp)) {
			(*it)->LoadBmpRes(gfx);
		}
	}
}

void Itemsys::ToggleCombining()
{
	combiner = !combiner;
	previtem = curritem = nullptr;
}

int Itemsys::GetCurrentId()
{
	if (curritem==nullptr) {
		return -1;
	}

	return curritem->id;
}

Item* Itemsys::GetCurrentIt()
{
	if (curritem == nullptr) {
		return nullptr;
	}

	return curritem;
}

int Itemsys::GetPrevIt()
{
	if (previtem == nullptr) {
		return -1;
	}

	return previtem->id;
}

void Itemsys::Nxtob()
{
	previtem = curritem;

	  for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
		if ((*it)->id == curritem->id) {
			if (it++ == items.end()) {
				return;

			}

			previtem = curritem;
			curritem = *it;

		}
	}
}

void Itemsys::Prevob()
{
	previtem = curritem;

	for (std::vector<Item*>::iterator it = items.end(); it != items.begin(); it--) {
		if ((*it)->id == curritem->id) {
			if (it-- == items.begin()) {
				return;
			}

			previtem = curritem;
			curritem = *it;

		}
	}
}

void Itemsys::Delete(int id)
{
	if (id == -1) {
		return;
	}
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
		if ((*it)->id == id) {
			(*it)->taggable = false;
			items.erase(it);
			break;
		}
	}
	for (std::vector<Item*>::iterator it = ref->begin(); it != ref->end(); it++) {
		if ((*it)->id == id) {
			ref->erase(it);
			break;
		}
	}
	curritem = nullptr;
	Reposition();
}

int Itemsys::CheckTrigs(POINT& p)
{
	if (cooldown < 10) {
		cooldown+=(int)(10.0*GameController::increment);
		return -1;
	}
	
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++)
	{
		if ((GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) && (*it)->CheckTrigg(p)) {
			if ((*it) == curritem || (*it) == previtem) {
				curritem = previtem = nullptr;
				cooldown = 0;
				return -1;
			}
			previtem = curritem;
			curritem = (*it);
			cooldown = 0;
			return (*it)->id;
		}
	}
	if (curritem != nullptr) {
		return curritem->id;
	}
	return -1;
}

void Itemsys::Reposition() {
	int i = 0;

	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++)
	{
		
		(*it)->drawtarget->SetRect(_spaces[i]);
		i++;

	}

}

void Itemsys::Draw(Graphics * gfx, const POINT& p)
{
	int i=0;
	for (Item* el : items) 
	{
		gfx->Scale(D2D1_SIZE_F(0.5f, 0.8f), el->drawtarget->GetCenter());
		el->RenderBmp(gfx, 1.0f, el->drawtarget->GetRect());
	
		gfx->ClearTransforms();
		gfx->Scale(D2D1_SIZE_F(0.9f, 0.85f), el->drawtarget->GetCenter());
		if (el->CheckTrigg(p)) {
			el->drawtarget->Fill(gfx,1.0f,0.0f,0.0f,0.3f);
		}
		else if (el ==curritem) {
			el->drawtarget->Fill(gfx, 0.0f, 1.0f, 0.0f, 0.3f);
		}
		else if (el ==previtem) {
			el->drawtarget->Fill(gfx, 0.0f, 0.0f, 1.0f, 0.3f);
		}
		gfx->ClearTransforms();
		i++;
	}

}
