// EPropertyTextblockWindow.h: interface for the EPropertyTextblockWindow class.
//
//////////////////////////////////////////////////////////////////////

#ifndef EPROPERTYTEXTBLOCKWINDOW
#define EPROPERTYTEXTBLOCKWINDOW

#include "EPropWndEdit.h"
#include "EPropWnd.h"

class EPropertyTextblock;

#define PTB_ID_EDIT 1
#define PTB_ID_BUTTON_OK 2
#define PTB_ID_BUTTON_CANCEL 3

class EPropertyTextblockWindow : public CFrameWnd
{

protected:

	EPropWndEdit m_Edit;
	CStatic      m_ButtonPanel;
	CButton      m_ButtonOK;
	CButton      m_ButtonCancel;

	CRect        m_EditRect;
	CRect        m_PanelRect;

	EPropertyTextblock* m_pPropertyTextblock;
	EPropWnd*    m_pCtrl;

public:

	EPropertyTextblockWindow( EPropertyTextblock* pPropertyTextblock , EPropWnd* pCtrl , const CString& sName );
	virtual ~EPropertyTextblockWindow();

//	afx_msg void OnKillFocus( CWnd* pNewWnd );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnButtonOk();
	afx_msg void OnClose();

	virtual BOOL OnCreateClient( LPCREATESTRUCT lpcs, CCreateContext* pContext );

	CString GetEditText();
	void SetEditText( const CString& s );

protected:
	
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_EPROPERTYTEXTBLOCKWINDOW_H__CF8FE6A9_AAF4_4662_9BFE_D0ADE855FE99__INCLUDED_)
