#pragma once
#include "Primitives.h"
#include "pch.h"
#include "Core/CoreMinimal.h"
#include "Level_control/GameController.h"
#include <vector>
#include "CoreTransforms.h"
#include "CoreLogging.h"



struct Player {


	Eli* character;
	float Deltaspeed;
	bool toggle;
	POINT targetloc;
	Player(Graphics* gfx,
		float spawnx,
		float spawny,
		float rad,
		float width,
		float height
	) {
		this->targetloc.x = -1;
		this->targetloc.y = -1;
		this->toggle = false;
		character = new Eli(spawnx, spawny, rad, width, height, gfx);
		Deltaspeed = 5.0f;
	}
	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.2f, float g = 0.0f, float b = 0.5f, float a = 1) {
		if (CheckPoint(targetloc) == false && toggle == true) {
			MoveToPoint(targetloc);
		}
		else {
			this->targetloc.x = -1;
			this->targetloc.y = -1;
			toggle = false;
		}


		if (fill) {


		}
		else {
			character->Render(gfx, r, g, b, a);
		}
	}
	bool CheckPoint(POINT& p) {
		if (targetloc.x < 0 || targetloc.y < 0) {
			return true;
		}
		//Get the anglex and angley
		//Get

		float x = character->EGetPoint(0.0f).x;
		float y = character->EGetPoint(0.0f).y;
		float temp[2] = { x,y };
		if (p.x < x && x - p.x>2.0f) {
			return false;
			//przesuñ w lewo
		}
		else if (x < p.x && p.x - x  > 2.0f) {
			return false;
			//przesuñ w prawo
		}

		if (p.y < y && y - p.y > 2.0f) {
			return false;
			//przesuñ w górê
		}
		else if (y < p.y && p.y - y  > 2.0f) {
			return false;
			//przesuñ w dó³
		}
		return true;
	}

	void MoveToPoint(POINT& p, float speed=STOP) {
		this->toggle = true;
		targetloc = p;
		D2D1_POINT_2F temp;
		temp.x = p.x;
		temp.y = p.y;
		//constraints here
		float x = character->EGetPoint(0.0f).x;
		float y = character->EGetPoint(0.0f).y;
		float angle = (float)Angle(character->EGetPoint(0.0f), character->Getpshx().vVect->v_0, temp);
		std::string temp1 = "Angle: " + std::to_string(angle)+"\n";
		OutputDebugStringA(temp1.c_str());
		if (targetloc.x < x && x - targetloc.x>2.0f) {
			character->Update(x, y);

			//przesuñ w lewo
		}
		else if (x < targetloc.x && targetloc.x - x  > 2.0f) {
			character->Update(x, y);

			//przesuñ w prawo
		}

		if (targetloc.y < y && y - targetloc.y > 2.0f) {
			character->Update(x, y);

			//przesuñ w górê
		}
		else if (y < targetloc.y && targetloc.y - y  > 2.0f) {
			character->Update(x, y);

			//przesuñ w dó³
		}

		return;

	}


};


struct Doors {
	float wait, threshold;
	Recta* left;
	Recta* right;
	GameLevel* prev;
	GameLevel* next;
public:

	Doors(Graphics* gfx, GameLevel* prev = nullptr, GameLevel* next = nullptr) {
		this->threshold = GameController::time;
		this->wait = 0;
		this->prev = prev;
		this->next = next;
		this->left = new Recta(1.0f, 300.0f, 1, 300, 100, 567, gfx);
		this->right = new Recta(1365.0f, 1.0f, 1266.0f, 300, 1365, 567, gfx);
	
	}
	//Zmiana poziomu bez udzia³u gracza
	bool UpdateTrig(POINT& p) {
		this->wait = GameController::time;

		if (wait < threshold + 3.0f) {

			return false;
		}

		if (left->CheckTrigg(p) && prev != nullptr) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) {
				GameController::SwitchLevel(prev);
				return true;
			}
		}
		if (right->CheckTrigg(p) && next != nullptr) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) {
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
		if (left->CheckTrigg(p) && prev!=nullptr) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) {
					if (lambda(player.character->EGetPoint(0.0f).x, left->GetX())) {
						GameController::SwitchLevel(prev);
						return true;
					
					}
				
			}
		}
		if (right->CheckTrigg(p) && next != nullptr) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & 0x8000) {
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
			float e[4] = { r, g, 0.1f + b, a };
			this->left->Fill(gfx, e);
		}
		else {
			this->left->Render(gfx, r, g, 0.1f + b, a);

		}
		if (right->CheckTrigg(p)) {
			float e[4] = { r, g, 0.1f + b, a };
			this->right->Fill(gfx, e);
		}
		else {
			this->right->Render(gfx, r, g, 0.1f + b, a);
		}
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