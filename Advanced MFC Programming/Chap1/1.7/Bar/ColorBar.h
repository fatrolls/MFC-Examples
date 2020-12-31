#if !defined(__COLORBAR_H__)
#define __COLORBAR_H__

class CColorBar : public CToolBar
{
public:
	CColorBar();
	BOOL AddComboBox();
	BOOL ShowComboBox();
	BOOL HideComboBox();
	virtual ~CColorBar();
	virtual CSize CalcDynamicLayout(int , DWORD);
	//{{AFX_VIRTUAL(CColorBar)
	//}}AFX_VIRTUAL

protected:
	CComboBox m_wndComboBox;

	//{{AFX_MSG(CColorBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif