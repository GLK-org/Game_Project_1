#include "Obj.h"

Obj::Obj(float x, float y) {
	center.x = x;
	center.y = y;
	frametime = actionframetime = 0.0f;
	debugmode = false;
	ttl = 0.0f;
	istriggered = false;
	if (x == NULL || y == NULL) Obj::~Obj();
	phsx = nullptr;
	bmp = nullptr;
	actionbmp = nullptr;
	direction = RIGHT;
	frame = actionframe = 0;

};

float Obj::GetX() const { return center.x; };
float Obj::GetY() const { return center.y; };
D2D1_POINT_2F Obj::GetCenter() const { return center; };
Direction Obj::GetDirctn() { return direction; };
void Obj::SetDirctn(Direction dir) { direction = dir; };
bool Obj::GetTrig() const { return istriggered; };
void Obj::SetX(float x) { center.x = x; };
void Obj::SetY(float y) { center.y = y; };
void Obj::SetTrig(bool t) { istriggered = t; };
void Obj::ToggleDebug() { debugmode = !debugmode; };
Obj::~Obj() {
	if (phsx != nullptr) {
		delete phsx;
	}
	if (bmp != nullptr) {
		bmp->Release();
	}
	if (actionbmp != nullptr) {
		actionbmp->Release();
	}

}