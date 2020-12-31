#ifndef __EX07ADIALOG_H__
#define __EX07ADIALOG_H__

// Ex07aDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx07aDialog dialog

#define WM_GOODBYE WM_USER + 5

class CEx07aDialog : public CDialog
{
private:
	CView* m_pView;
public:
	CEx07aDialog(CView* pView);
	BOOL Create();

// Construction
public:
	CEx07aDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEx07aDialog)
	enum { IDD = IDD_DIALOG1 };
	CString	m_strEdit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx07aDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEx07aDialog)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __EX07ADIALOG_H__
