#include "Engine.h"
#include "CoreMinimal.h"


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
    //WskaŸnik ¿eby ju¿ nie robiæ nowych kopi handlle;
    currentwindow = &windowHandle;
    //definiowanie factory, przekazywany wskaŸnik do wskaŸnika factory
   HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&factory);
   if (res != S_OK) return false;
    
   RECT rect;
   GetClientRect(*currentwindow, &rect);
   //Spojrzeæ na to
  res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(*currentwindow,D2D1::SizeU(rect.right,rect.bottom)), &rendertarget);
  if (res != S_OK) return false;
  int layercount = 4;
  for (int i = 0; i < layercount;i++) {
      ID2D1Layer* temp;
      res = rendertarget->CreateLayer(&temp);
      layers.push_back(temp);
      temp = nullptr;
      delete temp;
  }
 int t= layers.size();
 //Ustawienie pierwszej warstwy - t³o, na aktywn¹
 rendertarget->PushLayer(D2D1::LayerParameters(D2D1::RectF(200.0f,10.0f,120.0f,200.0f)), layers[0]);

  return true;
}



void Graphics::ClearScreen(float r, float g, float b)
{

    rendertarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::CreateEllipseGeometry(D2D1_ELLIPSE &eli, ID2D1EllipseGeometry ** EllipseGeo) {
    HRESULT hr;

    hr = factory->CreateEllipseGeometry(eli, EllipseGeo);
    if (hr == S_OK) {

   }
}

void Graphics::DrawBG()
{

}

void Graphics::DrawGeo(ID2D1EllipseGeometry* EllipseGeo) {
    ID2D1SolidColorBrush* brush;
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), &brush);
    rendertarget->DrawGeometry(EllipseGeo, brush, 5);
    brush->Release();
}

void Graphics::DrawCircle(float x, float y, float rad, float r, float g, float b, float a)
{
    //tworzenie pêdzla i generowanie elipsy
    ID2D1SolidColorBrush* brush;
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

    rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), rad, rad), brush, 3.0f);
    //
    brush->Release();
}
