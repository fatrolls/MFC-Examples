// videocli.cpp : implementation file
//
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:40  $

#include "stdafx.h"
#include "docktest.h"
#include "videocli.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoClipDialog dialog


CVideoClipDialog::CVideoClipDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoClipDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoClipDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVideoClipDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoClipDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoClipDialog, CDialog)
	//{{AFX_MSG_MAP(CVideoClipDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVideoClipDialog message handlers

BOOL CVideoClipDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CWnd * pGroupBox = GetDlgItem(IDC_GROUP);

	CRect rect;
	pGroupBox->GetClientRect(&rect);
	
	char szPath[MAX_PATH], szDrive[MAX_PATH], szDir[MAX_PATH],
				 szName[MAX_PATH], szExt[MAX_PATH];
		
	GetModuleFileName(NULL, szPath, MAX_PATH);
	_splitpath(szPath, szDrive, szDir, szName, szExt);
	_makepath(szPath, szDrive, szDir, "smugfngr", "avi");
			
	m_pSmugVideo = new CMRCAnimateCtrl;
	if (m_pSmugVideo->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
								rect, pGroupBox, 99))
	{
		if (m_pSmugVideo->Open(szPath)	 
					&& m_pSmugVideo->Play(ACF_REPEAT, 0, -1, 0 ))
		{	
			CenterWindowWithinParent(m_pSmugVideo);
		}
		else
		{
			m_pSmugVideo->DestroyWindow();
 		 	CString strMsg;
			strMsg.Format("Error playing AVI file. Please ensure %s exists in the specified directory", 
						 szPath); 		 	
 		 	AfxMessageBox(strMsg);
		}
	}		
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
