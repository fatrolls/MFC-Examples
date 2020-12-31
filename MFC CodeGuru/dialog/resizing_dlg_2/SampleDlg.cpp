// SampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ResizeDlg.h"

#include "ResizingDialog.h"

#include "SampleDlg.h"
#include "telescrp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg dialog


CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	CDWordArray c_info;
	SetControlInfo(IDC_LEFT_RESIZE,		RESIZE_HOR | RESIZE_VER);
	SetControlInfo(IDC_BOTTOM_ANCHORE,	ANCHORE_BOTTOM | RESIZE_HOR);
	SetControlInfo(IDOK,				ANCHORE_RIGHT);
	SetControlInfo(IDCANCEL,			ANCHORE_RIGHT);
	SetControlInfo(IDC_RIGHT_VER_RESIZE,ANCHORE_RIGHT | RESIZE_VER);
	SetControlInfo(IDC_SLIDER1,			ANCHORE_RIGHT | RESIZE_VER);
	
}


void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSampleDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CSampleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg message handlers

void CSampleDlg::OnOK() 
{
		ITeleSc nDriver;
 	// Save the current file

	// User cancelled the operation
	// by not saving the script.

	if (!nDriver.CreateDispatch(_T("TeleScript.Document"))) 
	{
		AfxMessageBox("Failed CreateDispatch");
		return; // problem
    }

	nDriver.SetTestMode(TRUE);

	if( !nDriver.OpenScript("C:\\projects\\ev_inbound.tsr"))
		{
			nDriver.ShutDown(); // tell the player to shut down
			AfxMessageBox("Error");
			return; // problem
		}

	
	CResizingDialog::OnOK();
}
