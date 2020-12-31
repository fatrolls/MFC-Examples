#if ! defined( PASSWORD_CHANGE_FILTER_CLASS_HEADER )

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
** $Workfile: CPasswordChangeFilter.hpp $
** $Revision: 4 $
** $Modtime: 1/04/00 4:52a $
*/

#define PASSWORD_CHANGE_FILTER_CLASS_HEADER

typedef struct __password_filter_unicode_string
{
   USHORT Length;
   USHORT MaximumLength;
   WCHAR *UnicodeString;
}
PASSWORD_FILTER_STRING, * PASSWORD_FILTER_STRING_P;

class CPasswordChangeFilter
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CPasswordChangeFilter( const CPasswordChangeFilter& ) {};
      CPasswordChangeFilter& operator=( const CPasswordChangeFilter& ) { return( *this ); };

   public:

      CPasswordChangeFilter();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CPasswordChangeFilter();

      virtual BOOL AddFilter( const CString& dll_name );
      virtual BOOL GetCurrentFilters( CStringArray& current_filters );
      virtual BOOL OnChanged( PASSWORD_FILTER_STRING * user_name, ULONG relative_id, PASSWORD_FILTER_STRING * new_password );
      virtual BOOL OnFilter( PASSWORD_FILTER_STRING * user_name, PASSWORD_FILTER_STRING * full_user_name, PASSWORD_FILTER_STRING * new_password, BOOL was_set );
      virtual BOOL OnInitialize( void );
      virtual BOOL RemoveFilter( const CString& dll_name );
};

#endif // PASSWORD_CHANGE_FILTER_CLASS_HEADER
