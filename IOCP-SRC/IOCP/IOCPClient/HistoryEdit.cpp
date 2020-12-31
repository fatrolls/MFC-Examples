/*
 *  HistoryEdit.cpp
 *
 *  Description:
 *    CHistoryEdit implementation
 *
 *    A CEdit subclass that allows you to display a text history
 *    of events.
 *
 *  Author:
 *    Ravi Bhavnani (ravib@datablast.net)
 *
 *  Revision History:
 *    15 Mar 1998   rab   Original version
 */

#include "stdafx.h"
#include "HistoryEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistoryEdit

CHistoryEdit::CHistoryEdit()
{
  m_bSelectable = FALSE;
}

CHistoryEdit::~CHistoryEdit()
{
}

BEGIN_MESSAGE_MAP(CHistoryEdit, CEdit)
	//{{AFX_MSG_MAP(CHistoryEdit)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryEdit operations

void CHistoryEdit::AppendString(CString str)
//
//  Purpose:
//    Appends a text string to the history buffer.
//
//  Returns:
//    None.
//
{
CString   strBuffer;    // current contents of edit control

  // Append string
  GetWindowText (strBuffer);
  if (!strBuffer.IsEmpty())
     strBuffer += "\r\n";
  strBuffer += str;
  SetWindowText (strBuffer);

  // Scroll the edit control
  LineScroll (GetLineCount(), 0);
}

/////////////////////////////////////////////////////////////////////////////
// CHistoryEdit message handlers

void CHistoryEdit::OnSetFocus(CWnd* pOldWnd) 
{
  // Don't allow user to select text
  if (m_bSelectable)
     CEdit::OnSetFocus (pOldWnd);
  else
     pOldWnd->SetFocus();
}

// End EditHistroy.cpp