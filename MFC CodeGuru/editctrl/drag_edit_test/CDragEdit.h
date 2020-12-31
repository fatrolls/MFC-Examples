//////////////////////////////////////
//
// Author : Sam Lu
// E-mail : ysl@springsoft.com.tw
//

#if !defined(AFX_CDRAGEDIT_H__871E3CD6_6359_11D1_8251_444553540000__INCLUDED_)
#define AFX_CDRAGEDIT_H__871E3CD6_6359_11D1_8251_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDragEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDragEdit window
#include <afxole.h>

class CDragEdit;

class CDEDropTarget : public COleDropTarget
{
public:
    CDEDropTarget()
        {
        ms_bBeginDrop=FALSE;
        ms_pEditCtl=NULL;
        }
    BOOL        Register(CDragEdit* pEdit);
    BOOL        OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
    DROPEFFECT  OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    void        OnDragLeave(CWnd* pWnd);
    DROPEFFECT  OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    DROPEFFECT  OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);

private:
    BOOL        ms_bBeginDrop;
    CDragEdit*  ms_pEditCtl;
};

class CDEDataSource : public COleDataSource
{
};

#define CDragEditBase   CEdit

class CDragEdit : public CDragEditBase
{
// Construction
public:
	CDragEdit();

// Attributes
public:
    enum {  DE_ENABLE_DRAG=1, 
            DE_ENABLE_DROP=2
    };

private:
    static  BOOL    ms_bOleInit;

    BOOL            ms_bDragInit;

    int             ms_nEnableFlags;

    BOOL            ms_bInDragging;

    BOOL            ms_bDropEqualDrag;
    int             ms_nDropPtLine;
    int             ms_nDropPtPos;

	CDEDropTarget	ms_dropTarget;
	CDEDataSource	ms_dropSource;

// Operations
public:
    BOOL    Init(int nFlags=(DE_ENABLE_DRAG|DE_ENABLE_DROP));

    BOOL    IsInDragging()                  {return ms_bInDragging;}
    void    SetDropEqualDrag(BOOL bEqual)   {ms_bDropEqualDrag=bEqual;}
    void    SetDropPos(int nLine, int nPos) {ms_nDropPtLine=nLine, 
                                             ms_nDropPtPos=nPos;}

    BOOL    GetCurRange(int& nLine1, int& nPos1, int& nLine2, int& nPos2);
    BOOL    GetLinePosByCursor(int& nLine, int& nPos);

    BOOL    SetCaretByCursor();
    BOOL    SetCaret(int nLine, int nPos);

    BOOL    DrawCaretByCursor();

    CPoint  GetPosFromLinePos(int nLine, int nPos)  
                {return PosFromChar(_LinePosToChar(nLine,nPos));}
    //we reimpelmented this function for fixing SDK's bug
    CPoint  PosFromChar(UINT uChar);

    BOOL    IsInSelRange();

    BOOL    EnableDrag()    
                {return (ms_nEnableFlags & DE_ENABLE_DRAG) ? TRUE : FALSE;}
    BOOL    EnableDrop()    
                {return (ms_nEnableFlags & DE_ENABLE_DROP) ? TRUE : FALSE;}
    

private:
    BOOL    _GetSelText(CString& str);
    void    _CharToLinePos(int nChar, int* pnLine, int* pnPos)
                {
                if (nChar<0) nChar=0;
                *pnLine=LineFromChar(nChar);
                *pnPos=nChar-LineIndex(*pnLine);
                }
    int     _LinePosToChar(int nLine, int nPos) {return LineIndex(nLine)+nPos;}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDragEdit)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDRAGEDIT_H__871E3CD6_6359_11D1_8251_444553540000__INCLUDED_)
