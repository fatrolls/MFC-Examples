///////////////////////////////////////////////////////////////////
// Header  : SIZEDLG.H
//
// Purpose : Header for class CWndSizeDlg
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 05-22-96
///////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CWndSizeDlg dialog

class CWndSizeDlg : public CDialog
{
// Construction
public:
	CWndSizeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_WNDSIZE };
	INT   m_nRadioBtn;
   UINT	m_uWidth;
	UINT	m_uHeight;

// Overrides
protected:
   // DDX/DDV support
   virtual void DoDataExchange(CDataExchange* pDX);    

// Implementation
protected:
   void ResizeParent(UINT uWidth, UINT uHeight);
   void SetNewSize(UINT uWidth, UINT uHeight);
	
   // Message handlers
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadioSizeClick();

   DECLARE_MESSAGE_MAP()

private:
   //
   // Control access methods to return control references
   //
   
   // Edit controls and labels
   CButton& editWidth() 
      { return *(CButton*) GetDlgItem(IDC_EDIT_WIDTH); }
   CButton& editHeight() 
      { return *(CButton*) GetDlgItem(IDC_EDIT_HEIGHT); }
   CButton& statWidth() 
      { return *(CButton*) GetDlgItem(IDC_STATIC_WIDTH); }
   CButton& statHeight() 
      { return *(CButton*) GetDlgItem(IDC_STATIC_HEIGHT); }

   // Radio buttons
   CButton& btn320() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_320); }
   CButton& btn640() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_640); }
   CButton& btn800() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_800); }
   CButton& btn1024() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_1024); }
   CButton& btnDesktop() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_DESKTOP); }
   CButton& btnCustom() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_CUSTOM); }

};
