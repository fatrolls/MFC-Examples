/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File file_map.cpp
// class CWizFileMapping
//
// 29/05/1995 17:39                             Author: Poul
///////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "sys_data.h"
#include "wsutils.h"

#include "file_map.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

TCHAR CWizTempFileStrategy::ms_lpszDefaultFileNamePrefix[] = _T("wiz");
TCHAR CWizTempFileStrategy::ms_lpszCurrentDir[] 		  = _T(".");
CWizTempFileStrategy	CWizFullFileView::DefaultStrategy;
///////////////////////////////////////////////////////////////////
// class CWizFileMapping

#define new DEBUG_NEW

//*****************************************************************
void CWizFileMapping::ThrowNotSuported()
{
	AfxThrowNotSupportedException();
}
//*****************************************************************
void CWizFileMapping::ThrowMemory()
{
	AfxThrowMemoryException();
}
//*****************************************************************
// Default Constructor
CWizFileMapping::CWizFileMapping (
			DWORD  dwMaximumSizeLow, DWORD dwMaximumSizeHigh,
			CWin32File* pFile, DWORD fdwProtect, 
			LPCTSTR lpszMapName,
    			LPSECURITY_ATTRIBUTES lpsa)
	: m_pFile (pFile)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	if (m_pFile != NULL)
		{
		ASSERT(m_pFile->Valid());
		hFile = *m_pFile;
		ASSERT(hFile != INVALID_HANDLE_VALUE);
		}
	else
		{
		ASSERT(dwMaximumSizeLow > 0 || dwMaximumSizeHigh > 0);
		}
	m_H = ::CreateFileMapping(
    		hFile,			// handle of file to map 
    		lpsa,			// optional security attributes 
    		fdwProtect,		// protection for mapping object 
    		dwMaximumSizeHigh,	// high-order 32 bits of object size  
    		dwMaximumSizeLow,	// low-order 32 bits of object size  
    		lpszMapName 		// name of file-mapping object 
   		);
	if (m_H == NULL)
		CWin32File::ThrowOsError();
}
//*****************************************************************
// Destructor
CWizFileMapping::~CWizFileMapping()
{
	Close();
}
//*****************************************************************
void CWizFileMapping::Close()
{
	if (m_H != NULL)
		{
		::CloseHandle (m_H);
		m_H = NULL;
		}
}

/////////////////////////////////////////////////////////////////////
// class CWizFileMapView
//*****************************************************************
// Constructor
CWizFileMapView::CWizFileMapView (
		CWizFileMapping& rMapping,	// file mapping
		DWORD  cbSize, 			// Size of View. if zero, entire file is mapping
		DWORD  fdwAccess,
		DWORD  dwOffsetHigh,		// high-order 32 bits of file offset 
    		DWORD  dwOffsetLow 		// low-order 32 bits of file offset 	
		)
	: m_rMapping (rMapping)
{
	m_Ptr = ::MapViewOfFile(
		    rMapping.m_H,	// file-mapping object to map into address space  
		    fdwAccess,		// access mode 
		    dwOffsetHigh,	// high-order 32 bits of file offset 
		    dwOffsetLow,	// low-order 32 bits of file offset 
		    cbSize 		// number of bytes to map 
		   );	
	if (m_Ptr == NULL)
		CWizFileMapping::ThrowMemory();
}
//*****************************************************************
// Destructor
CWizFileMapView::~CWizFileMapView ()
{
	VERIFY(::UnmapViewOfFile(m_Ptr));
}
//*****************************************************************
void CWizFileMapView::Flush(DWORD cbFlush)
{
	VERIFY(::FlushViewOfFile(m_Ptr, cbFlush));
}
/////////////////////////////////////////////////////////////////////////////
//*****************************************************************
static void GetTemp (LPTSTR Path)
{
	if (::GetTempPath(CWin32File::MaxPath, Path) == 0)
		CWin32File::ThrowOsError();
}
//*****************************************************************
static void GetOwn (LPTSTR Path)
{
	TCHAR 	Fname [_MAX_FNAME],
			drive [_MAX_DRIVE],
			dir   [_MAX_DIR],
			ext   [_MAX_EXT];

	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL && pApp->m_pszHelpFilePath != NULL &&
		pApp->m_pszHelpFilePath[0] != 0)
		{
		_tsplitpath (pApp->m_pszHelpFilePath, 
					drive, dir, Fname, ext);
		}
	else
		{
		HMODULE h = GetModuleHandle(NULL);
		const int mx = _MAX_PATH*4;
		TCHAR Path[mx]; Path[0] = 0;
		VERIFY(GetModuleFileName(h, Path, mx));
		_tsplitpath (Path, 
					drive, dir, Fname, ext);
		}
	_tmakepath  (Path, drive, dir, NULL,  NULL);
}
//*****************************************************************
static void GetCurr (LPTSTR Path)
{
	_tcscpy(Path,CWizTempFileStrategy::ms_lpszCurrentDir);
}
//*****************************************************************
BOOL CWizTempFileStrategy::IsLastAttempt(int nAttempt) const
{
	return (nAttempt >= MaxTempFileAttempts);
}
//*****************************************************************
BOOL CWizTempFileStrategy::MakeTempFileName (CString& str, int& nAttempt) const
{
	if (IsLastAttempt(nAttempt))
		return FALSE;
	if (nAttempt < 0) nAttempt = 0;
	str = "";
	TCHAR Path [CWin32File::MaxPath];
	switch (nAttempt)
		{
		case 0:
			switch (m_fNamesOrder)
				{
				case TempOwnCurr:
				case TempCurrOwn:
					GetTemp (Path);
					break;
				case OwnTempCurr:
				case OwnCurrTemp:
					GetOwn (Path);
					break;
				case CurrTempOwn:
				case CurrOwnTemp:
					GetCurr (Path);
					break;
				} // switch (m_fNamesOrder)
			break;
		case 1:
			switch (m_fNamesOrder)
				{
				case OwnTempCurr:
				case CurrTempOwn:
					GetTemp (Path);
					break;
				case CurrOwnTemp:
				case TempOwnCurr:
					GetOwn (Path);
					break;
				case OwnCurrTemp:
				case TempCurrOwn:
					GetCurr (Path);
					break;
				}// switch (m_fNamesOrder)
			break;
		case 2:
			switch (m_fNamesOrder)
				{
				case OwnCurrTemp:
				case CurrOwnTemp:
					GetTemp (Path);
					break;
				case CurrTempOwn:
				case TempCurrOwn:
					GetOwn (Path);
					break;
				case TempOwnCurr:
				case OwnTempCurr:
					GetCurr (Path);
					break;
				}// switch (m_fNamesOrder)
			break;
		default: 
			ASSERT(0); 
			return FALSE;
		}; //switch (nAttempt)
	nAttempt++;
	//-------------------------------------------------------------
	TCHAR FullPath [CWin32File::MaxPath];
	if (::GetTempFileName (Path, m_lpszFileNamePrefix, 0, FullPath) == 0)
		CWin32File::ThrowOsError();
	str = FullPath;
	//-------------------------------------------------------------
	return TRUE;
}
//*****************************************************************
/////////////////////////////////////////////////////////////////////////////
// class CWizFullFileView
//*****************************************************************
void	CWizFullFileView::MapView()
{
	DWORD nSize = 0;// Size of the mapping == size of the file
	// If file is empty - Give one page of size;
	// The real size will be adjusted in the destructor
	if (m_nSize == 0)
		nSize = gcSystemData.GetPageSize();

	const DWORD flProtect = (m_bReadOnly) ? PAGE_READONLY : PAGE_READWRITE;
	m_pMapping = new CWizFileMapping(
	  	nSize, 0,	// Size of the mapping == size of the file
	  	m_cFile,
		flProtect,	// fdwProtect
		NULL,		// No name for mapping
		NULL);		// No security attributes
	if (m_pMapping == NULL) 
		CWizFileMapping::ThrowMemory();

	const DWORD dwDesiredAccess = (m_bReadOnly) ? FILE_MAP_READ : FILE_MAP_ALL_ACCESS;
	m_pView = m_pMapping->AllocateView (
	  	0,					// Size of the file
		dwDesiredAccess,	// fdwAccess
		0,0);				// From Beginning of the file
	if (m_pView == NULL) 
		CWizFileMapping::ThrowMemory();
	m_pPtr = m_pView->GetPtr();
	if (m_pPtr == NULL) 
		CWizFileMapping::ThrowMemory();
}
//*****************************************************************
void	CWizFullFileView::Flush()
{
	if (PWin32File(m_cFile) != NULL)
		{
		m_pView->Flush();
		PWin32File(m_cFile)->Flush();
		}
}
//*****************************************************************
// Constructor:
CWizFullFileView::CWizFullFileView (
			  LPCTSTR  lpszName,
			  DWORD  fdwCreate,
			  DWORD  fdwShareMode)
		: m_cFile(lpszName, 			// Name 
			GENERIC_READ | GENERIC_WRITE,	// fdwAccess
			fdwCreate,			// fdwCreate
			FILE_ATTRIBUTE_NORMAL,		// fdwAttrsAndFlags
			fdwShareMode,
			NULL, NULL,
			TRUE),		// To create CWin32File object
		  m_pMapping (NULL),
		  m_pView (NULL),
		  m_nSize (PWin32File(m_cFile)->GetSize()),
		  m_nPhisicalSize (m_nSize),
		  m_pVirtMem (NULL),
		  m_pPtr(NULL),
		  m_bReadOnly(FALSE)
{
	MapView();
}
//*****************************************************************
// Constructor:
CWizFullFileView::CWizFullFileView (DWORD nSize,
		const CWizTempFileStrategy* pStrategy)
		: m_pMapping (NULL),
		  m_pView (NULL),
		  m_nSize (nSize),
		  m_nPhisicalSize (nSize),
		  m_pVirtMem (NULL),
		  m_cTempStrategy (*pStrategy),
		  m_pPtr(NULL),
		  m_bReadOnly(FALSE)
{
	if (m_cTempStrategy.IsFileSize (nSize))
		{
		OpenTempFile (nSize);
		}
	else
		{
		m_pVirtMem = new CWizVirtualMemory (
				m_cTempStrategy.MinFileSize(), 	// Maximum size
				nSize,				// Initial Size
				m_cTempStrategy.MemoryStep());	// Memory Step
		if (m_pVirtMem == NULL)
			CWizFileMapping::ThrowMemory();
		m_nSize = nSize;
		m_pPtr = m_pVirtMem->GetPtr();
		if (m_pPtr == NULL) 
			CWizFileMapping::ThrowMemory();
		}
}
//*****************************************************************
CWizFullFileView::~CWizFullFileView()
{
	delete m_pVirtMem;
	if (PWin32File(m_cFile) != NULL)
		{
		ASSERT(m_pView != NULL);
		if(!m_bReadOnly)
			m_pView->Flush();

		delete m_pView;
		delete m_pMapping;
		if (m_nSize != m_nPhisicalSize)
			PWin32File(m_cFile)->SetSize (m_nSize);
		}
	else
		{
		ASSERT(m_pView == NULL);
		ASSERT(m_pMapping == NULL);
		delete m_pView;
		delete m_pMapping;
		}
}
//*****************************************************************
void	CWizFullFileView::SetSize(DWORD nNewSize)
{
	if (nNewSize == m_nSize)
		return;
	if (PWin32File(m_cFile) != NULL)
		{
		if (nNewSize < m_nPhisicalSize)
			{
			m_nSize = nNewSize;
			return;
			}
		delete m_pView; m_pView = NULL;
		delete m_pMapping; m_pMapping = NULL;
		m_nSize = nNewSize;
		m_nPhisicalSize = RoundUp (m_nSize, gcSystemData.GetPageSize());
		PWin32File(m_cFile)->SetSize(m_nPhisicalSize);
		MapView();
		}
	else
		{
		ASSERT(m_pVirtMem != NULL);
		if (m_nSize < nNewSize)
			{
			if (m_cTempStrategy.IsFileSize (nNewSize))
				{
				DWORD nOldSize = m_nSize;
				OpenTempFile (nNewSize);
				ASSERT(m_pView != NULL);
				memcpy (m_pView->GetPtr(),m_pVirtMem->GetPtr(),nOldSize);
				delete m_pVirtMem;
				m_pVirtMem = NULL;
				}
			else
				{
				m_pVirtMem->SetSize (m_nSize = nNewSize);
				m_pPtr = m_pVirtMem->GetPtr();
				if (m_pPtr == NULL) 
					CWizFileMapping::ThrowMemory();
				}
			}
		else
			m_nSize = nNewSize;
		}
}
//*****************************************************************
void	CWizFullFileView::OpenTempFile (DWORD nSize)
{
	ASSERT(m_pView == NULL);
	ASSERT(m_pMapping == NULL);
	ASSERT(PWin32File(m_cFile) == NULL);
	CString Name;
	int nAttempt = 0;
	while (PWin32File(m_cFile) == NULL &&
		m_cTempStrategy.MakeTempFileName (Name,nAttempt))
		{
		try
			{
			m_cFile.Open (Name,			// name of the file 
			      GENERIC_READ | GENERIC_WRITE,	// access (read-write) mode 
			      //CREATE_NEW,			// how to create 
			      TRUNCATE_EXISTING,
			      FILE_ATTRIBUTE_TEMPORARY |
			      FILE_FLAG_SEQUENTIAL_SCAN |
			      FILE_FLAG_DELETE_ON_CLOSE
			      );
			PWin32File(m_cFile)->SetSize (nSize);
			}
		catch (CFileException*)
			{
			m_cFile.Close();
			if (m_cTempStrategy.IsLastAttempt (nAttempt))
				throw;
			}
		} // while
	m_nSize = m_nPhisicalSize = nSize;
	MapView();
}
//*****************************************************************
void	CWizFullFileView::SetReadOnly()
{
	if (m_bReadOnly)
		return;

	m_bReadOnly = TRUE;
	if (PWin32File(m_cFile) != NULL)
		{
		m_pView->Flush();
		delete m_pView; 
		delete m_pMapping; 
		m_pMapping = NULL;
		m_pView = NULL;
		MapView();
		}
}
//*****************************************************************
