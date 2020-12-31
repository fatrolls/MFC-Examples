// Doc.cpp : implementation of the Doc class
//

#include "stdafx.h"
#include "PrintFormEditor.h"

#include "Doc.h"
#include "MainFrm.h"
#include "View.h"

//#include <stream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Doc

CPrintFormObject ** ppClipObjs = NULL;
int iClipFormObj = 0;


CPrintFormObject::CPrintFormObject()
{
//enum { pfoStatic = 0, pfoEdit, pfoLine, pfoRect, pfoFrame, pfoImage, pfoRadio, pfoCheck, pfoSubForm };
	bSelected = false;

	rc = CRect(0,0,0,0);
	*cId = 0;
	*cCond = 0;
	*cId2 = 0;
	bBold = bItalic = bUnderline = false;
	lstrcpy(cFont, "Arial");
	iSize = 8;
	iType = -1;
	iBack = -1;
	crBack = RGB(255,255,255);
	crBdr = crFront= RGB(0,0,0);
	exInfo = 0;
	iBorder = 0;
	iBorderSize = 0;

	uiTextFormat = DT_LEFT|DT_TOP;
}

CPrintFormObject::CPrintFormObject(const int tpe)
{
//enum { pfoStatic = 0, pfoEdit, pfoLine, pfoRect, pfoFrame, pfoImage, pfoRadio, pfoCheck, pfoSubForm };
	bSelected = false;

	rc = CRect(0,0,0,0);
	*cId = 0;
	*cCond = 0;
	*cId2 = 0;
	bBold = bItalic = bUnderline = false;
	lstrcpy(cFont, "Arial");
	iSize = 8;
	iBack = -1;
	crBack = RGB(255,255,255);
	crBdr = crFront= RGB(0,0,0);
	exInfo = 0;
	iBorder = 0;
	iBorderSize = 0;

	iType = tpe;
	uiTextFormat = DT_LEFT|DT_TOP;

	switch (iType)
	{
	case pfoStatic:
		lstrcpy(cId, "Static Text");
		break;
	case pfoEdit:
		lstrcpy(cId, "[not yet assigned]");
		iBorder = bdrSingle;
		iBorderSize = 1;
		break;
	case pfoFrame:
		lstrcpy(cId, "Frame border");
		break;
	case pfoImage:
		lstrcpy(cId, "[not yet assigned]");
		break;
	case pfoRadio:
		lstrcpy(cId, "[not yet assigned]");
		break;
	case pfoCheck:
		lstrcpy(cId, "[not yet assigned]");
		break;
	case pfoSubForm:
		lstrcpy(cId, "[not yet assigned]");
		break;
	}
}

CPrintFormObject::CPrintFormObject(const CPrintFormObject * p)
{
	rc = p->rc;
	lstrcpy(cId, p->cId);
	lstrcpy(cCond, p->cCond);
	lstrcpy(cId2, p->cId2);

	bBold = p->bBold;
	bItalic = p->bItalic;
	bUnderline = p->bUnderline;
	lstrcpy(cFont, p->cFont);
	iSize = p->iSize;
	iType = p->iType;
	iBack = p->iBack;
	crBack = p->crBack;
	crFront = p->crFront;
	exInfo = p->exInfo;
	iBorder = p->iBorder;
	iBorderSize = p->iBorderSize;
	uiTextFormat = p->uiTextFormat;
	bSelected = p->bSelected;
	crBdr = p->crBdr;
}


CPrintFormObject::~CPrintFormObject()
{
}


IMPLEMENT_DYNCREATE(Doc, CDocument)

BEGIN_MESSAGE_MAP(Doc, CDocument)
	//{{AFX_MSG_MAP(Doc)
	ON_COMMAND(IDC_ADD_PAGE, OnAddPage)
	ON_UPDATE_COMMAND_UI(IDC_ADD_PAGE, OnUpdateAddPage)
	ON_COMMAND(IDC_REMOVE_PAGE, OnRemovePage)
	ON_UPDATE_COMMAND_UI(IDC_REMOVE_PAGE, OnUpdateRemovePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Doc construction/destruction

Doc::Doc()
{
	iFormObj = 0;
	ppObjs = NULL;
	rcPaper = CRect(0,0,1900,2600);

	iPages = 0;
	pPages = NULL;

	iSelpage = -1;
}

Doc::~Doc()
{
/*	if (iFormObj > 0)
	{
		for (int t = 0; t < iFormObj; t++)
		{
			delete ppObjs[t];
		}
		GlobalFree((HGLOBAL)ppObjs);
	}*/
	while (iPages > 0) RemovePage(iPages - 1);
}

CPage::CPage()
{
	iFormObj = 0;
	ppObjs = NULL;
	rcPaper = CRect(100,100,2000,2800);
}

CPage::~CPage()
{
	if (iFormObj > 0)
	{
		for (int t = 0; t < iFormObj; t++)
		{
			delete ppObjs[t];
		}
		GlobalFree((HGLOBAL)ppObjs);
	}
}

int Doc::AddPage()
{
	iPages ++;

	if (iPages > 1) pPages = (CPage **) GlobalReAlloc((HGLOBAL) pPages, sizeof(CPage *) * (iPages), GMEM_MOVEABLE|GMEM_ZEROINIT);
	else pPages = (CPage **) GlobalAlloc(GPTR, sizeof(CPage *));

	pPages[iPages-1] = new CPage;

	pPages[iPages-1]->name.Format("page %d", iPages);

	FillList();

	return iPages - 1;
}

void Doc::SelectPage(const int p)
{
	if (iSelpage >= 0 && iSelpage < iPages)
	{
		pPages[iSelpage]->name = name;
		pPages[iSelpage]->rcPaper = rcPaper;
		pPages[iSelpage]->ppObjs = ppObjs;
		pPages[iSelpage]->iFormObj = iFormObj;
	}

	if (p < iPages && p >= 0)
	{
		name = pPages[p]->name;
		rcPaper = pPages[p]->rcPaper;
		ppObjs = pPages[p]->ppObjs;
		iFormObj = pPages[p]->iFormObj;
	}
	else
	{
		iSelpage = -1;
		name = "";
		rcPaper = CRect(0,0,0,0);
		ppObjs = NULL;
		iFormObj = 0;
	}

	iSelpage = p;

	POSITION pos = GetFirstViewPosition();   
	while (pos != NULL)   
	{
		View* pView = (View *)GetNextView(pos);
		if (pView->GetSafeHwnd())
		{
			pView->Invalidate();
			pView->SetPaperRect(rcPaper);

			pView->UpdateWindow();
		}
	}
}

void Doc::RemovePage(const int p)
{
	if (iPages <= 0) return;

	int os = iSelpage;
	SelectPage(p);

/*	if (iFormObj > 0)
	{
		for (int t = 0; t < iFormObj; t++)
		{
			delete ppObjs[t];
		}
		GlobalFree((HGLOBAL)ppObjs);
		name = "";
		rcPaper = CRect(0,0,0,0);
		ppObjs = NULL;
		iFormObj = 0;
	}*/
	iPages --;
	if (iPages <= 0)
	{
		delete pPages[p];

		GlobalFree((HGLOBAL)pPages);
		pPages = NULL;
		iPages = 0;
		iSelpage = -1;
	}
	else
	{
		delete pPages[p];
		for (int t = p+1; t < iPages; t++)
			pPages[t-1] = pPages[t];
		pPages = (CPage **) GlobalReAlloc((HGLOBAL) pPages, sizeof(CPage *) * (iPages), GMEM_MOVEABLE|GMEM_ZEROINIT);

		iSelpage = -1;
		if (os < p) SelectPage(os);
		else SelectPage(os - 1);
	}
}

BOOL Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	SelectPage(AddPage());

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// Doc serialization

void Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// Doc diagnostics

#ifdef _DEBUG
void Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Doc commands

CPrintFormObject * Doc::AddObject(const int tpe)
{
	iFormObj ++;

	if (iFormObj > 1) ppObjs = (CPrintFormObject **) GlobalReAlloc((HGLOBAL) ppObjs, sizeof(CPrintFormObject *) * (iFormObj), GMEM_MOVEABLE|GMEM_ZEROINIT);
	else ppObjs = (CPrintFormObject **) GlobalAlloc(GPTR, sizeof(CPrintFormObject *));

	ppObjs[iFormObj-1] = new CPrintFormObject(tpe);

	return ppObjs[iFormObj-1];
}

void Doc::DeleteContents() 
{
	if (iSelpage >= 0 && iSelpage < iPages)
	{
		pPages[iSelpage]->name = name;
		pPages[iSelpage]->rcPaper = rcPaper;
		pPages[iSelpage]->ppObjs = ppObjs;
		pPages[iSelpage]->iFormObj = iFormObj;
	}

	while (iPages > 0) RemovePage(iPages - 1);
/*	if (iFormObj > 0 && ppObjs)
	{
		for (int t = 0; t < iFormObj; t++)
		{
			delete ppObjs[t];
		}
		GlobalFree((HGLOBAL)ppObjs);
	}

	iFormObj = 0;
	ppObjs = NULL;
*/	
	CDocument::DeleteContents();
}

void DrawARect(CDC * pDC, CRect rc)
{
	CPen pn(PS_SOLID, 1, RGB(128,128,128));
	CPen * op = pDC->SelectObject(&pn);
	pDC->MoveTo(rc.left, rc.top);
	pDC->LineTo(rc.left, rc.bottom - 1);
	pDC->LineTo(rc.right - 1, rc.bottom - 1);
	pDC->LineTo(rc.right - 1, rc.top);
	pDC->LineTo(rc.left, rc.top);
	pDC->SelectObject(op);
}

void DrawRect(CDC * pDC, CRect rc)
{
	pDC->MoveTo(rc.left, rc.top);
	pDC->LineTo(rc.left, rc.bottom - 1);
	pDC->LineTo(rc.right - 1, rc.bottom - 1);
	pDC->LineTo(rc.right - 1, rc.top);
	pDC->LineTo(rc.left, rc.top);
}


void DrawSelRect(CDC * pDC, CRect rc)
{
	pDC->DrawDragRect(rc, CSize(3,3), NULL, CSize(3,3));
}


void CPrintFormObject::Draw(CDC * pDC, int xos, int yos, int div)
{
//enum { pfoStatic = 0, pfoEdit, pfoLine, pfoRect, pfoFrame, pfoImage, pfoRadio, pfoCheck, pfoSubForm };
	CRect rc1(rc);
	rc1.top /= div;
	rc1.left /= div;
	rc1.right /= div;
	rc1.bottom /= div;

	if (iBorderSize < 1) iBorderSize = 1;



	rc1.OffsetRect(-xos, -yos);

	int obk = pDC->GetBkMode();
	COLORREF ocrt = pDC->GetTextColor();
	COLORREF ocrbk = pDC->GetBkColor();

/*	iBorder = bdrSingle;
	iBorderSize = 1;
	COLORREF	crBack, crFront;
*/
	if (iBack != 0) 
	{
		pDC->SetBkMode(TRANSPARENT); 
	}
	else 
	{
		pDC->SetBkMode(OPAQUE);
		pDC->FillSolidRect(rc1, crBack);
	}

	pDC->SetTextColor(crFront);
	pDC->SetBkColor(crBack);

	switch(iType)
	{
	case pfoStatic:
	case pfoEdit:
		{
			if (*cId)
			{
				CFont ft;
				CFont * of = pDC->SelectObject(CreateFont(ft, pDC, div));
				pDC->DrawText(CString(cId), rc1, uiTextFormat);
				pDC->SelectObject(of);
			}
			if (iBorder > 0)
			{
				CPen pn(PS_SOLID, iBorderSize, crFront);
				CPen * op = pDC->SelectObject(&pn);
				DrawRect(pDC, rc1);
				pDC->SelectObject(op);
			}
		}
		break;
	case pfoImage:
		{
			CPen pn(PS_SOLID, 1, RGB(0,0,0));
			CPen * op = pDC->SelectObject(&pn);
			DrawRect(pDC, rc1);
			pDC->FillSolidRect(rc1, RGB(212,212,212));
			CFont ft;
			CFont * of = pDC->SelectObject(CreateFont(ft, pDC, div));
			CString cs;
			cs.Format("Image: %s", cId); 
			pDC->DrawText(cs, rc1, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
			pDC->SelectObject(of);
			pDC->SelectObject(op);
		}
		if (iBorder > 0)
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			DrawRect(pDC, rc1);
			pDC->SelectObject(op);
		}
		break;
	case pfoSubForm:
		{
			CPen pn(PS_SOLID, 1, RGB(0,0,0));
			CPen * op = pDC->SelectObject(&pn);
			DrawRect(pDC, rc1);
			pDC->FillSolidRect(rc1, RGB(223,223,223));
			CFont ft;
			CFont * of = pDC->SelectObject(CreateFont(ft, pDC, div));
			CString cs;
			cs.Format("SubForm: %s", cId); 
			pDC->DrawText(cs, rc1, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
			pDC->SelectObject(of);
			pDC->SelectObject(op);
		}
		if (iBorder > 0)
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			DrawRect(pDC, rc1);
			pDC->SelectObject(op);
		}
		break;
	case pfoRect:
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			DrawRect(pDC, rc1);
//			pDC->FillSolidRect(rc1, crFront);			
			pDC->SelectObject(op);
		}
		break;
	case pfoLine:
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			pDC->MoveTo(rc1.left, rc1.top);
			pDC->LineTo(rc1.right, rc1.bottom);
			pDC->SelectObject(op);
		}
		break;
	case pfoVLine:
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			pDC->MoveTo(rc1.left, rc1.top);
			pDC->LineTo(rc1.left, rc1.bottom);
			pDC->SelectObject(op);
		}
		break;
	case pfoHLine:
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			pDC->MoveTo(rc1.left, rc1.top);
			pDC->LineTo(rc1.right, rc1.top);
			pDC->SelectObject(op);
		}
		break;
/*	case pfoStatic:
		lstrcpy(cId, "Static Text");
		break;
	case pfoEdit:
		lstrcpy(cId, "[not yet assigned]");
		break;
	case pfoFrame:
		lstrcpy(cId, "Frame border");
		break;
	case pfoFrame:
		lstrcpy(cId, "[not yet assigned]");
		break;
	case pfoRadio:
		lstrcpy(cId, "[not yet assigned]");
		break;
	case pfoCheck:
		lstrcpy(cId, "[not yet assigned]");
		break;
	case pfoSubForm:
		lstrcpy(cId, "[not yet assigned]");
		break;*/
	}
	pDC->SetBkMode(obk);
	pDC->SetTextColor(ocrt);
	pDC->SetBkColor(ocrbk);
	if (bSelected) DrawSelRect(pDC, rc1); else DrawARect(pDC, rc1);
}


CFont * CPrintFormObject::CreateFont(CFont & ft, CDC * pDC, const int iDiv)
{
	if (ft.GetSafeHandle()) ft.DeleteObject();
	if (pDC->IsPrinting())
		ft.CreatePointFont((iSize * 10), cFont, pDC);
	else
		ft.CreatePointFont(((iSize + 6)* 10), cFont, pDC);

	if (bBold || bItalic || bUnderline)
	{
		LOGFONT lf;
		ft.GetLogFont(&lf);
		if (bBold) lf.lfWeight = 700;
		if (bUnderline) lf.lfUnderline = TRUE;
		if (bItalic) lf.lfItalic = TRUE;
		ft.DeleteObject();
		ft.CreateFontIndirect(&lf);
	}
	return &ft;
}

void Doc::ClearSelection()
{
	for (int t = 0; t < iFormObj; t++)
		ppObjs[t]->bSelected = false;
}

int Doc::GetSelectedCount()
{
	int res = 0;
	for (int t = 0; t < iFormObj; t++)
		if (ppObjs[t]->bSelected) res ++;
	return res;
}

bool RectInRect(const CRect &_rect, const CRect &r1)
{
	if (r1.left>_rect.right || r1.right<_rect.left || r1.top>_rect.bottom || r1.bottom<_rect.top) return false;
	return true;
}

int Doc::SelectObject(CRect rcBound)
{
	int res = 0;
	for (int t = 0; t < iFormObj; t++)
	{
		if (RectInRect(ppObjs[t]->rc, rcBound))
		{
			if (!(ppObjs[t]->bSelected)) 
			{
				ppObjs[t]->bSelected = true;
				res ++;
			}
		}
	}
	return res;
}

int Doc::HitTest(CPoint & pt, CRect &rc, int &idx)
{
	idx = -1;
	int res = CRectTracker::hitNothing;
	for (int t = iFormObj - 1; t >= 0; t--)
	{
		if (ppObjs[t]->rc.PtInRect(pt))
		{
			rc = ppObjs[t]->rc;
			idx = t;
			return 1;
		}
	}
	return res;
}

void Doc::RemoveSelected()
{
	int newtot = GetSelectedCount();
	if (newtot > 0)
	{
		newtot = iFormObj - newtot;
		if (newtot > 0)
		{
			int i = 0;
			CPrintFormObject ** np = (CPrintFormObject **) GlobalAlloc(GPTR, sizeof(CPrintFormObject *) * newtot);
			for (int t = 0; t < iFormObj; t++)
			{
				if (ppObjs[t]->bSelected)
				{
					delete ppObjs[t];
				}
				else np[i++] = ppObjs[t];
			}
			GlobalFree((HGLOBAL) ppObjs);
			ppObjs = np;
			iFormObj = newtot;
		}
		else
		{
			if (iFormObj > 0 && ppObjs)
			{
				for (int t = 0; t < iFormObj; t++)
				{
					delete ppObjs[t];
				}
				GlobalFree((HGLOBAL)ppObjs);
			}

			iFormObj = 0;
			ppObjs = NULL;
		}
	}
}

void Doc::CopySelected()
{
	if (iClipFormObj > 0)
	{
		for (int t = 0; t < iClipFormObj; t++)
		{
			delete ppClipObjs[t];
		}
		GlobalFree((HGLOBAL)ppClipObjs);
	}
	ppClipObjs = NULL;
	iClipFormObj = 0;

	int newtot = GetSelectedCount();
	if (newtot > 0)
	{
		int i = 0;
		ppClipObjs = (CPrintFormObject **) GlobalAlloc(GPTR, sizeof(CPrintFormObject *) * newtot);
		for (int t = 0; t < iFormObj; t++)
		{
			if (ppObjs[t]->bSelected)
			{
				ppClipObjs[i++] = new CPrintFormObject(ppObjs[t]);
			}
		}
		iClipFormObj = newtot;
	}
}

void Doc::PasteClip()
{
	ClearSelection();

	for (int t = 0; t < iClipFormObj; t++)
	{
		iFormObj ++;

		if (iFormObj > 1) ppObjs = (CPrintFormObject **) GlobalReAlloc((HGLOBAL) ppObjs, sizeof(CPrintFormObject *) * (iFormObj), GMEM_MOVEABLE|GMEM_ZEROINIT);
		else ppObjs = (CPrintFormObject **) GlobalAlloc(GPTR, sizeof(CPrintFormObject *));

		ppObjs[iFormObj-1] = new CPrintFormObject(ppClipObjs[t]);

		ppObjs[iFormObj-1]->rc.OffsetRect(20,20);
		ppObjs[iFormObj-1]->bSelected = true;
		ppClipObjs[t]->rc.OffsetRect(20,20);
	}
}

void CPrintFormObject::Print(CDC * pDC, CPoint offset)
{
//enum { pfoStatic = 0, pfoEdit, pfoLine, pfoRect, pfoFrame, pfoImage, pfoRadio, pfoCheck, pfoSubForm };
	CRect rc1(rc);
	rc1.OffsetRect(offset.x, offset.y);

	rc1.top *= -1;
	rc1.bottom *= -1;

	int obk = pDC->GetBkMode();
	COLORREF ocrt = pDC->GetTextColor();
	COLORREF ocrbk = pDC->GetBkColor();

	if (iBack != 0) 
	{
		pDC->SetBkMode(TRANSPARENT); 
	}
	else 
	{
		pDC->SetBkMode(OPAQUE);
		pDC->FillSolidRect(rc1, crBack);
	}

	pDC->SetTextColor(crFront);
	pDC->SetBkColor(crBack);

	switch(iType)
	{
	case pfoStatic:
	case pfoEdit:
		{
			if (*cId)
			{
				CFont ft;
				CFont * of = pDC->SelectObject(CreateFont(ft, pDC, 1));
				pDC->DrawText(CString(cId), rc1, uiTextFormat);
				pDC->SelectObject(of);
			}
			if (iBorder > 0)
			{
				CPen pn(PS_SOLID, iBorderSize, crFront);
				CPen * op = pDC->SelectObject(&pn);
				DrawRect(pDC, rc1);
				pDC->SelectObject(op);
			}
		}
		break;
	case pfoRect:
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			DrawRect(pDC, rc1);
			pDC->SelectObject(op);
		}
		break;
	case pfoLine:
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			pDC->MoveTo(rc1.left, rc1.top);
			pDC->LineTo(rc1.right, rc1.bottom);
			pDC->SelectObject(op);
		}
		break;
	case pfoVLine:
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			pDC->MoveTo(rc1.left, rc1.top);
			pDC->LineTo(rc1.left, rc1.bottom);
			pDC->SelectObject(op);
		}
		break;
	case pfoHLine:
		{
			CPen pn(PS_SOLID, iBorderSize, crFront);
			CPen * op = pDC->SelectObject(&pn);
			pDC->MoveTo(rc1.left, rc1.top);
			pDC->LineTo(rc1.right, rc1.top);
			pDC->SelectObject(op);
		}
		break;
	}
	pDC->SetBkMode(obk);
	pDC->SetTextColor(ocrt);
	pDC->SetBkColor(ocrbk);
}

void Doc::OnAddPage() 
{
	SelectPage(AddPage());
	CPapersBar * pb = GfxGetPaperList();
	if (iSelpage >= 0)
		pb->wndList.SetItemState(iSelpage, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
}

void Doc::OnUpdateAddPage(CCmdUI* pCmdUI) 
{
	
}

void Doc::OnRemovePage() 
{
	CPapersBar * pb = GfxGetPaperList();
	int idx = pb->wndList.GetNextItem(-1, LVNI_SELECTED);
	pb->wndList.DeleteItem(idx);
	RemovePage(idx);
}

void Doc::OnUpdateRemovePage(CCmdUI* pCmdUI) 
{
	CPapersBar * pb = GfxGetPaperList();
	int idx = pb->wndList.GetNextItem(-1, LVNI_SELECTED);
	pCmdUI->Enable(idx >= 0);
}

void Doc::FillList()
{
	CPapersBar * pb = GfxGetPaperList();
	pb->wndList.DeleteAllItems();

	for (int t = 0; t < iPages; t++)
		pb->wndList.InsertItem(t, pPages[t]->name, 0);

	if (iSelpage >= 0)
		pb->wndList.SetItemState(iSelpage, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
}

void Doc::OnCloseDocument() 
{
	CPapersBar * pb = GfxGetPaperList();
	if (pb->pDoc == this) pb->pDoc = NULL;
	
	CDocument::OnCloseDocument();
}

void Doc::RenamePage(const int idx, CString cs)
{
	if (idx >= 0 && idx < iPages) pPages[idx]->name = cs;
	CPapersBar * pb = GfxGetPaperList();
	pb->wndList.SetItemText(idx, 0, cs);
	if (iSelpage == idx) name = cs;
}

void Parse2String(CString &src, CString &name, CString &value)
{
	name = value = "";
	int idx = src.Find('=');
	if (idx > 0)
	{
		name = src.Left(idx);
		value = src.Right(src.GetLength() - idx - 1);
	}
}

void GetNextValue(CString &src, CString &value)
{
	value = "";
	int idx = src.Find(',');
	if (idx >= 0)
	{
		value = src.Left(idx);
		src = src.Right(src.GetLength() - idx - 1);
	}
	else value = src;
}

BOOL Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
	DeleteContents();
	char buf[1024];
	CString cs, cs1, cs2;

	ifstream ifs(lpszPathName);
	ifs.getline(buf, 1023);	cs = buf;
	ASSERT(cs == "[Form Page Header]");
	
	ifs.getline(buf, 1023);	cs = buf;
	Parse2String(cs,cs1,cs2);
	ASSERT(cs1 == "NumPages");
	int np = atoi(cs2);

	for (int t = 0; t < np; t++)
	{
		AddPage();
		ifs.getline(buf, 1023);	cs = buf;
		Parse2String(cs,cs1,cs2);
		pPages[t]->name = cs2;
	}

	iSelpage = -1;
	ifs.getline(buf, 1023);	cs = buf;
	for (t = 0; t < iPages; t++)
	{
		SelectPage(t);
		ifs.getline(buf, 1023);	cs = buf;
		cs1.Format("[%s]", pPages[t]->name);
		ASSERT(cs1 == cs);

		ifs.getline(buf, 1023);	cs = buf;
		Parse2String(cs, cs1, cs2);
		ASSERT(cs1 == "Rect");
		GetNextValue(cs2, cs1);
		rcPaper.left = atoi(cs1);
		GetNextValue(cs2, cs1);
		rcPaper.top = atoi(cs1);
		GetNextValue(cs2, cs1);
		rcPaper.right = atoi(cs1);
		GetNextValue(cs2, cs1);
		rcPaper.bottom = atoi(cs1);

		while (cs != "" && ifs.good())
		{
			ifs.getline(buf, 1023);	cs = buf;
			if (cs != "")
			{
				CPrintFormObject * pf = AddObject(0);
				pf->Input(cs);
			}
		}
	}
	SelectPage(0);
	
	return TRUE;
}

BOOL Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	int osel = iSelpage;

	if (iSelpage >= 0 && iSelpage < iPages)
	{
		pPages[iSelpage]->name = name;
		pPages[iSelpage]->rcPaper = rcPaper;
		pPages[iSelpage]->ppObjs = ppObjs;
		pPages[iSelpage]->iFormObj = iFormObj;
	}

	int t,p;
	ofstream ofs(lpszPathName);
	 
	ofs << "[Form Page Header]\n";
	ofs << "NumPages=" << iPages  << "\n";
	for (t = 0; t < iPages; t++)
		ofs << "Page " << t << "=" << pPages[t]->name << "\n";

	for (p = 0; p < iPages; p++)
	{
		SelectPage(p);
		ofs << "\n[" << name << "]\n";
		ofs << "Rect=" << rcPaper.left << "," << rcPaper.top << "," << rcPaper.right << "," << rcPaper.bottom << "\n";
		for (int t = 0; t < iFormObj; t++) ppObjs[t]->Output(ofs);
	}
	SelectPage(osel);

	return true;
//	return CDocument::OnSaveDocument(lpszPathName);
}

CString RGBTOHEX(COLORREF cr)
{
	static CString cs;
	cs.Format("%02x%02x%02x", GetRValue(cr),GetGValue(cr),GetBValue(cr));
	return cs;
}

COLORREF HEXTORGB(CString cs)
{
	int r = 0, g = 0, b = 0;
	CString cs1;
	cs1 = cs.Left(2);
	sscanf(cs1, "%02x", &r);
	cs1 = cs.Mid(2,2);
	sscanf(cs1, "%02x", &g);
	cs1 = cs.Right(2);
	sscanf(cs1, "%02x", &b);
	COLORREF cr = RGB(r,g,b);
	return cr;
}

void CPrintFormObject::Output(ofstream & ofs)
{
	CString cs, cs1;
	switch (iType)
	{
	case pfoStatic:	cs = "Static="; break;
	case pfoEdit:	cs = "Edit="; break;
	case pfoLine:	cs = "Line="; break;
	case pfoRect:	cs = "Rect="; break;
	case pfoFrame:	cs = "Frame="; break;
	case pfoImage:	cs = "Image="; break;
	case pfoVLine:	cs = "VLine="; break;
	case pfoHLine:	cs = "HLine="; break;
	case pfoSubForm:cs = "Subform="; break;
	}
	if (cs == "") return;

	cs1.Format("%d,%d,%d,%d", rc.left,rc.top,rc.right,rc.bottom);
	cs += cs1;
	cs1.Format(",%s,%s,%s", cId, cCond, cId2);
	cs += cs1;
	cs1.Format(",%s,%s,%s", bBold ? "bold" : "", bItalic ? "italic" : "", bUnderline ? "underline" : "");
	cs += cs1;
	cs1.Format(",%s,%d,%d", cFont, iSize, iBack);
	cs += cs1;
	cs1.Format(",%s,%s,%s", RGBTOHEX(crBack), RGBTOHEX(crFront), RGBTOHEX(crBdr));
	cs += cs1;
	cs1.Format(",%d,%d,%d,%d", exInfo, iBorder, iBorderSize,uiTextFormat);
	cs += cs1;
	ofs << cs << "\n";
}

void CPrintFormObject::Input(CString &cs)
{
	CString cs1, cs2;
	Parse2String(cs, cs1, cs2);

	iType = -1;

	if (cs1.CompareNoCase("Static") == 0) iType = pfoStatic;
	if (cs1.CompareNoCase("Edit") == 0) iType = pfoEdit;
	if (cs1.CompareNoCase("Line") == 0) iType = pfoLine;
	if (cs1.CompareNoCase("Rect") == 0) iType = pfoRect;
	if (cs1.CompareNoCase("Frame") == 0) iType = pfoFrame;
	if (cs1.CompareNoCase("Image") == 0) iType = pfoImage;
	if (cs1.CompareNoCase("VLine") == 0) iType = pfoVLine;
	if (cs1.CompareNoCase("HLine") == 0) iType = pfoHLine;
	if (cs1.CompareNoCase("Subform") == 0) iType = pfoSubForm;

	ASSERT(iType != -1);
	
	GetNextValue(cs2, cs1);
	rc.left = atoi(cs1);
	GetNextValue(cs2, cs1);
	rc.top = atoi(cs1);
	GetNextValue(cs2, cs1);
	rc.right = atoi(cs1);
	GetNextValue(cs2, cs1);
	rc.bottom = atoi(cs1);

	GetNextValue(cs2, cs1);
	lstrcpy(cId, cs1);
	GetNextValue(cs2, cs1);
	lstrcpy(cCond, cs1);
	GetNextValue(cs2, cs1);
	lstrcpy(cId2, cs1);

	GetNextValue(cs2, cs1);
	bBold = cs1.CompareNoCase("bold") == 0 ? true : false;
	GetNextValue(cs2, cs1);
	bItalic = cs1.CompareNoCase("italic") == 0 ? true : false;
	GetNextValue(cs2, cs1);
	bUnderline = cs1.CompareNoCase("underline") == 0 ? true : false;

	GetNextValue(cs2, cs1);
	lstrcpy(cFont, cs1);
	GetNextValue(cs2, cs1);
	iSize = atoi(cs1);
	GetNextValue(cs2, cs1);
	iBack = atoi(cs1);

	GetNextValue(cs2, cs1);
	crBack = HEXTORGB(cs1);
	GetNextValue(cs2, cs1);
	crFront = HEXTORGB(cs1);
	GetNextValue(cs2, cs1);
	crBdr = HEXTORGB(cs1);

	GetNextValue(cs2, cs1);
	exInfo = atoi(cs1);
	GetNextValue(cs2, cs1);
	iBorder = atoi(cs1);
	GetNextValue(cs2, cs1);
	iBorderSize = atoi(cs1);
	GetNextValue(cs2, cs1);
	uiTextFormat = atoi(cs1);
}

void Doc::SetPageRect(CRect & rc)
{
	if (iSelpage >= 0 && iSelpage < iPages) pPages[iSelpage]->rcPaper = rc;

	rcPaper = rc;
	POSITION pos = GetFirstViewPosition();   
	while (pos != NULL)   
	{
		View* pView = (View *)GetNextView(pos);
		if (pView->GetSafeHwnd())
		{
			pView->Invalidate();
			pView->SetPaperRect(rcPaper);

			pView->UpdateWindow();
		}
	}

}
