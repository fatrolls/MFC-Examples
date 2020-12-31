// valid.cpp
//
#include "stdafx.h"
#include "valid.h"

BEGIN_MESSAGE_MAP(CValidDialog, CDialog)
	//{{AFX_MSG_MAP(CValidDialog)
	ON_MESSAGE(WM_VALIDATE, OnValidate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CValidDialog::CValidDialog(UINT ID) : CDialog(ID)
{
	TRACE("CValidDialog ctor\n");
    m_bValidationOn = TRUE;                      // turn validation on
}

void CValidDialog::ValidateDlgItem(CDataExchange* pDX, UINT ID)
{
	// return valid unless overridden in the dialog
	ASSERT(this);
	TRACE("CValidDialog::ValidateDlgItem (should be overridden)\n");
	return;
}


BOOL CValidDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// specific for WIN32 -- wParam/lParam processing different for WIN16
 	TRACE("CValidDialog::OnCommand, wParam = %x, lParam = %x\n", wParam, lParam);
	TRACE("m_bValidationOn = %d\n", m_bValidationOn);
	if(m_bValidationOn) {   // might be a killfocus
        UINT notificationCode = (UINT) HIWORD( wParam );
        if((notificationCode == EN_KILLFOCUS)  ||
           (notificationCode == LBN_KILLFOCUS) ||
           (notificationCode == CBN_KILLFOCUS) ) {
            CWnd* pFocus = CWnd::GetFocus();
            // if we're changing focus to another control in the same dialog
            if( pFocus && (pFocus->GetParent() == this) ){
            	if(pFocus->GetDlgCtrlID() != IDCANCEL) {
            	    // and focus not in Cancel button
                    // validate AFTER drawing finished
                	PostMessage(WM_VALIDATE, wParam);
				}
            }
        }
    }
	return CDialog::OnCommand(wParam, lParam); // pass it on
}


LONG CValidDialog::OnValidate(UINT wParam, LONG lParam)
{
	TRACE("Entering CValidDialog::OnValidate\n");
	CDataExchange dx(this, TRUE);
    m_bValidationOn = FALSE;               // temporarily off
    UINT controlID = (UINT) LOWORD( wParam );
	try {
	    ValidateDlgItem(&dx, controlID);
	}
	catch(CUserException* pUE) {
		pUE->Delete();
		TRACE("caught the exception\n");
		// fall through -- user already alerted via message box
	}
    m_bValidationOn = TRUE;
    return 0;                            // goes no further
}

