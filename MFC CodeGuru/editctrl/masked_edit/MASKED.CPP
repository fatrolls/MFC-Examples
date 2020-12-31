// MaskEd.cpp : implementation file
//

#include "stdafx.h"
#include "myproj.h"
#include "MaskEd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COleDateTime read /write

COleDateTime ReadCOleDateTime(LPCSTR lpszData)
{
  COleDateTime DateTime;
  DateTime.ParseDateTime(lpszData);
  return DateTime;
}

void FormatCOleDateTime(CString& strData, COleDateTime DateTime, int len)
{
  strData = "";
  if (DateTime.m_dt == 0) return;
  if (len == 8)
    strData = DateTime.Format("%d/%m/%y");
  else if(len == 5) // added these two
	strData = DateTime.Format("%H:%M");
  else
    strData = DateTime.Format("%d/%m/%Y");
}

/////////////////////////////////////////////////////////////////////////////
// DDX for mask control

void AFXAPI DDX_OleDate(CDataExchange* pDX, int nIDC, CDateEdit& rControl, COleDateTime& Date)
{
  DDX_Control(pDX, nIDC, (CWnd&)rControl);
  if (!pDX->m_bSaveAndValidate)
    rControl.SetDate(Date);
  else
    Date = rControl.GetDate();
}
  
/////////////////////////////////////////////////////////////////////////////
// CMaskEdit class

IMPLEMENT_DYNAMIC(CMaskEdit, CEdit)

BEGIN_MESSAGE_MAP(CMaskEdit, CEdit)
  //{{AFX_MSG_MAP(CMaskEdit)
  ON_WM_CHAR()
  ON_WM_KEYDOWN()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMaskEdit::CMaskEdit()
{
  m_bUseMask = FALSE;
  m_strMask = _T("");
  m_strLiteral = _T("");
  m_strValid = _T("");
  m_bMaskKeyInProgress = FALSE;
}

void CMaskEdit::SetMask(LPCSTR lpMask, LPCSTR lpLiteral, LPCSTR lpValid)
{
  m_bUseMask = FALSE;
  if (lpMask == NULL) return;
  m_strMask = lpMask;
  if (m_strMask.IsEmpty()) return;
  if (lpLiteral != NULL)
  {
    m_strLiteral = lpLiteral;
    if (m_strLiteral.GetLength() != m_strMask.GetLength())
      m_strLiteral.Empty();
  }
  else
    m_strLiteral.Empty();
  if (lpValid != NULL)
    m_strValid = lpValid;
  else
    m_strValid.Empty();
  m_bUseMask = TRUE;
}

void CMaskEdit::SendChar(UINT nChar)
{
  m_bMaskKeyInProgress = TRUE;
  #ifdef WIN32
    AfxCallWndProc(this, m_hWnd, WM_CHAR, nChar, 1);
  #else
    SendMessage(WM_CHAR, nChar, 1);
  #endif
  m_bMaskKeyInProgress = FALSE;
}

void CMaskEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  if (!m_bMaskKeyInProgress)
    if (!CheckChar(nChar)) return;

  if (m_bUseMask)
  {
    if (isprint(nChar))
    {
      // si un masque existe, on est en insert mode
      int startPos, endPos;
      GetSel(startPos, endPos);
      SetSel(startPos, endPos+1);
      Clear();
	  m_str.SetAt(endPos, nChar); // added this
    }
    else if (nChar == VK_BACK) return;
  }
  CEdit::OnChar(nChar, nRepCnt, nFlags);

  if (!m_bMaskKeyInProgress && m_bUseMask && !m_strLiteral.IsEmpty())
  {
    int startPos, endPos;
    GetSel(startPos, endPos);
    // make sure the string is not longer than the mask
    if (endPos < m_strLiteral.GetLength())
    {
      UINT c = m_strLiteral.GetAt(endPos);
      if (c != '_') SendChar(c);
    }
  }
}

BOOL CMaskEdit::CheckChar(UINT nChar)
{
  UINT c;

  // do not use mask
  if (!m_bUseMask) return TRUE;

  // control character, OK
  if (!isprint(nChar)) return TRUE;
	
  // unselect all selections, if any
  int startPos, endPos;
  GetSel(startPos, endPos);
  SetSel(-1, 0);
  SetSel(startPos, startPos);

  // check the key against the mask
  GetSel(startPos, endPos);

  // make sure the string is not longer than the mask
  if (endPos >= m_strMask.GetLength())
  {
    MessageBeep((UINT)-1);
    return FALSE;
  }

  // check to see if a literal is in this position
  c = '_';
  if (!m_strLiteral.IsEmpty())
    c = m_strLiteral.GetAt(endPos);

  if (c != '_')
  {
    SendChar(c);
    GetSel(startPos, endPos);
  }

  // check the valid string character
  if (m_strValid.Find(nChar) != -1) return TRUE;

  // check the key against the mask
  c = m_strMask.GetAt(endPos);
  BOOL doit = TRUE;
  switch (c)
  {
    case '0':		// digit only //completely changed this
    {
		BOOL doit = TRUE;
		if(isdigit(nChar))
		{
			if(m_isdate)
			{
				if(endPos == 0)
				{
					if(nChar > '3')
						doit = FALSE;
				}
				if(endPos == 1)
				{
					if(m_str.GetAt(0) == '3')
					{
						if(nChar > '1')
							doit = FALSE;
					}
				}
				if(endPos == 3)
				{
					if(nChar > '1')
						doit = FALSE;
				}
				if(endPos == 4)
				{
					if(m_str.GetAt(3) == '1')
					{
						if(nChar > '2')
							doit = FALSE;
					}
				}
			}
			else
			{
				if(endPos == 0)
				{
					if(nChar > '2')
						doit = FALSE;
				}
				if(endPos == 1)
				{
					if(m_str.GetAt(0) == '2')
					{
						if(nChar > '3')
							doit = FALSE;
					}
				}
				if(endPos == 3)
				{
					if(nChar > '5')
						doit = FALSE;
				}
			}
	        return doit;
		}
      break;
    }
    case '9':		// digit or space
    {
      if (isdigit(nChar)) return TRUE;
      if (nChar != VK_SPACE) return TRUE;
      break;
    }
    case '#':		// digit or space or '+' or '-'
    {
      if (isdigit(nChar)) return TRUE;
      if (nChar == VK_SPACE || nChar == VK_ADD || nChar == VK_SUBTRACT) return TRUE;
      break;
    }
    case 'L':		// alpha only
    {
      if (isalpha(nChar)) return TRUE;
      break;
    }
    case '?':		// alpha or space
    {
      if (isalpha(nChar)) return TRUE;
      if (nChar == VK_SPACE) return TRUE;
      break;
    }
    case 'A':		// alpha numeric only
    {
      if (isalnum(nChar)) return TRUE;
      break;
    }
    case 'a':		// alpha numeric or space
    {
      if (isalnum(nChar)) return TRUE;
      if (nChar == VK_SPACE) return TRUE;
      break;
    }
    case '&':		// all print character only
    {
      if (isprint(nChar)) return TRUE;
      break;
    }
  }
  MessageBeep((UINT)-1);
  return FALSE;
}

void CMaskEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  // si un masque existe, tester les touches spéciales
  if (m_bUseMask)
  {
    switch (nChar)
    {
      case VK_DELETE:
      case VK_INSERT: return;
    }
  }
  CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// CDateEdit class

IMPLEMENT_DYNAMIC(CDateEdit, CMaskEdit)

BEGIN_MESSAGE_MAP(CDateEdit, CMaskEdit)
  //{{AFX_MSG_MAP(CDateEdit)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDateEdit::CDateEdit()
{
  m_bUseMask = TRUE;
  m_isdate = TRUE; //added this
  m_strMask = _T("00/00/0000");
  m_strLiteral = _T("__/__/____");
}

void CDateEdit::SetDate(COleDateTime& Date)
{
  CString strText;
  FormatCOleDateTime(strText, Date, 10);
  m_str = strText;
  SetWindowText(strText);
}

COleDateTime CDateEdit::GetDate()
{
  CString strText;
  GetWindowText(strText);
  return ReadCOleDateTime(strText);
}

/////////////////////////////////////////////////////////////////////////////
// CTimeEdit class completely new

IMPLEMENT_DYNAMIC(CTimeEdit, CMaskEdit)

BEGIN_MESSAGE_MAP(CTimeEdit, CMaskEdit)
  //{{AFX_MSG_MAP(CTimeEdit)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTimeEdit::CTimeEdit()
{
  m_bUseMask = TRUE;
  m_isdate = FALSE; 
  m_strMask = _T("00:00");
  m_strLiteral = _T("__:__");
}

void CTimeEdit::SetTime(COleDateTime& Date)
{
  CString strText;
  FormatCOleDateTime(strText, Date, 5);
  m_str = strText;
  SetWindowText(strText);
}

COleDateTime CTimeEdit::GetTime()
{
  CString strText;
  GetWindowText(strText);
  return ReadCOleDateTime(strText);
}
