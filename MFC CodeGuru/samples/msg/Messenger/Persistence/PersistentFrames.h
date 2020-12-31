/* @doc
 *
 * @module PersistentFrames.h - CPersistentFrameWnd & CPersistentMDIFrameWnd classes |
 *
 * Definition for CPersistentFrameWnd and CPersistentFrameWnd classes
 *
 * Copyright (c)1997 David Carballo, All Right Reserved
 *
 * @end
 *
 * Created October 1997
 * Revised: -
 * Written by David Carballo
 * Internet: fibeto@redestb.es
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 */

#ifndef __PERSISTENTFRAMES_H_
#define __PERSISTENTFRAMES_H_

/*---------------------------------------------------------------------------

  @class	CPersistentFrameWnd | Frame window for SDI applications that
			implements window size and position persistence between diferent
			executions

  @base		public | CFrameWnd

  @access	Update/Painting Functions

  @cmember	void | InitialShowWindow | (UINT nCmdShow) | Shows the window
			as it was the last time the app was executed.

---------------------------------------------------------------------------*/
class CPersistentFrameWnd: public CFrameWnd
{
public:
	CPersistentFrameWnd();

	void InitialShowWindow(UINT nCmdShow);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersistentFrameWnd)
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CPersistentFrameWnd)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	DECLARE_DYNAMIC(CPersistentFrameWnd)
};


/*---------------------------------------------------------------------------

  @class	CPersistentMDIFrameWnd | Main frame window for MDI applications that
			implements window size and position persistence between diferent
			executions

  @base		public | CFrameWnd

  @access	Update/Painting Functions

  @cmember	void | InitialShowWindow | (UINT nCmdShow) | Shows the window
			as it was the last time the app was executed.

---------------------------------------------------------------------------*/
class CPersistentMDIFrameWnd : public CMDIFrameWnd
{
public:
	CPersistentMDIFrameWnd();
	
	void InitialShowWindow(UINT nCmdShow);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersistentMDIFrameWnd)
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CPersistentMDIFrameWnd)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	DECLARE_DYNAMIC(CPersistentMDIFrameWnd)
};

#endif	// __PERSISTENTFRAMES_H_
