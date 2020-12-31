#ifndef _MEMDC_H_
#define _MEMDC_H_

//////////////////////////////////////////////////
// CMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// This class implements a memory Device Context


class CMemDC2 : public CDC
{
public:

    // constructor sets up the memory DC
    CMemDC2(CDC* pDC) : CDC()
    {
        ASSERT(pDC != NULL);

        m_pDC = pDC;
        m_pOldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();
              
        if (m_bMemDC)    // Create a Memory DC
        {
            pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
            SetWindowOrg(m_rect.left, m_rect.top);
        }
        else        // Make a copy of the relevent parts of the current DC for printing
        {
            m_bPrinting = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
    }
    
    // Destructor copies the contents of the mem DC to the original DC
    ~CMemDC2()
    {
        if (m_bMemDC) 
        {    
            // Copy the offscreen bitmap onto the screen.
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);

            //Swap back the original bitmap.
            SelectObject(m_pOldBitmap);
        } else {
            // All we need to do is replace the DC with an illegal value,
            // this keeps us from accidently deleting the handles associated with
            // the CDC that was passed to the constructor.
            m_hDC = m_hAttribDC = NULL;
        }
    }

    // Allow usage as a pointer
    CMemDC2* operator->() {return this;}
        
    // Allow usage as a pointer
    operator CMemDC2*() {return this;}

private:
    CBitmap  m_bitmap;      // Offscreen bitmap
    CBitmap* m_pOldBitmap;  // bitmap originally found in CMemDC2
    CDC*     m_pDC;         // Saves CDC passed in constructor
    CRect    m_rect;        // Rectangle of drawing area.
    BOOL     m_bMemDC;      // TRUE if CDC really is a Memory DC.
};

class CMemDC : public CDC {
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_oldBitmap;
	CDC*		m_pDC;
	CRect		m_rcBounds;
public:
	CMemDC(CDC* pDC, const CRect& rcBounds) : CDC()
	{
		CreateCompatibleDC(pDC);
		m_bitmap = new CBitmap;
		m_bitmap->CreateCompatibleBitmap(pDC, rcBounds.Width(), rcBounds.Height());
		m_oldBitmap = SelectObject(m_bitmap);
		m_pDC = pDC;
		m_rcBounds = rcBounds;
	}
	void KillDC(){m_pDC = NULL;}
	~CMemDC() 
	{
		if(m_pDC)
			m_pDC->BitBlt(m_rcBounds.left, m_rcBounds.top, m_rcBounds.Width(), m_rcBounds.Height(), 
					this, m_rcBounds.left, m_rcBounds.top, SRCCOPY);
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) delete m_bitmap;
	}
	CMemDC* operator->() {
		return this;
	}
};

class CMemDCCtrl : public CDC
{
public:
	
	// constructor sets up the memory DC
	CMemDCCtrl(CDC* pDC) : CDC()
    {
		ASSERT(pDC != NULL);
		
		m_pDC = pDC;
		m_pOldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();
		
        if (m_bMemDC)	// Create a Memory DC
		{
            pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_pOldBitmap = SelectObject(&m_bitmap);
            SetWindowOrg(m_rect.left, m_rect.top);
        }
		else		// Make a copy of the relevent parts of the current DC for printing
		{
            m_bPrinting = pDC->m_bPrinting;
            m_hDC		= pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
	}
	
	// Destructor copies the contents of the mem DC to the original DC
	~CMemDCCtrl()
    {
		if (m_bMemDC) {	
			// Copy the offscreen bitmap onto the screen.
			m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				this, m_rect.left, m_rect.top, SRCCOPY);
			
            //Swap back the original bitmap.
            SelectObject(m_pOldBitmap);
		} else {
			// All we need to do is replace the DC with an illegal value,
			// this keeps us from accidently deleting the handles associated with
			// the CDC that was passed to the constructor.
            m_hDC = m_hAttribDC = NULL;
		}
	}
	
	// Allow usage as a pointer
    CMemDCCtrl* operator->() {return this;}
	
    // Allow usage as a pointer
    operator CMemDCCtrl*() {return this;}

private:
	CBitmap  m_bitmap;		// Offscreen bitmap
    CBitmap* m_pOldBitmap;	// bitmap originally found in CMemDC
    CDC*     m_pDC;			// Saves CDC passed in constructor
    CRect    m_rect;		// Rectangle of drawing area.
    BOOL     m_bMemDC;		// TRUE if CDC really is a Memory DC.
};


/**********************************************************************/

class CMemDC3 : public CDC {
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_oldBitmap;
	CDC*		m_pDC;
	CRect		m_rcBounds;
public:
	CMemDC3(CDC* pDC, const CRect& rcBounds) : CDC()
	{
		CreateCompatibleDC(pDC);
		m_bitmap = new CBitmap;
		m_bitmap->CreateCompatibleBitmap(pDC, rcBounds.Width(), rcBounds.Height());
		m_oldBitmap = SelectObject(m_bitmap);
		m_pDC = pDC;
		m_rcBounds = rcBounds;
	}
	void KillDC(){m_pDC = NULL;}
	~CMemDC3() 
		{
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) delete m_bitmap;
		}
	CMemDC3* operator->() 
		{
		return this;
	}
};

#endif
