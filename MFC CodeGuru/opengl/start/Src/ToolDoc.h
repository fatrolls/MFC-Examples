//********************************************
// ToolDoc.h
// The document, contain a SceneGraph
//********************************************
// pierre.alliez@cnet.francetelecom.fr
// Created : 12/12/97
// Modified
//********************************************


#if !defined(AFX_TOOLDOC_H__06A35631_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
#define AFX_TOOLDOC_H__06A35631_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSeneGraph3d; 

class CToolDoc : public CDocument
{
protected: // create from serialization only
	CToolDoc();
	DECLARE_DYNCREATE(CToolDoc)

// Attributes
private:
	//CSeneGraph3d m_SceneGraph;

// Functions
public:

	// OpenGL
	void RenderScene();


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLDOC_H__06A35631_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
