#if !defined(AFX_LSPDLG_H__A2A76D0E_1F8D_4564_89FF_E4AEC6BD056B__INCLUDED_)
#define AFX_LSPDLG_H__A2A76D0E_1F8D_4564_89FF_E4AEC6BD056B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LSPDlg.h : header file
//
#include "RootDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CLSPDlg dialog
enum Message
{
	WH_SEND = WM_USER+2000
};

struct LSPMessage
{
	WCHAR wszExeName[MAX_PATH];
    WCHAR wszFunction[MAX_PATH];
	WCHAR wszMessage[4096];
    WCHAR wszParam1[MAX_PATH];
    WCHAR wszParam2[MAX_PATH];
    WCHAR wszParam3[MAX_PATH];
    WCHAR wszParam4[MAX_PATH];
    WCHAR wszParam5[MAX_PATH];
    WCHAR wszParam6[MAX_PATH];
    WCHAR wszParam7[MAX_PATH];
    WCHAR wszParam8[MAX_PATH];
    WCHAR wszParam9[MAX_PATH];
    WCHAR wszParam10[MAX_PATH];
    int m_iParamCount;
	
	LSPMessage(char* szFunction, char* szMessage, char* szParams)
	{
        Init();
		//可执行文件名称
		char szExe[MAX_PATH] = {0};
		GetModuleFileNameA(NULL, szExe, MAX_PATH);
		int nLen = strlen(szExe);
		PWCHAR pOut = new WCHAR[nLen+1];
	    ZeroMemory(pOut, (nLen+1)*2);
	    MultiByteToWideChar(CP_ACP, MB_COMPOSITE, szExe, nLen, pOut, nLen);
		memcpy(wszExeName, pOut, nLen*2);
		delete [] pOut;
		//函数名称
		if (szFunction != NULL && strlen(szFunction) > 0)
		{
			nLen = strlen(szFunction);
            pOut = new WCHAR[nLen+1];
	        ZeroMemory(pOut, (nLen+1)*2);
	        MultiByteToWideChar(CP_ACP, MB_COMPOSITE, szFunction, nLen, pOut, nLen);
		    memcpy(wszFunction, pOut, nLen*2);
			delete [] pOut;
		}
		//Message
		if (szMessage != NULL && strlen(szMessage) > 0)
		{
			nLen = strlen(szMessage);
            pOut = new WCHAR[nLen+1];
	        ZeroMemory(pOut, (nLen+1)*2);
	        MultiByteToWideChar(CP_ACP, MB_COMPOSITE, szMessage, nLen, pOut, nLen);
		    memcpy(wszMessage, pOut, nLen*2);
			delete [] pOut;
		}
        //参数 
		if (szParams == NULL)
		{
			m_iParamCount = 0;
			return;
		}
		int i=0;
		char* p = strtok(szParams, ":");
		if (p == NULL)
		{
			m_iParamCount = 0;
			return;
		}
		PWCHAR pParam;
		while(p != NULL && i < 10)
		{
            nLen = strlen(p);
			pOut = new WCHAR[nLen+1];
	        ZeroMemory(pOut, (nLen+1)*2);
	        MultiByteToWideChar(CP_ACP, MB_COMPOSITE, p, nLen, pOut, nLen);
		    pParam = GetParamPointer(i);
			memcpy(pParam, pOut, nLen*2);
			delete [] pOut;
			p = strtok(NULL, ":");
			i++;
		}
        m_iParamCount = i;
	}
	LSPMessage(LSPMessage* that)
	{
        m_iParamCount = that->m_iParamCount;
		memcpy(wszExeName, that->wszExeName, 2*MAX_PATH);
		memcpy(wszFunction, that->wszFunction, 2*MAX_PATH);
		memcpy(wszMessage, that->wszMessage, 2*4096);
		memcpy(wszParam1, that->wszParam1, 2*MAX_PATH);
		memcpy(wszParam2, that->wszParam2, 2*MAX_PATH);
	    memcpy(wszParam3, that->wszParam3, 2*MAX_PATH);
		memcpy(wszParam4, that->wszParam4, 2*MAX_PATH);
		memcpy(wszParam5, that->wszParam5, 2*MAX_PATH);
		memcpy(wszParam6, that->wszParam6, 2*MAX_PATH);
		memcpy(wszParam7, that->wszParam7, 2*MAX_PATH);
		memcpy(wszParam8, that->wszParam8, 2*MAX_PATH);
		memcpy(wszParam9, that->wszParam9, 2*MAX_PATH);
		memcpy(wszParam10, that->wszParam10, 2*MAX_PATH);
	}
	PWCHAR GetParamPointer(int i)
	{
		switch(i)
		{
		case 0:
			return wszParam1;
        case 1:
			return wszParam2;
		case 2:
			return wszParam3;	
		case 3:
			return wszParam4;
        case 4:
			return wszParam5;
		case 5:
			return wszParam6;
		case 6:
			return wszParam7;
        case 7:
			return wszParam8;
		case 8:
			return wszParam9;
		case 9:
			return wszParam10;
        default:
			return NULL;
		}
	}
private:
	void Init()
	{
        m_iParamCount = 0;
		ZeroMemory(wszExeName, 2*MAX_PATH);
		ZeroMemory(wszFunction, 2*MAX_PATH);
		ZeroMemory(wszMessage, 2*4096);
		ZeroMemory(wszParam1, 2*MAX_PATH);
		ZeroMemory(wszParam2, 2*MAX_PATH);
		ZeroMemory(wszParam3, 2*MAX_PATH);
		ZeroMemory(wszParam4, 2*MAX_PATH);
		ZeroMemory(wszParam5, 2*MAX_PATH);
		ZeroMemory(wszParam6, 2*MAX_PATH);
		ZeroMemory(wszParam7, 2*MAX_PATH);
		ZeroMemory(wszParam8, 2*MAX_PATH);
		ZeroMemory(wszParam9, 2*MAX_PATH);
        ZeroMemory(wszParam10, 2*MAX_PATH);
	}
};

class CLSPDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CLSPDlg)
// Construction
public:
	CLSPDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLSPDlg)
	enum { IDD = IDD_LSP_DLG };
	CEdit	m_edtInfo;
	CBCGPMenuButton	m_btnLsp;
	CListBox	m_lstInfo;
	CButton	m_wndPlace;
	CBCGPEdit	m_edtLSPDllPath;
	CString	m_strLSPDllPath;
	CString	m_strLSPName;
	CString	m_strInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLSPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnLsp();
	afx_msg void OnSelchangeListinfo();
	//}}AFX_MSG
	afx_msg LRESULT OnSend(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
private:
	void OnUnhookSocket();
	void OnHookSocket();
	CBCGPPropList m_wndPropList;
    CMenu menu;
	HMODULE m_hProtocolDll;
	bool m_bNeedFree;

	void OnBtnInstallLsp();
	void OnBtnRemoveLsp();
	void OnBtnEnumProtocols();
	CBCGPProp* AddGroupProp(CString strName, CBCGPProp* pParent = NULL);
	void AddChildProp(CString strName, CString strValue, CBCGPProp* pParent = NULL);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSPDLG_H__A2A76D0E_1F8D_4564_89FF_E4AEC6BD056B__INCLUDED_)
