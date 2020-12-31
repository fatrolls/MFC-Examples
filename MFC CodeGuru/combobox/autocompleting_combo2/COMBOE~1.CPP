// ComboEdit.cpp : implementation file
//

#include "stdafx.h"
#include "cas.h"
#include "ComboEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboEdit

CComboEdit::CComboEdit()
: m_bHighlighted(false), m_nPos(0), m_nStartAfter(-1)
{
}

CComboEdit::~CComboEdit()
{
}


BEGIN_MESSAGE_MAP(CComboEdit, CEdit)
	//{{AFX_MSG_MAP(CComboEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboEdit message handlers

// This is called when a WM_KEYDOWN message is passed to CAS.
// OnKeyDown is needed because some special keys (like DELETE) 
// and the cursor keys are not trapped with a WM_CHAR message.
// After this function has been called, OnChar will be called
void CComboEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// Call base class implementation to ensure that key gets
	// handled as normal before I do anything dodgy with it
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	CTypeAheadCombo* pParent = (CTypeAheadCombo*) GetParent();
	
	// If the DELETE or BACKSPACE keys were pressed, set a flag
	m_bDelete = false;
	m_bBackspace = false;
	switch (nChar) {
	case VK_DELETE:
		m_bDelete = true;
		break;
	case VK_BACK:
		m_bBackspace = true;
		break;
	}

	// Get current cursor position
	m_nPos = LOWORD(pParent->GetEditSel());
	if ((nChar == VK_LEFT) || (nChar == VK_RIGHT)) {
		// If the left or right cursor keys have been pressed, this
		// will unhighlight the item
		m_bHighlighted = false;
		m_SearchString.Empty();
	}
	
	// If the DELETE key was not pressed, a WM_CHAR message does not get
	// generated, manually call OnChar() 
	if (m_bDelete)
		OnChar(nChar, nRepCnt, nFlags);
}

// This is called when  WM_CHAR message is sent to CAS. The nChar
// parameter contains the code of the character pressed.
void CComboEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// Only call the base class if it was NOT the DELETE key that was
	// pressed because if it was then it means that this function
	// has been called manually and calling the base class again would
	// cause two characters to get deleted!
	if (nChar != VK_DELETE)
		CEdit::OnChar(nChar, nRepCnt, nFlags);

	if (m_bHighlighted) {
		if ((m_bBackspace) || (m_bDelete)) {
			// A selection is highlighted and the backspace or delete
			// was pressed. Erase selection completely
			m_SearchString.Empty();
			m_bHighlighted = false;
			SetWindowText("");
			m_nStartAfter = -1;
		}
		else {
			// Alphanumeric key entered - go see if a match is found
			DoFind(nChar);
		}
	}
	else {
		// A selection is not highlighted, go see if a match is found
		DoFind(nChar);
	}
}

// DoFind() is an internal helper function to do the work of checking 
// a searh string against the items in the combo box. The search string
// is gradually built up by adding each new keysytoke to it as the user
// types it. If a match is found, that item in the combo box is highlighted
void CComboEdit::DoFind(UINT nChar)
{
	CString temp;
	int length = 0, index = 0;
	CTypeAheadCombo* pParent = (CTypeAheadCombo*) GetParent();

	// Get the key that the user typed
	GetWindowText(temp);
	// Add it to the existing search string
	m_SearchString += temp;
	// Get the length of the new string
	length = m_SearchString.GetLength();
	if (length) {
		// Search string is at least one character
		index = pParent->FindString(m_nStartAfter, m_SearchString);
		if (index != -1) {
			// Search string was found, highlight the item
			pParent->SetCurSel(index);
			m_nStartAfter = index;
			m_bHighlighted = true;
		}
		else {
			// Search string was not found in which case we want to put 
			// the user's text back into the edit box, reset
			// the search string and set the cursor appropriately
			if (m_bBackspace) {
				// BACKSPACE key pressed, the cursor position
				// needs to be one less than it was before
				pParent->SetEditSel(m_nPos - 1, m_nPos - 1);
			}
			else if (m_bDelete) {
				// DELETE key was pressed, leave the cursor as it was
				pParent->SetEditSel(m_nPos, m_nPos);
			}
			else if (m_bHighlighted) {
				// If the string was already highlighted then we put the
				// new search string in its place and set the cursor to the end
				SetWindowText(m_SearchString);
				pParent->SetEditSel(length, length);
			}
			else {
				// If a selection wasn't highlighted, we just move the cursor along
				pParent->SetEditSel(m_nPos + 1, m_nPos + 1);
			}
			// Clear out the search string 
			m_SearchString.Empty();
			m_bHighlighted = false;
		}
	}
}

