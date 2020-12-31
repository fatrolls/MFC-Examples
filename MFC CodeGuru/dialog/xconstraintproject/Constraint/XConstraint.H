/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			XConstraint, XConstraint::XObject
 * JRRC:			%J%
 *
 ****************************************************************************/

#ifndef __CONSTRAINTS__
#define __CONSTRAINTS__

#include <afxtempl.h>

const int CS_LEFT		= 0x0001;
const int CS_TOP		= 0x0001;
const int CS_RIGHT		= 0x0002;
const int CS_BOTTOM		= 0x0002;
const int CS_FIXWIDTH	= 0x0004;
const int CS_FIXHEIGHT	= 0x0004;
const int CS_POSITION	= 0x0008;

class XConstraint : public CObject
{
private:
	class XObject
	{
	public:
		CWnd	*pWnd;				// Pointer auf das Objekt
		CRect	rect;				// Original-Position und Größe des Objekts
		int		lAttachment;		// Linke  Orientierung des Objekts
		int		rAttachment;		// Rechte Orientierung des Objekts
		int		tAttachment;		// Obere  Orientierung des Objekts
		int		bAttachment;		// Untere Orientierung des Objekts

	public:
		XObject()					{}
		XObject(CWnd *pObject, CRect rect, int lAtt, int rAtt, int tAtt, int bAtt);

	public:
		void Resize(int newWidth, int newHeight, int oldWidth, int oldHeight);
	};

protected:
	CWnd		*pParent;						// Vaterobjekt (Dialogobjekt)
	CSize		size;							// Originalgröße des Dialogs
	CMap<UINT, UINT, XObject, XObject&>	objects;// Für jedes Element ein XObjekt

public:
	XConstraint()					{ pParent = NULL; }

public:
	void Set(CWnd *pWin);
	void Add(int ID, int l, int r, int t, int b);
	void Resize(int newWidth = -1, int newHeight = -1);
};

#endif // __CONSTRAINTS__
