#ifndef AFX_RISSSPLASH_H__5FCAC224_E486_11D1_9646_204C4F4F5020__INCLUDED_
#define AFX_RISSSPLASH_H__5FCAC224_E486_11D1_9646_204C4F4F5020__INCLUDED_

// 
// Copyright and author: 
// M.Loibl: mloibl@moss.de
// 
// You may handle this code to others only when you do not delete these
// copyright-lines.
// These source files may not be copied except by permission of the author.
// These source files may not be included in source or compiled form as any
// part of a commercial distribution except by permission of the
// author. 
// These files may be used freely for internal corporate use.
// These files may also may be used freely by students for 
// educational purposes.
// No warranty or guarrantee of fitness can be made to these files.
//
// 

#include "SplashThread.h"

class CSplashThreadDemo : public CSplashThread
{
public:
	CSplashThreadDemo();
	virtual ~CSplashThreadDemo();

	virtual void	DrawPost(CDC *pDC);


	//{{AFX_VIRTUAL(CSplashThreadDemo)
	//}}AFX_VIRTUAL

protected:
	virtual void	OnTimerInternal();
	void			SetHeaderSize(void);
	int				InitInstance();
	DWORD			m_StartOfStaticText,
					m_postTimerWaits;

	int				m_posHeaderMin_X;
	CSize			m_sizeHeader;
	CBitmap			m_bmp1,
					m_bmp2;
	CSize			m_BmpSize;
	CPoint			m_BmpStart;

	//{{AFX_MSG(CSplashThreadDemo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_RISSSPLASH_H__5FCAC224_E486_11D1_9646_204C4F4F5020__INCLUDED_
