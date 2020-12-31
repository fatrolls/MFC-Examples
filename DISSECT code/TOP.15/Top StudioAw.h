#if !defined(AFX_TOPSTUDIOAW_H__B0E47989_AF67_11D0_968D_444553540000__INCLUDED_)
#define AFX_TOPSTUDIOAW_H__B0E47989_AF67_11D0_968D_444553540000__INCLUDED_

// Top Studioaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see Top Studio.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CTopStudioAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);

protected:
	CDialogChooser* m_pChooser;
};

// This declares the one instance of the CTopStudioAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global TopStudioaw.  (Its definition is in Top Studioaw.cpp.)
extern CTopStudioAppWiz TopStudioaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPSTUDIOAW_H__B0E47989_AF67_11D0_968D_444553540000__INCLUDED_)
