#include "stdafx.h"

#ifndef __CHECKFRM_H__
#define __CHECKFRM_H__

/*
	This code is public domain - but if you modufy the code in any way, 
	and redistribute it, please make a comment, so I won't be blamed.
	
	Chrisitan Skovdal Andersen 20/2-1998 - csa@jubii.dk
*/

BOOL IsRectContainedInRect(CRect &rcChild, CRect &rcMother);

class CCheckFrame : public CObject
{
public:
	virtual void Enable(BOOL bEnable);
	void Set(CWnd *pParentWnd,UINT nFrmCtl);

	CWnd* m_pFrame; 
	CWnd* m_pDialog;
	CRect m_rFrm;
	CDWordArray m_adwWndHandles;


protected:
};

#endif