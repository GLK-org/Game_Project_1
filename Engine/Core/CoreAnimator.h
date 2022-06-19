#pragma once
#include <list>
#include <CoreMinimal.h>


template<typename T>
class ENGINE_API Animator {

	float refresh_rate=33.3f;
	std::list<T> renderlist;


	void Add();
	void Remove();
	void BeginDraw(Graphics * gfx);


};