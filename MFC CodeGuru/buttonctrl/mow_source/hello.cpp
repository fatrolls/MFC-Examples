// hello.cpp
// Date : April 4, 1998
// Author: SuhaS

#include "hello.h" 

// Declare the application class

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

// Create an instance of the application class
CHelloApp HelloApp;

// Declare the main window class
class CHelloWindow : public CFrameWnd
{
	CStatic* cs;
	CFont	 lblFont;
public:
	CHelloWindow();
	void CreateOptionButtons();
	void CreateDocumentation();
	~CHelloWindow();
};

// The InitInstance function is called each 
// time the application first executes
BOOL CHelloApp::InitInstance()
{
	m_pMainWnd = new CHelloWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;

}


// The constructor for the window class
CHelloWindow::CHelloWindow()
{


	const char *strWndClass = AfxRegisterWndClass (
	CS_HREDRAW | CS_VREDRAW,
	NULL,
	(HBRUSH)(COLOR_GRAYTEXT+1),
	NULL
	);

	this->Create(strWndClass, "Motif Option Menu Class...Suhas Kelkar",  
			WS_POPUP | WS_CAPTION | WS_OVERLAPPEDWINDOW,
			CRect(CPoint(10,10),CSize(500,600)), NULL );
	this->CenterWindow();		
	this->SetFocus();

	// Lets put some informative static label on the window
	CreateDocumentation();
	
	CreateOptionButtons();
	
}


// Create Option Butttons
void CHelloWindow::CreateOptionButtons()
{

	CVxPushButton *a1;
	CVxOptPicker *a;
	a = new CVxOptPicker(100, 50, 4, 1);
	a->Create("Ini", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_NOTIFY, 
				CRect(CPoint(100,500),CSize(175,50)), this, 11002);
	
	a1 = new CVxPushButton();
	a1->Create("Push 1", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
						 CRect(CPoint(3,3),CSize(100,50)), a->m_PopupWnd, 1001);
	//b1->SetBitmap2(IDB_BITMAP1);

	
	a->m_CurText   = "Push 1" ;
	a->m_CurBitmap = a1->GetBitmap2() ;
	a->m_CurButton = (CWnd *)a1 ;

	a1 = new CVxPushButton();
	a1->Create("Push 2", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
				CRect(CPoint(3,56),CSize(100,50)), a->m_PopupWnd, 1002);

	
	a1 = new CVxPushButton();
	a1->Create("Push 3", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
				CRect(CPoint(3,109),CSize(100,50)), a->m_PopupWnd, 1003);

	
	a1 = new CVxPushButton();
	a1->Create("Push 4", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
				CRect(CPoint(3,162),CSize(100,50)), a->m_PopupWnd, 1002);



	CVxPushButton *b1;
	CVxOptPicker *b;
	b = new CVxOptPicker(50, 50, 3, 3);
	// BS_NOTIFY is essential in order to receive any reflected
	// notification messages from the parent window
	// The size of button passed in here is irrelavent since we
	// use the width and height set in the Constructor function
	// called above due to the new call...
	b->Create("Ini", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_NOTIFY, 
				CRect(CPoint(280,500),CSize(175,50)), this, 11002);
	
	b1 = new CVxPushButton();
	b1->Create("Hi 1", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
						 CRect(CPoint(3,3),CSize(50,50)), b->m_PopupWnd, 11001);
	b1->SetBitmap2(IDB_BITMAP1);

	
	b->m_CurText   = "Hi 12" ;
	b->m_CurBitmap = b1->GetBitmap2() ;
	b->m_CurButton = (CWnd *)b1 ;

	b1 = new CVxPushButton();
	b1->Create("Hi 2", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
				CRect(CPoint(3,56),CSize(50,50)), b->m_PopupWnd, 11002);
	b1->SetBitmap2(IDB_BITMAP2);

	
	b1 = new CVxPushButton();
	b1->Create("Hi 3", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
				 CRect(CPoint(3,109),CSize(50,50)), b->m_PopupWnd, 11003);

	b1 = new CVxPushButton();
	b1->Create("Hi 1", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
						 CRect(CPoint(56,3),CSize(50,50)), b->m_PopupWnd, 11004);
	b1->SetBitmap2(IDB_BITMAP1);

	b1 = new CVxPushButton();
	b1->Create("Hi 2", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
				CRect(CPoint(56,56),CSize(50,50)), b->m_PopupWnd, 11005);
	b1->SetBitmap2(IDB_BITMAP2);

	b1 = new CVxPushButton();
	b1->Create("Hi 1", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
						 CRect(CPoint(109,3),CSize(50,50)), b->m_PopupWnd, 11006);
	b1->SetBitmap2(IDB_BITMAP1);

	CEdit *ed;
	ed = new CEdit();
	ed->Create(
                WS_CHILD | WS_VISIBLE | ES_LEFT |
                WS_BORDER | WS_TABSTOP | ES_MULTILINE | ES_AUTOHSCROLL,
                CRect(CPoint(56, 109), CSize(103, 50)),
                b->m_PopupWnd,
                1007);

    ed->SetWindowText("COOL !");

}

// Documentation label
void CHelloWindow::CreateDocumentation()
{
	lblFont.CreateFont(16,0,0,0,400,0,0,0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					"helvetica");

	// Here lets create information text
	CString info;

	info  = "                                            Motif Option Widget\n";
	info += "                                              By, Suhas Kelkar" ;
	info += "\n\n This control class is designed for use just like \"MOTIF";
	info += " Option Menu Widget\".\n";
	info += "\n I decided to write this special widget because of following special\n";
	info += " characteristics that it provides,\n\n";

	info += "   o Ability to have multiple columns \n";
	info += "   o Ability to put actual control classes (such as Push buttons) on the popup\n";
	info += "     window. This becomes important if you want to generate a push button \n";
	info += "     callback after the selection is made, just the MOTIF does it.\n";
	info += "   o Last but not least to make it behave exactly like MOTIF option button\n";
	info += "     This was particularly important for me since that meant minimal changes to\n";
	info += "     my source code.\n\n";

	info += " Since MOTIF Option Menu Widget can be customized in many different ways\n";
	info += " I leave it up to you to customize it as per your needs. \n\n";
	info += " There are two main classes,\n";
	info += "   o \"COptPicker\" class : This is where you can customize this widget to\n";
	info += "     respond to say right mouse button click etc. Also this is where you \n";
	info += "     can change the arrow to something else of your choice\n";

	info += "   o \"COptPopup\" class : This is where you can customize the popup window\n\n";
	
	info += " ( Some snippets of code in this sample were taken from some other samples on\n";
	info += "   this site. If you have any questions send me an email at sak@vx.com )\n\n";
	info += "                                        Have A Nice Day If You Can !";


	cs = new CStatic();
	cs->Create(	info, 
				WS_CHILD|WS_VISIBLE|WS_BORDER|SS_LEFT,
				CRect(10,10,480,480),
				this);

	cs->SetFont(&lblFont);


}


// the destructor

CHelloWindow::~CHelloWindow()
{
	delete cs;
}
