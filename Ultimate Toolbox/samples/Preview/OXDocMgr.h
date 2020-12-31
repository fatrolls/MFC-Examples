class COXDocManager : public CDocManager
{
	DECLARE_DYNAMIC(COXDocManager)
public:

	COXDocManager();

	// helper for standard commdlg dialogs
	virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);
};