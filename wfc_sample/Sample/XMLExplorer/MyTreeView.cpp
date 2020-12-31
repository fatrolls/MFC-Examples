// MyTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "XMLExplorer.h"
#include "MyTreeView.h"
#include "CXMLExplorerDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
** Image Identifier to What It Is to Item Data mappings
**
** IMAGE ID                     | WHAT IT IS                 | GetItemData() returns
** -----------------------------+----------------------------+------------------------------------
** IMAGE_ROOT                   | IT_IS_THE_ROOT             |
** IMAGE_TILE_2                 | IT_IS_AN_XML_DOCUMENT      | CExtensibleMarkupLanguageDocument *
** IMAGE_TILE_3                 | IT_IS_AN_ELEMENT           | CExtensibleMarkupLanguageElement *
** IMAGE_PROCESSING_INSTRUCTION | IT_IS_AN_ELEMENT           | CExtensibleMarkupLanguageElement *
** IMAGE_TEXT_SEGMENT           | IT_IS_AN_ELEMENT           | CExtensibleMarkupLanguageElement *
** IMAGE_LIST_OF_ENTITIES       | IT_IS_AN_ELEMENT           | CExtensibleMarkupLanguageDocument *
** IMAGE_ENTITY                 | IT_IS_AN_ELEMENT           | CExtensibleMarkupLanguageElement *
** IMAGE_ATTRIBUTES             | IT_IS_A_LIST_OF_ATTRIBUTES | CExtensibleMarkupLanguageElement *
** IMAGE_ATTRIBUTE              | IT_IS_AN_AN_ATTRIBUTE      | CExtensibleMarkupLanguageAttribute *
** IMAGE_META_DATA              | IT_IS_AN_ELEMENT           | CExtensibleMarkupLanguageElement *
*/

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{
   WFCTRACEINIT( TEXT( "CMyTreeView::CMyTreeView()" ) );
}

CMyTreeView::~CMyTreeView()
{
   WFCTRACEINIT( TEXT( "CMyTreeView::~CMyTreeView()" ) );
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	//{{AFX_MSG_MAP(CMyTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelectionChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView drawing

void CMyTreeView::OnDraw(CDC* /* pDC */ )
{
	//CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView diagnostics

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView message handlers

int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   lpCreateStruct->style |= ( TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT );

   if ( CTreeView::OnCreate( lpCreateStruct ) == (-1) )
   {
      return( -1 );
   }

   CXMLExplorerDocument * document_p = (CXMLExplorerDocument *) GetDocument();

   ASSERT( document_p != NULL );

   document_p->TreeView = this;

   ImageList.Create( IDB_IMAGELIST, 16, 0, RGB( 255, 0, 255 ) );
   ImageList.SetBkColor( GetSysColor( COLOR_WINDOW ) );

   CTreeCtrl& tree_control = GetTreeCtrl();

   tree_control.SetImageList( &ImageList, TVSIL_NORMAL );

   UpdateWindow();

   RootItem = tree_control.InsertItem( TEXT( "XML Parser" ), IMAGE_ROOT, IMAGE_ROOT );

   return( 0 );
}

void CMyTreeView::DeleteChildren( HTREEITEM parent_item )
{
   CTreeCtrl& tree_control = GetTreeCtrl();

   HTREEITEM child_item = (HTREEITEM) NULL;

   child_item = tree_control.GetChildItem( parent_item );

   while( child_item != NULL )
   {
      tree_control.DeleteItem( child_item );
      child_item = tree_control.GetChildItem( parent_item );
   }
}

DWORD CMyTreeView::ImageToWhatItIs( DWORD image_id ) const
{
   WFCTRACEINIT( TEXT( "CMyTreeView::ImageToWhatItIs()" ) );

   switch( image_id )
   {
      case IMAGE_ROOT:

         WFCTRACE( TEXT( "IT_IS_THE_ROOT" ) );
         return( IT_IS_THE_ROOT );

      case IMAGE_TILE_2:

         WFCTRACE( TEXT( "IT_IS_AN_XML_DOCUMENT" ) );
         return( IT_IS_AN_XML_DOCUMENT );

      case IMAGE_TILE_3:
      case IMAGE_PROCESSING_INSTRUCTION:
      case IMAGE_TEXT_SEGMENT:
      case IMAGE_META_DATA:

         WFCTRACE( TEXT( "IT_IS_AN_ELEMENT" ) );
         return( IT_IS_AN_ELEMENT );

      case IMAGE_ATTRIBUTE:

         WFCTRACE( TEXT( "IT_IS_AN_ATTRIBUTE" ) );
         return( IT_IS_AN_ATTRIBUTE );

      case IMAGE_ATTRIBUTES:

         WFCTRACE( TEXT( "IT_IS_A_LIST_OF_ATTRIBUTES" ) );
         return( IT_IS_A_LIST_OF_ATTRIBUTES );

      case IMAGE_LIST_OF_ENTITIES:

         WFCTRACE( TEXT( "IT_IS_AN_ENTITY" ) );
         return( IT_IS_AN_ENTITY );

      default:

         return( 0 );
   }
}

void CMyTreeView::Populate( CExtensibleMarkupLanguageDocument * xml_p )
{
   // Start with an empty tree
   DeleteChildren( RootItem );

   if ( xml_p == NULL )
   {
      return;
   }

   CTreeCtrl& tree_control = GetTreeCtrl();

   HTREEITEM document_item;

   CDocument * document_p = GetDocument();

   document_item = tree_control.InsertItem( document_p->GetPathName(), IMAGE_TILE_2, IMAGE_TILE_2, RootItem );
   tree_control.SetItemData( document_item, (DWORD) xml_p );

   // Add the entities

   AddEntities( tree_control, document_item, xml_p );

   CExtensibleMarkupLanguageElement * element_p = xml_p->GetRootElement();

   AddElement( tree_control, document_item, element_p );
}

void CMyTreeView::AddEntities( CTreeCtrl& tree_control, HTREEITEM parent_item, CExtensibleMarkupLanguageDocument * xml_p )
{
   const CExtensibleMarkupLanguageEntities& entities = xml_p->GetEntities();

   HTREEITEM entities_item = tree_control.InsertItem( TEXT( "Entities" ), IMAGE_LIST_OF_ENTITIES, IMAGE_LIST_OF_ENTITIES, parent_item );
   tree_control.SetItemData( entities_item, (DWORD) xml_p );

   DWORD enumerator = 0;

   if ( entities.Enumerate( enumerator ) == TRUE )
   {
      CString entity;
      CString value;

      while( entities.GetNext( enumerator, entity, value ) == TRUE )
      {
         tree_control.InsertItem( entity, IMAGE_ENTITY, IMAGE_ENTITY, entities_item );
      }
   }
}

void CMyTreeView::AddAttributes( CTreeCtrl& tree_control, HTREEITEM parent_item, CExtensibleMarkupLanguageElement * element_p )
{
   if ( element_p->GetNumberOfAttributes() == 0 )
   {
      return;
   }

   HTREEITEM attributes_item = tree_control.InsertItem( TEXT( "Attributes" ), IMAGE_ATTRIBUTES, IMAGE_ATTRIBUTES, parent_item );
   tree_control.SetItemData( attributes_item, (DWORD) element_p );

   DWORD enumerator = 0;

   if ( element_p->EnumerateAttributes( enumerator ) == TRUE )
   {
      CExtensibleMarkupLanguageAttribute * attribute_p = NULL;

      HTREEITEM attribute_item = NULL;

      while( element_p->GetNextAttribute( enumerator, attribute_p ) != FALSE )
      {
         attribute_item = tree_control.InsertItem( attribute_p->Name, IMAGE_ATTRIBUTE, IMAGE_ATTRIBUTE, attributes_item );
         tree_control.SetItemData( attribute_item, (DWORD) attribute_p );
      }
   }
}

void CMyTreeView::AddElement( CTreeCtrl& tree_control, HTREEITEM parent_item, CExtensibleMarkupLanguageElement * element_p )
{
   WFCTRACEINIT( TEXT( "CMyTreeView::AddElement()" ) );

   if ( element_p == NULL )
   {
      return;
   }

   HTREEITEM element_item;

   CString name;

   element_p->GetTag( name );

   if ( element_p->GetType() == CExtensibleMarkupLanguageElement::typeProcessingInstruction )
   {
      element_p->GetContents( name );
      element_item = tree_control.InsertItem( name, IMAGE_PROCESSING_INSTRUCTION, IMAGE_PROCESSING_INSTRUCTION, parent_item );
   }
   else if ( element_p->GetType() == CExtensibleMarkupLanguageElement::typeTextSegment )
   {
      if ( element_p->IsAllWhiteSpace() == FALSE )
      {
         element_p->GetContents( name );
      }

      element_item = tree_control.InsertItem( name, IMAGE_TEXT_SEGMENT, IMAGE_TEXT_SEGMENT, parent_item );
   }
   else if ( element_p->GetType() == CExtensibleMarkupLanguageElement::typeMetaData )
   {
      element_item = tree_control.InsertItem( name, IMAGE_META_DATA, IMAGE_META_DATA, parent_item );
   }
   else
   {
      element_item = tree_control.InsertItem( name, IMAGE_TILE_3, IMAGE_TILE_3, parent_item );
   }

   tree_control.SetItemData( element_item, (DWORD) element_p );

   // Now let's add any attributes

   AddAttributes( tree_control, element_item, element_p );

   DWORD enumerator = 0;

   if ( element_p->EnumerateChildren( enumerator ) == TRUE )
   {
      CExtensibleMarkupLanguageElement * child_p = NULL;

      while( element_p->GetNextChild( enumerator, child_p ) == TRUE )
      {
         // RECURSE RECURSE RECURSE!!!
         AddElement( tree_control, element_item, child_p );
      }
   }
}

void CMyTreeView::OnSelectionChanged( NMHDR * header_p, LRESULT* pResult )
{
   WFCTRACEINIT( TEXT( "CMyTreeView::OnSelectionChanged()" ) );

	NM_TREEVIEW * tree_view_p = (NM_TREEVIEW*) header_p;

   CTreeCtrl& tree_control = GetTreeCtrl();

   int image_id = 0;
   int unused   = 0;

   tree_control.GetItemImage( tree_view_p->itemNew.hItem, image_id, unused );

   //ITEMHANDLE item_handle = pNMTreeView->itemNew;

   DWORD what_it_is = ImageToWhatItIs( image_id );

   switch( what_it_is )
   {
      case IT_IS_AN_XML_DOCUMENT:

         {
            CExtensibleMarkupLanguageDocument * xml_p = (CExtensibleMarkupLanguageDocument *) tree_control.GetItemData( tree_view_p->itemNew.hItem );

            CXMLExplorerDocument * document_p = (CXMLExplorerDocument *) GetDocument();

            document_p->ShowDocument( xml_p );
         }

         break;

      case IT_IS_AN_ELEMENT:

         {
            CExtensibleMarkupLanguageElement * element_p = (CExtensibleMarkupLanguageElement *) tree_control.GetItemData( tree_view_p->itemNew.hItem );

            CXMLExplorerDocument * document_p = (CXMLExplorerDocument *) GetDocument();

            document_p->ShowElement( element_p );
         }

         break;

      case IT_IS_AN_ATTRIBUTE:

         {
            CExtensibleMarkupLanguageAttribute * attribute_p = (CExtensibleMarkupLanguageAttribute *) tree_control.GetItemData( tree_view_p->itemNew.hItem );

            CXMLExplorerDocument * document_p = (CXMLExplorerDocument *) GetDocument();

            document_p->ShowAttribute( attribute_p );
         }

         break;

      case IT_IS_A_LIST_OF_ATTRIBUTES:

         {
            CExtensibleMarkupLanguageElement * element_p = (CExtensibleMarkupLanguageElement *) tree_control.GetItemData( tree_view_p->itemNew.hItem );

            CXMLExplorerDocument * document_p = (CXMLExplorerDocument *) GetDocument();

            document_p->ShowListOfAttributes( element_p );
         }

         break;

      case IT_IS_AN_ENTITY:

         {
            CExtensibleMarkupLanguageDocument * xml_p = (CExtensibleMarkupLanguageDocument *) tree_control.GetItemData( tree_view_p->itemNew.hItem );

            CXMLExplorerDocument * document_p = (CXMLExplorerDocument *) GetDocument();

            document_p->ShowEntities( xml_p );
         }

         break;

      default:

         {
            CXMLExplorerDocument * document_p = (CXMLExplorerDocument *) GetDocument();

            document_p->ShowDefault();
         }

         break;
   }

	*pResult = 0;
}

BOOL CMyTreeView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
   WFCTRACEINIT( TEXT( "CMyTreeView::OnCommand()" ) );

   if ( wParam == 99782 )
   {
      Populate( (CExtensibleMarkupLanguageDocument *) lParam );
      return( TRUE ); // I handled this message
   }

	return CTreeView::OnCommand(wParam, lParam);
}
