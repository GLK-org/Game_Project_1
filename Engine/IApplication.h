#pragma once

//How the application should run - a template, export as dll

class ENGINE_API IApplication {


public:

	IApplication();

	virtual ~IApplication() = 0;

public:
	virtual void Initialize() = 0;

	virtual void Update() = 0;


};

IApplication* EntryApplication();