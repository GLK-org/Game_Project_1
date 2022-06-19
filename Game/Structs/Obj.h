#pragma once
#include "GameController.h"
#include "CoreMinimal.h"
#include "Phys_obj.h"

#define RED float[3] {1.0f,0.0f,0.0f};
#define GREEN float[3] {0.0f,1.0f,0.0f};
#define BLUE float[3] {0.0f,0.0f,1.0f};

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};


class Obj {

	
	bool istriggered;

public:
	D2D1_POINT_2F center;
	float frametime, actionframetime;
	int frame, actionframe;
	bool debugmode;
	phsxObj* phsx;
	ID2D1Bitmap* bmp;
	ID2D1Bitmap* actionbmp;
	float ttl;
	Direction direction;
	Obj(float x, float y);



	float GetX() const;
	float GetY() const;
	D2D1_POINT_2F GetCenter() const;
	Direction GetDirctn();
	void SetDirctn(Direction dir);
	bool GetTrig() const;
	void SetX(float x);
	void SetY(float y);
	void SetTrig(bool t);
	void ToggleDebug();
	virtual bool Init(Graphics* gfx) = 0;
	virtual void Render(Graphics* gfx, float r, float g, float b, float a) = 0; //Render needs to be changed as well with bitmaps
	virtual bool CheckTrigg(const POINT& p) = 0;
	virtual bool CheckTrigg(const D2D1_POINT_2F& p) = 0;
	virtual void Update(POINT& p) = 0;
	virtual void Update(float x=0, float y=0) = 0;
	virtual void Fill(Graphics* gfx, float e[] = { 0 }) = 0;
	virtual ~Obj();

};


