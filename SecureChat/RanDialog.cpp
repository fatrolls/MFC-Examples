// RanDialog.cpp : implementation file
//

#include "stdafx.h"
#include "RanDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRanDialog dialog


CRanDialog::CRanDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRanDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRanDialog)
	//}}AFX_DATA_INIT
	m_times_around=0;
	m_raw_pool_ptr=0;
	m_max_times_around=4;
}

void CRanDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRanDialog)
	DDX_Control(pDX, IDC_PROGRESS, m_cProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRanDialog, CDialog)
	//{{AFX_MSG_MAP(CRanDialog)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRanDialog message handlers

void CRanDialog::stir_it(unsigned int x)
{ // cycle around pool....
	m_raw_pool[m_raw_pool_ptr]^=(char)x;
	m_raw_pool_ptr++;
	if (m_raw_pool_ptr==_POOL_SIZE_) 
	{
		// Mininmum one klick ! 
		if ( m_times_around<m_max_times_around-1 )
		{
		  m_times_around++;
		}
		m_raw_pool_ptr=0;
	}
	m_cProgress.StepIt();
}


void CRanDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( m_times_around>=m_max_times_around )
	{
		CDialog::OnOK();
	}else
	{
		LARGE_INTEGER large;
		unsigned int i;
		QueryPerformanceCounter(&large);
		i=(unsigned int)large.LowPart;
		stir_it(i);
		stir_it(i>>8);
		stir_it(i>>16);		// bottom 24 bits look good!
		stir_it((unsigned int)point.x);
		stir_it((unsigned int)point.y);
	}
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CRanDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_times_around=0;
	m_raw_pool_ptr=0;
	m_max_times_around=4;
	m_cProgress.SetRange(0,m_max_times_around*_POOL_SIZE_);
	m_cProgress.SetStep(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRanDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Collect some entropy 
	LARGE_INTEGER large;
	unsigned int i;
	QueryPerformanceCounter(&large);
	i=(unsigned int)large.LowPart;
	stir_it(i);
	stir_it(i>>8);
	stir_it(i>>16);		// bottom 24 bits look good!
	stir_it((unsigned int)point.x);
	stir_it((unsigned int)point.y);
	
	// Hash the entire pool with SHA1. 
	MyCryptLib Cryptor;
	PBYTE pBuff=m_raw_pool;
	for(int j=0;j<_POOL_SIZE_/20;j++)
	{
		Cryptor.SHA1Hash(pBuff+j*20,m_raw_pool,_POOL_SIZE_);
	}	
	m_times_around++;
	m_cProgress.SetPos(m_times_around*_POOL_SIZE_);
	CDialog::OnLButtonDown(nFlags, point);
}
