#if ! defined( STLXML_HEADER_FILE )

#define STLXML_HEADER_FILE

#if ! defined( SUBSET_STLXML )
#define SUBSET_STLXML
#endif

#if ! defined( WFC_NO_DUMPING )
#define WFC_NO_DUMPING
#endif

#if ! defined( WFC_STL )
#define WFC_STL
#endif

#include <windows.h>
#include <tchar.h>

#define CARRIAGE_RETURN (13)
#define LINE_FEED       (10)

#define WFCTRACEINIT( string )          {;}
#define WFCLTRACEINIT( string )         {;}
#define WFCTRACEINITLEVEL( string, x )  {;}
#define WFCTRACE( string )              {;}
#define WFCTRACEVAL( string, value )    {;}
#define WFCTRACEBINVAL( string, value ) {;}
#define WFCTRACEDUMP( variable )        {;}
#define WFCTRACEERROR( error_code )     {;}
#define WFCTRACEON()                    {;}
#define WFCTRACEOFF()                   {;}
#define WFCTRACEALLON()                 {;}
#define WFCTRACEALLOFF()                {;}
#define WFCTRACELEVELON( x )            {;}
#define WFCTRACELEVELOFF( x )           {;}

#include <mfc2stl.h>

#include <CParsePoint.hpp>
#include <CDataParser.hpp>
#include <CExtensibleMarkupLanguage.hpp>
//#include <CXMLArchive.hpp>

#endif // STLXML_HEADER_FILE