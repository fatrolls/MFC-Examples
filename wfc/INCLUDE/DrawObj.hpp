#if ! defined ( DRAWING_OBJECTS_CLASS_HEADER )

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
** $Workfile: drawobj.hpp $
** $Revision: 10 $
** $Modtime: 1/04/00 5:00a $
*/

#define DRAWING_OBJECTS_CLASS_HEADER

#if ! defined( WFC_STL )

class CRectangle
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CRectangle )
#endif // WFC_NO_SERIALIZATION

   protected:

      void m_Initialize( void );
      void m_SetRectangles( void );

      DWORD m_Height;
      DWORD m_Width;

      COLORREF m_LineColor;
      COLORREF m_FillColor;

      CPoint m_Location;

      CRect m_LineRectangle;
      CRect m_FillRectangle;

   public:

      CRectangle();
      CRectangle( const CRectangle& source );
      CRectangle( DWORD height, DWORD width, const CPoint& location, COLORREF fill_color = WHITE, COLORREF line_color = BLACK );

      virtual ~CRectangle();

      virtual void     Copy( const CRectangle& source );
      virtual void     Copy( const CRectangle *source_p );
      virtual void     Draw( CDC& device_context );
      virtual COLORREF GetFillColor( void ) const;
      virtual DWORD    GetHeight( void ) const;
      virtual COLORREF GetLineColor( void ) const;
      virtual void     GetRectangle( CRect& destination ) const;
      virtual DWORD    GetWidth( void ) const;
      virtual void     OnClick( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void     Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual void     SetFillColor( COLORREF color );
      virtual void     SetHeight( DWORD height );
      virtual void     SetLineColor( COLORREF color );
      virtual void     SetLocation( const CPoint& size );
      virtual void     SetSize( const CSize& size );
      virtual void     SetWidth( DWORD width );

      /*
      ** Operators
      */

      virtual CRectangle& operator=( const CRectangle& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

class CRoundedRectangle : public CRectangle
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CRoundedRectangle )
#endif // WFC_NO_SERIALIZATION

   protected:

      CPoint m_RoundingPoint;

   public:

      CRoundedRectangle();

      virtual ~CRoundedRectangle();

      virtual void  Copy( const CRoundedRectangle& source );
      virtual void  Copy( const CRoundedRectangle * source_p );
      virtual void  Draw( CDC& device_context );
      virtual DWORD GetRoundingSize( void ) const;
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual void  SetRoundingSize( DWORD rounding_size );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

class CSquare : public CRectangle
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CSquare )
#endif // WFC_NO_SERIALIZATION

   public:

      CSquare();
      CSquare( DWORD size, const CPoint& location, COLORREF fill_color = WHITE, COLORREF line_color = BLACK );
     
      virtual ~CSquare();

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual void SetHeight( DWORD height );
      virtual void SetSize( const CSize& size );
      virtual void SetWidth( DWORD width );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

class CEllipse : public CRectangle
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CEllipse )
#endif // WFC_NO_SERIALIZATION

   public:

      CEllipse();
      CEllipse( DWORD height, DWORD width, const CPoint& location, COLORREF fill_color = WHITE, COLORREF line_color = BLACK );
      
      virtual ~CEllipse();

      virtual void Draw( CDC& device_context );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

class CCircle : public CSquare
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CCircle )
#endif // WFC_NO_SERIALIZATION

   public:

      CCircle();
      CCircle( DWORD size, const CPoint& location, COLORREF fill_color = WHITE, COLORREF line_color = BLACK );
      
      virtual ~CCircle();

      virtual void Draw( CDC& device_context );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

#endif // WFC_STL

#endif // DRAWING_OBJECTS_CLASS_HEADER
