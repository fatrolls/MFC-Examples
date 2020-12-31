// winpeDoc.h : interface of the CWinpeDoc class
//
/////////////////////////////////////////////////////////////////////////////
//#include "pefile.h"
#define FILETYPE_EXE 1
#define FILETYPE_DLL  2
#define PRINTMARGIN 2
class CWinpeDoc : public CDocument
{
protected: // create from serialization only
	CWinpeDoc();
	DECLARE_DYNCREATE(CWinpeDoc)

// Attributes
public:
	void SetDocPrtFont(LPLOGFONT lp);
	void SetDocScrnFont(LPLOGFONT lp);
	// font data used by all views
	CFont* m_screenFont;
	CFont* m_printerFont;
	UINT m_cyScreen;
	//UINT m_cyPrinter;
	
	// menu data used by all views
	BOOL m_Dump_Checked;
	BOOL m_DebugDir_Checked;
	BOOL m_Exports_Checked;
	BOOL m_Imports_Checked;
	BOOL m_Headers_Checked;
	BOOL m_Resources_Checked;
	BOOL m_Sections_Checked;
	// functions
	void TurnChecksOff();
	INT GetOpenFileType();
	BYTE* GetDocumentDataP();
	UINT GetDocumentLength();
	UINT GetBytes(UINT,UINT,PVOID);
	PIMAGE_SECTION_HEADER GetEnclosingSectionHeader(DWORD rva,PIMAGE_NT_HEADERS pNTHeader);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinpeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinpeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinpeDoc)
	afx_msg void OnUpdateViewsDebugdir(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewsDump(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewsExports(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewsHeaders(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewsImports(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewsResources(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewsSectntbl(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	INT m_nFileType;
	LPBYTE m_pFileData;
	DWORD m_nDocLength;
	HANDLE m_hFileMapping;
	HANDLE m_hFile;
	BOOL m_DebugDir_Enabled;
	BOOL m_Exports_Enabled;
	BOOL m_Imports_Enabled;
	BOOL m_Dump_Enabled;
	BOOL m_Headers_Enabled;
	BOOL m_Resources_Enabled;
	BOOL m_Sections_Enabled;
	//
	

};

/////////////////////////////////////////////////////////////////////////////
