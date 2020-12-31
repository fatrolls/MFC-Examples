#pragma once



class CTranslucentDialog;

class CImgWnd : public CDialog
{
public:
	CImgWnd(const wchar_t* wszFile, UINT nID, CWnd* pParentWnd=NULL);
	virtual ~CImgWnd();

public:
	virtual INT_PTR	DoModal();

protected:
	virtual void	OnOK();
	virtual void	OnCancel();
	virtual BOOL	OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	void			DoCreate();

private:
	CTranslucentDialog*		m_pTranslucentWnd;	// 半透明窗口
	COLORREF				m_ColorKey;			// 层级窗口所设置的透明色，通过此透明色作为m_Brush，以镂空背景
	CBrush					m_Brush;
};

