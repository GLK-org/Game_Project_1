#pragma once
#include "CoreLogging.h"
#include "CoreTransforms.h"
#include "GameController.h"
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

	phsxObj(D2D1_POINT_2F& e, float speed = SLOW, double m=0.0f) {
		collidex = collidey = false;
		vVect = new VelocVect(e);
		mass = m;
		accellim = speed;
	}
	void SetVLim(float lim) {
		if (signbit(lim) == true) return;
		accellim = lim;
	}
	void ClearSpeed() {
		//vVect->v_0.x = vVect->v_0.y = 0.0f;
		//vVect->angle.x = vVect->angle.y = 0.0f;
		vVect->len = 0.0f;
	}
	void LinAccelerate(const D2D1_POINT_2F& center, double ax, double ay, bool active=false) {
		//basic gravity, not a function but a parameter, to develop

		//OutputDebugStringA(MakeLPCSTR( { &(vVect->len) } ) );
		//OutputDebugStringA(MakeLPCSTR({ &(vVect->v_0.x) }));
		//OutputDebugStringA(MakeLPCSTR({ &(vVect->v_0.y) }));
		this->active = active;
		if (GameController::gravity)
									{
			D2D1_POINT_2F e = { ax,ay + GRAV };
		vVect->UpdateLoc(e,center);
			}
		else {
			D2D1_POINT_2F e = { ax,ay };
			vVect->UpdateLoc(e,center);
		}

	}
	void LinAccelerate(const D2D1_POINT_2F& center, const D2D1_POINT_2F& p, bool active=false) {


		//OutputDebugStringA(MakeLPCSTR( { &(vVect->len) } ) );
		//OutputDebugStringA(MakeLPCSTR({ &(vVect->v_0.x) }));
		//OutputDebugStringA(MakeLPCSTR({ &(vVect->v_0.y) }));
		this->active = active;
		if (GameController::gravity)
		{
		D2D1_POINT_2F e = { p.x,p.y+GRAV };
		vVect->UpdateLoc(e, center);
	}
		else {
		D2D1_POINT_2F e = { p.x,p.y };
		vVect->UpdateLoc(e, center);
		}

	}
	

	void SqrdAccelerate(double ax, double ay) {
		POINT p(ax, ay);
//		Sq(p, accellim);
		vVect->v_0.x += ax;
		vVect->v_0.y += ay;
	}

	void LinDeccelerate(const D2D1_POINT_2F& center, float ttl, float speed=1.1f) {
		vVect->len = vVect->len/(ttl * speed);
	}

	void SqrdDeccelerate(double ax, double ay) {
		POINT p(ax, ay);
//		Sq(p, accellim);
		vVect->v_0.x -= ax;
		vVect->v_0.y -= ay;
	}

	void PhsxUpdate(D2D1_POINT_2F& center,float ttl,bool decel=false, float speed =SLOW) {
		//prymitywne collidery ale ¿eby coœ by³o
		//k¹t modyfikuje tu przyspieszenie, ogólnie nie ogranicza siê tylko do wskazywania kierunku
		//w którym pchaæ ma length
		if (signbit(accellim) == false) {
			accellim = speed;
		}
		if (active) {
			LinDeccelerate(center, ttl);
		}
		
		if (!collidex) {
			center.x += vVect->len * (vVect->angle.x);
		}

		if (!collidey) {
			center.y += vVect->len * (vVect->angle.y);
		}
		
	}

	
	~phsxObj() {
		delete vVect;
	}
};