/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_DLGOPTIONS_H__9D30D683_EEBE_11D3_B75E_00C04F6A7AE6__INCLUDED_)
#define AFX_DLGOPTIONS_H__9D30D683_EEBE_11D3_B75E_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptions.h : header file
//

#include "GridTreeBtnCell_src\GridTreeBtnCell.h"

typedef enum
{
    TREE_IMAGE_NONE,
    TREE_IMAGE_AUTO,
    TREE_IMAGE_CUSTOM,

    TREE_IMAGE_FENCE    // ** don't delete or move from end
}   TREE_IMAGE;

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog

class CDlgOptions : public CDialog
{
// Construction
public:
	CDlgOptions(CWnd* pParent = NULL);   // standard constructor

    void SetGrid( CGridCtrl* apGrid) { ASSERT( apGrid != NULL); m_pGridCtrl = apGrid; }

protected:
    void ChangeFont( int iRow);    // row to set text

    void GetGridProps();

    unsigned int SetBtnState(  int nRow);   // zero-based row to set
    // returns:  button state value


    void GetFontDesc(  const LOGFONT* apLOGFONT,   // font
                       CString& arstrFont);  // returns:  string that describes font

    BOOL IsButtonCheckType( UINT ui) ;
    // returns:  T=is DFCS_BUTTONCHECK; F=some other type of DFC_BUTTON


private:
// Dialog Data
	//{{AFX_DATA(CDlgOptions)
	enum { IDD = IDD_OPTIONS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

    // for defining tree + button cells
    CTreeColumn m_TreeColumn;
    CBtnDataBase m_BtnDataBase;

    CImageList m_ImageList;
    CGridCtrl m_Grid;

    CGridCtrl* m_pGridCtrl;          // grid that we're setting options for

    typedef struct
    {
        unsigned char ucLevel;      // tree level 0-127
        int iImage;                 // index to CImageList image, -1 if no image
        UINT uiBtnState;            // DrawFrameControl() button state, UINT_MAX if no button
        void* pv;                   // custom data to manipulate
        const char* pszText;        // Text for this tree item
    }   STRUCT_TREE_ITEM;

    CGridCtrl* _pGridCtrl;          // grid that we're setting options for

    // declared static to allow easier data initialization
    static STRUCT_TREE_ITEM m_TreeItemAry[];    // hardcoded option list
    static BOOL m_bShowTreeBoxes;
    static int m_iTreeImages;
    static BOOL m_bShowVertLines;
    static BOOL m_bShowHorzLines;
    static BOOL m_bRowResizing;
    static BOOL m_bColResizing;
    static int m_iPrintType;
    static BOOL m_bIsEditable;
    static BOOL m_bAllowSelection;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptions)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
    afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONS_H__9D30D683_EEBE_11D3_B75E_00C04F6A7AE6__INCLUDED_)
