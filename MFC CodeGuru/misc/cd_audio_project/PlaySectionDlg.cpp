// PlaySectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MCISample.h"
#include "PlaySectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaySectionDlg dialog


CPlaySectionDlg::CPlaySectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlaySectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlaySectionDlg)
	m_nFrameFrom = 0;
	m_nFrameTo = 0;
	m_nMinuteFrom = 0;
	m_nMinuteTo = 0;
	m_nSecondFrom = 0;
	m_nSecondTo = 0;
	//}}AFX_DATA_INIT
}


void CPlaySectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlaySectionDlg)
	DDX_Text(pDX, IDC_FRAME_FROM, m_nFrameFrom);
	DDV_MinMaxByte(pDX, m_nFrameFrom, 0, 255);
	DDX_Text(pDX, IDC_FRAME_TO, m_nFrameTo);
	DDV_MinMaxByte(pDX, m_nFrameTo, 0, 255);
	DDX_Text(pDX, IDC_MINUTE_FROM, m_nMinuteFrom);
	DDV_MinMaxByte(pDX, m_nMinuteFrom, 0, 255);
	DDX_Text(pDX, IDC_MINUTE_TO, m_nMinuteTo);
	DDV_MinMaxByte(pDX, m_nMinuteTo, 0, 255);
	DDX_Text(pDX, IDC_SECOND_FROM, m_nSecondFrom);
	DDV_MinMaxByte(pDX, m_nSecondFrom, 0, 255);
	DDX_Text(pDX, IDC_SECOND_TO, m_nSecondTo);
	DDV_MinMaxByte(pDX, m_nSecondTo, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlaySectionDlg, CDialog)
	//{{AFX_MSG_MAP(CPlaySectionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaySectionDlg message handlers
