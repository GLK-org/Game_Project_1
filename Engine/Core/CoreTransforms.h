#pragma once
#include "CoreMinimal.h"
#include <math.h>
#include <numbers>
#define TURBO 10.f
#define VERY_FAST 8.0f
#define FAST 6.0f
#define MEDIUM_FAST 4.0f
#define SLOW 2.0f
#define STOP 0.0f
struct ENGINE_API VelocVect {
	D2D1_POINT_2F v_0, angle;
	float len;
	VelocVect();
	VelocVect(D2D1_POINT_2F& e);
	void UpdateLoc(const D2D1_POINT_2F& v_0);
	void Length(const D2D1_POINT_2F& v_0, float lim);
	void Angle(const D2D1_POINT_2F& v_0 = { 0 });

};

void ENGINE_API Sq(const D2D1_POINT_2F& result, double limit);
double ENGINE_API Angle(const D2D1_POINT_2F& v_0, const D2D1_POINT_2F& v_1, const D2D1_POINT_2F& v_2);