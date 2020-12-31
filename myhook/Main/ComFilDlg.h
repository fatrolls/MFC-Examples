#if !defined(AFX_COMFILDLG_H__31D94F01_BE02_42A8_A285_5E3D9A9C40A9__INCLUDED_)
#define AFX_COMFILDLG_H__31D94F01_BE02_42A8_A285_5E3D9A9C40A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComFilDlg.h : header file
//

#include "RootDlg.h"
#include "Serial.h"
/////////////////////////////////////////////////////////////////////////////
// CComFilDlg dialog

class CComFileDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CComFileDlg)
// Construction
public:
	CComFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComFileDlg)
	enum { IDD = IDD_ComFile_DIALOG };
	CComboBox	m_BoudRate;
	CEdit	m_Save;
	CEdit	m_Log;
	CButton	m_Close;
	CButton	m_Send;
	CButton	m_Open;
	CEdit	m_Status;
	CEdit	m_EditFile;
	CComboBox	m_ComboPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonbrowser();
	afx_msg void OnButtonclose();
	afx_msg void OnButtonopen();
	afx_msg void OnButtonsend();
	afx_msg void OnDestroy();
	afx_msg void OnBtnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void AddLog(LPCTSTR lpszString);

	CSCSerial *m_pComFile;
	// 事件对象和线程对象
    HANDLE m_hServerThread;
	// 指示线程是否退出
	BOOL m_bThreadExit;
	BOOL m_bNeedSend;
    // 记录文件传输状态
	CFile m_SendFile;
	PBYTE m_pData;
	DWORD m_dwFileLen;
	DWORD m_dwRecvLen;

	friend DWORD WINAPI ServerThreadProc(LPVOID lpParam);	// 服务线程
private:
	BOOL Connect();
	DWORD ServerProc();
	BOOL SendFile(CFile& file, CSCSerial* pSerial);
	BYTE SendEOF();
	BYTE SendConnect();
	void OnRecvCmp(PBYTE pData, DWORD dwFileLen);	// 文件接收完毕
};

DWORD WINAPI ServerThreadProc(LPVOID lpParam);	// 服务线程
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMFILDLG_H__31D94F01_BE02_42A8_A285_5E3D9A9C40A9__INCLUDED_)
