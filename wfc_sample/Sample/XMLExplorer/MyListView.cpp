// MyListView.cpp : implementation file
//

#include "stdafx.h"
#include "XMLExplorer.h"
#include "MyListView.h"
#include "CXMLExplorerDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CListView)

CMyListView::CMyListView()
{
}

CMyListView::~CMyListView()
{
}

BEGIN_MESSAGE_MAP(CMyListView, CListView)
	//{{AFX_MSG_MAP(CMyListView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListView drawing

void CMyListView::OnDraw(CDC* /* pDC */ )
{
	//CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyListView message handlers

int CMyListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   lpCreateStruct->style |= LVS_REPORT;

   if ( CListView::OnCreate( lpCreateStruct ) == (-1) )
   {
      return( -1 );
   }

   CXMLExplorerDocument * document_p = (CXMLExplorerDocument *) GetDocument();

   document_p->ListView = this;

   return( 0 );
}

BOOL CMyListView::AddColumn( LPCTSTR column_name,
                             int column_number,
                             int width,
                             int sub_item,
                             int mask,
                             int format )
{
   CListCtrl& list_control = GetListCtrl();

   LV_COLUMN list_view_column;

   list_view_column.mask    = mask;
   list_view_column.fmt     = format;
   list_view_column.pszText = (LPTSTR) column_name;

   if ( width == (-1) )
   {
      list_view_column.cx = list_control.GetStringWidth( column_name ) + 15;
   }
   else
   {
      list_view_column.cx = width;
   }

   if ( mask & LVCF_SUBITEM )
   {
      if ( sub_item != (-1) )
      {
         list_view_column.iSubItem = sub_item;
      }
      else
      {
         list_view_column.iSubItem = column_number;
      }
   }

   return( list_control.InsertColumn( column_number, &list_view_column ) );
}

BOOL CMyListView::AddItem( int     row_number,
                           int     column_number,
                           LPCTSTR text,
                           int     image_index )
{
   LV_ITEM list_view_item;

   list_view_item.mask     = LVIF_TEXT;
   list_view_item.iItem    = row_number;
   list_view_item.iSubItem = column_number;
   list_view_item.pszText  = (LPTSTR) text;

   if ( image_index != (-1) )
   {
      list_view_item.mask  |= LVIF_IMAGE;
      list_view_item.iImage = image_index;
   }

   CListCtrl& list_control = GetListCtrl();

   if ( column_number == 0 )
   {
      return( list_control.InsertItem( &list_view_item ) );   
   }
   else
   {
      return( list_control.SetItem( &list_view_item ) );
   }
}

void CMyListView::Empty( void )
{
   CListCtrl& list_control = GetListCtrl();

   list_control.DeleteAllItems();

   while( list_control.DeleteColumn( 0 ) )
   {
      ;
   }

   UpdateWindow();
}

void CMyListView::ShowDocument( CExtensibleMarkupLanguageDocument * document_p )
{
   CListCtrl& list_control = GetListCtrl();

   if ( m_CurrentDisplay != CMyTreeView::IT_IS_AN_XML_DOCUMENT )
   {
      m_CurrentDisplay = CMyTreeView::IT_IS_AN_XML_DOCUMENT;

      list_control.DeleteAllItems();
      while( list_control.DeleteColumn( 0 ) );

      AddColumn( TEXT( "Field" ), 0, list_control.GetStringWidth( TEXT( "Parent/Child Separator Character" ) ) + 25 );
      AddColumn( TEXT( "Value" ), 1, list_control.GetStringWidth( TEXT( "WFC_XML_IGNORE_MISSING_XML_DECLARATION" ) ) + 25 );

      AddItem( 0, 0, TEXT( "Number Of Elements" ) );
      AddItem( 1, 0, TEXT( "Number Of Entities" ) );
      AddItem( 2, 0, TEXT( "Parse Options" ) );
      AddItem( 3, 0, TEXT( "Write Options" ) );
      AddItem( 4, 0, TEXT( "Is Standalone?" ) );
      AddItem( 5, 0, TEXT( "Parent/Child Separator Character" ) );
      AddItem( 6, 0, TEXT( "Parse Error Message" ) );
      AddItem( 7, 0, TEXT( "Parse Error Location" ) );
      AddItem( 8, 0, TEXT( "Name of Tag that won't Parse" ) );
      AddItem( 9, 0, TEXT( "Problematic Tag Began At" ) );
   }

   CString item_text;

   item_text.Format( TEXT( "%lu" ), document_p->GetNumberOfElements() );
   AddItem( 0, 1, item_text );

   const CExtensibleMarkupLanguageEntities& entities = document_p->GetEntities();

   item_text.Format( TEXT( "%lu" ), entities.GetSize() );
   AddItem( 1, 1, item_text );

   DWORD options = document_p->GetParseOptions();

   item_text.Empty();

   if ( options & WFC_XML_IGNORE_CASE_IN_XML_DECLARATION )
   {
      item_text = TEXT( "WFC_XML_IGNORE_CASE_IN_XML_DECLARATION" );
   }

   if ( options & WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES" );
   }

   if ( options & WFC_XML_FAIL_ON_ILL_FORMED_ENTITIES )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_FAIL_ON_ILL_FORMED_ENTITIES" );
   }

   if ( options & WFC_XML_IGNORE_ALL_WHITE_SPACE_ELEMENTS )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_IGNORE_ALL_WHITE_SPACE_ELEMENTS" );
   }

   if ( options & WFC_XML_IGNORE_MISSING_XML_DECLARATION )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_IGNORE_MISSING_XML_DECLARATION" );
   }

   if ( options & WFC_XML_DISALLOW_MULTIPLE_ELEMENTS )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_DISALLOW_MULTIPLE_ELEMENTS" );
   }

   if ( options & WFC_XML_LOOSE_COMMENT_PARSING )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_LOOSE_COMMENT_PARSING" );
   }

   if ( options & WFC_XML_ALLOW_AMPERSANDS_IN_ELEMENTS )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_ALLOW_AMPERSANDS_IN_ELEMENTS" );
   }

   AddItem( 2, 1, item_text );

   options = document_p->GetWriteOptions();

   item_text.Empty();

   if ( options & WFC_XML_INCLUDE_TYPE_INFORMATION )
   {
      item_text = TEXT( "WFC_XML_INCLUDE_TYPE_INFORMATION" );
   }

   if ( options & WFC_XML_DONT_OUTPUT_XML_DECLARATION )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_DONT_OUTPUT_XML_DECLARATION" );
   }

   if ( options & WFC_XML_WRITE_AS_UNICODE )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_WRITE_AS_UNICODE" );
   }

   if ( options & WFC_XML_WRITE_AS_BIG_ENDIAN )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_WRITE_AS_BIG_ENDIAN" );
   }

   if ( options & WFC_XML_WRITE_AS_UCS4 )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_WRITE_AS_UCS4" );
   }

   if ( options & WFC_XML_WRITE_AS_UCS4_UNUSUAL_2143 )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_WRITE_AS_UCS4_UNUSUAL_2143" );
   }

   if ( options & WFC_XML_WRITE_AS_UCS4_UNUSUAL_3412 )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_WRITE_AS_UCS4_UNUSUAL_3412" );
   }

   if ( options & WFC_XML_WRITE_AS_ASCII )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_WRITE_AS_ASCII" );
   }

   if ( options & WFC_XML_WRITE_AS_UTF8 )
   {
      if ( item_text.GetLength() > 0 )
      {
         item_text += TEXT( " | " );
      }

      item_text += TEXT( "WFC_XML_WRITE_AS_UTF8" );
   }

   AddItem( 3, 1, item_text );

   if ( document_p->IsStandalone() == FALSE )
   {
      item_text = TEXT( "No" );
   }
   else
   {
      item_text = TEXT( "Yes" );
   }

   AddItem( 4, 1, item_text );

   item_text.Empty();

   item_text += document_p->GetParentChildSeparatorCharacter();

   AddItem( 5, 1, item_text );

   CString tag_name;
   CParsePoint tag_began_at;
   CParsePoint error_location;

   document_p->GetParsingErrorInformation( tag_name, tag_began_at, error_location, &item_text );
   AddItem( 6, 1, item_text );

   item_text.Format( TEXT( "Byte %lu, Line Number %lu, Column %lu" ), error_location.GetIndex(), error_location.GetLineNumber(), error_location.GetLineIndex() );
   AddItem( 7, 1, item_text );

   AddItem( 8, 1, tag_name );

   item_text.Format( TEXT( "Byte %lu, Line Number %lu, Column %lu" ), tag_began_at.GetIndex(), tag_began_at.GetLineNumber(), tag_began_at.GetLineIndex() );
   AddItem( 9, 1, item_text );
}

void CMyListView::ShowElement( CExtensibleMarkupLanguageElement * element_p )
{
   CListCtrl& list_control = GetListCtrl();

   if ( m_CurrentDisplay != CMyTreeView::IT_IS_AN_ELEMENT )
   {
      m_CurrentDisplay = CMyTreeView::IT_IS_AN_ELEMENT;

      list_control.DeleteAllItems();
      while( list_control.DeleteColumn( 0 ) );

      AddColumn( TEXT( "Field" ), 0, list_control.GetStringWidth( TEXT( "Number of Immediate ChildrenWW" ) ) + 25 );
      AddColumn( TEXT( "Value" ), 1, list_control.GetStringWidth( TEXT( "Byte 8888, Line Number 8888, Column 8888" ) ) + 25 );

      AddItem( 0, 0, TEXT( "Total Number Of Children" ) );
      AddItem( 1, 0, TEXT( "Number of Immediate Children" ) );
      AddItem( 2, 0, TEXT( "Type" ) );
      AddItem( 3, 0, TEXT( "Tag" ) );
      AddItem( 4, 0, TEXT( "Complete Name" ) );
      AddItem( 5, 0, TEXT( "Started at" ) );
      AddItem( 6, 0, TEXT( "Ended at" ) );
      AddItem( 7, 0, TEXT( "Is All Whitespace?" ) );
      AddItem( 8, 0, TEXT( "Number of attributes" ) );
      AddItem( 9, 0, TEXT( "Contents" ) );
   }

   CString item_text;

   item_text.Format( TEXT( "%lu" ), element_p->GetTotalNumberOfChildren() );

   AddItem( 0, 1, item_text );

   item_text.Format( TEXT( "%lu" ), element_p->GetNumberOfChildren() );

   AddItem( 1, 1, item_text );

   switch( element_p->GetType() )
   {
      case CExtensibleMarkupLanguageElement::typeUnknown:

         item_text = TEXT( "Unknown" );
         break;

      case CExtensibleMarkupLanguageElement::typeProcessingInstruction:

         item_text = TEXT( "Processing Instruction" );
         break;

      case CExtensibleMarkupLanguageElement::typeComment:

         item_text = TEXT( "Comment" );
         break;

      case CExtensibleMarkupLanguageElement::typeCharacterData:

         item_text = TEXT( "CDATA" );
         break;

      case CExtensibleMarkupLanguageElement::typeElement:

         item_text = TEXT( "Element" );
         break;

      case CExtensibleMarkupLanguageElement::typeTextSegment:

         item_text = TEXT( "Text Segment" );
         break;

      case CExtensibleMarkupLanguageElement::typeMetaData:

         item_text = TEXT( "Meta Data" );
         break;

      default:

         item_text = TEXT( "Really Unknown" );
         break;
   }

   AddItem( 2, 1, item_text );

   element_p->GetTag( item_text );
   AddItem( 3, 1, item_text );

   element_p->GetCompleteName( item_text );
   AddItem( 4, 1, item_text );

   CParsePoint parse_point;

   element_p->GetBeginning( parse_point );

   item_text.Format( TEXT( "Byte %lu, Line Number %lu, Column %lu" ), parse_point.GetIndex(), parse_point.GetLineNumber(), parse_point.GetLineIndex() );
   AddItem( 5, 1, item_text );

   element_p->GetEnding( parse_point );

   item_text.Format( TEXT( "Byte %lu, Line Number %lu, Column %lu" ), parse_point.GetIndex(), parse_point.GetLineNumber(), parse_point.GetLineIndex() );
   AddItem( 6, 1, item_text );

   if ( element_p->IsAllWhiteSpace() == FALSE )
   {
      item_text = TEXT( "No" );
   }
   else
   {
      item_text = TEXT( "Yes" );
   }

   AddItem( 7, 1, item_text );

   item_text.Format( TEXT( "%lu" ), element_p->GetNumberOfAttributes() );
   AddItem( 8, 1, item_text );

   element_p->GetContents( item_text );
   AddItem( 9, 1, item_text );
}

void CMyListView::ShowDefault( void )
{
   CListCtrl& list_control = GetListCtrl();

   m_CurrentDisplay = 9999;

   list_control.DeleteAllItems();
   while( list_control.DeleteColumn( 0 ) );
}

void CMyListView::ShowAttribute( CExtensibleMarkupLanguageAttribute * attribute_p )
{
   CListCtrl& list_control = GetListCtrl();

   if ( m_CurrentDisplay != CMyTreeView::IT_IS_AN_ATTRIBUTE )
   {
      m_CurrentDisplay = CMyTreeView::IT_IS_AN_ATTRIBUTE;

      list_control.DeleteAllItems();
      while( list_control.DeleteColumn( 0 ) );

      AddColumn( TEXT( "Field" ), 0, list_control.GetStringWidth( TEXT( "Total Number Of Children" ) ) + 25 );
      AddColumn( TEXT( "Value" ), 1, list_control.GetStringWidth( TEXT( "Byte 8888, Line Number 8888, Column 8888" ) ) + 25 );

      AddItem( 0, 0, TEXT( "Name" ) );
      AddItem( 1, 0, TEXT( "Value" ) );
   }

   AddItem( 0, 1, attribute_p->Name  );
   AddItem( 1, 1, attribute_p->Value );
}

void CMyListView::ShowListOfAttributes( CExtensibleMarkupLanguageElement * element_p )
{
   CListCtrl& list_control = GetListCtrl();

   if ( m_CurrentDisplay != CMyTreeView::IT_IS_A_LIST_OF_ATTRIBUTES )
   {
      m_CurrentDisplay = CMyTreeView::IT_IS_A_LIST_OF_ATTRIBUTES;

      list_control.DeleteAllItems();
      while( list_control.DeleteColumn( 0 ) );

      AddColumn( TEXT( "Field" ), 0, list_control.GetStringWidth( TEXT( "Total Number Of Children" ) ) + 25 );
      AddColumn( TEXT( "Value" ), 1, list_control.GetStringWidth( TEXT( "Byte 8888, Line Number 8888, Column 8888" ) ) + 25 );

      AddItem( 0, 0, TEXT( "Number Of Attributes" ) );
   }

   CString item_text;

   item_text.Format( TEXT( "%lu" ), element_p->GetNumberOfAttributes() );

   AddItem( 0, 1, item_text );
}

void CMyListView::ShowEntities( CExtensibleMarkupLanguageDocument * xml_p )
{
   CListCtrl& list_control = GetListCtrl();

   if ( m_CurrentDisplay != CMyTreeView::IT_IS_AN_ENTITY )
   {
      m_CurrentDisplay = CMyTreeView::IT_IS_AN_ENTITY;

      list_control.DeleteAllItems();
      while( list_control.DeleteColumn( 0 ) );

      AddColumn( TEXT( "Entity" ), 0, list_control.GetStringWidth( TEXT( "Resolves ToWW" ) ) + 25 );
      AddColumn( TEXT( "Resolves To" ), 1, list_control.GetStringWidth( TEXT( "Byte 8888, Line Number 8888, Column 8888" ) ) + 25 );
   }

   CString item_text;

   const CExtensibleMarkupLanguageEntities& entities = xml_p->GetEntities();

   DWORD enumerator = 0;

   if ( entities.Enumerate( enumerator ) == TRUE )
   {
      CString entity;
      CString value;

      int item_index = 0;

      while( entities.GetNext( enumerator, entity, value ) == TRUE )
      {
         AddItem( item_index, 0, entity );
         AddItem( item_index, 1, value );
         item_index++;
      }
   }
}
