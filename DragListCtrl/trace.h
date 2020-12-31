/*==================trace 输出调试字符串====================
(一)功能：
	输出调试变量(类似于TRACE)

(二)特点:
	1.自动适应参数的类型(char、char*、string、CString、HWND、POINT、RECT....)
	2.自动适应输入参数的个数。(关闭了编译提醒 #pragma warning(disable: 4003) )
	3.会在输出的变量值前面自动添加变量的名称，方便查看
	4.程序自动创建Edit窗口用于输出转换后的字符串。
	5.程序退出时会将输出字符串保存到工程目录下的DebugData.txt。方便查看
	6.多种编译模式，比如可让DEBUG和Release版本都能输出调试变量或者两者都不输出
	7.支持UNICODE,WIN32,Dll,MFC

(三)使用说明：
	1.把trace.h复制到工程目录下（可以不添加到工程）。
	2.在文件"stdafx.h"里（文件的下方）添加 #include "trace.h"。之后就可以使用trace()宏了。
	3.所有输出的字符串会保存在工程目录下的"DebugData.txt"文件，以方便查看
	4.我把所有代码都放在一个头文件里，虽然不合符规范，但这样使用起来很方便。
	5.trace(x,y,z,w)宏原本有4个参数，当参数不如时，编译器会给出警告，
	  所以使用	#pragma warning(disable: 4003) 把这个编译警告给关掉了。

(四)可以使用的宏：
	trace(X,Y,Z,W)	//输出常用类型变量，如int、double、short、POINT、RECT、string
					//且自动适应变量的个数（变量数为1-4个）
	tracef()		//格式化字符串，类似sprintf
	traceLastError()//输出系统错误代码，调用了GetLastError()
	traceRel(X,Y)	 //当X=true，输出"Y: successful" ; x=false，输出"Y: failed"
	CEasyTrace::clear();			//清空窗口
	

(五)关于trace宏使能设置：
	1.默认情况下 NO_TRACE_WINDOW 和 TRACE_WINDOW都没定义，则
	  DEBUG版本会输出调试字符串，而Release版本不会
	2.如果开头定义了#define NO_TRACE_WINDOW
	  DEBUG版本和Release版本都不会输出输出调试字符串
	3.如果开头定义了#define TRACE_WINDOW
	  DEBUG版本和Release版本都会输出输出调试字符串
	4.每次修改上面2个宏后需要全部重新编译才会生效

(六)调用示例：
	void CDemoDlg::OnButton1() 
	{
		int a=45; double b=67.45; double c=847.424;short d=324;
		RECT rect;
		::GetWindowRect(m_hWnd,&rect);
		HWND hWnd=::GetForegroundWindow();
		POINT point;
		GetCursorPos(&point);
		bool ak=true;
		CPoint cpoint(88,421);
		CRect crect(19,423,56,522);
		CString mfcstr=_T("mfc CString");
		TCHAR buf[100]=_T("c style string"); 

	#ifdef _UNICODE
		wstring stlstr=_T("stl string");
	#else
		string stlstr=_T("stl string");
	#endif

		tracef(_T("tracef 类似于 %s"),_T("sprintf")); //格式化字符串，类似sprintf
		trace(_T("Impossible is nothing"));
		trace(stlstr);   //输出字符串
		trace(mfcstr);   //输出字符串
		trace(buf);   //输出字符串
		trace(a);		//输出int
		trace(a,b);		//输出int和double
		trace(a,b,c);
		trace(a,b,c,d);
		trace(point);	
		trace(point,cpoint);	//输出POINT 和 CPoint	
		trace(rect);
		trace(rect,crect);		//输出RECT 和 CRect
		trace(hWnd);			//输出窗口信息
		traceLastError();		//输出系统错误代码		
		traceRel(ak==true,"func()");  //当X=true，输出"Y: successful" ; x=false，输出"Y: failed"
	}

(七)技巧：
	1.有时候我们只想观察某一个变量的变化，但程序里有很多trace，所以输出到窗口的
	  数据影响了我们的观察。这是我们可以这样做，就能令其他trace都无效了。

	  traceStart();		//接收数据
	  trace(_T("只有 traceStart 和 traceStop 之间的trace才有效"));
	  traceStop();		//禁止接收数据


版权声明:
	没有版权，许可任何单位,个人随意使用,拷贝,修改，但作者不承担由
	此代码带来的任何损失。由于作者水平有限，错误或不完善之处，在
	所难免，由此为你带来的不便，还望海涵。如果有任何BUG，请联系作者，
	大家一起完善它！以后有更新统一放在以下网址上，你可以浏览并获得
	更新以及详细的使用说明：
	当前更新日期：2011-10-21
	http://blog.csdn.net/jacky_qiu/archive/2010/11/04/5986089.aspx

最后:
	如果此份代码为你带来了帮助，并且使你心生感谢之意。那我可否请你
	诚心恭敬地念10遍“南(音:拿na)无(音:摩mo)阿弥陀佛”？
	愿得佛力加持，使你工作顺利，合家幸福！
	
											Jacky
											2011-5-25
											qiujiejia@gmail.com

========================================================================*/


#ifndef _EASY_TRACE_H_
#define _EASY_TRACE_H_


//trace宏编译开关━━━━━━━━━
//  #define NO_TRACE_WINDOW		//DEBUG版本和Release版本都不会输出输出调试字符串
//  #define TRACE_WINDOW		//DEBUG版本和Release版本都会输出输出调试字符串	
#ifdef NO_TRACE_WINDOW
#else
#ifdef _DEBUG
#define TRACE_WINDOW
#else
#ifdef	RELEASE_TRACE
#define TRACE_WINDOW
#endif
#endif
#endif

//trace宏的参数是4个，当参数少于4个，编译器会给出警告，我们手动关闭这个
//警告(disable warning C4003: not enough actual parameters for macro)
#pragma warning(disable: 4003)
#pragma warning(disable: 4002)


#define	TRACE_WND_TEXT _T("TraceWnd")	//窗口标题
#define WM_CREATE_WND	WM_USER+888		//自定义消息
#define AUTO_HIDE_TIME	3000			//定义多少毫秒后自动窗口
#include <Windows.h> //需要的头文件
#include <tchar.h>
#include <sstream>


//Not #define TRACE_WINDOW
#ifndef TRACE_WINDOW 
#define trace(X)
#define tracef	__noop
#define traceLastError()	
#define traceRel(X)			
#define traceClear(X)				
#define traceStop(X)		
#define traceStart(X)		
#endif

//#define TRACE_WINDOW
#ifdef TRACE_WINDOW 

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━trace宏━━━━
#define trace(X,Y,Z,W) {CEasyTrace obj;	\
		obj.name(#X);	obj.add(X);	\
		obj.name(#Y);	obj.add(Y);	\
		obj.name(#Z);	obj.add(Z);	\
		obj.name(#W);	obj.add(W); }

#define tracef				  CEasyTrace::Tracef	
#define traceLastError()	{ CEasyTrace().TraceSysError();		}
#define traceRel(X)			{ CEasyTrace().TraceResult(#X,X);	}
#define traceClear(X)		{ ::SendMessage(::FindWindow(NULL,TRACE_WND_TEXT),WM_COMMAND,3,NULL); }				
#define traceStart(X)		{ CEasyTrace::IsReceive(TRUE);		}
#define traceStop(X)		{ CEasyTrace::IsReceive(FALSE);		}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━





class CTraceWnd
{
public:
	~CTraceWnd(){ ::DestroyWindow(::FindWindow(NULL,TRACE_WND_TEXT)); }
	
	/****************************************************************************
	行首序列号
	-1 ---- 不输出索引
	1   --- 重置索引值为1 
	0    ---获取索引
	****************************************************************************/
	static TCHAR* GetIndex(int opt=0)
	{
#define INDDEX_NUM 4  //对齐的位数

		static int num=1;
		static TCHAR buf[11]={0};
		static TCHAR buf2[11]={0};
		static BOOL IsOutIndex=-10;
		if (IsOutIndex==-10) IsOutIndex=GetProfileInt(TRACE_WND_TEXT,_T("m_IsIndex"),TRUE);

		if (opt==-1) IsOutIndex=FALSE;
		if (opt== 1) {IsOutIndex=1; num=1;}
		if (!IsOutIndex) {  buf[0]=NULL; return buf;}

		
		_itot(num++,buf,10);//int 转文本
		int len=_tcslen(buf);
		int count=INDDEX_NUM-len;
		if (count>0)
		{
			for (int i=0; i< count;i++)	{buf2[i]=' ';}
			_tcscpy(buf2+count,buf);
			return buf2;
		}
		else
			return buf;
	}


	static BOOL IsName(BOOL var=-1)
	{
		static int state=-10;
		if (state==-10)		state=GetProfileInt(TRACE_WND_TEXT,_T("m_IsName"),TRUE);
		if(var!=-1) state=var;
		return state;
	}
	
	/****************************************************************************
	输出的字符串到窗口
	****************************************************************************/
	static void CTraceWnd::PrintString(const TCHAR* OutputStr)
	{
		//寻找已创建的输出窗口
		HWND hWnd=::FindWindow(NULL,TRACE_WND_TEXT);
		
		//如果不存在，则创建窗口并初始化设置
		if ( !hWnd )
		{
			//定义这个对象是为了程序退出是调用析构函数来
			//保存文件和关闭窗口，除此之外没有其他用处了
			static CTraceWnd ForGetCloseMessage;
			
			//创建窗口
			hWnd=(HWND)WindowProc(NULL,WM_CREATE_WND,NULL,NULL);
			if (!hWnd)	return;
		}
		
		//将字符串输出到窗口
		::SendMessage(hWnd,EM_REPLACESEL,FALSE,(LPARAM)OutputStr);	
	}

	/****************************************************************************
	//保存窗口配置
	****************************************************************************/
	static void SaveConfig(BOOL	m_IsAutoWidth,BOOL m_IsAutoHide,BOOL m_IsHide,BOOL m_IsContinue,BOOL m_IsName,BOOL m_IsIndex,HWND hWnd)
	{
		TCHAR buf[11];
		_itot(m_IsAutoWidth,buf,10);	WriteProfileString(TRACE_WND_TEXT,_T("m_IsAutoWidth"),buf);
		_itot(m_IsAutoHide ,buf,10);	WriteProfileString(TRACE_WND_TEXT,_T("m_IsAutoHide"), buf);
		_itot(m_IsHide	   ,buf,10);	WriteProfileString(TRACE_WND_TEXT,_T("m_IsHide"),	  buf);
		_itot(m_IsContinue ,buf,10);	WriteProfileString(TRACE_WND_TEXT,_T("m_IsContinue"), buf);
		_itot(m_IsName	   ,buf,10);	WriteProfileString(TRACE_WND_TEXT,_T("m_IsName"),     buf);
		_itot(m_IsIndex	   ,buf,10);	WriteProfileString(TRACE_WND_TEXT,_T("m_IsIndex"),    buf);
		if (!m_IsHide)
		{
			RECT rect; 
			::GetWindowRect(hWnd,&rect);
			_itot(rect.left,buf,10);			WriteProfileString(TRACE_WND_TEXT,_T("x"),buf);
			_itot(rect.top,buf,10);				WriteProfileString(TRACE_WND_TEXT,_T("y"),buf);
			_itot(rect.right-rect.left,buf,10);	WriteProfileString(TRACE_WND_TEXT,_T("cx"),buf);
			_itot(rect.bottom-rect.top,buf,10);	WriteProfileString(TRACE_WND_TEXT,_T("cy"),buf);
		}
	}
	
	static void ReShowWindow(HWND hWnd)
	{
		int x=GetProfileInt(TRACE_WND_TEXT,_T("x"),0);
		int y=GetProfileInt(TRACE_WND_TEXT,_T("y"),0);
		int cx=GetProfileInt(TRACE_WND_TEXT,_T("cx"),200);
		int cy=GetProfileInt(TRACE_WND_TEXT,_T("cy"),600);
		::SetWindowPos(hWnd,HWND_TOPMOST,x,y,cx,cy,SWP_NOACTIVATE);
	}

	static void HideWindowToLeftScreen(HWND hWnd)
	{
		::SetWindowPos(hWnd,HWND_TOPMOST,-100,0,104,GetSystemMetrics(SM_CYSCREEN),NULL);
	}


	/****************************************************************************
	Edit Window的窗口过程
	****************************************************************************/
	static LRESULT CALLBACK CTraceWnd::WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
	{
		static WNDPROC	m_OldWndProc	=	NULL;
		static int		m_WindowWidth	=	200;	//窗口宽度
		static HWND		StaticWnd		=	NULL;	//
		static BOOL		m_IsReceive		=	TRUE;	//是否接受数据
		static BOOL		m_IsContinue	=	TRUE;	//当输出字符串时是否清空之前的数据
		static BOOL		m_IsAutoWidth	=	TRUE;	//是否根据字符串长度自动调整窗口宽度
		static BOOL		m_IsAutoHide	=	FALSE;	//是否自动隐藏
		static BOOL		m_IsHide		=	FALSE;	//是否隐藏
		static BOOL		m_IsName		=	TRUE;	//是否自动补上变量名
		static BOOL		m_IsIndex		=	TRUE;	//添加行号索引
	
		switch(message)
		{
		case WM_CREATE_WND: //创建Edit窗口 ,这是自定义消息
			{
				//获取窗口配置
				int x=GetProfileInt(TRACE_WND_TEXT,_T("x"),0);
				int y=GetProfileInt(TRACE_WND_TEXT,_T("y"),0);
				int cx=GetProfileInt(TRACE_WND_TEXT,_T("cx"),200);
				int cy=GetProfileInt(TRACE_WND_TEXT,_T("cy"),600);
				m_IsAutoWidth	=GetProfileInt(TRACE_WND_TEXT,_T("m_IsAutoWidth"),1);
				m_IsAutoHide	=GetProfileInt(TRACE_WND_TEXT,_T("m_IsAutoHide"),0);
				m_IsHide		=GetProfileInt(TRACE_WND_TEXT,_T("m_IsHide"),FALSE);
				m_IsContinue	=GetProfileInt(TRACE_WND_TEXT,_T("m_IsContinue"),TRUE);
				m_IsName		=GetProfileInt(TRACE_WND_TEXT,_T("m_IsName"),TRUE);
				IsName(m_IsName);
				m_IsIndex		=GetProfileInt(TRACE_WND_TEXT,_T("m_IsIndex"),TRUE);
				GetIndex( m_IsIndex ? 1 : -1);
				m_IsReceive		=TRUE; //不需要保存在配置文件

				//超出屏幕重新调整
				int SrcCx=GetSystemMetrics(SM_CXSCREEN);
				int SrcCy=GetSystemMetrics(SM_CYSCREEN);
				if (x<0 || x>=SrcCx) x=0;
				if (y<0 || y>=SrcCy) y=0;
				if (cx<100) cx=100;
				if (cy<40)	cy=40;
				if (x+cx>SrcCx) x=SrcCx-cx;
				if (y+cy>SrcCy) y=SrcCy-cy;

				//如果窗口是隐藏状态，修改x的值
				if (m_IsHide)
				{
					x=-cx+4;
					y=0;
					cy=GetSystemMetrics(SM_CYSCREEN);
				}

				HWND hWnd=CreateWindowEx(WS_EX_TOPMOST|WS_EX_TOOLWINDOW,TEXT("Edit"),TRACE_WND_TEXT ,
					WS_OVERLAPPEDWINDOW|WS_VSCROLL|WS_HSCROLL|
					ES_AUTOHSCROLL|ES_WANTRETURN|ES_MULTILINE , 
					x,y,cx,cy,
					NULL,NULL,NULL,NULL);
				
				if (hWnd==NULL)	return NULL;
				
				//创建菜单,并添加到窗口
				HMENU hMenu = CreateMenu() ;
				AppendMenu(hMenu,MF_STRING, 5,	_T("隐藏到屏幕左边") )	;
				AppendMenu(hMenu,MF_STRING, 3,	_T("清空窗口"));
				//-----------------sub menu
				HMENU hSubMenu=CreateMenu() ;
				AppendMenu(hSubMenu,MF_STRING, 6,  _T("自动隐藏") );
				AppendMenu(hSubMenu,MF_STRING, 7,  _T("接受数据") );
				AppendMenu(hSubMenu,MF_STRING, 4,  _T("根据字符串长度自动调整窗口宽度" ));
				AppendMenu(hSubMenu,MF_STRING, 9,  _T("连续输出数据"));
				AppendMenu(hSubMenu,MF_STRING, 10, _T("输出时自动添加变量名"));
				AppendMenu(hSubMenu,MF_STRING, 11, _T("输出时添加行号索引"));
				AppendMenu(hSubMenu,MF_STRING, 8,  _T("帮助"));
				//-----------------sub menu
				AppendMenu(hMenu, MF_POPUP,UINT(hSubMenu), _T("选项")) ;
				::SetMenu(hWnd,hMenu);
			

				//修改edit框的限制字符个数
				::SendMessage(hWnd,EM_SETLIMITTEXT,1000000, 0);
				
				//清空Edit
				::SendMessage(hWnd,WM_SETTEXT,NULL,(LPARAM)_T(""));	
				
				// 设置字体参数
				LOGFONT LogFont;
				::memset(&LogFont, 0, sizeof(LOGFONT));
				lstrcpy(LogFont.lfFaceName,_T("Fixedsys"));
				LogFont.lfHeight = -12; // 字体大小
				LogFont.lfCharSet = GB2312_CHARSET;
				// 创建字体
				HFONT hFont=CreateFontIndirect(&LogFont); 
				// 设置字体
				::SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, 0);
				
				//把hWnd的默认窗口过程替换为WindowProc,返回默认函数过程的函数指针
				m_OldWndProc=(WNDPROC)SetWindowLong(hWnd,GWL_WNDPROC, (LONG)WindowProc);
				if (!m_OldWndProc)
					return NULL;
				
				//显示时无焦点
				::ShowWindow(hWnd,SW_SHOWNOACTIVATE);
				
				//如果没有开启自动隐藏并且又处于隐藏状态，则弹出提示窗口
				if (!m_IsAutoHide && m_IsHide)
				{
					StaticWnd=CreateWindowEx(WS_EX_TOPMOST,_T("Static"),
						_T("Trace窗口隐藏在屏幕左边\n点击屏幕左边可恢复窗口"),
						WS_POPUP|WS_VISIBLE|WS_BORDER
						|SS_CENTER ,
						0,y,200,40,NULL,NULL,NULL,NULL); 

					SetTimer(hWnd,2,2000,NULL);
				}

				return (LRESULT)hWnd;
			}
			break;

		case WM_TIMER:
			{
				if (wParam==2) //关闭提示窗口
				{
					::DestroyWindow(StaticWnd); 
					break;
				}

				if ( !m_IsHide && ::GetForegroundWindow()!=hWnd)
				{
					//隐藏窗口
					m_IsHide=true;
					HideWindowToLeftScreen(hWnd);
				}
			}
			break;

		case WM_ACTIVATE:
			{
				if (LOWORD(wParam)==WA_INACTIVE ) //窗口失去焦点
				{
					if (m_IsAutoHide)
					{
						::SetTimer(hWnd,1,200,NULL); //延长200ms后hide
					}
				}
			}
			break;

		case WM_NCLBUTTONDOWN:
			{
				if (m_IsHide)
				{
					m_IsHide=false;
					ReShowWindow(hWnd); //重新显示窗口
					// save m_IsHide 
					SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
				}
				else
				{
					//传递默认操作另其改变窗口的位置大小
					int rel=::CallWindowProc(m_OldWndProc, hWnd, message, wParam, lParam); 

					if (wParam==HTLEFT	 ||wParam==HTTOP		||wParam==HTRIGHT		||wParam==HTBOTTOM || wParam==HTCAPTION ||
						wParam==HTTOPLEFT||wParam==HTTOPRIGHT	||wParam==HTBOTTOMLEFT	||wParam==HTBOTTOMRIGHT)
					{
						//保存窗口配置
						SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
					}

					return rel;
				}
			}
			break;

		case EM_REPLACESEL:
			{
				if(!m_IsReceive)	return 0;

				if (m_IsContinue)
				{
					//光标指向最后
					::SendMessage(hWnd,EM_SETSEL,4294967290, 4294967290);	

					//调用默认过程添加字符串到edit 窗口
					::CallWindowProc(m_OldWndProc, hWnd, message, wParam, lParam); 
				}
				else
				{
					::SendMessage(hWnd,WM_SETTEXT,NULL,lParam);
				}
				
				
				//开启了自动隐藏功能
				if (m_IsAutoHide)
				{
					if (m_IsHide)
					{
						m_IsHide=false;
						ReShowWindow(hWnd);
					}

					//设置AUTO_HIDE_TIME后隐藏窗口
					::SetTimer(hWnd,1,AUTO_HIDE_TIME,NULL);
				}

				//开启了自动调整窗口的宽度功能
				if (m_IsAutoWidth)
				{
					if (!m_IsHide)
					{
						int MinPos,MaxPos;
						GetScrollRange(hWnd,SB_HORZ, &MinPos,&MaxPos);
						if (m_WindowWidth<MaxPos+40)
						{
							m_WindowWidth=MaxPos+40;
							RECT rect; 
							::GetWindowRect(hWnd,&rect);
							::SetWindowPos(hWnd,NULL,0,0,m_WindowWidth,rect.bottom-rect.top,SWP_NOMOVE|SWP_NOACTIVATE);
						}
					}
				}
			}
			break;

		case WM_DESTROY:
			{
				//删除字体
				DeleteObject( (HFONT)::SendMessage(hWnd,WM_GETFONT,0,0) );
				//删除菜单
				DestroyMenu(GetMenu(hWnd));

				//设置程序运行的目录跟程序文件所在目录相同
				//当我们的程序被其他程序打开时，它的工作目录和打开它的那。
				//个程序的目录是相同的。所以我们需要把目录改回来
				TCHAR AppPath[MAX_PATH];
				int nlen=GetModuleFileName(NULL,AppPath,MAX_PATH);
				while(AppPath[--nlen]!='\\');  
				AppPath[nlen]='\0';
				SetCurrentDirectory(AppPath);	
				
				//获取窗口的字符串
				int len=::SendMessage(hWnd,WM_GETTEXTLENGTH,0,0);
				TCHAR* WindowText=new TCHAR[(len+1)*sizeof(TCHAR)];
				::GetWindowText(hWnd,WindowText,len+1);  //GetWindowText会自动添加NULL结束符
				
				//打开由于保存数据文件DebugData.txt,	
				FILE* fp=fopen("DebugData.txt","wb");	
				
#ifdef	_UNICODE//如果定义了unicode，则先转为ansi再保存
				//len是源字符串的长度 len=_tcslen(WindowText)
				//(len+1)*2是源字符串占用的内存空间，包括NULL结束符
				//nChars返回转换的字符个数，不包括NULL，既nChars=_tcslen(buffer)
				//wcstombs会自动添加NULL结束符
				char* buffer = new char[(len+1)*2];
				setlocale(LC_ALL,".936");
				int nChars = wcstombs(buffer,WindowText,(len+1)*2);
				setlocale(LC_ALL,"C");
				fwrite(buffer,1,nChars,fp);
				delete buffer;
#else	
				fwrite(WindowText,1,len,fp);
#endif
				delete[] WindowText;
				fclose(fp);
			}
			break;

		case WM_CLOSE:
			if (m_IsIndex) 
				GetIndex(TRUE);
			::DestroyWindow(hWnd);
			break;

		case WM_KEYDOWN:
			{
				//select all
				if (wParam=='A' && GetKeyState(VK_CONTROL)<0)
					::SendMessage(hWnd,EM_SETSEL,0,-1);
			}
			break;

		case WM_INITMENUPOPUP:
			{
				HMENU hSubMenu=(HMENU)wParam;
				CheckMenuItem(hSubMenu,6, MF_BYCOMMAND | m_IsAutoHide ? MF_CHECKED : MF_UNCHECKED );
				CheckMenuItem(hSubMenu,7, MF_BYCOMMAND | m_IsReceive  ? MF_CHECKED : MF_UNCHECKED);
				CheckMenuItem(hSubMenu,4, MF_BYCOMMAND | m_IsAutoWidth? MF_CHECKED : MF_UNCHECKED);
				CheckMenuItem(hSubMenu,9, MF_BYCOMMAND | m_IsContinue ? MF_CHECKED : MF_UNCHECKED);
				CheckMenuItem(hSubMenu,10,MF_BYCOMMAND | m_IsName     ? MF_CHECKED : MF_UNCHECKED);
				CheckMenuItem(hSubMenu,11,MF_BYCOMMAND | m_IsIndex    ? MF_CHECKED : MF_UNCHECKED);
			}
			break;

		case WM_COMMAND:
			{
				switch(wParam)
				{
				case 3:  //清空内容
					{
						if (m_IsIndex) 
							GetIndex(1);
						::SendMessage(hWnd,WM_SETTEXT,NULL,(LPARAM)_T(""));	
					}
					break;
				case 5:  //hide window int the left of the screen
					{
						//隐藏窗口
						m_IsHide=true;
						HideWindowToLeftScreen(hWnd);

						//隐藏窗口后要禁止自动隐藏
						m_IsAutoHide=false;
						SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
					}
					break;
				case 4:  //modify the Auto Adjust window width option
					{
						m_IsAutoWidth=!m_IsAutoWidth;
						SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
					}
					break;
				case 6:  //modify the Auto hide window option
					{
						m_IsAutoHide=!m_IsAutoHide;
						if(!m_IsAutoHide) ::KillTimer(hWnd,1);
						SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
					}
					break;
				case 7:  //modify the receivd date option
					{
						if(m_IsReceive)
							::SendMessage(hWnd,EM_REPLACESEL,FALSE,(LPARAM)_T("\r\n注意：当前处于禁止接收数据状态\r\n"));	

						m_IsReceive=!m_IsReceive;
						SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
					}
					break;
				case 8:  
					::SendMessage(hWnd,WM_SETTEXT,NULL,(LPARAM)_T("帮助及更新：\r\nhttp://blog.csdn.net/jacky_qiu/article/details/5986089\r\nEmail: qiujiejia@gmail.com"));	
					break;
				case 9:  //modify the receivd date option
					{
						m_IsContinue=!m_IsContinue;
						SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
					}
					break;
				case 10:  
					{
						m_IsName=!m_IsName;
						IsName(m_IsName);
						SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
					}
					break;
				case 11:  
					{
						m_IsIndex=!m_IsIndex;
						GetIndex( m_IsIndex ? 1 : -1);
						SaveConfig(m_IsAutoWidth,m_IsAutoHide,m_IsHide,m_IsContinue,m_IsName,m_IsIndex,hWnd);
					}
					break;
				}
			}
			break;

		default:
			return ::CallWindowProc(m_OldWndProc, hWnd, message, wParam, lParam); 
		}
		return 0;
	}
};





/****************************************************************************
CEasyTrace
****************************************************************************/
class CEasyTrace
{
private:

#ifdef	_UNICODE	
	std::wostringstream m_str;
#else	
	std::ostringstream m_str;
#endif	

public:
	void add(){}		//当trace宏参数不足时会调用此函数
	void name(){}		//当trace宏参数不足时会调用此函数

	//初始化一个ostringstream对象并且添加序列号
	CEasyTrace() {	 m_str<<CTraceWnd::GetIndex()<<_T("  ");    }

	//析构时将字符串输出到Edit窗口
	~CEasyTrace()
	{
		if(!IsReceive()) return;

		m_str<<_T("\r\n");   //输出“换行”
#ifdef	_UNICODE	
		CTraceWnd::PrintString(std::wstring(m_str.str()).c_str());
#else	
		CTraceWnd::PrintString(std::string(m_str.str()).c_str());
#endif	
	}

	//输出变量名
	void name(char* pStr)
	{
		if(!CTraceWnd::IsName()) return;

		if (strchr(pStr,'\"')!=NULL) return;
#ifdef	_UNICODE	
		wchar_t* UnicodeStr=AnsiToUnicode(pStr);
		m_str<<UnicodeStr<<_T("=");
		delete[] UnicodeStr;
#else
		m_str<<pStr<<_T("=");
#endif
	}

	//输出一般类型的变量
	template <class T> void add(T t)  {	m_str<<t<<_T("\t"); }

	//输出point
	void add(POINT point) {	m_str<<(_T("("))<<point.x<<(_T(","))<<point.y<<(_T(")\t")); }

	//输出rect
	void add(RECT rect)	{ m_str<<(_T("("))<<rect.left<<(_T(","))<<rect.top<<(_T(","))<<rect.right<<(_T(","))<<rect.bottom<<(_T(")-("))<<(rect.right-rect.left)<<(_T(","))<<(rect.bottom-rect.top)<<(_T(")\t"));	}

	//输出窗口信息
	void add(HWND hWnd) 
	{
		if (!::IsWindow(hWnd))	{ m_str<<_T("Invalid Window");	return;	}
		
		TCHAR WindowText[40];	::SendMessage(hWnd,WM_GETTEXT,(WPARAM)sizeof(WindowText)/sizeof(TCHAR),(LPARAM)WindowText);	
		TCHAR ClassName[40];	::GetClassName(hWnd,ClassName,sizeof(ClassName)/sizeof(TCHAR));
		RECT  rect;				::GetWindowRect(hWnd,&rect);

		m_str<<_T("━━━━━━━━━━━━━")
			 <<_T("\r\n\tWindow Text:  \"")	 <<WindowText
			 <<_T("\"\r\n\tClass Name:  \"") <<ClassName
			 <<_T("\"\r\n\tHandle:  0x")	 <<HWND(hWnd)
			 <<_T("\r\n\trect:\t");			 
		add(rect);
		m_str<<_T("\r\n\t━━━━━━━━━━━━━━━━");	
	}
	
	//输出系统错误代码
	void TraceSysError()	{ m_str<<_T("System Error Codes:")<<GetLastError();	}

	//输出函数执行的结果
	void TraceResult(char* pStr,BOOL IsOk)  
	{
#ifdef	_UNICODE
		wchar_t* UnicodeStr=AnsiToUnicode(pStr);
		m_str<<UnicodeStr;
		delete[] UnicodeStr;
#else
		m_str<<pStr;
#endif
		m_str<<_T(" : ")<<( IsOk==TRUE ? _T(" Successful(true)") : _T("Failed(false)") ); 
	}

	//输出MFC的 CPoint CRect CString
#ifdef __AFXWIN_H__
	void add(CPoint point)	{ add((POINT)point);}
	void add(CRect rect)	{ add((RECT)rect);}
	void add(CString str)	{ add((LPTSTR)(LPCTSTR)str); }
#endif 

	//ansi 转 unicode ，用完要删除指针
	wchar_t* AnsiToUnicode(char* AnsiStr)
	{
		UINT len=strlen(AnsiStr); 
		wchar_t* UnicodeStr= new wchar_t[len+1];
		setlocale(LC_ALL,".936");
		int num=mbstowcs(UnicodeStr,AnsiStr,len+1);
		setlocale(LC_ALL,"C");
		if(-1==num)	*UnicodeStr=NULL;
		return UnicodeStr;
	}

	//输出格式化字符串，类似sprintf
	static void Tracef(LPCTSTR lpszFormat, ...)
	{
		va_list args; va_start(args, lpszFormat);	//begin
		TCHAR szBuffer[1024];
		int rel=_vsntprintf(szBuffer, sizeof(szBuffer)/sizeof(TCHAR)-1, lpszFormat, args);
		if (rel==-1) szBuffer[sizeof(szBuffer)/sizeof(TCHAR)-1]=NULL;
		va_end(args);		//end
		CEasyTrace().add(szBuffer); //输出字符串
	}

	/****************************************************************************
	设置和获取接收状态 
	-1：	获取接收状态 
	TRUE：	设置为接收状态 
	FALSE：	禁止接收。
	****************************************************************************/
	static BOOL IsReceive(BOOL var=-1)
	{
		static BOOL state=true;
		if(var!=-1) state=var;
		return state;
	}

};


#endif // #define TRACE_WINDOW
#endif // #define _EASY_TRACE_H_
