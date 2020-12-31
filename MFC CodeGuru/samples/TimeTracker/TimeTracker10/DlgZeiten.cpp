// DlgZeiten.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "TimeTracker.h"
#include "DlgZeiten.h"
#include "ProjektNeu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgZeiten 


CDlgZeiten::CDlgZeiten(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZeiten::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgZeiten)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgZeiten::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgZeiten)
	DDX_Control(pDX, IDC_PROJEKTE, m_ProjektListe);
	DDX_Control(pDX, IDC_ZEITENLISTE, m_Liste);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgZeiten, CDialog)
	//{{AFX_MSG_MAP(CDlgZeiten)
	ON_CBN_SELENDOK(IDC_PROJEKTE, OnSelendokProjekte)
	ON_BN_CLICKED(IDC_NEU, OnNeu)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgZeiten 

BOOL CDlgZeiten::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_Liste.InsertColumn(0, "Tag",   LVCFMT_CENTER, 80);
	m_Liste.InsertColumn(1, "Start", LVCFMT_CENTER, 55);
	m_Liste.InsertColumn(2, "Ende",  LVCFMT_CENTER, 55);
	m_Liste.InsertColumn(3, "Zeit",  LVCFMT_CENTER, 55);

	CString t, Prj;
	t=theApp.GetProfileString("Projekte", "nAktiv", "1");
	t = "Datei" + t;
	t=theApp.GetProfileString("Projekte", t, "Standard-Projekt");

	FillListView(t);
	FillComboBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


BOOL CDlgZeiten::FillListView(CString &Datei)
{
	CStdioFile f;
	if (!f.Open(Datei, CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate))
		return FALSE;
	
	int nItem=-1, nSubitem, i, prev='e';
	CString str, stat, day, st, en, tim;
	float fStart, fEnde;

	m_Liste.DeleteAllItems();
	while (f.ReadString(str))
	{
		stat = str.Left(5);

		if (stat=="Start")
		{	nSubitem=1;
			nItem++;
		}
		else
			nSubitem=2;

		day = str.Mid(8, 12);
		if (prev=='e' ||(nSubitem==1 && prev=='s'))
			m_Liste.InsertItem(LVIF_TEXT, nItem, day, 0, 0, 0, 0);

		tim = str.Mid(22);
		m_Liste.SetItemText(nItem, nSubitem, tim);

		if (nSubitem==2 && prev=='s')
		{	
			st = m_Liste.GetItemText(nItem, 1);
			en = m_Liste.GetItemText(nItem, 2);

			// Abrechnung im Minutentakt
			fStart = atoi(st.Left(2))*60 + atoi(st.Mid(3,2)) + atoi(st.Right(2))/60.F;
			fEnde  = atoi(en.Left(2))*60 + atoi(en.Mid(3,2)) + atoi(en.Right(2))/60.F;

			if (fStart > fEnde) // past Midnight!
				fEnde += 24*60.F;
			fEnde-=fStart;

			tim.Format("%.2f h", fEnde/60.F);
			m_Liste.SetItemText(nItem, 3, tim);
		}
		
		if (nSubitem==1)
			prev='s';
		else
			prev='e';
	}

	fEnde=0;
	nItem++;
	for (i=0; i<nItem; i++)
	{	str = m_Liste.GetItemText(i, 3);

		fEnde += (float)atof(str);
	}

	day="";
	m_Liste.InsertItem(LVIF_TEXT, nItem, day, 0, 0, 0, 0);
	day="Gesamt:";
	m_Liste.SetItemText(nItem, 2, day);
	day.Format("%.2f h", fEnde);
	m_Liste.SetItemText(nItem, 3, day);
	m_Liste.SetItemText(nItem, 1, "0]|[");
	
	return TRUE;
}

void CDlgZeiten::OnSelendokProjekte() 
{
	CString sel, t;
	m_ProjektListe.GetLBText( m_ProjektListe.GetCurSel(), sel);

	int i, max=theApp.GetProfileInt("Projekte", "Anzahl", 0);
	for (i=1; i<=max; i++)
	{
		t.Format("Projekt%i", i);
		t=theApp.GetProfileString("Projekte", t, "Standard-Projekt");

		if (t == sel)
		{
			t.Format("Datei%i", i);
			t=theApp.GetProfileString("Projekte", t, "Standard-Projekt");
			FillListView(t);
			break;
		}
	}
}

void CDlgZeiten::OnNeu() 
{
	CProjektNeu dlg;
	
	int n=theApp.GetProfileInt("Projekte", "Anzahl", 0);

	if (dlg.DoModal()==IDOK)
	{	
		CString t;
		n++;
		theApp.WriteProfileInt("Projekte", "Anzahl", n);
		t.Format("Projekt%i", n);
		theApp.WriteProfileString("Projekte", t, dlg.m_Projekt);
		t.Format("Datei%i", n);
		theApp.WriteProfileString("Projekte", t, dlg.m_Datei);
	}

	FillComboBox();
}

void CDlgZeiten::OnDelete() 
{
	CString sel, prj, fil, t;
	m_ProjektListe.GetLBText( m_ProjektListe.GetCurSel(), sel);
	
	int i, j, max=theApp.GetProfileInt("Projekte", "Anzahl", 0);
	for (i=1; i<=max; i++)
	{
		prj.Format("Projekt%i", i);
		prj=theApp.GetProfileString("Projekte", prj, "Standard-Projekt");
		
		if (prj != sel)
			continue;
		
		fil.Format("Datei%i", i);
		fil=theApp.GetProfileString("Projekte", fil, "Standard-Projekt");
		
		if (MessageBox("Sind Sie sicher, daß Sie das Projekt \""+prj+"\" entfernen möchten?", NULL, MB_YESNO|MB_DEFBUTTON2)==IDYES)
		{	
			j=MessageBox("Möchten Sie auch die Projektdatei \""+fil+"\" löschen?", NULL, MB_YESNOCANCEL);

			if (j==IDCANCEL)
				return;
			if (j==IDYES)
				DeleteFile(fil);

			for (j=i+1; j<=max-1; j++)
			{
				t.Format("Projekt%i", j);
				prj=theApp.GetProfileString("Projekte", t, "Standard-Projekt");
				t.Format("Datei%i", j);
				fil=theApp.GetProfileString("Projekte", t, "Standard-Projekt");
				
				t.Format("Projekt%i", j-1);
				theApp.WriteProfileString("Projekte", t, prj);
				t.Format("Datei%i", j-1);
				theApp.WriteProfileString("Projekte", t, fil);
			}
			t.Format("Projekt%i", max);
			theApp.WriteProfileString("Projekte", t, "");
			t.Format("Datei%i", max);
			theApp.WriteProfileString("Projekte", t, "");

			j = theApp.GetProfileInt("Projekte", "Anzahl", 0);
			theApp.WriteProfileInt("Projekte", "Anzahl", j-1);

			if (j==theApp.GetProfileInt("Projekte", "nAktiv", 0))
				theApp.WriteProfileInt("Projekte", "nAktiv", 0);

			FillComboBox();
			OnSelendokProjekte();
		}
	}
}

void CDlgZeiten::FillComboBox()
{
	CString t;
	int i, max=theApp.GetProfileInt("Projekte", "Anzahl", 0);

	while (m_ProjektListe.DeleteString(0)!=CB_ERR);

	for (i=1; i<=max; i++)
	{
		t.Format("Projekt%i", i);
		t=theApp.GetProfileString("Projekte", t, "Standard-Projekt");
		m_ProjektListe.AddString(t);
	}
	t = theApp.GetProfileString("Projekte", "nAktiv", "1");
	t = "Projekt" + t;
	t = theApp.GetProfileString("Projekte", t, "");
	m_ProjektListe.SelectString(0, t);

}
