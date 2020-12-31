#include "wfc.h"
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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: Squiggle.cpp $
** $Revision: 4 $
** $Modtime: 3/08/98 3:29p $
*/

void PASCAL fill_data( CSquiggleData *data_p );
void PASCAL fill_constellation( CConstellationData *data_p );

class CMainWindow : public CFrameWnd
{
   public:

      CMainWindow();

      CLabeledGrid Grid;
      CLabeledGrid ConstellationGrid;

   protected:

      afx_msg int  OnCreate( LPCREATESTRUCT cs_p );
      afx_msg void OnPaint();
      afx_msg void OnTimer( UINT id );
      DECLARE_MESSAGE_MAP()
};

CMainWindow::CMainWindow()
{
   int number_of_rows    = 1;
   int number_of_columns = 1;

   Grid.SetSize( number_of_rows, number_of_columns );
   ConstellationGrid.SetSize( number_of_rows, number_of_columns );

   int row_index    = 0;
   int column_index = 0;

   for ( row_index = 0; row_index < number_of_rows; row_index++ )
   {
      for( column_index = 0; column_index < number_of_columns; column_index++ )
      {
         CSquiggle *squiggle_p = new CSquiggle;

         squiggle_p->SetHeight( 240 );
         squiggle_p->SetWidth(  320 );
         squiggle_p->SetLineColor( YELLOW );
         squiggle_p->SetFillColor( BLACK  );
         squiggle_p->SetNumberOfGridLines( 10, 8 );
         squiggle_p->SetLineThickness( 2 );
         squiggle_p->SetGridLineType( PS_SOLID );

         CSquiggleData *data_p = new CSquiggleData;

         data_p->MinimumValue = 1;
         data_p->MaximumValue = 256;
         data_p->Data.SetSize( 256 );

         fill_data( data_p );

         squiggle_p->SetSquiggleData( data_p, TRUE );

         Grid.SetAt( row_index, column_index, squiggle_p );

         // And now for something completely different . . .

         CConstellation *constellation_p = new CConstellation;

         constellation_p->SetHeight( 240 );
         constellation_p->SetWidth(  320 );
         constellation_p->SetLineColor( YELLOW );
         constellation_p->SetFillColor( BLACK  );
         constellation_p->SetNumberOfGridLines( 10, 8 );
         constellation_p->SetLineThickness( 2 );
         constellation_p->SetGridLineType( PS_SOLID );

         CConstellationData *constellation_data_p = new CConstellationData;

         constellation_data_p->MinimumWidthValue  = 1;
         constellation_data_p->MaximumWidthValue  = RAND_MAX;
         constellation_data_p->MinimumHeightValue = 1;
         constellation_data_p->MaximumHeightValue = RAND_MAX;
         constellation_data_p->SetSize( 4096 );

         fill_constellation( constellation_data_p );

         constellation_p->SetData( constellation_data_p, TRUE );

         ConstellationGrid.SetAt( row_index, column_index, constellation_p );
      }
   }

   TCHAR name[ 10 ];

   name[ 0 ] = TEXT( 'A' );
   name[ 1 ] = TEXT( ' ' );
   name[ 2 ] = TEXT( 'R' );
   name[ 3 ] = TEXT( 'o' );
   name[ 4 ] = TEXT( 'w' );
   name[ 5 ] = 0x00;

   for ( row_index = 0; row_index < number_of_rows; row_index++ )
   {
      name[ 0 ] = (TCHAR) ( TEXT( 'A' ) + row_index );
      Grid.SetRowName( row_index, name );
   }

   Grid.SetRowsTitle( TEXT( "Amplitude" ) );

   for( column_index = 0; column_index < number_of_columns; column_index++ )
   {
      _tsprintf( name, TEXT( "%02d" ), column_index );
      Grid.SetColumnName( column_index, name );
   }

   Grid.SetColumnsTitle( TEXT( "Frequency" ) );
   Grid.SetName( TEXT( "Battleship!" ) );
   Grid.SetLabelOptions( LABELED_GRID_COLUMNS_TITLE | LABELED_GRID_ROWS_TITLE );
   Grid.SetVerticalSpacing( 2 );
   Grid.SetHorizontalSpacing( 2 );
   
   CRect rectangle( 40, 40, 0, 0 );

   Grid.SetRectangle( rectangle );

   // Now for constellation data...

   ConstellationGrid.SetRowsTitle( TEXT( "Amplitude" ) );

   ConstellationGrid.SetColumnsTitle( TEXT( "Frequency" ) );
   ConstellationGrid.SetName( TEXT( "Battleship!" ) );
   ConstellationGrid.SetLabelOptions( LABELED_GRID_COLUMNS_TITLE | LABELED_GRID_ROWS_TITLE );
   ConstellationGrid.SetVerticalSpacing( 2 );
   ConstellationGrid.SetHorizontalSpacing( 2 );
   
   rectangle = CRect( 40, 360, 0, 0 );

   ConstellationGrid.SetRectangle( rectangle );
}

void PASCAL fill_data( CSquiggleData *data_p )
{
   static static_randomizer_initialized = 0;

   if ( static_randomizer_initialized == 0 )
   {
      static_randomizer_initialized = 1;

      srand( (unsigned) time( NULL ) );
   }

   if ( data_p == reinterpret_cast<CSquiggleData *>( NULL ) )
   {
      return;
   }

   int number_of_elements = data_p->Data.GetSize();
   int index              = 0;

   WORD random_value = 0;
   WORD valid_range  = data_p->ValidRange();
   WORD last_value   = 0;
   WORD direction    = 0;
   WORD new_value    = 0;

   while( index < number_of_elements )
   {
      random_value = (WORD) ( rand() % 67 );

      if ( direction == 0 )
      {
         new_value = (WORD) ( last_value + random_value );
         new_value += (WORD) data_p->MinimumValue;

         if ( new_value >= data_p->MaximumValue )
         {
            direction = 1;
            new_value = data_p->MaximumValue - random_value;
         }
      }
      else
      {
         if ( last_value < random_value )
         {
            new_value = data_p->MinimumValue + random_value;
            direction = 0;
         }
         else
         {
            new_value = (WORD) ( last_value - random_value );

            if ( new_value <= data_p->MinimumValue )
            {
               direction = 0;
               new_value = data_p->MinimumValue;
            }
         }
      }

      data_p->Data.SetAt( index, new_value );

      last_value = new_value;

      index++;
   }
}

void PASCAL fill_constellation( CConstellationData *data_p )
{
   static static_randomizer_initialized = 0;

   if ( static_randomizer_initialized == 0 )
   {
      static_randomizer_initialized = 1;

      srand( (unsigned) time( NULL ) );
   }

   if ( data_p == (CConstellationData *) NULL )
   {
      return;
   }

   int number_of_elements = data_p->NumberOfPoints;
   int index              = 0;

   DWORD random_height = 0;
   DWORD random_width  = 0;

   DWORD valid_width  = data_p->ValidWidth();
   DWORD valid_height = data_p->ValidHeight();

   while( index < number_of_elements )
   {
      random_width = ( rand() % valid_width );

      data_p->Data[ index ].x = random_width;

      random_height = ( rand() % valid_height );

      data_p->Data[ index ].y = random_height;

      index++;
   }
}

BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
   ON_WM_CREATE()
   ON_WM_PAINT()
   ON_WM_TIMER()
END_MESSAGE_MAP()

int CMainWindow::OnCreate( LPCREATESTRUCT )
{
   SetTimer( 1, 200, NULL );
   return( 0 );
}

void CMainWindow::OnPaint()
{
   CPaintDC device_context( this );

   Grid.Draw( device_context );
   ConstellationGrid.Draw( device_context );
}

void CMainWindow::OnTimer( UINT )
{
   CSquiggle *squiggle_p = (CSquiggle *) Grid.GetAt( 0, 0 );

   if ( squiggle_p != (CSquiggle *) NULL )
   {
      CSquiggleData *data_p = new CSquiggleData;

      if ( data_p != (CSquiggleData *) NULL )
      {
         data_p->MinimumValue = 1;
         data_p->MaximumValue = 256;
         data_p->Data.SetSize( 256 );

         fill_data( data_p );

         squiggle_p->SetSquiggleData( data_p, TRUE );

         CRect rectangle;

         squiggle_p->GetRectangle( rectangle );

         InvalidateRect( &rectangle, FALSE );
      }
   }

   CConstellation * constellation_p = reinterpret_cast<CConstellation *>( ConstellationGrid.GetAt( 0, 0 ) );

   if ( constellation_p != reinterpret_cast<CConstellation *>( NULL ) )
   {
      CConstellationData * data_p = reinterpret_cast<CConstellationData *>( constellation_p->GetData() );

      fill_constellation( data_p );

      constellation_p->SetDirtyData( TRUE );

      CRect rectangle;

      constellation_p->GetRectangle( rectangle );

      InvalidateRect( &rectangle, FALSE );
   }
}

class CSimpleApplication : public CWinApp
{
   public:

      BOOL InitInstance();
};

BOOL CSimpleApplication::InitInstance()
{
   CMainWindow *main_window_p = new CMainWindow;

   m_pMainWnd = main_window_p;

   main_window_p->Create( NULL, TEXT( "Simple" ) );

   {
      CClientDC device_context( main_window_p );

      main_window_p->Grid.PrepareForPainting( device_context );
      main_window_p->ConstellationGrid.PrepareForPainting( device_context );
   }

   main_window_p->ShowWindow( m_nCmdShow );
   main_window_p->UpdateWindow();

   return( TRUE );
}

CSimpleApplication dodah;
