#if !defined(AFX_SNIFFERDLG_H__1F5DCDB6_E355_460E_98B4_D5A50A12DCBC__INCLUDED_)
#define AFX_SNIFFERDLG_H__1F5DCDB6_E355_460E_98B4_D5A50A12DCBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SnifferDlg.h : header file
//
#include "RootDlg.h"
#include "ProtocolTypes.h"
/////////////////////////////////////////////////////////////////////////////
// CSnifferDlg dialog

class CSnifferDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CSnifferDlg)
// Construction
public:
	CSnifferDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSnifferDlg)
	enum { IDD = IDD_SNIFFER_DLG };
	CButton	m_btnStop;
	CButton	m_btnStart;
	CTreeCtrl	m_treeData;
	CComboBox	m_cmbInterface;
	int		m_iInterface;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnifferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void DecodePacket(char* bufT, DWORD dwRet);
	static UINT DoSniffer(LPVOID pParam);
	void GetInterface(CStringArray& anterface);

	// Generated message map functions
	//{{AFX_MSG(CSnifferDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnStartSniffer();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CFont m_Font;
	CImageList m_imgList;
	CWinThread* m_pThread;
	CEvent m_event;
	bool m_bThreadExit;

	struct InsertData
	{
	protected:
		struct TCP{
			CString strSrcPort;
			CString strDestPort;
			CString strWindowSize;
			CString strFlags;
			CString strSequence;
			CString strUserName;
			CString strPassword;
		}; 
		struct UDP
		{
			CString strSrcPort;
			CString strDestPort;
		};
		struct ARP
		{
			CString  strSrcMac;   //Ô´MAC
			CString  strDestMac;  //Ä¿µÄMAC 
		};
		
		enum PROTOCOL_TYPE { TCP_TYPE, UDP_TYPE, ARP_TYPE };
		
		CString strSrcIP;
		CString strDestIP;
		
		union{
			TCP* tcp;
			UDP* udp;
			ARP* arp;
		} Data;
		
		CString strData;
		PROTOCOL_TYPE m_iType;
	public:
		void Output(CTreeCtrl& tree);
		InsertData(PIPHeader pIpHeader, PTCPHeader pTcpHeader, char* pData, DWORD dwDataSize);
		InsertData(PIPHeader pIpHeader, PUDPHeader pUdpHeader, char *pData, DWORD dwDataSize);
		InsertData(PIPHeader pIpHeader, PARPHeader pArpHeader, char *pData, DWORD dwDataSize);
		~InsertData()
		{
			if (m_iType == TCP_TYPE)
				delete Data.tcp;
			if (m_iType == UDP_TYPE)
				delete Data.udp;
			if (m_iType == ARP_TYPE)
				delete Data.arp;
		}
	private:
		void GetFtpData(char *pData, DWORD dwSize);
		CString GetData(char* pData, DWORD dwSize);
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNIFFERDLG_H__1F5DCDB6_E355_460E_98B4_D5A50A12DCBC__INCLUDED_)
