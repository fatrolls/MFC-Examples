/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File FileMapWindow.h
// class CWizFileMapWindow
//
// 08/09/1996 14:00                             Author: Poul, Hadas & Oren
///////////////////////////////////////////////////////////////////

#ifndef __CWizFileMapWindow_H
#define __CWizFileMapWindow_H

#include <file_map.h>
#include <critsect.h>
#include <safe_ptr.h>
#include <sys_data.h>

/////////////////////////////////////////////////////////////////////////////
class CWizFileMapNoLocker
{
public:
	CWizFileMapNoLocker() {}
	~CWizFileMapNoLocker() {}

	void Lock() {}
	void UnLock() {}
};

/////////////////////////////////////////////////////////////////////////////
class CWizFileMapCritSectLocker : protected CWizCriticalSection
{
public:
	CWizFileMapCritSectLocker() 
		: CWizCriticalSection (TRUE) // Initialized at constructor
			{}
	~CWizFileMapCritSectLocker() {}

	void Lock()		{ Begin(); }
	void UnLock()	{ End();   }
};

#pragma warning(disable : 4270)
  
/////////////////////////////////////////////////////////////////////////////
// class CWizFileMapWindow
template<class LOCKER>
class CWizFileROFileMapping
{
public:
// Constructors:
	CWizFileROFileMapping (LPCTSTR  lpszName,	// File Name
			DWORD  fdwShareMode = 0,			// share mode; default - no sharing
			LPCTSTR  lpszMappingName = NULL,	// Name for mapping (to share between processes)
			LPSECURITY_ATTRIBUTES lpsa = NULL)	// address of security descriptor 
			: m_cFile(lpszName, 	// Name 
				GENERIC_READ,	// fdwAccess
				OPEN_EXISTING,	// fdwCreate
				FILE_ATTRIBUTE_READONLY,// fdwAttrsAndFlags
				fdwShareMode,
				lpsa, NULL),
			  m_cMapping (0, 0,	// Size of the mapping == size of the file
		  		&m_cFile,
				PAGE_READONLY,	// fdwProtect
				lpszMappingName,// Name for mapping
				lpsa)			// Security attributes
					{
					m_nSize = m_cFile.GetSize();
					}
// Destructor:
	~CWizFileROFileMapping () {}
public:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Nested classes:
public:
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class Window : protected CWizPtr<CWizFileMapView>
	{
	typedef CWizPtr<CWizFileMapView> PARENT;
	public:
		// Constructor:
		Window(
			CWizFileMapping& rMap,	// file mapping
			DWORD  cbSize, 			// Size of View. if zero, entire file is mapping
			DWORD  dwOffset,		// file offset 
			DWORD  dwMaxSize
			)
			: PARENT(NULL),
			  m_rMap   (rMap),
			  m_nSize  (cbSize),
			  m_nOffset(dwOffset),
			  m_nMaxSize(dwMaxSize)
				{
				RecreateView(cbSize, dwOffset);
				}

		// Copy constructor
		Window(Window& T)
			: PARENT(T.m_ptr),
			  m_rMap   (T.m_rMap),
			  m_nSize  (T.m_nSize),
			  m_nOffset(T.m_nOffset),
			  m_nMaxSize(T.m_nMaxSize)
			{
			T.m_ptr = NULL;
			}

		const void*	GetPtr(DWORD size, DWORD offset)
			{
			if (offset < m_nOffset ||  
				(offset + size) > (m_nOffset + m_nSize))
				RecreateView(size, offset);
			const char* const p = (char *)(m_ptr->GetPtr());
			return (p + offset - m_nOffset);
			}
	protected:
		void RecreateView(DWORD size, DWORD offset)
			{
			if (size + offset > m_nMaxSize)
				{
				ASSERT(0);
				AfxThrowMemoryException();
				}

			delete m_ptr;
			m_ptr = NULL;
			m_ptr = new CWizFileMapView (m_rMap, size, FILE_MAP_READ, 0, offset);
			m_nSize = size;
			m_nOffset = offset;
			ThrowMemoryExceptionIfNull((PARENT&)(*this));
			}

		CWizFileMapping& m_rMap;
		DWORD	m_nSize, m_nOffset,m_nMaxSize; 
	};
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
// Operations:
	Window Get(DWORD size, DWORD offset)
		{
		LOCAL_LOCK lock(m_cAccessLocker);
		return Window (m_cMapping, size, offset, m_nSize);
		}
	DWORD GetSize() { return m_nSize; }
protected:
// Local classes
	class LOCAL_LOCK
		{
		public:
			LOCAL_LOCK(LOCKER	&rLocker)
				:m_rAccessLocker(rLocker)
				{ 
				m_rAccessLocker.Lock();
				}
			~LOCAL_LOCK()
				{ 
				m_rAccessLocker.UnLock();
				}
		LOCKER	&m_rAccessLocker;
		};
protected:
// Members:
	CWin32File			m_cFile;
	CWizFileMapping		m_cMapping;
	LOCKER				m_cAccessLocker;
	DWORD				m_nSize;
// Implementation:
};

/////////////////////////////////////////////////////////////////////////////
// class CWizFileMapWindow
template<class LOCKER, class DATA>
class CWizTypedFileROFileMapping : public CWizFileROFileMapping<LOCKER>
{
typedef CWizFileROFileMapping<LOCKER> PARENT;
public:
// Constructors:
	CWizTypedFileROFileMapping (LPCTSTR  lpszName,	// File Name
			DWORD  fdwShareMode = 0,			// share mode; default - no sharing
			LPCTSTR  lpszMappingName = NULL,	// Name for mapping (to share between processes)
			LPSECURITY_ATTRIBUTES lpsa = NULL)	// address of security descriptor 
			: PARENT(lpszName, fdwShareMode, lpszMappingName, lpsa)
				{
				m_nDefaultWindowSize = gcSystemData.GetPageSize()/sizeof(DATA);
				if (m_nDefaultWindowSize > GetSize())
					m_nDefaultWindowSize = GetSize();
				if (m_nDefaultWindowSize <= 0)
					m_nDefaultWindowSize = 1;
				}
// Nested classes:
public:
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	typedef PARENT::Window ParentWindow;
	class Wnd : protected PARENT::Window
	{
	typedef ParentWindow PAPA;
	public:
		Wnd(
			CWizFileMapping& rMap,	// file mapping
			DWORD  dwOffset,		// file offset 
			DWORD  dwMaxSize,
			DWORD  dwWindowSize)
				: PAPA(rMap, sizeof(DATA), 
								dwOffset*sizeof(DATA), dwMaxSize),
				  m_nWindowSize (dwWindowSize*sizeof(DATA))
				{}
		Wnd(Wnd& T)
			: PAPA(T) ,
			  m_nWindowSize (T.m_nWindowSize)
			{}

		const DATA* GetPtr(int i)
			{
			const DWORD newOffset = i*sizeof(DATA);
			DWORD size = m_nWindowSize;;
			if (newOffset + m_nWindowSize > m_nMaxSize)
				{
				size = (m_nMaxSize - newOffset)/sizeof(DATA);
				if (size < 1) size = 1;
				size *= sizeof(DATA);
				}
			return (const DATA*)PAPA::GetPtr(size, newOffset);
			}
		const DATA& operator[] (int i) 
			{
			return *GetPtr(i);
			}
	protected:
		const DWORD m_nWindowSize;
	};

public:
// Operations:
	Wnd Get(DWORD offset, DWORD windowsize = -1)
		{
		LOCAL_LOCK lock(m_cAccessLocker);
		if (windowsize <= 0)
			windowsize = m_nDefaultWindowSize;
		return Wnd (m_cMapping, offset, m_nSize, windowsize);
		}
	DWORD GetSize() { return PARENT::GetSize()/sizeof(DATA); }
protected:
	DWORD	m_nDefaultWindowSize;
};
/////////////////////////////////////////////////////////////////////////////
#endif // __CWizFileMapWindow_H


