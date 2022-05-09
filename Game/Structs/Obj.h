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

	bool debugmode = true;
	phsxObj* phsx;
	float ttl;

	Obj(float x, float y) : posx(x), posy(y) {

		ttl = 0.0f;
		istriggered = false; 
		if (x == NULL || y == NULL) Obj::~Obj();

	};
	
	float GetX() const { return posx; };
	float GetY() const { return posy; };
	bool GetTrig() const { return istriggered; };
	void SetX(float x) {posx=x; };
	void SetY(float y) {posy=y; };
	void SetTrig(bool t) { istriggered=t; };
	void ToggleDebug() { debugmode = !debugmode; };
	virtual bool Init(Graphics* gfx) = 0;
	virtual void Render(Graphics* gfx, float r, float g, float b, float a) = 0;
	virtual bool CheckTrigg(const POINT& p) =0;
	virtual bool CheckTrigg(const D2D1_POINT_2F& p)=0;
	virtual void Update(POINT& p) = 0;
	virtual void Update(float x=0, float y=0) = 0;
//	virtual void DrawVelocityVect(Graphics gfx) = 0;
	virtual void Transform(Graphics* gfx, float tab[2]) = 0;
	virtual void Fill(Graphics* gfx, float e[] = { 0 }) =0;
//	virtual void phsxUpdate(float x=0, float y=0) = 0;
	virtual ~Obj() { delete phsx; };
};


