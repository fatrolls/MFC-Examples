// ==========================================================================
// 							Class Specification : COXVersionInfo
// ==========================================================================

// Header file : OXVerinfo.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class can be used to retrieve the version information
//	 from a file 5EXE, DLL, etc)

// Remark:
//		***

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////
#ifndef __VERINFO_H__
#define __VERINFO_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXVersionInfo : public CObject
{
DECLARE_DYNAMIC(COXVersionInfo)

// Data members -------------------------------------------------------------
public:
    DWORD m_dwSignature;
    DWORD m_dwStrucVersion;
    DWORD m_dwFileVersionMS;
    DWORD m_dwFileVersionLS;
    DWORD m_dwProductVersionMS;
    DWORD m_dwProductVersionLS;
    DWORD m_dwFileFlagsMask;
    DWORD m_dwFileFlags;
    DWORD m_dwFileOS;
    DWORD m_dwFileType;
    DWORD m_dwFileSubtype;
    DWORD m_dwFileDateMS;
    DWORD m_dwFileDateLS;
    
    DWORD m_dwLanguageCountryID;
    CString m_sLanguageCountry;

	CString m_sComments;
	CString m_sCompanyName;
	CString m_sFileDescription;
	CString m_sFileVersion;
	CString m_sInternalName;
	CString m_sLegalCopyright;
	CString m_sLegalTrademarks;
	CString m_sOriginalFilename;
	CString m_sPrivateBuild;
	CString m_sProductName;
	CString m_sProductVersion;
	CString m_sSpecialBuild;
	
protected:
	BOOL m_bValid;

	static const DWORD 	m_dwFixedFileInfoSignature;
	static const DWORD  m_dwAmericanEnglishTranslation;
	static LPCTSTR		m_pszTranslation;
	static LPCTSTR		m_pszFileInfo;
	
private:
	
// Member functions ---------------------------------------------------------
public:
	COXVersionInfo();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	BOOL ReadInfo(LPCTSTR pszPathName);
	// --- In  : pszPathName : The full path of the file of which the version info is requested
	// --- Out : 
	// --- Returns : Whether version info was found
	// --- Effect : Extracts the version info for the file
	
	BOOL ContainsValidInfo();
	// --- In  :
	// --- Out : 
	// --- Returns : Whether this version info contains valid info
	// --- Effect : 

	CString GetOSName();
	// --- In  :
	// --- Out : 
	// --- Returns : A text specifying the Operating System
	// --- Effect : 

	void Empty();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Clears the object
		
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual ~COXVersionInfo();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:      

private:
                   
// Message handlers ---------------------------------------------------------

};

#endif
// ==========================================================================
