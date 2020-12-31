// Client.cpp

#include <windows.h>
#include <stdio.h>
#include "../../yacl/include/hrx.h"
#include "../../yacl/include/smartif.h"
#include "../../yacl/include/ComInit.h"
#include "..\MeowMoniker.h"
#include "..\Base64.h"

#define DIM(rg) (sizeof(rg)/sizeof(*rg))

HRESULT TestBase64(int nIterations, bool bVerbose = false);
HRESULT TestMoniker();

void main()
{
    //TestBase64(1000);
    TestMoniker();
}

HRESULT TestMoniker()
{
    COM_TRY
    {
        CComInit    com;
        HRX         hrx;

        // Create
        SI(IUnknown)    punk1;
        hrx = punk1.CreateInstance(L"ComCourse.CoPoint", CLSCTX_LOCAL_SERVER);

        HINSTANCE               hinstDll = LoadLibrary("MeowMoniker.dll");
        if( !hinstDll ) hrx = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WINDOWS, GetLastError());

        PFNCREATEMEOWMONIKER    CreateMeowMoniker = (PFNCREATEMEOWMONIKER)GetProcAddress(hinstDll, "CreateMeowMoniker");
        if( !CreateMeowMoniker ) hrx = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WINDOWS, GetLastError());

        SI(IMoniker)    pmk;
        hrx = CreateMeowMoniker(punk1.Itf(),
                                IID_IUnknown,
                                MSHCTX_DIFFERENTMACHINE,
                                MSHLFLAGS_NORMAL,
                                pmk.RelItfRef());

        // Display
        SI(IBindCtx)    pbc;
        hrx = CreateBindCtx(0, pbc.RelItfRef());

        wchar_t*    pwszDisplayName;
        hrx = pmk->GetDisplayName(pbc.Itf(), 0, &pwszDisplayName);
        wprintf(L"DisplayName1 (%d)= %s\n",
                wcslen(pwszDisplayName), pwszDisplayName);

        printf("I'm pausing. Give me a character to satisfy scanf(): ");
        int x;
        scanf("%d", &x);

        // Bind
        SI(IUnknown)    punk2;
        hrx = pmk->BindToObject(pbc.Itf(), 0, IID_PPV(punk2));

        // Check
        if( punk1 == punk2 )
        {
            printf("Wahoo!\n");
        }
        else
        {
            printf("Waa, waa, waaaaaa...\n");
        }

        // Parse
        SI(IBindCtx)    pbc2;
        hrx = CreateBindCtx(0, pbc2.RelItfRef());

        SI(IMoniker)    pmk2;
        ULONG           cchEaten;
        hrx = MkParseDisplayName(pbc2.Itf(),
                                 pwszDisplayName,
                                 &cchEaten,
                                 pmk2.RelItfRef());

        // Bind again
        SI(IUnknown)    punk3;
        hrx = pmk2->BindToObject(pbc2.Itf(), 0, IID_PPV(punk3));

        // Check
        if( punk1 == punk3 )
        {
            printf("Wahoo!\n");
        }
        else
        {
            printf("Waa, waa, waaaaaa...\n");
        }

        CoTaskMemFree(pwszDisplayName);
    }
    COM_CATCH
}

HRESULT TestBase64(int nIterations, bool bVerbose)
{
    COM_TRY
    {
        HRX hrx;
            
        srand(GetTickCount());
        BYTE    rgb[4096];
        BYTE    rgb2[4096];
        char    sz[(DIM(rgb)+2)/3*4+1]; // Round up

        // Fill in a random buffer with random bytes
        for( int i = 0; i < DIM(rgb); i++ )
        {
            rgb[i] = rand()%256;
        }
        
        DWORD   nStart = GetTickCount();
        
        for( i = 0; i < nIterations; i++ )
        {
            size_t  nRawSize = rand()%DIM(rgb);
            size_t  nEncodedLen = (nRawSize+2)/3 * 4;   // Round up
            
            hrx = BufferEncode64(sz, nEncodedLen, rgb, nRawSize);
            sz[nEncodedLen] = 0;
            
            //printf("Encoded= %s\n", psz);
            
            // Decode and check
            hrx = BufferDecode64(rgb2, &nRawSize, sz, nEncodedLen);
            
            if( memcmp(rgb, rgb2, nRawSize) == 0 )
            {
                if( bVerbose )
                    printf("It worked with %d bytes!\t(remainder= %d)\n",
                    nRawSize, nRawSize%3);
            }
            else
            {
                if( bVerbose )
                    printf("It failed with %d bytes!\n", nRawSize);
                hrx = E_FAIL;
            }
        }

        DWORD   nEnd = GetTickCount();
        printf("%d iterations = %d ms (%f ms/iteration)\n",
               nIterations, nEnd - nStart, (nEnd - nStart)/double(nIterations));
    }
    COM_CATCH;
}

