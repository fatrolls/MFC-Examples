// ColorEditWnd syntax coloring class
//

#include "stdafx.h"
#include "ColorEditWnd.h"
;;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_LL 1024
#define MIN_X 10

/////////////////////////////////////////////////////////////////////////////
// ColorEditWnd

BEGIN_MESSAGE_MAP(ColorEditWnd, CWnd)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_GETDLGCODE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorEditWnd construction/destruction

ColorEditWnd::ColorEditWnd(CWnd * parent, CRect & rect,
	int nID, CString &keywordsFile, BOOL caseSensitive)
{
	CharDX = 9;
	CharDY = 13;
	TAB_SIZE = 4;
	cColorize = new Colorize(keywordsFile, caseSensitive);
	cCaseSensitive = caseSensitive;
	cfont.CreatePointFont(100,"Courier New",NULL);
	Create(NULL, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN |
			WS_VSCROLL | WS_HSCROLL,
			rect, parent, nID, NULL);
	SetScrollRange(SB_HORZ,0,200,FALSE);
	SetScrollRange(SB_VERT,0,200,FALSE);
	Reset();
}

ColorEditWnd::ColorEditWnd(CWnd * parent, CRect & rect,
	int nID, CString &keywordsFile, BOOL caseSensitive, 
	long pCharDX, long pCharDY, long pTabSize,
	int pFontSize, CString pFontName)
{
	CharDX = pCharDX;
	CharDY = pCharDY;
	TAB_SIZE = pTabSize;
	cColorize = new Colorize(keywordsFile, caseSensitive);
	cCaseSensitive = caseSensitive;
	cfont.CreatePointFont(pFontSize,pFontName,NULL);
	Create(NULL, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN |
			WS_VSCROLL | WS_HSCROLL,
			rect, parent, nID, NULL);
	SetScrollRange(SB_HORZ,0,200,FALSE);
	SetScrollRange(SB_VERT,0,200,FALSE);
	Reset();
}

void ColorEditWnd::Reset()
{
	cTheText.RemoveAll();
	cTheText.cCursorX = 0;
	cTheText.cCursorY = 0;
	cTheText.cAnchorX = 0;
	cTheText.cAnchorY = 0;
	cTheText.cViewX = 0;
	cTheText.cViewY = 0;
	cTheText.cFirstCharacter = 0;
	cTheText.cFirstLine = 0;
	cWasHilighted = FALSE;
	cLeftDown = FALSE;
	cIgnoreCtl = FALSE;
	cCaretOn = FALSE;
	cTheText.SetAtGrow(cTheText.cCursorY,"");
}

void ColorEditWnd::LoadText(CString &pText)
{
	Reset();
	long index;
	CString temp;
	for(index = 0; index < pText.GetLength(); index++)
	{
		if(pText.GetAt(index) == 13)
			pText.SetAt(index,'\n');
		if(pText.GetAt(index) == 9)
			pText.SetAt(index,char(32));
	}
	while(pText.GetLength())
	{
		temp = pText.SpanExcluding("\n");
		temp.TrimRight();
		cTheText.SetAtGrow(cTheText.cCursorY,temp);
		cTheText.cCursorY++;
		pText = pText.Right(pText.GetLength() - (temp.GetLength()+1));
	}
	cTheText.cCursorX = 0;
	cTheText.cCursorY = 0;
	cTheText.cAnchorX = 0;
	cTheText.cAnchorY = 0;
	cTheText.cViewX = 0;
	cTheText.cFirstCharacter = 0;
	cTheText.cFirstLine = 0;
	cTheText.cViewY = 0;
	cWasHilighted = FALSE;
	cLeftDown = FALSE;
	cIgnoreCtl = FALSE;
}

void ColorEditWnd::UnloadText(CString &pText)
{
	long index;
	pText.Empty();
	for(index = 0; index < cTheText.GetSize(); index++)
	{
		pText = pText + cTheText[index];
		pText = pText + '\n';
	}
}

ColorEditWnd::~ColorEditWnd()
{
	delete cColorize;
}

CScriptText & CScriptText::operator = (CScriptText & source)
{
	cFirstCharacter = source.cFirstCharacter;
	cFirstLine = source.cFirstLine;
	cViewX = source.cViewX;
	cViewY = source.cViewY;
	cAnchorX = source.cAnchorX;
	cAnchorY = source.cAnchorY;
	cCursorX = source.cCursorX;
	cCursorY = source.cCursorY;
	RemoveAll();
	int loop;
	for(loop = 0; loop < source.GetSize(); loop++)
	{
		Add(source.GetAt(loop));
	}
	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// ColorEditWnd drawing

void ColorEditWnd::OnPaint()
{
	CDC* pDC;
	PAINTSTRUCT ps;
	pDC = BeginPaint(&ps);
	pDC->SelectObject(cfont);
	pDC->SetBkMode(TRANSPARENT);
	long x;
	long y = 0;
	long p;
	CString temp;
	CTypedPtrArray<CPtrArray, void*> pColors;
	CRect client;
	GetClientRect(client);
	for(p=cTheText.cFirstLine; p<min(cTheText.GetSize(), 
		cTheText.cFirstLine + (client.Height() / CharDY +1)); p++)
	{
		x  = MIN_X;
		temp = cTheText[p];
		cColorize->SetLineColors(temp,pColors);
		int j;
		for(j=cTheText.cFirstCharacter; j<temp.GetLength(); j++)
		{
			pDC->SetTextColor((COLORREF)(pColors[j]));
			if(IsHilighted(j,p))
			{
				pDC->FillSolidRect(CRect(x,y,x+CharDX,y+CharDY),
					RGB(180,180,255));
			}
			else
			{
				pDC->FillSolidRect(CRect(x,y,x+CharDX,y+CharDY),
					RGB(255,255,255));
			}
			pDC->TextOut(x,y,temp[j]);
			x+=CharDX;
		}
		y+=CharDY;
	}
	DrawCursor(pDC,TRUE);
	EndPaint(&ps);
	ReleaseDC(pDC);
}


void ColorEditWnd::DrawLine()
{
	DrawLine(cTheText.cCursorY);
}

void ColorEditWnd::DrawLine(long pLine)
{
	if(pLine < cTheText.cFirstLine) return;
	if(pLine > cTheText.GetUpperBound()) return;
	CClientDC dc(this);
	dc.SelectObject(cfont);
	long x;
	long y;
	long p;
	CString temp;
	CTypedPtrArray<CPtrArray, void*> pColors;
	x = MIN_X;
	y = pLine * CharDY - cTheText.cFirstLine;
	p = pLine;
	temp = cTheText[p];
	cColorize->SetLineColors(temp,pColors);
	int j;
	for(j=cTheText.cFirstCharacter; j<temp.GetLength(); j++)
	{
		dc.SetTextColor((COLORREF)(pColors[j]));
		if(IsHilighted(j,p))
		{
			dc.FillSolidRect(CRect(x,y,x+CharDX,y+CharDY),
				RGB(180,180,255));
		}
		else
		{
			dc.FillSolidRect(CRect(x,y,x+CharDX,y+CharDY),
				RGB(255,255,255));
		}
		dc.TextOut(x,y,temp[j]);
		x+=CharDX;
	}
	CRect client;
	GetClientRect(client);
	client.left = x;
	client.top = y;
	client.bottom = y + CharDY;
	dc.FillSolidRect(client,RGB(255,255,255));
}


/////////////////////////////////////////////////////////////////////////////
// ColorEditWnd message handlers

void ColorEditWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar == 16) return; //ignore all shift keys
	if(!cIgnoreCtl)
	{
		int ctrl = GetKeyState(VK_CONTROL);
		if(ctrl & 0xf0 ) //control key down
		{
			TRACE("%d\n",nChar);
			switch(nChar)
			{
			case 88: //Cut (fall through)
			case 67: //Copy
				{
					DoCopy();
				}
				if(nChar == 88)
				{
					if(Hilight()) RemoveHilighted();
				}
				break;
			case 86: //paste
				{
					DoPaste();
				}
				break;
			default:
				break;
			}
			return;
		}
	}
	DrawCursor(FALSE);
	switch(nChar)
	{
	case 9: //tab key
		{
			if(!(cTheText.cCursorX % TAB_SIZE))
			{ OnKeyDown(32,nRepCnt,nFlags); }
			while(cTheText.cCursorX % TAB_SIZE)
			{ OnKeyDown(32,nRepCnt,nFlags); }
		}
		break;
	case 35: //end
		cTheText.cCursorX = cTheText[cTheText.cCursorY].GetLength();
		UpdateAnchor(TRUE);
		break;
	case 36: //home
		cTheText.cCursorX = 0;
		UpdateAnchor(TRUE);
		break;
	case 37: //left arrow
		cTheText.cCursorX--;
		if(cTheText.cCursorX < 0)
		{
			if(cTheText.cCursorY >0)
			{
				cTheText.cCursorY--;
				cTheText.cCursorX = cTheText[cTheText.cCursorY].GetLength();
			}
			else
			{
				cTheText.cCursorX = 0;
			}
		}
		UpdateAnchor(TRUE);
		break;
	case 38: //up arrow
		if(cTheText.cCursorY > 0)
		{
			cTheText.cCursorY--;
			cTheText.cCursorX = min(cTheText.cCursorX,cTheText[cTheText.cCursorY].GetLength());
		}
		UpdateAnchor(TRUE);
		break;
	case 39: //right arrow
		cTheText.cCursorX++;
		if(cTheText.cCursorX > cTheText[cTheText.cCursorY].GetLength())
		{
			if(cTheText.cCursorY < cTheText.GetUpperBound())
			{
				cTheText.cCursorY++;
				cTheText.cCursorX = 0;
			}
			else
			{
				cTheText.cCursorX--;
			}
		}
		UpdateAnchor(TRUE);
		break;
	case 40: //down arrow
		if(cTheText.cCursorY < cTheText.GetUpperBound())
		{
			cTheText.cCursorY++;
			cTheText.cCursorX  = min(cTheText.cCursorX,cTheText[cTheText.cCursorY].GetLength());
		}
		UpdateAnchor(TRUE);
		break;
	case 13: //return (enter)
		{
			if(Hilight()) RemoveHilighted();
			CString temp;
			temp = 	cTheText[cTheText.cCursorY].Right(
				cTheText[cTheText.cCursorY].GetLength()-cTheText.cCursorX);
			cTheText[cTheText.cCursorY] = cTheText[cTheText.cCursorY].Left(cTheText.cCursorX);
			cTheText.cCursorY ++;
			cTheText.cCursorX = 0;
			if(cTheText.cCursorY > 0)
			{
				int insert = 0;
				while(insert < cTheText[cTheText.cCursorY-1].GetLength())
				{
					if(cTheText[cTheText.cCursorY-1].GetAt(insert) != 32)
					{
						break;
					}
					insert++;
				}
				while(insert)
				{
					temp = " " + temp;
					insert--;
					cTheText.cCursorX++;
				}
			}
			cTheText.InsertAt(cTheText.cCursorY,temp);
			Invalidate();
		}
		UpdateAnchor(FALSE);
		break;
	case 8: //Backspace, delete prior character
		if(Hilight()) RemoveHilighted();
		OnKeyDown(37, nRepCnt, nFlags);
		DeleteChar();
		break;
	case 46: //Delete, delete following character
		if(Hilight()) RemoveHilighted();
		DeleteChar();
		break;
	default:
		{
			if(Hilight()) RemoveHilighted();
			int charval = nChar;
			if(charval > 127) //punctuation and stuff
			{
				int shift = GetKeyState(VK_SHIFT);
				int caps = GetKeyState(VK_CAPITAL);
				if(!(shift & 0xf0 || caps & 0x01)) //unshifted
				{
					switch(charval)
					{
					//top row
					case 192: //` ~
						charval = '`';
						break;
					case 189: //- _
						charval = '-';
						break;
					case 187: //= +
						charval = '=';
						break;
					//2nd row
					case 219: //[ {
						charval = '[';
						break;
					case 221: //] }
						charval = ']';
						break;
					case 220: //\ |
						charval = '\\';
						break;
					//3d row
					case 186: //; :
						charval = ';';
						break;
					case 222: //' "
						charval = 39;
						break;
					//4th row
					case 188: //, >
						charval = ',';
						break;
					case 190: //. >
						charval = '.';
						break;
					case 191: // / ?
						charval = '/';
						break;
					default:
						charval = 32;
					}
				}
				else //shifted
				{
					switch(charval)
					{
					//top row
					case 192: //` ~
						charval = '~';
						break;
					case 189: //- _
						charval = '_';
						break;
					case 187: //= +
						charval = '+';
						break;
					//2nd row
					case 219: //[ {
						charval = '{';
						break;
					case 221: //] }
						charval = '}';
						break;
					case 220: //\ |
						charval = '|';
						break;
					//3d row
					case 186: //; :
						charval = ':';
						break;
					case 222: //' "
						charval = '"';
						break;
					//4th row
					case 188: //, <
						charval = '<';
						break;
					case 190: //. >
						charval = '>';
						break;
					case 191: // / ?
						charval = '?';
						break;
					default:
						charval = 32;
					}
				}
				InsertChar(charval);
			}
			else
			{
				//A-Z and a-z
				if((charval < 91) && (charval > 64))
				{
					int shift = GetKeyState(VK_SHIFT);
					int caps = GetKeyState(VK_CAPITAL);
					if(!(shift & 0xf0 || caps & 0x01)) //unshifted
					{
						charval = nChar + 32;
					}	
					InsertChar(charval);
				}
				//0 through 9
				if((charval < 58) && (charval > 47))
				{
					int shift = GetKeyState(VK_SHIFT);
					int caps = GetKeyState(VK_CAPITAL);
					if((shift & 0xf0 || caps & 0x01)) //shifted
					{
						switch(charval)
						{
						case 48: //0
							charval = ')';
							break;
						case 49: //1
							charval = '!';
							break;
						case 50: //2
							charval = '@';
							break;
						case 51: //3
							charval = '#';
							break;
						case 52: //4
							charval = '$';
							break;
						case 53: //5
							charval = '%';
							break;
						case 54: //6
							charval = '^';
							break;
						case 55: //7
							charval = '&';
							break;
						case 56: //8
							charval = '*';
							break;
						case 57: //9
							charval = '(';
							break;
						}
					}	
					InsertChar(charval);
				}
				//space
				else if(charval == 32)
				{
					InsertChar(32);
				}
			}
			break;
		}
	}
	if(Hilight())
	{
		long i;
		for(i=min(cTheText.cAnchorY, cTheText.cCursorY)-1; i<=max(cTheText.cAnchorY, cTheText.cCursorY)+1; i++)
		{
			DrawLine(i);
		}
	}
	DrawCursor(TRUE);
}

void ColorEditWnd::InsertChar(int pChar)
{
	InsertChar(pChar,TRUE);
}

void ColorEditWnd::InsertChar(int pChar, BOOL pRedraw)
{
	CString str = char(pChar);
	InsertString(str,pRedraw);
}

//delete the following character
void ColorEditWnd::DeleteChar()
{
	if(cTheText.cCursorX >= cTheText[cTheText.cCursorY].GetLength())
	{
		if(cTheText.cCursorY < cTheText.GetUpperBound())
		{
			cTheText[cTheText.cCursorY] = cTheText[cTheText.cCursorY] + cTheText[cTheText.cCursorY+1];
			cTheText.RemoveAt(cTheText.cCursorY + 1); 
			Invalidate();
		}

	}
	else
	{
		cTheText[cTheText.cCursorY] = cTheText[cTheText.cCursorY].Left(cTheText.cCursorX) + 
			cTheText[cTheText.cCursorY].Right(
			cTheText[cTheText.cCursorY].GetLength()-(cTheText.cCursorX+1));
	}
	UpdateAnchor(FALSE);
	DrawLine();
}

void ColorEditWnd::InsertString(CString &pString)
{
	InsertString(pString,TRUE);
}
void ColorEditWnd::InsertString(CString &pString,BOOL pRedraw)
{
	cTheText[cTheText.cCursorY] = cTheText[cTheText.cCursorY].Left(cTheText.cCursorX) + 
		pString + cTheText[cTheText.cCursorY].Right(
		cTheText[cTheText.cCursorY].GetLength()-cTheText.cCursorX);
	cTheText.cCursorX++;
	UpdateAnchor(FALSE);
	if(pRedraw) DrawLine();
}

void ColorEditWnd::DrawCursor(BOOL pShow)
{
	CClientDC dc(this);
	DrawCursor(&dc, pShow);
}

void ColorEditWnd::DrawCursor(CDC * pDC, BOOL pShow)
{
	CRect rect;
	rect.left = ((cTheText.cCursorX - cTheText.cFirstCharacter) * CharDX) - 1;
	rect.right = rect.left + 2;
	rect.top = ((cTheText.cCursorY- cTheText.cFirstLine) * CharDY) - 1;
	rect.bottom = rect.top + CharDY + 1;
	rect.left += MIN_X;
	rect.right += MIN_X;
	if(pShow)
	{
//		pDC->FillSolidRect(rect,RGB(0,100,255));
		if(!cCaretOn)
		{
			ShowCaret();
			cCaretOn = TRUE;
		}
		SetCaretPos(CPoint(rect.left,rect.top));
	}
	else
	{
//		pDC->FillSolidRect(rect,RGB(255,255,255));
		if(cCaretOn)
		{
			HideCaret();
			cCaretOn = FALSE;
		}
		SetCaretPos(CPoint(rect.left,rect.top));
	}
}

void ColorEditWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//convert click to cursor position
	point.x -= MIN_X;
	cLeftDown = TRUE;
	SetFocus();
	DrawCursor(FALSE);
	cTheText.cCursorX = (point.x + CharDX/2) / CharDX + cTheText.cFirstCharacter;
	cTheText.cCursorY = point.y / CharDY + cTheText.cFirstLine;
	cTheText.cCursorY = min(cTheText.cCursorY,cTheText.GetUpperBound());
	cTheText.cCursorX = min(cTheText.cCursorX,cTheText[cTheText.cCursorY].GetLength());
	int shift = GetKeyState(VK_SHIFT);
	if(shift & 0xf0) //shifted
	{
		Invalidate(FALSE);
	}
	else //normal
	{
		cTheText.cAnchorX = cTheText.cCursorX;
		cTheText.cAnchorY = cTheText.cCursorY;
		Hilight();
	}
	DrawCursor(TRUE);
}

void ColorEditWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	point.x -= MIN_X;
	if(cLeftDown) //dragging to select
	{
		long oldX = cTheText.cCursorX;
		long oldY = cTheText.cCursorY;
		cTheText.cCursorX = (point.x + CharDX/2) / CharDX + cTheText.cFirstCharacter;
		cTheText.cCursorY = point.y / CharDY + cTheText.cFirstLine;
		cTheText.cCursorY = min(cTheText.cCursorY,cTheText.GetUpperBound());
		cTheText.cCursorX = min(cTheText.cCursorX,cTheText[cTheText.cCursorY].GetLength());
		if((oldX != cTheText.cCursorX) || (oldY != cTheText.cCursorY))
		{
			DrawCursor(FALSE);
			Invalidate(FALSE);
			DrawCursor(TRUE);
		}
	}
}

void ColorEditWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	point.x -= MIN_X;
	cLeftDown = FALSE;
}


BOOL ColorEditWnd::Hilight()
{
	BOOL cAmHilighted;
	if(cTheText.cAnchorX != cTheText.cCursorX)
	{
		cAmHilighted = TRUE;
	}
	else if(cTheText.cAnchorY != cTheText.cCursorY)
	{
		cAmHilighted = TRUE;
	}
	else
	{
		cAmHilighted = FALSE;
	}
	if(cAmHilighted != cWasHilighted)
	{
		cWasHilighted = cAmHilighted;
		Invalidate(FALSE);
	}
	return(cAmHilighted);
}

BOOL ColorEditWnd::IsHilighted(long pX,long pY)
{
	if(!Hilight())
	{
		return(FALSE);
	}
	else
	{
		long AnchorRowCol = cTheText.cAnchorX + cTheText.cAnchorY * MAX_LL;
		long CursorRowCol = (cTheText.cCursorX-1) + cTheText.cCursorY * MAX_LL;
		long TestRowCol = pX + pY * MAX_LL;
		if(AnchorRowCol < CursorRowCol)
		{
			if(TestRowCol < AnchorRowCol) return(FALSE);
			if(TestRowCol > CursorRowCol) return(FALSE);
		}
		else
		{
			if(TestRowCol < CursorRowCol+1) return(FALSE);
			if(TestRowCol > AnchorRowCol-1) return(FALSE);
		}
	}
	return(TRUE);
}

//remove the hilighted portion of the text
void ColorEditWnd::RemoveHilighted()
{
	long junkY;
	long junkX;
	//make sure the anchor is first
	if(cTheText.cCursorY < cTheText.cAnchorY)
	{
		junkY = cTheText.cCursorY;
		cTheText.cCursorY = cTheText.cAnchorY;
		cTheText.cAnchorY = junkY;
		junkX = cTheText.cCursorX;
		cTheText.cCursorX = cTheText.cAnchorX;
		cTheText.cAnchorX = junkX;
	}

	//if it is all one line then handle special
	if(cTheText.cCursorY == cTheText.cAnchorY)
	{
		if(cTheText.cCursorX < cTheText.cAnchorX)
		{
			junkX = cTheText.cCursorX;
			cTheText.cCursorX = cTheText.cAnchorX;
			cTheText.cAnchorX = junkX;
			cTheText[cTheText.cAnchorY] = cTheText[cTheText.cAnchorY].Left(cTheText.cAnchorX) +
				cTheText[cTheText.cAnchorY].Right(
				cTheText[cTheText.cAnchorY].GetLength()-(cTheText.cCursorX+1));
		}
	}
	//it is multiple lines
	else
	{
		//remove all whole lines between the two
		while(cTheText.cCursorY > cTheText.cAnchorY + 1)
		{
			cTheText.RemoveAt(cTheText.cAnchorY + 1);
			cTheText.cCursorY--;
		}

		//there are only two lines now
		//combine the two lines together
		cTheText[cTheText.cAnchorY] = cTheText[cTheText.cAnchorY].Left(cTheText.cAnchorX) +
			cTheText[cTheText.cCursorY].Right(
			cTheText[cTheText.cCursorY].GetLength()-(cTheText.cCursorX+1));

		//remove the second line
		cTheText.RemoveAt(cTheText.cCursorY);
		cTheText.cCursorY--;
	}

	cTheText.cCursorX = cTheText.cAnchorX;
	cTheText.cCursorY = cTheText.cAnchorY;
	Invalidate();
}

void ColorEditWnd::UpdateAnchor(BOOL pTestShift)
{
	if(pTestShift)
	{
		int shift = GetKeyState(VK_SHIFT);
		if(!(shift & 0xf0)) //not shifted
		{
			cTheText.cAnchorX = cTheText.cCursorX;
			cTheText.cAnchorY = cTheText.cCursorY;
		}
	}
	else
	{
		cTheText.cAnchorX = cTheText.cCursorX;
		cTheText.cAnchorY = cTheText.cCursorY;
	}
}

BOOL ColorEditWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect client;
	pDC->GetClipBox(&client);
	pDC->FillSolidRect(client,RGB(255,255,255));
	return TRUE;
}


//allow the control to get all keys
UINT ColorEditWnd::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

void ColorEditWnd::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	CRect client;
	GetClientRect(client);
	long window_height = client.Height()/CharDY; //in lines
	long total_height = cTheText.GetSize(); //in lines
	switch(nSBCode)
	{
	case SB_BOTTOM:			//Scroll to bottom.
		cTheText.cFirstLine = max(0,total_height - window_height);
		Invalidate();
		break;
	case SB_LINEDOWN:		//Scroll one line down.
		cTheText.cFirstLine += 1;
		Invalidate();
		break;
	case SB_PAGEDOWN:		//Scroll one page down.
		cTheText.cFirstLine += window_height * 3 / 4;
		Invalidate();
		break;
	case SB_LINEUP:			//Scroll one line up.
		cTheText.cFirstLine = max(0,cTheText.cFirstLine - 1);
		Invalidate();
		break;
	case SB_PAGEUP:			//Scroll one page up.
		cTheText.cFirstLine -= window_height * 3 / 4;
		cTheText.cFirstLine = max(0,cTheText.cFirstLine);
		Invalidate();
		break;
	case SB_THUMBPOSITION:	//Scroll to the absolute position. The current position is provided in nPos.
	case SB_THUMBTRACK:		//Drag scroll box to specified position. The current position is provided in nPos.
		cTheText.cFirstLine = nPos;
		Invalidate();
		break;
	case SB_TOP:			//Scroll to top.
		cTheText.cFirstLine = 0;
		Invalidate();
		break;
	case SB_ENDSCROLL:		//End scroll.
		break;
	default:
		break;
	}
	SetScrollPos(SB_VERT, cTheText.cFirstLine, TRUE );
}



void ColorEditWnd::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	CRect client;
	GetClientRect(client);
	long window_width = client.Width()/CharDX;	
	switch(nSBCode)
	{
	case SB_LEFT:			//Scroll to far left.
		cTheText.cFirstCharacter = 0;
		Invalidate();
		break;
	case SB_LINELEFT:		//Scroll left.
		cTheText.cFirstCharacter = max(0, cTheText.cFirstCharacter - 1);
		Invalidate();
		break;
	case SB_PAGELEFT:		//Scroll one page left.
		cTheText.cFirstCharacter -= window_width * 3 / 4;
		cTheText.cFirstCharacter = max(0, cTheText.cFirstCharacter);
		Invalidate();
		break;
	case SB_LINERIGHT:		//Scroll right one line.
		cTheText.cFirstCharacter += 1;
		Invalidate();
		break;
	case SB_PAGERIGHT:		//Scroll one page right.
		cTheText.cFirstCharacter += window_width * 3 / 4;
		Invalidate();
		break;
	case SB_RIGHT:			//Scroll to far right.
		Invalidate();
		break;
	case SB_THUMBPOSITION:	//Scroll to absolute position. The current position is specified by the nPos parameter.
	case SB_THUMBTRACK:		//Drag scroll box to specified position. The current position is specified by the nPos parameter.
		cTheText.cFirstCharacter = nPos;
		Invalidate();
		break;
	case SB_ENDSCROLL:		//End scroll.
	default:
		break;
	}
	SetScrollPos(SB_HORZ, cTheText.cFirstCharacter, TRUE );
}

void ColorEditWnd::Retab()
{
	int line;
	int index;
	int indent = 0;
	CString junk;
	CString word;
	char test;
	for(line=0; line<cTheText.GetSize(); line++)
	{
		junk = cTheText[line];
		junk.TrimLeft();
		junk.TrimRight();
		word.Empty();
		index = 0;
		while(index < junk.GetLength())
		{
			test = junk[index];
			if(cColorize->IsWhiteSpace(test)) break;
			word = word + test;
			index++;
		}
		index = indent;
		if(cColorize->IsTabPlusWord(word))
		{
			indent += TAB_SIZE;
		}
		else if(cColorize->IsTabMinusWord(word))
		{
			indent -= TAB_SIZE;
			if(indent < 0) indent = 0;
			index = indent;
		}
		while(index)
		{
			junk = " " + junk;
			index --;
		}
		cTheText[line] = junk;
	}
	cTheText.cCursorX = cTheText.cFirstCharacter;
	cTheText.cCursorY = cTheText.cFirstLine;
	Invalidate();
}

void ColorEditWnd::DoCopy()
{
	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		CString data;
		data.Empty();
		long StartX,StartY,EndX,EndY;
		long AnchorRowCol = cTheText.cAnchorX + cTheText.cAnchorY * MAX_LL;
		long CursorRowCol = (cTheText.cCursorX-1) + cTheText.cCursorY * MAX_LL;
		if(AnchorRowCol < CursorRowCol)
		{
			StartX = cTheText.cAnchorX;
			StartY = cTheText.cAnchorY;
			EndX = cTheText.cCursorX;
			EndY = cTheText.cCursorY;
		}
		else
		{
			StartX = cTheText.cCursorX;
			StartY = cTheText.cCursorY;
			EndX = cTheText.cAnchorX;
			EndY = cTheText.cAnchorY;
		}
		while(StartY < EndY)
		{
			while(StartX < cTheText[StartY].GetLength())
			{
				data = data + cTheText[StartY].GetAt(StartX);
				StartX++;
			}
			data = data + char(13);
			data = data + char(10);
			StartY++;
			StartX=0;
		}
		while(StartX < EndX)
		{
			data = data + cTheText[StartY].GetAt(StartX);
			StartX++;
		}
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, 
			data.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(data));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}
}

void ColorEditWnd::DoPaste()
{
	if(Hilight()) RemoveHilighted();
	char * buffer;
	OpenClipboard();
	buffer = (char*)GetClipboardData(CF_TEXT);
	CloseClipboard();
	long i;
	cIgnoreCtl = TRUE;
	for(i=0; i<strlen(buffer); i++)
	{
		if(buffer[i] > 31)
		{
			InsertChar(buffer[i],FALSE);
		}
		else if((buffer[i] == 13) || (buffer[i] == '\n'))
		{
			CString temp;
			temp = 	cTheText[cTheText.cCursorY].Right(
				cTheText[cTheText.cCursorY].GetLength()-cTheText.cCursorX);
			cTheText[cTheText.cCursorY] = cTheText[cTheText.cCursorY].Left(cTheText.cCursorX);
			cTheText.cCursorY ++;
			cTheText.cCursorX = 0;
			cTheText.InsertAt(cTheText.cCursorY,temp);
		}
		else if(buffer[i] == 9)
		{
			if(!(cTheText.cCursorX % TAB_SIZE))
			{ InsertChar(32,FALSE); }
			while(cTheText.cCursorX % TAB_SIZE)
			{ InsertChar(32,FALSE); }
		}
	}
	cIgnoreCtl = FALSE;
	Invalidate();
}


int ColorEditWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	cCaretOn = FALSE;
	cCursor = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
		
	return 0;
}


BOOL ColorEditWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CRect client;
	GetClientRect(client);
	CPoint cursorpt;
	GetCursorPos(&cursorpt);
	ScreenToClient(&cursorpt);
	if(client.PtInRect(cursorpt))
	{
		SetCursor(cCursor);
		return TRUE;		
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void ColorEditWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if(bShow)
	{
		if(!IsWindowVisible())
		{
			CreateSolidCaret(2,CharDY + 1);
			ShowCaret();
			cCaretOn = TRUE;			
		}
	}
	CWnd::OnShowWindow(bShow, nStatus);
}