// ex28cView.cpp : implementation of the CEx28cView class
//

#include "stdafx.h"
#include "ex28c.h"

#include "ex28cSet.h"
#include "SectionSet.h"
#include "ex28cDoc.h"
#include "ex28cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28cView

IMPLEMENT_DYNCREATE(CEx28cView, CRecordView)

BEGIN_MESSAGE_MAP(CEx28cView, CRecordView)
	//{{AFX_MSG_MAP(CEx28cView)
	ON_COMMAND(ID_RECORD_ADD, OnRecordAdd)
	ON_COMMAND(ID_RECORD_CLEARFIELDS, OnRecordClearfields)
	ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
	ON_UPDATE_COMMAND_UI(ID_RECORD_DELETE, OnUpdateRecordDelete)
	ON_COMMAND(ID_RECORD_UPDATE, OnRecordUpdate)
	ON_UPDATE_COMMAND_UI(ID_RECORD_UPDATE, OnUpdateRecordUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28cView construction/destruction

CEx28cView::CEx28cView()
	: CRecordView(CEx28cView::IDD)
{
	//{{AFX_DATA_INIT(CEx28cView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CEx28cView::~CEx28cView()
{
}

void CEx28cView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx28cView)
	DDX_FieldText(pDX, IDC_ID, m_pSet->m_InstructorID, m_pSet);
	DDX_FieldText(pDX, IDC_NAME, m_pSet->m_Name, m_pSet);
	DDX_FieldText(pDX, IDC_ROOM, m_pSet->m_RoomNo, m_pSet);
	//}}AFX_DATA_MAP
}

BOOL CEx28cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CEx28cView::OnInitialUpdate()
{
	m_pSet = GetDocument()->m_pEx28cSet;
	CRecordView::OnInitialUpdate();
	LoadListbox();
}

/////////////////////////////////////////////////////////////////////////////
// CEx28cView diagnostics

#ifdef _DEBUG
void CEx28cView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CEx28cView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CEx28cDoc* CEx28cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx28cDoc)));
	return (CEx28cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28cView database support
CRecordset* CEx28cView::OnGetRecordset()
{
	return m_pSet;
}


void CEx28cView::LoadListbox()
{
	CEx28cDoc* pDoc = GetDocument();
	CListBox* pLB = (CListBox*) GetDlgItem(IDC_SECTIONS);
	CSectionSet sect(&pDoc->m_database);  // db passed via constructor

	sect.m_strFilter.Format("InstructorID = '%s'", 
		(LPCSTR) m_pSet->m_InstructorID);

	sect.m_strFilter="InstructorID=?";
	sect.m_InstructorIDParam=m_pSet->m_InstructorID;

	sect.Open();
	pLB->ResetContent();
	while(!sect.IsEOF()) {
		pLB->AddString(sect.m_CourseID + " " + sect.m_SectionNo);
		sect.MoveNext();
	}
	// sect closed by CRecordset destructor
}
/////////////////////////////////////////////////////////////////////////////
// CEx28cView message handlers

BOOL CEx28cView::OnMove(UINT nIDMoveCommand) 
{
	switch (nIDMoveCommand)
	{
		case ID_RECORD_PREV:
			m_pSet->MovePrev();
			if (!m_pSet->IsBOF())
				break;

		case ID_RECORD_FIRST:
			m_pSet->MoveFirst();
			break;

		case ID_RECORD_NEXT:
			m_pSet->MoveNext();
			if (!m_pSet->IsEOF())
				break;
			if (!m_pSet->CanScroll()) {
				// clear out screen since we're sitting on EOF
				m_pSet->SetFieldNull(NULL);
				break;
			}

		case ID_RECORD_LAST:
			m_pSet->MoveLast();
			break;

		default:
			// Unexpected case value
			ASSERT(FALSE);
	}
	// Show results of move operation
	UpdateData(FALSE);
	LoadListbox();
	return TRUE;
}

void CEx28cView::OnRecordAdd() 
{
	m_pSet->AddNew();
	UpdateData(TRUE);
	if (m_pSet->CanUpdate())
	{
		m_pSet->Update();
	}
	if(!m_pSet->IsEOF()) {
		m_pSet->MoveLast();
	}
//	m_pSet->Requery(); // for sorted sets
	UpdateData(FALSE);
	LoadListbox();
}

void CEx28cView::OnRecordClearfields() 
{
	m_pSet->m_InstructorID = _T("");
	m_pSet->m_Name = _T("");
	m_pSet->m_RoomNo = _T("");
	UpdateData(FALSE);
	LoadListbox();
//	CListBox* pLB = (CListBox*) GetDlgItem(IDC_SECTIONS);
//	pLB->ResetContent();
}

void CEx28cView::OnRecordDelete() 
{
	try {
		m_pSet->Delete();
	}
	catch(CDBException* e) {
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pSet->MoveFirst(); // lost our place!
		UpdateData(FALSE);
		return;
	}
    m_pSet->MoveNext();
    // back to last if we moved off the end
    if (m_pSet->IsEOF()) {
      m_pSet->MoveLast();
    }
    // is the set now empty?
    if (m_pSet->IsEOF()) {
      m_pSet->SetFieldNull(NULL);
    }
    UpdateData(FALSE);
	LoadListbox();
}

void CEx28cView::OnUpdateRecordDelete(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!m_pSet->IsEOF());
}

void CEx28cView::OnRecordUpdate() 
{
	m_pSet->Edit();
	UpdateData(TRUE);
	if (m_pSet->CanUpdate()) {
		m_pSet->Update();
	}
	LoadListbox();
// snapshots only : must requery if key field changed
}

void CEx28cView::OnUpdateRecordUpdate(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!m_pSet->IsEOF());
}
