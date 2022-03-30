#pragma once
#include "Core\CoreMinimal.h"
#define RED float[3] {1.0f,0.0f,0.0f};
#define GREEN float[3] {0.0f,1.0f,0.0f};
#define BLUE float[3] {0.0f,0.0f,1.0f};


class Obj {
	float posx, posy;
	bool istriggered;
public:
	Obj(float x, float y) : posx(x), posy(y) {
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
	virtual void Render(Graphics* gfx) = 0;
	virtual bool CheckTrigg(const POINT& p) { return this->GetTrig(); };
	virtual void Update(POINT& p, int i[] = { 0 }) = 0;
	virtual void Transform(Graphics* gfx, float tab[2]) = 0;
	virtual void Fill(Graphics* gfx, float e[] = { 0 }) =0;
	virtual ~Obj() { };
};

class ColTex {
	
	//oteksturowanie b�dzie tutaj

public:
	ColTex();
	~ColTex();
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

	bool Init(Graphics* gfx) override {
		//Do usuni�cia
		return true;

	}
	void Transform(Graphics* gfx, float tab[2]) override {

		if (tab == nullptr || (sizeof(tab) / sizeof(*tab)) < 2) {
			return;
		}
		gfx->DrawBG(eli.point, tab);
	}

	void Render(Graphics* gfx) override {	
		
		 gfx->DrawEllipse(&eli, 0.2f, 0.3f, 0.2f, 0.6f);
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
	void Update(POINT& p, int i[] = { 0 }) override {
		//updatetrigger
		this->CheckTrigg(p);

		//updateloc
		if (i == nullptr || (sizeof(i)/sizeof(*i)) < 2 ) {

			eli.point.x = this->GetX();
			eli.point.y = this->GetY();
			return;
		}

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

	D2D1_RECT_F rec;
	//Niepotrzebnie trzymane dodatkowo
	float left, right, top, bottom;


public:
	Recta(float x, float y, float l, float t, float r, float b, Graphics* gfx) : Obj(x, y) {
		if (l== NULL || r == NULL || t == NULL || b == NULL) {
			Recta::Obj::~Obj();
		}
		//Powt�rzone informacje, mog� si� przyda� ale zobaczymy
		this->rec = { 0 };
		this->left = l;
		this->top = t;
		this->right = r;
		this->bottom = b;
		rec = D2D1::RectF(l, t, r, b);
	};

	bool Init(Graphics* gfx) override {
		
		//gfx->CreateEllipseGeometry(rec, &m_pEllipseGeometry);
		return true;

	}
	void Transform(Graphics* gfx, float tab[2]) override {

		if (tab == nullptr || (sizeof(tab) / sizeof(*tab)) < 2) {
			return;
		}
		//gfx->DrawBG(rec.point, tab);
	}
	void Render(Graphics* gfx) override {
		
		//	gfx->DrawGeo(m_pEllipseGeometry);
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
	void Update(POINT& p, int i[] = { 0 }) override {
		//updatetrigger
		

		//updateloc
		if (i == nullptr) {

			rec.bottom = this->GetY();
			rec.top = this->GetY();
			rec.left = this->GetX();
			rec.right = this->GetX();
			return;
		}
		rec.bottom = i[1];
		rec.top = i[1];
		rec.left = i[0];
		rec.right = i[0];
	}
	~Recta() {
		Obj::~Obj();
	}
};