#pragma once
#include "Obj.h"
#include "Phys_obj.h"



class Eli : public Obj {
	D2D1_ELLIPSE eli;
	float w, h;
	float r;

public:
	Eli(float x, float y, float r, float w, float h, Graphics* gfx, bool phs = true);
	virtual ~Eli();
	float GetSetX(float x = NULL);
	float GetSetY(float y = NULL);

	const D2D1_POINT_2F& EGetPoint(float e);
	bool Init(Graphics* gfx) override;

	void DrawVelocityVect(Graphics* gfx);

	phsxObj& Getpshx();

	void Render(Graphics* gfx, float r, float g, float b, float a) override;

	void Fill(Graphics* gfx, float e[] = { 0 }) override;
	bool CheckTrigg(const POINT& p) override;

	bool CheckTrigg(const D2D1_POINT_2F& p) override;

	void Update(POINT& p) override;

	void Update(float x = 0, float y = 0) override;

	
	

};

class Recta : public Obj {
	D2D1_RECT_F rec;
	float width;
	float height;

public:
	Recta(float x, float y, float width, float height, Graphics* gfx, bool phs = true);
	Recta(float x, float y, float width, float height, bool phs = true);

	Recta(const Recta& rec);
	Recta(const Recta* rec);

	virtual ~Recta();
	D2D1_RECT_F& GetRect();
	void SetRect(D2D1_RECT_F rect);

	void UpdateCenter(float x, float y);

	D2D1_POINT_2F& GetCenter();

	void UpdateCenter();

	bool Init(Graphics* gfx) override;


	void Render(Graphics* gfx, float r, float g, float b, float a) override;
	
	phsxObj& Getpshx();

	void Fill(Graphics* gfx, float e[] = { 0 }) override;

	void Fill(Graphics* gfx, float r, float g, float b, float a);

	bool CheckTrigg(const POINT& p) override;

	bool CheckTrigg(const D2D1_POINT_2F& p) override;

	bool CheckTrigg(const D2D1_RECT_F& p);

	void DrawVelocityVect(Graphics* gfx);

	void Update(POINT& p) override;

	void Update(float x = 0, float y = 0) override;
	void Update(float x, float y, bool grav) ;

	ID2D1Bitmap** GetBmp();

	Recta operator= (const Recta& thingy);


	Recta operator= (Recta* thingy);
};
