// FormJob.cpp: implementation of the CFormJob class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPrintForm.h"
#include "FormJob.h"
#include <fstream.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// CPrintFormObject implementaion
//////////////////////////////////////////////////////////////////////


CFormJob::CPrintFormObject::CPrintFormObject()
{
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

CFormJob::CPrintFormObject::~CPrintFormObject()
{
}

CFont * CFormJob::CPrintFormObject::CreateFont(CFont & ft, CDC * pDC, const int iDiv)
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

void DrawRect(CDC * pDC, CRect rc)
{
	pDC->MoveTo(rc.left, rc.top);
	pDC->LineTo(rc.left, rc.bottom - 1);
	pDC->LineTo(rc.right - 1, rc.bottom - 1);
	pDC->LineTo(rc.right - 1, rc.top);
	pDC->LineTo(rc.left, rc.top);
}

void CFormJob::CPrintFormObject::Print(CDC * pDC, CPoint offset)
{
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

void CFormJob::CPrintFormObject::Input(CString &cs)
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void CFormJob::Parse2String(CString &src, CString &name, CString &value)
{
	name = value = "";
	int idx = src.Find('=');
	if (idx > 0)
	{
		name = src.Left(idx);
		value = src.Right(src.GetLength() - idx - 1);
	}
}

void CFormJob::GetNextValue(CString &src, CString &value)
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

CString CFormJob::RGBTOHEX(COLORREF cr)
{
	static CString cs;
	cs.Format("%02x%02x%02x", GetRValue(cr),GetGValue(cr),GetBValue(cr));
	return cs;
}

COLORREF CFormJob::HEXTORGB(CString cs)
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


CFormJob::CFormJob()
{
	csPageName = "";
	rcPage = CRect(0,0,0,0);
}

CFormJob::~CFormJob()
{
	Clear();
}

void CFormJob::Clear()
{
	csObjectArray.RemoveAll();
	csScriptFile = "";
	csPageName = "";
}

bool CFormJob::LoadPage(const char * cFileName, const char * cPageName)
{
	ASSERT(cFileName && cPageName && *cFileName && *cPageName);

	Clear();
	ifstream ifs(cFileName);
	if (ifs.is_open())
	{
		bool bFind = false;
		char buf[1024];
		CString cs, cs1, cs2;
		cs1.Format("[%s]", cPageName);
		csScriptFile = cFileName;

		while (ifs.good() && bFind == false)
		{
			ifs.getline(buf,1023); cs = buf;
			if (cs.CompareNoCase(cs1) == 0) bFind = true;
		}
		if (bFind)
		{
			csPageName = cPageName;

			ifs.getline(buf,1023); cs = buf;

			Parse2String(cs, cs1, cs2);
			ASSERT(cs1 == "Rect");
			GetNextValue(cs2, cs1);
			rcPage.left = atoi(cs1);
			GetNextValue(cs2, cs1);
			rcPage.top = atoi(cs1);
			GetNextValue(cs2, cs1);
			rcPage.right = atoi(cs1);
			GetNextValue(cs2, cs1);
			rcPage.bottom = atoi(cs1);

			while (cs != "" && ifs.good())
			{
				ifs.getline(buf, 1023);	cs = buf;
				if (cs != "") csObjectArray.Add(cs);
			}
			if (csObjectArray.GetSize() > 0) return true;
			TRACE1("Warning: empty page (%s)\n", cPageName);
			return true;
		}
		TRACE2("CFormJob::LoadPage - error searching for page <%s> in file <%s> - page not found.\n", cPageName, cFileName);
		return false;
	}
	TRACE1("CFormJob::LoadPage - error opening input stream for file <%s>.\n", cFileName);
	return false;
}


bool CFormJob::SelectPrintObject(const int idx)
{
	if (idx >= 0 && idx < csObjectArray.GetSize())
	{
		cPrintObject.iType = -1;
		cPrintObject.Input(csObjectArray.GetAt(idx));
		return cPrintObject.iType >= 0 ? true : false;
	}
	return false;
}

int CFormJob::GetPrintObjectCount()
{
	return csObjectArray.GetSize();
}

void CFormJob::Print(CDC * pDC)
{
	if (cPrintObject.iType >= 0)
	{
		cPrintObject.Print(pDC, rcPage.TopLeft());
	}
}

bool CFormJob::HasSubForm(CString & csName, CSize & szItem)
{
	for (int t = 0; t < csObjectArray.GetSize(); t++)
	{
		if (csObjectArray.GetAt(t).Find("Subform") == 0)
		{
			SelectPrintObject(t);

			CFormJob subJob;
			if (subJob.LoadPage(csScriptFile, cPrintObject.cId))
			{
				csName = cPrintObject.cId;
				szItem = subJob.rcPage.Size();
				return true;
			}
		}
	}
	return false;
}
