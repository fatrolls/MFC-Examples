#include <windows.h>
#include <windowsx.h>
#include <dbt.h>
#include <stdio.h>

HWND hwndList;
HINSTANCE hInst;

LRESULT WINAPI MainWndProc(HWND, UINT, WPARAM, LPARAM);
void log(const char *ctl, ...);

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
	{                             // WinMain
	HWND hwnd;
	MSG msg;
	static char *szAppName = "DEVCHANGE";
	
	hInst = hInstance;
	if (!hPrev)
		{                          // register window class
		WNDCLASS wc;
		wc.style = 0;
		wc.lpfnWndProc = MainWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = szAppName;
		if (!RegisterClass(&wc))
			return 0;
	}                          // register window class
	
	hwnd = CreateWindow(szAppName, "Plug and Play Test Program", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	
	if (!hwnd)
		return 0;
	
	ShowWindow(hwnd, nShow);
	
	while (GetMessage(&msg, 0, 0, 0))
		{                          // process messages
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}                          // process messages
	
	return msg.wParam;
	}                             // WinMain

LRESULT WINAPI MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{								// MainWndProc
	switch (msg)
		{							// process message
	
	case WM_CREATE:
		{							// WM_CREATE
		hwndList = CreateWindow("LISTBOX", "", WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,
			0, 0, 0, 0, hwnd, NULL, hInst, NULL);
		if (!hwndList)
			return -1;

		return 0;
		}							// WM_CREATE

	case WM_SIZE:
		if (hwndList)
			{						// resize list control
			RECT rc;
			GetClientRect(hwnd, &rc);
			MoveWindow(hwndList, 0, 0, rc.right, rc.bottom, TRUE);
			}						// resize list control
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_DEVICECHANGE:
		{							// WM_DEVICECHANGE
		static struct {UINT msg; char *name;} dbt[] =
			{{DBT_DEVNODES_CHANGED, "DBT_DEVNODES_CHANGED"}
			,{DBT_QUERYCHANGECONFIG, "DBT_QUERYCHANGECONFIG"}
			,{DBT_CONFIGCHANGED, "DBT_CONFIGCHANGED"}
			,{DBT_CONFIGCHANGECANCELED, "DBT_CONFIGCHANGECANCELED"}
			,{DBT_MONITORCHANGE, "DBT_MONITORCHANGE"}
			,{DBT_DEVICEARRIVAL, "DBT_DEVICEARRIVAL"}
			,{DBT_DEVICEQUERYREMOVE, "DBT_DEVICEQUERYREMOVE"}
			,{DBT_DEVICEQUERYREMOVEFAILED, "DBT_DEVICEQUERYREMOVEFAILED"}
			,{DBT_DEVICEREMOVEPENDING, "DBT_DEVICEREMOVEPENDING"}
			,{DBT_DEVICEREMOVECOMPLETE, "DBT_DEVICEREMOVECOMPLETE"}
			,{DBT_DEVICETYPESPECIFIC, "DBT_DEVICETYPESPECIFIC"}};
		int i;

		for (i = 0; i < arraysize(dbt); ++i)
			if (wParam == dbt[i].msg)
				break;
		if (i >= arraysize(dbt))
			{						// unknown msg
			log("WM_DEVICECHANGE %8.8lX, %8.8lX", wParam, lParam);
			return 0;
			}						// unknown msg
		
		if (wParam >= DBT_DEVICEARRIVAL && wParam <= DBT_DEVICETYPESPECIFIC)
			{						// device-related message
			static char *typenames[] =
				{"OEM", "DEVNODE", "VOLUME", "PORT", "NET"};
			struct _DEV_BROADCAST_HEADER *p = (struct _DEV_BROADCAST_HEADER *) lParam;

			log("WM_DEVICECHANGE %s, type %s", dbt[i].name, typenames[p->dbcd_devicetype]);

			switch (p->dbcd_devicetype)
				{					// select on device type code

			case DBT_DEVTYP_OEM:
				#define tp ((struct _DEV_BROADCAST_OEM*) p)
				log("  identifier %8.8lX, suppfunc %8.8lX",
					 tp->dbco_identifier, tp->dbco_suppfunc);
				#undef tp
				break;

			case DBT_DEVTYP_DEVNODE:
				{					// DBT_DEVTYP_DEVNODE
				#define tp ((struct _DEV_BROADCAST_DEVNODE*) p)
				DWORD devnode = tp->dbcd_devnode;
				HKEY devkey;
				char keyname[256];
				DWORD lkeyname;
		
				_snprintf(keyname, sizeof(keyname), "Config Manager\\Enum\\%8.8lX", devnode);
				RegOpenKeyEx(HKEY_DYN_DATA, keyname, 0, KEY_READ, &devkey);
				lkeyname = sizeof(keyname);
				RegQueryValueEx(devkey, "HardwareKey", NULL, NULL, keyname, &lkeyname);

				log("  devnode %8.8lX (%s)", devnode, keyname);
				if (devkey)
					RegCloseKey(devkey);
				#undef tp
				break;
				}					// DBT_DEVTYP_DEVNODE

			case DBT_DEVTYP_VOLUME:
				{					// DBT_DEVTYP_VOLUME
				int unit;
				DWORD unitmask;
				char flags[80] = "";
				#define tp ((struct _DEV_BROADCAST_VOLUME*) p)

				for (unit = -1, unitmask = tp->dbcv_unitmask; unitmask; ++unit, unitmask >>= 1)
					;				// determine unit number
				
				if (tp->dbcv_flags & DBTF_MEDIA)
					strcpy(flags, " MEDIA");
				if (tp->dbcv_flags & DBTF_NET)
					strcat(flags, " NET");
				
				log("  drive %c:, flags %s", 'A' + unit, flags);
				#undef tp
				break;
				}					// DBT_DEVTYP_VOLUME

			case DBT_DEVTYP_PORT:
				#define tp ((struct _DEV_BROADCAST_PORT*) p)
				log("  name %s", tp->dbcp_name);
				#undef tp
				break;

			case DBT_DEVTYP_NET:
				{					// DBT_DEVTYP_NET
				char *resource;
				#define tp ((struct _DEV_BROADCAST_NET*) p)
				switch (tp->dbcn_resource)
					{				// get resource code
				case DBTF_RESOURCE:
					resource = "RESOURCE";
					break;
				case DBTF_XPORT:
					resource = "XPORT";
					break;
				case DBTF_SLOWNET:
					resource = "SLOWNET";
					break;
				default:
					resource = "unknown";
					break;
					}				// get resource code
				log("  resource %d (%s), flags %8.8lX",
					 tp->dbcn_resource, resource, tp->dbcn_flags);
				#undef tp
				break;
				}					// DBT_DEVTYP_NET

			default:
				log("WM_DEVICECHANGE %s, type %X", dbt[i].name, p->dbcd_devicetype);
				break;
				}					// select on device type code
			}						// device-related message
		else
			log("WM_DEVICECHANGE %s, %8.8lX", dbt[i].name, lParam);
		return 0;
		}							// WM_DEVICECHANGE

		}							// process message
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
	}								// MainWndProc
	
void log(const char *ctl, ...)
	{								// log
	char buffer[256];
	int index;
	if (!hwndList)
		return;
	wvsprintf(buffer, ctl, (va_list)(&ctl+1));
	if ((index = (int) SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)(LPSTR) buffer)) == LB_ERRSPACE)
		{							// out of space
		SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
		index = (int) SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)(LPSTR) buffer);
		}							// out of space
	SendMessage(hwndList, LB_SETTOPINDEX, index, 0);
	}								// log
	
