// PropertiesBar.cpp : implementation file
//

#include "stdafx.h"
#include "skinsdemo.h"
#include "PropertiesBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesBar

const UINT IDC_PROPERTIES = 1001;

CPropertiesBar::CPropertiesBar()
{
}

CPropertiesBar::~CPropertiesBar()
{
}


BEGIN_MESSAGE_MAP(CPropertiesBar, COXSizeControlBar)
	//{{AFX_MSG_MAP(CPropertiesBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPropertiesBar message handlers

int CPropertiesBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_wndProperties.Create(NULL, NULL, WS_VISIBLE | WS_CHILD, CRect(0,0,0,0), this/*,
		IDC_PROPERTIES*/))
	{
		return -1;
	}

	// Uncomment the next line if you want to hide the combo box
	// m_wndProperties.ShowCombo(FALSE);

	// Put some items in the combo box
	for (int i = 0; i < 10; i++)
	{
		COMBOBOXEXITEM cbi;
		cbi.iItem = i;
		cbi.mask = CBEIF_TEXT;
		CString strText;
		strText.Format(_T("Item %d"), i);
		cbi.pszText = (TCHAR*)(LPCTSTR) strText;
		m_wndProperties.GetComboBoxEx().InsertItem(&cbi);
	}

	// Uncomment the next line if you want to hide the toolbar
	// m_wndProperties.ShowToolBar(FALSE);
	
	InitProperties();

	return 0;
}

void CPropertiesBar::OnSize(UINT nType, int cx, int cy) 
{
	COXSizeControlBar::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rectClient;
	GetClientRect(rectClient);
	m_wndProperties.MoveWindow(rectClient);	
}

void CPropertiesBar::InitProperties()
{
	ASSERT(::IsWindow(m_hWnd));	// this window must be already created

	HPROPERTY hProperty;
	
	// Text
	hProperty= m_wndProperties.InsertProperty(
		_T("Text"),											// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a text field."),		// property description
		_T("Data"),											// category
		&m_textEditor);										// editor window

	// Read-only field (no editor)
	hProperty= m_wndProperties.InsertProperty(
		_T("Serial Number"),								// property name
		_T("K67-FR45-5"),									// initail value
		_T("Demonstrates the use of a read-only field."),	// property description
		_T("Data"));										// category

	// List of items
	CStringArray items;
	items.Add(_T("New York"));
	items.Add(_T("Chicago"));
	items.Add(_T("London"));
	items.Add(_T("Paris"));
	items.Add(_T("Toronto"));
	items.Add(_T("Berlin"));
	items.Add(_T("Rome"));
	items.Add(_T("Los Angeles"));

	m_listEditor.SetListItems(&items, &m_wndProperties);	// set the list of items
	hProperty= m_wndProperties.InsertProperty(
		_T("City"),											// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a list field."),		// property description
		_T("Data"),											// category
		&m_listEditor);										// editor window

	// Number
	hProperty= m_wndProperties.InsertProperty(
		_T("Number"),										// property name
		_T("0.00"),											// initail value
		_T("Demonstrates the use of a numeric field."),		// property description
		_T("Data"),											// category
		&m_numericEditor);									// editor window

	// Phone number (using COXMaskedEdit)
	m_phoneNumberEditor.SetMask(_T("(###) ###-#### Ex.###"));
	hProperty= m_wndProperties.InsertProperty(
		_T("Telephone"),									// property name
		_T("(   )    -     Ex."),							// initail value
		_T("Demonstrates the use of a masked field."),		// property description
		_T("Data"),											// category
		&m_phoneNumberEditor);								// editor window

	// Currency
	hProperty= m_wndProperties.InsertProperty(
		_T("Currency"),										// property name
		_T("$0.00"),										// initail value
		_T("Demonstrates the use of a currency field."),	// property description
		_T("Data"),											// category
		&m_currencyEditor);									// editor window

	// IP Address
	hProperty= m_wndProperties.InsertProperty(
		_T("IP Address"),									// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a ip address field."),	// property description
		_T("Data"),											// category
		&m_ipAddressEditor);								// editor window

	// Date (use "dd" to specify the day, "mm" to specify the month
	// and either "yy" or "yyyy" to specify the year)
	m_dateEditor.SetDateFormat(_T("dd/mm/yyyy"));
	hProperty= m_wndProperties.InsertProperty(
		_T("Date"),											// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a date field."),		// property description
		_T("Data"),											// category
		&m_dateEditor);										// editor window

	// Time
	hProperty= m_wndProperties.InsertProperty(
		_T("Time"),											// property name
		_T("1.00 s"),										// initail value
		_T("Demonstrates the use of a time field."),		// property description
		_T("Physical Fields"),								// category
		&m_timeEditor);										// editor window
	
	// Angle
	hProperty = m_wndProperties.InsertProperty(
		_T("Angle"),										// property name
		_T("0.00 °"),										// initail value
		_T("Demonstrates the use of an angle field."),		// property description
		_T("Physical Fields"),								// category
		&m_angleEditor);									// editor window
	
	// Length
	hProperty = m_wndProperties.InsertProperty(
		_T("Length"),										// property name
		_T("0.00 m"),										// initail value
		_T("Demonstrates the use of a length field."),		// property description
		_T("Physical Fields"),								// category
		&m_lengthEditor);									// editor window
	
	// Temperature
	hProperty = m_wndProperties.InsertProperty(
		_T("Temperature"),									// property name
		_T("0.00 °C"),										// initail value
		_T("Demonstrates the use of a temparature field."),	// property description
		_T("Physical Fields"),								// category
		&m_temperatureEditor);								// editor window

	// Color
	hProperty = m_wndProperties.InsertProperty(
		_T("Color"),										// property name
		_T("None"),											// initail value
		_T("Demonstrates the use of a color field."),		// property description
		_T("Miscellaneous"),								// category
		&m_colorEditor);									// editor window

	// Calculator
	hProperty = m_wndProperties.InsertProperty(
		_T("Calculator"),									// property name
		_T("0.00"),											// initail value
		_T("Demonstrates the use of a calculator field."),	// property description
		_T("Miscellaneous"),								// category
		&m_calculatorEditor);								// editor window

	// Directory
	hProperty = m_wndProperties.InsertProperty(
		_T("Directory"),									// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a directory field."),	// property description
		_T("Miscellaneous"),								// category
		&m_directoryEditor);								// editor window

	// Filename
	hProperty = m_wndProperties.InsertProperty(
		_T("Filename"),										// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a filename field."),	// property description
		_T("Miscellaneous"),								// category
		&m_filenameEditor);									// editor window
}

