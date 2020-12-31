#ifndef CDRAW_DLG_H
#define CDRAW_DLG_H

#define ID_DOWN_INVALID	-1
#define ID_DOWN_MAX		0
#define ID_DOWN_MIN		1
#define ID_DOWN_CLOSE	2

//按钮的位图大小
#define BMP_WIDTH	31
#define BMP_HEIGHT	23


class CDrawDlg : public CDialog
{
	DECLARE_DYNAMIC(CDrawDlg)
public:
	CDrawDlg(UINT nIDTemplate, CWnd* pParent = NULL);
	virtual ~CDrawDlg();

	DECLARE_MESSAGE_MAP()
protected:
/**重载函数**/
	virtual void PreSubclassWindow();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

/**自定义函数**/

	// 获取窗体风格
	void GetWindowStyle();
	// 设置最小化、最大化、关闭按钮的位置坐标
	void SetButtonRegion();
	// 判断当前鼠标坐标是否位于指定的矩形区域内
	BOOL PtInRect(CRect &rtWin, CRect &rtClientBtn, CPoint &pt);


/**重载消息处理函数**/

	// 窗口风格改变时发送的消息
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg	void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg HRESULT OnNcHitTest(CPoint point);

private:
	// 是否具有最小、最大按钮、系统菜单、标题栏风格
	int m_MaxStyle;
	int m_MinStyle;
	int m_SysMenuStyle;
	int m_CaptionStyle;

	// 最大化、最小化、关闭按钮
	CRect m_rtMaxBox;
	CRect m_rtMinBox;
	CRect m_rtCloseBox;

	// 标记按下的按钮
	int m_nIDBtn;
	// 标题栏的高度
	int m_cyCaption;
	// 对话框边框的高度和宽度
	CPoint m_ptDlgFrame;

	// 对话框图标
	HICON m_hIcon;

	// 最大化按钮的三种状态：鼠标悬浮、正常状态、按下
	CBitmap m_bmMaxHover;
	CBitmap m_bmMaxNormal;
	CBitmap m_bmMaxDown;

	// 还原按钮的三种状态：鼠标悬浮、正常状态、按下
	CBitmap m_bmRestoreHover;
	CBitmap m_bmRestoreNormal;
	CBitmap m_bmRestoreDown;

	// 最小化按钮的三种状态：鼠标悬浮、正常状态、按下
	CBitmap m_bmMinHover;
	CBitmap m_bmMinNormal;
	CBitmap m_bmMinDown;

	// 关闭按钮的三种状态：鼠标悬浮、正常状态、按下
	CBitmap m_bmCloseHover;
	CBitmap m_bmCloseNormal;
	CBitmap m_bmCloseDown;
};


#endif //CDRAW_DLG_H