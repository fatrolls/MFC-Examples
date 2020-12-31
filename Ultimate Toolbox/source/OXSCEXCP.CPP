#include "stdafx.h"
#include "OXSCEXCP.H"
#include "OXRSERCM.H"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

#ifdef _DEBUG
// character strings to use for dumping COXSerialCommException

static const LPCTSTR rgszCOXSerialCommExceptionCause[] =
	{
	_T("none"),
		_T("notAvailable"),
		_T("breakDetect"),
		_T("rxTimeout"),
		_T("ctsTimeout"),
		_T("dsrTimeout"),
		_T("cdTimeout"),
		_T("frameError"),
		_T("parityError"),
		_T("overrunError"),
		_T("rxQueueOverflow"),
		_T("txQueueFull"),
		_T("wmQuitReceived"),
		_T("ioError"),
		_T("modeError")
	};
static const TCHAR szUnknown[] = _T("unknown");
#endif

COXSerialCommException::COXSerialCommException(int cause /*= none*/, LPCTSTR lpszSerialCommName /* = NULL */) :
CFileException(CFileException::generic, -1, lpszSerialCommName),
m_ext_cause(cause)
	{
	}

COXSerialCommException::COXSerialCommException(COXSerialCommException& other) :
	CFileException(other.m_cause, -1, m_strFileName),
	m_ext_cause(other.m_ext_cause)
	{
	}
	
COXSerialCommException& COXSerialCommException::operator = (const COXSerialCommException& other)
	{
	m_cause = other.m_cause;
	m_ext_cause = other.m_ext_cause;
	m_lOsError = other.m_lOsError;
	m_strFileName = other.m_strFileName;
	return *this;
	}
	
	
BOOL COXSerialCommException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError,
	PUINT pnHelpContext)
	{
	ASSERT(lpszError != NULL && AfxIsValidString(lpszError, nMaxError));
	
	if (pnHelpContext != NULL)
		*pnHelpContext = m_ext_cause + IDS_SERIAL_NONE;
	
	// we can use CString here; archive errors aren't caused
	// by being out of memory.
	
	CString sMessage;
	CString sSerialCommName = m_strFileName;
	if (sSerialCommName.IsEmpty())
		sSerialCommName.LoadString(IDS_SERIAL_NONAME);
	AfxFormatString1(sMessage,
		m_ext_cause + IDS_SERIAL_NONE, sSerialCommName);
	lstrcpyn(lpszError, sMessage, nMaxError);
	
	return TRUE;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////
	// CArchiveException
	
#ifdef _DEBUG
void COXSerialCommException::Dump(CDumpContext& dc) const
	{
	CFileException::Dump(dc);
	
	dc << _T(" m_ext_cause = ");
	if (m_ext_cause >= 0 && m_ext_cause < (sizeof(rgszCOXSerialCommExceptionCause)/sizeof(LPCTSTR)))
		dc << rgszCOXSerialCommExceptionCause[m_ext_cause];
	else
		dc << szUnknown;
	
	dc << _T("\n");
	}
#endif //_DEBUG
	
void AFXAPI AfxThrowSerialCommException(int cause,
	LPCTSTR lpszSerialCommName /* = NULL */)
	{
#ifdef _DEBUG
	LPCTSTR lpsz;
	if (cause >= 0 && cause < (sizeof(rgszCOXSerialCommExceptionCause)/sizeof(LPCTSTR)))
		lpsz = rgszCOXSerialCommExceptionCause[cause];
	else
		lpsz = szUnknown;
	TRACE1("COXSerialComm exception: %hs.\n", lpsz);
		
#endif //_DEBUG
		
	THROW(new COXSerialCommException(cause, lpszSerialCommName));
	}
	
IMPLEMENT_DYNAMIC(COXSerialCommException, CException)
		
/////////////////////////////////////////////////////////////////////////////


