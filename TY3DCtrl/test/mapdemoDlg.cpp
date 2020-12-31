 

#include "stdafx.h"
#include "mapdemo.h"
#include "mapdemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CMapDemoDlg::CMapDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapDemoDlg::IDD, pParent)
 
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
 
}
CMapDemoDlg::~CMapDemoDlg() 
{
 
}
void CMapDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_MXOBJECT1, mScene);
    DDX_Control(pDX, IDC_11, mProjTree);
 
}

BEGIN_MESSAGE_MAP(CMapDemoDlg, CDialog)
    ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
	ON_WM_TIMER()
    ON_WM_CLOSE()
   
END_MESSAGE_MAP()


//   message handlers

BOOL CMapDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
    TCHAR path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    CString str = path;
    int pos = str.ReverseFind('\\'); 
    _tcscpy(path+pos+1, _T("111.png")); 
    mScenePtr = mScene.GetControlUnknown();
    ASSERT(mScenePtr != NULL);
    mTreePtr = mProjTree.GetControlUnknown();
    ASSERT(mTreePtr != NULL);

    str = _T("<image driver=\"gdal\" name=\"world-tiff\" cache_enabled=\"false\"> \
        <url>D:/osgearth/osgearth/data/world.tif</url>\
        <caching_policy usage=\"no_cache\"/>    \
        </image>");
    BSTR xml = str.AllocSysString();
    CLSID clsidConfig;
    HRESULT hr=CLSIDFromProgID(OLESTR("TY3DCtrl.ConfigOpt.1"),&clsidConfig);   
    IConfigOptPtr config(clsidConfig);
    config->FromXML(IMAGELAYEROPT, xml);
    mScenePtr->GetMap()->AddLayer(config);
    config.Release();
    SysFreeString(xml);


	str = _T("<model name=\"cities\" driver=\"feature_geom\">\
		<features name=\"cities\" driver=\"ogr\">\
		<url>D:/osgearth/osgearth/data/world.shp</url>\
		<change_attribute key=\"cntry_name\" value=\"osgEarthLand\"/>\
		</features>\
		<styles>\
		<style type=\"text/css\">      \
			cities {\
				text-provider:  annotation;\
				text-content:   [cntry_name];\
				text-priority:  [pop_cntry];\
				text-halo:      #3f3f7f;\
				text-align:     center_center;\
				text-declutter: true;\
			}    \
		</style>\
		</styles>\
		</model>");
    xml = str.AllocSysString();

    IConfigOptPtr config2(clsidConfig);
    config2->FromXML(MODELLAYEROPT, xml);
    mScenePtr->GetMap()->AddLayer(config2);
    config2.Release();
    SysFreeString(xml);

    VARIANT var;
    VariantInit(&var);
    var.vt = VT_DISPATCH;
    var.pdispVal= mScenePtr.GetInterfacePtr();
    mTreePtr->AttachScene(var);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMapDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
    else
    {        
        CPaintDC dc(this); // device context for painting
        CRect rc;
        GetDlgItem(IDC_MXOBJECT1)->GetWindowRect(&rc);
        ScreenToClient(&rc);
        rc.InflateRect(2,2);
        dc.DrawEdge(&rc, EDGE_SUNKEN, BF_RECT );//»æÖÆµØÍ¼±ß¿ò
        CDialog::OnPaint();

    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMapDemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

 

void CMapDemoDlg::OnDestroy()
{
 
}
 
BEGIN_EVENTSINK_MAP(CMapDemoDlg, CDialog)
 
END_EVENTSINK_MAP()
 
 

 

void CMapDemoDlg::OnClose()
{
    CDialog::OnClose();
    OnCancel();
}
 
BOOL CMapDemoDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    if(pMsg->message==WM_KEYDOWN)
    {
        if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
            pMsg->wParam=NULL ;
    }

    return CDialog::PreTranslateMessage(pMsg);
}  
 

void CMapDemoDlg::OnSize( UINT nType, int cx, int cy )
{
    if (mProjTree.m_hWnd && mScene.m_hWnd)
    {
 
        CRect rc;
        GetWindowRect(&rc);
        ScreenToClient(&rc);
        CRect rc2;
        mProjTree.GetWindowRect(&rc2);
        mProjTree.MoveWindow(0,0,rc2.Width(),rc.Height()); 
        mScene.MoveWindow(rc2.Width(),0,rc.Width()-rc2.Width(),rc.Height());
    }
  

}