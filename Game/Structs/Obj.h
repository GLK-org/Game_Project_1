#pragma once
#include "Core\CoreMinimal.h"
#define RED float[3] {1.0f,0.0f,0.0f};
#define GREEN float[3] {0.0f,1.0f,0.0f};
#define BLUE float[3] {0.0f,0.0f,1.0f};


class Obj {
	float posx, posy;

public:
	Obj(float x, float y) : posx(x), posy(y) { if (x == NULL || y == NULL) Obj::~Obj(); 
	};
	float GetX() { return posx; };
	float GetY() { return posy; };
	void SetX(float x) {posx=x; };
	void SetY(float y) {posy=y; };
	virtual bool Init(Graphics* gfx) = 0;
	virtual void Render(Graphics* gfx) = 0;
	virtual void Update(int i[] = { 0 }) = 0;
	virtual void Transform(Graphics* gfx, float tab[2]) = 0;
	virtual void Fill(Graphics* gfx) =0;
	virtual ~Obj() { };
};

class ColTex {
	
	//oteksturowanie bêdzie tutaj

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
		//Do usuniêcia
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
	void Fill(Graphics* gfx) override {};
	void Update(int i[] = { 0 }) override {

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
		//Powtórzone informacje, mog¹ siê przydaæ ale zobaczymy
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
	void Fill(Graphics* gfx) override {
		gfx->FillRect(&rec);


	}
	void Update(int i[] = { 0 }) override {
	/*	rec.bottom =0;
		rec.top=0;
		rec.left=0;
		rec.right=0;*/
	};

	~Recta() {
		Obj::~Obj();
	}
};