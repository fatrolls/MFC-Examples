#pragma once
/* CVSTab

作者：严政
时间：2009.8.26
版本：1.1
更新：2009.8.31
	+ ToolTips支持，需要在父窗口实现
	+ 可以添加子窗体
功能：

画出来的TAB类似下面（可参考FireFox的Tab）

****************************************************************************
*(TAB1) | (TAB2) | (TAB3) | (TAB4) |(+)|                          |(↓)|（X）
****************************************************************************

描述：
	上图中+为新建，↓为下拉菜单，X为关闭按钮（其中任何一个都可以去掉）。
	除了新建和下拉菜单标签外，其余每个页面标签宽度相同。
	标签又一个默认宽度，所有标签宽度总和超过该标签则自动平均缩小宽度。例如新建按钮
、下拉菜单按钮、关闭宽度分别为A、B和C，预留空白区域宽度为W，标签默认宽度为X,控件总
宽度为Y，标签总数为N,则计算规则如下：
	if (N*X+A+B+C+W <= Y)
		X不变
	else
		X = (Y-A-B-C-2)/N;

注意：
	VSTAB_LBUTTONDOWN、VSTAB_RBUTTONDOWN
	父窗口必须有针对上面消息的对应的消息处理函数，并且需要delete掉lParam参数，否则内存泄漏
	
*/
#include <map>
#include "MemDC.h"

//宏定义
#define CLOSE_ITEM_WIDTH		16		//关闭标签宽度
#define NEW_ITEM_WIDTH			20		//新建标签宽度
#define DROP_MENU_WIDTH			16		//下拉菜单宽度
#define DEFAULT_ITEM_WIDHT		100		//默认标签宽度
#define DEFAULT_ITEM_HEIGHT		25		//默认标签高度
#define HMARGIN					2		//默认水平区域宽度
#define VMARGIN					0		

#define BTN_NEW_ITEM			0		
#define BTN_DROP_MENU			1
#define BTN_CLOSE_ITEM			2

//击中按钮，作为消息代码发送给父窗口，如果击中标签页，为非负整数
#define HIT_NEW_ITEM			-1
#define HIT_DROP_MENU			-2
#define HIT_CLOSE_ITEM			-3
#define HIT_OUT_OF_RANGE		-99		//鼠标点击不再区域中时返回

#define BTNST_NORMAL			0		//新建和下拉擦得标签为普通状态
#define BTNST_HOT				1		//激活状态，鼠标在上面的时候

#define COLOR_BORDER			RGB(51,153,255)
#define COLOR_BK_HOT			RGB(192,221,252)
#define COLOR_BK_NORMAL			GetSysColor(COLOR_BTNFACE)
#define COLOR_ITEM_SELECTED		RGB(51,153,255)//RGB(245,190,63)

#define TIMER_MOUSE_HOVER		0	//鼠标在项上停留多长时间才发送mouse move 消息
#define MOUSE_HOVER_ELAPSE		500	//毫秒

//消息代码
#define VSTAB_LBUTTONDOWN		WM_USER+3333
#define VSTAB_RBUTTONDOWN		WM_USER+3334
#define VSTAB_MOUSEMOVE			WM_USER+3345

//用户可以随意在这个结构中定义每个标签页的属性
typedef struct TabItem{
	TabItem(){
		nImage = 5;
		nCloseBtn = 0;
		nItem = 0;
		nData = 0;
		strItem = "";
		pWnd = NULL;
	}
	int nImage;			//Tab前那个图片索引,如果是负数，不画
	int nCloseBtn;		
	int nItem;			//标题索引
	int nData;			//标题包含的数据
	CString strItem;	//标题文字
	CWnd *pWnd;
}TabItem, *PTabItem;

struct NM_DATA{
	NMHDR hdr;
	TabItem* pItem;
	int hitArea;		//事件发生的区域
	CPoint hitPoint;	//鼠标点击的坐标（屏幕坐标系）
};
class CVSTab : public CWnd
{
	DECLARE_DYNAMIC(CVSTab)

public:
	CVSTab();
	virtual ~CVSTab();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();


private:
	int m_nControlID;

	int m_nItemCount;
	int m_nCurItem;
	int m_nItemHeight;	//暂时根据控件高度计算
	int m_nItemWidth;
	
	int m_btnState[3];	//0为新建，1为下拉菜单,2关闭

	//
	int m_nCurMouseHoverItem;	
	int m_nOldMouseHoverItem;
	bool m_bTimerAlive;
	CPoint m_curPoint;

	CFont m_fontText;
	COLORREF m_clrText;

	CImageList m_ImageList;
	CImageList* m_pImageList;

	CList<PTabItem, PTabItem> m_TabItemList;
protected:
	void DrawTabItem(CDC *pDC, CRect rcItem, int nItem);
	void CVSTab::DrawArrow(CDC *pDC, CPoint ptArrow, COLORREF crCol=RGB(0,0,0));
	int HitTest(CPoint pt);
	int CheckItem(int nItem);
	
	int DeleteItem(POSITION rpos);
	int CalculateItemWidth(void);
	NM_DATA* NewNotifyMsg(int nCode, int nArea, CPoint pt, TabItem* pItem);
public:
	void SetImageList(CImageList *pImageList){ m_pImageList = pImageList; }
	CImageList* GetImageList(){ return m_pImageList; }

	//Item's function
	TabItem*  FindItem(int nItem, bool itemOrData=true);
	int GetItemCount(){ return m_nItemCount; }
	int GetCurSel() { return m_nCurItem; }
	int SetCurSel(int nItem);
	int SetItemText(int nItem, CString szText);
	CString GetItemText(int nItem);
	BOOL SetItemTextFont(CString szFont, UINT nHeight);
	CFont* GetItemTextFont(){ return &m_fontText; }
	void SetItemTextColor(COLORREF clrText){ m_clrText = clrText; }
	COLORREF GetItemTextColor(){ return m_clrText; }
	int SetItemImage(int nItem, int nImage);
	int GetItemImage(int nItem);
	void SetItemWidth(int wd){ m_nItemWidth = wd; }
	int GetItemWidth(){ return m_nItemWidth; }
	//void SetItemHeight(int ht){ m_nItemHeight = ht; }
	//int SetItemHeight(){ return m_nItemHeight; }

	int InsertItem(TabItem* pItem);
	int InsertItem(CString szText, CWnd *pWnd=NULL, int nImage=-1,int nData=0);
	int DeleteItem(int nInfo, bool itemOrData);
	CRect GetItemRect(int nItem);
	
	//create vstab
	BOOL Create(CWnd *pParent, CRect rc, UINT nID);

	//msg function
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	BOOL DrawIcon(CDC* pDC, int nImage, CPoint point);
	void DrawLine(CDC* pDC, CPoint ptStart, CPoint ptEnd, COLORREF clrPen);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


