// ColorPickerCB.cpp
//
// (c) 1998 James R. Twine
//
// Based On Code That Was Found On www.codeguru.com, And Was 
// © 1997 Baldvin Hansson
//
//	Create A ComboBox (Drop List) And Set The
//	"Owner Draw Fixed" And "Has Strings" Styles/Checkboxes, And
//	Map This Class To It.  See?  Simple!
//


#if !defined(AFX_COLORPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_)
#define AFX_COLORPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//
//	Constants...
//
#define		CCB_MAX_COLORS			16							// Colors In List
#define		CCB_MAX_COLOR_NAME		16							// Max Chars For Color Name - 1


//
//	Internal Structure For Color/Name Storage...
//
struct	SColorAndName
{
	/**/	SColorAndName()
	{
		ZeroMemory( this, sizeof( SColorAndName ) );		// Init Structure
	};
	/**/	SColorAndName( COLORREF crColor, PCSTR cpColor )
	{
		ZeroMemory( this, sizeof( SColorAndName ) );		// Init Structure
		m_crColor = crColor;								// Set Color RGB Value
		strncpy( m_cColor, cpColor, CCB_MAX_COLOR_NAME );	// Set Color Name
	};
	COLORREF	m_crColor;									// Actual Color RGB Value
	char		m_cColor[ CCB_MAX_COLOR_NAME ];				// Actual Name For Color
};



class CColorPickerCB : public CComboBox
{
// Construction
public:
	CColorPickerCB();

// Attributes
private:
	bool			m_bInitialized;							// Control Initialized?
	CString			m_sColorName;							// Name Of Selected Color
	static
	SColorAndName	ms_pColors[ CCB_MAX_COLORS ];			// Array Of Colors And Names

private:

	void			Initialize( void );						// Initialize Control/Colors

public:
	COLORREF		GetSelectedColorValue( void );			// Get Selected Color Value
	CString			GetSelectedColorName( void );			// Get Selected Color Name

	void			SetSelectedColorValue( COLORREF crClr );// Set Selected Color Value
	void			SetSelectedColorName( PCSTR cpColor );	// Set Selected Color Name

	bool			RemoveColor( PCSTR cpColor );			// Remove Color From List
	bool			RemoveColor( COLORREF crClr );			// Remove Color From List
	
	int				AddColor( PCSTR cpNam, COLORREF crClr );// Insert A New Color

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPickerCB)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Implementation
public:
	virtual	~CColorPickerCB();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorPickerCB)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPICKERCB_H__C74333B7_A13A_11D1_ADB6_C04D0BC10000__INCLUDED_)
