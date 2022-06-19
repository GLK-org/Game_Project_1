#include "Level_controls.h"

	BaseUnknown::BaseUnknown(std::string n, bool tag) {
		condition = false;
		taggable = false;
		spd = F_SLOWEST;
		drawtarget = nullptr;
	};
	BaseUnknown::~BaseUnknown() {
		delete drawtarget;
	}

	void BaseUnknown::SetSpd(Speed spd) {
		this->spd = spd;
	};

	bool BaseUnknown::CheckTrigg(const POINT& p) {
		if (drawtarget->CheckTrigg(p)) {
			return true;
		}
		return false;
	};

	bool  BaseUnknown::CheckTrigg(const D2D1_POINT_2F& p) {
		if (drawtarget->CheckTrigg(p)) {
			return true;
		}
		return false;
	};

	bool  BaseUnknown::CheckTrigg(const D2D1_RECT_F& p) {
		if (drawtarget->CheckTrigg(p)) {
			return true;
		}
		return false;
	};

	void BaseUnknown::Update(float x, float y) {
		drawtarget->Update(x, y);
	}

	void BaseUnknown::Update(float x, float y, bool grav) {
		drawtarget->Update(x, y,grav);
	}

	void  BaseUnknown::Update(POINT& p) {
		drawtarget->Update(p);
	}

	D2D1_POINT_2F BaseUnknown::Get_inv_veloc()
	{
		D2D1_POINT_2F e = drawtarget->phsx->Get_inv_veloc();
		return e;
	}



#define PL_TOLERATED_DISTANCEX WNDWIDTH/40.0f
#define PL_TOLERATED_DISTANCEY WNDHEIGHT / 18.0f

Player::Player(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height
	) : BaseUnknown("Player") {
		this->speed = 0;
		drawtarget = new Recta(spawnx, spawny, width, height, gfx);
		this->targetloc.x = spawnx;
		this->targetloc.y = spawny;
		drawtarget->phsx->mass = 2.0f;
		feet= D2D1::Point2F(spawnx,height);
		LoadBmpRes(gfx,IDB_PNG8);

	}

	 Player::~Player() {
	}

	void Player::Render(Graphics* gfx, POINT& p, bool fill, float r , float g, float b, float a) {
		drawtarget->ttl += GameController::increment;

		if (fill) {


		}
		else {

			drawtarget->Render(gfx, r, g, b, a);

		}
	}

	void Player::RenderBmp(Graphics* gfx,
		FLOAT opacity,
		bool anim) {
		drawtarget->frametime = drawtarget->frametime + GameController::increment;

		if (drawtarget->bmp != nullptr) {

			float offset = 0;
			D2D1_RECT_F teet = D2D1::RectF(
				drawtarget->GetRect().left,
				drawtarget->GetRect().top - offset,
				drawtarget->GetRect().right,
				drawtarget->GetRect().bottom - offset);


			if (speed != STOP) {
				if (drawtarget->frame == 0) {
					drawtarget->frame = 1;
				}
				if (this->drawtarget->direction == LEFT) {

					gfx->Mirror(drawtarget->GetCenter());
					gfx->Drawbmp(drawtarget->bmp, teet, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, 512, 512), drawtarget->frame, drawtarget->frametime, spd, true, 1);

					gfx->ClearTransforms();
				}
				else if (this->drawtarget->direction == RIGHT) {
					gfx->Drawbmp(drawtarget->bmp, teet, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, 512, 512), drawtarget->frame, drawtarget->frametime, spd, true, 1);

				}
			}
			else {
				drawtarget->frame = 0;
				gfx->Drawbmp(drawtarget->bmp, teet, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, 512, 512), drawtarget->frame, drawtarget->frametime, spd, 0);

			}
			drawtarget->DrawVelocityVect(gfx);
			return;

		}
	}


	void Player::RenderSpecialBmp(Graphics* gfx,
		FLOAT opacity, std::wstring name,
		bool anim,
		Speed spd, int startingframe) {
		drawtarget->actionframetime += GameController::increment;
		if (condition == false) {
			return;
		}
		if (drawtarget->actionbmp != nullptr) {
			float offset = 0;

			D2D1_RECT_F teet = D2D1::RectF(
				drawtarget->GetRect().left,
				drawtarget->GetRect().top - offset,
				drawtarget->GetRect().right,
				drawtarget->GetRect().bottom - offset);





			gfx->Drawbmp(drawtarget->actionbmp, teet, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, 512, 512), drawtarget->actionframe, drawtarget->actionframetime, spd, anim, startingframe);

			return;

		}
	}

	HRESULT Player::LoadBmp(Graphics* gfx, std::wstring name) {
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\" + name));
		float width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		float length = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(drawtarget->actionbmp));


	};

	HRESULT Player::LoadBmpRes(Graphics* gfx, int ind, bool sup) {
		
		float width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		float height = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		if (sup) {
			return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width, height, &(drawtarget->actionbmp));
		}
		else {
			return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width, height, &(drawtarget->bmp));
		}
		


	};

	HRESULT Player::LoadBmp(Graphics* gfx) {
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\Bt.png"));
		float width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		float length = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(drawtarget->bmp));


	}
	void Player::UpdateFeet()
	{
		feet.x = drawtarget->GetX();
		feet.y = drawtarget->GetRect().bottom;
	};

	bool Player::CheckPoint() {

		float x = feet.x;
		float y = feet.y;

		if (targetloc.x < x && x - targetloc.x>PL_TOLERATED_DISTANCEX) {
			return false;
			//przesuñ w lewo
		}
		else if (x < targetloc.x && targetloc.x - x  > PL_TOLERATED_DISTANCEX) {
			return false;
			//przesuñ w prawo
		}

		if (targetloc.y < y && y - targetloc.y >PL_TOLERATED_DISTANCEY) {
			return false;
			//przesuñ w górê
		}
		else if (y < targetloc.y && targetloc.y - y  > PL_TOLERATED_DISTANCEY) {
			return false;
			//przesuñ w dó³
		}
		speed = STOP;
		return true;
	}

	void Player::SetPoint(POINT& p) {
		targetloc = p;

	}

	void Player::MoveToPoint(POINT& p, float speed, bool grav) {
		//constraints here
		if (spd == STOP)return;
		float x = feet.x;
		
		if (targetloc.x < x && x - targetloc.x>PL_TOLERATED_DISTANCEX) {
			if (x - targetloc.x < PL_TOLERATED_DISTANCEX) {
				drawtarget->Update(x - targetloc.x, 0.0f,grav);
				this->drawtarget->SetDirctn(RIGHT);
				UpdateFeet();
				return;
			}
			drawtarget->Update(-speed, 0.0f, grav);
			this->drawtarget->SetDirctn(LEFT);
			UpdateFeet();
			//przesuñ w lewo
		}
		else if (x < targetloc.x && targetloc.x - x  > PL_TOLERATED_DISTANCEX) {
			if (targetloc.x - x < PL_TOLERATED_DISTANCEX) {
				drawtarget->Update(x - targetloc.x, 0.0f, grav);
				this->drawtarget->SetDirctn(LEFT);
				UpdateFeet();
				return;
			}
			drawtarget->Update(speed, 0.0f, grav);
			this->drawtarget->SetDirctn(RIGHT);
			UpdateFeet();
			//przesuñ w prawo
		}

		if (grav != true) {
			float y = feet.y;
			
			if (targetloc.y < y && y - targetloc.y > PL_TOLERATED_DISTANCEY) {
				if (y - targetloc.y < PL_TOLERATED_DISTANCEY && y - targetloc.y > 0.0f) {
					drawtarget->Update(0.0f, -(y - targetloc.y) / PL_TOLERATED_DISTANCEY);
					UpdateFeet();
					return;
				}
				drawtarget->Update(0.0f, -(speed / 4.0f));
				UpdateFeet();
				//przesuñ w górê
			}
			else if (y < targetloc.y && targetloc.y - y  > PL_TOLERATED_DISTANCEY) {
				if (y - targetloc.y < PL_TOLERATED_DISTANCEY && y - targetloc.y > 0.0f) {
					drawtarget->Update(0.0f, (targetloc.y - y) / 2.0f);
					UpdateFeet();
					return;
				}
				drawtarget->Update(0.0f, (speed / 4.0f));
				UpdateFeet();
				//przesuñ w dó³
			}
		}
		else {
			float y = feet.y;

			if (targetloc.y < y && y - targetloc.y > PL_TOLERATED_DISTANCEY) {
				if (y - targetloc.y < PL_TOLERATED_DISTANCEY && y - targetloc.y > 0.0f) {
					drawtarget->Update(0.0f, -(y - targetloc.y) / 2.0f, grav);
					UpdateFeet();
					return;
				}
				drawtarget->Update(0.0f, -(speed / 4.0f) / 2.0f, grav);
				UpdateFeet();
				//przesuñ w górê
			}
			else if (y < targetloc.y && targetloc.y - y  > PL_TOLERATED_DISTANCEY) {
				if (y - targetloc.y < PL_TOLERATED_DISTANCEY && y - targetloc.y > 0.0f) {
					drawtarget->Update(0.0f, (targetloc.y - y) / 8.0f, grav);
					UpdateFeet();
					return;
				}
				drawtarget->Update(0.0f, (speed / 4.0f) / 8.0f, grav);
				UpdateFeet();
				//przesuñ w dó³
			}
		}
		
		return;

	}
	void Player::Move(POINT& p, float speed, bool invol) {
		if (invol == true) {
			this->SetPoint(p);
			this->speed++;
			this->speed %= 4;

		}


		if (GameController::PressButton(RI_MOUSE_LEFT_BUTTON_DOWN, true)) {
			this->SetPoint(p);
			this->speed++;
			this->speed %= 4;
		}



		if (this->CheckPoint() == false) {
			switch (this->speed) {
			case 0: {
				this->MoveToPoint(p, STOP);
				break;
			}
			case 1: {
				this->MoveToPoint(p, SLOW);
				SetSpd(F_MEDIUM);
				break;
			}
			case 2: {
				this->MoveToPoint(p, MEDIUM_FAST);
				SetSpd(F_FAST);
				break;
			}
			case 3: {
				this->MoveToPoint(p, FAST);
				SetSpd(F_IMMEDIATE);
				break;
			}
			default:
				Update();
				break;
			}

		}
		else {
			this->speed = 0;
			
			//	this->character->Getpshx().ClearSpeed();
		}
	}
	void Player::Move(POINT& p, float speed, D2D1_RECT_F* limit, bool grav) {

		if (limit != nullptr) {
			if (p.x >= limit->left && p.x <= limit->right) {
				if (p.y >= limit->top && p.y <= limit->bottom) {


					if (GameController::PressButton(RI_MOUSE_LEFT_BUTTON_DOWN, true)) {
						this->SetPoint(p);
						this->speed++;
						this->speed %= 4;
					}
				}
			}
		}
		else {

			if (GameController::PressButton(RI_MOUSE_LEFT_BUTTON_DOWN, true)) {
				this->SetPoint(p);
				this->speed++;
				this->speed %= 4;
			}

		}

		if (this->CheckPoint() == false) {
			switch (this->speed) {
			case 0: {
				this->MoveToPoint(p, STOP);
				break;
			}
			case 1: {
				this->MoveToPoint(p, SLOW);
				SetSpd(F_MEDIUM);
				break;
			}
			case 2: {
				this->MoveToPoint(p, MEDIUM_FAST);
				SetSpd(F_FAST);
				break;
			}
			case 3: {
				this->MoveToPoint(p, MEDIUM_FAST);
				SetSpd(F_IMMEDIATE);
				break;
			}
			default:
				Update(0,0,grav);
				break;
			}
		}
		else {
			Update(0, 0, grav);
			this->speed = 0;
			//	this->character->Getpshx().ClearSpeed();
		}

	}

	Doors::Doors(Graphics* gfx, GameLevel* prev, GameLevel* next) : BaseUnknown("Doors") {
		this->threshold = GameController::time;
		this->lopen = this->ropen = true;
		this->wait = 0;
		this->frame = 0;
		this->prev = prev;
		this->next = next;
		this->left = new Recta(WNDWIDTH * 3 / 100, WNDHEIGHT * 53 / 100, WNDHEIGHT / 8.0f, WNDHEIGHT / 3.5f, gfx, false);
		this->right = new Recta(WNDWIDTH - (WNDWIDTH * 3 / 100), WNDHEIGHT * 53 / 100, WNDHEIGHT / 8.0f, WNDHEIGHT / 3.5f, gfx, false);
		this->wallsl = new Recta(*left);
		this->wallsr = new Recta(*right);
		D2D1_RECT_F temp = left->GetRect();
		temp.bottom = temp.top;
		temp.top = 0;
		wallsl->SetRect(temp);

		temp = right->GetRect();
		temp.bottom = temp.top;
		temp.top = 0;
		wallsr->SetRect(temp);

	LoadBmpRes(gfx, IDB_PNG10);
	LoadBmpReswalls(gfx, IDB_PNG11);
	}

	Doors::~Doors() {


		delete left, right;
		delete wallsl, wallsr;
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
	bool Doors::UpdateTrig(POINT& p) {
		this->wait = GameController::time;

		if (wait < threshold + 3.0f) {

			return false;

		}

		if (left->CheckTrigg(p) && prev != nullptr && lopen == true) {
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
	bool Doors::UpdateTrig(POINT& p, const Player& player) {
		this->wait = GameController::time;

		auto lambda = [](float big, float smal) {

			if (big - smal <= 100.0f && big - smal > 0.0f) {
				return true;
			}
			return false;
		};

		if (wait < threshold + 3.0f) {

			return false;
		}
		if (left->CheckTrigg(p) && prev != nullptr && lopen == true) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
				if (lambda(player.drawtarget->GetCenter().x, left->GetX())) {
					GameController::SwitchLevel(prev);
					return true;

				}

			}
		}
		if (right->CheckTrigg(p) && next != nullptr && ropen == true) {
			if (GetKeyState(RI_MOUSE_LEFT_BUTTON_DOWN) & KEY_PRESSED) {
				if (lambda(right->GetX(), player.drawtarget->GetCenter().x)) {
					GameController::SwitchLevel(next);
					return true;
				}

			}
		}
		return false;
	}


	void Doors::Render(Graphics* gfx, POINT& p, float r, float g, float b, float a) {



		gfx->Drawbmp(wallsl->bmp, wallsl->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, drawtarget->frametime, spd);


		gfx->Drawbmp(wallsr->bmp, wallsr->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, drawtarget->frametime, spd);

		if (left->CheckTrigg(p)) {
			if (lopen) {
				gfx->Drawbmp(left->bmp, left->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(512, 0, 1024, 512), frame, drawtarget->frametime, spd);
			}
			else {
				gfx->Drawbmp(left->bmp, left->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, drawtarget->frametime, spd);
			}
		}
		else {
			gfx->Drawbmp(left->bmp, left->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, drawtarget->frametime, spd);
		}

		if (right->CheckTrigg(p)) {
			if (ropen) {
				gfx->Drawbmp(right->bmp, right->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(512, 0, 1024, 512), frame, drawtarget->frametime, spd);
			}
			else {
				gfx->Drawbmp(right->bmp, right->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, drawtarget->frametime, spd);
			}
		}
		else {

			gfx->Drawbmp(right->bmp, right->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), frame, drawtarget->frametime, spd);
		}

	}

	HRESULT Doors::LoadBmp(Graphics* gfx) {
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



	}
	HRESULT Doors::LoadBmpRes(Graphics* gfx, int ind, bool sup)
	{

		float width1 = left->GetRect().right - left->GetRect().left;
		float height1 = left->GetRect().bottom - left->GetRect().top;
		float width2 = right->GetRect().right - right->GetRect().left;
		float height2 = right->GetRect().bottom - right->GetRect().top;
		HRESULT hr;

			hr= gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width1, height1, &(left->bmp));
			if (hr == S_OK) {
				return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width2, height2, &(right->bmp));
		}
			
		
	}
	; HRESULT Doors::LoadBmpReswalls(Graphics* gfx, int ind)
	{

		float width1 = wallsl->GetRect().right - wallsl->GetRect().left;
		float height1 = wallsl->GetRect().bottom - wallsl->GetRect().top;
		float width2 = right->GetRect().right - right->GetRect().left;
		float height2 = right->GetRect().bottom - right->GetRect().top;
		HRESULT hr;

		hr = gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width1, height1, &(wallsl->bmp));
		if (hr == S_OK) {
			return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width2, height2, &(wallsr->bmp));
		}


	}
	HRESULT Doors::LoadBmp(Graphics* gfx, std::wstring name) {
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\" + name));

		HRESULT hr;
		float width1 = wallsl->GetRect().right - wallsl->GetRect().left;
		float length1 = wallsl->GetRect().bottom - wallsl->GetRect().top;
		gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width1, length1, &(wallsl->bmp));
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width1, length1, &(wallsr->bmp));




	};



	Panel::Panel(Graphics* gfx) {
		base = new Recta(WNDWIDTH / 2, CENTER_Y, WNDWIDTH, WNDHEIGHT / 4 + (WNDHEIGHT / 50), gfx, false);
		item_base = new Recta(CENTER_X, CENTER_Y, WIDTH_ITEM, HEIGHT_ITEM, gfx, false);
		for (int i = 0; i < 4; i++) {
			int j = 1;
			int k = 1;
			switch (i) {
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
			spaces[i] = new Recta(CENTER_X + ((CENTER_X / 7) * j), CENTER_Y + ((CENTER_Y / 16) * k), WIDTH_ITEM / 2.35, HEIGHT_ITEM / 2.75, gfx, false);
		}
		text_base = new Recta(WNDWIDTH / 4 + WNDWIDTH / 18, CENTER_Y, WIDTH_ITEM * 5 / 6, HEIGHT_ITEM, gfx, false);
		points = new Recta(WNDWIDTH / 2, WNDHEIGHT * 6 / 100, WIDTH_ITEM * 4 / 10, HEIGHT_ITEM * 5 / 10, gfx, false);
		LoadBmpRes(gfx, IDB_PNG22, text_base);
		LoadBmpRes(gfx, IDB_PNG3, base);
		LoadBmpRes(gfx, IDB_PNG14, points);
		for (int i = 0; i < 4; i++) {
			LoadBmpRes(gfx, IDB_PNG20, spaces[i]);
		}
	}

	Panel::~Panel() {
		delete base;
		delete item_base;
		delete text_base;
		delete points;
		for (Recta* el : spaces) {
			delete el;
		}
	}

	void Panel::DrawBmp(Graphics* gfx, Recta* obj, int frame) {

		gfx->Drawbmp(obj->bmp, obj->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 1920, 1080), frame, drawtarget->frametime, spd);
	}


	HRESULT Panel::LoadBmp(Graphics* gfx, Recta* obj, std::wstring name, bool bg) {
		float length, width;
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring adding = std::wstring(L"\\Artworks\\" + name);

		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));
		width = obj->GetRect().right - obj->GetRect().left;
		length = obj->GetRect().bottom - obj->GetRect().top;

		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(obj->bmp));


	}
	HRESULT Panel::LoadBmpRes(Graphics* gfx, int ind, bool sup)
	{
		float width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		float height = drawtarget->GetRect().bottom - drawtarget->GetRect().top;

		return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width, height, &(drawtarget->bmp));
	}

	; HRESULT Panel::LoadBmpRes(Graphics* gfx, int ind, Recta* obj)
	{
		float width = obj->GetRect().right - obj->GetRect().left;
		float height = obj->GetRect().bottom - obj->GetRect().top;

		return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width, height, &(obj->bmp));
	}

	void Panel::Render(Graphics* gfx) {
		DrawBmp(gfx, base);

		for (int i = 0; i < 4; i++) {
			DrawBmp(gfx, spaces[i]);
		}
		DrawBmp(gfx, text_base);
		DrawBmp(gfx, points);
	};

	void Panel::DrawTxt(Graphics* gfx, Writer* wrt, D2D1_RECT_F rect, std::string inputtxt, DWRITE_TEXT_ALIGNMENT align, DWRITE_PARAGRAPH_ALIGNMENT par, float val) {

		D2D1_RECT_F temp = rect;
		temp.top += HEIGHT_ITEM / 8;
		temp.bottom -= HEIGHT_ITEM / 8;
		temp.left += WIDTH_ITEM / 10;
		temp.right -= WIDTH_ITEM / 10;
		std::string text;
		/*for (int i = 0; i<5; i++)
		{
			text += std::to_string(vals[i]) + "\n";
		}*/
		if (val > -1) {
			text += " " + std::to_string((int)val);
		}

		wrt->Draw_Text(inputtxt + text, temp, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	}

	void Panel::SetText(std::string inputtxt, int choice) {
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

	void Panel::LoadTextOnStuff(Graphics* gfx, Writer* wrt, int choice) {

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


		 BaseButton::BaseButton(Obj* ob, float r, float g, float b, float a, std::string text) {
		this->ob = ob;
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->text = text;

	};
	
		 BaseButton::~BaseButton() { delete ob; };

	void BaseButton::Render(Graphics* gfx, float r, float g, float b, float a, bool wtext, Writer* wrt, bool colorable)
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
			float e[4] = { r - 0.4f, g + 0.2f, b + 0.2f, a };
			ob->Fill(gfx, e);
		}

		if (wtext == true) {
			D2D1_RECT_F container(
				ob->GetX() - ob->GetX() / 2,
				ob->GetY() - ob->GetY() / 2,
				ob->GetX() + ob->GetX() / 2,
				ob->GetY() + ob->GetY() / 2
			);
			wrt->Draw_Text(text, container);
		};
	}
	
	bool BaseButton::CheckTrg(POINT& p) { return ob->CheckTrigg(p); }
	HRESULT BaseButton::LoadBmpRes(Graphics* gfx, int ind, bool sup)
	{
		return E_NOTIMPL;
	}
	;




	Item::Item(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		int id,
		bool interactable,
		bool combinable,
		bool consumable,
		States state
	) : BaseUnknown(name, true) {

		drawtarget = new Recta(spawnx, spawny, width, height, gfx, false);
		this->interactable = interactable;
		this->combinable = combinable;
		this->consumable = consumable;
		this->state = state;
		this->id = id;
	};

	Item::Item(const Item* copying) : BaseUnknown(copying->name, copying->taggable) {
		drawtarget = new Recta(copying->drawtarget);
		this->interactable = copying->interactable;
		this->combinable = copying->combinable;
		this->consumable = copying->consumable;
		this->state = copying->state;
		this->id = copying->id;

	}
	Item::~Item() {
	}

	void Item::RenderBmp(Graphics* gfx,
		FLOAT opacity, D2D1_RECT_F rec, bool anim) {
		drawtarget->frametime = drawtarget->frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, rec, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), drawtarget->frame, drawtarget->frametime, spd, anim);


	}

	HRESULT Item::LoadBmpRes(Graphics* gfx, int ind, bool sup)
	{
		float width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		float height = drawtarget->GetRect().bottom - drawtarget->GetRect().top;

		return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width, height, &(drawtarget->bmp)); 
	}

	HRESULT Item::LoadBmp(Graphics* gfx, Recta* obj, std::wstring name) {
		float length, width;
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring adding = std::wstring(L"\\Artworks\\" + name);

		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));
		width = obj->GetRect().right - obj->GetRect().left;
		length = obj->GetRect().bottom - obj->GetRect().top;

		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(obj->bmp));


	};



	Ball::Ball(Graphics* gfx,
		float spawnx,
		float spawny,
		float rad,
		float width,
		float height,
		std::string name 
	) : BaseUnknown(name) {

		drawtarget = new Recta(spawnx, spawny, width, height, gfx, true);
		this->targetloc.x = spawnx;
		this->targetloc.y = spawny;
		LoadBmpRes(gfx, IDB_PNG2);

	}
	Ball::~Ball() {
	}

	void Ball::Render(Graphics* gfx, POINT& p, bool fill, float r, float g, float b, float a) {

		drawtarget->ttl += GameController::increment;

		if (fill) {


		}
		else {

			drawtarget->Render(gfx, r, g, b, a);
			drawtarget->DrawVelocityVect(gfx);

		}

	}
	void Ball::RenderBmp(Graphics* gfx,FLOAT opacity, bool anim) {
		drawtarget->frametime = drawtarget->frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), drawtarget->frame, drawtarget->frametime, spd, anim);

	}

	HRESULT Ball::LoadBmp(Graphics* gfx, std::wstring name) {
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\Ball.png"));
		float width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		float length = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, length, &(drawtarget->bmp));


	}

	HRESULT Ball::LoadBmpRes(Graphics* gfx, int ind, bool sup)
	{
		float width = drawtarget->GetRect().right - drawtarget->GetRect().left;
		float height = drawtarget->GetRect().bottom - drawtarget->GetRect().top;

		return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width, height, &(drawtarget->bmp));
	}
	;
	void Ball::Update(float x, float y) {
		drawtarget->Update(x, y);
	}



	Inanimate::Inanimate(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		int texturefile,
		bool traversible,
		bool solid,
		std::string name,
		bool taggable
	) : BaseUnknown(name, taggable) {


		drawtarget = new Recta(spawnx, spawny, width, height, gfx, false);
		this->texturefile = texturefile;
		this->traversible = traversible;
		this->solid = solid;
		LoadBmpRes(gfx, texturefile);
		this->name = name;
		this->taggable = taggable;
	}
		Inanimate::~Inanimate() {}
	bool Inanimate::getTrav() {
		return traversible;
	}
	void Inanimate::setTrav(bool set) {
		traversible = set;
	}

	void Inanimate::Render(Graphics* gfx, POINT& p, bool fill, float r, float g, float b, float a) {

		if (fill) {


		}
		else {

			drawtarget->Render(gfx, r, g, b, a);

		}
	}

	void Inanimate::RenderBmp(Graphics* gfx,
		FLOAT opacity, bool anim, int startingframe) {
		drawtarget->frametime = drawtarget->frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), drawtarget->frame, drawtarget->frametime, spd, anim, startingframe);


	}
	void Inanimate::RenderBmpBG(Graphics* gfx,
		FLOAT opacity, bool anim, int startingframe) {
		drawtarget->frametime = drawtarget->frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 1920, 1080), drawtarget->frame, drawtarget->frametime, spd, anim, startingframe);


	}

	HRESULT Inanimate::LoadBmp(Graphics* gfx, std::wstring name, bool bg) {

		float height, width;
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring adding = std::wstring(L"\\Artworks\\") + texturefile;

		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));
		if (bg) {
			width = WNDWIDTH;
			height = WNDHEIGHT;
		}
		else {
			width = drawtarget->GetRect().right - drawtarget->GetRect().left;
			height = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		}

		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, height, &(drawtarget->bmp));

	}
	HRESULT Inanimate::LoadBmpRes(Graphics* gfx, int ind, bool sup)
	{
		float height, width;
		if (sup) {
			width = WNDWIDTH;
			height = WNDHEIGHT;
		}
		else {
			width = drawtarget->GetRect().right - drawtarget->GetRect().left;
			height = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		}

		return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width, height, &(drawtarget->bmp));
	};

	HRESULT Inanimate::LoadBmp(Graphics* gfx, float width, float height, std::wstring name, bool bg) {

		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring adding = std::wstring(L"\\Artworks\\") + texturefile;

		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));

		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, height, &(drawtarget->bmp));


	};

	Animate::Animate(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		int texturefile,
		bool traversible,
		bool solid,
		std::string name,
		bool taggable,
		float mass
	) : BaseUnknown(name, taggable) {


		drawtarget = new Recta(spawnx, spawny, width, height, gfx, true);
		this->texturefile = texturefile;
		this->traversible = traversible;
		this->solid = solid;
		drawtarget->phsx->mass = mass;
		LoadBmpRes(gfx, texturefile);
		this->name = name;
		this->taggable = taggable;
	}
	Animate::~Animate() {
	}


	bool Animate::getTrav() {
		return traversible;
	}
	void Animate::setTrav(bool set) {
		traversible = set;
	}

	void Animate::Render(Graphics* gfx, POINT& p, bool fill, float r, float g, float b, float a) {

		if (fill) {


		}
		else {

			drawtarget->Render(gfx, r, g, b, a);

		}
	}

	void Animate::RenderBmp(Graphics* gfx,
		FLOAT opacity, bool anim) {

		drawtarget->frametime = drawtarget->frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 512, 512), drawtarget->frame, drawtarget->frametime, spd, anim);

	}
	void Animate::RenderBmpBG(Graphics* gfx,
		FLOAT opacity, bool anim) {

		drawtarget->frametime = drawtarget->frametime + GameController::increment;
		if (drawtarget->bmp != nullptr)
			gfx->Drawbmp(drawtarget->bmp, drawtarget->GetRect(), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 1920, 1080), drawtarget->frame, drawtarget->frametime, spd, anim);

	}

	HRESULT Animate::LoadBmp(Graphics* gfx, std::wstring name, bool bg) {

		float height, width;
		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring adding = std::wstring(L"\\Artworks\\") + texturefile;

		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));
		if (bg) {
			width = WNDWIDTH;
			height = WNDHEIGHT;
		}
		else {
			width = drawtarget->GetRect().right - drawtarget->GetRect().left;
			height = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		}

		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, height, &(drawtarget->bmp));

	};

	HRESULT Animate::LoadBmp(Graphics* gfx, float width, float height, std::wstring name, bool bg) {

		wchar_t exeDir[1024];
		DWORD let = GetModuleFileName(NULL, exeDir, 1024);
		std::wstring et = std::wstring(exeDir);
		std::wstring adding = std::wstring(L"\\Artworks\\") + texturefile;

		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, adding));

		return gfx->LoadBMP(nullptr, nullptr, fullpath.c_str(), width, height, &(drawtarget->bmp));


	};
	
	HRESULT Animate::LoadBmpRes(Graphics* gfx, int ind, bool sup)
	{
		float height, width;
		if (sup) {
			width = WNDWIDTH;
			height = WNDHEIGHT;
		}
		else {
			width = drawtarget->GetRect().right - drawtarget->GetRect().left;
			height = drawtarget->GetRect().bottom - drawtarget->GetRect().top;
		}

		return gfx->LoadBmpFromRes(NULL, NULL, ind, L"PNG", width, height, &(drawtarget->bmp));

	};

	void Animate::Update(float x, float y) {

		drawtarget->Update(x, y);
	}

	void Animate::Update(POINT& p) {
		drawtarget->Update(p);
	}

	FloatingText::FloatingText(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		std::string text
	) {
		drawtarget = new Recta(spawnx, spawny, width, height, gfx);
		this->text = text;
	}

	FloatingText::~FloatingText() {
	}

	void FloatingText::Render(Graphics* gfx, POINT& p, Writer* wrt, bool fill, float r, float g, float b , float a) {

		//	drawtarget->Render(gfx, r, g, b, a);
		D2D1_RECT_F temp(p.x, p.y, p.x + WNDWIDTH / 12.0f, p.y + WNDHEIGHT / 12.0f);
		wrt->Draw_Text(text, temp);
	}
	void FloatingText::SetText(std::string inputtxt) {
		text = inputtxt;
	}
	HRESULT FloatingText::LoadBmpRes(Graphics* gfx, int ind, bool sup)
	{
		return E_NOTIMPL;
	}
	void FloatingText::Update(POINT p) {

		drawtarget->Update(p);
	}

