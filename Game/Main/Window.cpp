#include "..\Game\pch\pch.h"
#include "Level_control\GameController.h"
WCHAR		WindowClass[MAX_NAME_STRING];
WCHAR		WindowTitle[MAX_NAME_STRING];

INT			WindowHeight;
INT			WindowWidth;

Graphics* graphics;
Writer * writer;
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) {

	switch (message) {
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	/*case WM_PAINT: {
		graphics->BeginDraw();
		graphics->ClearScreen(0.0f, 0.0f, 0.5f);
		graphics->DrawCircle(104, 150, 50, 1.0f, 0.0f, 0.0f, 1.0f);
	
		
		graphics->EndDraw();
	}
	*/
	}



	return DefWindowProc(hWnd, message, wparam, lparam);
}




int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	
	//Inicjalizacja parametrów startowych

	wcscpy_s(WindowClass, TEXT("TutorialOneClass"));
	wcscpy_s(WindowTitle, TEXT("TutorialOneTitle"));

	WindowWidth = WNDWIDTH;
	WindowHeight = WNDHEIGHT;
	//Tworzenie i definiowanie w³aœciwoœci klasy okna

	WNDCLASSEX wcex;
	

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowClass;
	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = WindowProcess;

	//Rejestracja klasy?
	RegisterClassEx(&wcex);

	//Wyœwietlanie okna
	//Handler - "reprezentacja okna"
	RECT rect = {0,0, WindowWidth, WindowHeight};
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW,false,WS_EX_OVERLAPPEDWINDOW);

	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, rect.right-rect.left, rect.bottom-rect.top, nullptr, nullptr, HInstance(), nullptr);

	if (!hWnd) {
		MessageBox(0, L"Failed to Create Window", 0, 0);
		return 0;
	}
	//Inicjalizacja obiektu do rysowania, przekazanie mu handlera okna
	graphics = new Graphics();

	if (!graphics->Init(hWnd)) {
		delete graphics;
		return -1;
	}
	writer = new Writer();

	if (writer->Initialize(graphics->getFac(), graphics->getRTg()) != S_OK) {
		delete writer;
		return -1;
	}

	GameController::Init(graphics,writer);
	//Wyœwietlanie okna i ³adowanie wstêpnego poziomu
	
	ShowWindow(hWnd, SW_SHOW);
	Menu* m = new Menu();
	GameController::LoadInitialLevel(new Level1());
	
	//Nas³uchuj zdarzenie wy³¹czenia tak, ¿eby okno siê nie wy³¹cza³o do tego momentu

	//Definiowanie pustej zmiennej msg (Tak, ten format zdaje siê konieczny, do research'u)
	MSG msg = { 0 };
	//Nas³uchiwanie 
	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			
			
			if (GetKeyState('2') & KEY_PRESSED) {
				GameController::SwitchLevel(new Level2());
			}
			else if (GetKeyState('1') & KEY_PRESSED) {
				GameController::SwitchLevel(new Level1());
			}
			else if (GetKeyState('3') & KEY_PRESSED) {
				GameController::SwitchLevel(new Level3());
			}
			else if (GetKeyState(VK_ESCAPE) & KEY_PRESSED) {
				GameController::paused = !GameController::paused;
			}
			//Render:
			graphics->BeginDraw();
			GameController::Play(graphics);
			graphics->EndDraw();
			
		}
	}

	delete graphics;
	delete writer;
	return 0;
}
