#include "wfc.h"
#pragma hdrstop

class CMainWindow : public CFrameWnd
{
   public:

      CMainWindow();

      CLabeledGrid Grid;

   protected:

      afx_msg void OnPaint();
      DECLARE_MESSAGE_MAP()
};

CMainWindow::CMainWindow()
{
   int number_of_rows    = 10;
   int number_of_columns = 10;

   Grid.SetSize( number_of_rows, number_of_columns );

   int row_index    = 0;
   int column_index = 0;

   for ( row_index = 0; row_index < number_of_rows; row_index++ )
   {
      for( column_index = 0; column_index < number_of_columns; column_index++ )
      {
         CSquare *square_p = new CSquare;

         square_p->SetSize( 30 );
         square_p->SetLineColor( BLACK );
         square_p->SetFillColor( WHITE );

         Grid.SetAt( row_index, column_index, square_p );
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
      name[ 0 ] = TEXT( 'A' ) + row_index;
      Grid.SetRowName( row_index, name );
   }

   Grid.SetRowsTitle( TEXT( "Rows Title" ) );

   for( column_index = 0; column_index < number_of_columns; column_index++ )
   {
      _tsprintf( name, TEXT( "%02d" ), column_index );
      Grid.SetColumnName( column_index, name );
   }

   Grid.SetColumnsTitle( TEXT( "Columns Title" ) );
   Grid.SetName( TEXT( "Battleship!" ) );
   //Grid.SetLabelOptions( LABELED_GRID_ALL_TITLES );
   Grid.SetLabelOptions( LABELED_GRID_COLUMNS_TITLE | LABELED_GRID_ROWS_TITLE );
   Grid.SetVerticalSpacing( 2 );
   Grid.SetHorizontalSpacing( 2 );
   
   CRect rectangle( 90, 60, 0, 0 );

   Grid.SetRectangle( rectangle );
}

BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
   ON_WM_PAINT()
END_MESSAGE_MAP()

void CMainWindow::OnPaint()
{
   CPaintDC device_context( this );

   Grid.Draw( device_context );
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
   }

   main_window_p->ShowWindow( m_nCmdShow );
   main_window_p->UpdateWindow();

   return( TRUE );
}

CSimpleApplication dodah;
