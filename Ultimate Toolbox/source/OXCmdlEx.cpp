// ==========================================================================
// 						Class Implementation : COXCommandLineException
// ==========================================================================

// Source file : oxcmdlex.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "oxcmdlex.h"	// class specification
#include "oxcmdopt.h"

#ifdef WIN32
	#include "wincon.h"		// for AllocConsole call	
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( COXCommandLineException, CException );

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:
COXCommandLineException::COXCommandLineException(LPCTSTR pszcError,
												 COXCommandOptions* pCmdOpt /* = NULL */)
	{
	if (pCmdOpt != NULL)
		{
		ASSERT(pCmdOpt->IsKindOf(RUNTIME_CLASS(COXCommandOptions)));
		m_sErrMsg = pCmdOpt->Usage(pszcError);
		}
	else
		m_sErrMsg = pszcError;
	}

BOOL COXCommandLineException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError,
											  UINT* /* pnHelpContext */ /* = NULL */)
	{
	ASSERT(lpszError != NULL && AfxIsValidString(lpszError, nMaxError));

	lstrcpyn(lpszError, m_sErrMsg, nMaxError);

	return TRUE;
	}

BOOL COXCommandLineException::WriteToStdErr()
	{            
#ifdef WIN32	
	DWORD written;
	HANDLE StdErr = GetStdHandle(STD_ERROR_HANDLE);
	if (StdErr == INVALID_HANDLE_VALUE)
		{
		if (AllocConsole())
			StdErr = GetStdHandle(STD_ERROR_HANDLE);
		else
			return FALSE;
		}

	if (StdErr != INVALID_HANDLE_VALUE)
		{
		WriteFile(StdErr, m_sErrMsg, m_sErrMsg.GetLength(), &written, 0);
		return TRUE;
		}

	return FALSE;
#else
	fprintf(stderr, m_sErrMsg);      
    return TRUE;  
#endif	
	}

// protected:

// private:

// ==========================================================================
