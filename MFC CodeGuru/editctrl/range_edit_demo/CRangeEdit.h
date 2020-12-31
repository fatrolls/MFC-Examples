//*****************************************************************************
//	header file
//*****************************************************************************
//
//	FILE NAME:		CRangeEdit.h
//
//	DESCRIPTION:	This file contains the attributes and methods for the
//					CRangeEdit class.
//
//*****************************************************************************
//
//	MODIFICATION HISTORY:
//	Rev #		Date		Author
//	001			3/2/1998	Donald R. Kichline	(drkich@csrlink.net)
//	002			3/6/1998	Donald R. Kichline
//
//*****************************************************************************
//
//	MODIFICATION SUMMARY:
//
//	Rev #		Description
//	001			Created the class
//	002			1.	Moved range validation from OnChar() to OnUpdate().
//
//				2.	Removed the OnChar() member function.
//			
//				3.	Added a member variable to hold the last valid value
//					entered by the operator.
//
//				4.	Seperated the code to remove the leading zeros from 
//					a string, into a seperate function.
//
//				5.	Allow NULL to be a valid value entered by an operator.
//					This occurs when the operator deletes the number in
//					the control.
//
//*****************************************************************************


#if !defined(AFX_RANGEEDIT_H__A8919B9F_CB7C_11D1_ADB8_000000000000__INCLUDED_)
#define AFX_RANGEEDIT_H__A8919B9F_CB7C_11D1_ADB8_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRangeEdit : public CEdit
{
public:
// Construction
	CRangeEdit();

//	Destructor
	virtual ~CRangeEdit();

// Attributes


// Operations


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRangeEdit)
	//}}AFX_VIRTUAL

// Implementation
	void SetRange ( LONG inLMin, LONG inLMax );


protected:
	// Generated message map functions
	//{{AFX_MSG(CRangeEdit)
	afx_msg void OnUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
//  Implementation
	void RemoveLeadingZeros ( void );

//	Attributes
	LONG	myMax;		//	Maximum number the edit control will accept
	LONG	myMin;		//	Minimum number the edit control will accept
	LONG	myLastValidValue;	//	The last valid value entered by the 
								//		operator.  Used to undo invalid
								//		key-strokes.
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANGEEDIT_H__A8919B9F_CB7C_11D1_ADB8_000000000000__INCLUDED_)
