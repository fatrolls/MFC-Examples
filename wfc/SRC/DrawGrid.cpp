#include <wfc.h>
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: drawgrid.cpp $
** $Revision: 14 $
** $Modtime: 1/05/00 3:37a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CDrawingObjectGrid, CObject,            1 )
IMPLEMENT_SERIAL( CLabeledGrid,       CDrawingObjectGrid, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG )
#define new DEBUG_NEW
#endif // _DEBUG

CDrawingObjectGrid::CDrawingObjectGrid()
{
   m_Initialize();
}

CDrawingObjectGrid::CDrawingObjectGrid( DWORD number_of_rows, DWORD number_of_columns )
{
   m_Initialize();
   SetSize( number_of_rows, number_of_columns );
}

CDrawingObjectGrid::~CDrawingObjectGrid()
{
   RemoveAll();
}

void CDrawingObjectGrid::Draw( CDC& device_context )
{
   int index              = 0;
   int number_of_elements = m_ObjectArray.GetSize();

   CRectangle *object_p = (CRectangle *) NULL;

   while( index < number_of_elements )
   {
      object_p = (CRectangle *) m_ObjectArray[ index ];
      
      if ( object_p != NULL )
      {
         object_p->Draw( device_context );
      }

      index++;
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CDrawingObjectGrid::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_Name = \""            ) << m_Name              << TEXT( "\"\n" );
   dump_context << TEXT( "   m_NumberOfRows = "      ) << m_NumberOfRows      << TEXT( "\n" );
   dump_context << TEXT( "   m_NumberOfColumns = "   ) << m_NumberOfColumns   << TEXT( "\n" );
   dump_context << TEXT( "   m_VerticalSpacing = "   ) << m_VerticalSpacing   << TEXT( "\n" );
   dump_context << TEXT( "   m_HorizontalSpacing = " ) << m_HorizontalSpacing << TEXT( "\n" );

   m_ObjectArray.Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

CRectangle*& CDrawingObjectGrid::ElementAt( DWORD row_number, DWORD column_number )
{
   return( (CRectangle *&) m_ObjectArray.ElementAt( ( row_number * m_NumberOfColumns ) + column_number ) );
}

CRectangle* CDrawingObjectGrid::GetAt( DWORD row_number, DWORD column_number )
{
   return( (CRectangle *) m_ObjectArray.ElementAt( ( row_number * m_NumberOfColumns ) + column_number ) );
}

DWORD CDrawingObjectGrid::GetHeight( void ) const
{
   DWORD height = 0;
   DWORD index  = 0;

   CRectangle *object_p = (CRectangle *) NULL;

   while( index < m_NumberOfRows )
   {
      object_p = (CRectangle *) m_ObjectArray[ index ];

      if ( object_p != NULL )
      {
         height += object_p->GetHeight();
         height += m_VerticalSpacing;
      }

      index++;
   }

   if ( m_NumberOfRows > 0 )
   {
      height -= m_VerticalSpacing;
   }

   return( height );
}

int CDrawingObjectGrid::GetHorizontalSpacing( void ) const
{
   return( m_HorizontalSpacing );
}

BOOL CDrawingObjectGrid::GetIndexFromPoint( DWORD& _row_index, DWORD& _column_index, const CPoint& point )
{
   DWORD row_index    = 0;
   DWORD column_index = 0;

   CRectangle *object_p = (CRectangle *) NULL;

   CRect rectangle;

   while( row_index < (DWORD) m_NumberOfRows )
   {
      column_index = 0;

      while( column_index < (DWORD) m_NumberOfColumns )
      {
         object_p = GetAt( row_index, column_index );

         if ( object_p != NULL )
         {
            object_p->GetRectangle( rectangle );

            if ( rectangle.PtInRect( point ) != FALSE )
            {
               _row_index    = row_index;
               _column_index = column_index;
               return( TRUE );
            }
         }

         column_index++;
      }

      row_index++;
   }

   return( FALSE );
}

void CDrawingObjectGrid::GetName( CString& name_of_grid ) const
{
   name_of_grid = m_Name;
}

DWORD CDrawingObjectGrid::GetNumberOfColumns( void ) const
{
   return( m_NumberOfColumns );
}

DWORD CDrawingObjectGrid::GetNumberOfRows( void ) const
{
   return( m_NumberOfRows );
}

void CDrawingObjectGrid::GetRectangle( CRect& rectangle ) const
{
   if ( m_ObjectArray[ 0 ] == NULL )
   {
      rectangle.SetRectEmpty();
      return;
   }

   CRectangle *object_p = (CRectangle *) m_ObjectArray[ 0 ];

   if ( object_p == NULL )
   {
      rectangle.SetRectEmpty();
      return;
   }

   CRect object_rectangle;

   object_p->GetRectangle( object_rectangle );

   rectangle.left   = object_rectangle.left;
   rectangle.top    = object_rectangle.top;
   rectangle.right  = rectangle.left + GetWidth();
   rectangle.bottom = rectangle.top  + GetHeight();
}

DWORD CDrawingObjectGrid::GetVerticalSpacing( void ) const
{
   return( m_VerticalSpacing );
}

DWORD CDrawingObjectGrid::GetWidth( void ) const
{
   DWORD width = 0;
   DWORD index = 0;

   CRectangle *object_p = NULL;

   while( index < m_NumberOfColumns )
   {
      object_p = (CRectangle *) m_ObjectArray[ index ];

      if ( object_p != NULL )
      {
         width += object_p->GetWidth();
         width += m_HorizontalSpacing;
      }

      index++;
   }

   if ( m_NumberOfColumns > 0 )
   {
      width -= m_HorizontalSpacing;
   }

   return( width );
}

void CDrawingObjectGrid::m_Initialize( void )
{
   RemoveAll();
   m_VerticalSpacing   = 1;
   m_HorizontalSpacing = 1;
   m_NumberOfRows      = 0;
   m_NumberOfColumns   = 0;

   m_Name.Empty();
}

void CDrawingObjectGrid::RemoveAll( void )
{
   int loop_index         = 0;
   int number_of_elements = m_ObjectArray.GetSize();

   CRectangle * object_p = NULL;

   while( loop_index < number_of_elements )
   {
      object_p = (CRectangle *) m_ObjectArray[ loop_index ];

      if ( object_p != NULL )
      {
         delete object_p;
      }

      m_ObjectArray.SetAt( loop_index, NULL );

      loop_index++;
   }

   m_ObjectArray.RemoveAll();

   m_NumberOfRows    = 0;
   m_NumberOfColumns = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CDrawingObjectGrid::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << m_NumberOfRows;
      archive << m_NumberOfColumns;
      archive << m_VerticalSpacing;
      archive << m_HorizontalSpacing;
      archive << m_Name;
   }
   else
   {
      archive >> m_NumberOfRows;
      archive >> m_NumberOfColumns;
      archive >> m_VerticalSpacing;
      archive >> m_HorizontalSpacing;
      archive >> m_Name;
   }

   m_ObjectArray.Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

void CDrawingObjectGrid::SetAt( DWORD row_number, DWORD column_number, CRectangle *new_element )
{
   DWORD index = ( row_number * m_NumberOfColumns ) + column_number;

   CRectangle *object_p = (CRectangle *) m_ObjectArray[ index ];

   if ( object_p != NULL )
   {
      if ( object_p == new_element )
      {
         return;
      }
      else
      {
         delete object_p;
      }
   }

   m_ObjectArray[ index ] = new_element;
}

void CDrawingObjectGrid::SetFillColor( DWORD row_number, DWORD column_number, COLORREF color )
{
   CRectangle *object_p = GetAt( row_number, column_number );

   if ( object_p != NULL )
   {
      object_p->SetFillColor( color );
   }
}

void CDrawingObjectGrid::SetHorizontalSpacing( DWORD horizontal_spacing )
{
   m_HorizontalSpacing = horizontal_spacing;
}

void CDrawingObjectGrid::SetLineColor( DWORD row_number, DWORD column_number, COLORREF color )
{
   CRectangle *object_p = GetAt( row_number, column_number );

   if ( object_p != NULL )
   {
      object_p->SetLineColor( color );
   }
}

void CDrawingObjectGrid::SetName( LPCTSTR name_of_grid )
{
   if ( name_of_grid != NULL )
   {
      m_Name = name_of_grid;
   }
   else
   {
      m_Name.Empty();
   }
}

void CDrawingObjectGrid::SetRectangle( const CRect& source )
{
   if ( m_ObjectArray[ 0 ] == NULL )
   {
      return;
   }

   CRectangle *object_p = (CRectangle *) m_ObjectArray[ 0 ];

   if ( object_p == NULL )
   {
      return;
   }

   DWORD vertical_size   = object_p->GetHeight();
   DWORD horizontal_size = object_p->GetWidth();

   DWORD vertical_location   = source.top;
   DWORD horizontal_location = source.left;

   DWORD column_index = 0;
   DWORD row_index    = 0;

   CPoint point;

   while( row_index < m_NumberOfRows )
   {
      column_index        = 0;
      horizontal_location = source.left;

      while( column_index < m_NumberOfColumns )
      {
         point.x = horizontal_location;
         point.y = vertical_location;

         object_p = GetAt( row_index, column_index );

         if ( object_p != NULL )
         {
            object_p->SetLocation( point );
         }

         horizontal_location += (horizontal_size + m_HorizontalSpacing );
         column_index++;
      }

      vertical_location += ( vertical_size + m_VerticalSpacing );
      row_index++;
   }
}

void CDrawingObjectGrid::SetSize( DWORD number_of_rows, DWORD number_of_columns )
{
   RemoveAll();

   m_NumberOfRows    = number_of_rows;
   m_NumberOfColumns = number_of_columns;
   m_ObjectArray.SetSize( m_NumberOfRows * m_NumberOfColumns );
}

void CDrawingObjectGrid::SetVerticalSpacing( DWORD vertical_spacing )
{
   m_VerticalSpacing = vertical_spacing;
}

/*
** And now for some labels
*/

CLabeledGrid::CLabeledGrid()
{
   m_Initialize();
}

CLabeledGrid::CLabeledGrid( DWORD number_of_rows, DWORD number_of_columns )
{
   m_Initialize();
   SetSize( number_of_rows, number_of_columns );
}

CLabeledGrid::~CLabeledGrid()
{
   m_RowNamesFont.DeleteObject();
   m_RowsTitleFont.DeleteObject();
   m_ColumnNamesFont.DeleteObject();
   m_ColumnsTitleFont.DeleteObject();
}

void CLabeledGrid::Draw( CDC& device_context )
{
#if defined( _DEBUG )

   if ( m_PrepareForPaintingWasCalled == FALSE )
   {
      WFCLTRACEINIT( TEXT( "CLabeledGrid::Draw()" ) );
      WFCTRACE( TEXT( "PrepareForPainting() has not been called, you will probably get goofy looking output." ) );
   }

#endif // _DEBUG

   /*
   ** Go draw the CRectangles...
   */

   CDrawingObjectGrid::Draw( device_context );

   int x_coordinate         = 0;
   int y_coordinate         = 0;
   int object_height        = 0;
   int object_width         = 0;
   int label_height         = 0;
   int label_width          = 0;
   int column_labels_offset = 0;
   int row_labels_offset    = 0;

   CRectangle *rectangle_p = NULL;

   CRect rect;

   CString name;

   CSize size;

   DWORD index = 0;

   CFont *old_font = (CFont *) NULL;

   CString grid_name;

   rectangle_p = GetAt( 0, 0 );
   rectangle_p->GetRectangle( rect );

   if ( m_LabelOptions & LABELED_GRID_ROW_NAMES )
   {
      index = 0;

      // Use the new font

      old_font = device_context.SelectObject( &m_RowNamesFont );

      while( index < m_NumberOfRows )
      {
         rectangle_p = GetAt( index, 0 );

         rectangle_p->GetRectangle( rect );

         /*
         ** Get the rectangle for the actual drawing objects...
         **
         **                rect.left (x_coordinate)
         **                |
         **                v
         **     rect.top ->+-----+   +-----+   +-----+
         ** (y_coordinate) |     |   |     |   |     |
         **                | 0,0 |   | 0,1 |   | 0,2 |
         **                |     |   |     |   |     |
         **                +-----+   +-----+   +-----+
         **
         **                +-----+   +-----+   +-----+
         **                |     |   |     |   |     |
         **                | 1,0 |   | 1,1 |   | 1,2 |
         **                |     |   |     |   |     |
         **                +-----+   +-----+   +-----+
         **
         **                +-----+   +-----+   +-----+
         **                |     |   |     |   |     |
         **                | 2,0 |   | 2,1 |   | 2,2 |
         **                |     |   |     |   |     |
         **                +-----+   +-----+   +-----+
         */

         x_coordinate = rect.left;
         y_coordinate = rect.top;

         /*
         ** Move the x_coordinate to the left to make room for the longest row title (the longest row title was determined
         ** in the call to PrepareForPainting().
         **
         ** Horizontal Spacing is the distance betweeen drawing objects in the grid:
         **
         **                        m_HorizontalSpacing
         **                        |
         **                        v
         **                       |-|
         **                +-----+   +-----+   +-----+
         **                |     |   |     |   |     |
         **                | 0,0 |   | 0,1 |   | 0,2 |
         **                |     |   |     |   |     |
         **                +-----+   +-----+   +-----+
         **
         **                +-----+   +-----+   +-----+
         **                |     |   |     |   |     |
         **                | 1,0 |   | 1,1 |   | 1,2 |
         **                |     |   |     |   |     |
         **                +-----+   +-----+   +-----+
         **
         **                +-----+   +-----+   +-----+
         **                |     |   |     |   |     |
         **                | 2,0 |   | 2,1 |   | 2,2 |
         **                |     |   |     |   |     |
         **                +-----+   +-----+   +-----+
         */

         x_coordinate -= ( m_NumberOfLogicalUnitsInLongestRowName + ( m_HorizontalSpacing * 2 ) + 1 );

         /*
         ** Try to vertically center the row label in the space provided by the height of the object
         */

         GetRowName( index, name );

         size = device_context.GetTextExtent( name, name.GetLength() );

         label_height  = size.cy;
         object_height = rect.Height();

         y_coordinate += ( object_height / 2 );
         y_coordinate -= ( label_height  / 2 );

         /*
         ** Make sure we didn't go above the object
         */

         if ( y_coordinate < rect.top )
         {
            y_coordinate = rect.top;
         }

         /*
         ** Now store where we are in case we have to paint the rows title
         */

         row_labels_offset = x_coordinate - ( m_HorizontalSpacing + 1 );

         device_context.TextOut( x_coordinate, y_coordinate, name );

         index++;
      }

      // Put back the original font

      device_context.SelectObject( old_font );
      old_font = NULL;
   }

   if ( m_LabelOptions & LABELED_GRID_COLUMN_NAMES )
   {
      index = 0;

      old_font = device_context.SelectObject( &m_ColumnNamesFont );

      while( index < m_NumberOfColumns )
      {
         rectangle_p = GetAt( 0, index );

         rectangle_p->GetRectangle( rect );

         GetColumnName( index, name );

         /*
         ** Try to center the label
         */

         x_coordinate = rect.left;

         size = device_context.GetTextExtent( name, name.GetLength() );

         column_labels_offset = m_VerticalSpacing + size.cy + 1;
         y_coordinate = rect.top - column_labels_offset;

         if ( y_coordinate < 0 )
         {
            y_coordinate = 0;
         }
         
         label_width  = size.cx;
         object_width = rect.Width();

         x_coordinate += ( object_width / 2 );
         x_coordinate -= ( label_width  / 2 );

         if ( x_coordinate < rect.left )
         {
            x_coordinate = rect.left;
         }

         device_context.TextOut( x_coordinate, y_coordinate, name );

         index++;
      }

      // Put back the original font

      device_context.SelectObject( old_font );
      old_font = NULL;
   }

   if ( m_LabelOptions & LABELED_GRID_COLUMNS_TITLE )
   {
      /*
      ** Get the rectangle for the entire grid
      */

      GetRectangle( rect );

      x_coordinate  = rect.left;
      x_coordinate += rect.Width() / 2;
      x_coordinate -= m_NumberOfLogicalUnitsInColumnsTitle / 2;

      GetColumnsTitle( name );

      old_font = device_context.SelectObject( &m_ColumnsTitleFont );

      size = device_context.GetTextExtent( name, name.GetLength() );
      
      y_coordinate = rect.top - ( size.cy + column_labels_offset + m_VerticalSpacing + 1 );

      if ( y_coordinate < 0 )
      {
         y_coordinate = 0;
      }

      device_context.TextOut( x_coordinate, y_coordinate, name );

      // Put back the original font

      device_context.SelectObject( old_font );
      old_font = NULL;
   }

   if ( m_LabelOptions & LABELED_GRID_ROWS_TITLE )
   {
      /*
      ** Get the rectangle for the entire grid
      */

      GetRectangle( rect );

      /*
      ** Get the rectangle for the actual drawing objects...
      **
      **                rect.left (x_coordinate)
      **                |
      **                v
      **                +-----+   +-----+   +-----+
      **                |     |   |     |   |     |
      **                | 0,0 |   | 0,1 |   | 0,2 |
      **                |     |   |     |   |     |
      **                +-----+   +-----+   +-----+
      **
      **                +-----+   +-----+   +-----+
      **                |     |   |     |   |     |
      **                | 1,0 |   | 1,1 |   | 1,2 |
      **                |     |   |     |   |     |
      **                +-----+   +-----+   +-----+
      **
      **                +-----+   +-----+   +-----+
      **                |     |   |     |   |     |
      **                | 2,0 |   | 2,1 |   | 2,2 |
      **                |     |   |     |   |     |
      **  rect.bottom ->+-----+   +-----+   +-----+
      **  (y_coordinate)
      */

      x_coordinate = rect.left;
      y_coordinate = rect.bottom;

      GetRowsTitle( name );

      old_font = device_context.SelectObject( &m_RowsTitleFont );

      size = device_context.GetTextExtent( name, name.GetLength() );

      /*
      ** Now this is a little weird, remember that the rows title is turned so that it runs from the bottom
      ** of the grid to the top. This means we need to move to the left of the grid by the number of logical
      ** units in the *height* of the title. Usually we don't care about the height of a title when dealing
      ** in the x-axis but since we turned the font so it will print vertically, the height of the title 
      ** becomes the width (strange but true...).
      */

      label_height = size.cy;

      //x_coordinate -= ( row_labels_offset + m_HorizontalSpacing + label_height + 1 );
      x_coordinate -= ( row_labels_offset + label_height + m_HorizontalSpacing );

      y_coordinate -= rect.Height() / 2;
      y_coordinate += m_NumberOfLogicalUnitsInRowsTitle / 2;

      device_context.TextOut( x_coordinate, y_coordinate, name );

      // Put back the original font

      device_context.SelectObject( old_font );
      old_font = NULL;
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CLabeledGrid::Dump( CDumpContext& dump_context ) const
{
   CDrawingObjectGrid::Dump( dump_context );

   dump_context << TEXT( "m_ColumnNames is" );
   m_ColumnNames.Dump( dump_context );
   
   dump_context << TEXT( "m_RowNames is" );
   m_RowNames.Dump( dump_context );

   dump_context << TEXT( "m_RowsTitle                               = \"" ) << m_RowsTitle                               << TEXT( "\"\n" );
   dump_context << TEXT( "m_ColumnsTitle                            = \"" ) << m_ColumnsTitle                            << TEXT( "\"\n" );
   dump_context << TEXT( "m_ColumnFontSize                          = "   ) << m_ColumnFontSize                          << TEXT( "\n" );
   dump_context << TEXT( "m_ColumnsTitleFontSize                    = "   ) << m_ColumnsTitleFontSize                    << TEXT( "\n" );
   dump_context << TEXT( "m_RowFontSize                             = "   ) << m_RowFontSize                             << TEXT( "\n" );
   dump_context << TEXT( "m_RowsTitleFontSize                       = "   ) << m_RowsTitleFontSize                       << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfLogicalUnitsInLongestRowName    = "   ) << m_NumberOfLogicalUnitsInLongestRowName    << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfLogicalUnitsInLongestColumnName = "   ) << m_NumberOfLogicalUnitsInLongestColumnName << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfLogicalUnitsInRowsTitle         = "   ) << m_NumberOfLogicalUnitsInRowsTitle         << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfLogicalUnitsInColumnsTitle      = "   ) << m_NumberOfLogicalUnitsInColumnsTitle      << TEXT( "\n" );
   dump_context << TEXT( "m_LabelOptions                            = "   ) << m_LabelOptions                            << TEXT( "\n" );

   dump_context << TEXT( "m_RowNamesFont is " );
   m_RowNamesFont.Dump( dump_context );

   dump_context << TEXT( "m_ColumnNamesFont is " );
   m_ColumnNamesFont.Dump( dump_context );
   
   dump_context << TEXT( "m_RowsTitleFont is " );
   m_RowsTitleFont.Dump( dump_context );

   dump_context << TEXT( "m_ColumnsTitleFont is " );
   m_ColumnsTitleFont.Dump( dump_context );
}

#endif // _DEBUG

void CLabeledGrid::GetColumnName( DWORD column_number, CString& column_name ) const
{
   if ( column_number >= (DWORD) m_ColumnNames.GetSize() )
   {
      column_name.Empty();
      return;
   }

   column_name = m_ColumnNames[ column_number ];
}

void CLabeledGrid::GetColumnsTitle( CString& columns_title ) const
{
   columns_title = m_ColumnsTitle;
}

void CLabeledGrid::GetRowName( DWORD row_number, CString& row_name ) const
{
   if ( row_number >= (DWORD) m_RowNames.GetSize() )
   {
      row_name.Empty();
      return;
   }

   row_name = m_RowNames[ row_number ];
}

void CLabeledGrid::GetRowsTitle( CString& rows_title ) const
{
   rows_title = m_RowsTitle;
}

void CLabeledGrid::m_Initialize( void )
{
   m_ColumnFontSize                          = 0;
   m_ColumnsTitleFontSize                    = 0;
   m_RowFontSize                             = 0;
   m_RowsTitleFontSize                       = 0;
   m_NumberOfLogicalUnitsInLongestRowName    = 0;
   m_NumberOfLogicalUnitsInLongestColumnName = 0;
   m_NumberOfLogicalUnitsInRowsTitle         = 0;
   m_NumberOfLogicalUnitsInColumnsTitle      = 0;
   m_LabelOptions                            = 0;
   m_RowsTitle.Empty();
   m_ColumnsTitle.Empty();

#if defined( _DEBUG )

   m_PrepareForPaintingWasCalled = FALSE;

#endif // _DEBUG
}

void CLabeledGrid::m_SetColumnFontSize( CDC& device_context, DWORD font_size )
{
   WFCLTRACEINIT( TEXT( "CLabeledGrid::m_SetColumnFontSize()" ) );

   m_ColumnFontSize = font_size;

   TRY
   {
      LOGFONT lf;

      ::ZeroMemory( &lf, sizeof( lf ) );

      lf.lfHeight         = -::MulDiv( m_ColumnFontSize, device_context.GetDeviceCaps( LOGPIXELSY ), 72 );
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfQuality        = DEFAULT_QUALITY;
      lf.lfWeight         = FW_NORMAL;
      lf.lfClipPrecision  = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
      lf.lfPitchAndFamily = FF_SWISS;
      lf.lfEscapement     = 0;

      if ( m_ColumnNamesFont.CreateFontIndirect( &lf ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "CreateFontIndirect() failed with " ), ::GetLastError() );
      }
   }
   CATCH( CResourceException, e )
   {
      WFCTRACE( TEXT( "CLabeledGrid::m_SetColumnFontSize(), font creation failed" ) );
      return;
   }
   END_CATCH
}

void CLabeledGrid::m_SetColumnsTitleFontSize( CDC& device_context, DWORD font_size )
{
   WFCLTRACEINIT( TEXT( "CLabeledGrid::m_SetColumnsTitleFontSize()" ) );

   m_ColumnsTitleFontSize = font_size;

   TRY
   {
      LOGFONT lf;

      ::ZeroMemory( &lf, sizeof( lf ) );

      lf.lfHeight         = -::MulDiv( m_ColumnsTitleFontSize, device_context.GetDeviceCaps( LOGPIXELSY ), 72 );
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfQuality        = DEFAULT_QUALITY;
      lf.lfWeight         = FW_NORMAL;
      lf.lfClipPrecision  = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
      lf.lfPitchAndFamily = FF_SWISS;
      lf.lfEscapement     = 0;

      if ( m_ColumnsTitleFont.CreateFontIndirect( &lf ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "CreateFontIndirect failed with " ), ::GetLastError() );
      }
   }
   CATCH( CResourceException, e )
   {
      WFCTRACE( TEXT( "CLabeledGrid::m_SetColumnsTitleFontSize(), font creation failed" ) );
      return;
   }
   END_CATCH
}

void CLabeledGrid::m_SetRowFontSize( CDC& device_context, DWORD font_size )
{
   WFCLTRACEINIT( TEXT( "CLabeledGrid::m_SetRowFontSize()" ) );

   m_RowFontSize = font_size;

   TRY
   {
      LOGFONT lf;

      ::ZeroMemory( &lf, sizeof( lf ) );

      lf.lfHeight         = -::MulDiv( m_RowFontSize, device_context.GetDeviceCaps( LOGPIXELSY ), 72 );
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfQuality        = DEFAULT_QUALITY;
      lf.lfWeight         = FW_NORMAL;
      lf.lfClipPrecision  = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
      lf.lfPitchAndFamily = FF_SWISS;
      lf.lfEscapement     = 0;

      if ( m_RowNamesFont.CreateFontIndirect( &lf ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "CreateFontIndirect failed with " ), ::GetLastError() );
      }
   }
   CATCH( CResourceException, e )
   {
      WFCTRACE( TEXT( "CLabeledGrid::m_SetColumnFontSize(), font creation failed" ) );
      return;
   }
   END_CATCH
}

void CLabeledGrid::m_SetRowsTitleFontSize( CDC& device_context, DWORD font_size )
{
   WFCLTRACEINIT( TEXT( "CLabeledGrid::m_SetRowsTitleFontSize()" ) );

   m_RowsTitleFontSize = font_size;

   TRY
   {
      LOGFONT lf;

      ::ZeroMemory( &lf, sizeof( lf ) );

      lf.lfHeight         = -::MulDiv( m_RowsTitleFontSize, device_context.GetDeviceCaps( LOGPIXELSY ), 72 );
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfQuality        = DEFAULT_QUALITY;
      lf.lfWeight         = FW_NORMAL;
      lf.lfClipPrecision  = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
      lf.lfPitchAndFamily = FF_SWISS;
      lf.lfEscapement     = 900;

      if ( m_RowsTitleFont.CreateFontIndirect( &lf ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "CreateFontIndirect() failed with " ), ::GetLastError() );
      }
   }
   CATCH( CResourceException, e )
   {
      WFCTRACE( TEXT( "CLabeledGrid::m_SetColumnFontSize(), font creation failed" ) );
      return;
   }
   END_CATCH
}

void CLabeledGrid::PrepareForPainting( CDC&  device_context, 
                                       DWORD row_font_size,
                                       DWORD column_font_size,
                                       DWORD rows_title_font_size,
                                       DWORD columns_title_font_size )
{
   m_SetColumnFontSize(       device_context, column_font_size        );
   m_SetRowFontSize(          device_context, row_font_size           );
   m_SetColumnsTitleFontSize( device_context, columns_title_font_size );
   m_SetRowsTitleFontSize(    device_context, rows_title_font_size    );

   CSize size;

   DWORD index         = 0;
   DWORD biggest_value = 0;

   CFont *old_font = (CFont *) NULL;

   old_font = device_context.SelectObject( &m_RowsTitleFont );

   size = device_context.GetTextExtent( m_RowsTitle, m_RowsTitle.GetLength() );

   m_NumberOfLogicalUnitsInRowsTitle = size.cx;

   device_context.SelectObject( &m_ColumnsTitleFont );

   size = device_context.GetTextExtent( m_ColumnsTitle, m_ColumnsTitle.GetLength() );

   m_NumberOfLogicalUnitsInColumnsTitle = size.cx;

   device_context.SelectObject( &m_RowNamesFont );

   CString name;

   while( index < m_NumberOfRows )
   {
      GetRowName( index, name );

      if ( (DWORD) name.GetLength() > biggest_value )
      {
         size = device_context.GetTextExtent( name, name.GetLength() );
      }

      index++;
   }

   m_NumberOfLogicalUnitsInLongestRowName = size.cx;

   index         = 0;
   biggest_value = 0;

   device_context.SelectObject( &m_ColumnNamesFont );

   while( index < m_NumberOfColumns )
   {
      GetColumnName( index, name );

      if ( (DWORD) name.GetLength() > biggest_value )
      {
         size = device_context.GetTextExtent( name, name.GetLength() );
      }

      index++;
   }

   m_NumberOfLogicalUnitsInLongestColumnName = size.cx;

   device_context.SelectObject( old_font );

#if defined( _DEBUG )

   m_PrepareForPaintingWasCalled = TRUE;

#endif // _DEBUG
}

void CLabeledGrid::RemoveAll()
{
   CDrawingObjectGrid::RemoveAll();

   m_ColumnNames.RemoveAll();
   m_RowNames.RemoveAll();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CLabeledGrid::Serialize( CArchive& archive )
{
   CDrawingObjectGrid::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << m_ColumnsTitle;
      archive << m_RowsTitle;
   }
   else
   {
      archive >> m_ColumnsTitle;
      archive >> m_RowsTitle;
   }

   m_ColumnNames.Serialize( archive );
   m_RowNames.Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

void CLabeledGrid::SetColumnName( DWORD column_number, LPCTSTR column_name )
{
   if ( column_number > m_NumberOfColumns )
   {
      return;
   }

   if ( column_name == NULL )
   {
      m_ColumnNames.SetAt( column_number, TEXT( "" ) );
   }
   else
   {
      m_ColumnNames.SetAt( column_number, column_name );
   }
}

void CLabeledGrid::SetColumnsTitle( LPCTSTR columns_title )
{
   if ( columns_title == NULL )
   {
      m_ColumnsTitle.Empty();
   }
   else
   {
      m_ColumnsTitle = columns_title;
   }
}

void CLabeledGrid::SetLabelOptions( DWORD options )
{
   m_LabelOptions = options;
}

void CLabeledGrid::SetRowName( DWORD row_number, LPCTSTR row_name )
{
   if ( row_number > m_NumberOfRows )
   {
      return;
   }

   if ( row_name == NULL )
   {
      m_RowNames.SetAt( row_number, TEXT( "" ) );
   }
   else
   {
      m_RowNames.SetAt( row_number, row_name );
   }
}

void CLabeledGrid::SetRowsTitle( LPCTSTR rows_title )
{
   if ( rows_title == NULL )
   {
      m_RowsTitle.Empty();
   }
   else
   {
      m_RowsTitle = rows_title;
   }
}

void CLabeledGrid::SetSize( DWORD number_of_rows, DWORD number_of_columns )
{
   CDrawingObjectGrid::SetSize( number_of_rows, number_of_columns );

   m_ColumnNames.SetSize( m_NumberOfColumns );
   m_RowNames.SetSize( m_NumberOfRows );
}

#endif // WFC_STL

// End of source
