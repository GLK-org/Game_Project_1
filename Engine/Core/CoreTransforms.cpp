#include "Engine.h"
#include "CoreTransforms.h"
#include "CoreLogging.h"

VelocVect::VelocVect() {
	v_0.x = 1.0f;
	v_0.y = 1.0f;
	len = 0.0f;
	angle.x = angle.y = 0.0f;
}
VelocVect::VelocVect(D2D1_POINT_2F& e) {
	v_0.x = 1.0f+e.x;
	v_0.y = 1.0f+e.y;
	len = 0.0f;
	angle.x = angle.y = 0.0f;
}



float VelocVect::Length(const D2D1_POINT_2F& vAdd, const D2D1_POINT_2F& center, float lim)
 {
 float Diffx = v_0.x-center.x;
 float Diffy =  v_0.y-center.y;
 float res = sqrt((pow(Diffx, 2.0) + pow(Diffy, 2.0)));
 if (res >= lim) {
	 return lim;
	}
	 return res;
	}

void VelocVect::Angle(const D2D1_POINT_2F& origin) {
	//Zmienne ¿eby po prostu wygodniej by³o wpisywaæ wspó³rzêdne
	float Diffx = (this->v_0.x - origin.x);
	float Diffy = (this->v_0.y - origin.y);
	float m = 10.0;
	angle.x =  atan((1/m)*Diffx);
	angle.y =  atan((1/m)*Diffy);
//	OutputDebugStringA(MakeLPCSTR( &angle.y ));
}

void VelocVect::UpdateLoc(const D2D1_POINT_2F& vAdd, const D2D1_POINT_2F& center, float lim) {

	float tempx, tempy;
	tempx = this->v_0.x + vAdd.x;
	tempy = this->v_0.y + vAdd.y;
	D2D1_POINT_2F et(tempx, tempy);
	float test = Length(et,center,lim);
	if (0 <= test && test <= lim) {

		this->v_0.x += vAdd.x;
		this->v_0.y += vAdd.y;
		len = test;
		Angle(center);
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

double Angle(const D2D1_POINT_2F& v_0, const D2D1_POINT_2F& v_1, const D2D1_POINT_2F& v_2)
{
	double Diff01x = (double)v_1.x- (double)v_0.x;
	double Diff01y = (double)v_1.y- (double)v_0.y;
	double Diff02x = (double)v_2.x - (double)v_0.x;
	double Diff02y = (double)v_2.y - (double)v_0.y;
	double top = (Diff01x * Diff02x) + (Diff01y * Diff02y);
	double bot = sqrt(pow(Diff01x, 2.0) + pow(Diff01y, 2.0)) * sqrt(pow(Diff02x, 2.0) + pow(Diff02y, 2.0));
	double angle = acos(
				top
				/
				bot );
	return angle;
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
