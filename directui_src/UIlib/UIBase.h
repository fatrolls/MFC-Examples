#if !defined(AFX_UIBASE_H__20050509_3DFB_5C7A_C897_0080AD509054__INCLUDED_)
#define AFX_UIBASE_H__20050509_3DFB_5C7A_C897_0080AD509054__INCLUDED_

#pragma once


/////////////////////////////////////////////////////////////////////////////////////
//

class CPaintManagerUI;


#define UI_WNDSTYLE_CONTAINER  (0)
#define UI_WNDSTYLE_FRAME      (WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_CHILD      (WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define UI_WNDSTYLE_DIALOG     (WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_WNDSTYLE_EX_FRAME   (WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG  (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

#define UI_CLASSSTYLE_CONTAINER  (0)
#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)


/////////////////////////////////////////////////////////////////////////////////////
//

#define ASSERT(expr)  _ASSERTE(expr)

#ifdef _DEBUG
   #define TRACE __Trace
   #define TRACEMSG __TraceMsg
#else
   #define TRACE
   #define TRACEMSG _T("")
#endif

void UILIB_API __Trace(LPCTSTR pstrFormat, ...);
LPCTSTR __TraceMsg(UINT uMsg);


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRect : public tagRECT
{
public:
   CRect();
   CRect(const RECT& src);
   CRect(int iLeft, int iTop, int iRight, int iBottom);

   int GetWidth() const;
   int GetHeight() const;
   void Empty();
   void Join(const RECT& rc);
   void ResetOffset();
   void Normalize();
   void Offset(int cx, int cy);
   void Inflate(int cx, int cy);
   void Deflate(int cx, int cy);
   void Union(CRect& rc);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CSize : public tagSIZE
{
public:
   CSize();
   CSize(const SIZE& src);
   CSize(const RECT rc);
   CSize(int cx, int cy);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CPoint : public tagPOINT
{
public:
   CPoint();
   CPoint(const POINT& src);
   CPoint(int x, int y);
   CPoint(LPARAM lParam);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdPtrArray
{
public:
   CStdPtrArray(int iPreallocSize = 0);
   virtual ~CStdPtrArray();

   void Empty();
   void Resize(int iSize);
   bool IsEmpty() const;
   int Find(LPVOID iIndex) const;
   bool Add(LPVOID pData);
   bool SetAt(int iIndex, LPVOID pData);
   bool InsertAt(int iIndex, LPVOID pData);
   bool Remove(int iIndex);
   int GetSize() const;
   LPVOID* GetData();

   LPVOID GetAt(int iIndex) const;
   LPVOID operator[] (int nIndex) const;

protected:
   LPVOID* m_ppVoid;
   int m_nCount;
   int m_nAllocated;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdValArray
{
public:
   CStdValArray(int iElementSize, int iPreallocSize = 0);
   virtual ~CStdValArray();

   void Empty();
   bool IsEmpty() const;
   bool Add(LPCVOID pData);
   bool Remove(int iIndex);
   int GetSize() const;
   LPVOID GetData();

   LPVOID GetAt(int iIndex) const;
   LPVOID operator[] (int nIndex) const;

protected:
   LPBYTE m_pVoid;
   int m_iElementSize;
   int m_nCount;
   int m_nAllocated;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CWindowWnd
{
public:
   CWindowWnd();

   HWND GetHWND() const;
   operator HWND() const;

   bool RegisterWindowClass();
   bool RegisterSuperclass();

   HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
   HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
   HWND Subclass(HWND hWnd);
   void Unsubclass();
   void ShowWindow(bool bShow = true, bool bTakeFocus = true);
   bool ShowModal();
   void Close();
   void CenterWindow();
   void SetIcon(UINT nRes);

protected:
   virtual LPCTSTR GetWindowClassName() const = 0;
   virtual LPCTSTR GetSuperClassName() const;
   virtual UINT GetClassStyle() const;

   LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
   LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
   void ResizeClient(int cx = -1, int cy = -1);

   virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
   virtual void OnFinalMessage(HWND hWnd);

   static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
   static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
   HWND m_hWnd;
   WNDPROC m_OldWndProc;
   bool m_bSubclassed;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CWaitCursor
{
public:
   CWaitCursor();
   ~CWaitCursor();

protected:
   HCURSOR m_hOrigCursor;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdString
{
public:
   enum { MAX_LOCAL_STRING_LEN = 63 };

   CStdString();
   CStdString(const TCHAR ch);
   CStdString(const CStdString& src);
   CStdString(LPCTSTR lpsz, int nLen = -1);
   virtual ~CStdString();

   static CStdString RES(UINT nRes);

   void Empty();
   int GetLength() const;
   bool IsEmpty() const;
   TCHAR GetAt(int nIndex) const;
   void Append(LPCTSTR pstr);
   void Assign(LPCTSTR pstr, int nLength = -1);
   LPCTSTR GetData();
   
   void SetAt(int nIndex, TCHAR ch);
   operator LPCTSTR() const;

   TCHAR operator[] (int nIndex) const;
   const CStdString& operator=(const CStdString& src);
   const CStdString& operator=(const TCHAR ch);
   const CStdString& operator=(LPCTSTR pstr);
#ifndef _UNICODE
   const CStdString& CStdString::operator=(LPCWSTR lpwStr);
#endif
   CStdString operator+(const CStdString& src);
   CStdString operator+(LPCTSTR pstr);
   const CStdString& operator+=(const CStdString& src);
   const CStdString& operator+=(LPCTSTR pstr);
   const CStdString& operator+=(const TCHAR ch);

   bool operator == (LPCTSTR str) const;
   bool operator != (LPCTSTR str) const;
   bool operator <= (LPCTSTR str) const;
   bool operator <  (LPCTSTR str) const;
   bool operator >= (LPCTSTR str) const;
   bool operator >  (LPCTSTR str) const;

   int Compare(LPCTSTR pstr) const;
   int CompareNoCase(LPCTSTR pstr) const;
   
   void MakeUpper();
   void MakeLower();

   CStdString Left(int nLength) const;
   CStdString Mid(int iPos, int nLength = -1) const;
   CStdString Right(int nLength) const;

   int Find(TCHAR ch, int iPos = 0) const;
   int Find(LPCTSTR pstr, int iPos = 0) const;
   int ReverseFind(TCHAR ch) const;
   int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);
   
   void ProcessResourceTokens();
   int __cdecl Format(LPCTSTR pstrFormat, ...);

protected:
   LPTSTR m_pstr;
   TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};


#endif // !defined(AFX_UIBASE_H__20050509_3DFB_5C7A_C897_0080AD509054__INCLUDED_)
