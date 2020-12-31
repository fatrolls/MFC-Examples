//  Project     : general base class
//  Compiler    : Visual C++ 5.0 / 6.0
//  Plattform   : Windows 95/98, Windows NT 3.51/4.0/2000
//  File        : ST_SplitterWnd.h 
//  Programmer  : dz, SoftToys
//  Copyright   : 2001 SoftToys
//  Contact     : info@softtoys.com
//  Description : base class for handling splitter windows 
//  History     : 02.Sept. 2001 Version 1.0
//

/*
   Credits: Oleg Galkin, the methods ShowColumn and HideColumn are taken from 
            an article posted by Oleg Galkin on www.codeguru.com

            Caroline Englebienne, Adrian Roman and Dongik Shin helped with their 
				excellent articles about the switching views on www.codeguru.com and
				www.codeproject.com.

*/



#if !defined(AFX_ST_SPLITTERWND_H__6C9C6214_ED01_4243_A840_63FEDCE65D1E__INCLUDED_)
#define AFX_ST_SPLITTERWND_H__6C9C6214_ED01_4243_A840_63FEDCE65D1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#pragma warning(disable:4786)

#include <vector>
//using namespace std;

#define LEFT_SIDE     0
#define RIGHT_SIDE    1
#define TOP_SIDE      LEFT_SIDE    
#define BOTTOM_SIDE   RIGHT_SIDE


class ST_SplitterWnd : public CSplitterWnd  
{

public:

	ST_SplitterWnd(int nLevel = 0);
	virtual ~ST_SplitterWnd();

	bool			Create( CWnd* pParentWnd , CRuntimeClass* pView1 , CRuntimeClass* pView2 , CCreateContext* pContext , bool bVertical = true , int nID = AFX_IDW_PANE_FIRST );
    bool			IsShown(int nPane);		// true if pane is shown (not hidden)
    void			ToggleSide(int nPane);			// Show or hide row of column
//    void			SetRegistryKey(LPCSTR p) {m_sRegKey = p;};

    ST_SplitterWnd* m_pSubSplitterWnd[2]; // 0=Left/Top, 1=Right/Bottom
    ST_SplitterWnd* AddSubDivision( int nSide , CRuntimeClass* pView1 , CRuntimeClass* pView2 ,	CCreateContext* pContext , bool bVertical );

   /* support for switching views */
    int AddView(int nSide, CRuntimeClass * pViewClass, CCreateContext* pContext);
	 void SwitchToView(int nSide,int nViewIX = -1);

	 void SetPaneSize( int iPaneIndex , int nSize );

protected:   


	inline void SideToRowCol(int nSide, int* nRow, int*  nCol) 
	{
		if (m_bVertical) {
			*nRow = 0;
			*nCol = nSide;
		}
		else {
			*nRow = nSide;
			*nCol = 0;
		}
	};

	void RecalcColRowInfo();

	void ShowRow();               // show row
   void HideRow(int rowHide);    // hide row
   void ShowColumn();            // show column
   void HideColumn(int colHide); // hide column

//   void SaveToRegistry();
//   void RememberSize();

   /* support for switching views */
	bool HideView(int nRow, int nCol);
	bool ShowView(int nRow, int nCol,CWnd* pWnd);

	int m_nHiddenPane;
 //  int m_nHiddenCol;	//0 is 0 is hidden, 1 if 1 is hidden, -1 if none are hidden
 //  int m_nHiddenRow; 	//0 is 0 is hidden, 1 if 1 is hidden, -1 if none are hidden

	void StopTracking(BOOL bAccept);
	void RecalcLayout();
	int m_nBarSize;			//the bar size is used to calculate pane 0 size when pane 1 is fixed
   int m_iFixedSizePane;	//the pane (0 or 1) that holds fixed width/height
   int m_nFixedSize;		//width/height og fixed pane, the other pane resizes to fit

	int m_nPaneSize[2];
	int m_nPaneMinSize[2];

   bool m_bVertical;
   CString m_sRegKey;
   int m_nLevel;

	/* support for switching views */
	std::vector<CWnd*> m_views[2];

   int m_nCurrentView[2]; // side as index

//--------------------
protected:

	//{{AFX_MSG(CMainFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_ST_SPLITTERWND_H__6C9C6214_ED01_4243_A840_63FEDCE65D1E__INCLUDED_)
