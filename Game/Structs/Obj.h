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
	virtual ~Obj();
	virtual void Render() = 0;
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
	float r;
	float r, g, b, a;

public:
	Eli(int x, int y, int r) : Obj(x, y) { if (r == NULL) Eli::Obj::~Obj(); m_pEllipseGeometry = NULL; };
	void Render(Graphics* gfx) {
		if (!m_pEllipseGeometry) {

		}
	//	gfx->DrawCircle(Eli::GetX(), Eli::GetY(), r, 1.0f, 0.0f, 0.0f, 1.0f);
	};
	void Update();

};



class Cube : public Obj {

public:
	void Render();
    void Update();

};