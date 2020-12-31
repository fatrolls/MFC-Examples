//*****************************************************************************
//	implementation file
//*****************************************************************************
//
//	FILE NAME:		CRangeEdit.cpp
//
//	DESCRIPTION:	This file contains the methods for the
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

//	Include Files
//
#include "stdafx.h"
#include "CRangeEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//	Defines
//
#define BLANK_ENTRY		-1


//*****************************************************************************
//
//	METHOD NAME :	CRangeEdit constructor
//
//	DESCRIPTION :	This is the CRangeEdit constructor.
//
//	PARAMETERS :
//	NAME			I/O		TYPE			DESCRIPTION
//	n/a
//
//	RETURN TYPE :
//	TYPE			DESCRIPTION
//	n/a
//
//*****************************************************************************

CRangeEdit::CRangeEdit() :
myMin ( 0 ),		//	Initialize member variables to zero
myMax ( 100 ),
myLastValidValue ( 0 )
{
}




//*****************************************************************************
//
//	METHOD NAME :	CRangeEdit destructor
//
//	DESCRIPTION :	This is the CRangeEdit destructor.
//
//	PARAMETERS :
//	NAME			I/O		TYPE			DESCRIPTION
//	n/a
//
//	RETURN TYPE :
//	TYPE			DESCRIPTION
//	n/a
//
//*****************************************************************************

CRangeEdit::~CRangeEdit()
{
}







//*****************************************************************************
//
//	METHOD NAME :	BEGIN_MESSAGE_MAP and END_MESSAGE_MAP macros
//
//	DESCRIPTION :	Each CCmdTarget-derived class must provide a message
//					map to handle messages.  The BEGIN_MESSAGE_MAP macro
//					is followed by entries for each message-handler
//					function in this class and the END_MESSAGE_MAP macro.
//
//	PARAMETERS :
//	NAME			I/O		TYPE			DESCRIPTION
//	n/a				 I		CRangeEdit		Class type
//	n/a				 I		CEdit			Class type
//
//	RETURN TYPE :
//	TYPE			DESCRIPTION
//	n/a
//
//*****************************************************************************

BEGIN_MESSAGE_MAP(CRangeEdit, CEdit)
	//{{AFX_MSG_MAP(CRangeEdit)
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
















//*****************************************************************************
//
//	METHOD NAME :	CRangeEdit.OnUpdate
//
//	DESCRIPTION :	This member function is called when the edit control is
//					about to display altered text.
//
//					This member function firsts removes all leading zeros from
//					the edit control.  Then it will validate the number entered
//					by the operator.  If the number is invalid, then the last
//					valid value is restored..
//
//	PARAMETERS :
//	NAME			I/O		TYPE			DESCRIPTION
//	n/a
//
//	RETURN TYPE :
//	TYPE			DESCRIPTION
//	n/a
//
//*****************************************************************************

void CRangeEdit::OnUpdate() 
{
	//	Local Variables
	//
	CString strWindowText;
	LONG ValidationNumber;



	//	Initialize Variables
	//
	strWindowText.Empty ( );
	ValidationNumber = 0;




	//	Remove the leading zeros from the
	//		edit control
	//
	RemoveLeadingZeros ( );

	



	//	Copy the contents of the edit control
	//		to a string
	//
	GetWindowText ( strWindowText );



	//	Check if the edit control is blank
	//
	if ( strWindowText.IsEmpty ( ) )
	{
		//	The operator erased the last number.  Thus the last valid value
		//		entered by the operator is NULL.
		//
		myLastValidValue = BLANK_ENTRY;
	}


	else
	{
		//	There is a number to validate in the string
		//
		//	Convert the string to a LONG
		//
		ValidationNumber = atol ( strWindowText );



		//	Check if the number falls within the specified range
		//
		if ( ( ValidationNumber < myMin ) || ( ValidationNumber > myMax ) )
		{
			//	The number is invalid, it is out of the specified range
			//
			//	Check what type of value the last Valid Value is:
			//		1.	A number:	which is indicated by a value greater than
			//						or equal to 0.
			//
			//		2.	NULL:		which is indicated by BLANK_ENTRY (-1).
			//
			if ( myLastValidValue >= 0 )
			{
				//	The last value is a number
				//
				strWindowText.Format ( "%d", myLastValidValue );
			}



			else
			{
				//	The last value was a NULL
				//
				strWindowText.Empty ( );
			}




			//	Set the Edit control with the Last Valid Value
			//
			SetWindowText ( strWindowText );




			//	Place the cursor at the end of the string
			//
			SetSel ( strWindowText.GetLength ( ), strWindowText.GetLength ( ) );





			//	Alert the operator of the error
			//
			MessageBeep ( 0xFFFFFFFF );
		}




		else
		{
			//	The number is valid, that is, it is in the specified range
			//
			//	Set the last valid value to the current number 
			//		in the edit control
			//
			myLastValidValue = ValidationNumber;
		}
	}
}










//*****************************************************************************
//
//	METHOD NAME :	CRangeEdit.SetRange
//
//	DESCRIPTION :	This member function will set the member variables that
//					represents the minimum and maximum number the edit
//					control will accept.
//
//	PARAMETERS :
//	NAME			I/O		TYPE			DESCRIPTION
//	inLMin			 I		LONG			Contains the minimum number the
//											edit control will accept.
//	inLMax			 I		LONG			Contains the maximum number the
//											edit control will accept.
//
//	RETURN TYPE :
//	TYPE			DESCRIPTION
//	n/a
//
//*****************************************************************************

void CRangeEdit::SetRange ( LONG inLMin, LONG inLMax )
{
	//	Set the member variables
	//
	myMin = inLMin;
	myMax = inLMax;
	myLastValidValue = myMin;
}












//*****************************************************************************
//
//	METHOD NAME :	CRangeEdit.RemoveLeadingZeros
//
//	DESCRIPTION :	This member function will remove all leading zeros
//					from the edit control.
//
//	PARAMETERS :
//	NAME			I/O		TYPE			DESCRIPTION
//	n/a
//
//	RETURN TYPE :
//	TYPE			DESCRIPTION
//	n/a
//
//*****************************************************************************

void CRangeEdit::RemoveLeadingZeros ( void )
{
	//	Local Variables
	//
	CString strWindowText;
	SHORT index;



	//	Initialize Variables
	//
	strWindowText.Empty ( );
	index = 0;




	
	//	Copy the contents of the edit control
	//		to a string
	//
	GetWindowText ( strWindowText );

	
	
	

	//	Check if the length of the text in the edit
	//		control is greater than 1
	//
	//	If the length is 1 then there can not be any
	//		leading zeroes
	//
	if ( strWindowText.GetLength ( ) > 1 )
	{
		//	Get the index of the first
		//		non-zero character
		//
		index = strWindowText.FindOneOf ( "123456789" );


		
		//	Check if there are any leading zeroes
		//		if the first non-zero character
		//		is at any position but 0, then
		//		there are leading zeros
		//
		if ( index > 0 )
		{
			//	Leading zeroes were found
			//		Remove them
			//
			strWindowText = strWindowText.Mid ( index );
		}



		//	Check if no non-zero characters were found
		//		That means there are only zeros in the
		//		string
		//
		else  if ( index == -1 )
		{
			//	There is only zeroes in the string
			//		change the string to only one zero
			//
			strWindowText = "0";
		}



		//	Check if the text was formatted, the index is not 0
		//
		if ( index != 0 )
		{
			//	The text was formatted, update the edit controls text
			//
			SetWindowText ( strWindowText );



			//	Set the cursor position
			//
			SetSel ( 0, 0 );
		}
	}
}






//	Undefine the BLANK_ENTRY definition
//
#undef BLANK_ENTRY