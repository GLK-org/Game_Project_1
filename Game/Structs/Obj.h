#pragma once
#include "GameController.h"
#include "CoreMinimal.h"
#include "Phys_obj.h"
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
	virtual void Update(POINT& p) = 0;
	virtual void Update(float x=0, float y=0) = 0;
	virtual void Transform(Graphics* gfx, float tab[2]) = 0;
	virtual void Fill(Graphics* gfx, float e[] = { 0 }) =0;
	virtual ~Obj() { };
};


