//  ---------------------------------------------------------
//
//      ( C )     Copyright C - Channel Eng. AG 1998
//      Use or copying of all or any part of the document,
//      except as permitted by the License Agreement is
//      prohibited.
//
//      Author  : Michael Wild, 5063  C - Channel Eng. AG
//
//      Purpose : 
//      This File contains the class CAdvancedTreeCtrl
// 
//      Creation date: April 28, 1998
//
//  ---------------------------------------------------------

#if !defined(AFX_MYTREECTRL_H__26090B18_8B26_11D1_8E51_0000F877728F__INCLUDED_)
#define AFX_MYTREECTRL_H__26090B18_8B26_11D1_8E51_0000F877728F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MytreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTreeCtrl window

class CAdvancedTreeCtrl : public CTreeCtrl
{
// Construction /Destruction
public:
	CAdvancedTreeCtrl();
	virtual ~CAdvancedTreeCtrl();

protected:
    CArray<HANDLE, HANDLE> m_dibArray;
    HANDLE m_dibButtons[2];

private:
	CImageList  m_imglDrives;

    // Paging Members
    long        m_lNumberOfItems;
    long        m_lPageStart;
    HTREEITEM   m_hPageStartingItem;

    struct PagingInfos
	{
		HTREEITEM	m_hStartItem;
		int		    m_iNumberOfItems;
	};

    CArray<PagingInfos,PagingInfos&> m_PagingInfos;

    PagingInfos m_ActualPage;

    DWORD   m_dwLastError;
    
// Attributes
public:
    BOOL            m_bContinuePrinting;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
    // Init Methods
	void InitImageList( void );

    // Paging Method
    void MakePaging( CDC* pDC, CPrintInfo* pInfo );

    // Draw Method
    void DrawTreeCtrl( CDC * pDC, CPrintInfo* pInfo );
 
    // DIB Convertmethod
    void CreateDibArrays( void );
    void DeleteDibArrays( void );

private:
    // Convert Methods for ImageList -> DIB
    HANDLE ImageToDIB( CImageList* pImageList, int iImageNumber, CWnd* pWnd 
                      ,BOOL bOverlay = FALSE, HTREEITEM actualItem = NULL );
    HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal ) ;

    // Print Tree Methods
	void DrawNodes( CDC * pDC, CPrintInfo* pInfo, HTREEITEM actualItem );
    BOOL PrintDIB( HDC hDC, HANDLE hDib, int xOrigin, int yOrigin ) ;
    void DrawTreeLines( CDC * pDC, HTREEITEM hItem, CRect rect ); 
    void DrawTreeButtons( CDC * pDC, HTREEITEM hItem, CRect rect ); 

    // Paging Methods
    void StartPaging( CDC* pDC, CPrintInfo* pInfo, HTREEITEM actualItem );
    void EndPaging( CPrintInfo* pInfo );

	// Generated message map functions
protected:
	//{{AFX_MSG(CAdvancedTreeCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__26090B18_8B26_11D1_8E51_0000F877728F__INCLUDED_)
