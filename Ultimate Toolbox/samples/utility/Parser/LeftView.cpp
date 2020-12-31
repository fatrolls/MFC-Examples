// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "ParserView.h"

#include "ParserViewDoc.h"
#include "LeftView.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAll)
	ON_COMMAND(ID_COLLAPSE_ALL, OnCollapseAll)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
    m_nCloseEmptyFolder = 0;
    m_nCloseFolder = 1;
    m_nOpenFolder  = 2;
    m_nTextItem    = 3;
    m_nAttribute   = 4;
    m_nComment     = 5;
    m_nProcInstr   = 6;
    m_nMarkup      = 7;
    m_nCData       = 8;

    m_pRightView = NULL;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= (TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_FULLROWSELECT);

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* /*pDC*/)
{
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Returns a string that is less than or equal to 20 chars long
LPCTSTR CLeftView::BriefText(LPCTSTR szText)
{
#define BRIEF_LENGTH 20

    static TCHAR szBrief[BRIEF_LENGTH+1];

    if (_tcslen(szText) <= BRIEF_LENGTH)
        return szText;

	UTBStr::tcsncpy(szBrief, 20, szText, BRIEF_LENGTH-3);
    szBrief[BRIEF_LENGTH-3] = TEXT('\0');
	UTBStr::tcscat(szBrief, BRIEF_LENGTH, TEXT("..."));

    return szBrief;
}

// Fills the tree recursively with the contents of the parser tree
void CLeftView::FillTree(HTREEITEM hParent, COXParserElement* pElement)
{
    if (pElement->GetType() != COXParserObject::ELEMENT)
        return;
	
	int i = 0;
    for (i = 0; i < pElement->NumAttributes(); i++)
    {
        COXAttribute* pAttribute = pElement->Attribute(i);
        if (!pAttribute) continue;

        TCHAR szText[1024];
        
        if (pAttribute->GetAttributeType() == COXAttribute::ATTR_STRING)
            UTBStr::stprintf(szText, 1024, TEXT("\"%s\"=\"%s\""), pAttribute->GetName(), pAttribute->GetStringValue());
        else if (pAttribute->GetAttributeType() == COXAttribute::ATTR_INTEGER)
            UTBStr::stprintf(szText, 1024, TEXT("\"%s\"=%d"), pAttribute->GetName(), pAttribute->GetIntValue());

        HTREEITEM hItem = GetTreeCtrl().InsertItem(szText, m_nAttribute, m_nAttribute, hParent);
        GetTreeCtrl().SetItemData(hItem, (DWORD) pAttribute);
    }
         
    for (i = 0; i < pElement->NumObjects(); i++)
    {
        COXParserObject* pObject = pElement->Object(i);
        if (!pObject) continue;

        HTREEITEM hNewParent;
        switch (pObject->GetType())
        {
            case COXParserObject::CDATA:
                hNewParent = GetTreeCtrl().InsertItem(BriefText(pObject->GetText()), 
                                                      m_nCData, m_nCData, 
                                                      hParent);
                GetTreeCtrl().SetItemData(hNewParent, (DWORD) pObject);
                break;

            case COXParserObject::COMMENT:
                hNewParent = GetTreeCtrl().InsertItem(BriefText(pObject->GetText()), 
                                                      m_nComment, m_nComment, 
                                                      hParent);
                GetTreeCtrl().SetItemData(hNewParent, (DWORD) pObject);
                break;

            case COXParserObject::ELEMENT:
                if (!((COXParserElement*)pObject)->NumObjects())
                    hNewParent = GetTreeCtrl().InsertItem(pObject->GetText(),
                    m_nCloseEmptyFolder, m_nCloseEmptyFolder,
                    hParent);
                else
                    hNewParent = GetTreeCtrl().InsertItem(pObject->GetText(),
                    m_nCloseFolder, m_nCloseFolder,
                    hParent);
                GetTreeCtrl().SetItemData(hNewParent, (DWORD) pObject);
                FillTree(hNewParent, (COXParserElement*)pObject);
                break;

            case COXParserObject::MARKUP:
                hNewParent = GetTreeCtrl().InsertItem(BriefText(pObject->GetText()), 
                                                      m_nMarkup, m_nMarkup, 
                                                      hParent);
                GetTreeCtrl().SetItemData(hNewParent, (DWORD) pObject);
                break;

            case COXParserObject::PLAINTEXT:
                hNewParent = GetTreeCtrl().InsertItem(BriefText(pObject->GetText()), 
                                                      m_nTextItem, m_nTextItem, 
                                                      hParent);
                GetTreeCtrl().SetItemData(hNewParent, (DWORD) pObject);
                break;

            case COXParserObject::PROCINSTR:
                hNewParent = GetTreeCtrl().InsertItem(BriefText(pObject->GetText()), 
                                                      m_nProcInstr, m_nProcInstr, 
                                                      hParent);
                GetTreeCtrl().SetItemData(hNewParent, (DWORD) pObject);
                break;
        }
    }        
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

    m_Images.Create(IDB_BITMAP, 16, 1, RGB(255,255,255));
    GetTreeCtrl().SetImageList(&m_Images, TVSIL_NORMAL);

    if (m_pRightView)
        m_pRightView->GetListCtrl()->SetImageList(&m_Images, LVSIL_SMALL);

    CParserViewDoc* pDoc = GetDocument();
    COXParser* pParser = pDoc->GetParser();

    HTREEITEM hItem = GetTreeCtrl().InsertItem(pParser->Root()->GetName(), 
                                               m_nCloseFolder, m_nCloseFolder);
    GetTreeCtrl().SetItemData(hItem, (DWORD) pParser->Root());

    CWaitCursor wait;
    FillTree(hItem, pParser->Root());
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CParserViewDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CParserViewDoc)));
	return (CParserViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    HTREEITEM hItem = pNMTreeView->itemNew.hItem;
    COXParserObject* pObject = (COXParserObject*) GetTreeCtrl().GetItemData(hItem);
    if (!pObject)
        return;

    if (pObject->GetType() == COXParserObject::ELEMENT)
    {
        COXParserElement* pElement = (COXParserElement*) pObject;
        if (pNMTreeView->action == TVE_COLLAPSE)
        {
            if (pElement->NumObjects())
                GetTreeCtrl().SetItemImage(hItem, m_nCloseFolder, m_nCloseFolder);
            else
                GetTreeCtrl().SetItemImage(hItem, m_nCloseEmptyFolder, m_nCloseEmptyFolder);
        }
        else if (pNMTreeView -> action == TVE_EXPAND)
            GetTreeCtrl().SetItemImage(hItem, m_nOpenFolder, m_nOpenFolder);
    }

	*pResult = 0;
}

void CLeftView::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (!m_pRightView || !m_pRightView->GetEditView() || !m_pRightView->GetListView())
        return;

    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    HTREEITEM hItem = pNMTreeView->itemNew.hItem;
    COXParserObject* pObject = (COXParserObject*) GetTreeCtrl().GetItemData(hItem);
    if (!pObject)
        return;

    ////////////////////////////////////////////////////////////////////////
    //  Fill in edit control
    ////////////////////////////////////////////////////////////////////////

    CString strType;
    int nNumObjects = 0;
    int nNumAttributes = 0;

    switch (pObject->GetType())
    {
        case COXParserObject::ATTRIBUTE:
            strType = "Attribute";
            break;

        case COXParserObject::CDATA:
            strType = "Character Data";
            break;
        
        case COXParserObject::COMMENT:
            strType = "Comment";
            break;
            
        case COXParserObject::MARKUP:
            strType = "Markup";
            break;
            
        case COXParserObject::PLAINTEXT:
            strType = "Plain text";
            break;
            
        case COXParserObject::PROCINSTR:
            strType = "Processing Instruction";
            break;
            
        case COXParserObject::ELEMENT:
            strType = "Element";
            nNumObjects = ((COXParserElement*)pObject)->NumObjects();
            nNumAttributes = ((COXParserElement*)pObject)->NumAttributes();
            break;

        default:
            strType = "Unknown";
            break;
    }

    // Need to convert \n's to \r\n's
    LPCTSTR szValue = pObject->GetText();
    COXQuickString strNew;
    strNew.SetLength(_tcslen(szValue)+1);
    while (*szValue)
    {
        if (*szValue == TEXT('\n'))
            strNew.Append(TEXT('\r'));
        strNew.Append(*szValue);
        szValue++;
    }

    CString str;
    str.Format(_T("Object Type:\t%s\r\n")
               _T("Attributes:\t%d\r\n")
               _T("SubObjects:\t%d\r\n")
               _T("Flags:\t\t%d\r\n")
               _T("Name/Text:\r\n%s"),
                strType, nNumAttributes, nNumObjects,
                pObject->GetFlags(), (LPCTSTR)strNew);

    if (pObject->GetType() == COXParserObject::ATTRIBUTE)
    {
        COXAttribute* pAttr = (COXAttribute*) pObject;
        CString tmp;
        if ( pAttr->GetAttributeType()  == COXAttribute::ATTR_STRING)
            tmp.Format(_T("Value:\t\t\"%s\"\r\n"), pAttr->GetStringValue());
        else
            tmp.Format(_T("Value:\t\t%d\r\n"), pAttr->GetIntValue());

        str += tmp;
    }

    m_pRightView->GetEditView()->SetWindowText(str);


    ////////////////////////////////////////////////////////////////////////
    //  Fill in list control
    ////////////////////////////////////////////////////////////////////////

    CListCtrl *pList = m_pRightView->GetListCtrl();
    m_pRightView->SetRedraw(FALSE);

    pList->DeleteAllItems();
    if (pList->GetHeaderCtrl())
    {
        for (int i = pList->GetHeaderCtrl()->GetItemCount()-1; i >= 0; i--)
            m_pRightView->GetListCtrl()->DeleteColumn(i);
    }

    if (pObject->GetType() == COXParserObject::ELEMENT)
    {
        pList->InsertColumn(0, _T("Object type")); 
        pList->InsertColumn(1, _T("Name")); 
        pList->InsertColumn(2, _T("SubObjects")); 
        pList->InsertColumn(3, _T("Value/Text")); 
        
        COXParserElement* pElement = (COXParserElement*) pObject;
        
        int nRow = 0;

		int i = 0;
        for (i = 0; i < pElement->NumAttributes(); i++)
        {
            COXAttribute* pAttribute = pElement->Attribute(i);
            if (!pAttribute) continue;
            
            pList->InsertItem(LVIF_TEXT|LVIF_IMAGE, nRow, _T("Attribute"), 0,0, m_nAttribute, 0);
            pList->SetItemText(nRow, 1, pAttribute->GetName());
            pList->SetItemText(nRow, 2, _T("0"));
            pList->SetItemText(nRow, 3, pAttribute->GetStringValue());
            nRow++;
        }
        
        for (i = 0; i < pElement->NumObjects(); i++)
        {
            COXParserObject* pSubObject = pElement->Object(i);
            if (!pSubObject) continue;

            switch (pSubObject->GetType())
            {
                case COXParserObject::CDATA:
                    pList->InsertItem(LVIF_TEXT|LVIF_IMAGE, nRow, _T("CDATA"), 0,0, m_nCData, 0);
                    pList->SetItemText(nRow, 1, _T(""));
                    pList->SetItemText(nRow, 2, _T("0"));
                    pList->SetItemText(nRow, 3, pSubObject->GetText());
                    nRow++;
                    break;

                case COXParserObject::PLAINTEXT:
                    pList->InsertItem(LVIF_TEXT|LVIF_IMAGE, nRow, _T("Plain Text"), 0,0, m_nTextItem, 0);
                    pList->SetItemText(nRow, 1, _T(""));
                    pList->SetItemText(nRow, 2, _T("0"));
                    pList->SetItemText(nRow, 3, pSubObject->GetText());
                    nRow++;
                    break;
                
                case COXParserObject::COMMENT:
                    pList->InsertItem(LVIF_TEXT|LVIF_IMAGE, nRow, _T("Comment"), 0,0, m_nComment, 0);
                    pList->SetItemText(nRow, 1, _T(""));
                    pList->SetItemText(nRow, 2, _T("0"));
                    pList->SetItemText(nRow, 3, pSubObject->GetText());
                    nRow++;
                    break;
                    
                case COXParserObject::MARKUP:
                    pList->InsertItem(LVIF_TEXT|LVIF_IMAGE, nRow, _T("Markup"), 0,0, m_nMarkup, 0);
                    pList->SetItemText(nRow, 1, _T(""));
                    pList->SetItemText(nRow, 2, _T("0"));
                    pList->SetItemText(nRow, 3, pSubObject->GetText());
                    nRow++;
                    break;
                    
                case COXParserObject::PROCINSTR:
                    pList->InsertItem(LVIF_TEXT|LVIF_IMAGE, nRow, _T("Processing Instruction"), 0,0, m_nProcInstr, 0);
                    pList->SetItemText(nRow, 1, _T(""));
                    pList->SetItemText(nRow, 2, _T("0"));
                    pList->SetItemText(nRow, 3, pSubObject->GetText());
                    nRow++;
                    break;
                    
                case COXParserObject::ELEMENT:
                    {
                        COXParserElement* pSubElement = (COXParserElement*) pSubObject;
                        if (pSubElement->NumObjects())
                            pList->InsertItem(LVIF_TEXT|LVIF_IMAGE, nRow, _T("Element"), 
                                              0,0, m_nCloseFolder, 0);
                        else
                            pList->InsertItem(LVIF_TEXT|LVIF_IMAGE, nRow, _T("Element"), 
                                              0,0, m_nCloseEmptyFolder, 0);

                        CString strNum;
                        strNum.Format(_T("%d"), pSubElement->NumObjects());
                        pList->SetItemText(nRow, 1, pSubElement->GetName());
                        pList->SetItemText(nRow, 2, strNum);
                        pList->SetItemText(nRow, 3, _T(""));
                        nRow++;
                    }
                    break;
            }
        }
        
        for (int col = 0; col < 3; col++) 
        {
            pList->SetColumnWidth(col, LVSCW_AUTOSIZE);
            int wc1 = pList->GetColumnWidth(col);
            pList->SetColumnWidth(col,LVSCW_AUTOSIZE_USEHEADER);
            int wc2 = pList->GetColumnWidth(col);
            int wc = max(20, max(wc1,wc2));
            pList->SetColumnWidth(col, wc);
        }
        pList->SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
    }

    m_pRightView->SetRedraw(TRUE);
    m_pRightView->Invalidate();
    
    *pResult = 0;
}

void CLeftView::OnExpandAll() 
{
    GetTreeCtrl().SetRedraw(FALSE);
    ExpandBranch(GetTreeCtrl().GetRootItem(), TVE_EXPAND);
    GetTreeCtrl().SetRedraw(TRUE);
}

void CLeftView::OnCollapseAll() 
{
    GetTreeCtrl().SetRedraw(FALSE);
    ExpandBranch(GetTreeCtrl().GetRootItem(), TVE_COLLAPSE);
    GetTreeCtrl().SetRedraw(TRUE);
}

void CLeftView::ExpandBranch(HTREEITEM hItem, UINT nCode)
{
    GetTreeCtrl().Expand(hItem, nCode);

    HTREEITEM hChild = GetTreeCtrl().GetChildItem(hItem);
    while (hChild)
    {
        ExpandBranch(hChild, nCode);
        hChild = GetTreeCtrl().GetNextSiblingItem(hChild);
    }    
}

