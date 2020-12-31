// MyWindow.h: interface for the CMyWindow class.
//
//////////////////////////////////////////////////////////////////////
// Written by Mario Zucca 
//        mailto:mario@GenoaValley.org
//        http://www.GenoaValley.org
//
// Copyright (c) 2000.
//
// The code contained in this file is based on the original
// Grid control written by Chris Maunder,
//        mailto:chris@codeproject.com
//        http://www.codeproject.com

#if !defined(AFX_MYWINDOW_H__A7A02CC0_5701_11D3_B21E_006097FEBF00__INCLUDED_)
#define AFX_MYWINDOW_H__A7A02CC0_5701_11D3_B21E_006097FEBF00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////
// Prova di un nuovo edit control
/////////////////////////////////////////////
//#include "NewgridT1.h"

#include "atlcontrols.h"
#include "GridCell.h"
class CMyWindow : 
	public CWindowImpl<CMyWindow,ATLControls::CEdit  >
{
public:
	void StopEdit();
	void SetCell(CGridCell* cell,
					 int row,
					 int col);

   // Optionally specify name of the new Windows class
   DECLARE_WND_CLASS("MyEdit") 
              // If this macro is not specified in your
              // class, ATL will generate a class name
   BEGIN_MSG_MAP(CMyWindow)
//      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
      MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
   END_MSG_MAP()

   LRESULT OnPaint(UINT nMsg, WPARAM wParam, 
                   LPARAM lParam, BOOL& bHandled)
   {
	   return paint(nMsg, wParam,lParam, bHandled);
   }
   LRESULT OnKillFocus(UINT nMsg, WPARAM wParam, 
                   LPARAM lParam, BOOL& bHandled)
   {
		// Stop the current in place operation
		BSTR buf=::SysAllocString(OLESTR(""));
		GetWindowText(buf);
		if(m_Cell)
			m_Cell->put_Text(buf); // .. and then notify to cell

		//DestroyWindow();
		::PostMessage(m_Cell->GetHWNDGrid(),
			WM_USER,
			m_nRow,
			m_nCol);

		::SysFreeString(buf);
		return DefWindowProc();
   }
   virtual LRESULT paint(UINT nMsg, WPARAM wParam, 
                   LPARAM lParam, BOOL& bHandled)
   {
      // Do some painting code
      return DefWindowProc();
   }
	CMyWindow();
	virtual ~CMyWindow();
	int m_nCol;
	int m_nRow;

protected:
	CGridCell* m_Cell;
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if(wParam == VK_RETURN)
		{
		::PostMessage(m_Cell->GetHWNDGrid(),
			WM_USER,
			m_nRow,
			m_nCol);

			return 0;
		}

		return DefWindowProc(uMsg,wParam,lParam);
	}
};

#endif // !defined(AFX_MYWINDOW_H__A7A02CC0_5701_11D3_B21E_006097FEBF00__INCLUDED_)
