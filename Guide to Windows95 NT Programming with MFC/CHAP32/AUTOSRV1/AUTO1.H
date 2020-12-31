///////////////////////////////////////////////////////////////////
// Module  : AUTO1.H
//
// Purpose : Interface for the CAuto1 class.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 07-06-96
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CAuto1 command target class - OLE Automation server

class CAuto1 : public CCmdTarget
{
	DECLARE_DYNCREATE(CAuto1)
	CAuto1();    // protected constructor used by dynamic creation

public:
   // Overrides
	virtual void OnFinalRelease();
	
protected:
	virtual ~CAuto1();

	DECLARE_OLECREATE(CAuto1)

	// Dispatch map functions
	afx_msg float CalcGrossPay(float fHourlyWage, 
      float fHoursWorked);

   DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

///////////////////////////////////////////////////////////////////