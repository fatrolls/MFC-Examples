
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
// #include <afxext.h>         // MFC extensions

#pragma warning( disable : 4711 )	// automatic inline selected
#pragma warning( disable : 4275 )	// non dll-interface class 'X' used as base for dll-interface class 'Y'
#pragma warning( disable : 4251 )	// 'm' : class 'X' needs to have dll-interface to be used by clients of class 'Y'

// Oh the joys of the preprocessor :-)
#define __LINE_NO__(A,B)   A"("#B") : "
#define __LINE_NO2__(A,B) __LINE_NO__(A,B)
#define __FILEINFO__ __LINE_NO2__(__FILE__,__LINE__)
// This allows me to put 'reminder' messages in the code that the compiler can then spit
// out with file and lineno info, doing something like this
// #pragma message( __FILEINFO__ "Fix Me!!!" )
