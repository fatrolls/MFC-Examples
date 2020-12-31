/*************************************************************************

BmpDlg.h header file

CBmpDialog: A bitmap open dialog with preview. 
            by The Gremlin

Compatibility: Visual C++ 4.0 and up.

**************************************************************************/

#ifndef _BMPDIALOG_H_
#define _BMPDIALOG_H_


// CBmpDialog dialog

class CBmpDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CBmpDialog)

public:
	CBmpDialog(BOOL bOpenFileDialog = TRUE, // TRUE for FileOpen, FALSE for FileSaveAs. Who would want a save with preview?
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

    static BOOL m_showpreview;  // Store this variable in the registry if you want the "Show Preview" setting to be persistent

    static HBITMAP hpreview;

protected:
	//{{AFX_MSG(CBmpDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif