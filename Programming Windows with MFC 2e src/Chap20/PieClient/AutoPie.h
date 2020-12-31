// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// CAutoPie wrapper class

class CAutoPie : public COleDispatchDriver
{
public:
	CAutoPie() {}		// Calls COleDispatchDriver default constructor
	CAutoPie(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAutoPie(const CAutoPie& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	LPDISPATCH GetChart();
	void SetChart(LPDISPATCH);
	LPDISPATCH GetWindow();
	void SetWindow(LPDISPATCH);
	LPDISPATCH GetToolbar();
	void SetToolbar(LPDISPATCH);

// Operations
public:
	void Quit();
};
/////////////////////////////////////////////////////////////////////////////
// CAutoChart wrapper class

class CAutoChart : public COleDispatchDriver
{
public:
	CAutoChart() {}		// Calls COleDispatchDriver default constructor
	CAutoChart(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAutoChart(const CAutoChart& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL Save(LPCTSTR pszPath);
	long GetRevenue(short nQuarter);
	void SetRevenue(short nQuarter, long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// CAutoWindow wrapper class

class CAutoWindow : public COleDispatchDriver
{
public:
	CAutoWindow() {}		// Calls COleDispatchDriver default constructor
	CAutoWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAutoWindow(const CAutoWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetVisible();
	void SetVisible(BOOL);

// Operations
public:
	void Refresh();
};
/////////////////////////////////////////////////////////////////////////////
// CAutoToolbar wrapper class

class CAutoToolbar : public COleDispatchDriver
{
public:
	CAutoToolbar() {}		// Calls COleDispatchDriver default constructor
	CAutoToolbar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAutoToolbar(const CAutoToolbar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetVisible();
	void SetVisible(BOOL);

// Operations
public:
};
