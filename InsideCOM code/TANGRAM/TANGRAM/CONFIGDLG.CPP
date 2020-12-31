///////////////////////////////////////////////////////////
//
//
// ConfigDlg.cpp : implementation file
//
//

#include "stdafx.h"
#include "tangram.h"
#include "ConfigDlg.h"

#include <objbase.h>
#include <comcat.h>
#include <initguid.h>
#include "WorldCat.h" //CATID_TangramWorldCategory

#include "registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Helper function
BOOL getFriendlyName(const CLSID& clsid, LPCTSTR szFriendlyName, int iLength);

///////////////////////////////////////////////////////////
//
// CConfigDlg dialog
//

///////////////////////////////////////////////////////////
//
// Constructor
//
CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)

	m_bLocalModel = FALSE;
	//}}AFX_DATA_INIT
}


///////////////////////////////////////////////////////////
//
// DoDataExchange
//
void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_WORLD_LIST, m_listWorld);
	DDX_Check(pDX, IDC_MODEL_LOCAL_CHECK, m_bLocalModel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//
//
// CConfigDlg message handlers
//
//
///////////////////////////////////////////////////////////
//
// OnInitDialog
//
BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// --- Fill the World Components list box with components with the world CATID. ---

	// Create the standard COM Category Manager
	ICatInformation* pICatInformation = NULL ;
	HRESULT hr = ::CoCreateInstance(	CLSID_StdComponentCategoriesMgr,
										NULL, CLSCTX_ALL, IID_ICatInformation,
										(void**)&pICatInformation) ;
	if (FAILED(hr))
	{
		ASSERT(hr) ;
		return FALSE;
	}

	// Array of Categories
	int cIDs = 1 ;
	CATID IDs[1] ;
	IDs[0] = CATID_TangramWorldCategory ;

		// Get the IEnumCLSID interface.
	IEnumCLSID* pIEnumCLSID = NULL ;
	hr = pICatInformation->EnumClassesOfCategories(cIDs, IDs, 0, NULL, &pIEnumCLSID) ;
	ASSERT(SUCCEEDED(hr)) ;

	// Get the next CLSID in the list.
	char szFriendlyName[128] ;
	CLSID clsid ;

	while ((hr = pIEnumCLSID->Next(1, &clsid, NULL)) == S_OK)
	{
		// We have the clsid
		// Get the friendly name for the clsid.
		if (getFriendlyName(clsid, szFriendlyName, sizeof(szFriendlyName)))
		{
			int index = m_listWorld.AddString(szFriendlyName) ;

			// Add the clisd to the listbox.
			CLSID* pclsid = new CLSID ;
			*pclsid = clsid ;

			m_listWorld.SetItemDataPtr(index, pclsid) ;
		}
	}
	ASSERT(SUCCEEDED(hr)) ;

	if (m_listWorld.GetCount() > 0)
	{
		m_listWorld.SetCurSel(0) ;
	}


	// CleanUp
	pICatInformation->Release() ;
	
	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

///////////////////////////////////////////////////////////
//
// OnDestroy
//
void CConfigDlg::OnDestroy() 
{
	// Clean up the data in the list box.
	int count = m_listWorld.GetCount() ;

	for (int i = 0 ; i < count ; i++)
	{
		CLSID* pclisd = reinterpret_cast<CLSID*>(m_listWorld.GetItemDataPtr(i)) ;
		delete pclisd ;
	}

	CDialog::OnDestroy();
}

///////////////////////////////////////////////////////////
//
// getFriendlyName Helper function.
//
BOOL getFriendlyName(const CLSID& clsid, LPCTSTR szFriendlyName, int iLength)
{
	HKEY hKey;
	char szKeyBuf[1024] ;
	char szCLSID[CLSID_STRING_SIZE] ;

	// Convert the clsid to a string.
	CLSIDtochar(clsid, szCLSID, CLSID_STRING_SIZE) ;

	// Make the key.
	sprintf(szKeyBuf, "CLSID\\%s", szCLSID) ;

	// Create and open key and subkey.
	long lResult = RegOpenKeyEx(	HKEY_CLASSES_ROOT ,
									szKeyBuf, 
									0, 
									KEY_ALL_ACCESS, 
									&hKey) ;
	if (lResult != ERROR_SUCCESS)
	{
		return FALSE ;
	}

	// Set the Value.
	ASSERT(szFriendlyName != NULL) ;
	DWORD dwSize = iLength ;
	lResult = RegQueryValueEx( hKey, NULL, NULL, NULL, (BYTE *)szFriendlyName, &dwSize);

	RegCloseKey(hKey);

	return lResult == ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////
//
// OnCancel
//
void CConfigDlg::OnCancel() 
{
	m_clsid = GUID_NULL ;
		
	CDialog::OnCancel();
}

///////////////////////////////////////////////////////////
//
// OnOK
//
void CConfigDlg::OnOK() 
{
	if (m_listWorld.GetCount() != LB_ERR)
	{
		int index = m_listWorld.GetCurSel() ;
		if (index == LB_ERR) 
		{
			index = 0 ;
		}
		m_clsid = *(reinterpret_cast<CLSID*>(m_listWorld.GetItemDataPtr(index))) ;
	}
	else
	{
		m_clsid = GUID_NULL ;
	}
	
	CDialog::OnOK();
}
