#include "PasswordDLL.h"
#pragma hdrstop

BOOL __stdcall InitializeChangeNotify( void )
{
   extern MyPasswordFilter Static_Filter;

   MessageBeep( 0 );

   Static_Filter.OnInitialize();

   return( TRUE );
}
