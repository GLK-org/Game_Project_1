#include "Engine.h"
#include "CoreWriter.h"

 WCHAR const Writer::msc_fontName[] = L"Verdana";
 FLOAT const Writer::msc_fontSize = 35;

HRESULT Writer::Initialize(ID2D1Factory* factory, ID2D1RenderTarget& target) {

    m_pD2DFactory = factory;
     // Create a Direct2D factory.
    reftarget = &target;
     if (SUCCEEDED(hr))
     {
         // Create a DirectWrite factory.
         hr = DWriteCreateFactory(
             DWRITE_FACTORY_TYPE_SHARED,
             __uuidof(m_pDWriteFactory),
             reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
         );
     };

     if (SUCCEEDED(hr))
     {
         // Create a DirectWrite text format object.
         hr = m_pDWriteFactory->CreateTextFormat(
             msc_fontName,
             NULL,
             DWRITE_FONT_WEIGHT_NORMAL,
             DWRITE_FONT_STYLE_NORMAL,
             DWRITE_FONT_STRETCH_NORMAL,
             msc_fontSize,
             L"", //locale
             &m_pTextFormat

         );

     };

     if (SUCCEEDED(hr))
     {
         // Center the text horizontally and vertically.
         m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

         m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

     };
     return hr;
 }

void Writer::Draw_Text(std::string text, D2D1_RECT_F rect)
{
    std::wstring wstext = std::wstring(text.begin(), text.end());
    const wchar_t* wtext = wstext.c_str();
    HRESULT hr;
    ID2D1SolidColorBrush* brush;
    hr=reftarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), &brush);
    if (hr == S_OK) {
        reftarget->DrawText(
            wtext,
            text.size(),
            m_pTextFormat,
            rect,
            brush
        );
   }
  

}

;