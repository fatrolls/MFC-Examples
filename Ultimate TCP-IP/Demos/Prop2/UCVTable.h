// UCVTable.h: interface for the CUCVTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCVTABLE_H__50B6BF63_19E1_11D3_B57C_0080C83F712F__INCLUDED_)
#define AFX_UCVTABLE_H__50B6BF63_19E1_11D3_B57C_0080C83F712F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "UCWnd.h"
class CUCWnd;
struct ListWnd{
	CUCWnd *WndClass;
	ListWnd *Next;
};

class CUCVTable  
{
public:
	CUCWnd * FindClass(HWND wnd);
	int AddItem(CUCWnd* wnd);
	CUCVTable();
	int DeleteClass(CUCWnd *cwnd);
	virtual ~CUCVTable();

private:
	ListWnd *m_SWnd;
};

#endif // !defined(AFX_UCVTABLE_H__50B6BF63_19E1_11D3_B57C_0080C83F712F__INCLUDED_)
