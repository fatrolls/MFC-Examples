///////////////////////////////////////////////////////////////////
//  Header   : DYNLINK2.H
//
//  Purpose  : Interface for the DYNLINK2.DLL.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-02-96
///////////////////////////////////////////////////////////////////

// Macro for DLL exports in Win32, replaces Win16 __export
#define DllExport  __declspec(dllexport)

// Global function
extern "C" DllExport FLOAT Multiply2Floats(FLOAT f1, FLOAT f2);

///////////////////////////////////////////////////////////////////
// The CDynLink2App class

class CDynLink2App : public CWinApp
{
public:
	CDynLink2App();
};

///////////////////////////////////////////////////////////////////