#ifndef IPROPERTYHOST_H
#define IPROPERTYHOST_H

#include "EPropList.h"
#include "EPropListCtrl.h"

// Implement this class in your object that needs properties presented in
// property control
class IPropertyHost
{

public:    

	//The control will ask hosts for propertylist here. This is done when
	//propertyhost is set in the control. Add property items to the list
	//throught the parsed in list.
    virtual void GetProperties( EPropList& PropList )
	{
	}

	//Called from the view when the property is changing to allow veto from
	//property host. Return true if the change is ok, else false. Override
	//if special constraints are bound to the property. This default
	//implementation allows for any change.
    virtual bool PropertyChanging( const void* pProperty , void* pNewValue )
	{
		return true;	//yes, please change
	}

	//the control will ask you if the property is enabled each time it is
	//redrawn. This enables you to disable a property on the fly.
	virtual bool IsPropertyEnabled( const void* pProperty )
	{
		return true;
	}

	//Override this to identify yourself.
//	virtual CString GetPropertyHostName()
//	{
//		return "Object";
//	}
};

#include "EPropertyDouble.h"
#include "EPropertyFloat.h"
#include "EPropertyInt.h"
#include "EPropertyColor.h"
#include "EPropertyCombo.h"
#include "EPropertyString.h"
#include "EPropertyCheck.h"
#include "EPropertyFile.h"
#include "EPropertyFont.h"
#include "EPropertyTextblock.h"

#endif