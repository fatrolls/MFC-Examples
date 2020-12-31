// pendlg.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#include "stdafx.h"
#include "scribble.h"
#include "pendlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPenWidthsDlg dialog

CPenWidthsDlg::CPenWidthsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPenWidthsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPenWidthsDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_nThickWidth = 0;
	m_nThinWidth = 0;
	//}}AFX_DATA_INIT
}

void CPenWidthsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPenWidthsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_THIN_PEN_WIDTH, m_nThinWidth);
	DDV_MinMaxInt(pDX, m_nThinWidth, 1, 20);
	DDX_Text(pDX, IDC_THICK_PEN_WIDTH, m_nThickWidth);
	DDV_MinMaxInt(pDX, m_nThickWidth, 1, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPenWidthsDlg, CDialog)
	//{{AFX_MSG_MAP(CPenWidthsDlg)
		// NOTE: the ClassWizard will add message map macros here
	ON_BN_CLICKED(IDC_DEFAULT_PEN_WIDTHS, OnDefaultPenWidths)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPenWidthsDlg message handlers



void CPenWidthsDlg::OnDefaultPenWidths()
{
	m_nThinWidth = 2;
	m_nThickWidth = 5;
	UpdateData(FALSE);  // causes DoDataExchange()
		// bSave=FALSE means don't save from screen,
		// rather, write to screen
}
