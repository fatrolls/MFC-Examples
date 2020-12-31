// client.cpp  pseudo-OLE command-line application
#include <stdio.h>
#include <stddef.h> // for offsetof in METHOD_PROLOGUE
#include <assert.h>
#include "interface.h"


//----------main program-----------------------------------------------
int main() // simulates OLE client program
{
    TRACE("Entering client main\n");
    IUnknown* pUnk; // If you declare these void*, you lose type-safety
    IMotion* pMot;
    IVisual* pVis;
    IClassFactory* pClf; 
    
    GetClassObject(CLSID_CSpaceship, IID_IClassFactory,
                  (void**) &pClf); 

    pClf->CreateInstance(IID_IUnknown, (void**) &pUnk);
    pUnk->QueryInterface(IID_IMotion, (void**) &pMot); // All three
    pMot->QueryInterface(IID_IVisual, (void**) &pVis); //   pointers
                                                       //   should work
    TRACE("main: pUnk = %p, pMot = %p, pDis = %p\n", pUnk, pMot, pVis);
    
    // Test all the interface virtual functions
    pMot->Fly();
    int nPos = pMot->GetPosition();
    TRACE("nPos = %d\n", nPos);
    pVis->Display();

    pClf->Release();
    pUnk->Release();
    pMot->Release();
    pVis->Release();
    return 0;
}
