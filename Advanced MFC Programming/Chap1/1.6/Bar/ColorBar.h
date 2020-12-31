#if !defined(__COLORBAR_H__)
#define __COLORBAR_H__

class CColorBar : public CToolBar
{
public:
	CComboBox m_wndComboBox;
	BOOL m_bVertical;

	CColorBar();
	BOOL AddComboBox();
	BOOL SetHorizontal();
	BOOL SetVertical();
	virtual ~CColorBar();
	virtual CSize CalcDynamicLayout(int , DWORD);
	//{{AFX_VIRTUAL(CColorBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CEditBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif