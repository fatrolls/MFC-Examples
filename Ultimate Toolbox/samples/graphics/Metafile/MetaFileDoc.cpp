// MetaFileDoc.cpp : implementation of the CMetaFileDoc class
//

#include "stdafx.h"
#include "MetaFile.h"

#include "MetaFileDoc.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc

IMPLEMENT_DYNCREATE(CMetaFileDoc, CDocument)

BEGIN_MESSAGE_MAP(CMetaFileDoc, CDocument)
	//{{AFX_MSG_MAP(CMetaFileDoc)
	ON_COMMAND(ID_FILE_CREATE_METAFILE, OnFileCreateMetafile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc construction/destruction

CMetaFileDoc::CMetaFileDoc()
{
	// TODO: add one-time construction code here

	// at startup the logo is loaded as EMF from resource
	m_MetaFile.LoadFile(IDR_HATECOMP_EMF);
}

CMetaFileDoc::~CMetaFileDoc()
{
}

BOOL CMetaFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc serialization

void CMetaFileDoc::Serialize(CArchive& ar)
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
// CMetaFileDoc diagnostics

#ifdef _DEBUG
void CMetaFileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMetaFileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMetaFileDoc commands

BOOL CMetaFileDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	CString sFileName=lpszPathName;
	// Load file, update caption and all Views
	if ( ! m_MetaFile.LoadFile(sFileName) )
	{	
		AfxMessageBox (_T("Error opening the MetaFile"));
		return FALSE; 
	}
	AfxGetApp()->m_pMainWnd->SetWindowText("MetaFileDemo: " + m_MetaFile.GetDescription());
	UpdateAllViews(NULL);

	return TRUE;
}

void CMetaFileDoc::OnFileCreateMetafile() 
{
	// TODO: Add your command handler code here
	
	HDC hdcEMF;
	COXMetaFile* pMetaFile=new COXMetaFile;

	// create a demo EMF - File
    hdcEMF = pMetaFile->CreateFile ("", "Created by Ultimate Toolbox OXMetaFile class") ;
	if(hdcEMF!=NULL)
	{
		CRect rect;
		rect.left=0;
		rect.right=300;
		rect.top=0;
		rect.bottom=200;
		CRect rectOrig=rect;
		
		CDC* pDC=CDC::FromHandle(hdcEMF);
		int nSaveDC=pDC->SaveDC();
		pDC->Rectangle(&rect);

		CBrush brush;
		for (int i=0; i<rectOrig.Height(); i+=10)
		{
			rect.bottom=rect.top+10;
			if(brush.CreateSolidBrush(RGB(0,0,255-i)))
			{
				pDC->FillRect(&rect,&brush) ;
				rect.top=rect.bottom;
				brush.DeleteObject();
			}
		}

		CString sText=_T("You've created this metafile!");
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		LOGFONT lf;
		::ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight=-22;
		lf.lfWeight=800;
		UTBStr::tcscpy(lf.lfFaceName, LF_FACESIZE, _T("Times New Roman"));
		CFont font;
		if(font.CreateFontIndirect(&lf))
		{
			pDC->SelectObject(&font);
		}
		pDC->DrawText(sText, &rectOrig, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		if((HFONT)font)
		{
			font.DeleteObject();
		}

		pMetaFile->CloseFile () ;

		pDC->RestoreDC(nSaveDC);

		CString sFileName=pMetaFile->GetFileName();
		
		delete pMetaFile;

		OnOpenDocument(sFileName);
		SetPathName(sFileName,TRUE);
	}
	else
	{
		pMetaFile->CloseFile () ;
		delete pMetaFile;
	}
	UpdateAllViews(NULL);
}
