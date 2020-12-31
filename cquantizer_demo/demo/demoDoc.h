// demoDoc.h : interface of the CDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////
#define MAX_UNDO_LEVELS 8

#define	WM_USER_NEWIMAGE WM_USER+1
#define WM_USER_PROGRESS WM_USER+2

class CxImage;
class CDemoDoc : public CDocument
{
protected: // create from serialization only
	CDemoDoc();
	DECLARE_DYNCREATE(CDemoDoc)

// Attributes
public:
//	enum
//	{
//		WM_USER_NEWIMAGE = WM_USER+1
//	};

	CxImage *image;				//main image
	HANDLE	hThread,hProgress;	//elaboration thread

	void	*m_fp[4];	//function parameters
	long	m_MenuCommand;

// Operations
public:
	void SubmitUndo();
	inline CxImage *GetImage() { return image; }
	inline BOOL GetStretchMode() { return stretchMode; }
	inline BOOL GetWaitingClick() { return m_WaitingClick; }
	inline void SetWaitingClick(BOOL b) { m_WaitingClick=b; }
	inline float GetZoomFactor() { return m_ZoomFactor; }
	int ComputePixel(float x, float y, float &x1, float &y1);
	void ComputeNewImage(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL DoSave(LPCTSTR pszPathName, BOOL bReplace =TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Stopwatch(int start0stop1);
	void UpdateStatusBar();
	virtual ~CDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL stretchMode;
	CxImage *imageUndo[MAX_UNDO_LEVELS];
	int m_UndoLevel;
	float m_ZoomFactor;
	BOOL m_WaitingClick;
	LARGE_INTEGER m_swFreq, m_swStart, m_swStop; //stopwatch
	float m_etime; //elapsed time
	DWORD dwThreadID;
	long m_progress;

	//{{AFX_MSG(CDemoDoc)
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnStretchMode();
	afx_msg void OnUpdateStretchMode(CCmdUI* pCmdUI);
	afx_msg void OnTransformEllipse();
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
	afx_msg void OnCximageFlip();
	afx_msg void OnCximageMirror();
	afx_msg void OnCximageNegative();
	afx_msg void OnCximageGrayscale();
	afx_msg void OnCximageRotate();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
	afx_msg void OnViewNormalviewing11();
	afx_msg void OnUpdateViewNormalviewing11(CCmdUI* pCmdUI);
	afx_msg void OnCximageSettransparency();
	afx_msg void OnUpdateCximageSettransparency(CCmdUI* pCmdUI);
	afx_msg void OnCximageRemovetransparency();
	afx_msg void OnUpdateCximageRemovetransparency(CCmdUI* pCmdUI);
	afx_msg void OnCximageResample();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCximageFlip(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCximageGrayscale(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCximageMirror(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCximageNegative(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCximageResample(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCximageRotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransformEllipse(CCmdUI* pCmdUI);
	afx_msg void OnCximageDecreasebpp();
	afx_msg void OnCximageIncreasebpp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
