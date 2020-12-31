///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Dateiname: COLLECT.H                                                      //
//                                                                           //
// Autor:     Andreas Jäger, Friedrich-Schiller-Universität Jena             //
//                                                                           //
// System:    WIN_RWPM.EXE und WINLRWPM.EXE                                  //
//                                                                           //
// Beschreibung: Kollektionen als Templates                                  //
//                                                                           //
// Hinweise:                                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include "resource.h"


///////////////////////////////////////////////////////////////////////////////
// template-Klasse CCollection                                               //
///////////////////////////////////////////////////////////////////////////////
/*
Diese Klasse entspricht in ihrer Funktionalität dem bekannten PASCAL-Objekt,
sie ist jedoch typensicherer, da nicht mit generischen, sondern mit T* - Zeigern
gearbeitet wird. Außerdem ist die Zahl der Objekte in der Kollektion nahezu un-
begrenzt (Indizierung mit long).
Es können Objekte des Typs "T" oder "abgeleitet von T" gespeichert werden,
wobei ein Zeiger auf ein Objekt vom Typ T entgegengenommen wird, der dann von
der Kollektion verwaltet wird. 
Zusätzlich ist es möglich, mittels des mitgelieferten Dialogs CChooseCollDialog
bzw. TNoHelpChooseCollDialog ein Item als selektiert zu markieren.
Wird CChooseCollDialog verwendet, so muß das Objekt T eine (virtuelle) Help-
Funktion bereitstellen.

Sortierte Kollektionen müssen zusätzlich zur Help-Funktion eine
Vegleichs-Funktion Compare bereitstellen.
*/
template <class T>
class CCollection : public CObject
{
public:
	// Konstruktor und Standard-Konstruktor
	CCollection(char* name = _T("CCollection"), long _limit = 2, long _delta = 50);

	// Destruktor
	virtual ~CCollection();

	// Lesender Zugriff auf count und delta
	long Count() const                     {return count;};
	long CountNonZero() const; // Anzahl der gespeicherten Zeiger ohne Berücksichtigung der NULL-Zeiger
	long Delta() const                     {return delta;};
	bool IsEmpty() const                   {return count == 0L;};
	void SetDelta(long _delta)             {delta = _delta;};

	// Zugriff auf Items
	T* At(long index) const                {return ((index>=0L) && (index<count)) ? items[index] : NULL;};
	T* operator [](long index) const       {return ((index>=0L) && (index<count)) ? items[index] : NULL;};
	T* First() const                       {return (count>0L) ? items[0L] : NULL;};
	T* Last() const                        {return (count>0L) ? items[count-1L] : NULL;};

	// Löschen von Items
	virtual void AtFree(long index, bool discardmem = false);
	virtual void FreeAll(bool discardmem = false); // true übergeben, um freigewordenen Speicher zu verwerfen

protected:
	// Speicher-Verwaltung
	virtual T** Alloc_Mem(long _limit)     {T** _items = new T*[_limit]; ASSERT(_items); return _items;};
	virtual void ReleaseMem()              {delete[] items;};
	virtual void Resize(long _limit); // Anpassung des Speicherblocks, es werden keine Items eingefügt

public:
	// Einfügen von Items
	virtual void AtInsert(T* t, long index);
	virtual void Insert(T* t);

	// Ersetzen von Items
	virtual void AtPut(T* t, long index);
	// Zeiger in der Kollektion durch NULL-Zeiger ersetzen, hilfreich, wenn
	// das Objekt von außerhalb gelöscht wurde
	virtual void SetNULL(long index)      {if (index>=0 && index<count) items[index]=NULL;};

	// Suche nach Items
	virtual long Search(T* t) const;

	// Entfernen von NULL-Zeigern
	virtual void Pack();

	// Verschieben von Items von einer Kollektion in eine andere
	friend CCollection<T>& operator << (CCollection<T>& dest, CCollection<T>& source);

	virtual void Serialize(CArchive& ar);

	// Datenfelder
public:
	CString Name;
protected:
	long count; // Anzahl der Elemente, die sich in der Collection befinden
	long delta; // Inkrement, um das sich die Zahl der aufnehmbaren Elemente vergrößert oder verkleinert
	long limit; // Anzahl der aufnehmbaren Elemente, ohne die Collection zu vergrößern
	T** items;  // Zeiger auf Speicherblock

	// Privater Kopier-Konstruktor und Zuweisungsoperator. 
	// Somit werden die vom Compiler automatisch generierten
	// Funktionen verborgen, da diese nicht korrekt arbeiten.
	// Kollektionen haben in dieser Version keine Kopier-
	// Semantik.
private:
	CCollection(const CCollection<T>& /*coll*/)  {};
	CCollection<T>& operator = (const CCollection<T>& /*coll*/) {return *this;};
};

template <class T>
class CSortCollection : public CCollection<T>
{
public:
	// Konstruktor
	CSortCollection(char* name = _T("CSortedCollection"), long _limit = 2L, long _delta = 50L)
		: CCollection<T>(name, _limit, _delta)
	{ };

	// Vergleich von Items
	virtual int Compare(T* t1, T* t2) const;

	// Suche nach Items
	long Search(T* t) const;
	long BSearch(T* t) const;
	
	// Sortieren
	virtual bool BubbleSort();
	virtual bool InsertionSort();
	virtual bool SelectionSort();
	virtual bool ShellSort();
	virtual bool QuickSort(long l = -1, long r = -1);
	virtual bool MergeSort(long l = -1, long r = -1);

	// Privater Kopier-Konstruktor und Zuweisungsoperator. 
	// Somit werden die vom Compiler automatisch generierten
	// Funktionen verborgen, da diese nicht korrekt arbeiten.
	// Kollektionen haben in dieser Version keine Kopier-
	// Semantik.
private:
	CSortCollection(const CSortCollection<T>& /*coll*/) {};
	CSortCollection<T>& operator = (const CSortCollection<T>& /*coll*/) {return *this;};
};

template <class T>
class CSortedCollection : public CSortCollection<T>
{
public:
	// Konstruktor
	CSortedCollection(char* name = _T("CSortedCollection"), long _limit = 2L, long _delta = 50L, bool _duplicates = false)
		: CSortCollection<T>(name, _limit, _delta), duplicates(_duplicates)
	{ };

	virtual ~CSortedCollection()           {};

	// Duplikate
	void SetDuplicates(bool _duplicates = false){duplicates = _duplicates;};
	bool Duplicates() const                {return duplicates;};

	// Einfügen von Items
	virtual void Insert(T* t);

protected:
	bool duplicates;

	// Privater Kopier-Konstruktor und Zuweisungsoperator. 
	// Somit werden die vom Compiler automatisch generierten
	// Funktionen verborgen, da diese nicht korrekt arbeiten.
	// Kollektionen haben in dieser Version keine Kopier-
	// Semantik.
private:
	CSortedCollection(const CSortedCollection<T>& /*coll*/) {};
	CSortedCollection<T>& operator = (const CSortedCollection<T>& /*coll*/) {return *this;};
};

// Template-Klasse CChooseCollection. 
template<class T>
class CChooseCollection : public CCollection<T>
{
public:
	// Konstruktor und Standard-Konstruktor
	CChooseCollection(char* name = _T("CChooseCollection"), long _limit = 2, long _delta = 50)
		: CCollection<T>(name, _limit, _delta), Selected(0)
	{
	};

	// Destruktor
	virtual ~CChooseCollection()      {};

	// Auswahl
	long GetSelIndex() const          {return Selected;};
	CString GetSelName() const        {return *GetSelected();};
	void SetSelIndex(long _index);
	void SetSelIndex(char* _name);
	T* GetSelected() const            {return At(Selected);};
	bool ChooseSelected(char* dialogtitle = _T("Auswahl"), CWnd* parent = NULL);
	long* MultiSelection(char* dialogtitle = _T("Auswahl"));
	long Find(char* name);

	virtual void Serialize(CArchive& ar);

protected:
	long Selected;

	// Privater Kopier-Konstruktor und Zuweisungsoperator. 
	// Somit werden die vom Compiler automatisch generierten
	// Funktionen verborgen, da diese nicht korrekt arbeiten.
	// Kollektionen haben in dieser Version keine Kopier-
	// Semantik.
private:
	CChooseCollection(const CChooseCollection<T>& /*coll*/) {};
	CChooseCollection<T>& operator = (const CChooseCollection<T>& /*coll*/) {return *this;};
};

template<class T>
class CChooseCollDialog : public CDialog
{
public:
	//enum { IDD = IDD_CHOOSECOLLDIALOG1 };
	CChooseCollDialog(CChooseCollection<T>& coll, LPCTSTR lpszTemplateName, CWnd* parent = NULL) : CDialog(lpszTemplateName, parent), Coll(coll), Selected(coll.GetSelIndex()) {};
	CChooseCollDialog(CChooseCollection<T>& coll, CWnd* parent = NULL, UINT nIDTemplate = IDD_CHOOSECOLLDIALOG) : CDialog(nIDTemplate, parent), Coll(coll), Selected(coll.GetSelIndex()) {};
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	CListBox m_ctlListBox;
	int Selected;
	CChooseCollection<T>& Coll;
};

// ================== CCollection =============================================

template <class T>
CCollection<T>::CCollection(char* name, long _limit, long _delta) : Name(name)
{
	items = Alloc_Mem(_limit);
	count = 0L;
	delta = _delta;
	limit = _limit;
};

template <class T>
CCollection<T>::~CCollection()
{
	for (long i=0L; i<count; i++) delete items[i];
	ReleaseMem();
};

template <class T>
void CCollection<T>::Resize(long _limit)
{
	if (_limit == limit) return; // nichts zu tun

	// temporäres Feld erzeugen
	T** tempitems = Alloc_Mem(_limit);
	// Kopieren
	memcpy(tempitems, items, min(limit, _limit)*sizeof(T*));
	// Altes Feld freigeben
	ReleaseMem();
	limit = _limit;
	items = tempitems;
};

template <class T>
void CCollection<T>::Insert(T* t)
{
	if (count == limit)
	{
		Resize(limit + delta);
	}
	items[count++] = t;
};

template <class T>
void CCollection<T>::FreeAll(bool discardmem) // true übergeben, um freigewordenen Speicher zu verwerfen
{
	for (long i=0L; i<count; i++) delete items[i];
	count = 0L;
	if (discardmem) Resize(delta);
};

template <class T>
void CCollection<T>::AtPut(T* t, long index)
{
	ASSERT(index>=0);
	if (index < 0) return;
	if(index>=count) 
	{
		if (limit<index+1+delta) Resize(index+1+delta);
		for (long j=count; j<index; j++)
		{
			items[j] = NULL;
		}
		items[index] = t;
		count = index + 1;
	}
	else
	{
		if (items[index] != t)
		{
			delete items[index];
			items[index] = t;
		};
	};
};

template <class T>
void CCollection<T>::AtFree(long index, bool discardmem)
{
	ASSERT(index>=0L && index<count);
	if ((index<0L) || (index>=count)) return;
	delete items[index];
	items[index] = NULL;
	if (discardmem)
	{
		for (long i=index; i<count-1; i++)
		{
			items[i] = items[i+1];
		};
		count--;
	}
	else
	{
		if (index==count-1) count--;
	}
};

template <class T>
void CCollection<T>::AtInsert(T* t, long index)
{
	ASSERT(index>=0L && index<=count);
	if(index>=count) 
	{
		if (limit<index+1+delta) Resize(index+1+delta);
		for (long j=count; j<index; j++)
		{
			items[j] = NULL;
		}
		items[index] = t;
		count = index + 1;
	}
	else
	{
		if (count == limit)
		{
			Resize(limit + delta);
		};
		count++;
		for(long i=count; i>index; i--)
		{
			items[i] = items[i-1];
		};
		items[index] = t;
	}
};

template <class T>
long CCollection<T>::Search(T* t) const
{
	for (long i=0L; i<count; i++)
	{
		if (items[i] == t) return i;
	};
	return -1L;
};

template <class T>
long CCollection<T>::CountNonZero() const
{
	long ptrcount = 0L;
	long i;
	for (i=0L; i<Count(); i++)
	{
		if (At(i)) ptrcount++;
	};
	return ptrcount;
};

// Entfernen von NULL-Zeigern
template <class T>
void CCollection<T>::Pack()
{
	long ptrcount = CountNonZero();
	T** tempitems = Alloc_Mem(ptrcount + 10L);  // kleine Sicherheit
	// Kopieren
	long j = 0L;
	for (long i=0L; i<Count(); i++)
	{
		if (At(i))
		{
			tempitems[j++] = At(i);
		}
	};
	// Altes Feld freigeben
	ReleaseMem();
	limit = ptrcount + 10L;
    count = ptrcount;
	items = tempitems;
};

// Verschieben von Items von einer Collection in eine andere
template <class T>
CCollection<T>& operator << (CCollection<T>& dest, CCollection<T>& source)
{
	for (long i=0L; i<source.Count(); i++)
	{
		dest.Insert(source.At(i));
	};
	source.count = 0; //!! count wird auf Null gesetzt, ohne die Items freizugeben,
							//da diese jetzt von dest verwaltet werden
	return dest;
};

template<class T>
void CCollection<T>::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << CountNonZero();
		ar << delta;
		ar << limit;
		for (long i=0; i<count; i++)
		{
			if (At(i))
			{
				At(i)->Serialize(ar);
			}
		}
	}
	else
	{
		FreeAll();
		ar >> count;
		ar >> delta;
		ar >> limit;
		items = Alloc_Mem(limit);
		for (long i=0; i<count; i++)
		{
			T* t = new T();
			t->Serialize(ar);
			items[i] = t;
		}
	}
};

// ================== CSortCollection =======================================

template <class T>
long CSortCollection<T>::Search(T* t) const
{
	// kann mit binärer Suche (BSearch) effizienter erledigt werden
	
	for(long i=0L; i<count; i++)
	{
		if (Compare(items[i], t) == 0) return i;
	};
	
	return -1;
};

template <class T>
long CSortCollection<T>::BSearch(T* t) const
{
	long l = 0;
	long r = count-1;
	long m;

	while (l<=r)
	{
		m = (l+r)/2;
		switch (Compare(At(m), t))
		{
		case -1: l = m+1; break;
		case 0:  return m;
		case 1:  r = m-1;
		}
	}
	return -1;
};

template <class T>
int CSortCollection<T>::Compare(T* t1, T* t2) const
{
	if (!t1 && !t2) return 0;
	if (!t1) return -1;
	if (!t2) return  1;
	return t1->Compare(*t2);
};

template <class T>
bool CSortCollection<T>::BubbleSort()
{
	for (long i=1; i<count; i++)
	{
		for (long j=count-1; j>=i; j--)
		{
			if (Compare(At(j), At(j-1)) == -1)
			{
				T* t = items[j];
				items[j] = items[j-1];
				items[j-1] = t;
				j--;
			}
		}
	}
	return true;
};

template <class T>
bool CSortCollection<T>::InsertionSort()
{
	for (long i=1; i<count; i++)
	{
		long j = i;
		while (j>0 && Compare(At(j), At(j-1)) == -1) 
		{
			T* t = items[j];
			items[j] = items[j-1];
			items[j-1] = t;
			j--;
		}
	}
	return true;
};

template <class T>
bool CSortCollection<T>::SelectionSort()
{
	for (long i=0; i<count; i++)
	{
		long minindex = i;
		T* minkey = At(i);
		for (long j=i+1; j<count; j++)
		{
			if (Compare(At(j), minkey) == -1)
			{
				minkey = At(j);
				minindex = j;
			}
			items[minindex] = items[i];
			items[i] = minkey;
		}
	}
	return true;
};

template <class T>
bool CSortCollection<T>::ShellSort()
{
	return true;
};

template <class T>
bool CSortCollection<T>::MergeSort(long l, long r)
{
	if (l==-1) l = 0;
	if (r==-1) r = count-1;
	return true;
};

template <class T>
bool CSortCollection<T>::QuickSort(long l, long r)
{
	if (l==-1) l = 0;
	if (r==-1) r = count-1;
	return true;
};

// ================== CSortedCollection =======================================

template <class T>
void CSortedCollection<T>::Insert(T* t)
{
	if (!duplicates && Search(t))
	{
		return;    // keine doppelten Schlüssel -> Item wird nicht eingefügt
	};
	if (count == limit)
	{
		Resize(limit + delta);
	};

	count++;
	for(long i=count-1; i>0L; i--)
	{
		if (Compare(items[i-1], t) <= 0)
		{
			items[i] = t;
			return;
		};
		items[i] = items[i-1];
	};
	items[0] = t;
};

// ================== CChooseCollection =======================================
template <class T>
void CChooseCollection<T>::SetSelIndex(long _index)
{
	ASSERT(_index>=0L && _index<count);
	Selected = _index;
	if (Selected < 0L) Selected = 0L;
	if (Selected >= count) Selected = count-1;
};

template <class T>
long CChooseCollection<T>::Find(char* _name)
{
	for (long i=0L; i<count; i++)
	{
		if (At(i)->GetName().Collate(_name)) == 0)
		{
			return i;
		}
	}
	return -1L;
}

template <class T>
void CChooseCollection<T>::SetSelIndex(char* _name)
{
	long i = Find(_name);
	if (i>=0) Selected = i;
};

template <class T>
bool CChooseCollection<T>::ChooseSelected(char* /*dialogtitle*/, CWnd* parent)
{
	CChooseCollDialog<T> dlg(*this, parent);
	if (dlg.DoModal() && dlg.Selected >= 0)
	{
		Selected = dlg.Selected;
		return true;
	}
	return false;
};

template <class T>
long* CChooseCollection<T>::MultiSelection(char* dialogtitle)
{
	return NULL;
};

template<class T>
void CChooseCollDialog<T>::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHOOSECOLLDIALOG_LIST1, m_ctlListBox);
	DDX_LBIndex(pDX, IDC_CHOOSECOLLDIALOG_LIST1, Selected);
};

template<class T>
BOOL CChooseCollDialog<T>::OnInitDialog()
{
	BOOL ret = CDialog::OnInitDialog();
	if (Coll.IsEmpty()) return false; // nothing to choose
	for (long i=0; i<Coll.Count(); i++)
	{
		m_ctlListBox.AddString(Coll.At(i)->GetName());
	}
	m_ctlListBox.SetCurSel(Coll.GetSelIndex());
	return ret;
};

template<class T>
BOOL CChooseCollDialog<T>::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((int)HIWORD(wParam)==LBN_DBLCLK && (int) LOWORD(wParam)==IDC_CHOOSECOLLDIALOG_LIST1)
	{
		wParam = IDOK;
		lParam = 0;
	}
	return CDialog::OnCommand(wParam, lParam);
}

template<class T>
void CChooseCollection<T>::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		CCollection<T>::Serialize(ar);
	}
	else
	{
		CCollection<T>::Serialize(ar);
		Selected = 0; // ist beim Speichern verlorengegangen
	}
}