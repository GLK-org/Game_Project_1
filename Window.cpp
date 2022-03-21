#include "pch/pch.h"
#include "Core/CoreMinimal.h"
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
	
	//Inicjalizacja parametrów startowych

	wcscpy_s(WindowClass, TEXT("TutorialOneClass"));
	wcscpy_s(WindowTitle, TEXT("TutorialOneTitle"));

	WindowWidth = 1366;
	WindowHeight = 768;
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

	graphics = new Graphics();

	if (!graphics->Init(hWnd)) {
		delete graphics;
		return -1;
	}
	
	ShowWindow(hWnd, SW_SHOW);
	
	//Nas³uchuj zdarzenie wy³¹czenia tak, ¿eby okno siê nie wy³¹cza³o do tego momentu

	float y = 0.0f;
	float x = 0.0f;
	float ySpeed = 0.0f;
	float xSpeed = 0.0f;
	MSG msg = { 0 };

	//Odœwie¿anie ekranu i pseudofizyka
	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			
			//'Update':
			ySpeed += 1.0f;
			y += ySpeed;
			x += xSpeed;
			if (GetKeyState('A')) {
				xSpeed += 1.0f;
			}
			if (GetKeyState('D')) {
				xSpeed -= 1.0f;
			}

			if (y > WindowHeight) {
				y = WindowHeight;
				ySpeed = -30.0f;
			}
			if (x < 0) {
				x = 0;
				xSpeed = 5.0f;
			}
			else if (x > WindowWidth) {
				x = WindowWidth;
				xSpeed = -5.0f;
			}
			//Render:
			graphics->BeginDraw();
			graphics->ClearScreen(0.0f,0.0f,0.5f);
			graphics->DrawCircle(x, y, 50, 1.0f, 0.0f, 0.0f, 1.0f);
			graphics->EndDraw();
		}
	}
	delete graphics;
	return 0;
}
