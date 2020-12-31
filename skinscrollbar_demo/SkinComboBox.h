#pragma once


// CSkinComboBox

class CSkinComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CSkinComboBox)

public:
	CSkinComboBox();
	virtual ~CSkinComboBox();

	void SkinScroll(HBITMAP hBmp)
	{
		m_hBmpScroll=hBmp;
		//手动弹出下拉列表以便进行列表窗口的子类化
		ShowDropDown(TRUE);
		ShowDropDown(FALSE);
	}

protected:
	afx_msg void OnCbnCloseup();
	afx_msg void OnCbnDropdown();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

private:
	HWND	m_hWndList;
	HBITMAP	m_hBmpScroll;
};


