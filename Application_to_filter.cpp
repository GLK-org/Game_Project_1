
#include "pch/pch.h"
#include "Application.h"
#include "WinEntry.h"

ENTRYAPP(Application)

Application::Application()
{

}

Application::~Application()
{
}

void Application::Initialize()
{
	MessageBox(0, L"Zaladowano",0,0);
}

void Application::Update()
{
	MessageBox(0, L"Loop", 0, 0);
}