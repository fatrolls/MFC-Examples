
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


/////////////////////////////////////////////////////////////////////////////
// COXWinApp:
// 
//

class COXWinApp : public CWinApp
{
DECLARE_DYNAMIC(COXWinApp)
// Data Members
public:

protected:

private:

// Member Functions
public:
	COXWinApp();
	void AddDocTemplate(CDocTemplate* pTemplate);
	virtual CFileDialog* NewFileDialog(BOOL bOpenFileDialog, DWORD lFlags);

protected:

private:


};


/////////////////////////////////////////////////////////////////////////////
