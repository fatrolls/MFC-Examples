// CDragEdit.cpp : implementation file
//
// Author : Sam Lu
// E-mail : ysl@springsoft.com.tw
//

#include "stdafx.h"
#include "DragEdit.h"
#include "CDragEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXLINELEN 2048

enum {
    DE_INSEL, DE_BEFORESEL, DE_AFTERSEL
};

/////////////////////////////////////////////////////////////////////////////
// CDragEdit

CDragEdit::CDragEdit()
{
    ms_bDragInit=FALSE;
    ms_nEnableFlags=0;
    ms_bInDragging=FALSE;
    ms_bDropEqualDrag=FALSE;
}

CDragEdit::~CDragEdit()
{
}


BEGIN_MESSAGE_MAP(CDragEdit, CDragEditBase)
	//{{AFX_MSG_MAP(CDragEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragEdit message handlers
BOOL CDragEdit::ms_bOleInit=FALSE;

BOOL CDragEdit::Init(int nFlags) 
{
    if (!ms_bOleInit) {
        if (!AfxOleInit()) {
            TRACE("Fail in OLE initialating\n");
            return FALSE;
        }
        ms_bOleInit=TRUE;
    }

    if (ms_bDragInit) return FALSE;

    ms_nEnableFlags=nFlags;

    if (!GetSafeHwnd()) {
        TRACE("You should create CDragEdit first, before this function is called\n");
		return FALSE;
    }
	if (!ms_dropTarget.Register(this)) {
		TRACE("Fail in registing drop target\n");
		return FALSE;
	}
    ms_bDragInit=TRUE;
	return TRUE;
}

//we reimpelmented this function for fixing SDK's bug that
//it always returns (-1,-1) when the uChar is the last char
CPoint CDragEdit::PosFromChar(UINT uChar)
{
    if (0==uChar)
        return CPoint(0,0);
    CPoint pt=CDragEditBase::PosFromChar(uChar);
    if (pt.x<0 && pt.y<0) {
        int nLine, nPos;
        _CharToLinePos((int)uChar,&nLine,&nPos);
        //get dc and select current using font
        CClientDC dc(this);
        dc.SelectObject(GetFont());
        //get position of previous char
        pt=CDragEditBase::PosFromChar(uChar-1);        
        if (nPos==0) {
            //if current char is the first char
            //we get the current y from previous y plus font height
            CSize szFont=dc.GetTextExtent("A",1);
            pt.y+=szFont.cy;
            pt.x=0;
        }
        else {
            char szBuf[MAXLINELEN];
            GetLine(nLine,szBuf,sizeof(szBuf));
            CSize szFont=dc.GetTextExtent(&szBuf[nPos-1],1);
            pt.x+=szFont.cx;
        }
        dc.SelectStockObject(SYSTEM_FONT);
    }
    return pt;
}

//get line and pos information from current selection range
BOOL CDragEdit::GetCurRange(int& nLine1, int& nPos1, int& nLine2, int& nPos2)
{
    //get current selection range
    GetSel(nPos1,nPos2);
    //and trans. to line, pos
    _CharToLinePos(nPos1,&nLine1,&nPos1);
    _CharToLinePos(nPos2,&nLine2,&nPos2);
    return TRUE;
}

//get line and pos from current cursor position
//return TRUE, if cursor is exactly at a char
//return FALSE, if cursor is at white space area
BOOL CDragEdit::GetLinePosByCursor(int& nLine, int& nPos)
{
    CPoint ptCursor;
    GetCursorPos(&ptCursor);
    ScreenToClient(&ptCursor);

    nPos=(int)(short)LOWORD((DWORD)CharFromPos(ptCursor));
    if (nPos<0) nPos=0;
    _CharToLinePos(nPos,&nLine,&nPos);

    //the following codes will check if cusor is at white space area
    //get the maximum x of nLine
    CPoint ptChar;
    ptChar=PosFromChar(LineIndex(nLine)+LineLength(LineIndex(nLine)));
    if (ptChar.x<ptCursor.x || ptCursor.x<0)
        return FALSE;
    return TRUE;
}

//set edit's caret position by current cursor position
BOOL CDragEdit::SetCaretByCursor()
{
    //get cursor's position and translate it to client coordinate
    CPoint ptCursor;
    GetCursorPos(&ptCursor);
    ScreenToClient(&ptCursor);
    //set caret position
    int nChar=(int)LOWORD((DWORD)CharFromPos(ptCursor));
    SetSel(nChar,nChar);
    return TRUE;
}

BOOL CDragEdit::SetCaret(int nLine, int nPos)
{
    int nChar=_LinePosToChar(nLine,nPos);
    SetSel(nChar,nChar);
    return TRUE;
}

//draw a caret at current cursor position
//this function will not affect the caret position or selection status
BOOL CDragEdit::DrawCaretByCursor()
{
    int nLine, nPos;
    GetLinePosByCursor(nLine,nPos);
    SetCaretPos(GetPosFromLinePos(nLine,nPos));
    return TRUE;
}

//test if (nLine,Pos) is within (nLine1,nPos1)~(nLine2,nPos2)
static int LinePosInRange(int nLine, int nPos,
                           int nLine1, int nPos1,
                           int nLine2, int nPos2)
{
    if (nLine1==nLine2) {//single line selection mark
        if (nLine<nLine1) return DE_BEFORESEL;
        if (nLine>nLine1) return DE_AFTERSEL;
        //nLine==nLine1
        if (nPos<nPos1) return DE_BEFORESEL;
        if (nPos>nPos2) return DE_AFTERSEL;
    }
    else { //multi-line selection mark
        if (nLine<nLine1) return DE_BEFORESEL;
        if (nLine>nLine2) return DE_AFTERSEL;
        if (nLine==nLine1 && 
            nPos<nPos1) return DE_BEFORESEL;
        if (nLine==nLine2 && 
            nPos>nPos2) return DE_AFTERSEL;
    }
    return DE_INSEL;
}

//return TRUE, if cursor is within the selection mark
BOOL CDragEdit::IsInSelRange()
{
    int nLine1, nPos1, nLine2, nPos2;
    GetCurRange(nLine1,nPos1,nLine2,nPos2);
    if (nLine1==nLine2 && nPos1==nPos2) //no selection mark
        return FALSE;

    int nLine, nPos;
    if (!GetLinePosByCursor(nLine,nPos)) //out of selection mark
        return FALSE;
    return (LinePosInRange(nLine,nPos,nLine1,nPos1,
                           nLine2,nPos2)==DE_INSEL) ? TRUE : FALSE;
}

BOOL CDragEdit::_GetSelText(CString& str)
{
    int nLine1, nPos1, nLine2, nPos2;
    GetCurRange(nLine1,nPos1,nLine2,nPos2);
    ASSERT(nLine1>=0 && nPos1>=0 && nLine2>=0 && nPos2>=0);
    char szBuf[MAXLINELEN];
    int nLen;
    //single-line selection
    if (nLine1==nLine2) {
        nLen=GetLine(nLine1,szBuf,sizeof(szBuf));
        szBuf[nLen]='\0';
        szBuf[nPos2]='\0';
        str=szBuf+nPos1;
        return TRUE;
    }
    //multi-line section
    nLen=GetLine(nLine1,szBuf,sizeof(szBuf));
    szBuf[nLen]='\0';
    str=szBuf+nPos1;
    for (int i=nLine1+1; i<nLine2; i++) {
        str+="\r\n";
        nLen=GetLine(i,szBuf,sizeof(szBuf));
        szBuf[nLen]='\0';
        str+=szBuf;
    }
    str+="\r\n";
    nLen=GetLine(nLine2,szBuf,sizeof(szBuf));
    szBuf[nLen]='\0';
    szBuf[nPos2]='\0';
    str+=szBuf;
    return TRUE;
}

void CDragEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (!EnableDrag()) {
        CDragEditBase::OnLButtonDown(nFlags, point);
        return;
    }

    if (IsInSelRange()) {
        //get selected text
        CString str;
        if (!_GetSelText(str)) {
            CDragEditBase::OnLButtonDown(nFlags, point);
            return;
        }
        int nLine1, nPos1, nLine2, nPos2;
        GetCurRange(nLine1,nPos1,nLine2,nPos2);
        //make a copy of selected text to a global memory
        HGLOBAL hData=GlobalAlloc(GHND|GMEM_SHARE,strlen(str)+1);
        strcpy((LPSTR)GlobalLock(hData),str);
        GlobalUnlock(hData);
        ms_dropSource.CacheGlobalData(CF_TEXT,hData);

        //defined dragging area
        CRect   rc(point.x-5, point.y-5, point.x+5, point.y+5);
        //It seems it is a MFC's bug that MFC will set capture to AfxGetMainWnd()
        //and use its coordinate to test the lpRectStartDrag.
        //So, we need to first translate the rc's coordinate.
        MapWindowPoints(AfxGetMainWnd(),&rc);

        //start dragging
        ms_bDropEqualDrag=FALSE;
        ms_bInDragging=TRUE;
        DROPEFFECT dwEffect=ms_dropSource.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE,&rc);
        ms_bInDragging=FALSE;
        if (dwEffect & (DROPEFFECT_MOVE | DROPEFFECT_COPY)) {
            if (dwEffect & DROPEFFECT_MOVE) {
                if (ms_bDropEqualDrag) {
                    //If drag source equal to drop target and user want to
                    //move string
                    ms_bDropEqualDrag=FALSE;
                    int nSel=LinePosInRange(ms_nDropPtLine,ms_nDropPtPos,
                                             nLine1,nPos1,nLine2,nPos2);
                    //we don't allow the string be moved into selection area
                    if (nSel==DE_INSEL)
                        return;
                    else {
                        if (nSel==DE_AFTERSEL) {
                            //If user want to move the string back,
                            //we need to adjust the ms_nDropPtLine 
                            //and ms_nDropPtPos
                            int nChar=_LinePosToChar(ms_nDropPtLine,ms_nDropPtPos);
                            nChar-=str.GetLength();
                            //delet selected string first
                            ReplaceSel("",TRUE);
                            _CharToLinePos(nChar,&ms_nDropPtLine,&ms_nDropPtPos);
                            //set new insert point
                            SetCaret(ms_nDropPtLine,ms_nDropPtPos);
                        }
                        else {
                            //delet selected string first
                            ReplaceSel("",TRUE);
                            //set new insert point
                            SetCaret(ms_nDropPtLine,ms_nDropPtPos);
                        }
                        //insert dragged string and sel. it
                        int nBeg, nEnd;
                        GetSel(nBeg,nEnd);        
                        nEnd+=str.GetLength();
                        ReplaceSel(str,TRUE);
                        SetSel(nBeg,nEnd);
                    }
                }
                else
                    ReplaceSel("",TRUE);
            }
            ms_bDropEqualDrag=FALSE;
            return;
        }
        ms_bDropEqualDrag=FALSE;
        //If user does not want to drag string, we reset the caret pos.
	    SetCaretByCursor();
        return;
    }
	CDragEditBase::OnLButtonDown(nFlags, point);
}

BOOL CDragEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if (EnableDrag()) {
        if (IsInSelRange()) {
            //if the cursor is over a selection mark
            //we will change the cursor shape to a arrow type
            //It means user can drag it.
            ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
            return FALSE;
        }        	
    }
    //Otherwise, we keep the cursor shape as its original type
	return CDragEditBase::OnSetCursor(pWnd, nHitTest, message);
}

/*************************************************************
CDEDropTarget
**************************************************************/
BOOL CDEDropTarget::Register(CDragEdit* pEdit)
{
    ms_pEditCtl=pEdit;
    return COleDropTarget::Register(pEdit);
}

DROPEFFECT CDEDropTarget::OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point)
{
    ASSERT(ms_pEditCtl);

    //if pWnd is kind of CView, we let COleDropTarget to handle it
	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))
		return COleDropTarget::OnDragScroll(pWnd,dwKeyState,point);

    if (!ms_bBeginDrop)
        return DROPEFFECT_NONE;

    CRect rectClient;
	ms_pEditCtl->GetClientRect(&rectClient);
	CRect rect = rectClient;
    //nScrollInset is a COleDropTarget's static member variable
    rect.InflateRect(-nScrollInset, -nScrollInset);
	// hit-test against inset region
	if (rectClient.PtInRect(point) && !rect.PtInRect(point)) {
        UINT        uMsg;
        int         nCode;
        CScrollBar* pScrollBar=NULL;        
		// determine which way to scroll along both X & Y axis
        if (point.x<rect.left) {
            pScrollBar=ms_pEditCtl->GetScrollBarCtrl(SB_HORZ);
            uMsg=WM_HSCROLL;
			nCode=SB_LINELEFT;
        }
        else if (point.x>=rect.right) {
            pScrollBar=ms_pEditCtl->GetScrollBarCtrl(SB_HORZ);
            uMsg=WM_HSCROLL;
			nCode=SB_LINERIGHT;
        }
        if (point.y<rect.top) {
            pScrollBar=ms_pEditCtl->GetScrollBarCtrl(SB_VERT);
            uMsg=WM_VSCROLL;
			nCode=SB_LINEUP;
        }
        else if (point.y>=rect.bottom) {
			pScrollBar=ms_pEditCtl->GetScrollBarCtrl(SB_VERT);
            uMsg=WM_VSCROLL;
			nCode=SB_LINEDOWN;
        }

        LRESULT l=ms_pEditCtl->SendMessage(uMsg,MAKEWPARAM(nCode,0),
            (LPARAM)(pScrollBar ? pScrollBar->GetSafeHwnd() : NULL));

        ms_pEditCtl->DrawCaretByCursor();

        if (dwKeyState & MK_CONTROL)
            return DROPEFFECT_SCROLL | DROPEFFECT_COPY;
        else
            return DROPEFFECT_SCROLL | DROPEFFECT_MOVE;
    }
    return DROPEFFECT_NONE;
}

DROPEFFECT CDEDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, 
                                      DWORD dwKeyState, CPoint point)
{
    ASSERT(ms_pEditCtl);

    if (!ms_pEditCtl->EnableDrop() ||
        !pDataObject->IsDataAvailable(CF_TEXT)) 
        return DROPEFFECT_NONE;

    DROPEFFECT dwEffect;
    
    if (dwKeyState & MK_CONTROL)
        dwEffect=DROPEFFECT_COPY;
    else
        dwEffect=DROPEFFECT_MOVE;

    ms_bBeginDrop=TRUE;

    //we set focus to current window such that the caret will be shown
    ms_pEditCtl->SetFocus();

    return dwEffect;
}

void CDEDropTarget::OnDragLeave(CWnd* pWnd)
{
    ASSERT(ms_pEditCtl);

    ms_bBeginDrop=FALSE;
}

DROPEFFECT CDEDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, 
                                     DWORD dwKeyState, CPoint point)
{
    ASSERT(ms_pEditCtl);

    if (!ms_bBeginDrop)
        return DROPEFFECT_NONE;

    DROPEFFECT dwEffect;
    
    if (dwKeyState & MK_CONTROL)
        dwEffect=DROPEFFECT_COPY;
    else
        dwEffect=DROPEFFECT_MOVE;

    ms_pEditCtl->DrawCaretByCursor();
    return dwEffect;
}

BOOL CDEDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
                           DROPEFFECT dropEffect, CPoint point)
{
    ASSERT(ms_pEditCtl);

    if (!ms_bBeginDrop)
        return FALSE;

    if (ms_pEditCtl->IsInDragging() &&
        ms_pEditCtl->IsInSelRange())
        return DROPEFFECT_NONE;

    HGLOBAL hData=pDataObject->GetGlobalData(CF_TEXT);
    if (!hData) {
        TRACE("Fail in getting data\n");
        return FALSE;
    }
    LPCSTR lpcszData=(LPCSTR)GlobalLock(hData);
    if ((dropEffect & DROPEFFECT_MOVE) &&
        ms_pEditCtl->IsInDragging()) {
        //If the drag window equal to drop window and
        //user want to move string, we let drag source
        //to move string by itself
        ms_pEditCtl->SetDropEqualDrag(TRUE);
        int nLine, nPos;
        ms_pEditCtl->GetLinePosByCursor(nLine,nPos);
        ms_pEditCtl->SetDropPos(nLine,nPos);
    }
    else {
        //set dropped point
        ms_pEditCtl->SetCaretByCursor();
        //insert string and select the inserted string
        int nBeg, nEnd;
        ms_pEditCtl->GetSel(nBeg,nEnd);        
        nEnd+=strlen(lpcszData);
        ms_pEditCtl->ReplaceSel(lpcszData,TRUE);
        ms_pEditCtl->SetSel(nBeg,nEnd);
    }
    GlobalUnlock(hData);
    return TRUE;
}
