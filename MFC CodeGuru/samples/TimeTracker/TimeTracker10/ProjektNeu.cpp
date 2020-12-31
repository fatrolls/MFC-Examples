// ProjektNeu.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "TimeTracker.h"
#include "ProjektNeu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CProjektNeu 


CProjektNeu::CProjektNeu(CWnd* pParent /*=NULL*/)
	: CDialog(CProjektNeu::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjektNeu)
	m_Datei = _T("");
	m_Projekt = _T("");
	//}}AFX_DATA_INIT
}


void CProjektNeu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjektNeu)
	DDX_Text(pDX, IDC_DATEI, m_Datei);
	DDX_Text(pDX, IDC_PROJEKT, m_Projekt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjektNeu, CDialog)
	//{{AFX_MSG_MAP(CProjektNeu)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CProjektNeu 
