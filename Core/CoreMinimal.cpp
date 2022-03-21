//cpp z minimalnymi opcjami

#include "CoreMinimal.h"
#include "Engine.h"

Graphics::Graphics()
{
    factory = NULL;
    rendertarget = NULL;

}

Graphics::~Graphics()
{
    if (factory) { factory->Release(); }
    if (rendertarget) { rendertarget->Release(); }
}

bool Graphics::Init(HWND windowHandle)
{
    //definiowanie factory, przekazywany wska�nik do wska�nika factory
   HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&factory);
   if (res != S_OK) return false;
    
   RECT rect;
   GetClientRect(windowHandle, &rect);
   //Spojrze� na to
  res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(windowHandle,D2D1::SizeU(rect.right,rect.bottom)), &rendertarget);
  if (res != S_OK) return false;
  
  return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
    rendertarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float rad, float r, float g, float b, float a)
{
    //tworzenie p�dzla i generowanie elipsy
    ID2D1SolidColorBrush* brush;
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

    rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), rad, rad), brush, 3.0f);
    //
    brush->Release();
}