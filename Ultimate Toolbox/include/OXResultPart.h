// ==========================================================================
// 					Class Specification : COXResultPart
// ==========================================================================

// Header file : OXResultPart.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	YES	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class encapsulates a single result code and its message

//	An object can be constructed from an HRESULT value.
//	Now the accompanying message will be retrieved from the message resource
//	When optional parameters are needed they can be supplied

//	A group of these object can be stored in a COXResultObj

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXRESULTPART_H__
#define __OXRESULTPART_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#ifndef __AFXOLE_H__
#include <AfxOle.h>
#define __AFXOLE_H__
#endif


class OX_CLASS_DECL COXResultPart : public CObject
{
DECLARE_SERIAL(COXResultPart);

// Data members -------------------------------------------------------------
public:
protected:
	COleDateTime	m_creationTime;
	HRESULT			m_resultCode;
	CString			m_sResultMessage;
	DWORD			m_dwExtra;

	static DWORD	m_dwLangID;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXResultPart();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs an empty result item object

	COXResultPart(HRESULT resultCode, ...);
	COXResultPart(LPCTSTR pszModuleName, HRESULT resultCode, ...);
	// --- In  : (optional) pszModuleName : Name of the module containing the message resource
	//			  resultCode : Result code to use
	//            ... : Optional parameters used to build the message
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs a result item object with the specified
	//              resultcode
	//				The appropriate message is retrieved from resource
	//			    and for this the optional parameters may be used

	COXResultPart(const COXResultPart& resultItem);
	// --- In  : resultItem : Object to copy
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy constructor

	BOOL Initialize();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Initializes to an empty result item object

	BOOL Initialize(HRESULT resultCode, ...);
	BOOL Initialize(LPCTSTR pszModuleName, HRESULT resultCode, ...);
	BOOL InitializeSpecial(LPCTSTR pszModuleName, DWORD resultCode, ...);
	// --- In  : (optional) pszModuleName : Name of the module containing the message resource
	//			  resultCode : Result code to use
	//            ... : Optional parameters used to build the message
	// --- Out : 
	// --- Returns : Whether the message could be retrieved successfully
	// --- Effect : Initializes a result item object with the specified
	//              resultcode
	//				The appropriate message is retrieved from resource
	//			    and for this the optional parameters may be used

	HRESULT GetResultCode() const;
	// --- In  :
	// --- Out : 
	// --- Returns : The result code of this object
	// --- Effect : 

	void SetResultCode(HRESULT resultCode);
	// --- In  : resultCode : New result code to set
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets the result code to a new value
	//				Other parts (message etc) are not automatically updated

	CString GetResultMessage() const;
	// --- In  :
	// --- Out : 
	// --- Returns : The result message of this object
	// --- Effect : 

	void SetResultMessage(CString sResultMessage);
	// --- In  : sResultMessage : New result message to set
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets the result code to a new value
	//				Other parts (code etc) are not automatically updated

	void AppendMessage(CString sMessage);
	// --- In  : sMessage : Message to append
	// --- Out : 
	// --- Returns : 
	// --- Effect : Appends the specified text to the result message

	CString BuildExtendedMessage() const;
	// --- In  :
	// --- Out : 
	// --- Returns : The extended result message of this object
	// --- Effect : 

	COleDateTime GetTimeStamp() const;
	// --- In  :
	// --- Out : 
	// --- Returns : The time stamp when the item was created
	// --- Effect : 

	void SetTimeStamp(COleDateTime creationTime);
	// --- In  : creationTime : New creation time to set
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets the creation date to a new value
	//				Other parts (code etc) are not automatically updated
	//				The date must be valid

	DWORD GetExtraData() const;
	// --- In  :
	// --- Out : 
	// --- Returns : The extra data of this object
	// --- Effect : 

	void SetExtraData(DWORD dwExtra);
	// --- In  : dwExtra : New extra data  to set
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets the extra data to a new value
	//				Other parts (code etc) are not automatically updated

	COXResultPart& operator=(const COXResultPart& resultItem);
	// --- In  : resultItem : Object to assigne
	// --- Out : 
	// --- Returns : This object 
	// --- Effect : Assignment operator

	BOOL Succeeded() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether the result code specifies success (SUCCEEDED)
	// --- Effect : 

	BOOL Failed() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether the result code specifies failure (FAILED)
	// --- Effect : 

	WORD GetCode() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The code part of the result code (HRESULT_CODE)
	// --- Effect : 

	WORD GetFacility() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The facility part of the result code (HRESULT_FACILITY)
	// --- Effect : 

	WORD GetSeverity() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The severity part of the result code (HRESULT_SEVERITY)
	// --- Effect : 

	WORD GetSeverityEx() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The extended severity part of the result code (bits 31 and 30)
	// --- Effect : 

	virtual void Serialize(CArchive& ar);
	// --- In  : ar : Archive used in serialization
	// --- Out : 
	// --- Returns :
	// --- Effect : Serializes the object

#ifdef _DEBUG
	virtual void AssertValid() const;
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : AssertValid performs a validity check on this object 
	//				by checking its internal state. 
	//				In the Debug version of the library, AssertValid may assert and 
	//				thus terminate the program.
	
	virtual void Dump(CDumpContext& dc) const;
	// --- In  : dc : The diagnostic dump context for dumping, usually afxDump.
	// --- Out : 
	// --- Returns :
	// --- Effect : Dumps the contents of the object to a CDumpContext object. 
	//				It provides diagnostic services for yourself and 
	//				 other users of your class. 
#endif

	virtual ~COXResultPart();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

protected:
	BOOL InitializeEx(HRESULT resultCode, va_list* pArgs);
	BOOL InitializeEx(LPCTSTR pszModuleName, HRESULT resultCode, va_list* pArgs);
	BOOL InitializeExSpecial(LPCTSTR pszModuleName, DWORD dwResultCode, va_list* pArgs);
	static BOOL RetrieveResultMessage(CString sModuleName, HRESULT resultCode, 
		va_list* pArgs, CString& sResultMessage);
	static BOOL RetrieveSpecialMessage(CString sModuleName, DWORD dwResultCode, 
		va_list* pArgs, CString& sResultMessage);

private:
                   
};

// Define some handy macros
#include "OXResultPartDef.h"

#endif // __OXRESULTPART_H__
// ==========================================================================
