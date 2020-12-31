// ==========================================================================
//                     Template Implementation : COXSPtr
// ==========================================================================

// Source file : OXSPtr.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      

/////////////////////////////////////////////////////////////////////////////			  
#include "stdafx.h"
#include "OXSPtr.h"

// //////////////////////////////////////////////////////////////////////////
// Definition of static variables

// Define the only valid COXObjectCreator object
OX_CLASS_DECL COXObjectCreator NEW_OBJECT;

#if defined(_DEBUG) && !defined(DISABLE_SMART_CHECK)
// Use a global object that keeps track of smart pointers and 
// that will be used for debugging purposes
COXSmartWatcher smartWatcher;
#endif

// ==========================================================================
