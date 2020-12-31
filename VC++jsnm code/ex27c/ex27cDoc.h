// ex27cDoc.h : interface of the CEx27cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27CDOC_H__1EAAB6F5_6011_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX27CDOC_H__1EAAB6F5_6011_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

extern const CLSID clsid; // defined in ex27c.cpp
void ITrace(REFIID iid, const char* str);

#define SETFORMATETC(fe, cf, asp, td, med, li)   \
	((fe).cfFormat=cf, \
	 (fe).dwAspect=asp, \
	 (fe).ptd=td, \
	 (fe).tymed=med, \
	 (fe).lindex=li)

class CEx27cDoc : public CDocument
{
friend class CEx27cView;
private:
	CString m_strText;
	LPOLECLIENTSITE m_lpClientSite;
	LPOLEADVISEHOLDER m_lpOleAdviseHolder;
	LPDATAADVISEHOLDER m_lpDataAdviseHolder;
 	CString m_strContainerApp;
	CString m_strContainerObj;
	HGLOBAL MakeMetaFile();


	BEGIN_INTERFACE_PART(OleObject, IOleObject)
		STDMETHOD(SetClientSite)(LPOLECLIENTSITE);
		STDMETHOD(GetClientSite)(LPOLECLIENTSITE*);
		STDMETHOD(SetHostNames)(LPCOLESTR, LPCOLESTR);
		STDMETHOD(Close)(DWORD);
		STDMETHOD(SetMoniker)(DWORD, LPMONIKER);
		STDMETHOD(GetMoniker)(DWORD, DWORD, LPMONIKER*);
		STDMETHOD(InitFromData)(LPDATAOBJECT, BOOL, DWORD);
		STDMETHOD(GetClipboardData)(DWORD, LPDATAOBJECT*);
		STDMETHOD(DoVerb)(LONG, LPMSG, LPOLECLIENTSITE, LONG, 
			HWND, LPCRECT);
		STDMETHOD(EnumVerbs)(LPENUMOLEVERB*);
		STDMETHOD(Update)();
		STDMETHOD(IsUpToDate)();
		STDMETHOD(GetUserClassID)(LPCLSID);
		STDMETHOD(GetUserType)(DWORD, LPOLESTR*);
		STDMETHOD(SetExtent)(DWORD, LPSIZEL);
		STDMETHOD(GetExtent)(DWORD, LPSIZEL);
		STDMETHOD(Advise)(LPADVISESINK, LPDWORD);
		STDMETHOD(Unadvise)(DWORD);
		STDMETHOD(EnumAdvise)(LPENUMSTATDATA*);
		STDMETHOD(GetMiscStatus)(DWORD, LPDWORD);
		STDMETHOD(SetColorScheme)(LPLOGPALETTE);
	END_INTERFACE_PART(OleObject)

	BEGIN_INTERFACE_PART(DataObject, IDataObject)
		STDMETHOD(GetData)(LPFORMATETC, LPSTGMEDIUM);
		STDMETHOD(GetDataHere)(LPFORMATETC, LPSTGMEDIUM);
		STDMETHOD(QueryGetData)(LPFORMATETC);
		STDMETHOD(GetCanonicalFormatEtc)(LPFORMATETC, LPFORMATETC);
		STDMETHOD(SetData)(LPFORMATETC, LPSTGMEDIUM, BOOL);
		STDMETHOD(EnumFormatEtc)(DWORD, LPENUMFORMATETC*);
		STDMETHOD(DAdvise)(LPFORMATETC, DWORD, LPADVISESINK, LPDWORD);
		STDMETHOD(DUnadvise)(DWORD);
		STDMETHOD(EnumDAdvise)(LPENUMSTATDATA*);
	END_INTERFACE_PART(DataObject)

	BEGIN_INTERFACE_PART(PersistStorage, IPersistStorage)
		STDMETHOD(GetClassID)(LPCLSID);
		STDMETHOD(IsDirty)();
		STDMETHOD(InitNew)(LPSTORAGE);
		STDMETHOD(Load)(LPSTORAGE);
		STDMETHOD(Save)(LPSTORAGE, BOOL);
		STDMETHOD(SaveCompleted)(LPSTORAGE);
		STDMETHOD(HandsOffStorage)();
	END_INTERFACE_PART(PersistStorage)

	DECLARE_INTERFACE_MAP()

protected: // Create from serialization only
	CEx27cDoc();
	DECLARE_DYNCREATE(CEx27cDoc)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnFinalRelease();
	virtual void OnCloseDocument();
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx27cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
public:
	//{{AFX_MSG(CEx27cDoc)
	afx_msg void OnModify();
	afx_msg void OnFileUpdate();
	afx_msg void OnUpdateFileUpdate(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations 
//  immediately before the previous line.

#endif 
// !defined(AFX_EX27CDOC_H__1EAAB6F5_6011_11D0_848F_00400526305B__INCLUDED_)
