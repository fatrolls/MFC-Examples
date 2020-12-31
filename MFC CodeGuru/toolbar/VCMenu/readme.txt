		VC/Office style dockable menus & toolbars
		-----------------------------------------

Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)
Portions Copyright (C) 1998 George H. Stahl (GStahl@VipMail.Com)

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

----------------------------------------------------------------------------------

Requires VC++ 5 (Not sure it can be made to work on VC4.2).
Requires commctrl.dll 4.71 or above (4.70 will probably work too).

Simple usage:

Create an MDI or SDI app
Add the following to the end of your stdafx.h

#define AUTO_SUBCLASS
#include <NGToolbar.h>

Complex(!) usage:

Derive your main frame from CNMDIFrameWnd or CNSDIFrameWnd
Use CNGenericToolBar instead of CToolBar
You can set the text that appears on the toolbar buttons by
putting a third 'line' in its associated text (eg. xxx\nyyyy\nzzz).
To set the startup state of a toolbar call CNGenericToolBar::SetVisualState.

Rebuilding NGTLB10x.DLL:

(in addition to above) Requires up to date commctrl.h from MS

Build will create NGTLB10R.DLL for release and NGTLB10D.DLL for debug.
Library inclusion is automatic (see NGToolbar.h)

Tony Hoyle
April 1998