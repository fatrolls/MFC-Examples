#if !defined(AFX_SPINBUTTONCTRL7_H__88DF334A_0849_4ABB_B067_05959DA60225__INCLUDED_)
#define AFX_SPINBUTTONCTRL7_H__88DF334A_0849_4ABB_B067_05959DA60225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpinButtonCtrl7.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpinButtonCtrl7 window

class CSpinButtonCtrl7 : public CSpinButtonCtrl
{
// Construction
public:
        CSpinButtonCtrl7();

// Attributes
public:
/*****************************************************************************
* This is necessary to retrofit these calls to MFC VS 6. This class is
* useless in VS7. Harmless, but useless.
*****************************************************************************/
#if _MFCVER < 0x0700
        void SetRange32(int low, int high) {
           ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, UDM_SETRANGE32, (WPARAM)low, (LPARAM)high); }
        void GetRange32(int & low, int & high) {
           ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, UDM_GETRANGE32, (WPARAM)&low, (LPARAM)&high); }
        void SetPos32(int pos) {
           ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, UDM_SETPOS32, 0, (LPARAM)pos); }
        int GetPos32() {
           ASSERT(::IsWindow(m_hWnd)); return ::SendMessage(m_hWnd, UDM_GETPOS32, 0, (LPARAM)NULL); }
#endif
// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CSpinButtonCtrl7)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CSpinButtonCtrl7();

        // Generated message map functions
protected:
        //{{AFX_MSG(CSpinButtonCtrl7)
                // NOTE - the ClassWizard will add and remove member functions here.
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPINBUTTONCTRL7_H__88DF334A_0849_4ABB_B067_05959DA60225__INCLUDED_)
