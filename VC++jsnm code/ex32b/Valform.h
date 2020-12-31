// valform.h

#ifndef _VALIDFORM
#define _VALIDFORM

#define WM_VALIDATE WM_USER + 5

class CValidForm : public CFormView
{
DECLARE_DYNAMIC(CValidForm)
private:
		BOOL m_bValidationOn;
public:
	CValidForm(UINT ID);
	// overide in derived dlg to perform validation	
    virtual void ValidateDlgItem(CDataExchange* pDX, UINT ID); 
	//{{AFX_VIRTUAL(CValidForm)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CValidForm)
	afx_msg LONG OnValidate(UINT wParam, LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // _VALIDFORM
