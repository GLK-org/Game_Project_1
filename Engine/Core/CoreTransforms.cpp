#pragma once
#include "Engine.h"
#include "CoreTransforms.h"

VelocVect::VelocVect(D2D1_POINT_2F& e) {
	v_0.x = e.x;
	v_0.y = e.y;
	len = 0.0f;
	angle.x = angle.y = 0.0f;
}

void VelocVect::UpdatePsxCtr(float x, float y) {
	v_0.x = x;
	v_0.y = y;
}

inline void VelocVect::UpdatePsxCtr(D2D1_POINT_2F p) {
	v_0.x = p.x;
	v_0.y = p.y;

}

inline float VelocVect::Length(const D2D1_POINT_2F& vDirection, const D2D1_POINT_2F& center, float lim)
{
	//Ta funckja mo¿e byæ wtórna, bardziej przydaje siê tu circlelen do obliczania czy promieñ ko³a rysowaniego z center do v_0 jest wiêkszy od lim
	float Diffx =  vDirection.x - center.x;
	float Diffy =  vDirection.y - center.y;
	float res = sqrt((pow(Diffx, 2.0f) + pow(Diffy, 2.0f)));
	return res;
}

inline void VelocVect::Angle(const D2D1_POINT_2F& vDirection, const D2D1_POINT_2F& center) {
	//Obliczanie k¹ta znormalizowan¹ funkcj¹ atan, tj wartoœci od ok. 0 do 1
	float Diffx = (vDirection.x - center.x);
	float Diffy = (vDirection.y - center.y);
	float m=2.0f;
	angle.x =  (4*atan(Diffx) / m)  /std::numbers::pi;
	angle.y =  (4*atan(Diffy) / m)  /std::numbers::pi;
//	OutputDebugStringA(MakeLPCSTR( &angle.y ));

}

void VelocVect::UpdateLoc(const D2D1_POINT_2F& vAdd, const D2D1_POINT_2F& center, float lim) {

	auto euclid = [](float length, float lim) {
		float result=length;
		int two=0;
		while (result > lim) {
			result = result / 2.0f;
			two++;

		}

		
		return two;
	};

	auto euclid2 = [](float& length, float lim) {
		float result = length;
		while (result > lim) {
			result = result / 2.0f;

		}

	};

	auto circlelen = [](float x, float y, float lim) {
		float res = pow(x, 2.0f) + pow(y, 2.0f);
		if (res <= lim) {
			return true;
		}
		return false;
	};

	//funkcje lambda ¿eby odgruzowaæ widocznoœæ funkcji

	float tempx, tempy;
	

	tempx = v_0.x + vAdd.x;
	tempy = v_0.y + vAdd.y;
	D2D1_POINT_2F et(tempx, tempy);
	
	if (circlelen(center.x - tempx, center.y - tempy, lim)) {
		
		float length = Length(et, center, lim);

		if (length <= lim) {
			Angle(et, center);
			if (true);
			v_0.x += vAdd.x;
			v_0.y += vAdd.y;
			len = length;

		}
		else {
			float div = euclid(length, lim);
			if (div == 0) div = 1.0f;
			Angle(et, center);
			v_0.x += vAdd.x / div;
			v_0.y += vAdd.y / div;
			len = lim;

		}
	}
	else{
		//pomniejszenie v_0 ¿eby nie przekracza³o len i po tym ten sam kawa³ek kodu
	euclid2(v_0.x, lim);
	euclid2(v_0.y, lim);

	tempx = v_0.x + vAdd.x;
	tempy = v_0.y + vAdd.y;
	D2D1_POINT_2F et1(tempx, tempy);

	float length = Length(et1, center, lim);
	Angle(et1, center);
	if (true);
	v_0.x += vAdd.x;
	v_0.y += vAdd.y;
	len = length;
	}
	//len = Length(v_0,center, FAST);
	
	

	
}

void Sq(POINT& result, double limit) {
	double tempx = pow(result.x,2.0);
	double tempy = pow(result.y,2.0);

	if (tempx + tempy > limit) {
		return;
	}
	else {
		result.x = tempx;
		result.y = tempy;
		
	}
}

D2D1_POINT_2F Angle(const D2D1_POINT_2F& vDirection, const D2D1_POINT_2F& center)
{
	float Diffx = (vDirection.x - center.x);
	float Diffy = (vDirection.y - center.y);
	float m = 2.0f;
	D2D1_POINT_2F angle(0.0f,0.0f);
	angle.x = (4 * atan(Diffx) / m) / std::numbers::pi;
	angle.y = (4 * atan(Diffy) / m) / std::numbers::pi;
	return angle;
}
D2D1_POINT_2F Angle(const POINT& vDirection, const D2D1_POINT_2F& center)
{
	float Diffx = (vDirection.x - center.x);
	float Diffy = (vDirection.y - center.y);
	float m = 2.0f;
	D2D1_POINT_2F angle(0.0f, 0.0f);
	angle.x = (4 * atan(Diffx) / m) / std::numbers::pi;
	angle.y = (4 * atan(Diffy) / m) / std::numbers::pi;
	return angle;
}

D2D1_VECTOR_2F ENGINE_API Vector_sum(D2D1_POINT_2F vec_0[2], D2D1_POINT_2F vec_1[2])
{
	D2D1_VECTOR_2F sum(0.0f,0.0f);
	

	return sum;
}

float ENGINE_API LLength(const POINT& v_0, const POINT& center, float lim)
{
	float Diffx = v_0.x - center.x;
	float Diffy = v_0.y - center.y;
	float res = sqrt((pow(Diffx, 2.0) + pow(Diffy, 2.0)));
	if (res >= lim) {
		return lim;
	}
	return res;

}

