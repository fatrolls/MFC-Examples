#ifndef __WIZ_PROP_PAGE__
#define __WIZ_PROP_PAGE__

class CWizPropertySheet;

class CWizPropertyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CWizPropertyPage)
public:
	BOOL Enable(BOOL bEnable=TRUE);
	BOOL IsEnabled(void);
	CWizPropertyPage();
	CWizPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0);
	CWizPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0 );

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage1)
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL
protected:
	virtual LRESULT GetNextPage(BOOL forward = TRUE);
	BOOL m_bEnabled;
	CWizPropertySheet *m_pPropSheet;

	friend class CWizPropertySheet;
};

#endif