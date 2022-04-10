#pragma once
#include "Obj.h"
#include "Phys_obj.h"

class Eli : public Obj {
	D2D1_ELLIPSE eli;
	float w, h;
	float r;

public:
	Eli(float x, float y, float r, float w, float h, Graphics* gfx) : Obj(x, y) {
		if (w == NULL || h == NULL) {
			Eli::Obj::~Obj();
		}
		
		this->eli = { 0 };
		this->w = w;
		this->h = h;
		this->r = r;
		eli = D2D1::Ellipse(D2D1::Point2F(this->GetX(), this->GetY()), w, h);
		//Zapisuje pozycjê startow¹ elipsy do obiektu pseudofizycznego
		phsx = new phsxObj(eli.point);
	};

	float GetSetX(float x=NULL) {
		if (x != NULL) {
			this->SetX(abs(x));
		}
		return this->GetX();
	};
	float GetSetY(float y=NULL) {
		if (y != NULL) {
			this->SetY(abs(y));
		}

		return this->GetY();
	};

	const D2D1_POINT_2F& EGetPoint(float e) { return eli.point; };
	bool Init(Graphics* gfx) override {
		//Do usuniêcia
		return true;

	}

	/*void DrawVelocityVect(Graphics* gfx) {
		gfx->DrawLine(eli.point, this->phsx->vVect->v_0, this->phsx->vVect->len, 0.2f, 0.3f, 0.4f, 1.0f);
	};*/

	phsxObj& Getpshx() {
		return *phsx;
	}
	void Transform(Graphics* gfx, float tab[2]) override {

		if (tab == nullptr || (sizeof(tab) / sizeof(*tab)) < 2) {
			return;
		}
		gfx->DrawBG(eli.point, tab);
	}

	void Render(Graphics* gfx, float r, float g, float b, float a) override {

		gfx->DrawEllipse(&eli, r, g, b, a);
		//	gfx->DrawCircle(Eli::GetX(), Eli::GetY(), r, 1.0f, 0.0f, 0.0f, 1.0f);
		//DrawVelocityVect(gfx);
	};
	void Fill(Graphics* gfx, float e[] = { 0 }) override {};
	bool CheckTrigg(const POINT& p) override {
		if (p.x >= (eli.point.x - eli.radiusX / 2) && p.x <= (eli.point.x + eli.radiusX / 2)) {
			if (p.y >= (eli.point.y - eli.radiusY / 2) && p.y <= (eli.point.y + eli.radiusY / 2)) {
				this->SetTrig(true);
				return this->GetTrig();
			}
		}
		this->SetTrig(false);
		return this->GetTrig();
	};
	void Update(POINT& p) override {
		this->CheckTrigg(p);
		
		
		eli.point.x = this->GetSetX(p.x);
		eli.point.y = this->GetSetY(p.y);

	}

	void Update(float x=0, float y=0) override {
		this->ttl += GameController::increment * 10.0f;


		phsx->LinAccelerate(this->eli.point, x, y);
		phsx->PhsxUpdate(this->eli.point, MEDIUM_FAST);
		//updatetrigger

		//updateloc


		/*
		if (i == nullptr || (sizeof(i) / sizeof(*i)) < 2) {

			eli.point.x = this->GetX();
			eli.point.y = this->GetY();
			return;
		}
		for (int j = 0; j < 2; j++) {
			if (i[j] < 0) {
				return;
			}
		}
		SetX(i[0]);
		SetY(i[1]);
		eli.point.x = i[0];
		eli.point.y = i[1];*/
	};
	/*void phsxUpdate(float x = 0, float y = 0) override {
		this->ttl += GameController::increment * 10.0f;


		phsx->LinAccelerate(this->eli.point, x, y);
		phsx->PhsxUpdate(this->eli.point);
	}*/
	~Eli() {
		Obj::~Obj();
	}
};

class Recta : public Obj {
	ID2D1Bitmap* bmp;
	D2D1_RECT_F rec;
	D2D1_POINT_2F center;

public:
	Recta(float x, float y, float l, float t, float r, float b, Graphics* gfx) : Obj(x, y) {
		if (l == NULL || r == NULL || t == NULL || b == NULL) {
			Recta::Obj::~Obj();
		}
		//Powtórzone informacje, mog¹ siê przydaæ ale zobaczymy
		this->bmp = nullptr;
		this->rec = { 0 };
		rec = D2D1::RectF(l, t, r, b);
		center.x = l - r;
		center.y = b - t;
	};
	void UpdateCenter(float x, float y) {
		//KOORDYNATY CENTRUM PROSTOK¥TA NIE MOG¥ BYÆ UJEMNE
		if (signbit(x) == true || signbit(y) == true) return;
		center.x = x;
		center.y = y;

	};
	bool Init(Graphics* gfx) override {

		return true;

	}
	void Transform(Graphics* gfx, float tab[2]) override {

		if (tab == nullptr || (sizeof(tab) / sizeof(*tab)) < 2) {
			return;
		}
		//gfx->DrawBG(rec.point, tab);
	}
	void Render(Graphics* gfx, float r, float g, float b, float a) override {

		gfx->DrawRect(&rec, 0.4f, 0.8f, 0.6f, 0.7f);

	};
	void Fill(Graphics* gfx, float e[] = { 0 }) override {
		gfx->FillRect(&rec, e);


	}
	bool CheckTrigg(const POINT& p) override {
		if (p.x >= rec.left && p.x <= rec.right) {
			if (p.y >= rec.top && p.y <= rec.bottom) {
				this->SetTrig(true);
				return this->GetTrig();
			}
		}
		this->SetTrig(false);
		return this->GetTrig();
	};
	/*void DrawVelocityVect(Graphics* gfx) {
		gfx->DrawLine({0}, phsx->vVect->v_0, phsx->vVect->len, 0.2f, 0.3f, 0.4f, 1.0f);
	}; */
	void Update(POINT& p) override {
		this->CheckTrigg(p);
		rec.left = this->GetX() - (1 / 2) * rec.right;
		rec.right = this->GetX() + (1 / 2) * rec.right;
		rec.top = this->GetY() - (1 / 2) * rec.bottom;
		rec.bottom += this->GetY() + (1 / 2) * rec.bottom;
	}

	void Update(float x=0, float y=0) override {
		//updatetrigger
		this->ttl += GameController::increment;


		//updateloc
			SetX(x);
			SetY(y);
			rec.bottom += y;
			rec.top += y;
			rec.left += x;
			rec.right += x;
		
	}

/*	void phsxUpdate(float x = 0, float y = 0) override {
		this->ttl += GameController::increment * 10.0f;


		phsx->LinAccelerate(this->center, x, y);
		phsx->PhsxUpdate(this->center);
		rec.bottom += center.y;
		rec.top += center.y;
		rec.left += center.x;
		rec.right += center.x;
	}*/
	ID2D1Bitmap** GetBmp() {

		return &bmp;
	}

	~Recta() {
		Obj::~Obj();
	}
};
