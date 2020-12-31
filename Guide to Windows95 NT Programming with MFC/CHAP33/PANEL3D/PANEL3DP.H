///////////////////////////////////////////////////////////////////
//  Module  : PANEL3DP.H
//
//  Purpose : Interface for CPanel3dPropPage property page class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-10-96
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
// CPanel3dPropPage - Property page class

class CPanel3dPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPanel3dPropPage)
	DECLARE_OLECREATE_EX(CPanel3dPropPage)

public:
	CPanel3dPropPage();  // Constructor

   //
   // Dialog Data
	//
   
   enum { IDD = IDD_PROPPAGE_PANEL3D };

	int		m_bevelWidth;
	CString	m_Caption;
	int		m_textAlignment;
	BOOL	   m_drawText3d;
	BOOL	   m_drawBorder;
	int		m_bevelStyle;

protected:
	//
   // DDX/DDV support
   //
   virtual void DoDataExchange(CDataExchange* pDX);    
};
