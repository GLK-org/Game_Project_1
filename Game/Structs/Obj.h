#pragma once
#include "Core\CoreMinimal.h"
#define RED float[3] {1.0f,0.0f,0.0f};
#define GREEN float[3] {0.0f,1.0f,0.0f};
#define BLUE float[3] {0.0f,0.0f,1.0f};


class Obj {
	float posx, posy;

public:
	Obj(int x, int y) : posx(x), posy(y) { if (posx == NULL || posy == NULL) Obj::~Obj(); };
	float GetX() { return posx; };
	float GetY() { return posy; };
	virtual ~Obj() { };
	virtual void Render(Graphics* gfx) = 0;
	virtual void Update() = 0;
};

class ColTex {
	
	//oteksturowanie bêdzie tutaj

public:
	ColTex();
	~ColTex();
};


class Eli : public Obj {
	ID2D1EllipseGeometry* m_pEllipseGeometry;
	float w, h;
	float r, g, b, a;

public:
	Eli(float x, float y, float r, float w, float h, Graphics* gfx) : Obj(x, y) { 
		if (w == NULL || h == NULL) {
			Eli::Obj::~Obj(); 
					}
		this->w = w;
		this->h = h;

		gfx->CreateEllipseGeometry(x, y, w, h, m_pEllipseGeometry);
	};

	void Render(Graphics* gfx) {
		gfx->DrawGeo(m_pEllipseGeometry);
	//	gfx->DrawCircle(Eli::GetX(), Eli::GetY(), r, 1.0f, 0.0f, 0.0f, 1.0f);
	};
	void Update();

};



class Cube : public Obj {

public:
	void Render();
    void Update();

};