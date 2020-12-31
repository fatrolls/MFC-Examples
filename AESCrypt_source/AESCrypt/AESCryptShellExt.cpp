/*
 *  AESCryptShellExt.cpp
 *
 *  Copyright (C) 2006, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This module implements the code necessary to integrate with the
 *  Windows shell (Explorer).
 *
 */


#include "stdafx.h"
#include "AESCrypt.h"
#include "AESCryptShellExt.h"
#include "AESCryptWorkerThreads.h"

/*
 * Make the global thread class visible in this module.
 */
extern AESCryptWorkerThreads AES_Crypt_Worker_Threads;

/*
 * AESCryptShellExt Constructor
 *
 * The class constructor will load bitmaps and perform other initialization
 * operations.
 */
AESCryptShellExt::AESCryptShellExt()
{
    Context_Bitmap =
        (HBITMAP) LoadImage(_pModule->GetModuleInstance(),
                            MAKEINTRESOURCE(IDB_CTXBITMAP),
                            IMAGE_BITMAP,
                            0,
                            0,
                            LR_DEFAULTCOLOR);
    
    // Make the context menu transparent, assuming the specified
    // color is the transparent color
    MakeMenuBitmapTransparent(0x99b4d1);

    //Context_Bitmap = LoadBitmap(    _pModule->GetModuleInstance(),
    //                                MAKEINTRESOURCE(IDB_CTXBITMAP));
    File_List = NULL;
}

/*
 * ~AESCryptShellExt Destructor
 *
 * The class destructor will do cleanup of things allocated for the class.
 */
AESCryptShellExt::~AESCryptShellExt()
{
    // Free the bitmap object
    if (Context_Bitmap != NULL)
    {
        DeleteObject(Context_Bitmap);
    }

    // If there is a file list, delete it.
    if (File_List != NULL)
    {
        delete File_List;
    }
}

/*
 * MakeMenuBitmapTransparent
 *
 * This routine will attempt to make the context menu icon transparent.
 * The color to be made transparent is specified as the input parameter.
 */
void AESCryptShellExt::MakeMenuBitmapTransparent(COLORREF color)
{
    // Transform black into the context menu color
    if (Context_Bitmap != NULL)
    {
        BITMAP bm;
        int bm_size;
        BITMAPINFO bmInfo;
        HBITMAP transparent_bitmap;
        HDC hdc_input;
        HDC hdc_output;
        unsigned char *pixels;
        int i;
        DWORD menu_color;
        unsigned char red, green, blue;
        unsigned char menu_red, menu_green, menu_blue;

        // Extract the red, green, and blue components from the specified color
        red = (color >> 16) & 0xff;
        green = (color >> 8) & 0xff;
        blue = (color) & 0xff;

        // Create device contexts for the original and resulting bitmap
        hdc_input = CreateCompatibleDC(NULL);
        hdc_output = CreateCompatibleDC(NULL);

        // Select the bitmap into the input DC
        SelectObject(hdc_input, Context_Bitmap);

        // Get the bitmap information
        GetObject(Context_Bitmap, sizeof(bm), &bm);

        // Create a 24bpp DBI section we can manipulate
        memset(&bmInfo, 0, sizeof(BITMAPINFO));
        bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmInfo.bmiHeader.biWidth = bm.bmWidth;
        bmInfo.bmiHeader.biHeight = bm.bmHeight;
        bmInfo.bmiHeader.biPlanes = 1;
        bmInfo.bmiHeader.biBitCount = 24;
        transparent_bitmap = CreateDIBSection(  hdc_output,
                                                &bmInfo,
                                                DIB_RGB_COLORS,
                                                (void **) &pixels,
                                                NULL,
                                                0);
        if (transparent_bitmap != NULL)
        {
            // Select the transparent bitmap into the output DC
            SelectObject(hdc_output, transparent_bitmap);

            // Copy the input bitmap
            BitBlt( hdc_output, 0, 0,
                    bm.bmWidth, bm.bmHeight,
                    hdc_input, 0, 0,
                    SRCCOPY);

            // Get the menu color
            menu_color = GetSysColor(COLOR_MENU);
            menu_red = GetRValue(menu_color);
            menu_green = GetGValue(menu_color);
            menu_blue = GetBValue(menu_color);

            // Count the total number of octets in the bitmap
            bm_size = (bm.bmHeight * bm.bmWidth) * 3;

            // Look for the specified color and replace it
            for(i=0; i < bm_size; i += 3)
            {
                if ((pixels[i] == blue) &&
                    (pixels[i+1] == green) &&
                    (pixels[i+2] == red))
                {
                    pixels[i] = menu_blue;
                    pixels[i+1] = menu_green;
                    pixels[i+2] = menu_red;
                }
            }

            // Delete the old context menu bitmap object
            DeleteObject(Context_Bitmap);

            // Replace the context menu bitmap with the transparent one
            Context_Bitmap = transparent_bitmap;
        }

        // Delete the device contexts
        DeleteDC(hdc_input);
        DeleteDC(hdc_output);
    }
}

/*
 * Initialize
 *
 * This virtual function is called to initialize the shell extension.
 */
HRESULT AESCryptShellExt::Initialize(   LPCITEMIDLIST pidlFolder,
                                        LPDATAOBJECT pDO,
                                        HKEY hProgID)
{
    HDROP       hdrop;
    UINT        file_count;
    FORMATETC   etc = { CF_HDROP, NULL, DVASPECT_CONTENT,
                        -1, TYMED_HGLOBAL };
    STGMEDIUM   stg = { TYMED_HGLOBAL };
    TCHAR       filename[MAX_PATH], fileext[5];
    size_t      filename_length;
    bool        this_file_aes;

    // Read the list of folders
    if (FAILED(pDO->GetData(&etc,&stg)))
    {
        return E_INVALIDARG;
    }

    // Get an HDOP handle
    hdrop = (HDROP) GlobalLock(stg.hGlobal);
    if (hdrop == NULL)
    {
        ReleaseStgMedium(&stg);
        return E_INVALIDARG;
    }

    // Get a count of the number of files
    file_count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);

    // Try to allocate a list to store filenames
    // If we fail, don't crash, just don't show the context menu
    try
    {
        File_List = new StringList;
    }
    catch(...)
    {
        return E_INVALIDARG;
    }

    // Initialize the variables that indicate the type of files we have
    AES_Files = false;
    Non_AES_Files = false;

    for(UINT i = 0; i < file_count; i++)
    {
        if (!DragQueryFile(hdrop, i, filename, MAX_PATH))
        {
            continue;
        }

        // See if there is a .aes extension on the filename
        filename_length = _tcsnlen(filename, MAX_PATH);
        if (filename_length > MAX_PATH)
        {
            // This should never happen, but...
            continue;
        }

        this_file_aes = false;
        if (filename_length > 4)
        {
            _tcsncpy_s(fileext,5,filename+filename_length-4,4);
            if(!_tcsicmp(fileext,_T(".aes")))
            {
                this_file_aes = true;
            }
        }

        if (this_file_aes == true)
        {
            AES_Files = true;

            // We do not allow mixing of file types
            if (Non_AES_Files == true)
            {
                // Exiting now is faster.
                break;
            }
        }
        else
        {
            Non_AES_Files = true;

            // We do not allow mixing of file types
            if (AES_Files == true)
            {
                // Exiting now is faster.
                break;
            }
        }

        File_List->push_back(filename);
    }

    // Release resources
    GlobalUnlock(stg.hGlobal);
    ReleaseStgMedium(&stg);

    // If there are filenames in the list, then we will insert an
    // option in the context menu.  However, if there is a mix of
    // AES file and non-AES files, do not show the menu option.  We
    // should only show the option when the list is not mixed.
    if (File_List->empty() ||
        ((AES_Files == true) && (Non_AES_Files == true)))
    {
        return E_INVALIDARG;
    }
    else
    {
        return S_OK;
    }
}

/*
 * QueryContextMenu
 *
 * This function will display a context menu item in Explorer.
 */
HRESULT AESCryptShellExt::QueryContextMenu( HMENU hmenu,
                                            UINT uMenuIndex,
                                            UINT uidFirstCmd,
                                            UINT uidLastCmd,
                                            UINT uFlags)
{
    UINT uCmdID = uidFirstCmd;
    
    // If the flags include CMF_DEFAULTONLY then we shouldn't do anything.
    if (uFlags & CMF_DEFAULTONLY)
    {
        return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
    }

    // Insert our menu choices
    if (AES_Files == true)
    {
        InsertMenu( hmenu,
                    uMenuIndex,
                    MF_STRING | MF_BYPOSITION,
                    uCmdID++,
                     _T("AES Decrypt"));
    }
    else
    {
        InsertMenu( hmenu,
                    uMenuIndex,
                    MF_STRING | MF_BYPOSITION,
                    uCmdID++,
                     _T("AES Encrypt"));
    }

    // Insert the bitmap
    if (Context_Bitmap != NULL )
    {
        SetMenuItemBitmaps( hmenu,
                            uMenuIndex,
                            MF_BYPOSITION,
                            Context_Bitmap,
                            NULL);
    }

    // Tell the shell that we added one menu item
    return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 1);

}

/*
 * GetCommandString
 *
 * This function will provide help text
 */
#ifdef _M_X64
HRESULT AESCryptShellExt::GetCommandString( UINT_PTR uCmdID,
#else
HRESULT AESCryptShellExt::GetCommandString( UINT uCmdID,
#endif
                                            UINT uFlags,
                                            UINT* puReserved,
                                            LPSTR szName,
                                            UINT cchMax)
{
    USES_CONVERSION;
    LPCTSTR help_text;

    if (uFlags & GCS_HELPTEXT)
    {
        switch (uCmdID)
        {
            case 0:
                if (AES_Files == true)
                {
                    help_text = _T("Decrypt selected AES file(s)");
                }
                else
                {
                    help_text = _T("AES Encrypt selected file(s)");
                }
                break;

            default:
                ATLASSERT(0);           // should never get here
                return E_INVALIDARG;
                break;
            }

        // Copy the help text into the supplied buffer.  If the shell wants
        // a Unicode string, we need to case szName to an LPCWSTR.
        if (uFlags & GCS_UNICODE)
        {
            lstrcpynW((LPWSTR) szName, T2CW(help_text), cchMax);
        }
        else
        {
            lstrcpynA(szName, T2CA(help_text), cchMax);
        }
    }
    else if (uFlags & GCS_VERB)
        {
        // Copy the verb name into the supplied buffer.  If the shell wants
        // a Unicode string, we need to case szName to an LPCWSTR.
        switch ( uCmdID )
        {
            case 0:
                if (AES_Files == true)
                {
                    if (uFlags & GCS_UNICODE)
                    {
                        lstrcpynW((LPWSTR) szName, L"AES Decrypt", cchMax);
                    }
                    else
                    {
                        lstrcpynA(szName, "AES Decrypt", cchMax);
                    }
                }
                else
                {
                    if (uFlags & GCS_UNICODE)
                    {
                        lstrcpynW((LPWSTR) szName, L"AES Encrypt", cchMax);
                    }
                    else
                    {
                        lstrcpynA(szName, "AES Encrypt", cchMax);
                    }
                }
                break;

            default:
                ATLASSERT(0);           // should never get here
                return E_INVALIDARG;
                break;
        }
    }

    return S_OK;
}

/*
 * InvokeCommand
 *
 * This function will start the work of encrypting or decrypting when
 * the user selects this shell extension from the context menu.
 */
HRESULT AESCryptShellExt::InvokeCommand(LPCMINVOKECOMMANDINFO pInfo)
{
    // If lpVerb really points to a string, ignore this function call and bail out.  
    if (HIWORD(pInfo->lpVerb) != 0)
    {
        return E_INVALIDARG;
    }

    // Check that lpVerb is one of our commands (0 or 1)
    switch (LOWORD(pInfo->lpVerb))
    {
        case 0:
            AES_Crypt_Worker_Threads.ProcessFiles(  File_List,
                                                    (Non_AES_Files == TRUE));
            // We passed the pointer to AES_Crypt_Worker_Threads,
            // so set it to NULL here to avoid double deletion
            File_List = NULL;
            return S_OK;
            break;

        default:
            ATLASSERT(0);               // should never get here
            return E_INVALIDARG;
            break;
    }
}
