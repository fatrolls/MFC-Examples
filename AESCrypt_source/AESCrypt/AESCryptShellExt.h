/*
 *  AESCryptShellExt.h
 *
 *  Copyright (C) 2006, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This defines the C++ class for integrating with the Windows shell.
 *
 */

#pragma once
#include "resource.h"       // main symbols

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

//
// AESCryptShellExt Declaration
//
class ATL_NO_VTABLE AESCryptShellExt :
        public CComObjectRootEx<CComSingleThreadModel>,
        public CComCoClass<AESCryptShellExt, &CLSID_AESCryptShellExtCom>,
        public IShellExtInit,
        public IContextMenu
{
    private:
        void MakeMenuBitmapTransparent(COLORREF color);

    protected:
        HBITMAP     Context_Bitmap;
        StringList  *File_List;
        bool        AES_Files;
        bool        Non_AES_Files;

    public:
        AESCryptShellExt();
        ~AESCryptShellExt();

        // IShellExtInit
        STDMETHOD(Initialize)(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

        // IContextMenu
#ifdef _M_X64
		STDMETHOD(GetCommandString)(UINT_PTR, UINT, UINT*, LPSTR, UINT);
#else
		STDMETHOD(GetCommandString)(UINT, UINT, UINT*, LPSTR, UINT);
#endif
        STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO);
        STDMETHOD(QueryContextMenu)(HMENU, UINT, UINT, UINT, UINT);

        DECLARE_REGISTRY_RESOURCEID(IDR_AESCRYPTSHELLEXT)
        DECLARE_NOT_AGGREGATABLE(AESCryptShellExt)

        BEGIN_COM_MAP(AESCryptShellExt)
            COM_INTERFACE_ENTRY(IShellExtInit)
            //COM_INTERFACE_ENTRY(IContextMenu) // This does not work.  What's the trick?
            COM_INTERFACE_ENTRY_IID(IID_IContextMenu, IContextMenu)
        END_COM_MAP()

        DECLARE_PROTECT_FINAL_CONSTRUCT()

        HRESULT FinalConstruct()
        {
            return S_OK;
        }

        void FinalRelease()
        {
        }
};

OBJECT_ENTRY_AUTO(__uuidof(AESCryptShellExtCom), AESCryptShellExt)
