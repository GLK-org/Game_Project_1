#include "Engine.h"
#include "CoreMinimal.h"

Graphics::Graphics()
{
    currentwindow = NULL;
    factory = NULL;
    rendertarget = NULL;
    WICfactory = NULL;
}

Graphics::~Graphics()
{
    
    if (factory) { factory->Release(); }
    if (rendertarget) { rendertarget->Release(); }
    if (WICfactory) { WICfactory->Release(); }
    layers.clear();

}

bool Graphics::Init(HWND windowHandle)
{
    CoInitialize(NULL);
    //WskaŸnik ¿eby ju¿ nie robiæ nowych kopi handlle;
    currentwindow = &windowHandle;
    //definiowanie factory, przekazywany wskaŸnik do wskaŸnika factory
   HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&factory);
   if (res != S_OK) return false;


   res = CoCreateInstance(
       CLSID_WICImagingFactory,
       NULL,
       CLSCTX_INPROC_SERVER,
       IID_PPV_ARGS(&WICfactory)


   );

   RECT rect;
   GetClientRect(*currentwindow, &rect);
   //Spojrzeæ na to
  res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(*currentwindow,D2D1::SizeU(rect.right,rect.bottom)), &rendertarget);
  if (res != S_OK) return false;
  
  /*
  int layercount = 4;
  for (int i = 0; i < layercount;i++) {
      ID2D1Layer* temp;
      res = rendertarget->CreateLayer(&temp);
      layers.push_back(temp);
      temp = nullptr;
      delete temp;
  }
 int t= layers.size();*/
 //Ustawienie pierwszej warstwy - t³o, na aktywn¹
 //rendertarget->PushLayer(D2D1::LayerParameters(D2D1::RectF(100.0f,10.0f,120.0f,200.0f)), layers[0]);

  return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{

    rendertarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::CreateEllipseGeometry(D2D1_ELLIPSE * eli, ID2D1EllipseGeometry ** EllipseGeo) {
    HRESULT hr;

    hr = factory->CreateEllipseGeometry(eli, EllipseGeo);
    if (hr == S_OK) {

   }
}

void Graphics::DrawBG(D2D1_POINT_2F point, float tab[2])
{
    rendertarget->SetTransform(D2D1_MATRIX_3X2_F(D2D1::Matrix3x2F::Skew(tab[0],tab[1],point)));

}

void Graphics::DrawGeo(ID2D1EllipseGeometry* EllipseGeo) {
    ID2D1SolidColorBrush* brush;
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), &brush);
    rendertarget->DrawGeometry(EllipseGeo, brush, 5);
    brush->Release();
}

void Graphics::DrawEllipse(
    D2D1_ELLIPSE * eli,
    float r, float g, float b, float a
    )
    {
    //tworzenie pêdzla i generowanie elipsy
    ID2D1SolidColorBrush* brush;
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

    rendertarget->DrawEllipse(eli, brush, 3.0f);
    //
    brush->Release();
}

void Graphics::DrawRect(
    D2D1_RECT_F * rect,
    float r, float g, float b, float a
    )
    {
    ID2D1SolidColorBrush* brush; 
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

    rendertarget->DrawRectangle(rect, brush, 3.0f);
    //
    brush->Release();
}

void Graphics::FillRect(D2D1_RECT_F* rect, float e[])
{
    
    ID2D1SolidColorBrush* brush;
    if (e != nullptr) {
        rendertarget->CreateSolidColorBrush(D2D1::ColorF(e[0]/1000.0f, e[1]*2 / 1000.0f, e[2], e[3]), &brush);
       
    }
    else {
        rendertarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.2f, 0.f, 1.0f), &brush);
    }
    
    rendertarget->FillRectangle(rect,brush);
}

void Graphics::DrawLine(D2D1_POINT_2F& p1, D2D1_POINT_2F& p2, float r, float g, float b, float a)
{
    ID2D1SolidColorBrush* brush;
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

    rendertarget->DrawLine(p1, p2, brush);
    //

}

void Graphics::DrawLine(D2D1_POINT_2F& p1, D2D1_POINT_2F& p2, float length, float r, float g, float b, float a)
{
    ID2D1SolidColorBrush* brush;
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);
    D2D1_POINT_2F finale;
    finale.x = (p2.x+p1.x);
    finale.y = (p2.y+ p1.y) ;
    rendertarget->DrawLine(p1, finale, brush);
    //

}

void Graphics::DrawLine(D2D1_POINT_2F& p1, D2D1_POINT_2F& p2, float length, D2D1_POINT_2F& angle, float r, float g, float b, float a)
{
    ID2D1SolidColorBrush* brush;
    rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);
    D2D1_POINT_2F finale;
    finale.x = p1.x+length*angle.x;
    finale.y = p1.y+length*angle.y;
    rendertarget->DrawLine(p1, finale, brush);
    //

}

HRESULT Graphics::LoadBMP(
    ID2D1RenderTarget* pRenderTarget,
    IWICImagingFactory* pIWICFactory,
    PCWSTR uri,
    UINT destinationWidth,
    UINT destinationHeight,
    ID2D1Bitmap** ppBitmap
)
{
    if (pRenderTarget == nullptr) {
        pRenderTarget = rendertarget;
    }
    if (pIWICFactory == nullptr) {
        pIWICFactory = WICfactory;
    }
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    //Stream narazie nieu¿ywany
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;
    IWICBitmapScaler* pScaler = NULL;


    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );

    if (SUCCEEDED(hr))
    {
        // Create the initial frame.
        hr = pDecoder->GetFrame(0, &pSource);
    }

    if (SUCCEEDED(hr))
    {

        // Convert the image format to 32bppPBGRA
        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
        hr = pIWICFactory->CreateFormatConverter(&pConverter);

    }


    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pSource,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.f,
            WICBitmapPaletteTypeMedianCut
        );

        if (SUCCEEDED(hr))
        {

            // Create a Direct2D bitmap from the WIC bitmap.
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );
        }

        pDecoder->Release();
        pSource->Release();
        pStream->Release();
        pConverter->Release();
        pScaler->Release();

        return hr;
    }
}