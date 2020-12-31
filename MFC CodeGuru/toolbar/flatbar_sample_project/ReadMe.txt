Some time ago, I saw Roger Onslow's flat toolbar implementation on
www.codeguru.com.
The fact, that I need a special product (MSIE) (or even DLL ->commctrl.dll)
was somewhat inconvenient to me. So I started to develop my own version
of a flat looking toolbar without such requirements. The result is a class
called CToolBarEx.
With CToolBarEx one can toggle between flat- and "classic"-mode. The
appropriate look will be shown immediataly (have a look at the sample
to see how easy it is).
Don't wonder if some parts of the code seem to be well known to you.
The drawing of separators and the gripper was (more or less) stolen
from Roger's toolbar (why should I do all of the hard bits again ;-)

In flat-mode CToolBarEx makes all of the drawings by itself.
In classic-mode, MFC does the work.
Since VC++ >= 4.2 provides custom-draw abilities, this feature will be
emulated in flat mode by a local helper class, so one can use this
feature regardless of the current mode (flat or classic).
To get some further informations on owner-drawing, have a look at
the implementation file ToolBarEx.cpp. The MainFrm.cpp in the sample
application may provide even more informations, if you're not
familiar with owner-drawing on toolbars.

CToolBarEx consists of two files:
	ToolBarEx.h
	ToolBarEx.cpp

To use CToolBarEx in an MFC application, you have to perform
the following steps (I assume you use App-/Class-Wizard):
1.	#include "ToolBarEx.h"
	in either StdAfx.h or MainFrm.h

2.	Change the type of CMainFrame::m_wndToolBar from
	CToolBar to CToolBarEx
That's it.

Have fun

	Jörg
