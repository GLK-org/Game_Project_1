#pragma once
#include "CoreMinimal.h"

class ENGINE_API GameLevel {

public:

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render(Graphics* gfx) {};
	virtual void Update() = 0;
};