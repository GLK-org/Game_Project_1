#pragma once
#include "Primitives.h"
#include "pch.h"
#include "Core/CoreMinimal.h"
#include "Level_control/GameController.h"
#include <vector>
#include "CoreTransforms.h"
#include "CoreLogging.h"
#include "CoreWriter.h"


struct Player {

    int speed;
	Eli* character;
	POINT targetloc;
	Player(Graphics* gfx,
		float spawnx,
		float spawny,
		float rad,
		float width,
		float height
	) {
		this->speed = 0;
		character = new Eli(spawnx, spawny, rad, width, height, gfx);
		this->targetloc.x = spawnx;
		this->targetloc.y = spawny;
	}
	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.2f, float g = 0.5f, float b = 0.5f, float a = 1) {
		character->ttl += GameController::increment;

		if (fill) {


		}
		else {

			character->Render(gfx, r, g, b, a);

		}
	}
	bool CheckPoint() {

		float x = character->EGetPoint(0.0f).x;
		float y = character->EGetPoint(0.0f).y;

		if (targetloc.x < x && x - targetloc.x>2.0f) {
			return false;
			//przesuñ w lewo
		}
		else if (x < targetloc.x && targetloc.x - x  > 2.0f) {
			return false;
			//przesuñ w prawo
		}

		if (targetloc.y < y && y - targetloc.y > 2.0f) {
			return false;
			//przesuñ w górê
		}
		else if (y < targetloc.y && targetloc.y - y  > 2.0f) {
			return false;
			//przesuñ w dó³
		}
		return true;
	}
	void SetPoint(POINT& p) {
		targetloc = p;

	}
	void MoveToPoint(POINT& p, float speed=STOP) {
		//constraints here
		float x = character->EGetPoint(0.0f).x;
		float y = character->EGetPoint(0.0f).y;
		
		if (targetloc.x < x && x - targetloc.x>2.0f) {
			if (x-targetloc.x < 2.0f) {
				character->Update(x-targetloc.x, 0.0f);
				return;
			}
			character->Update(-speed,0.0f);

			//przesuñ w lewo
		}
		else if (x < targetloc.x && targetloc.x - x  > 2.0f) {
			if (targetloc.x - x < 2.0f) {
				character->Update(x - targetloc.x, 0.0f);
				return;
			}
			character->Update(speed,0.0f);

			//przesuñ w prawo
		}
		
		if (targetloc.y < y && y - targetloc.y > 2.0f) {
			if (y - targetloc.y < 2.0f && y - targetloc.y > 0.0f) {
				character->Update(0.0f, -(y - targetloc.y));
				return;
			}
			character->Update(0.0f,-speed);

			//przesuñ w górê
		}
		else if (y < targetloc.y && targetloc.y - y  > 2.0f) {
			if (y - targetloc.y < 2.0f && y - targetloc.y > 0.0f) {
				character->Update(0.0f, targetloc.y-y);
				return;
			}
			character->Update(0.0f,speed);

			//przesuñ w dó³
		}
		return;

	}
	void Move(POINT& p, float speed, float limit[2][2] = {0}) {
		if (limit != nullptr) {
			if (p.x >= limit[0][0] && p.x <= limit[1][0]) {
				if (p.y >= limit[0][1] && p.y <= limit[1][1]) {


					if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
						this->SetPoint(p);
						this->speed++;
						this->speed %= 5;
					}
				}
			}
		}
		else {

			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
				this->SetPoint(p);
				this->speed++;
				this->speed %= 5;
			}
		
		}
		
		if (this->CheckPoint() == false) {
			switch(this->speed) {
				case 0: {
					this->MoveToPoint(p, STOP);
					return;
				}
				case 1: {
					this->MoveToPoint(p, SLOW);
					return;
				}
				case 2: {
					this->MoveToPoint(p, MEDIUM_FAST);
					return;
				}
				case 3: {
					this->MoveToPoint(p, FAST);
					return;
				}
				case 4: {
					this->MoveToPoint(p, VERY_FAST);
					return;
				}
				
			}
			this->speed = 0;
		}
		else {
		//	this->character->Getpshx().ClearSpeed();
		}
	}
	~Player() {
		delete character;
	}
};


struct Doors {
	//Obiekt zdarzenia do kontroli blokady drzwi
	float wait, threshold;
	bool lopen, ropen;
	float y=500;
	Recta* left;
	Recta* right;
	GameLevel* prev;
	GameLevel* next;
public:

	Doors(Graphics* gfx, GameLevel* prev = nullptr, GameLevel* next = nullptr) {
		this->threshold = GameController::time;
		this->lopen = this->ropen = true;
		this->wait = 0;
		this->prev = prev;
		this->next = next;
		this->left = new Recta(50.0f, y, 100.0f, 267.0f, gfx,false);
		this->right = new Recta(1316.0f,y, 100.0f, 267.0f, gfx,false);
	
	}
	//Zmiana poziomu bez udzia³u gracza
	bool UpdateTrig(POINT& p) {
		this->wait = GameController::time;

		if (wait < threshold + 3.0f) {

			return false;
		}

		if (left->CheckTrigg(p) && prev != nullptr && lopen==true) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
				GameController::SwitchLevel(prev);
				return true;
			}
		}
		if (right->CheckTrigg(p) && next != nullptr && ropen == true) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
				GameController::SwitchLevel(next);
				return true;
			}
		}
		return false;
	}
	//Zmiana poziomu z potrzeb¹ zbli¿enia siê postaci gracza do "drzwi"
	bool UpdateTrig(POINT& p, const Player& player) {
		this->wait = GameController::time;

		auto lambda = [](float big, float smal) {
			
			if (big - smal <= 100.0f && big - smal > 0.0f) {
				return true;
			}
			return false;
		};

		if (wait<threshold+3.0f) {

			return false;
		}
		if (left->CheckTrigg(p) && prev!=nullptr && lopen == true) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
					if (lambda(player.character->EGetPoint(0.0f).x, left->GetX())) {
						GameController::SwitchLevel(prev);
						return true;
					
					}
				
			}
		}
		if (right->CheckTrigg(p) && next != nullptr && ropen == true) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
					if (lambda(right->GetX(), player.character->EGetPoint(0.0f).x) ) {
						GameController::SwitchLevel(next);
						return true;
					}
				
			}
		}
		return false;
	}
	void Render(Graphics* gfx, POINT& p, float r, float g, float b, float a) {

		if (left->CheckTrigg(p)) {
			float b[4];
			if (lopen) {
				 float e[4] = { 0.2f, 0.4f, 0.7f , a };
				 for (int i : e) {
					 b[i] = e[i];
				 }
			}
			else {
				float e[4] = { r, g, 0.1f, a };
				for (int i : e) {
					b[i] = e[i];
				}
				 
			}
			this->left->Fill(gfx, b);
		}
		else {
			this->left->Render(gfx, r, g, 0.1f + b, a);

		}
		if (right->CheckTrigg(p)) {
			float b[4];
			if (ropen) {
				float e[4] = { 0.2f, 0.4f, 0.7f , a };
				for (int i : e) {
					b[i] = e[i];
				}
			}
			else {
				float e[4] = { r, g, 0.1f, a };
				for (int i : e) {
					b[i] = e[i];
				}
			}
			
			this->right->Fill(gfx, b);
		}
		else {
			this->right->Render(gfx, r, g, 0.1f + b, a);
		}
	}
	~Doors(){
		delete left,right;
		prev = nullptr;
		next = nullptr;
		delete prev, next;
	}
};


class Interactibles {
	struct El {
		Obj* ob;
		float ttl;
		float r, g, b, a;
		El() {
			ttl = 0;
			r = g = b = 0;
			a = 1.0f;

		}
		void Update() {
		//	ob->Update();
			ttl += 0.1f;
		}
	};

	std::vector <El* > objs;

public:

	Interactibles(){

	}
	void Render(Graphics* gfx, float r, float g, float b, float a) {
		for (std::vector<El*>::iterator it = objs.begin(); it != objs.end(); ++it) {
			(*it)->ob->Render(gfx,r,g,b,a);
		}
	
	};
	~Interactibles() {
	};


};

class BaseButton {
public:
	Obj* ob;
	float r, g, b, a;
	std::string text;
	BaseButton(Obj* ob, float r, float g, float b, float a, std::string text = "0") {
		this->ob = ob;
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->text = text;
	
	};
	virtual ~BaseButton() { delete ob; };
	void Render(Graphics* gfx, float r, float g, float b, float a, bool wtext = false, Writer* wrt = {0}, bool colorable=false)
	{
		if (colorable == true) {
			if (ob->GetTrig()) {
				float e[4] = { r + 0.1f, g + 0.5f, b + 0.1f, a };
				ob->Fill(gfx, e);
			}
			else {
				ob->Render(gfx, r, g, b, a);
				float e[4] = { r + 0.4f, g + 0.2f, b + 0.2f, a };
				ob->Fill(gfx, e);
			}
		}
		else {
			ob->Render(gfx, r, g, b, a);
			float e[4] = { r-0.4f, g+0.2f, b+0.2f, a };
			ob->Fill(gfx,e);
		}
		
		if (wtext == true) {
			D2D1_RECT_F container(
								ob->GetX()- ob->GetX() /2,
								ob->GetY() - ob->GetY() / 2,
								ob->GetX() + ob->GetX() / 2,
								ob->GetY() + ob->GetY() / 2
								);
			wrt->Draw_Text(text, container);
		};
	}
	bool CheckTrg(POINT& p) { return ob->CheckTrigg(p); };
	virtual void OnTrig() =0;


};