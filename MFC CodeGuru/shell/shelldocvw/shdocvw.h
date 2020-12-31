// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IWebBrowser wrapper class

class IWebBrowser : public COleDispatchDriver
{
public:
	IWebBrowser() {}		// Calls COleDispatchDriver default constructor
	IWebBrowser(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWebBrowser(const IWebBrowser& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void GoBack();
	void GoForward();
	void GoHome();
	void GoSearch();
	void Navigate(LPCTSTR URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers);
	void Refresh();
	void Refresh2(VARIANT* Level);
	void Stop();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetContainer();
	LPDISPATCH GetDocument();
	BOOL GetTopLevelContainer();
	CString GetType();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	CString GetLocationName();
	CString GetLocationURL();
	BOOL GetBusy();
};
/////////////////////////////////////////////////////////////////////////////
// DWebBrowserEvents wrapper class

class DWebBrowserEvents : public COleDispatchDriver
{
public:
	DWebBrowserEvents() {}		// Calls COleDispatchDriver default constructor
	DWebBrowserEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DWebBrowserEvents(const DWebBrowserEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void BeforeNavigate(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT* PostData, LPCTSTR Headers, BOOL* Cancel);
	void NavigateComplete(LPCTSTR URL);
	void StatusTextChange(LPCTSTR Text);
	void ProgressChange(long Progress, long ProgressMax);
	void DownloadComplete();
	void CommandStateChange(long Command, BOOL Enable);
	void DownloadBegin();
	void NewWindow(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT* PostData, LPCTSTR Headers, BOOL* Processed);
	void TitleChange(LPCTSTR Text);
	void FrameBeforeNavigate(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT* PostData, LPCTSTR Headers, BOOL* Cancel);
	void FrameNavigateComplete(LPCTSTR URL);
	void FrameNewWindow(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT* PostData, LPCTSTR Headers, BOOL* Processed);
	void Quit(BOOL* Cancel);
	void WindowMove();
	void WindowResize();
	void WindowActivate();
	void PropertyChange(LPCTSTR Property_);
};
/////////////////////////////////////////////////////////////////////////////
// IWebBrowserApp wrapper class

class IWebBrowserApp : public COleDispatchDriver
{
public:
	IWebBrowserApp() {}		// Calls COleDispatchDriver default constructor
	IWebBrowserApp(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWebBrowserApp(const IWebBrowserApp& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void GoBack();
	void GoForward();
	void GoHome();
	void GoSearch();
	void Navigate(LPCTSTR URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers);
	void Refresh();
	void Refresh2(VARIANT* Level);
	void Stop();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetContainer();
	LPDISPATCH GetDocument();
	BOOL GetTopLevelContainer();
	CString GetType();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	CString GetLocationName();
	CString GetLocationURL();
	BOOL GetBusy();
	void Quit();
	void ClientToWindow(long* pcx, long* pcy);
	void PutProperty(LPCTSTR Property_, const VARIANT& vtValue);
	VARIANT GetProperty_(LPCTSTR Property_);
	CString GetName();
	long GetHwnd();
	CString GetFullName();
	CString GetPath();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetStatusBar();
	void SetStatusBar(BOOL bNewValue);
	CString GetStatusText();
	void SetStatusText(LPCTSTR lpszNewValue);
	long GetToolBar();
	void SetToolBar(long nNewValue);
	BOOL GetMenuBar();
	void SetMenuBar(BOOL bNewValue);
	BOOL GetFullScreen();
	void SetFullScreen(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IWebBrowser2 wrapper class

class IWebBrowser2 : public COleDispatchDriver
{
public:
	IWebBrowser2() {}		// Calls COleDispatchDriver default constructor
	IWebBrowser2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWebBrowser2(const IWebBrowser2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void GoBack();
	void GoForward();
	void GoHome();
	void GoSearch();
	void Navigate(LPCTSTR URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers);
	void Refresh();
	void Refresh2(VARIANT* Level);
	void Stop();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetContainer();
	LPDISPATCH GetDocument();
	BOOL GetTopLevelContainer();
	CString GetType();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	CString GetLocationName();
	CString GetLocationURL();
	BOOL GetBusy();
	void Quit();
	void ClientToWindow(long* pcx, long* pcy);
	void PutProperty(LPCTSTR Property_, const VARIANT& vtValue);
	VARIANT GetProperty_(LPCTSTR Property_);
	CString GetName();
	long GetHwnd();
	CString GetFullName();
	CString GetPath();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetStatusBar();
	void SetStatusBar(BOOL bNewValue);
	CString GetStatusText();
	void SetStatusText(LPCTSTR lpszNewValue);
	long GetToolBar();
	void SetToolBar(long nNewValue);
	BOOL GetMenuBar();
	void SetMenuBar(BOOL bNewValue);
	BOOL GetFullScreen();
	void SetFullScreen(BOOL bNewValue);
	void Navigate2(VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers);
	long QueryStatusWB(long cmdID);
	void ExecWB(long cmdID, long cmdexecopt, VARIANT* pvaIn, VARIANT* pvaOut);
	void ShowBrowserBar(VARIANT* pvaClsid, VARIANT* pvarShow, VARIANT* pvarSize);
	long GetReadyState();
	BOOL GetOffline();
	void SetOffline(BOOL bNewValue);
	BOOL GetSilent();
	void SetSilent(BOOL bNewValue);
	BOOL GetRegisterAsBrowser();
	void SetRegisterAsBrowser(BOOL bNewValue);
	BOOL GetRegisterAsDropTarget();
	void SetRegisterAsDropTarget(BOOL bNewValue);
	BOOL GetTheaterMode();
	void SetTheaterMode(BOOL bNewValue);
	BOOL GetAddressBar();
	void SetAddressBar(BOOL bNewValue);
	BOOL GetResizable();
	void SetResizable(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// DWebBrowserEvents2 wrapper class

class DWebBrowserEvents2 : public COleDispatchDriver
{
public:
	DWebBrowserEvents2() {}		// Calls COleDispatchDriver default constructor
	DWebBrowserEvents2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DWebBrowserEvents2(const DWebBrowserEvents2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void StatusTextChange(LPCTSTR Text);
	void ProgressChange(long Progress, long ProgressMax);
	void CommandStateChange(long Command, BOOL Enable);
	void DownloadBegin();
	void DownloadComplete();
	void TitleChange(LPCTSTR Text);
	void PropertyChange(LPCTSTR szProperty);
	void BeforeNavigate2(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
	void NewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	void NavigateComplete2(LPDISPATCH pDisp, VARIANT* URL);
	void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
	void OnQuit();
	void OnVisible(BOOL Visible);
	void OnToolBar(BOOL ToolBar);
	void OnMenuBar(BOOL MenuBar);
	void OnStatusBar(BOOL StatusBar);
	void OnFullScreen(BOOL FullScreen);
	void OnTheaterMode(BOOL TheaterMode);
};
/////////////////////////////////////////////////////////////////////////////
// IFolderViewOC wrapper class

class IFolderViewOC : public COleDispatchDriver
{
public:
	IFolderViewOC() {}		// Calls COleDispatchDriver default constructor
	IFolderViewOC(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IFolderViewOC(const IFolderViewOC& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetFolderView(LPDISPATCH pDisp);
};
/////////////////////////////////////////////////////////////////////////////
// DShellFolderViewEvents wrapper class

class DShellFolderViewEvents : public COleDispatchDriver
{
public:
	DShellFolderViewEvents() {}		// Calls COleDispatchDriver default constructor
	DShellFolderViewEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DShellFolderViewEvents(const DShellFolderViewEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SelectionChanged();
};
/////////////////////////////////////////////////////////////////////////////
// DShellWindowsEvents wrapper class

class DShellWindowsEvents : public COleDispatchDriver
{
public:
	DShellWindowsEvents() {}		// Calls COleDispatchDriver default constructor
	DShellWindowsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DShellWindowsEvents(const DShellWindowsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void WindowRegistered(long lCookie);
	void WindowRevoked(long lCookie);
};
/////////////////////////////////////////////////////////////////////////////
// IShellWindows wrapper class

class IShellWindows : public COleDispatchDriver
{
public:
	IShellWindows() {}		// Calls COleDispatchDriver default constructor
	IShellWindows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IShellWindows(const IShellWindows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH Item(const VARIANT& index);
	LPUNKNOWN _NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// IShellLinkDual wrapper class

class IShellLinkDual : public COleDispatchDriver
{
public:
	IShellLinkDual() {}		// Calls COleDispatchDriver default constructor
	IShellLinkDual(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IShellLinkDual(const IShellLinkDual& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetPath();
	void SetPath(LPCTSTR lpszNewValue);
	CString GetDescription();
	void SetDescription(LPCTSTR lpszNewValue);
	CString GetWorkingDirectory();
	void SetWorkingDirectory(LPCTSTR lpszNewValue);
	CString GetArguments();
	void SetArguments(LPCTSTR lpszNewValue);
	long GetHotkey();
	void SetHotkey(long nNewValue);
	long GetShowCommand();
	void SetShowCommand(long nNewValue);
	void Resolve(long fFlags);
	long GetIconLocation(BSTR* pbs);
	void SetIconLocation(LPCTSTR bs, long iIcon);
	void Save(const VARIANT& vWhere);
};
/////////////////////////////////////////////////////////////////////////////
// FolderItemVerb wrapper class

class FolderItemVerb : public COleDispatchDriver
{
public:
	FolderItemVerb() {}		// Calls COleDispatchDriver default constructor
	FolderItemVerb(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FolderItemVerb(const FolderItemVerb& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void DoIt();
};
/////////////////////////////////////////////////////////////////////////////
// FolderItemVerbs wrapper class

class FolderItemVerbs : public COleDispatchDriver
{
public:
	FolderItemVerbs() {}		// Calls COleDispatchDriver default constructor
	FolderItemVerbs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FolderItemVerbs(const FolderItemVerbs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(const VARIANT& index);
	LPUNKNOWN _NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// Folder wrapper class

class Folder : public COleDispatchDriver
{
public:
	Folder() {}		// Calls COleDispatchDriver default constructor
	Folder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Folder(const Folder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetTitle();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetParentFolder();
	LPDISPATCH Items();
	LPDISPATCH ParseName(LPCTSTR bName);
	void NewFolder(LPCTSTR bName, const VARIANT& vOptions);
	void MoveHere(const VARIANT& vItem, const VARIANT& vOptions);
	void CopyHere(const VARIANT& vItem, const VARIANT& vOptions);
	CString GetDetailsOf(const VARIANT& vItem, long iColumn);
};
/////////////////////////////////////////////////////////////////////////////
// FolderItems wrapper class

class FolderItems : public COleDispatchDriver
{
public:
	FolderItems() {}		// Calls COleDispatchDriver default constructor
	FolderItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FolderItems(const FolderItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Item(const VARIANT& index);
	LPUNKNOWN _NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// FolderItem wrapper class

class FolderItem : public COleDispatchDriver
{
public:
	FolderItem() {}		// Calls COleDispatchDriver default constructor
	FolderItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FolderItem(const FolderItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetPath();
	LPDISPATCH GetGetLink();
	LPDISPATCH GetGetFolder();
	BOOL GetIsLink();
	BOOL GetIsFolder();
	BOOL GetIsFileSystem();
	BOOL GetIsBrowsable();
	DATE GetModifyDate();
	void SetModifyDate(DATE newValue);
	long GetSize();
	CString GetType();
	LPDISPATCH Verbs();
	void InvokeVerb(const VARIANT& vVerb);
};
/////////////////////////////////////////////////////////////////////////////
// IShellFolderViewDual wrapper class

class IShellFolderViewDual : public COleDispatchDriver
{
public:
	IShellFolderViewDual() {}		// Calls COleDispatchDriver default constructor
	IShellFolderViewDual(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IShellFolderViewDual(const IShellFolderViewDual& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH GetFolder();
	LPDISPATCH SelectedItems();
	LPDISPATCH GetFocusedItem();
	void SelectItem(VARIANT* pvfi, long dwFlags);
	CString PopupItemMenu(LPDISPATCH pfi, const VARIANT& vx, const VARIANT& vy);
	LPDISPATCH GetScript();
	long GetViewOptions();
};
/////////////////////////////////////////////////////////////////////////////
// IShellDispatch wrapper class

class IShellDispatch : public COleDispatchDriver
{
public:
	IShellDispatch() {}		// Calls COleDispatchDriver default constructor
	IShellDispatch(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IShellDispatch(const IShellDispatch& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH NameSpace(const VARIANT& vDir);
	LPDISPATCH BrowseForFolder(long HWND, LPCTSTR Title, long Options, const VARIANT& RootFolder);
	LPDISPATCH Windows();
	void Open(const VARIANT& vDir);
	void Explore(const VARIANT& vDir);
	void MinimizeAll();
	void UndoMinimizeALL();
	void FileRun();
	void CascadeWindows();
	void TileVertically();
	void TileHorizontally();
	void ShutdownWindows();
	void Suspend();
	void EjectPC();
	void SetTime();
	void TrayProperties();
	void Help();
	void FindFiles();
	void FindComputer();
	void RefreshMenu();
	void ControlPanelItem(LPCTSTR szDir);
};
/////////////////////////////////////////////////////////////////////////////
// IShellUIHelper wrapper class

class IShellUIHelper : public COleDispatchDriver
{
public:
	IShellUIHelper() {}		// Calls COleDispatchDriver default constructor
	IShellUIHelper(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IShellUIHelper(const IShellUIHelper& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void AddFavorite(LPCTSTR URL, VARIANT* Title);
	void AddChannel(LPCTSTR URL);
	void AddDesktopComponent(LPCTSTR URL, LPCTSTR Type, VARIANT* Left, VARIANT* Top, VARIANT* Width, VARIANT* Height);
	BOOL IsSubscribed(LPCTSTR URL);
};
