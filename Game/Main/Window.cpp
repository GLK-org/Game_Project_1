#include "..\Game\pch\pch.h"
#include "Level_control\GameController.h"
#include "Level_1.h"
#include "Level_2.h"

WCHAR		WindowClass[MAX_NAME_STRING];
WCHAR		WindowTitle[MAX_NAME_STRING];

INT			WindowHeight;
INT			WindowWidth;

Graphics* graphics;
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
	
	//Inicjalizacja parametr�w startowych

	wcscpy_s(WindowClass, TEXT("TutorialOneClass"));
	wcscpy_s(WindowTitle, TEXT("TutorialOneTitle"));

	WindowWidth = 1366;
	WindowHeight = 768;
	//Tworzenie i definiowanie w�a�ciwo�ci klasy okna

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

	//Wy�wietlanie okna
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
	GameController::Init(graphics);
	//Wy�wietlanie okna i �adowanie wst�pnego poziomu
	ShowWindow(hWnd, SW_SHOW);
	GameController::LoadInitialLevel(new Level1());

	//Nas�uchuj zdarzenie wy��czenia tak, �eby okno si� nie wy��cza�o do tego momentu

	//Definiowanie pustej zmiennej msg (Tak, ten format zdaje si� konieczny, do research'u)
	MSG msg = { 0 };

	//Nas�uchiwanie 
	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			
			GameController::Update();
			if (GetKeyState('2')) {
				GameController::SwitchLevel(new Level2());
			}
			else if (GetKeyState('1')) {
				GameController::SwitchLevel(new Level1());
			}
			//Render:
			graphics->BeginDraw();
			GameController::Render(graphics);
			graphics->EndDraw();
			
		}
	}

	delete graphics;
	return 0;
}
