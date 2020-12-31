// OutlookDoc.cpp : implementation of the COutlookDoc class
//

#include "stdafx.h"
#include "Outlook.h"

#include "OutlookDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookDoc

IMPLEMENT_DYNCREATE(COutlookDoc, CDocument)

BEGIN_MESSAGE_MAP(COutlookDoc, CDocument)
	//{{AFX_MSG_MAP(COutlookDoc)
	ON_COMMAND(ID_ADDRESS_BOOK, OnAddressBook)
	ON_COMMAND(ID_AUTO_PREVIEW, OnAutoPreview)
	ON_COMMAND(ID_BACK, OnBack)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FIND_ITEMS, OnFindItems)
	ON_COMMAND(ID_FORWARD, OnForward)
	ON_COMMAND(ID_FORWARD_MESSAGE, OnForwardMessage)
	ON_COMMAND(ID_GROUP_BY_BOX, OnGroupByBox)
	ON_COMMAND(ID_MOVE_TO_FOLDER, OnMoveToFolder)
	ON_COMMAND(ID_NEW_MESSAGE, OnNewMessage)
	ON_COMMAND(ID_OFFICE_ASSISTANT, OnOfficeAssistant)
	ON_COMMAND(ID_REPLY_TO_ALL, OnReplyToAll)
	ON_COMMAND(ID_TOGGLE_TREE, OnToggleTree)
	ON_COMMAND(ID_UP_ONE_FOLDER, OnUpOneFolder)
	ON_COMMAND(ID_REPLY, OnReply)
	ON_COMMAND(ID_APPOINTMENT, OnAppointment)
	ON_COMMAND(ID_CONTACT, OnContact)
	ON_COMMAND(ID_MEETING_REQUEST, OnMeetingRequest)
	ON_COMMAND(ID_NOTE, OnNote)
	ON_COMMAND(ID_OFFICE_DOCUMENT, OnOfficeDocument)
	ON_COMMAND(ID_POST_IN_FOLDER, OnPostInFolder)
	ON_COMMAND(ID_TASK, OnTask)
	ON_COMMAND(ID_TASK_REQUEST, OnTaskRequest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookDoc construction/destruction

COutlookDoc::COutlookDoc()
{
	// TODO: add one-time construction code here

}

COutlookDoc::~COutlookDoc()
{
}

BOOL COutlookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COutlookDoc serialization

void COutlookDoc::Serialize(CArchive& ar)
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
// COutlookDoc diagnostics

#ifdef _DEBUG
void COutlookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COutlookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookDoc commands

void COutlookDoc::OnAddressBook() 
{
	AfxMessageBox(_T("OnAddressBook"));
}

void COutlookDoc::OnAutoPreview() 
{
	AfxMessageBox(_T("OnAutoPreview"));
}

void COutlookDoc::OnBack() 
{
	AfxMessageBox(_T("OnBack"));
}

void COutlookDoc::OnDelete() 
{
	AfxMessageBox(_T("OnDelete"));
}

void COutlookDoc::OnFilePrintPreview() 
{
	AfxMessageBox(_T("OnFilePrintPreview"));
}

void COutlookDoc::OnFindItems() 
{
	AfxMessageBox(_T("OnFindItems"));
}

void COutlookDoc::OnForward() 
{
	AfxMessageBox(_T("OnForward"));
}

void COutlookDoc::OnForwardMessage() 
{
	AfxMessageBox(_T("OnForwardMessage"));
}

void COutlookDoc::OnGroupByBox() 
{
	AfxMessageBox(_T("OnGroupByBox"));
}

void COutlookDoc::OnMoveToFolder() 
{
	AfxMessageBox(_T("OnMoveToFolder"));
}

void COutlookDoc::OnNewMessage() 
{
	AfxMessageBox(_T("OnNewMessage"));
}

void COutlookDoc::OnOfficeAssistant() 
{
	AfxMessageBox(_T("OnOfficeAssistant"));
}

void COutlookDoc::OnReplyToAll() 
{
	AfxMessageBox(_T("OnReplyToAll"));
}

void COutlookDoc::OnToggleTree() 
{
	AfxMessageBox(_T("OnToggleTree"));
}

void COutlookDoc::OnUpOneFolder() 
{
	AfxMessageBox(_T("OnUpOneFolder"));
}

void COutlookDoc::OnReply() 
{
	AfxMessageBox(_T("OnReply"));
}

void COutlookDoc::OnAppointment() 
{
	AfxMessageBox(_T("OnAppointment"));
}

void COutlookDoc::OnContact() 
{
	AfxMessageBox(_T("OnContact"));
}

void COutlookDoc::OnMeetingRequest() 
{
	AfxMessageBox(_T("OnMeetingRequest"));
}

void COutlookDoc::OnNote() 
{
	AfxMessageBox(_T("OnNote"));
}

void COutlookDoc::OnOfficeDocument() 
{
	AfxMessageBox(_T("OnOfficeDocument"));	
}

void COutlookDoc::OnPostInFolder() 
{
	AfxMessageBox(_T("OnPostInFolder"));	
}

void COutlookDoc::OnTask() 
{
	AfxMessageBox(_T("OnTask"));	
}

void COutlookDoc::OnTaskRequest() 
{
	AfxMessageBox(_T("OnTaskRequest"));	
}
