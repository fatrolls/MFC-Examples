///////////////////////////////////////////////////////////////////
//  Module  : PANEL3DC.H
//
//  Purpose : Interface for CPanel3dCtrl OLE control class
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-10-96
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
// CPanel3dCtrl - OLE control class

class CPanel3dCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPanel3dCtrl)

public:
   //
   // Enumerated types for this class
   //

   enum BevelStyle 
   { 
      bsNone, bsInset, bsRaised
   };   

   enum TextAlign 
   { 
      taLeftTop,    taLeftMid,   taLeftBottom, 
      taCenterTop,  taCenter,    taCenterBottom,
      taRightTop,   taRightMid,  taRightBottom
   };

public:
	CPanel3dCtrl();  // Constructor

// Override methods

	// Drawing method
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, 
      const CRect& rcInvalid);

	// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);

protected:
	~CPanel3dCtrl();   // Destructor

	DECLARE_OLECREATE_EX(CPanel3dCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CPanel3dCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CPanel3dCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CPanel3dCtrl)		// Type name and misc status

   //
   // Helper Methods
   //
   
   void DrawCaption(CDC* pDC, CRect& rc, HDC hDC);
   void DrawBevel(CDC* pDC, CRect& rc, CPen& pen1, CPen& pen2);
   void DrawBevelInset(CDC* pDC, CRect& rc);
   void DrawBevelRaised(CDC* pDC, CRect& rc);
   void DrawControl(CDC& dc);

   //
   // Dispatch maps
	//
   
   short  m_textAlignment;
	short  m_bevelWidth;
	short  m_bevelStyle;
	BOOL   m_drawText3d;
	BOOL   m_drawBorder;
	
   afx_msg void OnTextAlignmentChanged();
   afx_msg void OnBevelWidthChanged();
	afx_msg void OnBevelStyleChanged();
	afx_msg void OnDrawText3dChanged();
	afx_msg void OnDrawBorderChanged();
	
   DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

public:
   //
   // Dispatch IDs
	//
   
   enum {
	   dispidTextAlignment = 1L,
	   dispidBevelWidth    = 2L,
	   dispidBevelStyle    = 3L,
	   dispidDrawText3d    = 4L,
	   dispidDrawBorder    = 5L
	};
};

///////////////////////////////////////////////////////////////////