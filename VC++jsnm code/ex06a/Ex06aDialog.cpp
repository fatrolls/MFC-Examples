// Ex06aDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex06a.h"
#include "Ex06aDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx06aDialog dialog


CEx06aDialog::CEx06aDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx06aDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEx06aDialog)
	m_strBio = _T("");
	m_nCat = -1;
	m_strDept = _T("");
	m_bInsDis = FALSE;
	m_strEduc = _T("");
	m_strLang = _T("");
	m_bInsLife = FALSE;
	m_nLoyal = 0;
	m_bInsMed = FALSE;
	m_strName = _T("");
	m_nRely = 0;
	m_strSkill = _T("");
	m_nSsn = 0;
	//}}AFX_DATA_INIT
}


void CEx06aDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx06aDialog)
	DDX_Text(pDX, IDC_BIO, m_strBio);
	DDX_Radio(pDX, IDC_CAT, m_nCat);
	DDX_LBString(pDX, IDC_DEPT, m_strDept);
	DDX_Check(pDX, IDC_DIS, m_bInsDis);
	DDX_CBString(pDX, IDC_EDUC, m_strEduc);
	DDX_CBString(pDX, IDC_LANG, m_strLang);
	DDX_Check(pDX, IDC_LIFE, m_bInsLife);
	DDX_Scroll(pDX, IDC_LOYAL, m_nLoyal);
	DDX_Check(pDX, IDC_MED, m_bInsMed);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Scroll(pDX, IDC_RELY, m_nRely);
	DDX_CBString(pDX, IDC_SKILL, m_strSkill);
	DDX_Text(pDX, IDC_SSN, m_nSsn);
	DDV_MinMaxInt(pDX, m_nSsn, 0, 999999999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEx06aDialog, CDialog)
	//{{AFX_MSG_MAP(CEx06aDialog)
	ON_BN_CLICKED(IDC_SPECIAL, OnSpecial)
	ON_BN_CLICKED(IDC_OK, OnClickedOk)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx06aDialog message handlers

void CEx06aDialog::OnSpecial() 
{
	TRACE("CEx06aDialog::OnSpecial\n");	
}

BOOL CEx06aDialog::OnInitDialog() 
{
	// Be careful to call CDialog::OnInitDialog
	//  only once in this function
	CListBox* pLB = (CListBox*) GetDlgItem(IDC_DEPT);
	pLB->InsertString(-1, "Documentation");
	pLB->InsertString(-1, "Accounting");
	pLB->InsertString(-1, "Human Relations");
	pLB->InsertString(-1, "Security");

	CScrollBar* pSB = (CScrollBar*) GetDlgItem(IDC_LOYAL);
	pSB->SetScrollRange(nMin, nMax);

	pSB = (CScrollBar*) GetDlgItem(IDC_RELY);
	pSB->SetScrollRange(nMin, nMax);

	// Call after initialization
	return CDialog::OnInitDialog();
}

void CEx06aDialog::OnOK() 
{
	// dummy OnOK function -- do NOT call CDialog::OnOK()
	TRACE("CEx06aDialog::OnOK\n");
}

void CEx06aDialog::OnClickedOk() 
{
	TRACE("CEx06aDialog::OnClickedOk\n");
	CDialog::OnOK();
}

void CEx06aDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nTemp1, nTemp2;

	nTemp1 = pScrollBar->GetScrollPos();
	switch(nSBCode) {
	case SB_THUMBPOSITION:
		pScrollBar->SetScrollPos(nPos);
		break;
	case SB_LINELEFT: // left arrow button
		nTemp2 = (nMax - nMin) / 10;
		if ((nTemp1 - nTemp2) > nMin) {
			nTemp1 -= nTemp2;
		}
		else {
			nTemp1 = nMin;
		}
		pScrollBar->SetScrollPos(nTemp1);
		break;
	case SB_LINERIGHT: // right arrow button
		nTemp2 = (nMax - nMin) / 10;
		if ((nTemp1 + nTemp2) < nMax) {
			nTemp1 += nTemp2;
		}
		else {
			nTemp1 = nMax;
		}
		pScrollBar->SetScrollPos(nTemp1);
		break;
	}
}
