
#ifndef __IOtherInterface_H__
#define __IOtherInterface_H__

#include "Unknwn.h"

// {39C07942-BFCC-11d2-A100-00A0C9A6F472}
extern "C" const GUID IID_OtherInterface;

class IOtherInterface : public IUnknown 
{
	public : 
		virtual HRESULT __stdcall OtherFunction( ) = 0 ;
};

#endif // __IOtherInterface_H__