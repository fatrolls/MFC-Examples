#include "stdafx.h"
#include "CDB.h"
#include "CDBDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CCDBDoc, CDocument)

BEGIN_MESSAGE_MAP(CCDBDoc, CDocument)
	//{{AFX_MSG_MAP(CCDBDoc)
	ON_COMMAND(ID_FILEDIALOGBOX_FILEOPEN, OnFiledialogboxFileopen)
	ON_COMMAND(ID_FILEDIALOGBOX_FILESAVE, OnFiledialogboxFilesave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCDBDoc::CCDBDoc()
{
}

CCDBDoc::~CCDBDoc()
{
}

BOOL CCDBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CCDBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CCDBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCDBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

void CCDBDoc::OnFiledialogboxFileopen() 
{
	CFileDialog	dlg(TRUE);
	CString szStr;

    dlg.m_ofn.lpstrFilter="Source Files(*.C;*.CPP;*.H;*.HPP)\0*.C;*.CPP;*.H;*.HPP\0Document(*.DOC;*.HTML)\0*.DOC;*.HTML\0All(*.*)\0*.*\0";
    dlg.m_ofn.nFilterIndex=1; 
	dlg.m_ofn.lpstrCustomFilter="DIB Files(*.BMP)\0*.BMP\0";
	dlg.m_ofn.nMaxCustFilter=26;
	if(dlg.DoModal() == IDOK)
	{
		szStr="File Name: ";
		szStr+=dlg.GetFileName();
		AfxMessageBox(szStr);
		szStr.Empty();
		szStr="Path Name: ";
		szStr+=dlg.GetPathName();
		AfxMessageBox(szStr);
	}
}

void CCDBDoc::OnFiledialogboxFilesave() 
{
	char szFile[256];
	CFileDialog	dlg(FALSE);
	CString szStr;

	sprintf(szFile, "TestFile");
	dlg.m_ofn.lpstrFile=szFile;
    dlg.m_ofn.nMaxFile=sizeof(szFile);
    dlg.m_ofn.lpstrDefExt="DIB";
    dlg.m_ofn.lpstrFilter="Source Files(*.C;*.CPP;*.H;*.HPP)\0*.C;*.CPP;*.H;*.HPP\0Document(*.DOC;*.HTML)\0*.DOC;*.HTML\0All(*.*)\0*.*\0";
    dlg.m_ofn.nFilterIndex=1;
	if(dlg.DoModal() == IDOK)
	{
		szStr="File Name: ";
		szStr+=dlg.GetFileName();
		AfxMessageBox(szStr);
		szStr.Empty();
		szStr="Path Name: ";
		szStr+=dlg.GetPathName();
		AfxMessageBox(szStr);
	}
}
