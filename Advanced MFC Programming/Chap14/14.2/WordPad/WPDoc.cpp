#include "stdafx.h"
#include "WordPad.h"
#include "MainFrm.h"
#include "WPDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CWordPadDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CWordPadDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CWordPadDoc)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

CWordPadDoc::CWordPadDoc()
{
}

CWordPadDoc::~CWordPadDoc()
{
}

BOOL CWordPadDoc::OnNewDocument()
{
	if(!CRichEditDoc::OnNewDocument())return FALSE;

	return TRUE;
}

BOOL CWordPadDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
{
	CString newName=lpszPathName;
	CFileDialog	dlg(FALSE);
	int iBad;

	if(newName.IsEmpty())
	{
/*		CDocTemplate *pTemplate=GetDocTemplate();
		ASSERT(pTemplate != NULL);

		newName=m_strPathName;
		if(bReplace && newName.IsEmpty())
		{
			newName=m_strTitle;
			iBad=newName.FindOneOf(_T(" #%;/\\"));
			if(iBad != -1)newName.ReleaseBuffer(iBad);
		}
*/
		dlg.m_ofn.lpstrFilter=STRING_FILTER;
		dlg.m_ofn.nFilterIndex=1;
		if(dlg.DoModal() == IDOK)newName=dlg.GetPathName();
		else return FALSE;
		if(dlg.m_ofn.nFilterIndex == 1)m_bRTF=TRUE;
		else m_bRTF=FALSE;
	
		if(bReplace)
		{
			CString szFind;

			if(dlg.m_ofn.nFilterIndex == 1)
			{
				szFind=newName;
				szFind.MakeLower();
				iBad=szFind.Find(".txt");
				if(iBad != -1)newName.ReleaseBuffer(iBad);
				newName+=".rtf";
			}
			else
			{
				szFind=newName;
				szFind.MakeLower();
				iBad=szFind.Find(".rtf");
				if(iBad != -1)newName.ReleaseBuffer(iBad);
				newName+=".txt";
			}

		}
		else
		{
			if(dlg.m_ofn.nFilterIndex == 1)
			{
				newName+=".rtf";
			}
			else newName+=".txt";
		}
	}

	CWaitCursor wait;

	if(!OnSaveDocument(newName))
	{
		if(lpszPathName == NULL)
		{
			TRY
			{
				CFile::Remove(newName);
			}
			CATCH_ALL(e)
			{
				TRACE0("Warning: failed to delete file after failed SaveAs.\n");
			}
			END_CATCH_ALL
		}
		return FALSE;
	}
	if(bReplace)SetPathName(newName, TRUE);

	return TRUE;
}

CRichEditCntrItem *CWordPadDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CWordPadCntrItem(preo, (CWordPadDoc*) this);
}

void CWordPadDoc::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
	}
	else
	{
	}
	CRichEditDoc::Serialize(ar);
}

#ifdef _DEBUG
void CWordPadDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CWordPadDoc::Dump(CDumpContext &dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif
