/*
 *  PasswdDialog.cpp
 *
 *  Copyright (C) 2006, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This module implements a simple dialog box for prompting the user for
 *  a password.
 *
 */


#include "stdafx.h"
#include "PasswdDialog.h"

/*
 *  PasswdDialog Constructor
 */
PasswdDialog::PasswdDialog()
{
}

/*
 *  PasswdDialog Destructor
 */
PasswdDialog::~PasswdDialog()
{
}

/*
 *  OnInitDialog
 */
LRESULT PasswdDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    HWND window_handle;
    HICON hicon;

    CAxDialogImpl<PasswdDialog>::OnInitDialog(uMsg, wParam, lParam, bHandled);
    bHandled = TRUE;

    hicon = (HICON) ::LoadImage(_AtlBaseModule.GetResourceInstance(),
                                MAKEINTRESOURCE(IDI_AESCRYPT),
                                IMAGE_ICON,
                                LR_DEFAULTSIZE,
                                LR_DEFAULTSIZE,
                                LR_SHARED);
        
    SetIcon(hicon);
                    
    CenterWindow(GetForegroundWindow());

    // Limit the length of text in the password boxes to
    // MAX_PASSWD_LEN characters
    SendDlgItemMessage( IDC_PASSWD,
                        EM_SETLIMITTEXT,
                        MAX_PASSWD_LEN,
                        0);
    if (lParam)
    {
        encrypting = true;

        SendDlgItemMessage( IDC_PASSWDCONFIRM,
                            EM_SETLIMITTEXT,
                            MAX_PASSWD_LEN,
                            0);
    }
    else
    {
        encrypting = false;

        // Hide the password confirmation controls
        window_handle = GetDlgItem(IDC_PASSWDCONFIRM);
        ::ShowWindow(window_handle, SW_HIDE);
        window_handle = GetDlgItem(IDC_ENTERPASSWDCONFIRM);
        ::ShowWindow(window_handle, SW_HIDE);
    }
    
    return 1;  // Let the system set the focus
}

/*
 *  OnClickedOK
 */
LRESULT PasswdDialog::OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    TCHAR passwdconfirm[MAX_PASSWD_LEN+2];

    GetDlgItemText( IDC_PASSWD,
                    passwd,
                    MAX_PASSWD_LEN);
    
    // If we are encrypting files, check to make sure that the
    // password entered into the conformation field matches.
    // If decrypting, the confirmation is not necessary.
    if (encrypting)
    {
        GetDlgItemText( IDC_PASSWDCONFIRM,
                        passwdconfirm,
                        MAX_PASSWD_LEN);

        if (_tcscmp(passwd,passwdconfirm))
        {
            MessageBox( _T("Password confirmation check failed.\nVerify that the passwords match."),
                        _T("AES Crypt"),
                        MB_OK);
        }
        else if (_tcsnlen(passwd, MAX_PASSWD_LEN) == 0)
        {
            MessageBox( _T("You failed to enter a password."),
                        _T("AES Crypt"),
                        MB_OK);
        }
        else
        {
                    EndDialog(wID);
        }
    }
    else
    {
        if (_tcsnlen(passwd, MAX_PASSWD_LEN) == 0)
        {
            MessageBox( _T("You failed to enter a password."),
                        _T("AES Crypt"),
                        MB_OK);
        }
        else
        {
            EndDialog(wID);
        }
    }

    return 0;
}

/*
 *  OnClickedCancel
 */
LRESULT PasswdDialog::OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    EndDialog(wID);
    return 0;
}

