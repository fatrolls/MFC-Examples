// InstForm.cpp: implementation of the InstForm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "InstForm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInstForm::CInstForm()
{
	CString strURL;
	strURL = AfxGetApp()->GetProfileString("URLS", "InstructorForm", NULL);

	if (strURL.IsEmpty())
	{
		AfxMessageBox("No URL has been Specified \nfor Instructor Form.\nUse View Options to set it");
	}
	SetURL(strURL);
}

CInstForm::~CInstForm()
{
	m_pInst_Id->Release();
	m_pInst_Name->Release();
	m_pInst_Room->Release();
}


void CInstForm::OnLoad(IHTMLElementCollection * pCollection)
{
	CHTMLForm::OnLoad(pCollection);

	m_pInst_Id = GetInputElement("Inst_Id");
	m_pInst_Name = GetInputElement("Inst_Name");
	m_pInst_Room = GetInputElement("Inst_Room");
	
	m_InstSet.Open();
	m_InstSet.MoveFirst();
	DisplayData();

}

void CInstForm::DisplayData()
{
	m_pInst_Id->put_value(m_InstSet.m_InstructorID.AllocSysString());
	m_pInst_Name->put_value(m_InstSet.m_Name.AllocSysString());
	m_pInst_Room->put_value(m_InstSet.m_RoomNo.AllocSysString());
}



void CInstForm::ExecuteCmd(LPCTSTR lpszCmd)
{
	//Parse and execute
	//Not exactly a good way but for our purposes it is sufficient
	if (!strcmp(lpszCmd, "MoveFirst/"))
		m_InstSet.MoveFirst();
	else if (!strcmp(lpszCmd, "Previous/"))
	{
		if (!m_InstSet.IsBOF())
			m_InstSet.MovePrev();
	}
	else if (!strcmp(lpszCmd, "Next/"))
		{
			if (!m_InstSet.IsEOF())
				m_InstSet.MoveNext();
		}
	else if (!strcmp(lpszCmd, "Last/"))
		m_InstSet.MoveLast();
	
	DisplayData();
}
