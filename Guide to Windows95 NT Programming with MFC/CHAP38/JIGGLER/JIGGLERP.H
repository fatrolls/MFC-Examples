///////////////////////////////////////////////////////////////////
//  Module  : JIGGLERC.CPP
//
//  Purpose : Interface for the CJigglerPropPage property page 
//            class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-27-96
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// The CJigglerPropPage class

class CJigglerPropPage : public COlePropertyPage
{
   DECLARE_DYNCREATE(CJigglerPropPage)
   DECLARE_OLECREATE_EX(CJigglerPropPage)

// Constructor
public:
   CJigglerPropPage();

// Dialog Data
   //{{AFX_DATA(CJigglerPropPage)
   enum { IDD = IDD_PROPPAGE_JIGGLER };
   CString   m_Caption;
   int      m_nInterval;
   //}}AFX_DATA

// Implementation
protected:
   // DDX/DDV support
   virtual void DoDataExchange(CDataExchange* pDX);    

// Message map
   //{{AFX_MSG(CJigglerPropPage)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

};

///////////////////////////////////////////////////////////////////



