//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: PEOPLE.CPP
//

#include "prefix.h"
#include "people.h"
#include <fstream.h>
#include <iomanip.h>

MyApp myApp; // instantiate one and only app

class CBUSStates : public WPComboBox, public WPListData {
	static LPCSTR States[];
	int curState;
public:
	CBUSStates(WPWin *pwin, int id) : WPComboBox(pwin, id)
		{ setList(this); createWin(); } 

	static WPControl* New(WPWin* pwin, int id) 
		{ return new CBUSStates(pwin, id); }

	BOOL firstItem()		{ return curState = 1; }
	BOOL nextItem()		{ return States[curState] ? ++curState : 0; }
	DWORD getItemText(char *buf, int len)
		{ lstrcpy(buf, States[curState-1]); return 0; }
};

LPCSTR CBUSStates::States[] = {
	"AL","AK","AZ","AR","CA","CO","CN","DC","DE","FL","GA","HI","ID",
	"IL","IN","IA","KS","KY","LA","ME","MD","MA","MI","MN","MO","MS",
	"MT","NE","NV","NH","NJ","NM","NY","NC","ND","OH","OK","OR","PA",
	"RI","SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY",NULL
};

//////////////////
// Special kind of edit control lets user type digits only.
// 
class EditZip : public WPEdit {
public:
	EditZip(WPWin *pwin, int id) : WPEdit(pwin, id) 
		{ setLegalChars("0123456789-"); createWin(); }
	static WPControl* New(WPWin* pwin, int id)
		{ return new EditZip(pwin, id); }
};

enum STATUS { STFRIEND=0, STBUSINESS, STOTHER, NSTATUS };

class Person {					
// For Zortech and Microsoft, all Person members must be public (sigh).
// These compilers can't handle static initialization of the control map 
// correctly. DlgEditPerson is a friend of Person, so
// DlgEditPerson::ControlMap should be able to access its members. Borland
// handles this correctly (hooray), but not Microsoft nor Zortech (boo).
public:
	char		name[50];
	char		addr[50];
	char		city[30];
	char		zip[10];
	char		phone[15];
	char		state[3];
	int		status;
	BOOL		selected;

	Person()	{ clear(); }
	Person	*next;			// next person in list
	Person	*prev;			// previous person in list
	
	int format(char *buf, int len)
		{ return sprintf(buf,"%s\t%s", name, phone); }
	void clear()
		{ memset(this, 0, sizeof(Person)); }

	friend istream& operator>>(istream& is, Person& p);
	friend ostream& operator<<(ostream& os, Person& p);
	
	friend class DlgEditPerson;
};

class DlgEditPerson : public WPDialogModal {
	static WPControlMap ControlMap[];
public:
	DlgEditPerson(WPWin *pwin, Person *p)
		: WPDialogModal("DLGEDITPERSON", pwin, ControlMap, p) { createWin(); }

	BOOL command(int id, WORD msg);
	void updateScreen();
};

WPControlMap DlgEditPerson::ControlMap[] = {
	cmEdit( IDED_NAME,		Person,	name )
	cmEdit( IDED_ADDR,		Person,	addr )
	cmEdit( IDED_CITY,		Person,	city )
	cmCust( CBUSStates::New,IDCB_STATE,	Person,	state )
	cmEdit( IDED_PHONE,		Person,	phone )
	cmRBgp( IDRBG_STATUS,	Person,	status,		NSTATUS )
	cmCust( EditZip::New,	IDED_ZIP,	Person,	zip )
	cmButn( IDB_SELECTED,	Person,	selected )
	cmPush( IDM_OKNEXT)
	cmPush( IDM_OKPREV)
	cmEnd(IDED_NAME)
};

BOOL DlgEditPerson::command(int id, WORD msg)
{
	switch (id) {
	case IDM_OKNEXT:
	case IDM_OKPREV:
		updateObject();
		Person *p = (Person*)getObject();
		p = id==IDM_OKNEXT ? p->next : p->prev;
		assert(p);
		linkObject(p);
		return TRUE;
	}
	return WPDialogModal::command(id, msg);
}

void DlgEditPerson::updateScreen()
{
	Person *p = (Person*)getObject();
	getChild(IDM_OKNEXT)->enableWin(p->next != NULL);
	getChild(IDM_OKPREV)->enableWin(p->prev != NULL);
	WPDialogModal::updateScreen();
}

const char DELIM = 1;
const char NL = '\n';

istream& operator>>(istream& is, Person& p)
{
	char delim;
	is.get(p.name,	sizeof(p.name), DELIM); is >> delim;
	is.get(p.addr,	sizeof(p.addr), DELIM);	is >> delim;
	is.get(p.city,	sizeof(p.city), DELIM);	is >> delim;
	is.get(p.state,sizeof(p.state),DELIM);	is >> delim;
	is.get(p.zip,	sizeof(p.zip),	 DELIM);	is >> delim;
	is.get(p.phone,sizeof(p.phone),DELIM);	is >> delim;
	is >> p.status >> delim;
	is >> p.selected >> delim;
	is.get();					// eat newline
	return is;
}

ostream& operator<<(ostream& os, Person& p)
{
	if (p.name[0]) {
		os << p.name << DELIM;
		os << p.addr << DELIM;
		os << p.city << DELIM;
		os << p.state << DELIM;
		os << p.zip << DELIM;
		os << p.phone << DELIM;
		os << p.status << DELIM;
		os << p.selected << DELIM;
		os << NL;
	}
	return os;
}

//////////////////
// Alternating icon is special kind of static icon.
// 
class AltIcon : public WPStaticIcon {
	HICON icon1;
	HICON icon2;
	HICON whichIcon;
	int nclicks;
protected:
	BOOL timer(int id);
public:
	AltIcon(WPWin *pwin, int id, LPCSTR name1, LPCSTR name2);
	~AltIcon() { killTimer(1); }
};

//////////////////
// Create alternating icon
// 
AltIcon::AltIcon(WPWin *pwin, int id, LPCSTR name1, LPCSTR name2)
	: WPStaticIcon(pwin, id)
{
	whichIcon = icon1 = theApp->loadIcon(name1);
	icon2 = theApp->loadIcon(name2);
	nclicks=0;
	setTimer(1, 200);
	createWin();
}

//////////////////
// Handle timer message: swap icons
// 
BOOL AltIcon::timer(int id)
{
	if (++nclicks > 5) {
		linkObject(whichIcon = whichIcon==icon1 ? icon2 : icon1);
		updateScreen();
		if (nclicks > 6)
			nclicks=0;
	}
	return TRUE;
}

////////////////
// Special About dialog box w/animated icon.
// 
class AboutPeople : public WPDialogModal {
public:
	AboutPeople(WPWin *pwin) : WPDialogModal("DLGABOUT",pwin) 
		{ createWin(); }
	void initDlg() 
		{ new AltIcon(this, IDSI_ABOUTICON, "Hello1","Hello2"); }
};

// tab stops for main list window
static int TABS[] = { 100, 150, 200 };
const NTABS = sizeof(TABS)/sizeof(TABS[0]);

class PeopleWin : public WPMainWin, public WPListData {
	WPListBox *lbPeople;
	Person *firstPerson;
	Person *curPerson;
	int nPerson;
	int nPeople;
public:
	PeopleWin(LPCSTR fname);
	~PeopleWin();

	BOOL command(int id, WORD msg);
	BOOL menuInit(WPMenu &menu);

	void editPerson();
	BOOL fileOpen(LPCSTR fname);
	BOOL fileSave(LPCSTR fname);
	BOOL fileNew();
	BOOL sized(WPRect &box,WORD how)	{ lbPeople->moveWin(box); return TRUE; }
	BOOL gotFocus(WPWin *prev)			{ lbPeople->setFocus(); return TRUE; }
	BOOL anySelected()					{ return lbPeople->getSel()!=-1; }

	Person* getSelectedPerson();
	int getIndex(Person *p);

	// These are the ListData methods.
	BOOL firstItem()		
		{ return (curPerson=firstPerson) != NULL; }
	BOOL nextItem()
		{ if (curPerson) curPerson=curPerson->next; return curPerson!=NULL; }
	DWORD getItemText(char *buf, int len)
		{ if (curPerson) curPerson->format(buf, len); else *buf = 0; return 0; }
};

void MyApp::main()
{
	char fname[80];
	getCmdLine(fname);
	mainWin = new PeopleWin(fname);
	run();
}

PeopleWin::PeopleWin(LPCSTR fname)
{
	firstPerson = curPerson = NULL;
	nPerson = nPeople = 0;

	createWin();

	lbPeople = new WPListBox(this, IDLB_PEOPLE);
	createArgs.pos = this;
	createArgs.style &= ~WS_BORDER;
	lbPeople->createWin();
	lbPeople->setList(this);
	lbPeople->setTabStops(TABS, NTABS);
	
	fileInit(fname, "PEOPLE");
	fileNameFilter("People Files (*.PPL)\0*.PPL\0");
}

PeopleWin::~PeopleWin()
{
	fileNew();
}

Person *PeopleWin::getSelectedPerson()
{
	int index = lbPeople->getSel();
	Person *p = NULL;
	if (index >= 0) {
		for (p=firstPerson; p && index-->0; p=p->next)
			;
	}
	return p;
}

int PeopleWin::getIndex(Person *person)
{
	int index = 0;
	for (Person *p=firstPerson; p; p=p->next, index++) 
		if (p==person)
			break;
	return index;
}

void PeopleWin::editPerson()
{
	Person *p = getSelectedPerson();
	assert(p);
	WPDialog *dlg = new DlgEditPerson(this, p);
	if (dlg->isModified()) {
		fileIsModified(TRUE);
		lbPeople->setList(this, getIndex((Person*)dlg->getObject()));
	}
}

BOOL PeopleWin::command(int id, WORD msg)
{
	switch (id) {
	case WPIDM_ABOUT:
		{
		AboutPeople about(this);
		return TRUE;
		}
	case IDM_EDIT:
		editPerson();
		return TRUE;

	case IDM_EDITNEW:
	case WPIDM_EDITDELETE:
		ErrBox("Not implemented yet.");
		return TRUE;

	case IDLB_PEOPLE:
		if (msg==LBN_DBLCLK)
			editPerson();
		return TRUE;
	}
	return WPMainWin::command(id, msg);
}

BOOL PeopleWin::menuInit(WPMenu &menu)
{
	WPMenu mainMenu = this;
	if (menu==mainMenu) {
		Person *p = getSelectedPerson();
		menu.enableItem(IDM_EDIT, p!=NULL);
		menu.enableItem(WPIDM_EDITDELETE, p!=NULL);
	}
	return WPMainWin::menuInit(menu);
}

//////////////////
// File Open command
// 
BOOL PeopleWin::fileOpen(LPCSTR fname)
{
	char buf[MAXFILENAMELEN];
	lstrcpyn(buf, fname, MAXFILENAMELEN);
	ifstream inf(buf);
	if (!inf)
		return FALSE;

	nPeople = 0;
	fileNew();

	Person *prev = NULL;
	while (!inf.eof()) {
		nPeople++;
		Person* p = new Person;
		inf >> *p;
		p->prev = prev;
		if (prev)
			prev->next = p;
		else
			firstPerson = p;
		prev = p;
	}
	lbPeople->setList(this);

	return TRUE;
}

//////////////////			
// File Save command
// 
BOOL PeopleWin::fileSave(LPCSTR fname)
{
	char buf[MAXFILENAMELEN];
	lstrcpyn(buf, fname, MAXFILENAMELEN);
	ofstream fout(buf);
	if (fout) {
		for (Person* p = firstPerson; p; p=p->next)
			fout << *p;
		return TRUE;
	}
	return FALSE;
}

//////////////////
// New file: delete all the people
// 
BOOL PeopleWin::fileNew()
{
	while (firstPerson) {
		Person *p = firstPerson->next;
		delete firstPerson;
		firstPerson = p;
	}
	lbPeople->setList(this);
	return TRUE;
}
