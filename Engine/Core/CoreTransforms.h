#pragma once
#include "CoreMinimal.h"
#include <math.h>
#include <numbers>

#define TURBO WNDWIDTH*0.004f
#define VERY_FAST WNDWIDTH*0.003f
#define FAST WNDWIDTH*0.002f
#define MEDIUM_FAST WNDWIDTH*0.001f
#define SLOW WNDWIDTH*0.0005f
#define STOP 0.0f
#define GRAV 2.0f

struct ENGINE_API VelocVect {
	D2D1_POINT_2F v_0, angle;
	float len;
	VelocVect();
	VelocVect(D2D1_POINT_2F& e);
	inline void UpdatePsxCtr(float x, float y);
	inline void UpdatePsxCtr(D2D1_POINT_2F p);
	void UpdateLoc(const D2D1_POINT_2F& v_0, const D2D1_POINT_2F& center, float lim=MEDIUM_FAST);
	inline float Length(const D2D1_POINT_2F& v_0, const D2D1_POINT_2F& center, float lim);
	inline	void Angle(const D2D1_POINT_2F& vDirection, const D2D1_POINT_2F& center = { 0 });

};

D2D1_VECTOR_2F ENGINE_API Vector_sum(D2D1_VECTOR_2F vec_0, D2D1_VECTOR_2F vec_1);
float ENGINE_API LLength(const POINT& v_0, const POINT& center, float lim);
void ENGINE_API Sq(const D2D1_POINT_2F& result, double limit);
D2D1_POINT_2F ENGINE_API Angle(const D2D1_POINT_2F& v_0, const D2D1_POINT_2F& v_1);
D2D1_POINT_2F ENGINE_API Angle(const POINT& v_0, const D2D1_POINT_2F& v_1);