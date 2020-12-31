// Demo3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SemiTransparentDialogWithStandardCtrls.h"
#include "Demo3Dlg.h"


// CDemo3Dlg dialog

IMPLEMENT_DYNAMIC(CDemo3Dlg, CDialog)

CDemo3Dlg::CDemo3Dlg(CWnd* pParent /*=NULL*/)
	: CImgDialogBase(CDemo3Dlg::IDD
	, IDB_PNG_DLG2
	, _T("PNG")
	, AfxGetResourceHandle()
	, pParent
	)
{

}

CDemo3Dlg::~CDemo3Dlg()
{
}

void CDemo3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CImgDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctlTree);
}


BEGIN_MESSAGE_MAP(CDemo3Dlg, CImgDialogBase)
END_MESSAGE_MAP()


// CDemo3Dlg message handlers

void CDemo3Dlg::PostNcDestroy()
{
	CImgDialogBase::PostNcDestroy();
	delete this;
}

BOOL CDemo3Dlg::OnInitDialog()
{
	CImgDialogBase::OnInitDialog();

	HTREEITEM hRoot = m_ctlTree.InsertItem( _T("Root") );
	for( int i = 0; i < 100; i++)
	{
		CString strTemp;
		strTemp.Format( _T("Node %02d"), i);
		m_ctlTree.InsertItem( strTemp, hRoot);
	}
	m_ctlTree.Expand( hRoot, TVE_EXPAND);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
