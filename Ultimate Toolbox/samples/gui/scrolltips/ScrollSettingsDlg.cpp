// ScrollSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScrollTipDemo.h"
#include "ScrollSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollSettingsDlg dialog


CScrollSettingsDlg::CScrollSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrollSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollSettingsDlg)
	m_sHorizontalMask = _T("");
	m_bHorizontalPageAlign = FALSE;
	m_bHorizontalTop = FALSE;
	m_bVerticalLeft = FALSE;
	m_sVerticalMask = _T("");
	m_bVerticalPageAlign = FALSE;
	//}}AFX_DATA_INIT
}


void CScrollSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollSettingsDlg)
	DDX_Text(pDX, IDC_HORZ_MASK, m_sHorizontalMask);
	DDX_Check(pDX, IDC_HORZ_PAGE_ALIGN, m_bHorizontalPageAlign);
	DDX_Check(pDX, IDC_HORZ_TOP, m_bHorizontalTop);
	DDX_Check(pDX, IDC_VERT_LEFT, m_bVerticalLeft);
	DDX_Text(pDX, IDC_VERT_MASK, m_sVerticalMask);
	DDX_Check(pDX, IDC_VERT_PAGE_ALIGN, m_bVerticalPageAlign);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScrollSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollSettingsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollSettingsDlg message handlers
