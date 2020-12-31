/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klassen:			XConstraint, XConstraint::XObject
 * Files:			XConstraint.Cpp, XConstraint.H
 * Beschreibung:	Mit der Klasse kann die Größenänderungen von Dialog-
 *					elementen verwaltet werden. Hierbei werden Elemente
 *					an einen oder mehrere Ränder "angehängt", und bei einer
 *					Größenänderung des Dialogs wird dies "Anhängung" beibe-
 *					halten. Jedes Seite eines Dialogelements kann mit CS_LEFT,
 *					CS_RIGHT, CS_TOP oder CS_BOTTOM an einen der Ränder fest
 *					angekoppelt werden. Zusätzlich kann mit CS_POSITION die
 *					Position relativ zu einem Rand definiert werden. Mit
 *					CS_FIXWIDTH und CS_FIXHEIGHT wird das Element in der Größe
 *					fixiert.
 * Funktionen:		Set(), Add(), Resize()
 *
 ****************************************************************************/

#include "StdAfx.H"
#include "XConstraint.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

volatile static char jrrcid[] = "%J%";

/*****************************************************************************
 * Klasse:		XConstraint
 * Funktion:	XObject::XObject (Konstruktor der Sub-Klasse)
 * Parameter:	pObject		Pointer auf das Fenster
 *				newRect		Originalgröße des Fenster
 *				l, r, t, b	Attachments für links, rects, oben, unten
 * Return:		-
 * Beispiel:	cs.Add(id, CS_LEFT, CS_LEFT, CS_TOP, CS_TOP);
 *					==> Größe fest, Position fest
 *				cs.Add(id, CS_LEFT, CS_POSITION, CS_TOP, CS_BOTTOM);
 *					==> Breite variabel, Höhe variabel, Position fest
 *				cs.Add(id, CS_FIXWIDTH, CS_FIXWIDTH, CS_TOP, CS_BOTTOM);
 *					==> Breite fest, Höhe variabel, Position variabel
 *
 * Der XObject-Konstruktor übernimmt die Dimensionen des Objekts als
 * double-Werte und legt die Orientierung der Ränder fest. Die Kanten eines
 * Objekts können mit festem Offset zu einem Rand oder relativ zur Dialoggröße
 * positioniert werden.
 *
 *	Attachment	| Gültigkeit	| Bedeutung
 *	------------|---------------|---------------------------------------------
 *	CS_LEFT		| links, rechts	| Fester Abstand zum linken  Dialogrand
 *	CS_RIGHT	| links, rechts	| Fester Abstand zum rechten Dialogrand
 *	CS_TOP		| oben, unten	| Fester Abstand zum oberen  Dialogrand
 *	CS_BOTTOM	| oben, unten	| Fester Abstand zum unteren Dialogrand
 *	CS_POSITION	| links, rechts	| Abstand zum jeweiligen Rand relativ
 *				| oben, unten	| zur Dialoggröße
 *	CS_FIXWIDTH	| links, rechts	| Die Breite des Objekts bleibt unverändert
 *	CS_FIXHEIGHT| oben, unten	| Die Höhe des Objekts bleibt unverändert
 *				|				| Zusatz:
 *				| 				| Wenn ein FIX-Attribut sowohl für links als
 *				|				| auch für rechts (bzw. für oben und unten)
 *				|				| gesetzt wird, arbeitet 'Resize' wie bei
 *				|				| CS_POSITION, jedoch mit fester Größe.
 ****************************************************************************/
XConstraint::XObject::XObject(CWnd *pObject, CRect newRect, int l, int r, int t, int b)
{
	pWnd		= pObject;
	rect		= newRect;
	
	lAttachment	= l;
	rAttachment	= r;
	tAttachment	= t;
	bAttachment	= b;
}

/*****************************************************************************
 * Klasse:		XConstraint
 * Funktion:	XObject::Resize
 * Parameter:	newWidht, newHeight		Neue Dimensionen des Dialogs
 *				oldWidth, oldHeight		Alte Dimensionen des Dialogs
 * Return:		-
 *
 * Eigentliche Constraint-Verwaltung. Hierbei wird die neue und die alte
 * Dimension übergeben, sodaß die neuen Positionen je nach Attachment neu
 * berechnet werden kann.
 ****************************************************************************/
void XConstraint::XObject::Resize(int newWidth, int newHeight, int oldWidth, int oldHeight)
{
	const double xFaktor		= (double) newWidth  / oldWidth;
	const double yFaktor		= (double) newHeight / oldHeight;
	const int	 offsetWidth	= newWidth - oldWidth;
	const int	 offsetHeight	= newHeight - oldHeight;
	const int	 elementWidth	= rect.Width();
	const int	 elementHeight	= rect.Height();

	CRect rc(rect);

	switch (lAttachment)		// Linke Elementanbindung
	{
		case CS_LEFT:												break;
		case CS_RIGHT:		rc.left += offsetWidth;					break;
		case CS_POSITION:	rc.left  = int(rc.left * xFaktor);		break;
		case CS_FIXWIDTH:	if (rAttachment == CS_FIXWIDTH) 
								rc.left += offsetWidth / 2;			break;
	}

	switch (rAttachment)		// Rechte Elementanbindung
	{
		case CS_LEFT:												break;
		case CS_RIGHT:		rc.right += offsetWidth;				break;
		case CS_POSITION:	rc.right  = int(rc.right * xFaktor);	break;
		case CS_FIXWIDTH:	rc.right = rc.left + elementWidth;		break;
	}

	switch (tAttachment)		// Obere Elementanbindung
	{
		case CS_TOP:												break;
		case CS_BOTTOM:		rc.top += offsetHeight;					break;
		case CS_POSITION:	rc.top  = int(rc.top * yFaktor);		break;
		case CS_FIXHEIGHT:	if (bAttachment == CS_FIXHEIGHT)
								rc.top += offsetHeight / 2;			break;
    }

	switch (bAttachment)		// Untere Elementanbindung
	{
		case CS_TOP:												break;
		case CS_BOTTOM:		rc.bottom += offsetHeight;				break;
		case CS_POSITION:	rc.bottom  = int(rc.bottom * yFaktor);	break;
		case CS_FIXHEIGHT:	rc.bottom = rc.top + elementHeight;		break;
	}

	//========================================================================
	// Spezialbehandlung, wenn rechts/unten verschoben wird aber trotzdem
	// fest Größen verlangt wird.
	//========================================================================
	if ((rAttachment == CS_POSITION) && (lAttachment == CS_FIXWIDTH))
		rc.left		= rc.right - elementWidth;

	if ((bAttachment == CS_POSITION) && (tAttachment == CS_FIXHEIGHT))
		rc.top		= rc.bottom - elementHeight;

	//========================================================================
	// Objekt an die neue Position bewegen.
	//========================================================================
    pWnd->MoveWindow(rc, TRUE);
	pWnd->Invalidate(FALSE);
}

/*****************************************************************************
 * Klasse:		XConstraint
 * Funktion:	Add
 * Parameter:	id			ID des Constraint-Element (alternativ)
 *				l, r, t, b	Attachment des Elements (links, recht, oben, unten)
 * Return:		-
 *
 * Ein Dialogelement zur Constraint-Liste hinzugefügen. Anhand der ID des
 * Elements wird beim ersten Aufruf dessen Refrenz-Position bestimmt. Wenn
 * für das gleiche Element ein weiterer Aufruf erfolgt, wird die Referenz-
 * Position benutzt und nicht die aktuelle Objektposition, da sich diese
 * mittlerweile verändert haben kann.
 ****************************************************************************/
void XConstraint::Add(int id, int l, int r, int t, int b)
{
	ASSERT(pParent);

	CRect	rect;
	CWnd	*pWnd;
	XConstraint::XObject	search;

	if (!objects.Lookup(id, search))
	{
		pWnd = pParent->GetDlgItem(id);
		ASSERT(pWnd);

		pWnd->GetWindowRect(&rect);
		pParent->ScreenToClient(&rect);
	}
	else
	{
		pWnd	= search.pWnd;	// Originalpointer und
		rect	= search.rect;	// -größe übernehmen
	}

	objects[id] = XConstraint::XObject(pWnd, rect, l, r, t, b);
}

/*****************************************************************************
 * Klasse:		XConstraint
 * Funktion:	Resize
 * Parameter:	newWidht, newHeight		Neue Fensterdimensionen
 * Return:		-
 *
 * Einspungpunkt für die Constraints. Die Funktion wird normalerweise aus der
 * 'OnSize'-Methode des Dialogs aufgerufen, die einfach nur die neue Dimension
 * des Fensters übergibt. Von hier aus wird dann für alle vorhandenen
 * Constraint-Objekte die 'Resize'-Methode aufgerufen. Wenn '-1' übergeben
 * wird, werden alle Elemente wieder an die Ausgansposition zurückgesetzt.
 ****************************************************************************/
void XConstraint::Resize(int newWidth, int newHeight)
{
	if (newWidth  == -1) { newWidth = size.cx; newHeight = size.cy; }
	if (newWidth  ==  0) return;
	if (newHeight ==  0) return;

	UINT id;
	XConstraint::XObject constraint;
	for (POSITION pos = objects.GetStartPosition(); pos; )
	{
		objects.GetNextAssoc(pos, id, constraint);
		constraint.Resize(newWidth, newHeight, size.cx, size.cy);
	}
}

/*****************************************************************************
 * Klasse:		XConstraint
 * Funktion:	Set
 * Parameter:	pWnd	Pointer auf den Dialog
 * Return:		-
 *
 * Setzt das Dialogobjekt und bestimmt die Original-Fenstergröße.
 ****************************************************************************/
void XConstraint::Set(CWnd *pWnd)
{
	pParent = pWnd;

	CRect cRect;
	pParent->GetClientRect(cRect);
	size = cRect.Size();
}
