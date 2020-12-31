#include "common.h"
#include "resource.h"

HHOOK g_hHook								= NULL;				// 窗口钩子句柄
//HHOOK g_hGetMessageHook						= NULL;				// WH_GETMESSAGE HOOK 句柄

ULONG_PTR m_gdiplusToken					= NULL;				// GDI+ 全局资源句柄

typedef struct _MetroUIData {
	WNDPROC oldWndProc;					// 原来的窗口过程
	LONG lStyle;						// 原来的窗口样式
	LONG lStyleEx;						// 原来的扩展窗口样式
	BOOL bTracking;						// 标题栏鼠标消息事件
	int nMouseDownNCHTTEST;				// 鼠标按下时所在的区域
	int nNcHitTestCode;					// 鼠标移动时所在的区域
	HBRUSH hClientBrush;				// 客户区背景画刷
	map< HWND,HBRUSH > mapControlBrush;	// 控件的背景HBRUSH
}MetroUIData,*PMetroUIData;

enum NCHITTEST { NCHTCLOSEBUTTON = 190,NCHTMAXBUTTON,NCHTMINBUTTON,NCHTMENUBUTTON };// 鼠标在标题栏的位置

Gdiplus::Image * m_pPngMenuNormal			= NULL;				// 菜单按钮
Gdiplus::Image * m_pPngMenuOver				= NULL;
Gdiplus::Image * m_pPngMenuDown				= NULL;

Gdiplus::Image * m_pPngMinNormal			= NULL;				// 最小化按钮
Gdiplus::Image * m_pPngMinOver				= NULL;
Gdiplus::Image * m_pPngMinDown				= NULL;

Gdiplus::Image * m_pPngMaxNormal			= NULL;				// 最大化按钮
Gdiplus::Image * m_pPngMaxOver				= NULL;
Gdiplus::Image * m_pPngMaxDown				= NULL;

Gdiplus::Image * m_pPngRestoreNormal		= NULL;				// 恢复按钮
Gdiplus::Image * m_pPngRestoreOver			= NULL;
Gdiplus::Image * m_pPngRestoreDown			= NULL;

Gdiplus::Image * m_pPngCloseNormal			= NULL;				// 关闭按钮
Gdiplus::Image * m_pPngCloseOver			= NULL;
Gdiplus::Image * m_pPngCloseDown			= NULL;

LRESULT CALLBACK WindowProc( HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam );				// 新的窗口过程
LRESULT CALLBACK GetMsgProc( int code,WPARAM wParam,LPARAM lParam );

void SetWindowRegion( HWND hWnd );															// 设置窗口区域

void OnNcPaint( HWND hWnd,WPARAM wParam );													// 标题栏绘制函数
void OnPaint( HWND hWnd );																	// 客户区绘制函数

HBRUSH GetBrush( PMetroUIData pMetroUIData,HWND hWnd,WPARAM wParam,LPARAM lParam );								// 窗口尺寸改变时，重新设置客户区和各个子控件的背景画刷

void SetWindowRegion( HWND hWnd )
{
	SetWindowRgn( hWnd,NULL,FALSE );

	RECT rc;
	GetWindowRect( hWnd,&rc );
	HRGN hRgn = CreateRoundRectRgn( 0,0,rc.right - rc.left,rc.bottom - rc.top,4,4 );
	// 【重要】SetWindowRgn最后一个参数一定要设置为TRUE否则客户区会出现重影，如果用Invalidate刷新客户区会闪烁的特别厉害
	SetWindowRgn( hWnd,hRgn,TRUE );
	// 使用完HRGN后一定要释放该GDI对象
	::DeleteObject( hRgn );
}

LRESULT CALLBACK WindowProc( HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam )
{
	LRESULT lResult = 0;
	PMetroUIData pMetroUIData = (PMetroUIData)GetProp( hWnd,_T("MetroUI_Prop") );
	switch( uMsg )
	{
	case WM_INITDIALOG:
		lResult = ::CallWindowProc( pMetroUIData->oldWndProc,hWnd,uMsg,wParam,lParam );
		// 因为父窗口客户区背景是变化的，不是固定的， 所以当窗口尺寸改变时，各个子控件的背景也要随之改变，所以不能加下面的这句话。
		// 通过比对QQ发现QQ的背景不是变化的，QQ的尺寸在改变时只有变化后的那一部分尺寸才重新设置了背景，但是以前的那一部分尺寸的区域还是以前的背景。
		// 所以这个问题不好解决，客户区背景会随着尺寸变化的窗口，闪烁比较厉害，不好解决。
		//SetWindowLong( hWnd,GWL_STYLE,GetWindowLong( hWnd,GWL_STYLE ) | WS_CLIPCHILDREN );
		SetWindowRegion( hWnd );
		return lResult;
	case WM_NCDESTROY:
		{
			// 窗口销毁时设置回旧的窗口过程
			SetWindowLong( hWnd,GWL_WNDPROC,(LONG)(pMetroUIData->oldWndProc) );
			// 调用一次旧的窗口过程
			lResult = ::CallWindowProc( pMetroUIData->oldWndProc,hWnd,uMsg,wParam,lParam );
			// 释放客户区的背景HDC
			if( pMetroUIData->hClientBrush != NULL )
			{
				DeleteObject( pMetroUIData->hClientBrush );
				pMetroUIData->hClientBrush = NULL;
			}
			// 释放为所有控件创建的HBRUSH
			map< HWND,HBRUSH >::iterator p = pMetroUIData->mapControlBrush.begin();
			while( p != pMetroUIData->mapControlBrush.end() )
			{
				DeleteObject( (HBRUSH)(p->second) );
				p++;
			}
			pMetroUIData->mapControlBrush.clear();
			// 释放new出来的pMetroUIData
			delete pMetroUIData;
			// 移除设置的窗口标记
			RemoveProp( hWnd,_T("MetroUI_Prop") );
			return lResult;
		}
		break;
	case WM_NCCALCSIZE:
		break;
		// 【重要】
		// 在CDialog类中将调用基类的代码CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);去掉，但不改变lpncsp->rgrc[0]里面的值
		// 效果是对话框的标题栏和边框没有了，
		// 但如果改变lpncsp->rgrc[0]里面的值，将lpncsp->rgrc[0].top加上高度36，这样实现的效果是标题栏和边框又出来了
		// 这样做（也就是不调用基类的CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);）的好处是标题栏在绝大数情况下均不会自己绘制，
		// 这样系统的最小化最大化关闭按钮就不会出现了 但这样有一个问题是：像文件选择对话框的高度变小了，下面的取消按钮等显示不出来。
		// 最好的做法还是不处理这个消息，标题栏和重绘在状态改变里去重绘。  
		//OutputDebugString( _T("WM_NCCALCSIZE\r\n") ); 
		if( wParam == TRUE )
		{
			LONG lStyle = GetWindowLong( hWnd,GWL_STYLE );
			bool bResize = ( ( lStyle & WS_THICKFRAME ) == WS_THICKFRAME );
			NCCALCSIZE_PARAMS * lpncsp = (NCCALCSIZE_PARAMS*)lParam;
			lpncsp->rgrc[0].left += bResize ? GetSystemMetrics( SM_CXSIZEFRAME ) : GetSystemMetrics( SM_CXFIXEDFRAME );
			lpncsp->rgrc[0].top += GetSystemMetrics( SM_CYCAPTION ) + ( bResize ? GetSystemMetrics( SM_CYSIZEFRAME ) : GetSystemMetrics( SM_CYFIXEDFRAME ) );
			lpncsp->rgrc[0].bottom -= bResize ? GetSystemMetrics( SM_CYSIZEFRAME ) : GetSystemMetrics( SM_CYFIXEDFRAME );
			lpncsp->rgrc[0].right -= bResize ? GetSystemMetrics( SM_CXSIZEFRAME ) : GetSystemMetrics( SM_CXFIXEDFRAME );
		}
		// 直接返回，不让基类有处理机会。而且为了窗口一创建就HOOK窗口过程，来屏蔽掉基类的处理WM_NCCALCSIZE消息的过程，必须安装WH_CBT钩子
		// 如果安装WH_CALLWNDPROC是不行的，系统还是会进入到CDialog类的OnNcCalcSize处理过程中，具体原因没搞清楚。
		return 0L;
	case WM_NCACTIVATE:
		// 调用 lResult = ::CallWindowProc( pMetroUIData->oldWndProc,hWnd,uMsg,wParam,lParam ); 后发现lResult值总是为1，那么直接return 1;但不调用原来的窗口过程，就不会在刷新时出现系统标题栏
		// 注意这里是不能返回0的 否则会出现弹出的子对话框不是MODAL状态的现象。
		//lResult = ::CallWindowProc( pMetroUIData->oldWndProc,hWnd,uMsg,wParam,lParam );
		{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("WM_NCACTIVATE %d %d\r\n"),lResult,i++);OutputDebugString( buf );}
		//OnNcPaint( hWnd,1 );
		return 1L;
	case WM_ACTIVATEAPP:
		break;
	case WM_EXITSIZEMOVE:
		// 重载此消息目的是为了解决 ： 主窗口调用 SetWindowRgn 后点击子窗口滚动条时发现没响应（这是个大概率事件，出现概率很高）。
		::RedrawWindow( hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE|RDW_FRAME|RDW_ALLCHILDREN);
		break;
	case WM_SIZING:
		break;
	case WM_SIZE:
		//{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("WM_SIZE %d %d\r\n"),wParam,i++);OutputDebugString( buf );}
		lResult = ::CallWindowProc( pMetroUIData->oldWndProc,hWnd,uMsg,wParam,lParam );
		if( wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED )
		{
			// 重新设置客户区背景画刷和各个子控件的背景画刷  
			RECT rc,rcControl;
			GetClientRect( hWnd,&rc );
			LONG lStyle = GetWindowLong( hWnd,GWL_STYLE );
			bool bResize = ( ( lStyle & WS_THICKFRAME ) == WS_THICKFRAME );
			// 将rc.top将上便移标题栏高度再减2的像素，目的在于绘制客户区背景时保持和标题栏的背景渐变一致。
			rc.top -= GetSystemMetrics( SM_CYCAPTION ) + ( bResize ? GetSystemMetrics( SM_CYSIZEFRAME ) : GetSystemMetrics( SM_CYFIXEDFRAME ) ) - 2;
			// 重新设置窗口客户区背景HDC，用于设置子控件的背景画刷
			HDC hDC = ::GetDC( hWnd ); 
			if( hDC )
			{
				// 如果上次已经创建过HDC，先销毁它。
				if( pMetroUIData->hClientBrush != NULL )
				{
					DeleteObject( pMetroUIData->hClientBrush );
					pMetroUIData->hClientBrush = NULL;
				}
				HDC hMemDC = ::CreateCompatibleDC( hDC );
				HBITMAP hBitmap = ::CreateCompatibleBitmap( hDC,rc.right - rc.left,rc.bottom - rc.top );
				HBITMAP hOldBitmap = (HBITMAP)SelectObject( hMemDC,hBitmap );
				GradientFillRect( hMemDC,rc,0xFDE7C5,0xffffff,true );
				pMetroUIData->hClientBrush = ::CreatePatternBrush( hBitmap );
				// 客户区完整的背景HDC填充完成，开始为各个子控件重新构造背景画刷 
				map< HWND,HBRUSH >::iterator p = pMetroUIData->mapControlBrush.begin();
				while( p != pMetroUIData->mapControlBrush.end() )
				{
					// 创建子控件的背景画刷之前先将该控件以前的背景画刷释放 
					DeleteObject( (HBRUSH)(p->second) );

					GetWindowRect( (HWND)(p->first),&rcControl );
					ScreenToClient( hWnd,&rcControl );

					HDC hMemDC2 = ::CreateCompatibleDC( hMemDC );
					HBITMAP hBitmap2 = ::CreateCompatibleBitmap( hMemDC,rcControl.right - rcControl.left,rcControl.bottom - rcControl.top );

					HBITMAP hOldBitmap2 = (HBITMAP)SelectObject( hMemDC2,hBitmap2 );
					BitBlt( hMemDC2,0,0,rcControl.right - rcControl.left,rcControl.bottom - rcControl.top,hMemDC, rcControl.left, rcControl.top, SRCCOPY);

					HBRUSH hBrush = ::CreatePatternBrush( hBitmap2 );
					pMetroUIData->mapControlBrush[(HWND)(p->first)] = hBrush;

					SelectObject( hMemDC2,hOldBitmap2 );
					DeleteObject( hBitmap2 );
					DeleteDC( hMemDC2 );

					p++;
				}
				//将以前的设备选回去，否则可能会导致GDI资源释放出现问题。
				SelectObject( hMemDC,hOldBitmap );
				DeleteObject( hBitmap );
				DeleteDC( hMemDC );
				ReleaseDC( hWnd,hDC );
			}
			// 窗口尺寸改变了，重新设置窗口REGION
			SetWindowRegion( hWnd );
			InvalidateRect( hWnd,NULL,TRUE );
		}
		return lResult;
	case WM_ERASEBKGND:
		// 其实普通对话框里不需要做下面的背景重画操作，return TRUE;即可。但在文件选择对话框里，最上面有一个选择查看文件类型的ToolBarWindow32，背景是系统颜色的。
		// 只好将客户区的背景重画一下就不会出现那个系统颜色的背景了。
		if( pMetroUIData->hClientBrush )
		{
			// 用事先构造好的客户区背景HDC填充客户区的背景重绘消息
			RECT rc;
			GetClientRect( hWnd,&rc );
			HDC hMemDC = ::CreateCompatibleDC( (HDC)wParam );
			HBITMAP hBitmap = ::CreateCompatibleBitmap( (HDC)wParam,rc.right - rc.left,rc.bottom - rc.top );
			HBITMAP hOldBitmap = (HBITMAP)SelectObject( hMemDC,hBitmap );
			::FillRect( hMemDC,&rc,pMetroUIData->hClientBrush );
			::BitBlt( (HDC)wParam,0,0,rc.right - rc.left,rc.bottom - rc.top,hMemDC,0,0,SRCCOPY );
			SelectObject( hMemDC,hOldBitmap );
			DeleteObject( hBitmap );
			DeleteDC( hMemDC );
			return TRUE;
		}
		break;
	case WM_NCPAINT:
		OnNcPaint( hWnd,wParam );
		return 0L;
	case WM_PAINT:
		OnPaint( hWnd );
		return 0L;
	// CTabCtrl 有个恶心的地方，背景画刷无法改变，重载OnCtlColor不行，重载OnEraseBkgnd不行，只有一个办法，重载OnPaint 完全自己画才行。
	// 还有一个办法就是用SetWindowRgn设置TABCTRL的有效区域，可缓解，但是如果不重绘的话，系统的TABCTRL的边边线线等还是很难看，这里就不再考虑了。
	//case WM_CTLCOLORDLG://此消息始终收不到，不明白原因。 
	//case WM_CTLCOLORMSGBOX:
	//case WM_CTLCOLOREDIT:
	//case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORBTN:
		switch( GetWindowLong( (HWND)lParam,GWL_STYLE ) & BS_TYPEMASK )
		{
		case BS_CHECKBOX:			// 复选框
		case BS_AUTOCHECKBOX:		// 自动复选框
		case BS_3STATE:				// 三状态复选框
		case BS_AUTO3STATE:			// 自动三状态复选框
		case BS_RADIOBUTTON:		// 单选框
		case BS_AUTORADIOBUTTON:	// 自动单选框
		case BS_GROUPBOX:			// 组合框
			SetBkMode( (HDC)wParam,TRANSPARENT );
			return (LRESULT)GetBrush( pMetroUIData,hWnd,wParam,lParam );
		}
		break;
	//case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
		{
			// 不让禁用或者只读状态的编辑框也重画背景
			TCHAR tzClassName[8] = { 0 };
			GetClassName( (HWND)lParam,tzClassName,sizeof(tzClassName) );
			if( _tcsicmp( tzClassName,_T("Edit") ) == 0 )
				break;
		}
		SetBkMode( (HDC)wParam,TRANSPARENT );
		return (LRESULT)GetBrush( pMetroUIData,hWnd,wParam,lParam );
	case WM_NCHITTEST:
		lResult = ::CallWindowProc( pMetroUIData->oldWndProc,hWnd,uMsg,wParam,lParam );
		{
			LONG lStyle = GetWindowLong( hWnd,GWL_STYLE );
			//{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("WM_NCHITTEST %d %d\r\n"),lResult,i++);OutputDebugString( buf );}
			// 画最小化 最大化 关闭 按钮
			if( lStyle & WS_SYSMENU )
			{
				POINT pt = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
				RECT rcWindow,rcButton;
				GetWindowRect( hWnd,&rcWindow );
				// 求出标题栏矩形的大小
				rcWindow.top += 2;
				rcWindow.bottom = rcWindow.top + GetSystemMetrics( SM_CYCAPTION ) + ( ( ( lStyle & WS_THICKFRAME ) == WS_THICKFRAME ) ? GetSystemMetrics( SM_CYSIZEFRAME ) : GetSystemMetrics( SM_CYFIXEDFRAME ) );
				// 关闭按钮的矩形区
				rcButton = rcWindow;
				rcButton.left = rcButton.right - m_pPngCloseNormal->GetWidth();
				rcButton.right -= 2;
				if( PtInRect( &rcButton,pt ) )
					return NCHTCLOSEBUTTON;
				// 最大化按钮区域
				rcButton.right = rcButton.left;
				if( lStyle & WS_MAXIMIZEBOX )
				{
					rcButton.left = rcButton.right - m_pPngMaxNormal->GetWidth();
					if( PtInRect( &rcButton,pt ) )
						return NCHTMAXBUTTON;
				}
				// 最小化按钮区域
				rcButton.right = rcButton.left;
				if( lStyle & WS_MINIMIZEBOX )
				{
					rcButton.left = rcButton.right - m_pPngMinNormal->GetWidth();
					if( PtInRect( &rcButton,pt ) )
						return NCHTMINBUTTON;
				}
				//// 菜单按钮区域
				//rcButton.right = rcButton.left;
				//rcButton.left = rcButton.right - m_pPngMenuNormal->GetWidth();
				//if( PtInRect( &rcButton,pt ) )
				//	return NCHTMENUBUTTON;
			}
			// 屏蔽最大最小关闭消息.否则鼠标在最小化最大化关闭按钮上按下时那些按钮还会显示出来
			if( lResult == HTZOOM || lResult == HTMINBUTTON || lResult == HTCLOSE || lResult == HTHELP )
				return HTNOWHERE;//视为标题栏动作。
		}
		//{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("WM_NCHITTEST %d %d\r\n"),lResult,i++);OutputDebugString( buf );}
		return lResult;
	case 0x00AE://:WM_NCUAHDRAWCAPTION
	case 0x00AF://:WM_NCUAHDRAWFRAME
		lResult = GetWindowLong( hWnd,GWL_STYLE );
		if( lResult & WS_VISIBLE )
			SetWindowLong( hWnd,GWL_STYLE,lResult & ( ~WS_VISIBLE ) );
		::DefWindowProc( hWnd,uMsg,wParam,lParam );
		if( lResult & WS_VISIBLE )
			SetWindowLong( hWnd,GWL_STYLE,lResult );
		return TRUE;
	case WM_NCMOUSEMOVE:
		// WM_NCMOUSEMOVE 消息是由 WM_NCHITTEST 消息主动发出的，当在WM_NCHITTEST消息里return HTERROR或者其它值时，将不会产生WM_NCMOUSEMOVE消息
		if( !pMetroUIData->bTracking )
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hWnd;
			tme.dwFlags = TME_LEAVE | TME_NONCLIENT;
			pMetroUIData->bTracking = _TrackMouseEvent(&tme);
		}
		if( pMetroUIData->nNcHitTestCode != wParam )
		{
			// 鼠标原来在系统按钮上但现在不在了
			if( pMetroUIData->nNcHitTestCode == NCHTMAXBUTTON || pMetroUIData->nNcHitTestCode == NCHTMENUBUTTON || pMetroUIData->nNcHitTestCode == NCHTCLOSEBUTTON || pMetroUIData->nNcHitTestCode == NCHTMINBUTTON ||
				// 鼠标原来不在系统按钮上但现在在了
				wParam == NCHTMAXBUTTON || wParam == NCHTMENUBUTTON || wParam == NCHTCLOSEBUTTON || wParam == NCHTMINBUTTON )
			{
				// 先将HTTEST值赋给变量，因为在重绘函数中会判断变量的值，重绘前不给变量赋相应值的话，重绘没有效果。
				pMetroUIData->nNcHitTestCode = wParam;
				// 鼠标左键没有按下才触发重绘函数，如果左键处于按下状态，则不触发重绘函数
				if( (GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0 )
				{
		{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("WM_NCMOUSEMOVE %d %d %d\r\n"),wParam,pMetroUIData->nNcHitTestCode,i++);OutputDebugString( buf );}
					OnNcPaint( hWnd,1 );
				}
			}
			// 防止没有进入上面的条件判断，再赋值一次。
			pMetroUIData->nNcHitTestCode = wParam;
		}
		break;
	case WM_NCMOUSELEAVE:
		{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("WM_NCMOUSELEAVE WM_NCMOUSELEAVE %d %d\r\n"),wParam,i++);OutputDebugString( buf );}
		pMetroUIData->bTracking = FALSE;
		// 左键曾经在系统按钮上按下了
		if( pMetroUIData->nMouseDownNCHTTEST == NCHTMAXBUTTON || pMetroUIData->nMouseDownNCHTTEST == NCHTMENUBUTTON || pMetroUIData->nMouseDownNCHTTEST == NCHTCLOSEBUTTON || pMetroUIData->nMouseDownNCHTTEST == NCHTMINBUTTON )
		{
			// 左键当前处于松开状态：根据测试发现实际上不会进入这种情况
			if( (GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0 )
			{
				pMetroUIData->nNcHitTestCode = HTERROR;
				pMetroUIData->nMouseDownNCHTTEST = HTERROR;
				OnNcPaint( hWnd,1 );
			}
		}
		// 左键未在系统按钮上按下过
		else
		{
			// 鼠标上次所在位置刚好在最大化最小化关闭按钮上，现在鼠标离开了，要重绘这些按钮。
			if( pMetroUIData->nNcHitTestCode == NCHTCLOSEBUTTON || pMetroUIData->nNcHitTestCode == NCHTMAXBUTTON || pMetroUIData->nNcHitTestCode == NCHTMINBUTTON || pMetroUIData->nNcHitTestCode == NCHTMENUBUTTON )
			{
				pMetroUIData->nNcHitTestCode = HTERROR;
				OnNcPaint( hWnd,1 );
			}
			pMetroUIData->nNcHitTestCode = HTERROR;
		}
		break;
	case WM_NCLBUTTONDOWN:
		// 标题栏左键松开的消息在很多情况下是收不到的：标题栏单击；标题栏按下左键标题栏外释放左键；而且在WM_NCLBUTTONDOWN还不能直接SetCapture然后在WM_NCLBUTTONUP里ReleaseCapture，否则标题栏再怎么点击也没有反应了。
		// 为了解决按下左键后无法收到左键弹起的消息，在网上找了很多办法，没有一个完全无问题的，总有这样那样的BUG。
		// 最终解决办法是如果在系统按钮上按下了以后，先SetCapture再搞一个while(GetMessage())的循环，这样鼠标无论移到哪儿鼠标消息都会被本窗口收到。
		// 左键弹起消息也能收到，收到左键弹起消息之后再发送一个WM_NCLBUTTONUP的消息，即可很好的处理系统按钮的状态问题。
		// 以下仅判断当左键在系统按钮上按下时才设置nMouseDownNCHTTEST变量的值，并启动while(GetMessage())的循环，在标题栏的其它地方点击不进入下面的代码。
		if( wParam == NCHTCLOSEBUTTON || wParam == NCHTMAXBUTTON || wParam == NCHTMINBUTTON || wParam == NCHTMENUBUTTON )
		{
			pMetroUIData->nMouseDownNCHTTEST = wParam;
			// 鼠标按下之后进入while循环之前先重绘一下标题栏
			OnNcPaint( hWnd,1 );
			// 捕获鼠标，无论鼠标移动任何区域均能接收到鼠标消息
			SetCapture( hWnd );
			// 开始消息循环，直到鼠标左键松开，或其它事件触发。
			MSG msg;
			BOOL bRet = FALSE;
			while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0 )
			{
				//{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("GetMessage  0x%04x %d\r\n"),msg.message,i++);OutputDebugString( buf );}
				if( bRet == -1 )
				{
					break;
				}
				else
				{
					// 如果检测到鼠标左键松开的消息，处理消息并直接跳出，然后消息循环会进入到WM_NCLBUTTONUP的函数处理过程中，会重绘窗口
					if( msg.message == WM_NCLBUTTONUP || msg.message == WM_LBUTTONUP )
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
						break;
					}
					// 用户不走寻常路，左键还没放开就去按键盘：
					// 如果检测到按键按下的消息，跳出循环，则设置标志位，重绘窗口，跳出循环。因为此时已经无法进入WM_LBUTTONUP消息了
					if( msg.message == WM_KEYDOWN || msg.message == WM_KEYUP || msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP ||
						// 如果没有收到上面的消息但是左键已经松开了，跳出循环。
						(GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0 )
					{
						POINT pt;
						GetCursorPos( &pt );
						pMetroUIData->nNcHitTestCode = SendMessage( hWnd,WM_NCHITTEST,0,MAKELPARAM(pt.x,pt.y) );
						pMetroUIData->nMouseDownNCHTTEST = HTERROR;
						OnNcPaint( hWnd,1 );
						TranslateMessage(&msg);
						DispatchMessage(&msg);
						break;
					}
					// 不是上面的情况则是其它的消息，分发消息，进入消息的处理过程。
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			// 消息循环结束，释放鼠标捕获
			ReleaseCapture();
		}
		break;
	case WM_NCLBUTTONUP:
		// 标题栏上的 WM_NCLBUTTONUP 和 WM_NCMOUSELEAVE 消息非常恶心，在很多情况下会收不到，所以百度之后弄了一个while(GetMessage))的循环。s
		{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("WM_NCLBUTTONUP  %d %d\r\n"),wParam,i++);OutputDebugString( buf );}
		// 松开左键时鼠标在关闭按钮上
		if( wParam == NCHTCLOSEBUTTON )
		{
			// 而且鼠标上一次在关闭按钮上按下了。
			if( pMetroUIData->nMouseDownNCHTTEST == NCHTCLOSEBUTTON )
			{
				// 发出关闭窗口的消息
				PostMessage( hWnd,WM_SYSCOMMAND, SC_CLOSE, 0 );
			}
		}
		else if( wParam == NCHTMAXBUTTON )
		{
			if( pMetroUIData->nMouseDownNCHTTEST == NCHTMAXBUTTON )
			{
				PostMessage( hWnd,WM_SYSCOMMAND, IsZoomed( hWnd ) ? SC_RESTORE : SC_MAXIMIZE, 0 );
			}
		}
		else if( wParam == NCHTMINBUTTON )
		{
			if( pMetroUIData->nMouseDownNCHTTEST == NCHTMINBUTTON )
			{
				PostMessage( hWnd,WM_SYSCOMMAND, SC_MINIMIZE, 0 );
			}
		}
		pMetroUIData->nNcHitTestCode = wParam;//SendMessage( hWnd,WM_NCHITTEST,0,lParam );
		// 鼠标上一次在系统按钮上按下了，
		if( ( pMetroUIData->nMouseDownNCHTTEST == NCHTMAXBUTTON || pMetroUIData->nMouseDownNCHTTEST == NCHTMENUBUTTON || pMetroUIData->nMouseDownNCHTTEST == NCHTCLOSEBUTTON || pMetroUIData->nMouseDownNCHTTEST == NCHTMINBUTTON )
			// 但是松开左键时鼠标不在系统按钮上了。
			&& ( wParam != NCHTMAXBUTTON && wParam != NCHTMENUBUTTON && wParam != NCHTCLOSEBUTTON && wParam != NCHTMINBUTTON ) )
		{
			pMetroUIData->nMouseDownNCHTTEST = HTERROR;
			OnNcPaint( hWnd,1 );
		}
		pMetroUIData->nMouseDownNCHTTEST = HTERROR;
		break;
	case WM_LBUTTONUP:
		{static int i = 0;TCHAR buf[64] = { 0 };_stprintf(buf,_T("WM_LBUTTONUP  %d %d\r\n"),wParam,i++);OutputDebugString( buf );}
		{
			POINT pt = {GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)};
			ClientToScreen( hWnd,&pt );
			SendMessage( hWnd,WM_NCLBUTTONUP,SendMessage( hWnd,WM_NCHITTEST,0,MAKELPARAM(pt.x,pt.y) ),MAKELPARAM(pt.x,pt.y) );
		}
		break;
	default:break;
	}
	return ::CallWindowProc( pMetroUIData->oldWndProc,hWnd,uMsg,wParam,lParam );
}

void OnNcPaint( HWND hWnd,WPARAM wParam )
{
	PMetroUIData pMetroUIData = (PMetroUIData)GetProp( hWnd,_T("MetroUI_Prop") );
	HDC hDC = NULL;
	//if( wParam == 1 )
		hDC = GetWindowDC( hWnd);
	//else
	//{
	//	hDC = ::GetDCEx(m_hWnd,(HRGN)wParam,DCX_WINDOW | DCX_INTERSECTRGN | 0x10000);
	//}
	if( hDC == NULL ) return;

	RECT rcWindow,rcClient;
	GetWindowRect( hWnd,&rcWindow );
	GetClientRect( hWnd,&rcClient );
	ClientToScreen( hWnd,&rcClient );
	int nOffsetX = rcClient.left - rcWindow.left;
	int nOffsetY = rcClient.top - rcWindow.top;
	ScreenToClient( hWnd,&rcClient );
	int nWidth = rcWindow.right - rcWindow.left;
	int nHeight = rcWindow.bottom - rcWindow.top;
	rcWindow.left = 0;rcWindow.right = nWidth;rcWindow.top = 0;rcWindow.bottom = nHeight;
	rcClient.left += nOffsetX;rcClient.right += nOffsetX;rcClient.top += nOffsetY;rcClient.bottom += nOffsetY;

	// 一定要用双缓冲DC，否则闪烁会非常严重
	HDC hMemDC = CreateCompatibleDC( hDC );

	HBITMAP hMemBitmap = CreateCompatibleBitmap( hDC,nWidth,nHeight );
	HBITMAP hOldBitmap = (HBITMAP)SelectObject( hMemDC,hMemBitmap );

	HRGN rgnWindow = CreateRectRgn( rcWindow.left,rcWindow.top,rcWindow.right,rcWindow.bottom );
	HRGN rgnClient = CreateRectRgn( rcClient.left,rcClient.top,rcClient.right,rcClient.bottom );
	CombineRgn( rgnWindow,rgnWindow,rgnClient,RGN_XOR );
	DeleteObject( rgnClient );

	HRGN rgnWindowOld = CreateRectRgn( 0,0,0,0 );
	int nRet = GetWindowRgn( hWnd,rgnWindowOld );
	
	HBRUSH hBrush;
	HRGN hRgn;
	// 绘制标题栏时一定要设置剪切区域，否则绘制的内容会覆盖到客户区上面
	// 先绘制外边框
	CombineRgn( rgnWindow,rgnWindow,rgnWindowOld,RGN_AND );
	SelectClipRgn( hDC,rgnWindow );
	SelectClipRgn( hMemDC,rgnWindow );
	hBrush = CreateSolidBrush( 0x877A6F );
	FillRect( hMemDC,&rcWindow,hBrush );
	DeleteObject( hBrush );
	
	// 再绘制外边框往内缩进一个像素的内白边
	hRgn = CreateStretchRgn( rgnWindowOld,((float)nWidth-(float)2)/(float)nWidth,((float)nHeight-(float)2)/(float)nHeight,1,1 );
	CombineRgn( rgnWindow,rgnWindow,hRgn,RGN_AND );
	SelectClipRgn( hMemDC,rgnWindow );
	hBrush = CreateSolidBrush( 0xFBF6ED );
	FillRect( hMemDC,&rcWindow,hBrush );
	DeleteObject( hBrush );
	DeleteObject( hRgn );

	// 再绘制内白边以内的非客户区整体
	hRgn = CreateStretchRgn( rgnWindowOld,((float)nWidth-(float)4)/(float)nWidth,((float)nHeight-(float)4)/(float)nHeight,2,2 );
	CombineRgn( rgnWindow,rgnWindow,hRgn,RGN_AND );
	SelectClipRgn( hMemDC,rgnWindow );
	hBrush = CreateSolidBrush( 0xFDE7C5 );
	//FillRect( hMemDC,&rcWindow,hBrush );
	GradientFillRect( hMemDC,rcWindow,0xFDE7C5,0xffffff,true );
	DeleteObject( hBrush );
	DeleteObject( hRgn );

	//// 再绘制客户区向外扩张一个像素的边框
	//RECT rcTmp = rcClient;
	//rcTmp.left -= 1;rcTmp.top -= 1;rcTmp.right += 1;rcTmp.bottom += 1;
	//hBrush = CreateSolidBrush( 0xC1B592 );
	//FrameRect( hMemDC,&rcTmp,hBrush );
	//DeleteObject( hBrush );

	//rcTmp.top -= 1;rcTmp.bottom = rcTmp.top + 1;
	//hBrush = CreateSolidBrush( 0xF5EEE0 );
	//FillRect( hMemDC,&rcTmp,hBrush );
	//DeleteObject( hBrush );

	RECT rcTitle = rcWindow;
	rcTitle.left += 8;rcTitle.bottom = 30;
	// 画标题栏图标
	HICON hIcon = (HICON)::SendMessage( hWnd, WM_GETICON, ICON_SMALL, 0 );
	if( hIcon )
	{
		DrawIconEx( hMemDC,rcTitle.left,( rcTitle.bottom - rcTitle.top - GetSystemMetrics( SM_CYSMICON ) ) / 2,hIcon,GetSystemMetrics( SM_CXSMICON ),GetSystemMetrics( SM_CYSMICON ),NULL,NULL,DI_NORMAL );
		rcTitle.left += GetSystemMetrics( SM_CXSMICON ) + 5;
	}

	// 画最小化 最大化 关闭 按钮 同时计算标题栏文字的右界线，防止文字画到关闭最小化最大化按钮上了
	LONG lStyle = GetWindowLong( hWnd,GWL_STYLE );
	if( lStyle & WS_SYSMENU )
	{
		RECT rcButton = rcWindow;
		Gdiplus::Image * m_pImage = NULL;
		// 先画关闭按钮
		rcButton.left = rcButton.right - m_pPngCloseNormal->GetWidth();
		Gdiplus::Graphics graphics( hMemDC );
		m_pImage = m_pPngCloseNormal;
		rcTitle.right -= m_pImage->GetWidth();
		if( pMetroUIData->nNcHitTestCode == NCHTCLOSEBUTTON )
		{
			// 第一层判断：不能直接用if( pMetroUIData->nMouseDownNCHTTEST == NCHTCLOSEBUTTON )判断，否则会出现左键曾经在最大化按钮上按下了，但左健还没有释放
			// 此时，关闭按钮的状态会误设置为Over状态的了。
			if( pMetroUIData->nMouseDownNCHTTEST != HTERROR )
			{
				if( pMetroUIData->nMouseDownNCHTTEST == NCHTCLOSEBUTTON )
					m_pImage = m_pPngCloseDown;
			}
			else
				m_pImage = m_pPngCloseOver;
		}
		graphics.DrawImage( m_pImage,rcButton.left,0,m_pImage->GetWidth(),m_pImage->GetHeight() );
		// 画最大化按钮
		rcButton.right = rcButton.left;
		if( lStyle & WS_MAXIMIZEBOX )
		{
			if( lStyle & WS_MAXIMIZE )// 已经是最大化状态：画恢复按钮
			{
				m_pImage = m_pPngRestoreNormal;
				rcTitle.right -= m_pImage->GetWidth();
				if( pMetroUIData->nNcHitTestCode == NCHTMAXBUTTON )
				{
					if( pMetroUIData->nMouseDownNCHTTEST != HTERROR )
					{
						if( pMetroUIData->nMouseDownNCHTTEST == NCHTMAXBUTTON )
							m_pImage = m_pPngRestoreDown;
					}
					else
						m_pImage = m_pPngRestoreOver;
				}
				rcButton.left = rcButton.right - m_pImage->GetWidth();
				graphics.DrawImage( m_pImage,rcButton.left,0,m_pImage->GetWidth(),m_pImage->GetHeight() );
			}
			else// 不是最大化状态：画最大化按钮
			{
				m_pImage = m_pPngMaxNormal;
				rcTitle.right -= m_pImage->GetWidth();
				if( pMetroUIData->nNcHitTestCode == NCHTMAXBUTTON )
				{
					if( pMetroUIData->nMouseDownNCHTTEST != HTERROR )
					{
						if( pMetroUIData->nMouseDownNCHTTEST == NCHTMAXBUTTON )
							m_pImage = m_pPngMaxDown;
					}
					else
						m_pImage = m_pPngMaxOver;
				}
				rcButton.left = rcButton.right - m_pImage->GetWidth();
				graphics.DrawImage( m_pImage,rcButton.left,0,m_pImage->GetWidth(),m_pImage->GetHeight() );
			}
		}
		// 画最小化按钮
		m_pImage = m_pPngMinNormal;
		rcTitle.right -= m_pImage->GetWidth();
		if( pMetroUIData->nNcHitTestCode == NCHTMINBUTTON )
		{
			if( pMetroUIData->nMouseDownNCHTTEST != HTERROR )
			{
				if( pMetroUIData->nMouseDownNCHTTEST == NCHTMINBUTTON )
					m_pImage = m_pPngMinDown;
			}
			else
				m_pImage = m_pPngMinOver;
		}
		rcButton.right = rcButton.left;
		if( lStyle & WS_MINIMIZEBOX )
		{
			rcButton.left = rcButton.right - m_pImage->GetWidth();
			graphics.DrawImage( m_pImage,rcButton.left,0,m_pImage->GetWidth(),m_pImage->GetHeight() );
		}
		//// 画菜单按钮
		//m_pImage = m_pPngMenuNormal;
		//rcTitle.right -= m_pImage->GetWidth();
		//if( pMetroUIData->nNcHitTestCode == NCHTMENUBUTTON )
		//{
		//	if( pMetroUIData->nMouseDownNCHTTEST != HTERROR )
		//	{
		//		if( pMetroUIData->nMouseDownNCHTTEST == NCHTMENUBUTTON )
		//			m_pImage = m_pPngMenuDown;
		//	}
		//	else
		//		m_pImage = m_pPngMenuOver;
		//}
		//rcButton.right = rcButton.left;
		//rcButton.left = rcButton.right - m_pImage->GetWidth();
		//graphics.DrawImage( m_pImage,rcButton.left,0,m_pImage->GetWidth(),m_pImage->GetHeight() );
	}

	// 写标题栏文字
	rcTitle.right -= 8;
	TCHAR tzTitle[64] = { 0 };//最多只显示前64个字符
	GetWindowText( hWnd,tzTitle,sizeof(tzTitle) );
	int nOldBkMode = SetBkMode( hMemDC,TRANSPARENT );
	HFONT hFont = (HFONT)::SendMessage( hWnd, WM_GETFONT, 0, 0 );
	HFONT hFontTitle;
	LOGFONT lf;
	if( hFont != NULL )
	{
		::GetObject( hFont, sizeof(LOGFONT),&lf );
		//lf.lfWeight = FW_BOLD;
	}
	else
	{
		SystemParametersInfo( SPI_GETICONTITLELOGFONT,sizeof(LOGFONT),&lf,0 );
		//lf.lfWeight = FW_BOLD;
	}
	hFontTitle = CreateFontIndirect( &lf );
	HFONT hOldFont = (HFONT)SelectObject( hMemDC,hFontTitle );
	DrawShadowText( hMemDC,tzTitle,_tcsclen( tzTitle ),&rcTitle,DT_LEFT | DT_SINGLELINE | DT_VCENTER,0x000001,0xffffff,1,2 );
	DrawShadowText( hMemDC,tzTitle,_tcsclen( tzTitle ),&rcTitle,DT_LEFT | DT_SINGLELINE | DT_VCENTER,0x000001,0xffffff,-1,0 );
	SelectObject( hMemDC,hOldFont );
	DeleteObject( hFontTitle );
	SetBkMode( hMemDC,nOldBkMode );

	BitBlt( hDC,0,0,nWidth,nHeight,hMemDC,0,0,SRCCOPY );

	SelectObject( hMemDC,hOldBitmap );

	// 开始释放前面建立的资源对象
	DeleteObject( rgnWindowOld );
	DeleteObject( rgnWindow );
	DeleteObject( hMemBitmap );
	DeleteDC( hMemDC );

	ReleaseDC( hWnd,hDC );
}

HBRUSH GetBrush( PMetroUIData pMetroUIData,HWND hWnd,WPARAM wParam,LPARAM lParam )
{
	map< HWND,HBRUSH >::iterator p = pMetroUIData->mapControlBrush.find( (HWND)lParam );
	if( p == pMetroUIData->mapControlBrush.end() )
	{
		TCHAR buf[64] = { 0 };
		GetWindowText( (HWND)lParam,buf,64 );
		HDC hDC = ::GetDC( hWnd );
		if( hDC )
		{
			RECT rc,rcControl;
			GetClientRect( hWnd,&rc );
			LONG lStyle = GetWindowLong( hWnd,GWL_STYLE );
			bool bResize = ( ( lStyle & WS_THICKFRAME ) == WS_THICKFRAME );
			// 将rc.top将上便移标题栏高度再减2的像素，目的在于绘制客户区背景时保持和标题栏的背景渐变一致。
			rc.top -= GetSystemMetrics( SM_CYCAPTION ) + ( bResize ? GetSystemMetrics( SM_CYSIZEFRAME ) : GetSystemMetrics( SM_CYFIXEDFRAME ) ) - 2;
			GetWindowRect( (HWND)lParam,&rcControl );
			ScreenToClient( hWnd,&rcControl );

			HDC hMemDC = ::CreateCompatibleDC( hDC );
			HBITMAP hBitmap = ::CreateCompatibleBitmap( hDC,rc.right - rc.left,rc.bottom - rc.top );
			HBITMAP hOldBitmap = (HBITMAP)::SelectObject( hMemDC,hBitmap );

			GradientFillRect( hMemDC,rc,0xFDE7C5,0xffffff,true );

			HDC hMemDC2 = ::CreateCompatibleDC( hMemDC );
			HBITMAP hBitmap2 = ::CreateCompatibleBitmap( hMemDC,rcControl.right - rcControl.left,rcControl.bottom - rcControl.top );
			HBITMAP hOldBitmap2 = (HBITMAP)SelectObject( hMemDC2,hBitmap2 );
			
			BitBlt( hMemDC2,0,0,rcControl.right - rcControl.left,rcControl.bottom - rcControl.top,hMemDC, rcControl.left, rcControl.top, SRCCOPY);

			HBRUSH hBrush = ::CreatePatternBrush( hBitmap2 );
			pMetroUIData->mapControlBrush.insert( map<HWND,HBRUSH>::value_type( (HWND)lParam,hBrush ) );

			SelectObject( hMemDC2,hOldBitmap2 );
			DeleteObject( hBitmap2 );
			DeleteDC( hMemDC2 );

			SelectObject( hMemDC,hOldBitmap );
			DeleteObject( hBitmap );
			DeleteDC( hMemDC );

			ReleaseDC( hWnd,hDC );

			return hBrush;
		}
	}
	else
	{
		return (HBRUSH)(p->second);
	}
	return NULL;
}

void OnPaint( HWND hWnd )
{
	/*********************************************************************************************************************************************\
	IsIconic()作用是判断窗口是否处于最小化状态（点击了最小化按钮之后）。  对于普通的对话框来说，如果你在if (IsIconic()) 下面加入AfxMessageBox("haha") ，
	你会发现消息框并不会弹出。  原因是，if (IsIconic()) 这段代码是在OnPaint()函数内，当你最小化了对话框之后，虽然IsIconic()的值是TRUE，但是OnPaint()函数
	并不会运行。因为OnPaint()响应的是WM_PAINT消息，而WM_PAINT消息是针对客户区的。一个最小化了的窗口不需要重绘客户区。  为了验证这一点，可以设置一定时器，
	在OnTimer()函数里写上 if(IsIconic()) MessageBeep(MB_OK); 当你点击最小化按钮后，你会听见嘟嘟声。  那么这段代码究竟有什么用？它是不是永远不会被执行呢？
	当然不是。举两个例子。 第一，如果你强行发送WM_PAINT消息，它会执行。 第二，特殊的对话框。比如一个ToolBox风格的对话框。这个对话框不显示在任务栏，在最小
	化之后它会变成一个很小的一条显示在桌面上。这时如果它被遮挡，就会出发WM_PAINT消息，从而执行那段代码。    总之，一般情况下可以不要这段代码，它的特殊用
	途我也不是很了解，但是我们至少可以知道它是怎么样工作的。
	\********************************************************************************************************************************************/
	if( ::IsIconic( hWnd ) )
	{
	}
	else
	{
		PAINTSTRUCT ps;
		RECT rc;
		GetClientRect( hWnd,&rc );
		LONG lStyle = GetWindowLong( hWnd,GWL_STYLE );
		bool bResize = ( ( lStyle & WS_THICKFRAME ) == WS_THICKFRAME );
		rc.top -= GetSystemMetrics( SM_CYCAPTION ) + ( bResize ? GetSystemMetrics( SM_CYSIZEFRAME ) : GetSystemMetrics( SM_CYFIXEDFRAME ) ) - 2;
		HDC hDC = ::BeginPaint( hWnd,&ps );
		HDC hMemDC = ::CreateCompatibleDC( hDC );
		HBITMAP hBitmap = ::CreateCompatibleBitmap( hDC,rc.right - rc.left,rc.bottom - rc.top );
		HBITMAP hOldBitmap = (HBITMAP)SelectObject( hMemDC,hBitmap );
		GradientFillRect( hMemDC,rc,0xFDE7C5,0xffffff,true );
		::BitBlt( hDC,0,0,rc.right - rc.left,rc.bottom - rc.top,hMemDC,0,0,SRCCOPY );
		SelectObject( hMemDC,hOldBitmap );
		DeleteObject( hBitmap );
		DeleteDC( hMemDC );
		::EndPaint( hWnd,&ps );
	}
}

LRESULT CALLBACK CallWndProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if( ((CWPSTRUCT*)lParam)->message==WM_NCCREATE)
	{
		TCHAR tzClassName[64] = { 0 };
		GetClassName( ((CWPSTRUCT*)lParam)->hwnd,tzClassName,sizeof(tzClassName)-1 );
		if( _tcsicmp( tzClassName,_T("#32770") ) == 0 )
		{
			PMetroUIData pMetroUIData = new MetroUIData;
			pMetroUIData->oldWndProc = (WNDPROC)SetWindowLong( ((CWPSTRUCT*)lParam)->hwnd,GWL_WNDPROC,(LONG)WindowProc );
			pMetroUIData->lStyle = GetWindowLong( ((CWPSTRUCT*)lParam)->hwnd,GWL_STYLE );
			pMetroUIData->lStyleEx = GetWindowLong( ((CWPSTRUCT*)lParam)->hwnd,GWL_EXSTYLE );
			pMetroUIData->bTracking = FALSE;
			pMetroUIData->nMouseDownNCHTTEST = HTERROR;
			pMetroUIData->nNcHitTestCode = HTERROR;
			pMetroUIData->hClientBrush = NULL;
			SetProp( (HWND)wParam,_T("MetroUI_Prop"),(HANDLE)pMetroUIData );
		}
	}

	return CallNextHookEx(g_hHook,nCode,wParam,lParam);
}

LRESULT CALLBACK CBTProc( int nCode,WPARAM wParam,LPARAM lParam )
{
	if( HCBT_CREATEWND == nCode )
	{
		TCHAR tzClassName[64] = { 0 };
		GetClassName( (HWND)wParam,tzClassName,sizeof(tzClassName)-1 );
		if( _tcsicmp( tzClassName,_T("#32770") ) == 0 )
		{
			PMetroUIData pMetroUIData = new MetroUIData;
			pMetroUIData->oldWndProc = (WNDPROC)SetWindowLong( (HWND)wParam,GWL_WNDPROC,(LONG)WindowProc );
			pMetroUIData->lStyle = GetWindowLong( (HWND)wParam,GWL_STYLE );
			pMetroUIData->lStyleEx = GetWindowLong( (HWND)wParam,GWL_EXSTYLE );
			pMetroUIData->bTracking = FALSE;
			pMetroUIData->nMouseDownNCHTTEST = HTERROR;
			pMetroUIData->nNcHitTestCode = HTERROR;
			pMetroUIData->hClientBrush = NULL;
			SetProp( (HWND)wParam,_T("MetroUI_Prop"),(HANDLE)pMetroUIData );
		}
	}
	return CallNextHookEx(g_hHook,nCode,wParam,lParam);
}

LRESULT CALLBACK GetMsgProc( int code,WPARAM wParam,LPARAM lParam )
{
	if( ((MSG*)lParam)->message == WM_LBUTTONUP )
	{
		HWND hWnd = GetForegroundWindow();
		if( hWnd )
		{
			PMetroUIData pMetroUIData = (PMetroUIData)GetProp( hWnd,_T("MetroUI_Prop") );
			if( pMetroUIData )
			{
				if( pMetroUIData->nMouseDownNCHTTEST != HTERROR )
				{
					SendMessage( hWnd,WM_NCMOUSEMOVE,HTCLIENT,((MSG*)lParam)->lParam );
				}
			}
		}
	}
	return CallNextHookEx(g_hHook,code,wParam,lParam);
}

BOOL UseMetroUI( BOOL bUse )
{
	if( bUse )
	{
		// 已经安装过钩子，则返回FALSE
		if( g_hHook != NULL ) return FALSE;
		// 初始化GDI+支持
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		Gdiplus::GdiplusStartup( &m_gdiplusToken, &gdiplusStartupInput, NULL);
		// 从资源类加载PNG图片
		// 菜单按钮
		ImageFromIDResource( g_ucSysButtonMenuNormal,sizeof(g_ucSysButtonMenuNormal),m_pPngMenuNormal );
		ImageFromIDResource( g_ucSysButtonMenuOver,sizeof(g_ucSysButtonMenuOver),m_pPngMenuOver );
		ImageFromIDResource( g_ucSysButtonMenuDown,sizeof(g_ucSysButtonMenuDown),m_pPngMenuDown );
		// 最小化按钮
		ImageFromIDResource( g_ucSysButtonMinNormal,sizeof(g_ucSysButtonMinNormal),m_pPngMinNormal );
		ImageFromIDResource( g_ucSysButtonMinOver,sizeof(g_ucSysButtonMinOver),m_pPngMinOver );
		ImageFromIDResource( g_ucSysButtonMinDown,sizeof(g_ucSysButtonMinDown),m_pPngMinDown );
		// 最大化按钮
		ImageFromIDResource( g_ucSysButtonMaxNormal,sizeof(g_ucSysButtonMaxNormal),m_pPngMaxNormal );
		ImageFromIDResource( g_ucSysButtonMaxOver,sizeof(g_ucSysButtonMaxOver),m_pPngMaxOver );
		ImageFromIDResource( g_ucSysButtonMaxDown,sizeof(g_ucSysButtonMaxDown),m_pPngMaxDown );
		// 恢复按钮
		ImageFromIDResource( g_ucSysButtonRestoreNormal,sizeof(g_ucSysButtonRestoreNormal),m_pPngRestoreNormal );
		ImageFromIDResource( g_ucSysButtonRestoreOver,sizeof(g_ucSysButtonRestoreOver),m_pPngRestoreOver );
		ImageFromIDResource( g_ucSysButtonRestoreDown,sizeof(g_ucSysButtonRestoreDown),m_pPngRestoreDown );
		// 关闭按钮
		ImageFromIDResource( g_ucSysButtonCloseNormal,sizeof(g_ucSysButtonCloseNormal),m_pPngCloseNormal );
		ImageFromIDResource( g_ucSysButtonCloseOver,sizeof(g_ucSysButtonCloseOver),m_pPngCloseOver );
		ImageFromIDResource( g_ucSysButtonCloseDown,sizeof(g_ucSysButtonCloseDown),m_pPngCloseDown );

		g_hHook = SetWindowsHookEx(WH_CBT,CBTProc,0,GetCurrentThreadId());
		return ( g_hHook != NULL );
	}
	else
	{
		// 释放GDI+支持
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
		if( g_hHook )
		{
			UnhookWindowsHookEx(g_hHook);
			g_hHook = NULL;
		}
	}
	return TRUE;
}

/*********************************************************************************************************************************************************\
当在非客户区点击鼠标左键并释放时，系统会发送窗口的WM_LBUTTONUP(注意不是WM_NCLBUTTONUP，这是客户区的鼠标释放消息，但是我们现在在非客户区释放鼠标！
如之奈何)消息到线程的消息队列，但线程的消息队列压根就不把这个消息发送给这个窗口的窗口过程!

解决办法如下：

1.       响应非客户区鼠标按下的消息WM_NCLBUTTONDOWN， 定义一个flag, m_bNCLButtonDowned = true; 表示当前在非客户区按下了鼠标左键

2.       使用WH_GETMESSAGE的HOOK, hook整个线程的消息队列,从而得到在非客户区释放鼠标时的WM_LBUTTONUP消息(因为spy++就是这种方式，因此我们也可以采用这种方式，当然google里的那哥们使用的是mouse hook,忒复杂了些)

3.       在hook回调函数里的WM_LBUTTONUP消息判断当前m_bNCLButtonDowned == true?非客户区里是否按下了鼠标左键，如果是，则PostMessage一个WM_NCLBUTTONUP，将真正的非客户区的

鼠标释放消息发送给窗口的窗口过程

4.       在窗口过程里的WM_NCLBUTTONUP的处理函数里判断m_bNCLButtonDowned == true?如果是，则执行代码，同时置位m_bNCLButtonDowned,表示当前已经释放了鼠标左键，因此鼠标左键没有按下

其实有更好的办法（网上这么说的，我验证了一下，比较扯蛋，还是建议用第一种方法），不用hook。


在OnSysCommand函数里处理一下，手动发一个WM_NCLBUTTONUP消息，具体代码如下：
void CXX::OnSysCommand(UINT nID, LPARAM lParam)

{
   CDialog::OnSysCommand(nID, lParam);
   if( (nID & 0xFFF0) == SC_MOVE )
   {
    PostMessage(WM_NCLBUTTONUP, HTCAPTION, lParam);   // 发送WM_NCLBUTTONUP消息
   }

}

经过zhllxt的实际测试发现，在系统按钮上按下左键不动，鼠标移动到窗口外边，释放左键，WH_GETMESSAGE的HOOK仍然接收不到WM_LBUTTONUP消息，但是会触发WM_NCMOUSELEAVE消息
但当左键在系统按钮上按下，然后鼠标移动到客户区的控件上，并在控件上释放左键时，不会产生WM_NCMOUSELEAVE消息，却会进入WH_GETMESSAGE HOOK函数。
\*********************************************************************************************************************************************************/
