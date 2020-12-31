// SendDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Communicator.h"
#include "SendDataDlg.h"
#include "OXBlob.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendDataDlg dialog


CSendDataDlg::CSendDataDlg(COXCommMsg* pCommMsg, CWnd* pParent /*=NULL*/)
	: 
	CDialog(CSendDataDlg::IDD, pParent),
	m_pCommMsg(pCommMsg)
	{
	//{{AFX_DATA_INIT(CSendDataDlg)
	m_sValue = _T("");
	m_nType = 9;
	//}}AFX_DATA_INIT
	}


void CSendDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendDataDlg)
	DDX_Control(pDX, IDC_BROWSE, m_wndBrowse);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Text(pDX, IDC_VALUE, m_sValue);
	DDX_Radio(pDX, IDC_EMPTY, m_nType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendDataDlg, CDialog)
	//{{AFX_MSG_MAP(CSendDataDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendDataDlg message handlers

void CSendDataDlg::OnAdd() 
	{
	UINT nOleType = 0;
	COXVariant oleVariant;
	BOOL bSuccess = FALSE;
	CString sValue;

	UpdateData(TRUE);
	ASSERT((0 <= m_nType) && (m_nType < COXCommMsg::m_nArgumentTypesCount));
	nOleType = COXCommMsg::m_types[m_nType];

	// Assign as string and then let OLE convert it
	oleVariant = m_sValue;
	long nFileLength = 0;
	TRY
		{
		if (nOleType == COXCommMsg::ATBlob)
			{
			COXBlob blob;
			bSuccess = blob.ReadRaw(m_sValue);
			nFileLength = blob.GetSize();
			oleVariant = blob;
			}
		else if (nOleType != COXCommMsg::ATError)
			{
			oleVariant.ChangeType((VARTYPE)nOleType);
			bSuccess = TRUE;
			}
		else
			{
			// Conversions to and from VT_ERROR is not available from OLE
			// Use a VT_I4 instead
			oleVariant.ChangeType(COXCommMsg::ATI4);
			// ... Variant is a union, just change the type
			// oleVariant.scode = oleVariant.lVal;
			V_VT(&oleVariant) = (VARTYPE)nOleType;
			bSuccess = TRUE;
			}
		}
	END_TRY

	if (bSuccess)
		{
		m_pCommMsg->Add(oleVariant);
		// Convert back to string to visualize
		CString sText;
		TRY	
			{ 
			if (nOleType == COXCommMsg::ATBlob)
				sText.Format(_T("<binary of length %i>"), nFileLength);
			else
				{
				if (V_VT(&oleVariant) == COXCommMsg::ATError)
					// ... Variant is a union, just change the type
					// oleVariant.lVal= oleVariant.scode ;
					V_VT(&oleVariant) = COXCommMsg::ATI4;
				oleVariant.ChangeType(COXCommMsg::ATStr); 
				sText = V_BSTR(&oleVariant);
				}
			} 
		END_TRY
		sValue.Format(_T("%i. (%s) %s"), 
			m_wndList.GetCount() + 1,
			(LPCTSTR)COXCommMsg::m_typeNames[m_nType],
			(LPCTSTR)sText);
		m_wndList.AddString(sValue);
		m_wndList.SetTopIndex(m_wndList.GetCount() - 1);
		}
	else
		{
		AfxMessageBox(IDS_INVALID_VALUE, MB_ICONEXCLAMATION);
		}
	}

void CSendDataDlg::OnBrowse() 
	{
	UpdateData(TRUE);
	static TCHAR szFilter[] = _T("All Files (*.*) | *.* ||");
	CFileDialog fileDlg(TRUE, NULL, _T("*.*"), NULL, szFilter);

	if (fileDlg.DoModal() == IDOK)
		{
		m_sValue = fileDlg.GetPathName();
		// ... Set to Blob type by default
		m_nType = 12;
		UpdateData(FALSE);
		}

	}

