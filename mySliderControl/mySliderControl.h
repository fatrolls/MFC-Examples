#pragma once


// CmySliderControl

class CmySliderControl :
public CSliderCtrl 
{
    CDC m_dcBk ;
    CBitmap m_bmpBk ;
    CBitmap*m_bmpBkOld ;
    //CBitmap* m_pbmpOldBk;
    CPen m_penThumb ;
    CPen m_penThumbLight ;
    CPen m_penThumbLighter ;
    CPen m_penThumbDark ;
    CPen m_penThumbDarker ;
    COLORREF m_crThumb ;
    COLORREF m_crThumbLight ;
    COLORREF m_crThumbLighter ;
    COLORREF m_crThumbDark ;
    COLORREF m_crThumbDarker ;
    // Construction
    public :
    CmySliderControl();
    // Attributes
    public :
    // Operations
    public :
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMySliderControl)
    //}}AFX_VIRTUAL
    // Implementation
    public :
    virtual~CmySliderControl();
    // Generated message map functions
    protected :
    //{{AFX_MSG(CMySliderControl)
    afx_msg void OnCustomDraw(NMHDR*pNMHDR,LRESULT*pResult);
    afx_msg BOOL OnEraseBkgnd(CDC*pDC);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

