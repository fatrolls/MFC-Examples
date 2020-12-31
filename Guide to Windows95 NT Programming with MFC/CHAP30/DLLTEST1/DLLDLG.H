///////////////////////////////////////////////////////////////////
//  Header   : DLLDLG.H
//
//  Purpose  : Interface for the CDllDlg class.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-02-96
///////////////////////////////////////////////////////////////////

#ifndef IDD_DIALOG1
   #define IDD_DIALOG1  129
#endif

///////////////////////////////////////////////////////////////////
// CDllDialog dialog

class AFX_EXT_CLASS CDllDialog : public CDialog
{
// Construction
public:
	CDllDialog(CWnd* pParent = NULL);   // standard constructor

   // Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
   // Overrides
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	// Message map functions
	virtual BOOL OnInitDialog();
};

///////////////////////////////////////////////////////////////////
