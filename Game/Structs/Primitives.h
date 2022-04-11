#pragma once
#include "Obj.h"
#include "Phys_obj.h"

class Eli : public Obj {
	D2D1_ELLIPSE eli;
	float w, h;
	float r;

public:
	Eli(float x, float y, float r, float w, float h, Graphics* gfx, bool phs=true) : Obj(x, y) {
		if (w == NULL || h == NULL) {
			Eli::Obj::~Obj();
		}
		
		this->eli = { 0 };
		this->w = w;
		this->h = h;
		this->r = r;
		eli = D2D1::Ellipse(D2D1::Point2F(this->GetX(), this->GetY()), w, h);
		//Zapisuje pozycjê startow¹ elipsy do obiektu pseudofizycznego
		if(phs) phsx = new phsxObj(eli.point);
		
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

	void DrawVelocityVect(Graphics* gfx) {
		gfx->DrawLine(eli.point, this->phsx->vVect->v_0, this->phsx->vVect->len, 0.2f, 0.3f, 0.4f, 1.0f);
	};

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
		if(debugmode==true)DrawVelocityVect(gfx);
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
	bool CheckTrigg(const D2D1_POINT_2F& p) override {
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
		this->ttl += GameController::increment * 1.0f;

		if (phsx!=nullptr) {
			phsx->LinAccelerate(this->eli.point, x, y);
			phsx->PhsxUpdate(this->eli.point, FAST);
		}
		
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
	}
};

class Recta : public Obj {
	ID2D1Bitmap* bmp;
	D2D1_RECT_F rec;
	D2D1_POINT_2F center;

public:
	Recta(float x, float y, float width, float height, Graphics* gfx, bool phs = true) : Obj(x, y) {
		if (width == NULL || height == NULL ) {
			Recta::Obj::~Obj();
		}
		//Powtórzone informacje, mog¹ siê przydaæ ale zobaczymy
		this->bmp = nullptr;
		this->rec = { 0 };
		this->center = { 0 };
		float l, t, r, b;
		l = x - width / 2.0;
		r = x + width / 2.0 ;
		t = y - height / 2.0 ;
		b = y + height / 2.0 ;
		rec = D2D1::RectF(l, t, r, b);
		center.x =  r - l;
		center.y = b - t;
		if(phs) phsx = new phsxObj(center, FAST);
		
	};
	void UpdateCenter(float x, float y) {
		//KOORDYNATY CENTRUM PROSTOK¥TA NIE MOG¥ BYÆ UJEMNE
		if (signbit(x) == true || signbit(y) == true) return;
		center.x = x;
		center.y = y;

	};

	void UpdateCenter() {
		center.x = (rec.left - rec.right) / 2;
		center.y = (rec.bottom - rec.top) / 2;
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
		if (debugmode==true) {
			DrawVelocityVect(gfx);
		}
		
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
	bool CheckTrigg(const D2D1_POINT_2F& p) override {
		if (p.x >= rec.left && p.x <= rec.right) {
			if (p.y >= rec.top && p.y <= rec.bottom) {
				this->SetTrig(true);
				return this->GetTrig();
			}
		}
		this->SetTrig(false);
		return this->GetTrig();
	};
	void DrawVelocityVect(Graphics* gfx) {
		gfx->DrawLine(center, phsx->vVect->v_0, phsx->vVect->len, 0.2f, 0.3f, 0.4f, 1.0f);
	}; 

	void Update(POINT& p) override {
		this->CheckTrigg(p);
		rec.left = this->GetX() - (1 / 2) * rec.right;
		rec.right = this->GetX() + (1 / 2) * rec.right;
		rec.top = this->GetY() - (1 / 2) * rec.bottom;
		rec.bottom += this->GetY() + (1 / 2) * rec.bottom;
		UpdateCenter();
	}

	void Update(float x = 0, float y = 0) override {
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
			phsx->LinAccelerate(center, x, y);
			phsx->PhsxUpdate(center);
			rec.bottom = 2 * center.y;
			rec.top = rec.bottom - center.y;
			rec.right = 2 * center.x;
			rec.left = rec.right - center.x;
		}
		
		this->SetX(center.y);
		this->SetY(center.x);

	};
	ID2D1Bitmap** GetBmp() {

		return &bmp;
	};

	~Recta() {
		delete bmp;
	};
};
