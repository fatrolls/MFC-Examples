// NWaveio.cpp: implementation of the NWaveio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NWaveio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


int NWaveIO::OpenReadWaveFile(LPSTR pszFileName,          
	                          HMMIO *phmmioIn,            
	                          WAVEFORMATEX **ppwfxInfo,   
	                          MMCKINFO *pckInRIFF)
{

	HMMIO           hmmioIn;
	MMCKINFO        ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT   pcmWaveFormat;  // Temp PCM structure to load in.       
	WORD            dwExtraAlloc;   // Extra bytes for waveformatex 
	int             nError;         // Return value.
	CException		except(FALSE);


	// Initialization...
	*ppwfxInfo = NULL;
	nError = ERR_NONE;
	hmmioIn = NULL;

	try
    {
	    //Open the wave file 
		hmmioIn = ::mmioOpen(pszFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);

	    if(hmmioIn == NULL)
		{
		    nError = ERR_CANNOTOPEN;
			throw &except;
		}

		if(::mmioDescend(hmmioIn, pckInRIFF, NULL, 0) != 0)
		{
            nError = ERR_FAILDESCEND; 
		    throw &except;
		}


	    if((pckInRIFF->ckid != FOURCC_RIFF) || 
		   (pckInRIFF->fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		{
		    nError = ERR_NOTWAVEFILE;
		    throw &except;
		}
			
	    // Search the input file for for the 'fmt ' chunk.     
        ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
        if(::mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK) 
			!= 0)
		{
            nError = ERR_FAILDESCEND; 
		    throw &except;
		}
					
	
		// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
        // if there are extra parameters at the end, we'll ignore them 
        if(ckIn.cksize < (long)sizeof(PCMWAVEFORMAT))
		{
		    nError = ERR_NOTWAVEFILE;
		    throw &except;
		}
															
	
		// Read the 'fmt ' chunk into <pcmWaveFormat>.
        if(::mmioRead(hmmioIn, (HPSTR)&pcmWaveFormat, (long) sizeof(pcmWaveFormat)) 
		   != (long) sizeof(pcmWaveFormat))
		{
		    nError = ERR_CANNOTREAD;
		    throw &except;
		}
							

	    // Allocate the waveformatex, but if its not pcm
	    // format, read the next word, and thats how many extra
	    // bytes to allocate.
	    if(pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
		{
		    dwExtraAlloc = 0;                               
		}
	    else
		{
		    // Read in length of extra bytes.
		    if(::mmioRead(hmmioIn, (LPSTR) &dwExtraAlloc,
		       (long) sizeof(dwExtraAlloc)) != (long) sizeof(dwExtraAlloc))
			{
			    nError = ERR_CANNOTREAD;
			    throw &except;
			}
		}
					
	    // Ok, now allocate that waveformatex structure.
		if((*ppwfxInfo = (WAVEFORMATEX*)::VirtualAlloc(NULL, 
			sizeof(WAVEFORMATEX) + dwExtraAlloc, MEM_COMMIT, PAGE_READWRITE))
			== NULL)
		{
		    nError = ERR_NOMEMEORY;
		    throw &except;
		}

	    // Copy the bytes from the pcm structure to the waveformatex structure
	    ::memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
	    (*ppwfxInfo)->cbSize = dwExtraAlloc;

	    // Now, read those extra bytes into the structure, if dwExtraAlloc != 0.
	    if(dwExtraAlloc != 0)
		{
		    if(::mmioRead(hmmioIn, (LPSTR)(((BYTE*)&((*ppwfxInfo)->cbSize))+
			   sizeof(dwExtraAlloc)), (long)(dwExtraAlloc)) != (long)(dwExtraAlloc))
			{
			    nError = ERR_NOTWAVEFILE;
			    throw &except;
			}
		}

	    // Ascend the input file out of the 'fmt ' chunk.                                                            
	    if(::mmioAscend(hmmioIn, &ckIn, 0) != 0)
		{
            nError = ERR_FAILASCEND; 
		    throw &except;
		}
	}
	catch(CException * pException)
	{
	    if(*ppwfxInfo != NULL)
		{
		    ::VirtualFree(*ppwfxInfo, sizeof(WAVEFORMATEX) + dwExtraAlloc,
				          MEM_DECOMMIT);
		    *ppwfxInfo = NULL;
		}               

	    if(hmmioIn != NULL)
		{
	        ::mmioClose(hmmioIn, 0);
		    hmmioIn = NULL;
		}

		pException->Delete();
	}	
	
	*phmmioIn = hmmioIn;
	return nError;
}


int NWaveIO::StartReadWave(HMMIO *phmmioIn, MMCKINFO *pckIn, MMCKINFO *pckInRIFF)
{
	int             nError = ERR_NONE; 
	CException		except(FALSE);

 	try
	{
	    if(::mmioSeek(*phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC), SEEK_SET)
		   == -1)
		{
		    nError = ERR_FAILSEEK;
			throw &except;
		}

	    //Search the input file for for the 'data' chunk.
	    pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');
	    if(::mmioDescend(*phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK) != 0)
		{
            nError = ERR_FAILDESCEND; 
		    throw &except;
		}
	}
    catch(CException * pException)
	{
		pException->Delete();
	}

	return nError;
}


int NWaveIO::ReadWaveFile(HMMIO    hmmioIn,      
		                  UINT     uiRead,                
		                  BYTE     *pbDest,    
		                  MMCKINFO *pckIn,        
		                  UINT     *uiActualRead)
{
	MMIOINFO    mmioinfoIn;         // current status of <hmmioIn>
	int         nError;
	UINT        uiTemp;
	UINT        uiDataIn;
    CException	except(FALSE);

	nError = ERR_NONE;


	try
	{
	    if(::mmioGetInfo(hmmioIn, &mmioinfoIn, 0) != 0)
		{
			nError = ERR_FAILGETINFO;
		    throw &except;
		}
				
	    uiDataIn = uiRead;
	    
		if(uiDataIn > pckIn->cksize) 
		    uiDataIn = pckIn->cksize;       

	    pckIn->cksize -= uiDataIn;
	
	    for(uiTemp = 0; uiTemp < uiDataIn; uiTemp++)
		{
		    // Copy the bytes from the io to the buffer.
		    if(mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
			    if(::mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ) != 0)
				{
			        nError = ERR_FAILGETINFO;
		            throw &except;
				} 
	            if(mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
				{
				    nError = ERR_CORRUPTWAVEFILE;
		            throw &except;
				}
			}
			
		    // Actual copy.
		    *((BYTE*)pbDest + uiTemp) = *((BYTE*)mmioinfoIn.pchNext);                                                                                                   
            (BYTE*)mmioinfoIn.pchNext++;                      
		}


		if (::mmioSetInfo(hmmioIn, &mmioinfoIn, 0) != 0)
		{
		    nError = ERR_FAILSETINFO;
            throw &except;
		}

	    *uiActualRead = uiDataIn;
	}
    catch(CException * pException)
	{
	    *uiActualRead = 0;
		pException->Delete();
	}

	return nError;
}


int NWaveIO::LoadWaveFile(LPSTR pszFileName,         
			              UINT  *uiSize,     
			              WAVEFORMATEX **ppwfxInfo, 
			              BYTE **ppbData )
{
	HMMIO       hmmioIn;        
	MMCKINFO    ckInRiff;
	MMCKINFO    ckIn;
	int         nError;
    UINT        uiActualRead;
    CException	except(FALSE);

	nError = ERR_NONE;
	*ppbData = NULL;
	*ppwfxInfo = NULL;
	*uiSize = 0;
	
	
	try
	{
	    nError = OpenReadWaveFile(pszFileName, &hmmioIn, ppwfxInfo, &ckInRiff);
	
		if(nError != ERR_NONE)
		{
            throw &except;
		}


		nError = StartReadWave(&hmmioIn, &ckIn, &ckInRiff);
		if(nError != ERR_NONE)
		{
            throw &except;
		}

	
		// Ok, size of wave data is in ckIn, allocate that buffer.
		if((*ppbData = (BYTE *)::VirtualAlloc(NULL, ckIn.cksize,
			MEM_COMMIT, PAGE_READWRITE)) == NULL)
		{
		    nError = ERR_NOMEMEORY;
            throw &except;
		}

		nError = ReadWaveFile(hmmioIn, ckIn.cksize, *ppbData, &ckIn, &uiActualRead);
		if(nError != ERR_NONE)
		{
            throw &except;
		}
	
	    *uiSize = uiActualRead;
	}
    catch(CException * pException)
	{
		pException->Delete();
	    
		if(*ppbData != NULL)
		{
		    ::VirtualFree(ppbData, ckIn.cksize, MEM_DECOMMIT);
		    *ppbData = NULL;
		}
	    if(*ppwfxInfo != NULL)
		{
			DWORD dwExtra = (*ppwfxInfo)->cbSize;
		    ::VirtualFree(*ppwfxInfo, sizeof(WAVEFORMATEX) + dwExtra,
				          MEM_DECOMMIT);
		    *ppwfxInfo = NULL;
		}
		pException->Delete();
	}	

	// Close the wave file. 
	if(hmmioIn != NULL)
	{
		::mmioClose(hmmioIn, 0);
		hmmioIn = NULL;
	}

	return nError;
}


int NWaveIO::CloseReadWaveFile(HMMIO        *phmmio,  
			                   WAVEFORMATEX **ppwfxSrc)
{
	if(*ppwfxSrc != NULL)
	{
		DWORD dwExtra = (*ppwfxSrc)->cbSize;
		::VirtualFree(*ppwfxSrc, sizeof(WAVEFORMATEX) + dwExtra,
				          MEM_DECOMMIT);
		*ppwfxSrc = NULL;
	}

	if(*phmmio != NULL)
	{
		::mmioClose(*phmmio, 0);
		*phmmio = NULL;
	}

	return ERR_NONE;
}


