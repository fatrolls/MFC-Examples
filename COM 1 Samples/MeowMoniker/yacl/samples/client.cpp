#define _WIN32_WINNT 0x402
#include <windows.h>

#include "hello.h"
#include "hello_i.c"

#include "combook.h"
#include "combook.cpp"

void main(void)
{
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

    if (SUCCEEDED(hr))
    {
        {
            SI(IUnknown) siUnk;
            hr = siUnk.Instantiate(CLSID_Goodbye);
            if (SUCCEEDED(hr))
            {
                SI(IHello) siHello = siUnk;
                siHello->HelloWorld();
            }
            SI(IPersistStorage) sips;
            hr = sips.BindToObject(_U("D:\\dbox\\courseware\\ecom\\02_cxx.ppt"));

            

            SI(IClassFactory) sicf;
            hr = sicf.GetClassObject(OLESTR("Excel.Sheet"));

            SI(IUnknown) p1;
            
            hr = sicf->CreateInstance(0, IID_PPV(p1));
            hr = OleRun(p1.GetNonAddRefedInterface());
            

        }
        CoUninitialize();
    }
}