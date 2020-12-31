// valform.cpp
//
#include "stdafx.h"
#include "valform.h"

IMPLEMENT_DYNAMIC(CValidForm, CFormView)

BEGIN_MESSAGE_MAP(CValidForm, CFormView)
	//{{AFX_MSG_MAP(CValidForm)
	ON_MESSAGE(WM_VALIDATE, OnValidate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CValidForm::CValidForm(UINT ID) : CFormView(ID)
{
	TRACE("CValidForm ctor\n");
    m_bValidationOn = TRUE;                      // turn validation on
}

void CValidForm::ValidateDlgItem(CDataExchange* pDX, UINT ID)
{
	// return valid unless overridden in the form
	ASSERT(this);
	TRACE("CValidForm::ValidateDlgItem (should be overridden)\n");
	return;
}


BOOL CValidForm::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// specific for WIN32 -- wParam/lParam processing different for WIN16
 	TRACE("CValidForm::OnCommand, wParam = %x, lParam = %x\n", wParam, lParam);
	TRACE("m_bValidationOn = %d\n", m_bValidationOn);
	if(m_bValidationOn) {   // might be a killfocus
        UINT notificationCode = (UINT) HIWORD( wParam );
        if((notificationCode == EN_KILLFOCUS)  ||
           (notificationCode == LBN_KILLFOCUS) ||
           (notificationCode == CBN_KILLFOCUS) ) {
            CWnd* pFocus = CWnd::GetFocus(); // static function call
            // if we're changing focus to another control in the same form
            if( pFocus && (pFocus->GetParent() == this) ){
            	if(pFocus->GetDlgCtrlID() != IDCANCEL) {
            	    // and focus not in Cancel button
                    // validate AFTER drawing finished
                	BOOL rtn = PostMessage( WM_VALIDATE, wParam );
					TRACE("posted message, rtn = %d\n", rtn);
				}
            }
        }
    }
	return CFormView::OnCommand(wParam, lParam); // pass it on
}


LONG CValidForm::OnValidate(UINT wParam, LONG lParam)
{
	TRACE("Entering CValidForm::OnValidate\n");
	CDataExchange dx(this, TRUE);
    m_bValidationOn = FALSE;               // temporarily off
    UINT controlID = (UINT) LOWORD( wParam );
	try {
	    ValidateDlgItem(&dx, controlID);
	}
	catch(CUserException* pUE) {
		pUE->Delete();
		TRACE("CValidForm caught the exception\n");
		// fall through -- user already alerted via message box
	}
    m_bValidationOn = TRUE;
    return 0;                            // goes no further
}

