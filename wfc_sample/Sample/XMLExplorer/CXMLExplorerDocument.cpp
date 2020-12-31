// CXMLExplorerDocument.cpp : implementation of the CXMLExplorerDocument class
//

#include "stdafx.h"
#include "XMLExplorer.h"

#include "CXMLExplorerDocument.h"
#include "MyTreeView.h"
#include "MyListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerDocument

IMPLEMENT_DYNCREATE(CXMLExplorerDocument, CDocument)

BEGIN_MESSAGE_MAP(CXMLExplorerDocument, CDocument)
	//{{AFX_MSG_MAP(CXMLExplorerDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerDocument construction/destruction

CXMLExplorerDocument::CXMLExplorerDocument()
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::CXMLExplorerDocument()" ) );
   XML = NULL;
}

CXMLExplorerDocument::~CXMLExplorerDocument()
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::~CXMLExplorerDocument()" ) );

   if ( XML != NULL )
   {
      delete XML;
      XML = NULL;
   }
}

BOOL CXMLExplorerDocument::OnNewDocument()
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::OnNewDocument()" ) );

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////
// CXMLExplorerDocument serialization

void CXMLExplorerDocument::Serialize(CArchive& ar)
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
// CXMLExplorerDocument diagnostics

#ifdef _DEBUG
void CXMLExplorerDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CXMLExplorerDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerDocument commands

BOOL CXMLExplorerDocument::OnOpenDocument( LPCTSTR filename )
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::OnOpenDocument()" ) );

   if ( ! CDocument::OnOpenDocument( filename ) )
   {
      return( FALSE );
   }

   if ( XML == NULL )
   {
      XML = new CExtensibleMarkupLanguageDocument;
   }

   CFile file;

   if ( file.Open( filename, CFile::modeRead ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), filename );
      WFCTRACEERROR( GetLastError() );
      return( FALSE );
   }

   CByteArray bytes;

   bytes.SetSize( file.GetLength() );

   file.Read( bytes.GetData(), bytes.GetSize() );
   file.Close();

   CDataParser parser;

   parser.Initialize( &bytes, FALSE );

   DWORD parsing_options = XML->GetParseOptions();

   parsing_options |= WFC_XML_LOOSE_COMMENT_PARSING;

   XML->SetParseOptions( parsing_options );

   XML->Empty();

   WFCTRACELEVELON( 31 );

   if ( XML->Parse( parser ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't parse" ) );
      TreeView->PostMessage( WM_COMMAND, 99782, (LPARAM) XML );
      return( FALSE );
   }

   WFCTRACEVAL( TEXT( "XML parsed OK " ), filename );

   // TreeView->Populate( XML );

   // We post a message so CDocument's document path name will be filled in when we need it
   TreeView->PostMessage( WM_COMMAND, 99782, (LPARAM) XML );

   return( TRUE );
}

void CXMLExplorerDocument::ShowDocument( CExtensibleMarkupLanguageDocument * xml_p )
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::ShowDocument()" ) );

   if ( ListView != NULL && xml_p != NULL )
   {
      ListView->ShowDocument( xml_p );
   }
}

void CXMLExplorerDocument::ShowElement( CExtensibleMarkupLanguageElement * element_p )
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::ShowElement()" ) );

   if ( ListView != NULL && element_p != NULL )
   {
      ListView->ShowElement( element_p );
   }
}

void CXMLExplorerDocument::ShowEntities( CExtensibleMarkupLanguageDocument * xml_p )
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::ShowEntities()" ) );

   if ( ListView != NULL && xml_p != NULL )
   {
      ListView->ShowEntities( xml_p );
   }
}

void CXMLExplorerDocument::ShowDefault( void )
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::ShowDefault()" ) );

   if ( ListView != NULL )
   {
      ListView->ShowDefault();
   }
}

void CXMLExplorerDocument::ShowAttribute( CExtensibleMarkupLanguageAttribute * xml_p )
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::ShowAttribute()" ) );

   if ( ListView != NULL && xml_p != NULL )
   {
      ListView->ShowAttribute( xml_p );
   }
}

void CXMLExplorerDocument::ShowListOfAttributes( CExtensibleMarkupLanguageElement * xml_p )
{
   WFCTRACEINIT( TEXT( "CXMLExplorerDocument::ShowListOfAttributes()" ) );

   if ( ListView != NULL && xml_p != NULL )
   {
      ListView->ShowListOfAttributes( xml_p );
   }
}

