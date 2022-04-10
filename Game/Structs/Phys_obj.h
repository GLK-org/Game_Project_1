#pragma once
#include "CoreLogging.h"
#include "CoreTransforms.h"

struct phsxObj {
	VelocVect* vVect;
	float mass;//??
	float accellim;
	bool collidex, collidey;
	//Do zabawy


	phsxObj(){
		collidex = collidey = false;
		vVect = new VelocVect();
		mass = 0.0f;
		accellim = 2.5f;
	}

	phsxObj(D2D1_POINT_2F& e, double m=0.0f) {
		collidex = collidey = false;
		vVect = new VelocVect(e);
		mass = m;
		accellim = 2.5f;
	}
	void LinAccelerate(const D2D1_POINT_2F& p, double ax, double ay) {
		

		//OutputDebugStringA(MakeLPCSTR( { &(vVect->len) } ) );
		//OutputDebugStringA(MakeLPCSTR({ &(vVect->v_0.x) }));
		//OutputDebugStringA(MakeLPCSTR({ &(vVect->v_0.y) }));
		
		D2D1_POINT_2F e = {ax,ay};
		vVect->UpdateLoc(e);
		vVect->Angle(p);

		vVect->Length(p, accellim);

		
	}
	void LinAccelerate(const D2D1_POINT_2F& p) {


		//OutputDebugStringA(MakeLPCSTR( { &(vVect->len) } ) );
		//OutputDebugStringA(MakeLPCSTR({ &(vVect->v_0.x) }));
		//OutputDebugStringA(MakeLPCSTR({ &(vVect->v_0.y) }));
		float ax, ay;
		ax = (float)(rand() % 10);
		ay = (float)(rand() % 10);
		D2D1_POINT_2F e = { ax,ay };
		vVect->UpdateLoc(e);
		vVect->Angle(p);

		vVect->Length(p, accellim);


	}

	void SqrdAccelerate(double ax, double ay) {
		POINT p(ax, ay);
		Sq(p, accellim);
		vVect->v_0.x += ax;
		vVect->v_0.y += ay;
	}

	void LinDeccelerate(double ax, double ay) {
		vVect->v_0.x -= ax;
		vVect->v_0.y -= ay;
	}

	void SqrdDeccelerate(double ax, double ay) {
		POINT p(ax, ay);
		Sq(p, accellim);
		vVect->v_0.x -= ax;
		vVect->v_0.y -= ay;
	}

	void PhsxUpdate(D2D1_POINT_2F& target) {
		//prymitywne collidery ale ¿eby coœ by³o
		//k¹t modyfikuje tu przyspieszenie, ogólnie nie ogranicza siê tylko do wskazywania kierunku
		//w którym pchaæ ma length
		if (!collidex) {
			target.x += vVect->len * (vVect->angle.x)/ abs(vVect->angle.x);
		}
		if (!collidey) {
			target.y += vVect->len * (vVect->angle.y) / abs(vVect->angle.y);
		}
		
	}
};