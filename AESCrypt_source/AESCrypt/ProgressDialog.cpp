/*
 *  ProgressDialog.cpp
 *
 *  Copyright (C) 2006, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This module implements a simple progress box for showing the progress
 *  of file encryption and decryption.
 *
 */

#include "stdafx.h"
#include "ProgressDialog.h"

/*
 *  ProgressDialog Constructor
 */
ProgressDialog::ProgressDialog()
{
    abort_processing = false;
}

/*
 *  ProgressDialog Destructor
 */
ProgressDialog::~ProgressDialog()
{
}

/*
 *  OnInitDialog
 */
LRESULT ProgressDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    OSVERSIONINFO os_version_info;
    HICON hicon;

    CAxDialogImpl<ProgressDialog>::OnInitDialog(uMsg, wParam, lParam, bHandled);
    bHandled = TRUE;

    hicon = (HICON) ::LoadImage(_AtlBaseModule.GetResourceInstance(),
                                MAKEINTRESOURCE(IDI_AESCRYPT),
                                IMAGE_ICON,
                                LR_DEFAULTSIZE,
                                LR_DEFAULTSIZE,
                                LR_SHARED);

    SetIcon(hicon);

    // Center the dialog in the active window
    CenterWindow(GetForegroundWindow());

    // We set the lParam value when we create the window
    if (lParam)
    {
        SetDlgItemText( IDC_ENCRYPTINGMSG,
                        _T("Encrypting..."));
    }
    else
    {
        SetDlgItemText( IDC_ENCRYPTINGMSG,
                        _T("Decrypting..."));
    }

    // If the major OS version is less than 5, then set the status bar color
    // manually, otherwise we'll let the system use its defaults.
    GetVersionEx(&os_version_info);
    if (os_version_info.dwMajorVersion < 5)
    {
        // Set the progress bar color
        SendDlgItemMessage( IDC_PROGRESSBAR,
                            PBM_SETBARCOLOR,
                            0,
                            (LPARAM) (COLORREF) RGB(0,102,204));
    }

    return 1;  // Let the system set the focus
}

/*
 *  OnClickedCancel
 */
LRESULT ProgressDialog::OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    abort_processing = true;
    return 0;
}

