// ==========================================================================
// 							Class Implementation : COXSEHException
// ==========================================================================

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXSEH.h"

#if (0 < OXSEH_USE_FP)
#include <float.h>
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXSEHException, CException)
IMPLEMENT_DYNAMIC(COXSEHMemoryException, COXSEHException)
IMPLEMENT_DYNAMIC(COXSEHMathException, COXSEHException)
IMPLEMENT_DYNAMIC(COXSEHSpecialException, COXSEHException)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
CThreadLocal<COXSEHException::COXSEHState> COXSEHException::m_pSEHState;

// Data members -------------------------------------------------------------
// protected:
	// 	_EXCEPTION_POINTERS* m_pEP;
	// --- The information about the SEH (See the Win32 API GetExceptionCode())

	// class COXSEHState 
	// --- Helper class to organize data per thread

		// BOOL m_bSEHTrapping;
		// --- Whether SEH translation is enabled

		// BOOL m_bFPTrapping;
		// --- Whether FP exceptions are enabled

		// int m_nPreviousFPControl;
		// --- The state of the FPU control word before the FP exceptions were enabled (otherwise 0)
		// int m_nFPControlMask;
		// --- The new state of the FPU control word when the FP exceptions are enabled

		// _se_translator_function m_pfPreviousTranslator;
		// --- The translator that was installed before this one

	// static CThreadLocal<COXSEHState> m_pSEHState;
	// --- The access pointer-object (like smart-pointer) to the different objects.
	//     The object associated with the current thread will be used.
// private:
	
// Member functions ---------------------------------------------------------
// public:
void COXSEHException::EnableSEHTrapping(BOOL bTrapFP /* = FALSE */)
	{
	// Should not invoke this function twice without an intermediate call to 
	// DisableSEHTrapping() !
	// Thes states are organized on a per-thread base
	ASSERT(!m_pSEHState->m_bSEHTrapping);
	ASSERT(!m_pSEHState->m_bFPTrapping);

#if (0 < OXSEH_USE_FP)
	if (bTrapFP)
		{
		//	To trap floating point exceptions under WIN32, we must use _controlfp().
		int cw = ::_controlfp(0,0);
		m_pSEHState->m_nPreviousFPControl = cw;
		cw &= ~m_pSEHState->m_nFPControlMask;
		::_controlfp(cw, _MCW_EM);		
		m_pSEHState->m_bFPTrapping = TRUE;
		}
#else
	// For this class to use FP exceptions, define OXSEH_USE_FP as 1
	ASSERT(!bTrapFP);
#endif // OXSEH_USE_FP

	//  To use C++ Exception handling (try, catch) for structured exceptions,
	//  install a function to redirect them to C++ catch handlers.
	m_pSEHState->m_pfPreviousTranslator = _set_se_translator(MapSEHToCPPExceptions);
	m_pSEHState->m_bSEHTrapping = TRUE;
	}

void COXSEHException::DisableSEHTrapping()
	{
	// Should not invoke this finction without a previos call to EnsableSEHTrapping() !
	ASSERT(m_pSEHState->m_bSEHTrapping);

#if (0 < OXSEH_USE_FP)
	if (m_pSEHState->m_bFPTrapping)
		{
		// Reset to the previous trapping state
		_clearfp();
		::_controlfp(m_pSEHState->m_nPreviousFPControl, (unsigned int)~0);		
		m_pSEHState->m_bFPTrapping = FALSE;
		}
#endif // OXSEH_USE_FP
	
	// Re-install the previous C++ exception translator
	// The return code must be our mapping function !
	VERIFY(MapSEHToCPPExceptions == _set_se_translator (m_pSEHState->m_pfPreviousTranslator));
	m_pSEHState->m_bSEHTrapping = FALSE;
	}

BOOL COXSEHException::IsSEHTrappingEnabled()
	{
	return m_pSEHState->m_bSEHTrapping;
	}

BOOL COXSEHException::IsSEHFPTrappingEnabled()
	{
	return m_pSEHState->m_bFPTrapping;
	}

COXSEHException::COXSEHException(EXCEPTION_POINTERS* pEP /* = NULL */)
	:
	m_pEP(pEP)
	{                  
	}
	
UINT COXSEHException::GetCause()
	{
	if (m_pEP != NULL)
		return m_pEP->ExceptionRecord->ExceptionCode;
	else
		{
		TRACE0("COXSEHException::GetCause : Exception pointers not available, returning 0\n");
		return 0;
		}
	}

#ifdef _DEBUG
void COXSEHException::Dump(CDumpContext& dc) const
	{
	CException::Dump(dc);
	dc << _T("\nm_pEP : ") << (void*)m_pEP;
	if (m_pEP != NULL)
		dc << _T("\n\t with cause : ") << m_pEP->ExceptionRecord->ExceptionCode;
	}

void COXSEHException::AssertValid() const
	{
	CException::AssertValid();
	}
#endif

COXSEHException::~COXSEHException()
	{
	}

// COXSEHMemoryException -----------------------------------------------------
COXSEHMemoryException::COXSEHMemoryException(EXCEPTION_POINTERS* pEP /* = NULL */)
	:
	COXSEHException(pEP)
	{                  
	}
	
BOOL COXSEHMemoryException::IsInfoAvailable()
	{
	return (m_pEP != NULL) && (2 <= m_pEP->ExceptionRecord->NumberParameters);
	}

BOOL COXSEHMemoryException::GetReadWriteFlag()
	{
	if (IsInfoAvailable())
		return m_pEP->ExceptionRecord->ExceptionInformation[0];
	else
		{
		TRACE0("COXSEHException::GetReadWriteFlag : Exception information available, returning FALSE\n");
		return FALSE;
		}
	}

DWORD COXSEHMemoryException::GetAddress()
	{
	if (IsInfoAvailable())
		return m_pEP->ExceptionRecord->ExceptionInformation[1];
	else
		{
		TRACE0("COXSEHException::GetAddress : Exception information available, returning FALSE\n");
		return FALSE;
		}
	}

#ifdef _DEBUG
void COXSEHMemoryException::Dump(CDumpContext& dc) const
	{
	COXSEHException::Dump(dc);
	if ((m_pEP != NULL) && (2 <= m_pEP->ExceptionRecord->NumberParameters))
		{
		dc << _T("\n\t with Read/Write flag : ") << m_pEP->ExceptionRecord->ExceptionInformation[0];
		dc << _T("\n\t for memory adress : ") << m_pEP->ExceptionRecord->ExceptionInformation[1];
		}
	}

void COXSEHMemoryException::AssertValid() const
	{
	COXSEHException::AssertValid();
	}
#endif

COXSEHMemoryException::~COXSEHMemoryException()
	{
	}

// COXSEHMathException -----------------------------------------------------
COXSEHMathException::COXSEHMathException(EXCEPTION_POINTERS* pEP /* = NULL */)
	:
	COXSEHException(pEP)
	{                  
	}
	
#ifdef _DEBUG
void COXSEHMathException::Dump(CDumpContext& dc) const
	{
	COXSEHException::Dump(dc);
	}

void COXSEHMathException::AssertValid() const
	{
	COXSEHException::AssertValid();
	}
#endif

COXSEHMathException::~COXSEHMathException()
	{
	}

// COXSEHSpecialException -----------------------------------------------------
COXSEHSpecialException::COXSEHSpecialException(EXCEPTION_POINTERS* pEP /* = NULL */)
	:
	COXSEHException(pEP)
	{                  
	}
	
#ifdef _DEBUG
void COXSEHSpecialException::Dump(CDumpContext& dc) const
	{
	COXSEHException::Dump(dc);
	}

void COXSEHSpecialException::AssertValid() const
	{
	COXSEHException::AssertValid();
	}
#endif

COXSEHSpecialException::~COXSEHSpecialException()
	{
	}

// protected:
void __cdecl COXSEHException::MapSEHToCPPExceptions(UINT uCode, EXCEPTION_POINTERS* pEP)
	// --- In  : uCode : See the Win32 API GetExceptionCode()
	//			 pEP : See the Win32 API GetExceptionInformation()
	// --- Out : 
	// --- Returns :
	// --- Effect : This function is called when a SEH is thrown
	//				It converts it to a C++ exception
	{
	if ( (uCode == EXCEPTION_ACCESS_VIOLATION) ||
	     (uCode == EXCEPTION_DATATYPE_MISALIGNMENT) ||
	     (uCode == EXCEPTION_ARRAY_BOUNDS_EXCEEDED) ||
	     (uCode == EXCEPTION_STACK_OVERFLOW) ||
	     (uCode == EXCEPTION_INVALID_DISPOSITION) ||
	     (uCode == EXCEPTION_IN_PAGE_ERROR) ||
	     (uCode == EXCEPTION_GUARD_PAGE) )
		{
		TRACE1("COXSEHException::MapSEHToCPPExceptions : Translating to COXSEHMemoryException : 0x%lx\n", uCode);
		THROW(new COXSEHMemoryException(pEP));
		}
	else if ( (uCode == EXCEPTION_FLT_DENORMAL_OPERAND) ||
	     (uCode == EXCEPTION_FLT_DIVIDE_BY_ZERO) ||
	     (uCode == EXCEPTION_FLT_INEXACT_RESULT) ||
	     (uCode == EXCEPTION_FLT_INVALID_OPERATION) ||
	     (uCode == EXCEPTION_FLT_OVERFLOW) ||
	     (uCode == EXCEPTION_FLT_STACK_CHECK) ||
	     (uCode == EXCEPTION_FLT_UNDERFLOW) ||
	     (uCode == EXCEPTION_FLT_STACK_CHECK) ||
	     (uCode == EXCEPTION_INT_DIVIDE_BY_ZERO) ||
	     (uCode == EXCEPTION_INT_OVERFLOW) )
		{
		TRACE1("COXSEHException::MapSEHToCPPExceptions : Translating to COXSEHMathException : 0x%lx\n", uCode);

#if (0 < OXSEH_USE_FP)
		ASSERT(m_pSEHState->m_bFPTrapping);
		// Make sure the exception flags in the floating-point status word is cleared
		// The return value (the FP status word) is ignored, because it identifies the
		// type of exception, but we already know that (through uCode)
		_clearfp();

		// Empty the FPU stack
		// One way to do this by calling pop directly, but then we
		// have to know how many elements are on the stack
			// double dummy;
			// _asm
			//	{
			//	fstp dummy;
			//	}

		// Another solution is to reset the FPU,
		// but then we have to re-enable the exception trapping
		int cw = ::_controlfp(0,0);
		_fpreset();
		::_controlfp(cw, _MCW_EM);		
#endif // OXSEH_USE_FP

		THROW(new COXSEHMathException(pEP));
		}
	else if ( (uCode == EXCEPTION_BREAKPOINT) ||
	     (uCode == EXCEPTION_SINGLE_STEP) ||
	     (uCode == EXCEPTION_PRIV_INSTRUCTION) ||
	     (uCode == EXCEPTION_ILLEGAL_INSTRUCTION) ||
	     (uCode == EXCEPTION_NONCONTINUABLE_EXCEPTION) )
		{
		TRACE1("COXSEHException::MapSEHToCPPExceptions : Translating to COXSEHSpecialException : 0x%lx\n", uCode);
		THROW(new COXSEHSpecialException(pEP));
		}
	else
		{
		TRACE1("COXSEHException::MapSEHToCPPExceptions : Translating to COXSEHException : 0x%lx\n", uCode);
		THROW(new COXSEHException(pEP));
		}
	}


// private:

// Message handlers ---------------------------------------------------------

// ==========================================================================
