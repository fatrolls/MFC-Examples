#if ! defined( PASSWORD_FILTER_DLL )

#define PASSWORD_FILTER_DLL

#include <wfc.h>

class MyPasswordFilter : public CPasswordChangeFilter
{
   public:

      virtual BOOL OnChanged( PASSWORD_FILTER_STRING * user_name, ULONG relative_id, PASSWORD_FILTER_STRING * new_password );
};

#if defined( __cplusplus )
extern "C" {
#endif // __cplusplus

BOOL __stdcall InitializeChangeNotify( void );
LONG __stdcall PasswordChangeNotify( PASSWORD_FILTER_STRING * user_name, ULONG relative_id, PASSWORD_FILTER_STRING * password );

#if defined( __cplusplus )
}
#endif // __cplusplus

#endif // PASSWORD_FILTER_DLL
