// Grid.h : Declaration of the CGrid
// Written by Mario Zucca 
//        mailto:mario@GenoaValley.org
//        http://www.GenoaValley.org
//
// Copyright (c) 2000.
//
// The code contained in this file is based on the original
// Grid control written by Chris Maunder,
//        mailto:chris@codeproject.com
//        http://www.codeproject.com

#ifndef __GRID_H_
#define __GRID_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "GridCell.h"
#include "CellRange.h"	// Added by ClassView
#include "TitleTip.h"
#include "ATLNewGridCP.h"

#define IsSHIFTpressed() ( (GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0   )
#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )

/*
// Messages sent to the grid's parent (More will be added in future)
#define	GVN_BEGINLABELEDIT      LVN_BEGINLABELEDIT   // LVN_FIRST-5
#define	GVN_BEGINDRAG           LVN_BEGINDRAG        // LVN_FIRST-9
#define	GVN_BEGINRDRAG          LVN_BEGINRDRAG
#define GVN_COLUMNCLICK         LVN_COLUMNCLICK
#define	GVN_DELETEITEM          LVN_DELETEITEM
#define GVN_ENDLABELEDIT        LVN_ENDLABELEDIT     // LVN_FIRST-6
#define GVN_SELCHANGING         LVN_ITEMCHANGING 
#define GVN_SELCHANGED          LVN_ITEMCHANGED

.. no more messages, now we have events
*/
//////////////////////////////////////////////////////////////////
// Definizioni della grid
//////////////////////////////////////////////////////////////
#ifdef _WIN32_WCE
#define GRIDCONTROL_NO_TITLETIPS   // Do not use titletips for cells with large data
#define GRIDCONTROL_NO_DRAGDROP    // Do not use OLE drag and drop
#define GRIDCONTROL_NO_CLIPBOARD   // Do not use clipboard routines
#define GRIDCONTROL_NO_PRINTING    // Do not use printing routines

#ifdef WCE_NO_PRINTING
#define _WIN32_WCE_NO_PRINTING
#endif
#ifdef WCE_NO_CURSOR
#define _WIN32_WCE_NO_CURSOR
#endif

#else
// Use C++ exception handling instead of structured.
#undef TRY
#undef CATCH
#undef END_CATCH
#define TRY try
#define CATCH(ex_class, ex_object) catch(ex_class* ex_object)
#define END_CATCH
#endif  // _WIN32_WCE


// Use this as the classname when inserting this control as a custom control
// in the MSVC++ dialog editor
#define GRIDCTRL_CLASSNAME    _T("MFCGridCtrl")  // Window class name
#define IDC_INPLACE_CONTROL   8                  // ID of inplace edit controls

// storage typedef for each row in the grid
typedef std::vector<CGridCell*> GRID_ROW;
//typedef std::vector<CGridCell> GridCell;

#define SELECTED_CELL_FONT_WEIGHT 600    // weight of text for selected items
struct Rows
{
	UINT Height;
	_bstr_t Caption;

}; // Definizione delle righe
struct Cols
{
	UINT Width;
	_bstr_t Caption;

}; // Definizione delle colonne


// Get the number of lines to scroll with each mouse wheel notch
// Why doesn't windows give us this function???
UINT GetMouseScrollLines(); // Forward declaration

static const FONTDESC _fontdesc =
  { sizeof(FONTDESC), OLESTR("MS Sans Serif"), FONTSIZE( 8 ), NULL, 
     ANSI_CHARSET, FALSE, FALSE, FALSE };

/////////////////////////////////////////////////////////////////////////////
// CGrid
class ATL_NO_VTABLE CGrid : 
    // COM object implementation
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGrid, &CLSID_Grid>,
    // Control implementation
	public CComControl<CGrid>,
	public IOleControlImpl<CGrid>,
	public IOleObjectImpl<CGrid>,
	public IOleInPlaceActiveObjectImpl<CGrid>,
	public IViewObjectExImpl<CGrid>,
    // OC 96 specific
	public IOleInPlaceObjectWindowlessImpl<CGrid>,
	public IQuickActivateImpl<CGrid>,
    // Error info
	public ISupportErrorInfo,
    // Connection point
	public IConnectionPointContainerImpl<CGrid>,
 	public IProvideClassInfo2Impl<&CLSID_Grid, &DIID__IGridEvents, &LIBID_ATLNEWGRIDLib>,
   // Persistence
	public IPersistStreamInitImpl<CGrid>,
	public IPersistPropertyBagImpl<CGrid>,
    // Stock property
	public CStockPropImpl<CGrid, IGrid, &IID_IGrid, &LIBID_ATLNEWGRIDLib>,
    // Grid events
	public CProxy_IGridEvents< CGrid >
{
public:
    STDMETHODIMP GetMiscStatus (DWORD dwAspect, DWORD *pdwStatus);
	// Font
	HRESULT STDMETHODCALLTYPE put_Font(IFontDisp* pFont)
	{
		ATLTRACE2(atlTraceControls,2,_T("CGrid::put_Font\n"));
//		T* pT = (T*) this;
		if (FireOnRequestEdit(DISPID_FONT) == S_FALSE)
			return S_FALSE;
		m_pFont = 0;
		if (pFont)
		{
			CComQIPtr<IFont, &IID_IFont> p(pFont);
			if (p)
			{
				CComPtr<IFont> pFont;
				p->Clone(&pFont);
				if (pFont)
					pFont->QueryInterface(IID_IFontDisp, (void**) &m_pFont);
			}
		}
		m_bRequiresSave = TRUE;
		FireOnChanged(DISPID_FONT);
		FireViewChange();
		SendOnDataChange(NULL);
		SetFont(pFont);
		return S_OK;
	}
	HRESULT STDMETHODCALLTYPE putref_Font(IFontDisp* pFont)
	{
		ATLTRACE2(atlTraceControls,2,_T("CStockPropImpl::putref_Font\n"));
	//	T* pT = (T*) this;
		if (FireOnRequestEdit(DISPID_FONT) == S_FALSE)
			return S_FALSE;
		m_pFont = pFont;
		m_bRequiresSave = TRUE;
		FireOnChanged(DISPID_FONT);
		FireViewChange();
		SendOnDataChange(NULL);
		SetFont(pFont);
		return S_OK;
	}
	~CGrid() 
	{
		if(m_Font)
			DeleteObject(m_Font);
	}
	CGrid()
	{
		// Initializaton
		m_vbKeepTab = VARIANT_FALSE;
		 m_Font=NULL;
    		m_nRows=0; m_nCols=0;
    		m_nFixedRows=0; m_nFixedCols=0;
    		m_nDefCellHeight=10; // These will get changed to something meaningful
    		m_nDefCellWidth=30;  //    when the window is created or subclassed
		m_nVScrollMax=0; m_nHScrollMax=0;       // Scroll position
		m_nMargin=0;         // cell padding
		m_MouseMode=MOUSE_NOTHING; m_nGridLines=GVL_BOTH;
		m_bEditable=TRUE; m_bListMode=FALSE;
		m_bSingleRowSelection=FALSE; m_bAllowDraw=TRUE;      // allow draw updates
		m_bEnableSelection=TRUE; m_bAllowRowResize=TRUE;
		m_bAllowColumnResize=TRUE; m_bSortOnClick=TRUE;      // Sort on header row click if in list mode
		m_bHandleTabKey=TRUE;
		// Set the colours
		m_crWindowText=::GetSysColor(COLOR_WINDOWTEXT);
		m_crWindowColour=::GetSysColor(COLOR_WINDOW);
		m_cr3DFace=::GetSysColor(COLOR_3DFACE); m_crShadow=::GetSysColor(COLOR_3DSHADOW);
		m_crGridColour=RGB(192,192,192); m_crFixedBkColour=m_cr3DFace;
		m_crTextColour=m_crWindowText;	m_crTextBkColour=m_crWindowColour;
		m_crBkColour=m_crShadow; m_crFixedTextColour=m_crWindowText;
		m_bTitleTips=TRUE; m_TitleTip =NULL;     // show cell title tips
		m_bAscending=TRUE; m_SortColumn=-1;     // sorting stuff
		m_nTimerID=0;         // For drag-selection
		m_nTimerInterval=25;        // =in milliseconds
		m_nResizeCaptureRange=3;        // When resizing columns/row; the cursor has to be 
		                              // within +/-3 pixels of the dividing line for 
		                              // resizing to be possible
		m_pImageList=NULL;      
		m_bAllowDragAndDrop=FALSE;     // for drag and drop


		m_bWindowOnly=TRUE;
		FONTDESC fd = _fontdesc;
		OleCreateFontIndirect(&fd,IID_IFontDisp,(void**)&m_pFont);
	
	    m_nRowsPerWheelNotch = GetMouseScrollLines(); // Get the number of lines
	                                                  // per mouse wheel notch to scroll
	
	#ifdef _WIN32_WCE
	    m_bDoubleBuffer      = FALSE;     // Use double buffering to avoid flicker?
	#else
	    m_bDoubleBuffer      = TRUE;      // Use double buffering to avoid flicker?
	#endif
	
	#ifndef _WIN32_WCE
	    // Initially use the system message font for the GridCtrl font
	    NONCLIENTMETRICS ncm;
	    ncm.cbSize = sizeof(NONCLIENTMETRICS);
	    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	    memcpy(&m_Logfont, &(ncm.lfMessageFont), sizeof(LOGFONT));
	#else
	    LOGFONT lf;
	    GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
	    memcpy(&m_Logfont, &lf, sizeof(LOGFONT));
	#endif
	
	 
	    // set initial selection range (ie. none)
	//    m_SelectedCellMap.RemoveAll();
	//    m_PrevSelectedCellMap.RemoveAll();
	    m_SelectedCellMap.clear();
	    m_PrevSelectedCellMap.clear();
	
	    // The number of rows and columns will only be non-zero if theructor
	    // was called with non-zero initialising parameters. If this window was created
	    // using a dialog template then the number of rows and columns will be 0 (which
	    // means that the code below will not be needed - which is lucky 'cause it ain't
	    // gonna get called in a dialog-template-type-situation.
	
			
	        m_arRow.resize(0);    // initialize row heights
	        m_arCol.resize(0);     // initialize column widths
			m_crBkColour = RGB(128,128,128);
			m_crTextBkColour = RGB(255,255,255);
			m_crFixedBkColour = RGB(192,192,192);
			put_ColumnCount(10);
			put_RowCount(10);
			put_FixedRows(1);
			put_FixedCols(1);

	} // End ctor

DECLARE_REGISTRY_RESOURCEID(IDR_GRID)
DECLARE_NOT_AGGREGATABLE(CGrid)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGrid)
	COM_INTERFACE_ENTRY(IGrid)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY(IPersistPropertyBag)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CGrid)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	// Example entries
	PROP_ENTRY("RowCount", 4, CLSID_NULL)
	PROP_ENTRY("ColumnCount", 5, CLSID_NULL)
	PROP_ENTRY("ColumnResizing", 12, CLSID_NULL)
	PROP_ENTRY("RowResizing", 13, CLSID_NULL)
	PROP_ENTRY("GridLines", 14, CLSID_NULL)
	PROP_ENTRY("Editable", 15, CLSID_NULL)
	PROP_ENTRY("FixedRows", 16, CLSID_NULL)
	PROP_ENTRY("FixedCols", 17, CLSID_NULL)
	PROP_ENTRY("AllowSelection", 21, CLSID_NULL)
	PROP_ENTRY("ListMode", 22, CLSID_NULL)
	PROP_ENTRY("HeaderSort", 26, CLSID_NULL)
	PROP_ENTRY("SingleRowSelection", 27, CLSID_NULL)
	PROP_ENTRY("BackColor", 29, CLSID_NULL)
	PROP_ENTRY("FixedBackColor", 30, CLSID_NULL)
	PROP_ENTRY("TextColor", 31, CLSID_NULL)
	PROP_ENTRY("TextBackColor", 32, CLSID_NULL)
	PROP_ENTRY("Color", 33, CLSID_NULL)
	PROP_ENTRY("FixedTextColor", 34, CLSID_NULL)
	PROP_ENTRY("ToolTip", 39, CLSID_NULL)
	PROP_ENTRY("KeepTab", 42, CLSID_NULL)
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CGrid)
	CONNECTION_POINT_ENTRY(DIID__IGridEvents)
//	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)

END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CGrid)
	CHAIN_MSG_MAP(CComControl<CGrid>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_CHAR, OnChar)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
	MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
	MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_COMMAND,OnCommand)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_USER, OnWMUser)
END_MSG_MAP()

   BOOL PreTranslateAccelerator(LPMSG pMsg, HRESULT& hRet);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			 &IID_IGrid,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IGrid
public:
	STDMETHOD(get_KeepTab)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_KeepTab)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(SelectAllCells)();
	STDMETHOD(Refresh)();
	STDMETHOD(get_ToolTip)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_ToolTip)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Cell)(/*[in]*/ int Row,/*[in]*/ int Col, /*[out, retval]*/ IGridCell* *pVal);
	STDMETHOD(put_Cell)(/*[in]*/ int Row,/*[in]*/ int Col, /*[in]*/ IGridCell* newVal);
	STDMETHOD(SimpleConf)();
	// Stock properties
	CComPtr<IFontDisp> m_pFont;
	
	STDMETHOD(get_CellBgColor)(/*[in]*/ int Row, /*[in]*/ int Col, /*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_CellBgColor)(/*[in]*/ int Row, /*[in]*/ int Col, /*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_CellFgColor)(/*[in]*/ int Row, /*[in]*/ int Col, /*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_CellFgColor)(/*[in]*/ int Row, /*[in]*/ int Col, /*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_FixedTextColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_FixedTextColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_Color)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_Color)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_TextBackColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_TextBackColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_TextColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_TextColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_FixedBackColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_FixedBackColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_BackColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_BackColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(DeleteColumn)(int col);
	void EmptyCell(CGridCell* pCell, int nRow, int nCol);
	STDMETHOD(get_SingleRowSelection)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_SingleRowSelection)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_HeaderSort)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_HeaderSort)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(DeleteRow)(/*[in]*/ int row);
	STDMETHOD(get_CurrentCol)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_CurrentCol)(/*[in]*/ int newVal);
	STDMETHOD(get_CurrentRow)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_CurrentRow)(/*[in]*/ int newVal);
	STDMETHOD(get_ListMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_ListMode)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_AllowSelection)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_AllowSelection)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_CellEnabled)(/*[in]*/ int row,/*[in]*/ int col, /*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_CellEnabled)(/*[in]*/ int row,/*[in]*/ int col, /*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(AutosizeColumn)(/*[in]*/ int col);
	STDMETHOD(AutosizeRow)(/*[in]*/ int row);
	STDMETHOD(get_FixedCols)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_FixedCols)(/*[in]*/ int newVal);
	STDMETHOD(get_FixedRows)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_FixedRows)(/*[in]*/ int newVal);
	STDMETHOD(get_Editable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Editable)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_GridLines)(/*[out, retval]*/ grGridLines *pVal);
	STDMETHOD(put_GridLines)(/*[in]*/ grGridLines newVal);
	STDMETHOD(get_RowResizing)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_RowResizing)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_ColumnResizing)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_ColumnResizing)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(AutoSize)();
	STDMETHOD(get_CellFont)(/*[in]*/ int Row,/*[in]*/ int Col, /*[out, retval]*/ IFontDisp* *pVal);
	STDMETHOD(put_CellFont)(/*[in]*/ int Row,/*[in]*/ int Col, /*[in]*/ IFontDisp* newVal);
	STDMETHOD(get_ColumnWidth)(/*[in]*/ int Col, /*[out, retval]*/ int *pVal);
	STDMETHOD(put_ColumnWidth)(/*[in]*/ int Col, /*[in]*/ int newVal);
	STDMETHOD(get_RowHeight)(/*[in]*/ int nRow, /*[out, retval]*/ int *pVal);
	STDMETHOD(put_RowHeight)(/*[in]*/ int nRow, /*[in]*/ int newVal);
	STDMETHOD(get_ColumnCount)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_ColumnCount)(/*[in]*/ int newVal);
	STDMETHOD(get_RowCount)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_RowCount)(/*[in]*/ int newVal);
	STDMETHOD(InsertRow)(/*[in]*/ int Row,/*[in]*/ BSTR caption);
	STDMETHOD(get_Text)(/*[in]*/ int Row,/*[in]*/ int Col, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Text)(/*[in]*/ int Row,/*[in]*/ int Col, /*[in]*/ BSTR newVal);
	STDMETHOD(get_Image)(/*[in]*/ int Row,/*[in]*/ int Col, /*[out, retval]*/ short *pVal);
	STDMETHOD(put_Image)(/*[in]*/ int Row,/*[in]*/ int Col, /*[in]*/ short newVal);

// Attributes
protected:


    CTitleTip*   m_TitleTip;             // Title tips for cells
    // Drag and drop
    CCellID     m_LastDragOverCell;
#ifndef GRIDCONTROL_NO_DRAGDROP
    CGridDropTarget m_DropTarget;       // OLE Drop target for the grid
#endif
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		put_RowCount(0);
		put_ColumnCount(0);
		if(m_TitleTip)
		{
			//ATLASSERT(m_TitleTip->DestroyWindow());
// if uncomment the following line we have a crash in release mode why ??
			delete m_TitleTip;
		}
		return DefWindowProc();
	}
////////////////////////////////////////////////////////////
// Grid Operations
////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	// Message Handler
	///////////////////////////////////////////////////////////////////////////////
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
////////////////////////////////////////////////////////////
// End Grid Operations
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Grid Drawing
////////////////////////////////////////////////////////////
	BOOL RedrawCell(const CCellID &cell, HDC hDC = NULL);
	BOOL RedrawCell(int nRow, int nCol, HDC hDC);
	BOOL DrawFixedCell(HDC hDC, int nRow, int nCol, RECT rect, BOOL bEraseBk);
	void DrawGrid(HDC hDC,RECT rc);
	void EraseBkgnd(HDC hDC,RECT rc);
	BOOL InvalidateCellRect(const CCellID &cell);
	BOOL InvalidateCellRect(const CCellRange &cellRange);
////////////////////////////////////////////////////////////
// End Grid Drawing
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Grid Attributes
////////////////////////////////////////////////////////////
//    void SetImageList(HIMAGELIST pList)          { m_pImageList = pList;             }
//    HIMAGELIST GetImageList()              { return m_pImageList;              }

//    CCellID GetFocusCell()                  { return m_idCurrentCell;           }
//    COLORREF GetTextColor()                 { return m_crTextColour;            }
//    COLORREF GetTextBkColor()               { return m_crTextBkColour;          }
//    COLORREF GetFixedTextColor()            { return m_crFixedTextColour;       }
//    COLORREF GetFixedBkColor()              { return m_crFixedBkColour;         } 

//    int  GetColumnCount()                 { return m_nCols; }

//    void EnableDragAndDrop(BOOL bAllow = TRUE)    { m_bAllowDragAndDrop = bAllow;     }
//    BOOL GetDragAndDrop()                   { return m_bAllowDragAndDrop;       }
//    void SetHandleTabKey(BOOL bHandleTab = TRUE)  { m_bHandleTabKey = bHandleTab;     }
//    BOOL GetHandleTabKey()                  { return m_bHandleTabKey;           }
//	int GetSelectedCount() { return m_SelectedCellMap.size(); }

    BOOL GetSingleRowSelection();

	CGridCell* CreateCell(int nRow, int nCol);
	CCellID SetFocusCell(int nRow, int nCol);
	CCellID SetFocusCell(CCellID cell);
	void ResetScrollBars();
	SIZE GetTextExtent(LPCTSTR str, BOOL bUseSelectedFont  = TRUE);
	int GetScrollPos32(int nBar, BOOL bGetTrackPos = FALSE);
	SIZE GetCellExtent(int nRow, int nCol, HDC hDC);
	BOOL GetCellRangeRect(const CCellRange &cellRange, LPRECT lpRect);
	CCellID GetTopleftNonFixedCell();
	// This gets even partially visible cells
	CCellRange GetVisibleNonFixedCellRange(LPRECT pRect);
	BOOL IsCellVisible(CCellID cell);
	BOOL IsCellVisible(int nRow, int nCol);
	BOOL GetCellOrigin(int nRow, int nCol, LPPOINT p);
	BOOL GetCellOrigin(const CCellID &cell, LPPOINT p);
	BOOL GetCellRect(const CCellID &cell, LPRECT pRect);
	BOOL GetCellRect(int nRow, int nCol, LPRECT pRect);
	BOOL IsCellEditable(CCellID &cell);
	BOOL IsCellEditable(int nRow, int nCol);
	CCellRange GetUnobstructedNonFixedCellRange();
	CCellID GetCellFromPt(long x,long y, 
		BOOL bAllowFixedCellCheck = TRUE);
	BOOL SetFont(LOGFONT lf);
	int NewRow(_bstr_t strHeading, int nRow);
	long GetVirtualWidth();
	long GetVirtualHeight();
//	BOOL SetColumnWidth(int nCol, int width);
//	BOOL SetRowHeight(int nRow, int height);
	int GetFixedRowHeight();
	BOOL IsValid(int nRow, int nCol);
	BOOL IsValid(const CCellID &cell);
	BOOL IsValid(const CCellRange &range);
	// Indica se l'iteratore delle celle selezionate viene o meno invalidato
	BOOL SetItemState(int nRow, int nCol, UINT state, BOOL* itInv= NULL);
	int GetRowHeight(int nRow);
	int GetFixedColumnWidth();
	int GetColumnWidth(int nCol);
	CGridCell* GetCell(int nRow, int nCol);
	BOOL GetTextRect(int nRow, int nCol, LPRECT pRect);
	CCellID GetCellFromPt(POINT point, BOOL bAllowFixedCellCheck = TRUE);

	// BOOL GetItem(GV_ITEM* pItem);

private:
	VARIANT_BOOL m_vbKeepTab;
	virtual HRESULT OnDraw(ATL_DRAWINFO& di);
	void ResetSelectedRange();
	void AutoSizeRows();
	// selects columns
	void SelectColumns(CCellID currentCell);
	// selects rows
	void SelectRows(CCellID currentCell);
	// selects cells
	void SelectCells(CCellID currentCell);
	BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data, int low, int high);
	inline BOOL SetCell(int nRow, int nCol, CGridCell *pCell);
	BOOL SetScrollPos32(int nBar, int nPos, BOOL bRedraw = TRUE );
	void SetModified(BOOL bModified, int nRow, int nCol);
	void EnsureVisible(int nRow, int nCol);
	void EnsureVisible(CCellID &cell);
	void OnFixedRowClick(CCellID &cell);
	void OnFixedColumnClick(CCellID &cell);
	BOOL MouseOverColumnResizeArea(POINT point);
	BOOL MouseOverRowResizeArea(POINT point);
	void OnSelecting(const CCellID &currentCell);
	BOOL SortTextItems(int nCol, BOOL bAscending);
	BOOL SortTextItems(int nCol, BOOL bAscending, int low, int high);
	BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol,
					  BOOL bAscending, LPARAM data);
	void SetSelectedRange(const CCellRange &Range, 
							BOOL bForceRepaint = FALSE );
	void SetSelectedRange(int nMinRow, int nMinCol, 
						  int nMaxRow, int nMaxCol,
						  BOOL bForceRepaint = FALSE );
//	LRESULT SendMessageToParent(int nRow, int nCol, int nMessage);
	BOOL AutoSizeRow(int nRow);
	void OnEditCell(int nRow, int nCol, UINT nChar);
	void SetFont(IFontDisp* font);
	UINT GetItemState(int nRow, int nCol);

    // Cell size details
    int         m_nRows, m_nFixedRows, m_nCols, m_nFixedCols;
    // General attributes
    COLORREF    m_crTextColour, m_crTextBkColour, m_crBkColour,   // Grid colours
                m_crFixedTextColour, m_crFixedBkColour, m_crGridColour;
    COLORREF    m_crWindowText, m_crWindowColour, m_cr3DFace,     // System colours
                m_crShadow;    

    grGridLines         m_nGridLines;
    BOOL        m_bEditable;
    BOOL        m_bModified;
    BOOL        m_bAllowDragAndDrop;
    BOOL        m_bListMode;
    VARIANT_BOOL        m_bSingleRowSelection;
    BOOL        m_bAllowDraw;
    BOOL        m_bEnableSelection;
    VARIANT_BOOL        m_bSortOnClick;
    BOOL        m_bHandleTabKey;
    BOOL        m_bDoubleBuffer;
    BOOL        m_bTitleTips;

	std::vector<Rows>  m_arRow;
	std::vector<Cols> m_arCol;
    int         m_nMargin;
    int         m_nDefCellWidth, m_nDefCellHeight;
    int         m_nVScrollMax, m_nHScrollMax;

    // Fonts and images
    LOGFONT     m_Logfont;
    HFONT       m_PrinterFont,  // for the printer
                m_Font;         // for the grid
    HIMAGELIST  m_pImageList;

    // Mouse operations such as cell selection
    int         m_MouseMode;
    POINT      m_LeftClickDownPoint, m_LastMousePoint;

    int         m_nTimerID;
    int         m_nTimerInterval;
    int         m_nResizeCaptureRange;
    BOOL        m_bAllowRowResize, m_bAllowColumnResize;
    int         m_nRowsPerWheelNotch;
    // Printing information
    SIZE       m_CharSize;
    int         m_nPageHeight;
    SIZE       m_LogicalPageSize,      // Page size in gridctrl units.
                m_PaperSize;            // Page size in device units.

    // sorting
    int         m_bAscending;
    int         m_SortColumn;

    enum eMouseModes { MOUSE_NOTHING, MOUSE_SELECT_ALL, MOUSE_SELECT_COL, MOUSE_SELECT_ROW,
                       MOUSE_SELECT_CELLS, MOUSE_SCROLLING_CELLS,
                       MOUSE_OVER_ROW_DIVIDE, MOUSE_SIZING_ROW, 
                       MOUSE_OVER_COL_DIVIDE, MOUSE_SIZING_COL,
                       MOUSE_PREPARE_EDIT,
#ifndef GRIDCONTROL_NO_DRAGDROP
                       MOUSE_PREPARE_DRAG, MOUSE_DRAGGING
#endif
    };
	    // Cell data
	std::vector<GRID_ROW*> m_RowData;
//	std::vector<GridCell > m_RowData;

    CCellID     m_LeftClickDownCell, m_SelectionStartCell;
    CCellID     m_idCurrentCell;
//    CMap<DWORD,DWORD, CCellID, CCellID&> m_SelectedCellMap, m_PrevSelectedCellMap;
	typedef std::map<long,CCellID> selMap;
	typedef selMap::value_type ValuePair;

    selMap m_SelectedCellMap, m_PrevSelectedCellMap;
////////////////////////////////////////////////////////////
// End Grid Attributes
////////////////////////////////////////////////////////////



	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_pImageList = ImageList_LoadImage(_Module.m_hInst,
			MAKEINTRESOURCE(IDB_IMAGES),
			16, 1, RGB(255,255,255),
			IMAGE_BITMAP,
			LR_LOADMAP3DCOLORS | LR_DEFAULTCOLOR);
	
		// Create titletips
		#ifndef GRIDCONTROL_NO_TITLETIPS
		// Attenzione baco sulla gestione dei titleTips
		    if (m_bTitleTips)
			{
				m_TitleTip = new CTitleTip;
		        m_TitleTip->Create(m_hWnd);
			}
					
		#endif
		return 0;
	}
	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}



	LRESULT OnWMUser(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		CGridCell*pCell = GetCell((int) wParam,(int) lParam);
		if(pCell)
			pCell->StopEdit();
		return 0;
	}
};
#endif //__GRID_H_
