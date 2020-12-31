//=================================================================
//  class: CIMAP4License
//  File:  IMAP4License.cpp
//
//  IMAP4 ActiveX control license support
//
//=================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//=================================================================

#include "stdafx.h"
#include "stdio.h"
#include "IMAP4License.h"
#include "AboutDlg.h"

#define		MAX_KEY_LENGTH		100

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***************************************************
CIMAP4License
    Constructor
Params
    none
Return
	none
****************************************************/
CIMAP4License::CIMAP4License() 
{
}

/***************************************************
~CIMAP4License
    Destructor
Params
    none
Return
	none
****************************************************/
CIMAP4License::~CIMAP4License()
{

}

/***************************************************
VerifyLicenseKey
    Test the run-time license key. In evaluation mode
	displays an about box and returns TRUE 
Params
    bstr	- run-time license key to test
Return
	TRUE	- if key is Ok
	FALSE	- if not
****************************************************/
BOOL CIMAP4License::VerifyLicenseKey(BSTR bstr)   
{
	USES_CONVERSION;

#ifndef EVALUATION_MODE
	return !lstrcmp(OLE2T(bstr), _T(RUNTIME_LICENSE_KEY));  
#else
	CAboutDlg	dlg; 
	dlg.DoModal();
	return TRUE;
#endif
}

/***************************************************
GetLicenseKey
    Returns the run-time license key. In evaluation mode
	no run-time license returned.
Params
	dwReserved	- reserved
    bstr		- pointer to the license key string
Return
	TRUE		- success
****************************************************/
BOOL CIMAP4License::GetLicenseKey(DWORD dwReserved, BSTR* pBstr) 
{  
	USES_CONVERSION;

#ifndef EVALUATION_MODE
    *pBstr = SysAllocString( T2OLE(_T(RUNTIME_LICENSE_KEY))); 
#else
	*pBstr = SysAllocString( T2OLE(_T("Evaluation mode. No run-time license."))); 
#endif

    return TRUE;   
} 

/***************************************************
IsLicenseValid
    Check the design time license key.
	In evaluation mode always return TRUE;
Params
	none
Return
	TRUE	- if key is Ok
	FALSE	- if not
****************************************************/
BOOL CIMAP4License::IsLicenseValid() 
{
	USES_CONVERSION;

#ifndef EVALUATION_MODE

	static	BOOL	m_bLicenseChecked = FALSE;
	static	BOOL	m_bLicense = FALSE;

	CComBSTR	bstrKey;

	// Check the key only once
	if( ! m_bLicenseChecked ) {					

		// Create License file name 
	   char		szLicenseFile[MAX_PATH + 1];
	   GetSystemDirectory( szLicenseFile, MAX_PATH );
	   strcat(szLicenseFile, _T("\\data.lic"));

		// Open the file for reading
		FILE	*hFile = fopen( szLicenseFile, _T("rb") );
			
		if(hFile != NULL ) {
			char	szData[MAX_KEY_LENGTH + 1];

			// Read data from file
			int nBytesRead = fread(szData, sizeof(char), MAX_KEY_LENGTH, hFile);
			if( nBytesRead > 0 ) {
				szData[nBytesRead] = 0;

				// Return key
				if(strstr(szData, FULL_LICENSE_KEY) != NULL)
					m_bLicense = TRUE;
				}
		
			// Close the file 
			fclose(hFile);
			}

		m_bLicenseChecked = TRUE;
		}

	// Show error message if license not found
	if( ! m_bLicense ) {
		CAboutDlg	dlg("Can't create IMAP4 Control! License key is missing."); 
		dlg.DoModal();
		}

	return m_bLicense;

#else

	return TRUE;

#endif

}

#pragma warning (pop)