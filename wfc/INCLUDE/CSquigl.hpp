#if ! defined( SQUIGGLE_CLASS_HEADER )

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
** $Workfile: csquigl.hpp $
** $Revision: 13 $
** $Modtime: 1/04/00 4:54a $
*/

#define SQUIGGLE_CLASS_HEADER

#if ! defined( WFC_STL )

class CSquiggleData
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CSquiggleData )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      // Construction

      CSquiggleData();
      CSquiggleData( const CSquiggleData *source_p );
      virtual ~CSquiggleData();

      /*
      ** Data Members
      */

      CString    Start;
      CString    Stop;
      CTime      Time;
      WORD       MinimumValue;
      WORD       MaximumValue;
      CWordArray Data;

      // Methods

      virtual void Copy( const CSquiggleData& source );
      virtual void Copy( const CSquiggleData * source_p );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual WORD ValidRange( void );

      // Operators

      virtual CSquiggleData& operator=( const CSquiggleData& source );
};

class CSquiggle : public CRectangle
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CSquiggle )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CSquiggle( const CSquiggle& ) {};
      CSquiggle& operator=( const CSquiggle& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      BOOL m_AutomaticallyDelete;

      CSquiggleData *m_SquiggleData_p;

      int m_NumberOfPoints;

      WORD m_NumberOfXGridLines;
      WORD m_NumberOfYGridLines;

      DWORD m_LineThickness;
      DWORD m_GridLineType;

      COLORREF m_GridLineColor;

      POINT *m_PointArray;

      BOOL m_DataIsDirty;

   public:

      CSquiggle();
      CSquiggle( DWORD height, DWORD width, const CPoint& location, COLORREF fill_color, COLORREF line_color );

      virtual      ~CSquiggle();
      virtual void  Copy( const CSquiggle *source_p );
      virtual void  Draw( CDC& device_context );
      virtual void  Empty( void );
      virtual DWORD GetLineThickness( void ) const;
      virtual void  PrepareData( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual void  SetAutomaticallyDelete( BOOL new_value = TRUE );
      virtual void  SetDirtyData( BOOL new_value = TRUE );
      virtual void  SetGridLineColor( COLORREF grid_line_color );
      virtual void  SetGridLineType( DWORD type );
      virtual void  SetHeight( DWORD height );
      virtual void  SetLineThickness( DWORD thickness );
      virtual void  SetNumberOfGridLines( WORD number_of_x_lines, WORD number_of_y_lines );
      virtual void  SetSize( const CSize& size );
      virtual void  SetSquiggleData( CSquiggleData * source_p, BOOL auto_delete = FALSE );
      virtual void  SetWidth( DWORD width );
};

#endif // WFC_STL

#endif // SQUIGGLE_CLASS_HEADER
