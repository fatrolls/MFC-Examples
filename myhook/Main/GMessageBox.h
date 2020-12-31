#if !defined(AFX_GMESSAGEBOX_H__2678C180_04CA_4790_86C1_DCFD350ABADB__INCLUDED_)
#define AFX_GMESSAGEBOX_H__2678C180_04CA_4790_86C1_DCFD350ABADB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GMessageBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GMessageBox dialog

class GMessageBox : public CBCGPDialog
{
// Construction
public:
	GMessageBox(CWnd* pParent, CString strText, CString strCaption, UINT uType = MB_OK, COLORREF clr = COLOR_WINDOW);   // standard constructor
    ~GMessageBox();
// Dialog Data
	//{{AFX_DATA(GMessageBox)
	//enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GMessageBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GMessageBox)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//static int __stdcall MessageBoxCallbackProc(HWND hwnd, UINT uMsg, WPARAM lParam, LPARAM lpData);
    //LRESULT CALLBACK MessageBoxCallbackProc(/*HWND hwnd, */int code, /*UINT uMsg, */WPARAM wParam, LPARAM lparam);
private:
	CWnd* m_pParent;
	CString m_strText; 
	CString m_strCaption;
	UINT m_uType;
	COLORREF m_clrFace;
    CBCGPButton m_btnOK;
	CBCGPButton m_btnCancel;
	CBCGPButton m_btnAbort;
	CBCGPButton m_btnRetry;
	CBCGPButton m_btnIgnore;
	CBCGPButton m_btnYes;
	CBCGPButton m_btnNo;
	CBCGPButton m_btnClose;
	CBCGPButton m_btnHelp;
public:
	HWND m_hwnd;
	static GMessageBox* m_gBox;
public:
	UINT DoGModal();
	COLORREF GetFaceColor();
};

LRESULT CALLBACK MessageBoxCallbackProc(int code, WPARAM wParam, LPARAM lparam);
UINT AfxGMessageBox(CWnd* pParent, CString strText, CString strCaption, UINT uType = MB_OK, COLORREF clrFace = COLOR_WINDOW);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GMESSAGEBOX_H__2678C180_04CA_4790_86C1_DCFD350ABADB__INCLUDED_)
