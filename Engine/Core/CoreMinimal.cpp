
#include "Engine.h"
#include "CoreMinimal.h"
#include <chrono>
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
    HRESULT res;
    res= CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(res)) return false;
    //WskaŸnik ¿eby ju¿ nie robiæ nowych kopi handlle;
    currentwindow = &windowHandle;
    //definiowanie factory, przekazywany wskaŸnik do wskaŸnika factory
   res =D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&factory);
   if (FAILED(res)) return false;


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


  return true;
}

void Graphics::ClearScreen(float r, float g, float b, float a)
{

    rendertarget->Clear(D2D1::ColorF(r, g, b,a));

}


//Drawing Layers

void Graphics::DrawBg(float width, float height)
{
    rendertarget->PushLayer(D2D1::LayerParameters(D2D1::RectF(0, 0, width, height)), layers[0]);

}

void Graphics::StopDrawBg()
{
    rendertarget->PopLayer();
}

void Graphics::DrawChar(float width, float height)
{
    rendertarget->PushLayer(D2D1::LayerParameters(D2D1::RectF(0, 0, width, height)), layers[1]);

}

void Graphics::EndDrawChar()
{
    rendertarget->PopLayer();
}

void Graphics::DrawUI(float width, float height)
{
    rendertarget->PushLayer(D2D1::LayerParameters(D2D1::RectF(0, 0, width, height)), layers[2]);

}

void Graphics::StopDrawUI()
{
    rendertarget->PopLayer();
}

void Graphics::DrawElse(float width, float height)
{
    rendertarget->PushLayer(D2D1::LayerParameters(D2D1::RectF(0, 0, width, height)), layers[3]);

}

void Graphics::StopDrawElse()
{
    rendertarget->PopLayer();
}


//Transforms

void Graphics::Mirror(const D2D1_POINT_2F &p)
{
   // D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(180.0f, p);
  //  D2D1::Matrix3x2F test = D2D1::Matrix3x2F::Skew(0.0f,90.0f,p);
   D2D1::Matrix3x2F mirror = D2D1::Matrix3x2F::Scale(D2D1::Size(-1.0f, 1.0f), p);
//    D2D1::Matrix3x2F test3 = D2D1::Matrix3x2F::Skew(45.0f, 40.0f, p);
    rendertarget->SetTransform(mirror);
}

void Graphics::Scale(const D2D1_SIZE_F size, const D2D1_POINT_2F& p)
{
    D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(size, p);
    rendertarget->SetTransform(scale);
}

void Graphics::Rotate(float dg, const D2D1_POINT_2F& p)
{
    D2D1::Matrix3x2F rotate = D2D1::Matrix3x2F::Rotation(dg, p);
    rendertarget->SetTransform(rotate);
}

void Graphics::ClearTransforms()
{

    rendertarget->SetTransform(D2D1::Matrix3x2F::Identity());
}


//Create and draw basic shapes

void Graphics::CreateEllipseGeometry(D2D1_ELLIPSE* eli, ID2D1EllipseGeometry** EllipseGeo) {
    HRESULT hr;

    hr = factory->CreateEllipseGeometry(eli, EllipseGeo);
    if (hr == S_OK) {

    }
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
    ID2D1SolidColorBrush* brush=nullptr;
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

void Graphics::FillRect(D2D1_RECT_F* rect, float r, float g, float b, float a)
{

    ID2D1SolidColorBrush* brush;
        rendertarget->CreateSolidColorBrush(D2D1::ColorF(r,g, b, a), &brush);


    rendertarget->FillRectangle(rect, brush);
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


//BMPstuff

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
    };

    if (pIWICFactory == nullptr) {
        pIWICFactory = WICfactory;
    };

    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    //Stream narazie nieu¿ywany
    //IWICStream* pStream = NULL;
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
    };

    if (SUCCEEDED(hr))
    {
        hr = pIWICFactory->CreateBitmapScaler(&pScaler);
    }



    if (SUCCEEDED(hr))
    {

        // Convert the image format to 32bppPBGRA
        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
        hr = pIWICFactory->CreateFormatConverter(&pConverter);

    }

   /* if (SUCCEEDED(hr))
    {
        //Not working very well for now
        hr = pScaler->Initialize(
            pSource,                    // Bitmap source to scale.
            destinationWidth,                         // Scale width to half of original.
            destinationHeight,                        // Scale height to half of original.
            WICBitmapInterpolationModeFant);   // Use Fant mode interpolation.
    }*/

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pSource,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.0f,
            WICBitmapPaletteTypeMedianCut
        );
    }

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
        //pStream->Release();
        pConverter->Release();
        pScaler->Release();

        return hr;


};

void Graphics::Drawbmp(ID2D1Bitmap* bitmap,
    const D2D1_RECT_F& destinationRectangle,
    FLOAT                          opacity,
    D2D1_BITMAP_INTERPOLATION_MODE interpolationMode,
    const D2D1_RECT_F& sourceRectangle,
    int& frame,
    float& frametime,
    Speed& spd,
    bool anim,
    int starting_frame
) {
    int i1 = 0;
    int j1 = 0;


    if (anim) {
        Cooldown(frametime, frame, spd, starting_frame);
    }
        frame%= 4;
        
        switch (frame) {
        case 0:
            i1 = 0;
            j1 = 0;
            break;
        case 1:
            i1 = 1;
            j1 = 0;
            break;
        case 2:
            i1 = 0;
            j1 = 1;
            break;
        case 3:
            i1 = 1;
            j1 = 1;
            break;
        default:
            break;
        };

      

        D2D1_RECT_F tet = D2D1::RectF(
            sourceRectangle.left + sourceRectangle.right * i1,
            sourceRectangle.top + sourceRectangle.bottom * j1,
            sourceRectangle.right + sourceRectangle.right * i1,
            sourceRectangle.bottom + sourceRectangle.bottom * j1);
        rendertarget->DrawBitmap(bitmap, destinationRectangle, opacity, interpolationMode, tet);

};


//Cooldowns
bool Graphics::Cooldown(float &_frametime, int& _frame, Speed spd,int starting_frame) {
    float mod = 2.0f;
    switch (spd) {

       case F_SLOWEST:
           if (_frametime >= 3.4f+ starting_frame/3.4f*mod) {
               _frame++;
               _frametime = 0;
               return true;
           }
           break;
       case F_SLOW:
           if (_frametime >= 2.8f+ starting_frame/2.8f * mod) {
               _frame++;
               _frametime = 0;
               return true;
           }
           break;
       case F_MEDIUM:
           if (_frametime >= 2.2f+ starting_frame/2.2f * mod) {
               _frame++;
               _frametime = 0;
               return true;
           }
           break;
       case F_FAST:
           if (_frametime >= 1.6f+ starting_frame/1.6f * mod) {
               _frame++;
               _frametime = 0;
               return true;
           }
           break;

       case F_IMMEDIATE:
           if (_frametime >= 0.8f+ starting_frame/0.8f * mod) {
               _frame++;
               _frametime = 0;
               return true;
           }
           break;

       default:

           break;

    }

    return false;
};


HRESULT Graphics::LoadBmpFromRes(
    ID2D1RenderTarget* pRenderTarget,
    IWICImagingFactory* pIWICFactory,
    int resourceName,
    PCWSTR resourceType,
    UINT destinationWidth,
    UINT destinationHeight,
    ID2D1Bitmap** ppBitmap) {

            if (pRenderTarget == nullptr) {
                pRenderTarget = rendertarget;
            };

            if (pIWICFactory == nullptr) {
                pIWICFactory = WICfactory;
            };


    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;
  //  IWICBitmapScaler* pScaler = NULL;

    HRSRC imageResHandle = NULL;
    HGLOBAL imageResDataHandle = NULL;
    void* pImageFile = NULL;
    DWORD imageFileSize = 0;

    HMODULE e = GetModuleHandleW(L"Game.exe");

    // Locate the resource.
    imageResHandle = FindResourceW(e, MAKEINTRESOURCEW(resourceName), resourceType);

    HRESULT hr = imageResHandle ? S_OK : E_FAIL;

        if (SUCCEEDED(hr))
        {
        // Load the resource.
        imageResDataHandle = LoadResource(e, imageResHandle);

        hr = imageResDataHandle ? S_OK : E_FAIL;
        }
        if (SUCCEEDED(hr))
        {
            // Lock it to get a system memory pointer.
            pImageFile = LockResource(imageResDataHandle);

            hr = pImageFile ? S_OK : E_FAIL;
        }
        if (SUCCEEDED(hr))
        {
            // Calculate the size.
            imageFileSize = SizeofResource(e, imageResHandle);

            hr = imageFileSize ? S_OK : E_FAIL;

        }
    
        if (SUCCEEDED(hr))
        {
            // Create a WIC stream to map onto the memory.
            hr = pIWICFactory->CreateStream(&pStream);
        }
        if (SUCCEEDED(hr))
        {
            // Initialize the stream with the memory pointer and size.
            hr = pStream->InitializeFromMemory(
                reinterpret_cast<BYTE*>(pImageFile),
                imageFileSize
            );
        }

        if (SUCCEEDED(hr))
        {
            // Create a decoder for the stream.
            hr = pIWICFactory->CreateDecoderFromStream(
                pStream,
                NULL,
                WICDecodeMetadataCacheOnLoad,
                &pDecoder
            );
        }

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
                //create a Direct2D bitmap from the WIC bitmap.
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
       //     pScaler->Release();

            return hr;
        }
}
