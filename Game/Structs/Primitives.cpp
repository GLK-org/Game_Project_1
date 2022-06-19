#pragma once
#include "Primitives.h"

	Eli::Eli(float x, float y, float r, float w, float h, Graphics* gfx, bool phs) : Obj(x, y) {
		if (w == NULL || h == NULL) {
			Eli::Obj::~Obj();
		}

		this->eli = { 0 };
		this->w = w;
		this->h = h;
		this->r = r;
		eli = D2D1::Ellipse(D2D1::Point2F(this->GetX(), this->GetY()), w, h);
		//Zapisuje pozycjê startow¹ elipsy do obiektu pseudofizycznego
		if (phs) phsx = new phsxObj(eli.point);

	};
	Eli::~Eli() {

	};
	float Eli::GetSetX(float x) {
		if (x != NULL) {
			this->SetX(abs(x));
		}
		return this->GetX();
	};
	float Eli::GetSetY(float y) {
		if (y != NULL) {
			this->SetY(abs(y));
		}

		return this->GetY();
	};

	const D2D1_POINT_2F& Eli::EGetPoint(float e) { return eli.point; };
	bool Eli::Init(Graphics* gfx)  {
		//Do usuniêcia
		return true;

	}

	void Eli::DrawVelocityVect(Graphics* gfx) {
		gfx->DrawLine(eli.point, this->phsx->vVect->v_0, this->phsx->vVect->len, this->phsx->vVect->angle, 0.2f, 0.3f, 0.4f, 1.0f);
	};

	phsxObj& Eli::Getpshx() {
		return *phsx;
	}

	void Eli::Render(Graphics* gfx, float r, float g, float b, float a)  {

		gfx->DrawEllipse(&eli, r, g, b, a);
		//	gfx->DrawCircle(Eli::GetX(), Eli::GetY(), r, 1.0f, 0.0f, 0.0f, 1.0f);
		if (debugmode == true)DrawVelocityVect(gfx);
	};

	void Eli::Fill(Graphics* gfx, float e[])  {};
	bool Eli::CheckTrigg(const POINT& p)  {
		if (p.x >= (eli.point.x - eli.radiusX / 2) && p.x <= (eli.point.x + eli.radiusX / 2)) {
			if (p.y >= (eli.point.y - eli.radiusY / 2) && p.y <= (eli.point.y + eli.radiusY / 2)) {
				this->SetTrig(true);
				return this->GetTrig();
			}
		}
		this->SetTrig(false);
		return this->GetTrig();
	};

	bool Eli::CheckTrigg(const D2D1_POINT_2F& p)  {
		if (p.x >= (eli.point.x - eli.radiusX / 2) && p.x <= (eli.point.x + eli.radiusX / 2)) {
			if (p.y >= (eli.point.y - eli.radiusY / 2) && p.y <= (eli.point.y + eli.radiusY / 2)) {
				this->SetTrig(true);
				return this->GetTrig();
			}
		}
		this->SetTrig(false);
		return this->GetTrig();

	};

	void Eli::Update(POINT& p)  {
		this->CheckTrigg(p);


		eli.point.x = this->GetSetX(p.x);
		eli.point.y = this->GetSetY(p.y);
		//phsx->UpdatePsxCtr(p.x,p.y);
	};

	void Eli::Update(float x, float y)  {
		this->ttl += GameController::increment * 1.0f;

		if (phsx != nullptr) {
			phsx->PhsxUpdate(this->eli.point, ttl, x, y);
			this->SetX(eli.point.x);
			this->SetY(eli.point.y);
			int e = 0;
		}
	};





	Recta::Recta(float x, float y, float width, float height, Graphics* gfx, bool phs) : Obj(x, y) {

		if (width == NULL || height == NULL) {
			Recta::Obj::~Obj();
		}

		//Powtórzone informacje, mog¹ siê przydaæ ale zobaczymy

		this->bmp = nullptr;
		this->rec = { 0 };
		this->center = { 0 };
		this->width = width;
		this->height = height;
		float l, t, r, b;
		l = x - width / 2.0;
		r = x + width / 2.0;
		t = y - height / 2.0;
		b = y + height / 2.0;
		rec = D2D1::RectF(l, t, r, b);
		UpdateCenter();
		if (phs) phsx = new phsxObj(center, FAST);

	};

	Recta::Recta(float x, float y, float width, float height, bool phs) : Obj(x, y) {

		if (width == NULL || height == NULL) {
			Recta::Obj::~Obj();
		}

		//Powtórzone informacje, mog¹ siê przydaæ ale zobaczymy

		this->bmp = nullptr;
		this->rec = { 0 };
		this->center = { 0 };
		this->width = width;
		this->height = height;
		float l, t, r, b;
		l = x - width / 2.0;
		r = x + width / 2.0;
		t = y - height / 2.0;
		b = y + height / 2.0;
		rec = D2D1::RectF(l, t, r, b);
		UpdateCenter();
		if (phs) phsx = new phsxObj(center, FAST);

	};

	Recta::Recta(const Recta& rec) : Obj(rec.GetX(), rec.GetY()) {

		if (width == NULL || height == NULL) {
			Recta::Obj::~Obj();
		}

		//Powtórzone informacje, mog¹ siê przydaæ ale zobaczymy

		this->bmp = rec.bmp;
		this->center = rec.center;
		this->width = rec.width;
		this->height = rec.height;
		float l, t, r, b;
		l = rec.rec.left;
		r = rec.rec.right;
		t = rec.rec.top;
		b = rec.rec.bottom;
		this->rec = D2D1::RectF(l, t, r, b);
		UpdateCenter();
		if (phsx) phsx = new phsxObj(center, FAST);

	};
	Recta::Recta(const Recta* rec) : Obj(rec->GetX(), rec->GetY()) {

		if (width == NULL || height == NULL) {
			Recta::Obj::~Obj();
		}

		//Powtórzone informacje, mog¹ siê przydaæ ale zobaczymy

		this->bmp = rec->bmp;
		this->center = rec->center;
		this->width = rec->width;
		this->height = rec->height;
		float l, t, r, b;
		l = rec->rec.left;
		r = rec->rec.right;
		t = rec->rec.top;
		b = rec->rec.bottom;
		this->rec = D2D1::RectF(l, t, r, b);
		UpdateCenter();
		if (phsx) phsx = new phsxObj(center, FAST);

	};

	Recta::~Recta() {

	};
	D2D1_RECT_F& Recta::GetRect() { return rec; }
	void Recta::SetRect(D2D1_RECT_F rect) {
		rec.left = rect.left;
		rec.top = rect.top;
		rec.right = rect.right;
		rec.bottom = rect.bottom;
		UpdateCenter();
	}
	void Recta::UpdateCenter(float x, float y) {
		//KOORDYNATY CENTRUM PROSTOK¥TA NIE MOG¥ BYÆ UJEMNE
		if (signbit(x) == true || signbit(y) == true) return;

		center.x = x;
		center.y = y;


	};

	D2D1_POINT_2F& Recta::GetCenter() { return center; }

	void Recta::UpdateCenter() {
		center.x = (rec.left + rec.right) / 2;
		center.y = (rec.top + rec.bottom) / 2;

	};

	bool Recta::Init(Graphics* gfx)  {

		return true;

	};

	void Recta::Render(Graphics* gfx, float r, float g, float b, float a)  {

		gfx->DrawRect(&rec, 0.4f, 0.8f, 0.6f, 0.7f);
		if (debugmode == true) {
			DrawVelocityVect(gfx);
		}

	};

	phsxObj& Recta::Getpshx() {
		return *phsx;
	}

	void Recta::Fill(Graphics* gfx, float e[])  {
		gfx->FillRect(&rec, e);


	}

	void Recta::Fill(Graphics* gfx, float r, float g, float b, float a) {
		gfx->FillRect(&rec, r, g, b, a);


	}

	bool Recta::CheckTrigg(const POINT& p)  {
		if (p.x >= rec.left && p.x <= rec.right) {
			if (p.y >= rec.top && p.y <= rec.bottom) {
				this->SetTrig(true);
				return this->GetTrig();
			}
		}
		this->SetTrig(false);
		return this->GetTrig();
	};

	bool Recta::CheckTrigg(const D2D1_POINT_2F& p)  {
		if (p.x >= rec.left && p.x <= rec.right) {
			if (p.y >= rec.top && p.y <= rec.bottom) {
				this->SetTrig(true);
				return this->GetTrig();
			}
		}
		this->SetTrig(false);
		return this->GetTrig();
	}
	bool Recta::CheckTrigg(const D2D1_RECT_F& p)
	{
		
		
		if (CheckTrigg(D2D1::Point2F(p.left, p.top))) {
			this->SetTrig(true);
			return this->GetTrig();
		}
		if (CheckTrigg(D2D1::Point2F(p.right, p.top))) {
			this->SetTrig(true);
			return this->GetTrig();
		}
		if (CheckTrigg(D2D1::Point2F(p.left, p.bottom))) {
			this->SetTrig(true);
			return this->GetTrig();
		}
		if (CheckTrigg(D2D1::Point2F(p.right, p.bottom))) {
			this->SetTrig(true);
			return this->GetTrig();
		}

		this->SetTrig(false);
		return this->GetTrig();
	}
	;

	void Recta::DrawVelocityVect(Graphics* gfx) {
		if (phsx)
			gfx->DrawLine(center, phsx->vVect->v_0, phsx->vVect->len, phsx->vVect->angle, 1.0f, 0.3f, 0.4f, 1.0f);
	};

	void Recta::Update(POINT& p)  {
		rec.left = p.x - width / 2.0f;
		rec.right = p.x + width / 2.0f;
		rec.top = p.y - height / 2.0f;
		rec.bottom = p.y + height / 2.0f;

		UpdateCenter(p.x, p.y);
		phsx->UpdatePsxCtr(D2D1::Point2F(p.x, p.y));
	}

	void Recta::Update(float x , float y )  {
		//updatetrigger
		this->ttl += GameController::increment;


		//updateloc
		/*
			SetX(x);
			SetY(y);
			rec.bottom += y;
			rec.top += y;
			rec.left += x;
			rec.right += x;

		*/

		if (phsx != nullptr) {

			//Do something here, something with making next input a modulated previous result
			phsx->PhsxUpdate(center, ttl, x, y);

			rec.bottom = center.y + (height / 2.0f);
			rec.top = center.y - (height / 2.0f);
			rec.right = center.x + (width / 2.0f);
			rec.left = center.x - (width / 2.0f);

		}


	};

	void Recta::Update(float x, float y, bool grav) {
		//updatetrigger
		this->ttl += GameController::increment;


		//updateloc
		/*
			SetX(x);
			SetY(y);
			rec.bottom += y;
			rec.top += y;
			rec.left += x;
			rec.right += x;

		*/

		if (phsx != nullptr) {

			//Do something here, something with making next input a modulated previous result
			phsx->PhsxUpdate(center, ttl, x, y, LINEAR, grav);

			rec.bottom = center.y + (height / 2.0f);
			rec.top = center.y - (height / 2.0f);
			rec.right = center.x + (width / 2.0f);
			rec.left = center.x - (width / 2.0f);

		}


	};
	
	ID2D1Bitmap** Recta::GetBmp() {

		return &bmp;
	};

	Recta Recta::operator= (const Recta& thingy) {
		debugmode = thingy.debugmode;
		phsx = thingy.phsx;
		D2D1_POINT_2U temp = D2D1::Point2U(0.0f, 0.0f);
		const D2D1_RECT_U rectemp = D2D1::RectU(thingy.rec.left, thingy.rec.top, thingy.rec.right, thingy.rec.bottom);
		bmp->CopyFromBitmap(&temp, thingy.bmp, &rectemp);
		actionbmp->CopyFromBitmap(&temp, thingy.actionbmp, &rectemp);
		ttl = thingy.ttl;

		rec = thingy.rec;
		width = thingy.width;
		height = thingy.height;
		center = thingy.center;
		bool phs = false;
		if (thingy.phsx != nullptr) {
			phs = true;
		}

		return new Recta(thingy.GetX(),thingy.GetY(),thingy.width,thingy.height,phs);
	};

	Recta Recta::operator= (Recta* thingy) {
		debugmode = thingy->debugmode;
		phsx = thingy->phsx;
		D2D1_POINT_2U temp = D2D1::Point2U(0.0f, 0.0f);
		//	bmp->CopyFromBitmap(&temp, thingy.bmp, thingy.rec);
		//	actionbmp->CopyFromBitmap(&temp, thingy.actionbmp, thingy.rec);
		ttl = thingy->ttl;

		rec = thingy->rec;
		width = thingy->width;
		height = thingy->height;
		center = thingy->center;

		bool phs = false;
		if (thingy->phsx != nullptr) {
			phs = true;
		}

		return new Recta(thingy->GetX(), thingy->GetY(), thingy->width, thingy->height, phs);
	};

