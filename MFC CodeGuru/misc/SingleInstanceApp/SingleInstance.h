// SingleInstance.h : header file for the CSingleInstance class
//

#ifndef __SINGLEINSTANCE_H__
#define __SINGLEINSTANCE_H__

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CSingleInstance
// See SingleInstance.cpp for the implementation of this class
//

class CSingleInstance
{
public:
	CSingleInstance();
	~CSingleInstance();

	BOOL	Create( UINT nID );
	CString	GetClassName( void ) const;

protected:
	HANDLE	m_hMutex;
	CString	m_strClassName;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __SINGLEINSTANCE_H__
