/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File file_map.h
// class CWizFileMapping
//
// 29/05/1995 17:39                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizFileMapping_H
#define __CWizFileMapping_H

#include "w32file.h"
#include "virt_mem.h"


/////////////////////////////////////////////////////////////////////////////
// class CWizFileMapView - class for the memory pointer to
// existing file mapping (see below)
class CWizFileMapView
{
friend class CWizFileMapping;
public:
// Costructor
	// Creates memory view object of existing file mapping
	// For parameters see Win32 help for MapViewOfFile
	CWizFileMapView (
		CWizFileMapping& rMapping,// file mapping
		DWORD  cbSize = 0, 	// Size of View. if zero, entire file is mapping
		DWORD  fdwAccess = FILE_MAP_ALL_ACCESS,
		DWORD  dwOffsetHigh = 0,// high-order 32 bits of file offset 
    		DWORD  dwOffsetLow  = 0 // low-order 32 bits of file offset 	
		);
public:
// Destructor:
	~CWizFileMapView();
// Operations:
	// Flushes memory to a disk
	void Flush (DWORD  cbFlush = 0);
	// Returns a pointer to the memory view
	LPVOID GetPtr() const { return m_Ptr; }
protected:
// Implementation:
// Members:
	LPVOID	m_Ptr;
	CWizFileMapping& m_rMapping;
};
/////////////////////////////////////////////////////////////////////////////
// class CWizFileMapping - class for file mapping of CWin32File class objects
// to receive the memory pointer, use CWizFileMapView from CreateView function
class CWizFileMapping
{
friend class CWizFileMapView;
public:
// Constructors:
	// Constructor creates file mapping for the file
	// If pFile is NULL, creates memory-only mapping (on the paging file)
	// For parameters see Win32 help for CreateFileMapping
	CWizFileMapping(DWORD  dwMaximumSizeLow  = 0,		// low-order 32 bits of object size  
    			DWORD  dwMaximumSizeHigh = 0,		// high-order 32 bits of object size  
    			CWin32File* pFile = NULL,		// file to map 
    			DWORD  fdwProtect = PAGE_READWRITE,	// protection for mapping object 
    			LPCTSTR  lpszMapName = NULL,		// name of file-mapping object 
    			LPSECURITY_ATTRIBUTES  lpsa = NULL	// optional security attributes 
   			);
// Destructor:
	~CWizFileMapping ();
public:
// Static Operations:
	static void ThrowNotSuported();
	static void ThrowMemory();
// Operations:
	// returns handle of the opened file mapping
	operator HANDLE() { return m_H;}
	// test for valid state (opened succesfully)
	BOOL operator !() const { return !Valid(); }
	BOOL Valid() const { return (m_H != NULL);}

	// Creates memory view object of this mapping
	// For parameters see Win32 help for MapViewOfFile
	CWizFileMapView CreateView (
		DWORD  cbSize = 0, 	// Size of View. if zero, entire file is mapping
		DWORD  fdwAccess = FILE_MAP_ALL_ACCESS,
		DWORD  dwOffsetHigh = 0,// high-order 32 bits of file offset 
    		DWORD  dwOffsetLow  = 0 // low-order 32 bits of file offset 	
		)
		{
		return CWizFileMapView (*this, cbSize,fdwAccess,dwOffsetHigh,dwOffsetLow);
		}
	// Creates pointer to memory view object of this mapping
	// For parameters see Win32 help for MapViewOfFile
	CWizFileMapView* AllocateView (
		DWORD  cbSize = 0, 	// Size of View. if zero, entire file is mapping
		DWORD  fdwAccess = FILE_MAP_ALL_ACCESS,
		DWORD  dwOffsetHigh = 0,// high-order 32 bits of file offset 
    		DWORD  dwOffsetLow  = 0 // low-order 32 bits of file offset 	
		)
		{
		return new CWizFileMapView (*this, cbSize,fdwAccess,dwOffsetHigh,dwOffsetLow);
		}
protected:
// Implementation:
	void Close();
// Members:
	HANDLE	m_H;
	CWin32File* 	m_pFile;
};
/////////////////////////////////////////////////////////////////////////////
// Typed views of the file for different purposes:
/////////////////////////////////////////////////////////////////////////////
// Common abstract parent:
template <class TYPE>
class CWizFileView : public CWizFileMapView
{
public:
// Costructor
	CWizFileView (
		CWizFileMapping& rMapping,// file mapping
		DWORD  cbSize = 0, 	// Size of View. if zero, entire file is mapping
		DWORD  fdwAccess = FILE_MAP_ALL_ACCESS,
		DWORD  dwOffsetHigh = 0,// high-order 32 bits of file offset 
    		DWORD  dwOffsetLow  = 0 // low-order 32 bits of file offset 	
		)
	   : CWizFileMapView (rMapping,cbSize,fdwAccess,dwOffsetHigh,dwOffsetLow)
	   	{}
public:
// Operations:
	TYPE* 	GetPtr() const { return (TYPE *)CWizFileMapView::GetPtr(); }
	
	TYPE&   	operator[] (int i) 	 { return GetPtr()[i]; }
	const TYPE& 	operator[] (int i) const { return GetPtr()[i]; }
};
/////////////////////////////////////////////////////////////////////////////
// Template for Read-Only view of the file
// Class creates full size read-only view of the existing file
template <class TYPE>
class CWizROFileView
{
public: 
// Constructor:
	CWizROFileView (LPCTSTR  lpszName,	// File Name
			DWORD  fdwShareMode = 0)// share mode; default - no sharing
		: m_cFile(lpszName, 	// Name 
			GENERIC_READ,	// fdwAccess
			OPEN_EXISTING,	// fdwCreate
			FILE_ATTRIBUTE_READONLY,// fdwAttrsAndFlags
			fdwShareMode,
			NULL, NULL),
		  m_cMapping (0, 0,	// Size of the mapping == size of the file
		  	&m_cFile,
			PAGE_READONLY,	// fdwProtect
			NULL,		// No name for mapping
			NULL),		// No security attributes
		  m_cView (m_cMapping, 
		  	0,		// Size of the file
			FILE_MAP_READ,	// fdwAccess
			0,0)		// From Beginning of the file
				{}
	~CWizROFileView() {}
public:
// Operations:
	const TYPE* 	GetPtr() const { return m_cView.GetPtr(); }
	const TYPE& 	operator[] (int i) const { return m_cView.GetPtr()[i]; }
protected:
// Members:
	// WARNING !!! ASSUMED CONSTRUCTION AND DESTRUCTION ORDER OF
	// MEMBERS CORRESPONDING TO ORDER OF DECLARATION!
	CWin32File		m_cFile;
	CWizFileMapping		m_cMapping;
	CWizFileView<TYPE>	m_cView;
};
/////////////////////////////////////////////////////////////////////////////
// class CWizTempFileStrategy - helper class for defining
// the strategy of growing of CWizFullFileView
class CWizTempFileStrategy
{
public:
	// Strategy components:
	enum
		{
		// default step for growing RAM memory
		DefaultMemoryStep = 0xffff,
		// default Minimal size for creating file on a disk
		// enstead of memory - only 
		DefaultMinFileCreateSize = DefaultMemoryStep*4L,

		// Number of attepts to create disk file
		// in different directories
		MaxTempFileAttempts = 3,
		// Possible orders of creating disk file
		// in different directories : System temporary, Current
		// and program's own directory
		TempOwnCurr = 0,
		TempCurrOwn,
		OwnTempCurr,
		OwnCurrTemp,
		CurrTempOwn,
		CurrOwnTemp,
		};
	// Constructor:
	CWizTempFileStrategy (	// Minimal size for creating file on a disk
				// enstead of memory - only 
				DWORD 	nMinFileCreateSize = DefaultMinFileCreateSize, 
				// step for growing RAM memory
				DWORD	nMemoryStep = DefaultMemoryStep,
				// Order of creating disk file
				// in different directories : System temporary, Current
				// and program's own directory
				int	fNamesOrder = TempOwnCurr,
				// Prefix for creating temp file
				// for.ex: wiz00001.tmp
				LPCTSTR lpszFileNamePrefix = NULL)
		: m_nMinFileCreateSize (nMinFileCreateSize), 
		  m_fNamesOrder (fNamesOrder),
		  m_lpszFileNamePrefix (lpszFileNamePrefix),
		  m_nMemoryStep (nMemoryStep)
		  	{
			if (m_lpszFileNamePrefix == NULL)
				m_lpszFileNamePrefix = ms_lpszDefaultFileNamePrefix;
		  	ASSERT(fNamesOrder >= TempOwnCurr && fNamesOrder <= CurrOwnTemp);
		  	}
// Operations:
	BOOL	IsLastAttempt(int nAttempt) const;
	BOOL	MakeTempFileName (CString& str, int& nAttempt) const;
	DWORD	MinFileSize () const { return m_nMinFileCreateSize;}
	DWORD	MemoryStep  () const { return m_nMemoryStep;}
	BOOL	IsFileSize (DWORD nSize) const { return (nSize > m_nMinFileCreateSize); }
// Members:
protected:
	DWORD	m_nMinFileCreateSize;
	int	m_fNamesOrder;
	LPCTSTR m_lpszFileNamePrefix;
	DWORD	m_nMemoryStep;
public:
	static TCHAR ms_lpszDefaultFileNamePrefix[];
	static TCHAR ms_lpszCurrentDir[];
};
/////////////////////////////////////////////////////////////////////////////
// class CWizFullFileView - class for creating read/write file view
class CWizFullFileView
{
public:
// Constructors:
	// Constructor for working with non-temporary files.
	CWizFullFileView (LPCTSTR  lpszName,	// File Name
			  DWORD  fdwCreate = OPEN_ALWAYS,
			  DWORD  fdwShareMode = 0);// share mode; default - no sharing
	// Constructor for working with temporary files
	CWizFullFileView (DWORD nSize = 0,
			const CWizTempFileStrategy* pStrategy = &DefaultStrategy);
	// destructor
	~CWizFullFileView();
public:
// Operations:
	// get the size of used view
	DWORD	GetSize() const { return m_nSize; }
	// Unsafe pointer (assumed allocated already)
	LPVOID 	GetPtr() 
		{
		ASSERT(m_pPtr != NULL);
		return m_pPtr;
		/*
		if (m_pView != NULL)
			return m_pView->GetPtr(); 
		else
			{
			ASSERT(m_pVirtMem != NULL);
			return m_pVirtMem->GetPtr();
			}
		*/
		}
	// Safe pointer - allocates memory if needed
	LPVOID	TestPtr (DWORD nIndex, DWORD nSize)
		{
		if (m_nSize <= nIndex + nSize)
			SetSize (nIndex + nSize);
		return (((char *)GetPtr()) + nIndex);
		}
	// Set allocated size
	void	SetSize(DWORD nNewSize);
	// Flush memory to disk
	void	Flush();
	// After filling temp file once there are usually
	// frequent readings; in this case you should use
	// SetReadOnly to speed up significantly.
	void	SetReadOnly();
protected:
// Implementation:
	void	MapView();
	void	OpenTempFile (DWORD nSize);
// Members:
	// WARNING !!! ASSUMED CONSTRUCTION AND DESTRUCTION ORDER OF
	// MEMBERS CORRESPONDING TO ORDER OF DECLARATION!
	CWin32FilePtr		m_cFile;
	CWizFileMapping		*m_pMapping;
	CWizFileMapView		*m_pView;
	CWizVirtualMemory	*m_pVirtMem;
	DWORD				m_nSize,
						m_nPhisicalSize;
	CWizTempFileStrategy	m_cTempStrategy;

	LPVOID				m_pPtr;
	BOOL				m_bReadOnly;
protected:
	static CWizTempFileStrategy	DefaultStrategy;
};
/////////////////////////////////////////////////////////////////////////////
// class CWizTypedFullFileView  - template class 
// for creating read/write file view 
// TYPE can be any type  - built-in like int, or struct - 
// which can be read/written binary - i.e. hasn't virtual
// functions or nonbinary parents/data members
template <class TYPE>
class CWizTypedFullFileView : private CWizFullFileView
{
public:
// Constructors:
	// Constructor for working with non-temporary files.
	CWizTypedFullFileView (LPCTSTR  lpszName,
			  DWORD  fdwCreate = OPEN_ALWAYS,
			  DWORD  fdwShareMode = 0)
		: CWizFullFileView (lpszName,fdwCreate,fdwShareMode) 
			{}
	// Constructor for working with temporary files
	CWizTypedFullFileView (DWORD nRecords = 0,
			const CWizTempFileStrategy* pStrategy = &DefaultStrategy)
		: CWizFullFileView (nRecords*sizeof(TYPE),pStrategy) 
			{}
// Destructor	
	~CWizTypedFullFileView() {}
public:
// Operations:
	// Safe pointer to object
	TYPE*	GetPtr(int i = 0) 
		{ return (TYPE *)(CWizFullFileView::TestPtr(i*sizeof(TYPE),sizeof(TYPE))); }
	// Safe pointer to group of object
	TYPE*	Lock (int i, int n = 1)
		{ return (TYPE *)(CWizFullFileView::TestPtr(i*sizeof(TYPE),n*sizeof(TYPE))); }

	DWORD	GetSize() const   { return Div(CWizFullFileView::GetSize(),DWORD(sizeof(TYPE))); }
	TYPE&	operator[](int i) { return *(GetPtr(i)); }
	const TYPE& operator[](int i) const { return *(((CWizTypedFullFileView *)this)->GetPtr(i)); }
	
	void	SetSize(DWORD nRecords)	{ CWizFullFileView::SetSize(nRecords*sizeof (TYPE)); }
	void	Flush()			{ CWizFullFileView::Flush(); }


};
/////////////////////////////////////////////////////////////////////////////
#endif // __CWizFileMapping_H


