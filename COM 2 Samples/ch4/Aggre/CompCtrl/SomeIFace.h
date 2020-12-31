
#ifndef __ISomeInterface_H__
#define __ISomeInterface_H__

#include "Unknwn.h"

// {16DCB982-BEEB-11d2-B362-00104B08CC22}
extern "C" const GUID IID_SomeInterface;

class ISomeInterface: public IUnknown 
{
	public : 
		virtual HRESULT __stdcall SomeFunction( ) = 0 ;
};

#endif // __ISomeInterface_H__