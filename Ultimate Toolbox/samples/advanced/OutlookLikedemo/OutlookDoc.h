// OutlookDoc.h : interface of the COutlookDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKDOC_H__DA7AA82E_2C67_11D2_88E3_0080C859A484__INCLUDED_)
#define AFX_OUTLOOKDOC_H__DA7AA82E_2C67_11D2_88E3_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class COutlookDoc : public CDocument
{
protected: // create from serialization only
	COutlookDoc();
	DECLARE_DYNCREATE(COutlookDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutlookDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutlookDoc)
	afx_msg void OnAddressBook();
	afx_msg void OnAutoPreview();
	afx_msg void OnBack();
	afx_msg void OnDelete();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFindItems();
	afx_msg void OnForward();
	afx_msg void OnForwardMessage();
	afx_msg void OnGroupByBox();
	afx_msg void OnMoveToFolder();
	afx_msg void OnNewMessage();
	afx_msg void OnOfficeAssistant();
	afx_msg void OnReplyToAll();
	afx_msg void OnToggleTree();
	afx_msg void OnUpOneFolder();
	afx_msg void OnReply();
	afx_msg void OnAppointment();
	afx_msg void OnContact();
	afx_msg void OnMeetingRequest();
	afx_msg void OnNote();
	afx_msg void OnOfficeDocument();
	afx_msg void OnPostInFolder();
	afx_msg void OnTask();
	afx_msg void OnTaskRequest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKDOC_H__DA7AA82E_2C67_11D2_88E3_0080C859A484__INCLUDED_)
