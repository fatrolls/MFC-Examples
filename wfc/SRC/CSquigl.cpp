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
** $Workfile: csquigl.cpp $
** $Revision: 18 $
** $Modtime: 1/04/00 5:24a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CSquiggleData, CObject, 1 )
IMPLEMENT_SERIAL( CSquiggle, CRectangle, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif

/*
** The data that will be squiggle-ized...
*/

// Construction

CSquiggleData::CSquiggleData()
{
   m_Initialize();
}

CSquiggleData::~CSquiggleData()
{
   m_Initialize();
}

// Methods

void CSquiggleData::Copy( const CSquiggleData& source )
{
   Start        = source.Start;
   Stop         = source.Stop;
   Time         = source.Time;
   MinimumValue = source.MinimumValue;
   MaximumValue = source.MaximumValue;
   Data.Copy( source.Data );
}

void CSquiggleData::Copy( const CSquiggleData *source_p )
{
   // A pointer has been passed to us, this cannot be trusted

   try
   {
      Start        = source_p->Start;
      Stop         = source_p->Stop;
      Time         = source_p->Time;
      MinimumValue = source_p->MinimumValue;
      MaximumValue = source_p->MaximumValue;
      Data.Copy( source_p->Data );
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CSquiggleData::Empty( void )
{
   m_Initialize();
}

void CSquiggleData::m_Initialize( void )
{
   Start.Empty();
   Stop.Empty();
   Time = CTime( 0 );
   MinimumValue = 0;
   MaximumValue = 0;
   Data.RemoveAll();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CSquiggleData::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << Start;
      archive << Stop;
      archive << Time;
      archive << MinimumValue;
      archive << MaximumValue;
   }
   else
   {
      archive >> Start;
      archive >> Stop;
      archive >> Time;
      archive >> MinimumValue;
      archive >> MaximumValue;
   }

   Data.Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

WORD CSquiggleData::ValidRange( void )
{
   if ( MinimumValue > MaximumValue )
   {
      WORD temp_word = MaximumValue;
      MaximumValue = MinimumValue;
      MinimumValue = temp_word;
   }

   return( (WORD) ( MaximumValue - MinimumValue ) );
}

// Operators

CSquiggleData& CSquiggleData::operator=( const CSquiggleData& source )
{
   Copy( source );
   return( *this );
}

/*
** The Squiggle that you see on the screen
*/

CSquiggle::CSquiggle()
{
   m_AutomaticallyDelete = FALSE;
   m_PointArray          = (POINT *) NULL;
   m_Initialize();
}

CSquiggle::CSquiggle( DWORD height, DWORD width, const CPoint& location, COLORREF fill_color, COLORREF line_color )
          :CRectangle( height, width, location, fill_color, line_color )
{
   m_AutomaticallyDelete = FALSE;
   m_PointArray          = (POINT *) NULL;
   m_Initialize();
}

CSquiggle::~CSquiggle()
{
   try
   {
      if ( m_PointArray != (POINT *) NULL )
      {
         delete [] m_PointArray;
         m_PointArray = (POINT *) NULL;
      }

      if ( m_AutomaticallyDelete != FALSE )
      {
         delete m_SquiggleData_p;
      }

      m_Initialize();
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CSquiggle::Copy( const CSquiggle *source_p )
{
   // A pointer has been passed to us, do not trust it

   try
   {
      m_Initialize();

      CSquiggleData *data_p = NULL;
      
      try
      {
         data_p = new CSquiggleData;
      }
      catch( ... )
      {
         data_p = NULL;
      }

      if ( data_p == NULL )
      {
         return;
      }

      data_p->Copy( source_p->m_SquiggleData_p );

      SetSquiggleData( data_p, TRUE );

      CRectangle::Copy( source_p );
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CSquiggle::Draw( CDC& device_context )
{
   if ( m_SquiggleData_p == (CSquiggleData *) NULL )
   {
      ASSERT( FALSE );
      return;
   }

   if ( m_DataIsDirty != FALSE )
   {
      PrepareData();
   }

   CBitmap bitmap;

   CDC temporary_device_context;

   CBrush brush( m_FillColor );

   DWORD width  = GetWidth();
   DWORD height = GetHeight();

   BOOL result = bitmap.CreateCompatibleBitmap( &device_context, (int) width, (int) height );

   if ( result == 0 )
   {
      ASSERT( FALSE );
      return;
   }

   result = temporary_device_context.CreateCompatibleDC( &device_context );

   if ( result == 0 )
   {
      ASSERT( FALSE );
      return;
   }

   CBitmap *original_bitmap = temporary_device_context.SelectObject( &bitmap );

   temporary_device_context.FillRect( CRect( 0, 0, (int) width, (int) height ), &brush );

   /*
   ** Draw the grid if we need to
   */

   if ( m_NumberOfXGridLines > 0 || m_NumberOfYGridLines > 0 )
   {
      CPen grid_line_pen( (int) m_GridLineType, 1, m_GridLineColor );

      CPen *original_pen = temporary_device_context.SelectObject( &grid_line_pen );

      /*
      ** Now turn the background color into the same color as our FillRect to prevent
      ** dotted pens from being color-white-color...
      */

      COLORREF original_background_color = temporary_device_context.SetBkColor( m_FillColor );

      int index = 0;

      for( index = 1; index < m_NumberOfXGridLines; index++ )
      {
         temporary_device_context.MoveTo( (int) ( index * width / m_NumberOfXGridLines ), 0            );
         temporary_device_context.LineTo( (int) ( index * width / m_NumberOfXGridLines ), (int) height );
      }

      for( index = 1; index < m_NumberOfYGridLines; index++ )
      {
         temporary_device_context.MoveTo( 0,           (int) ( index * height / m_NumberOfYGridLines ) );
         temporary_device_context.LineTo( (int) width, (int) ( index * height / m_NumberOfYGridLines ) );
      }

      temporary_device_context.SetBkColor( original_background_color );
      temporary_device_context.SelectObject( original_pen );
      grid_line_pen.DeleteObject();
   }

   CPen line_pen( PS_SOLID, (int) m_LineThickness, m_LineColor );

   CPen *original_pen = temporary_device_context.SelectObject( &line_pen );

   temporary_device_context.Polyline( (LPPOINT) m_PointArray, m_NumberOfPoints );

   /*
   ** Copy to the screen
   */

   device_context.BitBlt( m_Location.x, m_Location.y, (int) width, (int) height, &temporary_device_context, 0, 0, SRCCOPY );

   /*
   ** Clean up
   */

   temporary_device_context.SelectObject( original_pen    );
   temporary_device_context.SelectObject( original_bitmap );
   line_pen.DeleteObject();
   bitmap.DeleteObject();
}

void CSquiggle::Empty( void )
{
   m_Initialize();
}

DWORD CSquiggle::GetLineThickness( void ) const
{
   return( m_LineThickness );
}

void CSquiggle::m_Initialize( void )
{
   m_SquiggleData_p     = (CSquiggleData *) NULL;
   m_PointArray         = (POINT *) NULL;
   m_NumberOfPoints     = 0;
   m_NumberOfXGridLines = 0;
   m_NumberOfYGridLines = 0;
   m_GridLineColor      = DARK_GREEN;
   m_LineThickness      = 1;
   m_GridLineType       = PS_DOT;
   m_DataIsDirty        = TRUE;
}

void CSquiggle::PrepareData( void )
{
   if ( m_PointArray == (POINT *) NULL )
   {
      return;
   }

   ASSERT( m_SquiggleData_p != NULL );

   if ( m_SquiggleData_p == NULL )
   {
      return;
   }

   int number_of_data_points = m_NumberOfPoints;

   // Avoid divide by zero errors

   if ( number_of_data_points == 0 )
   {
      number_of_data_points = 1;
   }

   int valid_range = m_SquiggleData_p->ValidRange();

   // Avoid divide by zero errors

   if ( valid_range == 0 )
   {
      valid_range = 1;
   }

   double x_ratio = (double) m_Width  / (double) number_of_data_points;
   double y_ratio = (double) m_Height / (double) valid_range;

   int origin_y = (int) ( (double) m_SquiggleData_p->MaximumValue * y_ratio );

   for ( int index = 0; index < m_NumberOfPoints; index++ )
   {
      m_PointArray[ index ].x = (int) ( (double) index * x_ratio );
      m_PointArray[ index ].y = origin_y - (int) ( (double) m_SquiggleData_p->Data.GetAt( index ) * y_ratio );
   }

   m_DataIsDirty = FALSE;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CSquiggle::Serialize( CArchive& archive )
{
   CRectangle::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << m_NumberOfXGridLines;
      archive << m_NumberOfYGridLines;
      archive << m_GridLineColor;
      archive << m_LineThickness;
      archive << m_GridLineType;

      DWORD do_we_have_data = 0;

      if ( m_SquiggleData_p != (CSquiggleData *) NULL )
      {
         do_we_have_data = 1;
      }

      archive << do_we_have_data;

      if ( do_we_have_data == 1 )
      {
         m_SquiggleData_p->Serialize( archive );
      }
   }
   else
   {
      archive >> m_NumberOfXGridLines;
      archive >> m_NumberOfYGridLines;
      archive >> m_GridLineColor;
      archive >> m_LineThickness;
      archive >> m_GridLineType;

      DWORD is_there_data = 0;

      archive >> is_there_data;

      if ( is_there_data == 1 )
      {
         CSquiggleData *data_p = NULL;
         
         try
         {
            data_p = new CSquiggleData;
         }
         catch( ... )
         {
            data_p = NULL;
         }

         if ( data_p == NULL )
         {
            return;
         }

         data_p->Serialize( archive );

         SetSquiggleData( data_p, TRUE );
      }
   }
}

#endif // WFC_NO_SERIALIZATION

void CSquiggle::SetAutomaticallyDelete( BOOL new_value )
{
   if ( new_value != FALSE )
   {
      m_AutomaticallyDelete = TRUE;
   }
   else
   {
      m_AutomaticallyDelete = FALSE;
   }
}

void CSquiggle::SetDirtyData( BOOL new_value )
{
   if ( new_value != FALSE )
   {
      m_DataIsDirty = TRUE;
   }
   else
   {
      m_DataIsDirty = FALSE;
   }
}

void CSquiggle::SetGridLineColor( COLORREF grid_line_color )
{
   m_GridLineColor = grid_line_color;
}

void CSquiggle::SetGridLineType( DWORD type )
{
   m_GridLineType = type;
}

void CSquiggle::SetHeight( DWORD height )
{
   CRectangle::SetHeight( height );
   m_DataIsDirty = TRUE;
}

void CSquiggle::SetLineThickness( DWORD thickness )
{
   m_LineThickness = thickness;
}

void CSquiggle::SetNumberOfGridLines( WORD number_of_x_lines, WORD number_of_y_lines )
{
   m_NumberOfXGridLines = number_of_x_lines;
   m_NumberOfYGridLines = number_of_y_lines;
}

void CSquiggle::SetSize( const CSize& size )
{
   CRectangle::SetSize( size );
   m_DataIsDirty = TRUE;
}

void CSquiggle::SetSquiggleData( CSquiggleData *source_p, BOOL auto_delete )
{
   // We have been passed a pointer, do not trust it

   try
   {
      if ( m_PointArray != (POINT *) NULL )
      {
         delete [] m_PointArray;
         m_PointArray = (POINT *) NULL;
      }
 
      m_NumberOfPoints = 0;

      if ( m_AutomaticallyDelete != FALSE )
      {
         delete m_SquiggleData_p;
         m_SquiggleData_p = (CSquiggleData *) NULL;
         m_AutomaticallyDelete = FALSE;
      }

      if ( source_p != (CSquiggleData *) NULL )
      {
         m_SquiggleData_p      = source_p;
         m_AutomaticallyDelete = auto_delete;

         m_NumberOfPoints = source_p->Data.GetSize();

         try
         {
            m_PointArray = new POINT[ m_NumberOfPoints ];
         }
         catch( ... )
         {
            m_PointArray = NULL;
         }

         if ( m_PointArray == (POINT *) NULL )
         {
            /*
            ** Out of Memory
            */

            m_NumberOfPoints = 0;
            return;
         }

         m_DataIsDirty = TRUE;
      }
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CSquiggle::SetWidth( DWORD width )
{
   CRectangle::SetWidth( width );
   m_DataIsDirty = TRUE;
}

#endif // WFC_STL

// End of source
