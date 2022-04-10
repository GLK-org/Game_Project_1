#pragma once
#include "CoreMinimal.h"
#include <math.h>
#include <numbers>

struct ENGINE_API VelocVect {
	D2D1_POINT_2F v_0, angle;
	float len;
	VelocVect();
	VelocVect(D2D1_POINT_2F& e);
	void UpdateLoc(const D2D1_POINT_2F& v_0);
	void Length(const D2D1_POINT_2F& v_0, float lim);
	void Angle(const D2D1_POINT_2F& v_0 = { 0 });

};

void Sq(POINT& result, double limit);