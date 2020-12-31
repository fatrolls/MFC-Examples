#define _WIN32_WINNT 0x402
#include <windows.h>

#include "hello.h"
#include "hello_i.c"

#include "combook.h"
#include "combook.cpp"

class SoLong : IHello
{
public:

// implement UpdateRegistry(HINSTANCE hInstance, BOOL bInstalling)
    static HRESULT STDAPICALLTYPE UpdateRegistry(HINSTANCE hInstance, BOOL bInstalling)
    {
        BEGIN_REGISTRY_TABLE(entries)
            REGISTRY_KEY(HKEY_CLASSES_ROOT, "HelloLib.Hello.1", 0, "Hello Class", REGFLAG_DELETE_BEFORE_REGISTERING)\
                REGISTRY_SUBKEY("CLSID", 0, "{DABA24E7-A38F-11d0-8C2F-0080C73925BA}", REGFLAG_NORMAL)\
            REGISTRY_KEY(HKEY_CLASSES_ROOT, "HelloLib.Hello", 0, "Hello Class", REGFLAG_NORMAL)\
                REGISTRY_SUBKEY("CurVer", 0, "HelloLib.Hello.1", REGFLAG_NORMAL)\
            REGISTRY_KEY(HKEY_CLASSES_ROOT, "CLSID\\" "{DABA24E7-A38F-11d0-8C2F-0080C73925BA}", 0, "Hello Class", REGFLAG_DELETE_BEFORE_REGISTERING)\
                REGISTRY_SUBKEY(REG_SERVER_TYPE, 0, REG_MODULE_NAME, REGFLAG_NORMAL)\
                REGISTRY_SUBKEY(REG_SERVER_TYPE, "ThreadingModel", "both", REGFLAG_NORMAL)\
                REGISTRY_SUBKEY("ProgID", 0, "HelloLib.Hello.1", REGFLAG_NORMAL)\
                REGISTRY_SUBKEY("VersionIndependentProgID", 0, "HelloLib.Hello", REGFLAG_NORMAL)\
        END_REGISTRY_TABLE()
        return RegistryTableUpdateRegistry(hInstance, entries, FALSE, bInstalling);
    }

// implement QueryInterface/AddRef/Release
    LONG m_cRef;
    SoLong(void) : m_cRef(0) {}
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if (riid == IID_IUnknown)
            *ppv = static_cast<IUnknown*>(this);
        else if (riid == IID_IHello)
            *ppv = static_cast<IHello*>(this);
        else 
            return (*ppv = 0), E_NOINTERFACE;
        ((IUnknown*)*ppv)->AddRef();
        return S_OK;
    }

    STDMETHODIMP_(ULONG) AddRef(void)
    {
        extern void STDAPICALLTYPE ModuleAddRef();
        if (m_cRef == 0)
            ModuleAddRef();
        return InterlockedIncrement(&m_cRef);
    }

    STDMETHODIMP_(ULONG) Release(void)
    {
        extern void STDAPICALLTYPE ModuleRelease();
        LONG res = InterlockedDecrement(&m_cRef);
        if (res == 0)
        {
            delete this;
            ModuleRelease();
        }
        return res;
    }

// implement static CreateInstance(IUnknown *, REFIID, void**)
    static HRESULT STDAPICALLTYPE CreateInstance(IUnknown *pUnkOuter, 
                                                 REFIID riid, void**ppv)
    {
        *ppv = 0;
        if (pUnkOuter)
            return CLASS_E_NOAGGREGATION;
        SoLong *p = new SoLong;
        if (!p)
            return E_OUTOFMEMORY;
        p->AddRef();
        HRESULT hr = p->QueryInterface(riid, ppv);
        p->Release();
        return hr;
    }

// implement static GetClassObject(REFIID, void **) that uses a GenericClassFactory
    static HRESULT STDAPICALLTYPE GetClassObject(REFIID riid, void **ppv)
    {
        static GenericClassFactory cf(CreateInstance);
        return cf.QueryInterface(riid, ppv);
    }



    STDMETHODIMP HelloWorld(void) {
        MessageBox(0, "Hello, World", "", MB_SETFOREGROUND);
        return NOERROR;
    }

};

class Hello : IHello
{
public:    
// implement UpdateRegistry(HINSTANCE hInstance, BOOL bInstalling)
    BEGIN_CLASS_REGISTRY_TABLE(Hello)
        REGISTRY_KEY(HKEY_CLASSES_ROOT, "HelloLib.Hello.1", 0, "Hello Class", REGFLAG_DELETE_BEFORE_REGISTERING)
            REGISTRY_SUBKEY("CLSID", 0, "{DABA24E7-A38F-11d0-8C2F-0080C73925BA}", REGFLAG_NORMAL)
        REGISTRY_KEY(HKEY_CLASSES_ROOT, "HelloLib.Hello", 0, "Hello Class", REGFLAG_NORMAL)
            REGISTRY_SUBKEY("CurVer", 0, "HelloLib.Hello.1", REGFLAG_NORMAL)
        REGISTRY_KEY(HKEY_CLASSES_ROOT, "CLSID\\" "{DABA24E7-A38F-11d0-8C2F-0080C73925BA}", 0, "Hello Class", REGFLAG_DELETE_BEFORE_REGISTERING)
            REGISTRY_SUBKEY(REG_SERVER_TYPE, 0, REG_MODULE_NAME, REGFLAG_NORMAL)
#ifdef DLLSVC
            REGISTRY_SUBKEY(REG_SERVER_TYPE, "ThreadingModel", "both", REGFLAG_NORMAL)
#endif
            REGISTRY_SUBKEY("ProgID", 0, "HelloLib.Hello.1", REGFLAG_NORMAL)
            REGISTRY_SUBKEY("VersionIndependentProgID", 0, "HelloLib.Hello", REGFLAG_NORMAL)
    END_CLASS_REGISTRY_TABLE()

// implement GetInterfaceTable
    BEGIN_INTERFACE_TABLE(Hello)
        IMPLEMENTS_INTERFACE(IHello)
    END_INTERFACE_TABLE()

// implement QueryInterface/AddRef/Release
    IMPLEMENT_UNKNOWN(Hello)

// implement static CreateInstance(IUnknown *, REFIID, void**)
    IMPLEMENT_CREATE_INSTANCE(Hello)

// implement static GetClassObject(REFIID, void **) that uses a GenericClassFactory
    IMPLEMENT_GENERIC_CLASS_FACTORY(Hello)



    STDMETHODIMP HelloWorld(void) {
        MessageBox(0, "Hello, World", "", MB_SETFOREGROUND);
        return NOERROR;
    }
};

class Goodbye : IHello
{
public:
// use shorthand version of class above
    IMPLEMENT_COCLASS(Goodbye, "{DABA24E9-A38F-11d0-8C2F-0080C73925BA}", "Goodbye Class", "HelloLib.Goodbye.1", "HelloLib.Goodbye", "both")
        IMPLEMENTS_INTERFACE(IHello)
    END_INTERFACE_TABLE()

    STDMETHODIMP HelloWorld(void) {
        MessageBox(0, "Hello, World", "", MB_SETFOREGROUND);
        return NOERROR;
    }
};

// map CLSID to GetClassObject/UpdateRegistry routine
BEGIN_COCLASS_TABLE(ClassTable)
    IMPLEMENTS_COCLASS(Hello)
    IMPLEMENTS_COCLASS(Goodbye)
    IMPLEMENTS_COCLASS(SoLong)
END_COCLASS_TABLE()

#ifdef DLLSVC

// implement ModuleAddRef/ModuleRelease/ModuleIsStopping/ModuleIsIdle
IMPLEMENT_DLL_MODULE_ROUTINES()

// implement DllGetClassObject/DllCanUnloadNow/Dll[Un]RegisterServer
IMPLEMENT_DLL_ENTRY_POINTS(ClassTable, 0, TRUE)

#else

// implement ModuleAddRef/ModuleRelease/ModuleIsStopping/ModuleServerListen
IMPLEMENT_MTAEXE_MODULE_ROUTINES()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR szCmdParam, int)
{
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

    if (SUCCEEDED(hr))
    {
// install, uninstall, or run server
        IMPLEMENT_EXE_ENTRY_POINTS(szCmdParam, ClassTable, 0, TRUE, CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)

        CoUninitialize();
    }
    return hr;
}

#endif
