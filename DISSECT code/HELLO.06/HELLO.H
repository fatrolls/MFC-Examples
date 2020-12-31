//--------------------------------------------------------------------
//              MFC 4.0  Hello Sample Program
//        Copyright (c) 1996   Top Studio * J.J.Hou
//
// 檔名      : hello.h
// 作者      : 侯俊傑
// 編譯聯結  : 請參考 hello.mak
//
// 宣告 Hello 程式的兩個類別 : CMyWinApp 和 CMyFrameWnd
//--------------------------------------------------------------------

class CMyWinApp : public CWinApp
{
public:
   virtual BOOL InitInstance();       // 每一個應用程式都應該改寫此函式
   virtual BOOL OnIdle(LONG lCount);  // OnIdle 用來處理閒置時間（idle time）
};

//--------------------------------------------------------------------
class CMyFrameWnd : public CFrameWnd
{
public:
   CMyFrameWnd();            // constructor
   afx_msg void OnPaint();   // for WM_PAINT
   afx_msg void OnAbout();   // for WM_COMMAND (IDM_ABOUT)
   void IdleTimeHandler(LONG lCount);  // we want it call by CMyWinApp::OnIdle

private:
   DECLARE_MESSAGE_MAP()     // Declare Message Map
   static VOID CALLBACK LineDDACallback(int,int,LPARAM);
   // 注意: callback 函式必須是 "static"，才能去除隱藏的 'this' 指標。
};
//--------------------------------------------------------------------

