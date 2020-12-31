#include "MainFrm.h"

//class CMainFrame;

class CShowProgress
{
public:
	CShowProgress(CMainFrame* pMainFrame, WORD nProgressIndex) 
	{ 
		m_pMainFrame=pMainFrame; 
		m_nProgressIndex=nProgressIndex; 
	}
	~CShowProgress() {}

protected:
	WORD m_nStep;
	WORD m_nStepIterator;
	WORD m_nDone;
	WORD m_nToDo;

	WORD m_nProgressIndex;
	CMainFrame* m_pMainFrame;

public:
	void SetStep(WORD nStep) { m_nStep=nStep; }
	void SetStepIterator(WORD nStepIterator) { m_nStepIterator=nStepIterator; }
	void SetDone(WORD nDone) { m_nDone=nDone; }
	void SetToDo(WORD nToDo) { m_nToDo=nToDo; }
	void Initialize(WORD nStep, WORD nToDo)
	{
		SetStep(nStep);
		SetToDo(nToDo);
		SetStepIterator(0);
		SetDone(0);
		m_pMainFrame->m_wndStatusBar.ResetBar(m_nProgressIndex);
	}
	void Reset()
	{
		SetStep(0);
		SetToDo(0);
		SetStepIterator(0);
		SetDone(0);
		m_pMainFrame->m_wndStatusBar.ResetBar(m_nProgressIndex);
	}
	void Iterate()
	{
		m_nStepIterator++;
		if(m_nStepIterator==m_nStep)
		{
			SetStepIterator(0);
			m_nDone++;
			DWORD wPercent=((DWORD)m_nDone*(DWORD)100)/(DWORD)m_nToDo;
			m_pMainFrame->m_wndStatusBar.
				SetBarProgress(m_nProgressIndex,TRUE,100,wPercent);
		}
	}
};