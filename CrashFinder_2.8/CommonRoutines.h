/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/

#ifndef _COMMONROUTINES_H
#define _COMMONROUTINES_H

#include "SymbolEngine.h"
#include "BinaryImage.h"

// The image list bitmap dimensions.
#define BITMAP_WIDTH    16
#define BITMAP_HEIGHT   15

// The defines for the validated and loaded states that are shown in the
// tree.
#define STATE_NOTVALID      0
#define STATE_VALIDATED     1
// Defines the information state for child nodes.
#define STATE_INFO          2

// LookUpAddressInformation return values.
typedef enum tagELURES
{
    eLUFAILED   = 0x0 ,
    eLUMOD      = 0x1 ,
    eLUSYM      = 0x2 ,
    eLULINE     = 0x4
} ELURES ;

/*----------------------------------------------------------------------
FUNCTION        :   InitializeSymbolEngine
DISCUSSION      :
    Initializes the symbol engine for full functionality in any
CrashFinder document.
PARAMETERS      :
    cSymEng - The symbol engine to initialize.
RETURNS         :
    FALSE - The was a problem initializing.
    TRUE  - Everything is initialized just hunky dory.
----------------------------------------------------------------------*/
BOOL InitializeSymbolEngine ( CSymbolEngine & cSymEng ) ;

/*----------------------------------------------------------------------
FUNCTION        :   LookUpAddressInformation
DISCUSSION      :
    Takes care of looking up the symbol information using the specified
symbol engine.
PARAMETERS      :
    cSymEng    - The symbol engine to use.
    dwAddr     - The address to look up.
    sModule    - On return, the module with the address.
    stIHSym    - On return, the symbol information.
    dwFnDispl  - On return, the function displacement.
    stIHLine   - On return, the line information.
    dwSrcDispl - On return, the source line displacement.
RETURNS         :
    Returns the ELURES enumeration bitfields indicating what exactly was
found for the address.
----------------------------------------------------------------------*/
int LookUpAddressInformation ( CSymbolEngine &     cSymEng    ,
                               DWORD64             dwAddr     ,
                               CString &           sModule    ,
                               IMAGEHLP_SYMBOL64 & stIHSym    ,
                               DWORD64 &           dwFnDispl  ,
                               IMAGEHLP_LINE64 &   stIHLine   ,
                               DWORD &             dwSrcDispl  ) ;

/*----------------------------------------------------------------------
FUNCTION        :   GetAddressSymbolString
DISCUSSION      :
    Looks up an address and plops the properly formatted string (based
on the applications global options) into strOutString.
PARAMETERS      :
    cSymEng      - The symbol engine to use.
    dwAddr       - The address to look up.
    strOutString - On return, the formatted string.
    szSeparators - The item separators to use.
RETURNS         :
    FALSE - The was a problem initializing.
    TRUE  - Everything is initialized just hunky dory.
----------------------------------------------------------------------*/
BOOL GetAddressSymbolString ( CSymbolEngine & cSymEng       ,
                              DWORD64         dwAddr        ,
                              CString &       strOutString  ,
                              LPCTSTR         szSeparators    ) ;

class CrashFinderTreeDisplay
{
////////////////////////////////////////////////////////////////////////
//                Public Construction and Desctruction
////////////////////////////////////////////////////////////////////////
public      :
    CrashFinderTreeDisplay ( void )
    {
        m_pSymEng = NULL ;
        m_pTree = NULL ;
        m_pFont = NULL ;
    }

    virtual ~CrashFinderTreeDisplay ( void )
    {
        if ( NULL != m_pFont )
        {
            delete m_pFont ;
        }
    }


////////////////////////////////////////////////////////////////////////
//                        Public Initialization
////////////////////////////////////////////////////////////////////////
public      :
    /*------------------------------------------------------------------
    FUNCTION        :   InitializeTreeControl
    DISCUSSION      :
        Initializes a tree control so it looks the same no matter who
        uses it in the CrashFinder program.
    PARAMETERS      :
        pTree   - The CTreeControl to initialize.
        cSymEng - The symbol engine to use.
    RETURNS         :
        The font used to initialize the tree control.  This must be kept
        and deleted on destruction by the caller.
    ------------------------------------------------------------------*/
    BOOL InitializeTreeControl ( CTreeCtrl *     pTree   ,
                                 CSymbolEngine * pSymEng  ) ;

////////////////////////////////////////////////////////////////////////
//                      Public Tree Manipulation
////////////////////////////////////////////////////////////////////////
public      :
    /*------------------------------------------------------------------
    FUNCTION        :   InsertImageInTree
    DISCUSSION      :
        Inserts the specified image to the tree control.  This also
    takes care of all the child nodes as well.
    PARAMETERS      :
        pImage     - The image to add.
        iState     - The imagelist item to use.
        hItemAfter - The item to insert after.
    RETURNS         :
        FALSE - The was a problem inserting the item.
        TRUE  - Everything is hunky dory.
    ------------------------------------------------------------------*/
    BOOL InsertImageInTree ( CBinaryImage *  pImage                ,
                             int             iState                ,
                             HTREEITEM       hItemAfter = TVI_LAST  ) ;

    /*------------------------------------------------------------------
    FUNCTION        :   InsertImageStatsIntoTree
    DISCUSSION      :
        Add the image statistics to the particular parent item.
    PARAMETERS      :
        hParent  - The parent item.
        pImage   - The image stats.
    RETURNS         :
        FALSE - The was a problem inserting the item.
        TRUE  - Everything is hunky dory.
    ------------------------------------------------------------------*/
    BOOL InsertImageStatsIntoTree ( HTREEITEM      hParent  ,
                                    CBinaryImage * pImage    ) ;


    /*------------------------------------------------------------------
    FUNCTION        :   DeleteImageStatsFromTree
    DISCUSSION      :
        Removes all the image stat items.
    PARAMETERS      :
        hParent - The parent item.
    RETURNS         :
        FALSE - The was a problem inserting the item.
        TRUE  - Everything is hunky dory.
    ------------------------------------------------------------------*/
    BOOL DeleteImageStatsFromTree ( HTREEITEM hParent ) ;

    /*------------------------------------------------------------------
    FUNCTION        :   UpdateImageStats
    DISCUSSION      :
        Updates the particular item's image stats.
    PARAMETERS      :
        hParent          - The parent item.
        pImage           - The image to update.
        bPrevWasGoodLoad - Did the previous insertion show all items?
    RETURNS         :
        FALSE - The was a problem inserting the item.
        TRUE  - Everything is hunky dory.
    ------------------------------------------------------------------*/
    BOOL UpdateImageStats ( HTREEITEM       hParent          ,
                            CBinaryImage *  pImage           ,
                            BOOL            bPrevWasGoodLoad  ) ;


////////////////////////////////////////////////////////////////////////
//                       Protected Data Members
////////////////////////////////////////////////////////////////////////
protected   :

    // The tree control to use.
    CTreeCtrl * m_pTree ;

    // The symbol engine to use.
    CSymbolEngine * m_pSymEng ;

    // The symbol engine font.
    CFont * m_pFont ;
} ;

#endif  // _COMMONROUTINES_H
