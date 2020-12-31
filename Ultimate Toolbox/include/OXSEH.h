// ==========================================================================
// 							Class Specification : COXSEHException
// ==========================================================================

// Header File : OXSEH.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CException

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class is a C++ wrapper around Structured Exception Handling.
//  SEH-exceptions that are thrown can now be catched using the
//    C++ try - catch statements or by the MFC TRY - CATCH macros

// Remark:
//	Call the function EnableSEHTrapping() to enable this exception wrapper
//  All SEH exceptions are from that point onwwards translated to a 
//   COXSEHException* exception.
//  The original exception code can be retrieved by calling the member function
//   GetCause()

// Example

// 	COXSEHException::EnableSEHTrapping();
// 	TRY
// 		{
//		int x = 1;
//		x = x / 0;
//		}
//	CATCH(COXSEHException, px)
//		{
//		if (pe->GetCause() == EXCEPTION_INT_DIVIDE_BY_ZERO)
//			::AfxMessageBox(_T("Integer divide by zero trapped with TRY, CATCH"));
//		}
//	END_CATCH

// 	COXSEHException::EnableSEHTrapping();
// 	try
// 		{
//		int x = 1;
//		x = x / 0;
//		}
//	catch(COXSEHException* px)
//		{
//		if (pe->GetCause() == EXCEPTION_INT_DIVIDE_BY_ZERO)
//			::AfxMessageBox(_T("Integer divide by zero trapped with try, catch"));
//		px->Delete();
//		}

//	Note that all settings are organized on a per-thread base. So functions such as
//	 EnableSEHTrapping() will enable trapping in the current thread.
//	If you are building a multi-threaded application and you want to trap all
//	 exceptions, you should call EnableSEHTrapping() from within every thread

// Prerequisites (necessary conditions):
//	This wrapper works only in WIN32 because WIN16 does not support SEH

/////////////////////////////////////////////////////////////////////////////
#ifndef __SEHEXCPT_H__
#define __SEHEXCPT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include <eh.h>		// For _set_se_translator

// If you do not want to trap Floating Point exceptions, define OXSEH_USE_FP as 0
#ifndef OXSEH_USE_FP 
#define OXSEH_USE_FP 1
#endif //OXSEH_USE_FP 

#if (0 < OXSEH_USE_FP)
#include <float.h>
#endif // (0 < OXSEH_USE_FP)


class OX_CLASS_DECL COXSEHException : public CException
{
DECLARE_DYNAMIC(COXSEHException)

// Data members -------------------------------------------------------------
public:
	
protected:
	_EXCEPTION_POINTERS* m_pEP;

	typedef void (__cdecl *_se_translator_function)( unsigned int, _EXCEPTION_POINTERS*);
	class OX_CLASS_DECL COXSEHState : public CNoTrackObject
		{
		public:
		BOOL m_bSEHTrapping;
		BOOL m_bFPTrapping;
		unsigned int m_nPreviousFPControl;
		unsigned int m_nFPControlMask;
		_se_translator_function m_pfPreviousTranslator;

		COXSEHState()
			:
			m_bSEHTrapping(FALSE),
			m_bFPTrapping(FALSE),
			m_nPreviousFPControl(0),
#if (0 < OXSEH_USE_FP)
			m_nFPControlMask(_EM_ZERODIVIDE | _EM_INVALID | _EM_DENORMAL | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_INEXACT),
#else
			m_nFPControlMask(0),
#endif // (0 < OXSEH_USE_FP)
			m_pfPreviousTranslator(0)
			{
			}

		};
	static CThreadLocal<COXSEHState> m_pSEHState;

private:
	
// Member functions ---------------------------------------------------------
public:
	static void EnableSEHTrapping(BOOL bTrapFP = FALSE);
	// --- In  : bTrapFP : Whether floating point exceptions should be trapped as well
	// --- Out : 
	// --- Returns :
	// --- Effect : Start the mapping of SEH to C++ exceptions;

	static void DisableSEHTrapping();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Stops the mapping of SEH to C++ exceptions;
	//				EnableSEHTrapping() must have been called previously

	static BOOL IsSEHTrappingEnabled();
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether the mapping of SEH to C++ exceptions is enabled
	// --- Effect : 

	static BOOL IsSEHFPTrappingEnabled();
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether FP exception will be trapped
	// --- Effect : 

	COXSEHException(_EXCEPTION_POINTERS* pEP = NULL);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
	
	UINT GetCause();
	// --- In  :
	// --- Out : 
	// --- Returns : The cause why the exception was thrown.
	//				 It is the code used by SEH (e.g. EXCEPTION_ACCESS_VIOLATION)
	//				 See <winbase.h> for possible codes
	// --- Effect : 

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG


	virtual ~COXSEHException();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object
	
protected:      
	static void __cdecl MapSEHToCPPExceptions(UINT uCode, _EXCEPTION_POINTERS* pep);

private:
                   
// Message handlers ---------------------------------------------------------

};

class OX_CLASS_DECL COXSEHMemoryException : public COXSEHException
{
DECLARE_DYNAMIC(COXSEHMemoryException)
// Data members -------------------------------------------------------------
// Member functions ---------------------------------------------------------
public:
	COXSEHMemoryException(_EXCEPTION_POINTERS* pEP = NULL);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	BOOL IsInfoAvailable();
	// --- In  :
	// --- Out : 
	// --- Returns : Whether extra information is available 
	//               (Read/Write flag and virtual memory address)
	// --- Effect : 

	BOOL GetReadWriteFlag();
	// --- In  :
	// --- Out : 
	// --- Returns : Whether the exception occurred when trying to read (FALSE)
	//               or to write (TRUE) to a virtual memory address
	// --- Effect : Be sure that IsInfoAvailable() == TRUE

	DWORD GetAddress();
	// --- In  :
	// --- Out : 
	// --- Returns : Get the virtual memory address that resulted in an exception
	// --- Effect : 
	// --- Effect : Be sure that IsInfoAvailable() == TRUE

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

		virtual ~COXSEHMemoryException();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object
};

class OX_CLASS_DECL COXSEHMathException : public COXSEHException
{
DECLARE_DYNAMIC(COXSEHMathException)
// Data members -------------------------------------------------------------
// Member functions ---------------------------------------------------------
public:
	COXSEHMathException(_EXCEPTION_POINTERS* pEP = NULL);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

		virtual ~COXSEHMathException();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object
};

class OX_CLASS_DECL COXSEHSpecialException : public COXSEHException
{
DECLARE_DYNAMIC(COXSEHSpecialException)
// Data members -------------------------------------------------------------
// Member functions ---------------------------------------------------------
public:
	COXSEHSpecialException(_EXCEPTION_POINTERS* pEP = NULL);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

		virtual ~COXSEHSpecialException();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object
};

#endif
// ==========================================================================
