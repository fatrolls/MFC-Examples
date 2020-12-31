///////////////////////////////////////////////////////////////////
//  Module  : JIGGLERC.H
//
//  Purpose : Interface for the CJigglerCtrl OLE control class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-27-96
///////////////////////////////////////////////////////////////////

#define IDC_TIMER1  100

///////////////////////////////////////////////////////////////////
// The CJigglerCtrl class

class CJigglerCtrl : public COleControl
{
   DECLARE_DYNCREATE(CJigglerCtrl)

// Constructor
public:
   CJigglerCtrl();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CJigglerCtrl)
   public:
   virtual void DoPropExchange(CPropExchange* pPX);
   //}}AFX_VIRTUAL

// Implementation
protected:
   CRect        m_rcBounds;     // Control bounding rect
   CFontHolder  m_fontDefault;  // Custom OLE font

   void JiggleText();

   DECLARE_OLECREATE_EX(CJigglerCtrl) // Class factory and guid
   DECLARE_OLETYPELIB(CJigglerCtrl)   // GetTypeInfo
   DECLARE_PROPPAGEIDS(CJigglerCtrl)  // Property page IDs
   DECLARE_OLECTLTYPE(CJigglerCtrl)   // Type name and misc status

// Message maps
   //{{AFX_MSG(CJigglerCtrl)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnDestroy();
   afx_msg void OnTimer(UINT nIDEvent);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   afx_msg void AboutBox();
   
// Event maps
   //{{AFX_EVENT(CJigglerCtrl)
   //}}AFX_EVENT
   DECLARE_EVENT_MAP()

// Dispatch maps
   //{{AFX_DISPATCH(CJigglerCtrl)
   short m_nInterval;
   afx_msg void OnIntervalChanged();
   afx_msg LPFONTDISP GetDefaultFont();
   afx_msg void SetDefaultFont(LPFONTDISP newValue);
   //}}AFX_DISPATCH
   DECLARE_DISPATCH_MAP()

// Dispatch and event IDs
public:
   enum {
   //{{AFX_DISP_ID(CJigglerCtrl)
   dispidInterval = 1L,
   dispidDefaultFont = 2L,
   //}}AFX_DISP_ID
   };
};

///////////////////////////////////////////////////////////////////
