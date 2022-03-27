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
	virtual void Update() = 0;
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
	};

	bool Init(Graphics* gfx) {
		eli = D2D1::Ellipse(D2D1::Point2F(this->GetX(),this->GetY()), w, h);
		gfx->CreateEllipseGeometry(eli, &m_pEllipseGeometry);
		return true;

	}

	void Render(Graphics* gfx) {	
		
		 gfx->DrawGeo(m_pEllipseGeometry);
	//	gfx->DrawCircle(Eli::GetX(), Eli::GetY(), r, 1.0f, 0.0f, 0.0f, 1.0f);
	};
	void Update() {
		eli.point.x = this->GetX();
		eli.point.y = this->GetY();
	};
	~Eli()  {
		if (m_pEllipseGeometry) {
			m_pEllipseGeometry->Release();
		}
		Obj::~Obj();
	} 
};

class Cube : public Obj {

public:
	void Render();
    void Update();

};