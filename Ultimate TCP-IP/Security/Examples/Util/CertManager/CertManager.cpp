// =================================================================
//  File:  CertManager.cpp
//  
//  Purpose:
//
//  Defines the entry point for the Certificate Manager application.
//
// =================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================

#include "stdafx.h"
#include "UTCertifListDlg.h"

int APIENTRY WinMain(HINSTANCE /* hInstance */,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
	CUT_CertificateListDlg	dlg;

	// set options
	dlg.SetTitle(_T("Certificate Manager"));
	dlg.SetStoreNames(_T(""));
	dlg.SetViewCertOnDblClk();

	// show certificate list dialog
	dlg.OpenDlg();
	return 0;
}



