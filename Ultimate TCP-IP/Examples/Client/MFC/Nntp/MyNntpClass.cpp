// MyNntpClass.cpp: implementation of the MyNntpClass class.
//
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NNTPclient.h"
#include "NNTPclientDlg.h"
#include "MyNntpClass.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyNntpClass::CMyNntpClass()
{
	m_pPrntDlg = NULL;
}

CMyNntpClass::~CMyNntpClass()
{

}
/***************************************************
IsAborted
    This virtual function is called during time consuming
	operations to check if we want to abort operatin


	For this sample we will return the inverse of the 
	aborted button.


Params
    none
Return
    TRUE	- abort operation
	FALSE	- continue
****************************************************/
BOOL CMyNntpClass::IsAborted() {
	return m_pPrntDlg->m_bisAborted;
}
/***************************************************

  Set the parent window to bo our dialog window
  we will use deligation to assign who is the parent window of 
  this class object so we can get access to the parents memeber controls
  
***************************************************/
void CMyNntpClass::SetParentWindow( CNNTPclientDlg *parentDlg){

	m_pPrntDlg = parentDlg;

}

/***************************************************
  when the command
  LIST GROUPS 
  is issued. Each goup title received will passed to this 
  call back function

  In this example we will update the News groups list 
  as soon as we receive them.

  If we need to abort this function we would return 
  FALSE
***************************************************/
int CMyNntpClass::OnNGetNewsGroupList(LPCSTR newsGroupTitle) {

    m_pPrntDlg->m_listGroup.AddString (WC(newsGroupTitle));
	m_pPrntDlg->m_staticWindow.SetWindowText(WC(newsGroupTitle));
	return TRUE;
}
/***************************************************
	OnNGetArticleList
	is called when the user calls NGetArticleList.
	
	For each article received we will receive:
		  
	LPCSTR artId - The article ID
	LPCSTR subject - The string of the article subject
	LPCSTR author - the name or/and email of the authur the article
	LPCSTR date - a string containing the date of the article
	LPCSTR refrence - the other articles refrenced in this article
	LPCSTR BytesCount - number of bytes in the artilce
	LPCSTR NumberOfLines - number of lines in the arrticle
Return:
  If we want to abort this process we would return FALSE
  otherwise, true is returned.

****************************************************/
int  CMyNntpClass::OnNGetArticleList(LPCSTR artId, LPCSTR subject,LPCSTR author,LPCSTR date, LPCSTR refrence,LPCSTR BytesCount, LPCSTR NumberOfLines, LPCSTR /* xrefs */ ){
	
	CString statusMessage;
	CUT_HeaderEncoding he;
	char szCharSet[80];
	// v4.2 Wonder if decoding should be built into the nntp classes...
	// update the parent class memebers so they can be used in the OnInsertItem, decoding on the fly
	m_pPrntDlg->m_strSubject = he.Decode(subject, szCharSet);
	m_pPrntDlg->m_strAuthor = he.Decode(author, szCharSet);
	m_pPrntDlg->m_strDate = date;
	m_pPrntDlg->m_strRefrence = refrence; 
	m_pPrntDlg->m_strBytesCount = BytesCount ;
	m_pPrntDlg->m_strNumberOfLines  = NumberOfLines;
	m_pPrntDlg->m_articlesList.InsertItem (m_pPrntDlg->m_icounter, WC(artId));
	
	// update the status control
	statusMessage = _T("Getting Article ") ;
	statusMessage+= artId;
	m_pPrntDlg->m_staticWindow.SetWindowText(statusMessage);
	m_pPrntDlg->m_icounter ++;	

	return !(m_pPrntDlg->m_bisAborted);

}