#if ! defined ( BUBBLE_CLASS_HEADER )

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
** $Workfile: cbubble.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 4:33a $
*/

#define BUBBLE_CLASS_HEADER

#if ! defined( WFC_STL )

class CBubble : public CWnd
{
   DECLARE_DYNAMIC( CBubble );

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CBubble( const CBubble& ) {};
      CBubble& operator=( const CBubble& ) { return( *this ); };

   private:

      static CString m_StaticClassName;
      static CFont   m_StaticFont;
      static DWORD   m_StaticHeight;

      int            m_FontSize;
      BOOL           m_Created;

      void m_SetFont( void );

   public:

      CBubble();
      CBubble( int font_size );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CBubble();

      virtual BOOL  Create( void );
      virtual BOOL  DestroyWindow( void );
      virtual DWORD GetHeight( void ) const;
      virtual void  Hide( void );
      virtual BOOL  IsCreated( void ) const;
      virtual void  SetFontSize( int font_size );
      virtual void  Show( CPoint screen_coordinates, const CString& string );

   protected:

      afx_msg void OnPaint( void );
      afx_msg LONG OnSetText( UINT, LONG lParam );

      DECLARE_MESSAGE_MAP()
};

#endif // WFC_STL

#endif // BUBBLE_CLASS_HEADER
