// Demo2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SemiTransparentDialogWithStandardCtrls.h"
#include "Demo2Dlg.h"
#include "./Src/Utility.h"

// CDemo2Dlg dialog

IMPLEMENT_DYNAMIC(CDemo2Dlg, CDialog)

CDemo2Dlg::CDemo2Dlg(CWnd* pParent /*=NULL*/)
	: CImgDialogBase( CDemo2Dlg::IDD
	, CUtility::GetModulePath() + _T("background.png")
	, pParent
	)
{

}

CDemo2Dlg::~CDemo2Dlg()
{
}

void CDemo2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CImgDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_lstDemo);
}


BEGIN_MESSAGE_MAP(CDemo2Dlg, CImgDialogBase)
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()


// CDemo2Dlg message handlers

BOOL CDemo2Dlg::OnInitDialog()
{
	CImgDialogBase::OnInitDialog();

	m_lstDemo.InsertColumn( 0, _T("Column1"), 0, 100);
	m_lstDemo.InsertColumn( 1, _T("Column2"), 0, 100);
	m_lstDemo.InsertColumn( 3, _T("Column3"), 0, 100);

	for( int i = 0; i < 100; i++)
	{
		CString strTemp;
		strTemp.Format( _T("Item %02d"), i);
		int nIndex = m_lstDemo.InsertItem( 0xFFFF, strTemp);

		strTemp.Format( _T("%X"), GetTickCount()+i);
		m_lstDemo.SetItemText( nIndex, 1, strTemp);
		m_lstDemo.SetItemText( nIndex, 2, strTemp);
	}

	m_lstDemo.SetExtendedStyle( m_lstDemo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_TRACKSELECT );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDemo2Dlg::OnNcDestroy()
{
	CImgDialogBase::OnNcDestroy();
	delete this;
}
