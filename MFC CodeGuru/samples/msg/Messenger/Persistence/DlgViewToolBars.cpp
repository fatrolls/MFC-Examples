/* 
 * Copyright (c)1997 David Carballo, All Right Reserved
 *
 * Created October 1997
 * Revised: -
 * Written by David Carballo
 * Internet: fibeto@redestb.es
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 */

#include "stdafx.h"

#ifndef __DLGVIEWTOOLBARS_H_
#include "DlgViewToolBars.h"
#endif	// __DLGVIEWTOOLBARS_H_

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewToolBars dialog


CDlgViewToolBars::CDlgViewToolBars(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewToolBars::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewToolBars)
	m_bShowToolTips = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgViewToolBars::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewToolBars)
	DDX_Control(pDX, IDC_LIST_TOOLBARS, m_lstToolbars);
	DDX_Check(pDX, IDC_CHECK_TOOLTIPS, m_bShowToolTips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewToolBars, CDialog)
	//{{AFX_MSG_MAP(CDlgViewToolBars)
	ON_BN_CLICKED(IDC_CHECK_TOOLTIPS, OnCheckTooltips)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewToolBars message handlers

void CDlgViewToolBars::OnCheckTooltips() 
{
	UpdateData();

	CFrameWnd*		pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	
	ASSERT_VALID(pMainFrame);

	POSITION		pos = pMainFrame->m_listControlBars.GetHeadPosition();
	
	CControlBar*	pBar = NULL;
	

	while (pos != NULL)
	{
		pBar = (CControlBar*)pMainFrame->m_listControlBars.GetNext(pos);

		ASSERT(pBar != NULL);
		ASSERT_VALID(pBar);

		if (pBar->IsKindOf(RUNTIME_CLASS(CToolBar)) || 
			pBar->IsKindOf(RUNTIME_CLASS(CDialogBar)))
		{
			if (m_bShowToolTips)
			{
				pBar->SetBarStyle(pBar->GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
			}
			else
			{
				pBar->SetBarStyle(pBar->GetBarStyle() & ~(CBRS_TOOLTIPS | CBRS_FLYBY));
			}
		}
	}
	
}

BOOL CDlgViewToolBars::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_lstToolbars.SetCheckStyle(BS_AUTOCHECKBOX);
	FillListToolBars();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgViewToolBars::FillListToolBars()
{
	CFrameWnd*		pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	
	ASSERT_VALID(pMainFrame);

	POSITION		pos = pMainFrame->m_listControlBars.GetHeadPosition();
	CString			sToolBarText;
	CControlBar*	pBar = NULL;
	int				iText;

	while (pos != NULL)
	{
		pBar = (CControlBar*)pMainFrame->m_listControlBars.GetNext(pos);

		ASSERT(pBar != NULL);
		ASSERT_VALID(pBar);

		if (pBar->IsKindOf(RUNTIME_CLASS(CToolBar)) || 
			pBar->IsKindOf(RUNTIME_CLASS(CDialogBar)))
		{
			pBar->GetWindowText(sToolBarText);

			iText = m_lstToolbars.AddString(sToolBarText);
			m_lstToolbars.SetItemDataPtr(iText, pBar);
			m_lstToolbars.SetCheck(iText, pBar->IsWindowVisible());
		}
	}
}

BOOL CDlgViewToolBars::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (HIWORD(wParam) == CLBN_CHKCHANGE && LOWORD(wParam) == IDC_LIST_TOOLBARS)
	{
		CFrameWnd*		pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	
		ASSERT_VALID(pMainFrame);

		int				nIndex = m_lstToolbars.GetCaretIndex();
		BOOL			bChecked;
		CControlBar*	pBar = NULL;

		if (nIndex != LB_ERR)
		{
			bChecked = m_lstToolbars.GetCheck(nIndex);

			pBar = (CControlBar*)m_lstToolbars.GetItemDataPtr(nIndex);
			if (NULL != pBar)
			{
				pMainFrame->ShowControlBar(pBar, bChecked, FALSE);
			}
		}

		return TRUE;
	}
	
	return CDialog::OnCommand(wParam, lParam);
}
