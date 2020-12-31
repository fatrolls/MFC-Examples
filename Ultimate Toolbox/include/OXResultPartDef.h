// ==========================================================================
// 					Macro Definition for COXResultPart
// ==========================================================================

// Header file : OXResultPartDef.h

// //////////////////////////////////////////////////////////////////////////

// These macros only have an actual implementation if _DEBUG is defined
// otherwise they all are defined empty

#ifndef __OXRESULTPARTDEF_H__
#define __OXRESULTPARTDEF_H__

#ifdef _DEBUG
	// OX_TRACE_ERROR_EX(RES, TX)
	// --- In  : RES : The numeric result code (long)
	//			 TX : A string which will be used as prefix
	// --- Out : 
	// --- Returns :
	// --- Effect : Traces the messages associated with sepcified result code
	//				together with leading text
#define OX_TRACE_ERROR_EX(RES, TX)									\
	{																\
	HRESULT r = (RES);												\
	if (HRESULT_FACILITY(r) == 0)									\
	     r = HRESULT_FROM_WIN32(r);									\
	if (FAILED(r))													\
		{															\
		COXResultPart resultPart(r);								\
		TRACE(_T("%s : HRESULT = 0x%X\n\t%s"), (TX), r, resultPart.GetResultMessage()); \
		}															\
	}

	// OX_TRACE_ERROR_EX(RES)
	// --- In  : RES : The numeric result code (long)
	// --- Out : 
	// --- Returns :
	// --- Effect : Traces the messages associated with sepcified result code
	//				together with the current file name and line number
#define OX_TRACE_ERROR(RES)											\
	{																\
	CString sLine;													\
	sLine.Format(_T("%i"), __LINE__);								\
	OX_TRACE_ERROR_EX(RES, CString(__FILE__) + _T(" (") + sLine + _T(")")); \
	}

	// OX_TRACE_LAST_ERROR_EX(TX)
	// --- In  : TX : A string which will be used as prefix
	// --- Out : 
	// --- Returns :
	// --- Effect : Traces the message associated with the last error
	//				together with leading text
#define OX_TRACE_LAST_ERROR_EX(TX)									\
	{																\
	HRESULT nLastError = ::GetLastError();							\
	OX_TRACE_ERROR_EX(HRESULT_FROM_WIN32(nLastError), TX);			\
	}

	// OX_TRACE_LAST_ERROR()
	// --- In  : TX : A string which will be used as prefix
	// --- Out : 
	// --- Returns :
	// --- Effect : Traces the message associated with the last error
	//				together with the current file name and line number
#define OX_TRACE_LAST_ERROR()										\
	{																\
	HRESULT nLastError = ::GetLastError();							\
	CString sLine;													\
	sLine.Format(_T("%i"), __LINE__);								\
	OX_TRACE_ERROR_EX(HRESULT_FROM_WIN32(nLastError), CString(__FILE__) + _T(" (") + sLine + _T(")")); \
	}

#else
#define OX_TRACE_ERROR_EX(RES, TX)
#define OX_TRACE_ERROR(RES)
#define OX_TRACE_LAST_ERROR_EX(TX)
#define OX_TRACE_LAST_ERROR()
#endif
#endif // __OXRESULTPARTDEF_H__
// ==========================================================================
