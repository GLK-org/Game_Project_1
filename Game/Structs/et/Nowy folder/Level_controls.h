#pragma once
#include "Primitives.h"
#include "pch.h"
#include "Core/CoreMinimal.h"
#include "Level_controller/GameController.h"
#include <vector>
#include "CoreTransforms.h"
#include "CoreLogging.h"
#include "CoreWriter.h"


#define CENTER_Y ((WNDHEIGHT*7)/8- WNDHEIGHT/100)
#define CENTER_X ((WNDWIDTH*3)/4)
#define WIDTH_ITEM ((WNDWIDTH + WNDWIDTH / 8 )/2-WNDWIDTH/12)
#define HEIGHT_ITEM (WNDHEIGHT / 4)

enum Objs {
	nl,
	Obj1,
	Obj2

};


enum States {
	not_earned,
	earned,
	in_use,
	used
};

class BaseUnknown {
public:
	float frametime;
	int frame = 0;
	Speed spd;
	std::string name;
	bool taggable;
	BaseUnknown(std::string n="NULL", bool tag=false) {
		name = n;
		frametime = 0;
		frame = 0;
		spd=F_FAST;
		taggable = tag;

	}
	void SetSpd(Speed spd) {
		this->spd = spd;
	};
};

struct Player : public BaseUnknown {
	
    int speed;
	Recta* character;
	POINT targetloc;
	Player(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height
	) : BaseUnknown("Player") {
		this->speed = 0;
		character = new Recta(spawnx, spawny, width, height, gfx);
		this->targetloc.x = spawnx;
		this->targetloc.y = spawny;
		LoadBmp(gfx);
		
	}
	virtual ~Player() {
		delete character;
	}

	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1) {
		character->ttl += GameController::increment;

		if (fill) {


		}
		else {

			character->Render(gfx, r, g, b, a);

		}
	}
	
	void RenderBmp(Graphics* gfx,
		FLOAT opacity,
		bool anim = false) {
		int i, j = 0;
		frametime =frametime+ GameController::increment;
		if (character->bmp != nullptr) {

		
		D2D1_RECT_F teet = D2D1::RectF(
			character->GetRect().left,
			character->GetRect().top-100,
			character->GetRect().right,
			character->GetRect().bottom-100);

		
		

	
		if (speed != STOP) {
			switch (frame) {
			case 0:
				i, j = 0;
			case 1:
				i = 1;
				j = 0;
				break;
			case 2:
				i = 0;
				j = 1;
				break;
			case 3:
				i = 1;
				j = 1;
				break;
			default:

				break;

			}
			if (this->character->direction == LEFT) {

				gfx->Mirror(character->GetCenter());
				gfx->Drawbmp(character->bmp, teet, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0 + 512 * i, 0 + 512 * j, 512 + 512 * i, 512 + 512 * j), frame,frametime,spd, anim);

				gfx->ClearTransforms();
			}
			else {
				gfx->Drawbmp(character->bmp, teet, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0 + 512 * i, 0 + 512 * j, 512 + 512 * i, 512 + 512 * j), frame, frametime, spd, anim);

			}
			if (frametime>1.0f) {
			frame = (frame + 1) % 4;
			frametime = 0;
			}
			return;
		}
		else {
			gfx->Drawbmp(character->bmp, teet, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, 512, 512), frame, frametime, spd, anim);


		}
		
		}
	}


	void RenderSpecialBmp(Graphics* gfx,
		FLOAT opacity, std::wstring name,
		bool anim = false) {
		frametime = frametime + GameController::increment;
		if (character->actionbmp != nullptr) {


			D2D1_RECT_F teet = D2D1::RectF(
				character->GetRect().left,
				character->GetRect().top - 100,
				character->GetRect().right,
				character->GetRect().bottom - 100);


				
			

				gfx->Drawbmp(character->actionbmp, teet, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0 + 512 * frame, 0, 512 + 512 * frame, 512), frame, frametime, spd, anim);
				
				return;

		}
	}

	HRESULT LoadBmp(Graphics* gfx, std::wstring name) {
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\" + name));
		float width = character->GetRect().right - character->GetRect().left;
		float length = character->GetRect().bottom - character->GetRect().top;
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(character->actionbmp));


	};

	HRESULT LoadBmp(Graphics* gfx)  {
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL,exeDir,1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring fullpath(std::wstring(exeDir).replace(et.size()-8, 8, L"\\Artworks\\Bt.png"));
		float width = character->GetRect().right - character->GetRect().left;
		float length = character->GetRect().bottom - character->GetRect().top;
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(character->bmp));


	};
	HRESULT LoadBmpInv(Graphics* gfx) {
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\Bt_mirror.png"));
		float width = character->GetRect().right - character->GetRect().left;
		float length = character->GetRect().bottom - character->GetRect().top;
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(character->bmp));


	};

	bool CheckPoint() {

		float x = character->GetCenter().x;
		float y = character->GetCenter().y;

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
		speed = STOP;
		return true;
	}
	void SetPoint(POINT& p) {
		targetloc = p;

	}
	void MoveToPoint(POINT& p, float speed=FAST) {
		//constraints here

		float x = character->GetCenter().x;
		float y = character->GetCenter().y;
		
		if (targetloc.x < x && x - targetloc.x>2.0f) {
			if (x-targetloc.x < 2.0f) {
				character->Update(x-targetloc.x, 0.0f);
				this->character->SetDirctn(RIGHT);
				return;
			}
			character->Update(-speed,0.0f);
			this->character->SetDirctn(LEFT);
			//przesuñ w lewo
		}
		else if (x < targetloc.x && targetloc.x - x  > 2.0f) {
			if (targetloc.x - x < 2.0f) {
				character->Update(x - targetloc.x, 0.0f);
				this->character->SetDirctn(LEFT);
				return;
			}
			character->Update(speed,0.0f);
			this->character->SetDirctn(RIGHT);
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
	void Move(POINT& p, float speed, float limit[2][2] = {0}, bool invol=false) {
		if (limit != nullptr) {
		 if (invol == true) {
			this->SetPoint(p);
			this->speed++;
			this->speed %= 5;

		}
		 else {

		 
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
	void Move(POINT& p, float speed, D2D1_RECT_F* limit) {
		if (limit != nullptr) {
			if (p.x >= limit->left && p.x <= limit->right) {
				if (p.y >= limit->top && p.y <= limit->bottom) {


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
			switch (this->speed) {
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
	
};


struct Doors : public BaseUnknown {
	//Obiekt zdarzenia do kontroli blokady drzwi
	float wait, threshold;
	bool lopen, ropen;;
	Recta* left;
	Recta* right;
	int frame;
	int chosen;
	GameLevel* prev;
	GameLevel* next;
public:

	Doors(Graphics* gfx, GameLevel* prev = nullptr, GameLevel* next = nullptr) : BaseUnknown("Doors") {
		this->threshold = GameController::time;
		this->lopen = this->ropen = true;
		this->wait = 0;
		this->frame = 0;
		this->prev = prev;
		this->next = next;
		this->left = new Recta(WNDWIDTH*3/100, WNDHEIGHT*53/100, 100.0f, 255.0f, gfx,false);
		this->right = new Recta(WNDWIDTH-(WNDWIDTH*3/100), WNDHEIGHT*53 /100, 100.0f, 255.0f, gfx, false);
		LoadBmp(gfx);
	}

	virtual ~Doors() {


		delete left, right;
		switch (chosen) {
		case -1:
			delete next;

			break;
		case 1:
			delete prev;
			break;
		default:
			break;
		}
		prev = nullptr;
		next = nullptr;
		delete prev, next;
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
				chosen = -1;
				return true;

			}
		}
		if (right->CheckTrigg(p) && next != nullptr && ropen == true) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
				GameController::SwitchLevel(next);
				chosen = 1;
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
					if (lambda(player.character->GetCenter().x, left->GetX())) {
						GameController::SwitchLevel(prev);
						return true;
					
					}
				
			}
		}
		if (right->CheckTrigg(p) && next != nullptr && ropen == true) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
					if (lambda(right->GetX(), player.character->GetCenter().x) ) {
						GameController::SwitchLevel(next);
						return true;
					}
				
			}
		}
		return false;
	}


	void Render(Graphics* gfx, POINT& p, float r, float g, float b, float a) {

			if (left->CheckTrigg(p)) {
				if (lopen) {
					gfx->Drawbmp(left->bmp, left->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(512, 0, 1024, 512), frame, frametime, spd);
				}
			}
			else {
				gfx->Drawbmp(left->bmp, left->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, frametime, spd);
			}
		
			if (right->CheckTrigg(p)) {
				if (ropen) {
					gfx->Drawbmp(right->bmp, right->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(512, 0, 1024, 512), frame, frametime, spd);
				}
			}
			else {

				gfx->Drawbmp(right->bmp, right->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, frametime, spd);
			}
		
	}
	

		HRESULT LoadBmp(Graphics * gfx, std::wstring name = {}) {
			wchar_t exeDir[1024];
			DWORD let = GetModuleFileName(NULL, exeDir, 1024);
			std::wstring et = std::wstring(exeDir);
			std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\Doors.png"));

			//left
			HRESULT hr;
				float width1 = left->GetRect().right - left->GetRect().left;
				float length1 = left->GetRect().bottom - left->GetRect().top;
				 hr = gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width1, length1, &(left->bmp));
			
			//right
				 if (hr == S_OK) {
					 float width2 = right->GetRect().right - right->GetRect().left;
					 float length2 = right->GetRect().bottom - right->GetRect().top;
					 return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width2, length2, &(right->bmp));

			}
				
				
			
		};

};

struct Panel : public BaseUnknown{


	Recta* base;
	Recta* item_base;
	Recta* spaces[4];
	Recta* text_base;
	Recta* points;
	std::string pointsTxt, text_baseTxt;
	Panel(Graphics* gfx)  {
		base = new Recta(WNDWIDTH/2, CENTER_Y, WNDWIDTH, WNDHEIGHT / 4 + (WNDHEIGHT / 50), gfx, false);
		item_base = new Recta(CENTER_X, CENTER_Y, WIDTH_ITEM, HEIGHT_ITEM, gfx, false);
		for (int i = 0; i < 4; i++) {
			int j = 1;
			int k = 1;
			switch(i) {
			case 1:
				j = -1;
				k = 1;
				break;
			case 2:
				j = 1;
				k = -1;
				break;
			case 3:
				j = -1;
				k = -1;
				break;
			default:
				break;
			}
			spaces[i] = new Recta(CENTER_X + ((CENTER_X / 7) * j), CENTER_Y + ((CENTER_Y / 16) * k), WIDTH_ITEM/2.35, HEIGHT_ITEM/2.75, gfx, false);
		}
		text_base = new Recta(WNDWIDTH/4+ WNDWIDTH / 18, CENTER_Y, WIDTH_ITEM*5/6, HEIGHT_ITEM, gfx, false);
		points= new Recta(WNDWIDTH / 2, WNDHEIGHT*6/100, WIDTH_ITEM * 4 / 10, HEIGHT_ITEM*5/10, gfx, false);		
		LoadBmp(gfx, text_base, L"One_thingy.png");
		LoadBmp(gfx, base, L"Base.png");
		LoadBmp(gfx, points, L"Frame_1080.png");
		for (int i = 0; i < 4; i++) {
			LoadBmp(gfx, spaces[i], L"Item_frame.png");
		}
	}
		
	virtual ~Panel() {
		delete base;
		delete item_base;
		delete text_base;
		delete points;
		for (Recta* el : spaces) {
			delete el;
		}
	}

	void DrawBmp(Graphics* gfx, Recta* obj, int frame=0){

		gfx->Drawbmp(obj->bmp, obj->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 1920, 1080), frame, frametime, spd);
		}


	HRESULT LoadBmp(Graphics* gfx, Recta* obj, std::wstring name = {}, bool bg = false) {
			float length, width;
			wchar_t exeDir[1024];
			DWORD let = GetModuleFileName(NULL, exeDir, 1024);
			std::wstring et = std::wstring(exeDir);
			std::wstring adding = std::wstring(L"\\Artworks\\"+name) ;

			std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));
				width = obj->GetRect().right - obj->GetRect().left;
				length = obj->GetRect().bottom - obj->GetRect().top;

			return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(obj->bmp));


		};



	void Render(Graphics* gfx) {
			DrawBmp(gfx, base);

			for (int i = 0; i < 4; i++) {
				DrawBmp(gfx, spaces[i]);
			}
			DrawBmp(gfx, text_base);
			DrawBmp(gfx, points);
		};

	void DrawTxt(Graphics* gfx, Writer* wrt, D2D1_RECT_F rect,std::string inputtxt, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT par = DWRITE_PARAGRAPH_ALIGNMENT_NEAR, float val = -1) {

			D2D1_RECT_F temp = rect;
			temp.top += 30.0f;
			temp.bottom -= 30.0f;
			temp.left += 80.0f;
			temp.right -= 80.0f;
			std::string text;
			/*for (int i = 0; i<5; i++)
			{
				text += std::to_string(vals[i]) + "\n";
			}*/
			if (val > -1) {
				text += " " + std::to_string((int)val);
			}
			
			wrt->Draw_Text(inputtxt+text,temp, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

		}

	void SetText(std::string inputtxt, int choice) {
			switch (choice) {
			case 1:
				pointsTxt = inputtxt;
				break;
			case 2:
				text_baseTxt = inputtxt;
				break;

			default:
				break;
			}
		}

	void LoadTextOnStuff(Graphics* gfx, Writer* wrt, int choice) {

		switch (choice) {
		case 1:
			DrawTxt(gfx, wrt, points->GetRect(), pointsTxt, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			break;
		case 2:
			DrawTxt(gfx, wrt, text_base->GetRect(), text_baseTxt);
			break;

		default:
			break;
			}

			
		};
};


class BaseButton : public BaseUnknown {
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

class Item : public BaseUnknown {
public:

	int id;
	bool interactable, combinable, consumable;
	int state;
	std::string name;
	Recta* drawtarget;



	Item(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		int id = nl,
		bool interactable = false,
		bool combinable = false,
		bool consumable = false,
		int state = not_earned
	) {
		drawtarget = new Recta(spawnx, spawny, width, height, gfx, false);
		this->interactable = interactable;
		this->combinable = combinable;
		this->consumable = consumable;
		this->state = state;

	};
	virtual ~Item() {
		delete drawtarget;
  }

	virtual void Use()=0;
	void RenderBmp(Graphics* gfx,
		FLOAT opacity, bool anim = false) {
		frametime = frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, frametime, spd, anim);


	}
};


struct Ball : public BaseUnknown {
	Recta* drawtarget;
	POINT targetloc;
	int frames = 4;
	Ball(Graphics* gfx,
		float spawnx,
		float spawny,
		float rad,
		float width,
		float height,
		std::string name = "NULL"
	) : BaseUnknown(name) {

		drawtarget = new Recta(spawnx, spawny, width, height, gfx, true);
		this->targetloc.x = spawnx;
		this->targetloc.y = spawny;
		LoadBmp(gfx);

	}
	virtual ~Ball() {
		delete drawtarget;
	}

	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1) {

		drawtarget->ttl += GameController::increment;

		if (fill) {


		}
		else {

			drawtarget->Render(gfx, r, g, b, a);
			drawtarget->DrawVelocityVect(gfx);

		}

	}
	void RenderBmp(Graphics* gfx,
		FLOAT opacity, bool anim = false) {

		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frames, frametime, spd,anim);

	}

	HRESULT LoadBmp(Graphics* gfx, std::wstring name = {}) {
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\Ball.png"));
		float width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		float length = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(drawtarget->bmp));


	};
	void Update(float x, float y) {
		drawtarget->Update(x, y);
	}
};

struct Inanimate : public BaseUnknown {

	Recta* drawtarget;
	POINT targetloc;
	bool traversible;
	bool solid;
	std::string name;
	std::wstring texturefile;
	
	Inanimate(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		std::wstring texturefile,
		bool traversible = false,
		bool solid = true,
		std::string name="NULL"
	) : BaseUnknown(name) {
		

		drawtarget = new Recta(spawnx, spawny, width, height, gfx, false);
		this->texturefile = texturefile;
		this->targetloc.x = spawnx;
		this->targetloc.y = spawny;
		this->traversible = traversible;
		this->solid = solid;
		LoadBmp(gfx, texturefile);
		
	}
	~Inanimate() {
		delete drawtarget;
	}

	bool getTrav() {
		return traversible;
	}
	void setTrav(bool set) {
		traversible = set;
	}

	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1) {

		if (fill) {


		}
		else {

			drawtarget->Render(gfx, r, g, b, a);

		}
	}

	void RenderBmp(Graphics* gfx,
		FLOAT opacity, bool anim = false) {
		frametime = frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, frametime, spd,anim);
		
		
	}
	void RenderBmpBG(Graphics* gfx,
		FLOAT opacity, bool anim = false) {
		frametime = frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 1920, 1080), frame, frametime, spd,anim);


	}

	HRESULT LoadBmp(Graphics* gfx, std::wstring name = {}, bool bg=false) {

		float length, width;
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring adding = std::wstring(L"\\Artworks\\") + texturefile;

		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));
		if (bg) {
			width = WNDWIDTH;
			length = WNDHEIGHT;
		}
		else {
		 width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		 length = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		}
		
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(drawtarget->bmp));

	};

	HRESULT LoadBmp(Graphics* gfx, float width, float height, std::wstring name = {}, bool bg = false) {

		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring adding = std::wstring(L"\\Artworks\\") + texturefile;

		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));

		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, height, &(drawtarget->bmp));


	};


}; 

struct FloatingText : public BaseUnknown {

	Recta* drawtarget;
	POINT targetloc;
	std::string text;
	int frame = 0;
	bool triggered; 
	FloatingText(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		std::string text
	) {
		drawtarget = new Recta(spawnx, spawny, width, height, gfx);
		this->text = text;
		this->targetloc.x = spawnx;
		this->targetloc.y = spawny;
	}

	virtual ~FloatingText() {
		delete drawtarget;
	}
	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1, Writer* wrt = {}) {

		if (triggered) {

	//	drawtarget->Render(gfx, r, g, b, a);
		
		wrt->Draw_Text(text, drawtarget->GetRect());
		}
	}
	void SetText(std::string inputtxt, int choice) {

			text = inputtxt;
	}
	void Update(POINT p) {

		drawtarget->Update(p);
	}
};