// MFCXDockBar.h: interface for the CMFCXDockBar class.
/*
Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
//////////////////////////////////////////////////////////////////////

#ifndef MFCXDOCKBAR__H
#define MFCXDOCKBAR__H

#include <afxpriv.h>

#ifndef MFCX_PROJ
#define CLASS_EXPORT AFX_CLASS_EXPORT
#else
#define CLASS_EXPORT AFX_CLASS_IMPORT
#endif

// ( originally CNGenericDockBar )

class CLASS_EXPORT CMFCXDockBar : public CDockBar
{
	DECLARE_DYNCREATE(CMFCXDockBar)
public:
	CMFCXDockBar();
	virtual ~CMFCXDockBar();
	virtual CSize CalcFixedLayout( BOOL bStretch, BOOL bHorz );

protected:
	//{{AFX_MSG(CMFCXDockBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
