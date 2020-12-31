#include "stdafx.h"
#include "App.h"
#include "MessageBoxDlg.h"
#include "MessageBoxX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMessageBoxDlg::CMessageBoxDlg(CWnd* pParent)	: CDialog(CMessageBoxDlg::IDD, pParent),
	                                              m_sCaption(_T("A Sample CMessageBoxX")),
	                                              m_bCheckBox(FALSE),
	                                              m_bCheckBoxInitialState(FALSE),
	                                              m_sCheckBoxText(_T("Don't Show me again!")),
	                                              m_bDisable(FALSE),
	                                              m_bRightAlign(FALSE),
	                                              m_sText(_T("Do you think that CMessageBoxX will make your development life easier?")),
	                                              m_bTimeout(FALSE),
	                                              m_bModifyCaptionForDisabled(FALSE),
	                                              m_bModifyCaptionForTimer(FALSE),
	                                              m_bResetTimerOnUserActivity(FALSE),
	                                              m_bHTML(FALSE),
	                                              m_sHTMLText(_T("<body margintop=0 marginbottom=0 marginleft=0 marginright=0><p><i>QHTM</i> and <b>CMessageBoxEx</b> in action together</p><hr><p>For more information and updates why not visit the web site <a href=\"http://www.naughter.com\">http://www.naughter.com</a> or drop me a note at <a href=\"mailto:pjna@naughter.com\">pjna@naughter.com</a></p></body>")),
	                                              m_bSelectableText(FALSE),
	                                              m_bAnimatedCaption(FALSE),
	                                              m_bAnimatedText(FALSE),
	                                              m_hIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME)),
	                                              m_bUserIcon(FALSE)
{
}

void CMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
  //Let the base class do its thing
	CDialog::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_CAPTION, m_sCaption);
	DDX_Check(pDX, IDC_CHECKBOX, m_bCheckBox);
	DDX_Check(pDX, IDC_CHECKBOX_INITIAL_STATE, m_bCheckBoxInitialState);
	DDX_Text(pDX, IDC_CHECKBOX_TEXT, m_sCheckBoxText);
	DDX_Check(pDX, IDC_DISABLE, m_bDisable);
	DDX_Check(pDX, IDC_RIGHTALIGN, m_bRightAlign);
	DDX_Text(pDX, IDC_TEXT, m_sText);
	DDX_Check(pDX, IDC_TIMEOUT, m_bTimeout);
	DDX_Check(pDX, IDC_MODIFY_CAPTION_FOR_DISABLED, m_bModifyCaptionForDisabled);
	DDX_Check(pDX, IDC_MODIFY_CAPTION_FOR_TIMER, m_bModifyCaptionForTimer);
	DDX_Check(pDX, IDC_RESET_TIMER_ON_USER_ACTIVITY, m_bResetTimerOnUserActivity);
	DDX_Check(pDX, IDC_HTML, m_bHTML);
	DDX_Text(pDX, IDC_HTMLTEXT, m_sHTMLText);
	DDX_Check(pDX, IDC_SELECTABLETEXT, m_bSelectableText);
	DDX_Text(pDX, IDC_CAPTION1, m_sCaption1);
	DDX_Text(pDX, IDC_CAPTION2, m_sCaption2);
	DDX_Check(pDX, IDC_ANIMATEDCAPTION, m_bAnimatedCaption);
	DDX_Check(pDX, IDC_ANIMATEDTEXT, m_bAnimatedText);
	DDX_Check(pDX, IDC_USERICON, m_bUserIcon);
}

BEGIN_MESSAGE_MAP(CMessageBoxDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_HTML, OnHtml)
END_MESSAGE_MAP()

BOOL CMessageBoxDlg::OnInitDialog()
{
  //Let the base class do its thing
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);	 //Set big icon
	SetIcon(m_hIcon, FALSE); //Set small icon

#ifndef CMESSAGEBOXX_HTML_SUPPORT
  GetDlgItem(IDC_HTML)->EnableWindow(FALSE);
  GetDlgItem(IDC_HTMLTEXT)->EnableWindow(FALSE);
#endif

	OnHtml();

	return TRUE;  //return TRUE unless you set the focus to a control
}

void CMessageBoxDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); //device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		//Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		//Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
		CDialog::OnPaint();
}

HCURSOR CMessageBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMessageBoxDlg::OnButton1() 
{
  if (UpdateData(TRUE))
  {
    CMessageBoxX msgbox(m_sText, m_sCaption, MB_YESNO);
    msgbox.SetCaption(m_sCaption);
    msgbox.SetText(m_sText);
    msgbox.SetSelectableText(m_bSelectableText);
    if (m_bCheckBox)
      msgbox.SetCheckBox(m_bCheckBoxInitialState, m_sCheckBoxText);

    if (m_bTimeout)
      msgbox.SetTimeout(20, IDNO, m_bModifyCaptionForTimer, m_bResetTimerOnUserActivity);

    msgbox.SetRightAlignButtons(m_bRightAlign);

    msgbox.SetModifiedButtonCaption(0, m_sCaption1);
    msgbox.SetModifiedButtonCaption(1, m_sCaption2);

  #ifdef CMESSAGEBOXX_HTML_SUPPORT
    msgbox.SetHTML(m_bHTML);
    msgbox.SetHTMLText(m_sHTMLText);
  #endif

  	if (m_bDisable)
      msgbox.SetDisabledButton(5, IDNO, m_bModifyCaptionForDisabled);

    CStringArray animatedText;
    if (m_bAnimatedText)
    {
      animatedText.Add(_T("Mary had a little lamb,                           ")); //Note for layout reasons, we need to ensure that the first item is the largest
      animatedText.Add(_T("Little lamb, little lamb,"));
      animatedText.Add(_T("Mary had a little lamb,"));
      animatedText.Add(_T("Its fleece was white as snow"));
      animatedText.Add(_T("And everywhere that Mary went,"));
      animatedText.Add(_T("Mary went, Mary went,"));
      animatedText.Add(_T("Everywhere that Mary went"));
      animatedText.Add(_T("The lamb was sure to go"));
      animatedText.Add(_T("It followed her to school one day"));
      animatedText.Add(_T("School one day, school one day"));
      animatedText.Add(_T("It followed her to school one day"));
      animatedText.Add(_T("Which was against the rules."));
      animatedText.Add(_T("It made the children laugh and play,"));
      animatedText.Add(_T("Laugh and play, laugh and play,"));
      animatedText.Add(_T("It made the children laugh and play"));
      animatedText.Add(_T("To see a lamb at school"));
      animatedText.Add(_T("And so the teacher turned it out,"));
      animatedText.Add(_T("Turned it out, turned it out,"));
      animatedText.Add(_T("And so the teacher turned it out,"));
      animatedText.Add(_T("But still it lingered near"));
      animatedText.Add(_T("And waited patiently about,"));
      animatedText.Add(_T("Patiently about, patiently about,"));
      animatedText.Add(_T("And waited patiently about"));
      animatedText.Add(_T("Till Mary did appear"));
      animatedText.Add(_T("Why does the lamb love Mary so?"));
      animatedText.Add(_T("Love Mary so? Love Mary so?"));
      animatedText.Add(_T("Why does the lamb love Mary so?"));
      animatedText.Add(_T("The eager children cry"));
      animatedText.Add(_T("Why, Mary loves the lamb, you know."));
      animatedText.Add(_T("Loves the lamb, you know, loves the lamb, you know"));
      animatedText.Add(_T("Why, Mary loves the lamb, you know."));
      animatedText.Add(_T("The teacher did reply"));
      msgbox.SetAnimatedText(800, &animatedText, TRUE);
    }

    CStringArray animatedCaption;
    if (m_bAnimatedCaption)
    {
      animatedCaption.Add(_T("Hey diddle diddle,"));
      animatedCaption.Add(_T("the cat and the fiddle,"));
      animatedCaption.Add(_T("The cow jumped over the moon,"));
      animatedCaption.Add(_T("The little dog laughed to see such sport,"));
      animatedCaption.Add(_T("And the dish ran away with the spoon."));
      msgbox.SetAnimatedCaption(1800, &animatedCaption, TRUE);
    }
    
    if (m_bUserIcon)
      msgbox.SetUserIcon(IDR_MAINFRAME);

    INT_PTR nResponse = msgbox.DoModal();
    nResponse;
    CButton* pwndCheckBoxState = static_cast<CButton*>(GetDlgItem(IDC_CHECKBOX_INITIAL_STATE));
    pwndCheckBoxState->SetCheck(msgbox.GetCheckBoxState());
  }
}

void CMessageBoxDlg::OnHtml() 
{
  CDataExchange DX(this, TRUE);
  DDX_Check(&DX, IDC_HTML, m_bHTML);  	
  GetDlgItem(IDC_HTMLTEXT)->EnableWindow(m_bHTML);
}
