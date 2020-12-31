// UrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Spider.h"
#include "UrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUrlDlg dialog
IMPLEMENT_SERIAL (CUrlDlg, CDialog, 1)


CUrlDlg::CUrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUrlDlg)
	m_root = FALSE;
	//}}AFX_DATA_INIT
	m_select=0;

}


void CUrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUrlDlg)
	DDX_Control(pDX, IDC_URLCOMBO, m_comboBox);
	DDX_Check(pDX, IDC_CHECKROOT, m_root);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUrlDlg, CDialog)
	//{{AFX_MSG_MAP(CUrlDlg)
	ON_CBN_SELCHANGE(IDC_URLCOMBO, OnSelchangeUrlcombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUrlDlg message handlers
void CUrlDlg::Serialize(CArchive& ar) 
{
    CDialog::Serialize (ar);

	if (ar.IsStoring())
	{	// storing code
		ar << m_count << m_select << m_root;

	}
	else
	{	// loading code
		ar >> m_count >> m_select >> m_root;

	}
	m_list.Serialize(ar);
	
	
}

BOOL CUrlDlg::LoadFile (LPCSTR lpszFileName)
{
    CFile file;
    BOOL bResult = TRUE;

    if (file.Open (lpszFileName, CFile::modeRead)) {
        CWaitCursor wait;
        CArchive ar (&file, CArchive::load);
		m_list.RemoveAll();
		Serialize (ar);

        //Invalidate ();
    }
    else {
        bResult = FALSE;
    }
    return bResult;
}

BOOL CUrlDlg::SaveFile (LPCSTR lpszFileName)
{
    CFile file;
    BOOL bResult = TRUE;

    if (file.Open (lpszFileName, CFile::modeCreate | CFile::modeWrite)) {
        CWaitCursor wait;
        CArchive ar (&file, CArchive::store);
        Serialize (ar);
    }
    else {
        CString string;
        string.Format ("Unable to Save URL Settings in file  %s", lpszFileName);
        MessageBox (string, "Error", MB_ICONEXCLAMATION | MB_OK);
        bResult = FALSE;
    }
    return bResult;
}

void CUrlDlg::OnOK()
{
	m_comboBox.GetWindowText(m_WebFileName);


	int nListCount =m_comboBox.GetCount();
	m_list.RemoveAll();
			

	// update the combo box so the most recently used URL is at the top
	CString strTemp;
	while (nListCount > 0)
	{
		m_comboBox.GetLBText(--nListCount, strTemp);
		if (m_WebFileName.Compare(strTemp) == 0)
		{
			m_comboBox.DeleteString(nListCount);
			nListCount = 0;
		}
	}
	m_comboBox.InsertString(0,(LPCTSTR) m_WebFileName );

	 nListCount =m_comboBox.GetCount();
	for(int i=0; i<nListCount; i++)
		
	{
		m_comboBox.GetLBText(i, strTemp);

		m_list.AddTail((LPCSTR) strTemp);
	}

	
	m_select = m_comboBox.GetCurSel();


	CDialog::OnOK();
}



BOOL CUrlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString rString;
	POSITION pos=NULL;
	
	int count= m_list.GetCount();
	if(count>0)
	{
		m_comboBox.ResetContent();

		for(int i=0; i<count; i++)
		{
				if( ( pos = m_list.FindIndex( i)) != NULL )
				{
					rString = m_list.GetAt( pos );
					m_comboBox.InsertString(i,(LPCTSTR) rString );

				}
			
		}
	}
	m_comboBox.SetCurSel(m_select);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUrlDlg::OnSelchangeUrlcombo() 
{
	m_select = m_comboBox.GetCurSel();
	if(m_select==CB_ERR) return;
	m_comboBox.SetCurSel(m_select);
	m_comboBox.GetLBText(m_select,m_WebFileName);
	
}
