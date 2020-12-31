// MfcSaverDlg.cpp : implementation file
//
//////////
//
// Copyright (C) 1991-98 Ed Halley.
//   http://www.explorati.com/people/ed/
//   ed@explorati.com
//
// This published source code represents original intellectual
// property, owned and copyrighted by Ed Halley.
//
// The owner has authorized this source code for general public
// use without royalty, under two conditions:
//    * The source code maintains this copyright notice in full.
//    * The source code is only distributed for free or
//      reasonable duplication cost, not for distribution profit.
//
// Unauthorized use, copying or distribution is a violation of
// U.S. and international laws and is strictly prohibited.
//
//////////
//

#include "StdAfx.h"
#include "MfcSaver.h"
#include "MfcSaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMfcSaverDlg, CScreenSaverDlg)
	//{{AFX_MSG_MAP(CMfcSaverDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnURL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMfcSaverDlg::CMfcSaverDlg()
{
	//{{AFX_DATA_INIT(CMfcSaverDlg)
	//}}AFX_DATA_INIT
}

BOOL CMfcSaverDlg::OnInitDialog()
{
	CScreenSaverDlg::OnInitDialog();

	return TRUE;
}

void CMfcSaverDlg::OnURL() 
{
	CString sURL;
	GetDlgItemText(IDC_BUTTON1, sURL);
	::ShellExecute(m_hWnd, NULL, sURL, NULL, NULL, 0);
}

/////////////////////////////////////////////////////////////////////////////

//
// As with most MFC dialog boxes, the DoDataExchange() is where all the work
// happens.  There's no easy DDX_Trackbar thing to set up the control, so
// we do it ourselves.  See how the SaveOptions() and RestoreOptions() are
// called on the CMfcSaver to keep those options persistent.
//

void CMfcSaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CScreenSaverDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcSaverDlg)
	//}}AFX_DATA_MAP

	CMfcSaver* pSaver = (CMfcSaver*)AfxGetScreenSaverWnd();
	if (!pSaver)
		return;

	CSliderCtrl* pSlider;
	if (!pDX->m_bSaveAndValidate)
	{
		pSaver->RestoreOptions();

		pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
		pSlider->SetRange(1, 50);
		pSlider->SetPos(pSaver->GetIconCount());

		pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
		pSlider->SetRange(1, 50);
		pSlider->SetPos(pSaver->GetIconSpeed());
	}
	else
	{
		pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
		pSaver->SetIconCount(pSlider->GetPos());

		pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
		pSaver->SetIconSpeed(pSlider->GetPos());

		pSaver->SaveOptions();
	}
}

