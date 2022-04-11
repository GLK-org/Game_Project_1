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

void VelocVect::UpdateLoc(const D2D1_POINT_2F& v_0) {
		this->v_0.x += v_0.x;
		this->v_0.y += v_0.y;
	
}

void VelocVect::Length(const D2D1_POINT_2F& v_0, float lim)
 {
 float Diffx = this->v_0.x;
 float Diffy =  this->v_0.y;
 float res = sqrt((pow(Diffx, 2.0) + pow(Diffy, 2.0)));
 if (res > lim) {
	 len = lim;
	 return;
 }
 else {
	 len = res;
	 return;
 }
	

	}
void VelocVect::Angle(const D2D1_POINT_2F& origin) {
	//Zmienne �eby po prostu wygodniej by�o wpisywa� wsp�rz�dne
	float Diffx = (this->v_0.x-origin.x)*std::numbers::pi;
	float Diffy = (this->v_0.y-origin.y) * std::numbers::pi;
	
	if (Diffx > 90.0f ) {
		Diffx = 90.0f * std::numbers::pi;
		
	}
	else if (Diffx < -90.0f) {
		Diffx = -90.0f * std::numbers::pi;
	}
	if (abs(Diffy) > 180.0f && signbit(Diffy)==true) {
		Diffy = 180.0f * std::numbers::pi;

	}
	else if (abs(Diffy) > 180.0f && signbit(Diffy)==false) {
           Diffy = 0.0f * std::numbers::pi;
	}

	angle.x =  sin(Diffx/ 180.0);
	angle.y = cos(Diffy/ 180.0);
//	OutputDebugStringA(MakeLPCSTR( &angle.y ));
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
