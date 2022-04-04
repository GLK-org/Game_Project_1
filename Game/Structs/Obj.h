#pragma once
#include "Core\CoreMinimal.h"
#include "Level_control\GameController.h"
#define RED float[3] {1.0f,0.0f,0.0f};
#define GREEN float[3] {0.0f,1.0f,0.0f};
#define BLUE float[3] {0.0f,0.0f,1.0f};


class Obj {
	float posx, posy;
	bool istriggered;

public:
	float ttl;
	Obj(float x, float y) : posx(x), posy(y) {
		ttl = 0.0f;
		istriggered = false; 
		if (x == NULL || y == NULL) Obj::~Obj();
	};
	float GetX() { return posx; };
	float GetY() { return posy; };
	bool GetTrig() { return istriggered; };
	void SetX(float x) {posx=x; };
	void SetY(float y) {posy=y; };
	void SetTrig(bool t) { istriggered=t; };
	virtual bool Init(Graphics* gfx) = 0;
	virtual void Render(Graphics* gfx, float r, float g, float b, float a) = 0;
	virtual bool CheckTrigg(const POINT& p) { return this->GetTrig(); };
	virtual void Update(POINT& p, bool move = false, float i[] = { 0 }) = 0;
	virtual void Transform(Graphics* gfx, float tab[2]) = 0;
	virtual void Fill(Graphics* gfx, float e[] = { 0 }) =0;
	virtual ~Obj() { };
};

class Eli : public Obj {
	D2D1_ELLIPSE eli;
    ID2D1EllipseGeometry* m_pEllipseGeometry;
	//Niepotrzebnie trzymane dodatkowo
	float w, h;
	float r;

public:
	Eli(float x, float y, float r, float w, float h, Graphics* gfx) : Obj(x, y) { 
		if (w == NULL || h == NULL) {
			Eli::Obj::~Obj(); 
					}
		this->eli = { 0 };
		this->m_pEllipseGeometry = nullptr;
		this->w = w;
		this->h = h;
		this->r = r;
		eli = D2D1::Ellipse(D2D1::Point2F(this->GetX(), this->GetY()), w, h);
	};
	D2D1_POINT_2F EGetPoint(float e) {return eli.point; };
	bool Init(Graphics* gfx) override {
		//Do usuniêcia
		return true;

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

	};
	void Fill(Graphics* gfx, float e[] = { 0 }) override {};
	bool CheckTrigg(const POINT& p) override {
		if (p.x >= (eli.point.x-eli.radiusX/2) && p.x <= (eli.point.x + eli.radiusX/2)) {
			if (p.y >= (eli.point.y - eli.radiusY/ 2) && p.y <= (eli.point.y + eli.radiusY/ 2)) {
				this->SetTrig(true);
				return this->GetTrig();
			}
		}
		this->SetTrig(false);
		return this->GetTrig();
	};
	void Update(POINT& p, bool move = false, float i[] = { 0 }) override {
		this->ttl += GameController::increment;
		//updatetrigger
		this->CheckTrigg(p);

		//updateloc
		if (i == nullptr || (sizeof(i)/sizeof(*i)) < 2 ) {

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
		eli.point.y = i[1];
	};
	~Eli()  {
		if (m_pEllipseGeometry) {
			m_pEllipseGeometry->Release();
		}
		Obj::~Obj();
	} 
};

class Recta : public Obj {
	ID2D1Bitmap* bmp;
	D2D1_RECT_F rec;
	//Niepotrzebnie trzymane dodatkowo
	float left, right, top, bottom;

public:
	Recta(float x, float y, float l, float t, float r, float b, Graphics* gfx) : Obj(x, y) {
		if (l== NULL || r == NULL || t == NULL || b == NULL) {
			Recta::Obj::~Obj();
		}
		//Powtórzone informacje, mog¹ siê przydaæ ale zobaczymy
		this->bmp = nullptr;
		this->rec = { 0 };
		this->left = l;
		this->top = t;
		this->right = r;
		this->bottom = b;
		rec = D2D1::RectF(l, t, r, b);
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

		gfx->DrawRect(&rec, 0.4f,0.8f,0.6f,0.7f);

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

	void Update(POINT& p, bool move = false, float i[] = { 0 }) override {
		//updatetrigger
		this->ttl += GameController::increment;


		//updateloc
		if (move) {

		
		if (i == nullptr) {

			rec.bottom = this->GetY();
			rec.top = this->GetY();
			rec.left = this->GetX();
			rec.right = this->GetX();
			return;
		}

		SetX(i[0]);
		SetY(i[1]);
		rec.bottom = i[1] -rec.bottom;
		rec.top = i[1]-rec.top;
		rec.left = i[0]- rec.left;
		rec.right = i[0]- rec.right;
		}
	}

	ID2D1Bitmap** GetBmp() {

		return &bmp;
	}

	~Recta() {
		Obj::~Obj();
	}
};

