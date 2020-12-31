// NGenericDockBar.h: interface for the CNGenericDockBar class.
//
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

#if !defined(AFX_NGENERICDOCKBAR_H__D09C39E2_A6EB_11D1_B0D4_00A0C94457BF__INCLUDED_)
#define AFX_NGENERICDOCKBAR_H__D09C39E2_A6EB_11D1_B0D4_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "afxpriv.h"

class CNGenericDockBar : public CDockBar
{
	DECLARE_DYNCREATE(CNGenericDockBar)
public:
	CNGenericDockBar();
	virtual ~CNGenericDockBar();
	virtual CSize CalcFixedLayout( BOOL bStretch, BOOL bHorz );

protected:
	//{{AFX_MSG(CNGenericDockBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_NGENERICDOCKBAR_H__D09C39E2_A6EB_11D1_B0D4_00A0C94457BF__INCLUDED_)
