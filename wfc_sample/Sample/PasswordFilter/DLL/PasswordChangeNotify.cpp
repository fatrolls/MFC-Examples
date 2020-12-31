#include "PasswordDLL.h"
#pragma hdrstop

LONG __stdcall PasswordChangeNotify( PASSWORD_FILTER_STRING * user_name, ULONG relative_id, PASSWORD_FILTER_STRING * password )
{
   extern MyPasswordFilter Static_Filter;

   if ( Static_Filter.OnChanged( user_name, relative_id, password ) != FALSE )
   {
      return( TRUE );
   }

   return( ERROR_ILL_FORMED_PASSWORD );
}
