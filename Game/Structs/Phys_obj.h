#pragma once
#include "CoreTransforms.h"


enum Types {
	LINEAR,
	QUADRATIC,



};

struct phsxObj {
	VelocVect* vVect;
	float mass;//??
	float accellim;
	bool collidex, collidey;
	float active;
	//Do zabawy


	phsxObj(){
		collidex = collidey = false;
		vVect = new VelocVect();
		mass = 0.0f;
		accellim = VERY_FAST;
		active = false;
	}

	phsxObj(D2D1_POINT_2F& e, float speed = SLOW, float m=0.0f) {
		collidex = collidey = false;
		vVect = new VelocVect(e);
		mass = m;
		accellim = speed;
		active = false;
	}
	virtual ~phsxObj() {
		delete vVect;
	}
	phsxObj operator= (const phsxObj& ob) {

	}
	D2D1_POINT_2F GetVelocVect() { return vVect->v_0; }
	void SetVLim(float lim) {
		if (signbit(lim) == true) {
			accellim = lim;
			return;

		}

	}
	D2D1_POINT_2F Get_inv_veloc() {
		D2D1_POINT_2F e(vVect->len, vVect->angle.y);
		return e;
	}
	void YAngleLock()
	{
		if (vVect->angle.y < 0){
			vVect->angle.y = 0.0f;
	 }
	}

		void UpdatePsxCtr(float x, float y) {
		vVect->UpdatePsxCtr(x,y);
	}

	void UpdatePsxCtr(const D2D1_POINT_2F& p) {
		vVect->UpdatePsxCtr(p);
	}

	void ClearSpeed() {
		vVect->len = 0.0f;
		vVect->angle.x = 0.0f;
		vVect->angle.y = 0.0f;
	}

	void ClearSpeed(const D2D1_POINT_2F p) {
		vVect->len = 0.0f;
		vVect->v_0.x = p.x;
		vVect->v_0.y = p.y;
		vVect->angle.x = 0.0f;
		vVect->angle.y = 0.0f;
	}
	void LinAccelerate(const D2D1_POINT_2F& center, float x, float y, bool grav=true) {
		if (x >= 1.0f || y >= 1.0f) {
			this->active = true;
		}
		else {
			this->active = false;
		}
		if (GameController::gravity==true && grav==true)
		{
		D2D1_POINT_2F e = { x,y + (GRAV*mass) };
		vVect->UpdateLoc(e,center,accellim);

			}
		else {
			D2D1_POINT_2F e = { x,y };
			vVect->UpdateLoc(e,center,accellim);
		}

	}
	void LinAccelerate(const D2D1_POINT_2F& center, const D2D1_POINT_2F& p, bool grav = true) {
		if (p.x >= 1.0f || p.y >= 1.0f) {
			this->active = true;
		}
		else {
			this->active = false;
		}
		if (GameController::gravity && grav==true)
		{
		D2D1_POINT_2F e = { p.x,p.y+(GRAV*mass) };
		vVect->UpdateLoc(e, center, accellim);
	}
		else {
		D2D1_POINT_2F e = { p.x,p.y };
		vVect->UpdateLoc(e, center, accellim);
		}

	}
	

	void SqrdAccelerate(double ax, double ay) {
		POINT p(ax, ay);
		vVect->v_0.x += ax;
		vVect->v_0.y += ay;
	}

	void LinDeccelerate(const D2D1_POINT_2F& center, float ttl, float speed=2.0f) {
		if (vVect->len < 1.0f) {
			ClearSpeed(center);
		}
		else {
			LinAccelerate(center,(vVect->len/speed) * (-(vVect->angle.x)), (vVect->len / speed) * (-(vVect->angle.y)));
		}
		
	}

	void SqrdDeccelerate(double ax, double ay) {
		POINT p(ax, ay);
		vVect->v_0.x -= ax;
		vVect->v_0.y -= ay;
	}

	void PhsxUpdate(D2D1_POINT_2F& center,float ttl,float x, float y, Types mode=LINEAR, bool grav=true) {
		//prymitywne collidery ale ¿eby coœ by³o
		//k¹t modyfikuje tu przyspieszenie, ogólnie nie ogranicza siê tylko do wskazywania kierunku
		//w którym pchaæ ma length
		if (mode == LINEAR) {
				
		//	if (active==false) {
			//	LinDeccelerate(center,ttl);
			//}
			//IT ALREADY MARKS THE CENTER IN A NEW PLACE
		//	else {
				LinAccelerate(center, x, y, grav);
		//	}
				center.x += vVect->len * (vVect->angle.x);
				center.y += vVect->len * (vVect->angle.y);
			
		}
		
		
	}

	

};