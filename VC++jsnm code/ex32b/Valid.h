// valid.h

#ifndef _VALIDDIALOG
#define _VALIDDIALOG

#define WM_VALIDATE WM_USER + 5

class CValidDialog : public CDialog
{
private:
		BOOL m_bValidationOn;
public:
	CValidDialog(UINT ID);
	
    virtual void ValidateDlgItem(CDataExchange* pDX, UINT ID); // overide in derived dlg to do validation
	//{{AFX_VIRTUAL(CValidDialog)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CValidDialog)
	afx_msg LONG OnValidate(UINT wParam, LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // _VALIDDIALOG
