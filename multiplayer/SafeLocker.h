// SafeLocker.h: interface for the CSafeLocker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAFELOCKER_H__6D80BFD3_7683_4FFC_A822_2732257EBDD3__INCLUDED_)
#define AFX_SAFELOCKER_H__6D80BFD3_7683_4FFC_A822_2732257EBDD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSafeLocker  
{
public:
	CSafeLocker();
	virtual ~CSafeLocker();

    void Lock(void);
    void UnLock(void);
    BOOL CanLock(void);
private:
	HANDLE      m_hMutex;
};

#endif // !defined(AFX_SAFELOCKER_H__6D80BFD3_7683_4FFC_A822_2732257EBDD3__INCLUDED_)
