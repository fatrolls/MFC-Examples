#if ! defined( CONSTELLATION_CLASS_HEADER )

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
** $Workfile: CConstellation.hpp $
** $Revision: 8 $
** $Modtime: 1/04/00 4:33a $
*/

#define CONSTELLATION_CLASS_HEADER

#if ! defined( WFC_STL )

class CConstellationData
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CConstellationData )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      // Construction

      CConstellationData();
      CConstellationData( const CConstellationData *source_p );
      CConstellationData( const CConstellationData& source   );
      virtual ~CConstellationData();

      /*
      ** Data Members
      */

      CString    Start;
      CString    Stop;
      CTime      Time;
      DWORD      MinimumWidthValue;
      DWORD      MaximumWidthValue;
      DWORD      MinimumHeightValue;
      DWORD      MaximumHeightValue;
      DWORD      NumberOfPoints;
      POINT *    Data;

      // Methods

      virtual void  Copy( const CConstellationData&  source );
      virtual void  Copy( const CConstellationData * source_p );
      virtual void  Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual void  SetSize( DWORD new_number_of_points );
      virtual DWORD ValidWidth( void );
      virtual DWORD ValidHeight( void );

      // Operators

      virtual CConstellationData& operator=( const CConstellationData& source );
};

class CConstellation : public CRectangle
{
   DECLARE_SERIAL( CConstellation )

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CConstellation( const CConstellation& ) {};
      CConstellation& operator=( const CConstellation& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      BOOL m_AutomaticallyDelete;

      CConstellationData *m_Data_p;

      DWORD m_NumberOfPoints;

      WORD m_NumberOfXGridLines;
      WORD m_NumberOfYGridLines;

      DWORD m_LineThickness;
      DWORD m_GridLineType;

      COLORREF m_GridLineColor;

      POINT *m_PointArray;

      BOOL m_DataIsDirty;

   public:

      CConstellation();
      CConstellation( DWORD height, DWORD width, const CPoint& location, COLORREF fill_color, COLORREF line_color );

      virtual      ~CConstellation();
      virtual void  Copy( const CConstellation *source_p );
      virtual void  Draw( CDC& device_context );
      virtual void  Empty( void );
      virtual CConstellationData * GetData( void ) const;
      virtual DWORD GetLineThickness( void ) const;
      virtual void  PrepareData( void );
      virtual void  Serialize( CArchive& archive );
      virtual void  SetAutomaticallyDelete( BOOL new_value = TRUE );
      virtual void  SetDirtyData( BOOL new_value = TRUE );
      virtual void  SetGridLineColor( COLORREF grid_line_color );
      virtual void  SetGridLineType( DWORD type );
      virtual void  SetHeight( DWORD height );
      virtual void  SetLineThickness( DWORD thickness );
      virtual void  SetNumberOfGridLines( WORD number_of_x_lines, WORD number_of_y_lines );
      virtual void  SetSize( const CSize& size );
      virtual void  SetData( CConstellationData * source_p, BOOL auto_delete = FALSE );
      virtual void  SetWidth( DWORD width );
};

#endif // WFC_STL

#endif // CONSTELLATION_CLASS_HEADER
