// PathComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "PathList.h"
#include "PathComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathComboBox

CPathComboBox::CPathComboBox()
{
	m_bFirstCall = TRUE;
	m_nIndexStart = -1;
	m_nIndexEnd = -1;
}

CPathComboBox::~CPathComboBox()
{
}

BEGIN_MESSAGE_MAP(CPathComboBox, CComboBoxEx)
	//{{AFX_MSG_MAP(CPathComboBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathComboBox message handlers

BOOL CPathComboBox::SetPath(LPCTSTR pszPath)
{
	if (m_bFirstCall) {
		m_bFirstCall = FALSE;

		//
		// Add an image list containing drive and folder images.
		//
		m_il.Create (IDB_IMAGES, 16, 1, RGB (255, 0, 255));
		SetImageList (&m_il);

		//
		// Add icons representing the drives on the host system.
		//
		int nPos = 0;
		int nCount = 0;
		CString string = _T ("?:\\");

		DWORD dwDriveList = ::GetLogicalDrives ();

		while (dwDriveList) {
			if (dwDriveList & 1) {
				string.SetAt (0, _T ('A') + nPos);
				CString strDrive = string.Left (2);
				UINT nType = ::GetDriveType (string);

				int nImage = 0;
				switch (nType) {

				case DRIVE_FIXED:
					nImage = 0;
					break;

				case DRIVE_REMOVABLE:
					nImage = 1;
					break;

				case DRIVE_CDROM:
					nImage = 2;
					break;

				case DRIVE_REMOTE:
					nImage = 3;
					break;
				}

				COMBOBOXEXITEM cbei;
				cbei.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE;
				cbei.iItem = nCount++;
				cbei.pszText = (LPTSTR) (LPCTSTR) strDrive;
				cbei.iImage = nImage;
				cbei.iSelectedImage = nImage;
				InsertItem (&cbei);
			}
			dwDriveList >>= 1;
			nPos++;
		}
	}

	//
	// Find the item that corresponds to the drive specifier in pszPath.
	//
	CString strPath = pszPath;
	CString strDrive = strPath.Left (2);

	int nDriveIndex = FindStringExact (-1, strDrive);
	if (nDriveIndex == CB_ERR)
		return FALSE;

	//
	// Delete previously added folder items (if any).
	//
	if (m_nIndexStart != -1 && m_nIndexEnd != -1) {
		ASSERT (m_nIndexEnd >= m_nIndexStart);
		int nCount = m_nIndexEnd - m_nIndexStart + 1;
		for (int i=0; i<nCount; i++)
			DeleteItem (m_nIndexStart);
		if (m_nIndexStart < nDriveIndex)
			nDriveIndex -= nCount;
		m_nIndexStart = -1;
		m_nIndexEnd = -1;
	}

	//
	// Add items representing the directories in pszPath.
	//
	int nCount = 0;
	int nStringIndex = strPath.Find (_T ('\\'), 0);

	if (nStringIndex++ != -1) {
		CString strItem;
		GetSubstring (nStringIndex, strPath, strItem);

		while (!strItem.IsEmpty ()) {
			COMBOBOXEXITEM cbei;
			cbei.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE |
				CBEIF_INDENT;
			cbei.iItem = nDriveIndex + ++nCount;
			cbei.pszText = (LPTSTR) (LPCTSTR) strItem;
			cbei.iImage = 4;
			cbei.iSelectedImage = 5;
			cbei.iIndent = nCount;
			InsertItem (&cbei);

			GetSubstring (nStringIndex, strPath, strItem);
		}
	}

	//
	// Record the indexes of the items that were added, too.
	//
	if (nCount) {
		m_nIndexStart = nDriveIndex + 1;
		m_nIndexEnd = nDriveIndex + nCount;
	}

	//
	// Finish up by selecting the final item.
	//
	int nResult = SetCurSel (nDriveIndex + nCount);
	return TRUE;
}

void CPathComboBox::GetSubstring(int& nStart, CString &string,
	CString &result)
{
	result = _T ("");
	int nLen = string.GetLength ();
	if (nStart >= nLen)
		return;

	int nEnd = string.Find (_T ('\\'), nStart);
	if (nEnd == -1) {
		result = string.Right (nLen - nStart);
		nStart = nLen;
	}
	else {
		result = string.Mid (nStart, nEnd - nStart);
		nStart = nEnd + 1;
	}
}

CString CPathComboBox::GetPath()
{
	//
	// Get the index of the selected item.
	//
	CString strResult;
	int nEnd = GetCurSel ();
	int nStart = nEnd + 1;

	//
	// Find the index of the "root" item.
	//
	COMBOBOXEXITEM cbei;
	do {
		cbei.mask = CBEIF_INDENT;
		cbei.iItem = --nStart;
		GetItem (&cbei);
	} while (cbei.iIndent != 0);

	//
	// Build a path name by combining all the items from the root item to
	// the selected item.
	//
	for (int i=nStart; i<=nEnd; i++) {
		TCHAR szItem[MAX_PATH];
		COMBOBOXEXITEM cbei;
		cbei.mask = CBEIF_TEXT;
		cbei.iItem = i;
		cbei.pszText = szItem;
		cbei.cchTextMax = sizeof (szItem) / sizeof (TCHAR);
		GetItem (&cbei);
		strResult += szItem;
		strResult += _T ("\\");
	}

	//
	// Strip the trailing backslash.
	//
	int nLen = strResult.GetLength ();
	strResult = strResult.Left (nLen - 1);
	return strResult;
}
