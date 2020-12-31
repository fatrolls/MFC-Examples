#if ! defined( XML_ARCHIVE_CLASS_HEADER )

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
** $Workfile: CXMLArchive.hpp $
** $Revision: 9 $
** $Modtime: 1/04/00 4:58a $
*/

#define XML_ARCHIVE_CLASS_HEADER

class CXMLArchive; // Catch-22 here

typedef BOOL (*XML_ARCHIVE_SERIALIZE_OBJECT) ( CXMLArchive * archive_p, const CString& name, void * parameter );

class CXMLArchive
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CXMLArchive( const CXMLArchive& ) {};
      CXMLArchive& operator=( const CXMLArchive& ) { return( *this ); };

   protected:

      BOOL m_AmIWriting;
      BOOL m_AddNewLineAfterEachElement;

      CString m_TimeZone;

      CExtensibleMarkupLanguageElement * m_Element_p;

   public:

      CXMLArchive();
      virtual ~CXMLArchive();

      virtual void SetAddNewLineAfterEachElement( BOOL add_new_line = TRUE );
      virtual BOOL GetAddNewLineAfterEachElement( void ) const;
      virtual BOOL IsLoading( void ) const;
      virtual BOOL IsStoring( void ) const;
      virtual CExtensibleMarkupLanguageElement * GetElement( void ) const;

      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, BOOL&             value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, CByteArray&       value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, CDWordArray&      value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, CFileTime&        value );

#if ! defined( WFC_STL )      
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, COleDateTime&     value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, COleDateTimeSpan& value );
#endif // WFC_STL

      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, CString&          value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, CStringArray&     value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, CSystemTime&      value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, CTime&            value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, CTimeSpan&        value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, double&           value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, DWORD&            value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, LONGLONG&         value );
      virtual CExtensibleMarkupLanguageElement * Read( const CString& tag, ULONGLONG&        value );

      virtual void ReadFrom( CExtensibleMarkupLanguageElement * element_p );

      virtual BOOL SerializeObject( const CString& tag, void * object_p, XML_ARCHIVE_SERIALIZE_OBJECT write_function );

      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, BOOL                    value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const CByteArray&       value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const CDWordArray&      value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const CFileTime&        value );

#if ! defined( WFC_STL )      
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const COleDateTime&     value, BOOL value_is_UTC_time = FALSE );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const COleDateTimeSpan& value );
#endif // WFC_STL

      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const CString&          value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const CStringArray&     value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const CSystemTime&      value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const CTime&            value, BOOL value_is_UTC_time = FALSE );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, const CTimeSpan&        value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, double                  value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, DWORD                   value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, LONGLONG                value );
      virtual CExtensibleMarkupLanguageElement * Write( const CString& tag, ULONGLONG               value );

      virtual void WriteTo( CExtensibleMarkupLanguageElement * element_p );
};

#endif // XML_ARCHIVE_CLASS_HEADER
