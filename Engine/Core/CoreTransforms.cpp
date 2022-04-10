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
	v_0.x = e.x;
	v_0.y = e.y;
	len = 0.0f;
	angle.x = angle.y = 0.0f;
}

void VelocVect::UpdateLoc(const D2D1_POINT_2F& v_0) {
		this->v_0.x += v_0.x;
		this->v_0.y += v_0.y;
	
	
	
}

void VelocVect::Length(const D2D1_POINT_2F& v_0, float lim)
 {
 float Diffx = this->v_0.x + v_0.x;
 float Diffy =  this->v_0.y + v_0.y;
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
void VelocVect::Angle(const D2D1_POINT_2F& v_0) {
	angle.x += (this->v_0.y - v_0.y) * sin((this->v_0.x-v_0.x) * std::numbers::pi / 180.0);
	angle.y += (this->v_0.y - v_0.y)*cos((this->v_0.y-v_0.y) * std::numbers::pi / 180.0);
	OutputDebugStringA(MakeLPCSTR({ &angle.y }));
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
	return;
}