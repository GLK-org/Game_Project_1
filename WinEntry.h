#include "Engine.h"
#include "IApplication.h"
extern IApplication* EntryApplication();

INT CALLBACK  WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {

	
	auto EntryApp = EntryApplication();

	EntryApp->Initialize();

	return 0;
}