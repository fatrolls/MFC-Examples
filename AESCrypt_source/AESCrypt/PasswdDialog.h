/*
 *  PasswdDialog.cpp
 *
 *  Copyright (C) 2006, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This file defines a simple dialog box class for prompting the user for
 *  a password.
 *
 */


#pragma once

#include "resource.h"
#include <atlhost.h>


class PasswdDialog : public CAxDialogImpl<PasswdDialog>
{
    public:
        PasswdDialog();

        ~PasswdDialog();

        enum { IDD = IDD_PASSWDDIALOG };

        TCHAR passwd[MAX_PASSWD_LEN+1];
        bool encrypting;

        BEGIN_MSG_MAP(PasswdDialog)
	        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	        COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	        COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	        CHAIN_MSG_MAP(CAxDialogImpl<PasswdDialog>)
        END_MSG_MAP()

        // Handler prototypes:
        //  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        //  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        //  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

        LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

        LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

        LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

