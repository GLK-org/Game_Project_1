#pragma once

#include "IApplication.h"
//makro creating an entry point
#define ENTRYAPP(x) IApplication* EntryApplication() { return new x;}

class Application : public IApplication {


public:

	Application();

	~Application();

	void Initialize();

	void Update();


};