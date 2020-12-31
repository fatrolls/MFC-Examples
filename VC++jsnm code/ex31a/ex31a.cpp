// EX31A.CPP - Implementation file for your Internet Server
//    ex31a Extension

#include "stdafx.h"
#include "ex31a.h"

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object
// NOTE: You may remove this object if you alter your project to no
// longer use MFC in a DLL.

CWinApp theApp;

///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CEx31aExtension, CHttpServer)
	ON_PARSE_COMMAND(ConfirmOrder, CEx31aExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("name") 
	ON_PARSE_COMMAND(ProcessPizzaForm, CEx31aExtension, ITS_PSTR ITS_PSTR ITS_I4 ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("name address quantity size top1=~ top2=~ top3=~ top4=~") 
	ON_PARSE_COMMAND(ProcessTimesheet, CEx31aExtension, ITS_I4 ITS_PSTR ITS_R8 ITS_I4)
	ON_PARSE_COMMAND_PARAMS("Period Employee Hours Job") 
	ON_PARSE_COMMAND(Default, CEx31aExtension, ITS_EMPTY)
	DEFAULT_PARSE_COMMAND(Default, CEx31aExtension)
END_PARSE_MAP(CEx31aExtension)


///////////////////////////////////////////////////////////////////////
// The one and only CEx31aExtension object

CEx31aExtension theExtension;


///////////////////////////////////////////////////////////////////////
// CEx31aExtension implementation

CEx31aExtension::CEx31aExtension()
{
	m_nTotalPizzaOrders = 0;
}

CEx31aExtension::~CEx31aExtension()
{
}

BOOL CEx31aExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// CEx31aExtension command handlers

void CEx31aExtension::Default(CHttpServerContext* pCtxt)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);

	*pCtxt << _T("This default message was produced by the Internet");
	*pCtxt << _T(" Server DLL Wizard. Edit your CEx31aExtension::Default()");
	*pCtxt << _T(" implementation to change it.\r\n");

	EndContent(pCtxt);
}

void CEx31aExtension::ConfirmOrder(CHttpServerContext* pCtxt, LPCTSTR pstrName)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);
	*pCtxt << "<p>Our courteous delivery person will arrive within 30 minutes.";
	*pCtxt << "<p>Thank you, " << pstrName << ", for using CyberPizza.";
	// now retrieve the order from disk by name, then make the pizza
	// be prepared to delete the order after a while if the customer doesn't confirm
	m_cs.Lock(); // gotta be threadsafe
	  long int nTotal = ++m_nTotalPizzaOrders;
	m_cs.Unlock();
	*pCtxt << "<p>Total pizza orders = " << nTotal;
	EndContent(pCtxt);
}

void CEx31aExtension::ProcessPizzaForm(CHttpServerContext* pCtxt, LPCTSTR pstrName,
				LPCTSTR pstrAddr, int nQuantity, LPCTSTR pstrSize,
				LPCTSTR pstrTop1, LPCTSTR pstrTop2,	LPCTSTR pstrTop3, LPCTSTR pstrTop4)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);
	if((strlen(pstrName) > 0) && (strlen(pstrAddr) > 0)) {
		*pCtxt << " Your pizza order is as follows:";
		*pCtxt << "<p>Name: " << pstrName;
		*pCtxt << "<p>Address: " << pstrAddr;
		*pCtxt << "<p>Number of pies: " << (long int) nQuantity;
		*pCtxt << "<p>Size: " << pstrSize;
		*pCtxt << "<p>Toppings: " << pstrTop1 << " " << pstrTop2 << " " << pstrTop3 << " " << pstrTop4;
		*pCtxt << "<p>The total cost is $23.49, including delivery.";
		*pCtxt << "<form action=\"ex31a.dll?ConfirmOrder\" method=POST>";
		*pCtxt << "<p><input type=\"hidden\" name=\"name\" value=\"" << pstrName << "\">"; // xref to original order
		*pCtxt << "<p><input type=\"submit\" value=\"Confirm and charge my credit card\">";
		*pCtxt << "</form>";
		// store this order in a disk file or database, referenced by name
	}
	else {
		*pCtxt << " You forgot to enter your name or address. Back up and try again.";
	}
	EndContent(pCtxt);
}

void CEx31aExtension::ProcessTimesheet(CHttpServerContext* pCtxt, int nPeriod,
				LPCTSTR pstrEmployee, double dHours, int nJob)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);
	*pCtxt << " Employee timesheet:";
	*pCtxt << "<p>Period: " << (long int) nPeriod;
	*pCtxt << "<p>Employee: " << pstrEmployee;
	*pCtxt << "<p>Hours: " << dHours;
	*pCtxt << "<p>Job: " << (long int) nJob;
	// store this transaction in a disk file or database
	EndContent(pCtxt);
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CEx31aExtension, CHttpServer)
	//{{AFX_MSG_MAP(CEx31aExtension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0



///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/

LPCTSTR CEx31aExtension::GetTitle() const
{
	return "Ex31a Pizza Extension";
}
