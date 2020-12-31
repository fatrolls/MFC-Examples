// NWaveio.h: interface for the NWaveio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NWAVEIO_H__CBFE8048_6558_47DE_9A05_C54312E77CF7__INCLUDED_)
#define AFX_NWAVEIO_H__CBFE8048_6558_47DE_9A05_C54312E77CF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <mmsystem.h>

namespace NWaveIO
{
	const int ERR_NONE              = 0x00;
	const int ERR_CANNOTOPEN        = 0x01;
    const int ERR_FAILASCEND        = 0x02; 
    const int ERR_FAILDESCEND       = 0x03; 
	const int ERR_NOTWAVEFILE       = 0x04;
	const int ERR_CANNOTREAD        = 0x05;
	const int ERR_NOMEMEORY         = 0x06;
	const int ERR_FAILSEEK          = 0x07;
	const int ERR_FAILGETINFO       = 0x08;
	const int ERR_FAILSETINFO       = 0x09;  
    const int ERR_CORRUPTWAVEFILE   = 0x0A;
	

    int OpenReadWaveFile(LPSTR, HMMIO *, WAVEFORMATEX **, MMCKINFO *);
    int StartReadWave(HMMIO *, MMCKINFO *, MMCKINFO *);
    int ReadWaveFile(HMMIO, UINT, BYTE *, MMCKINFO *, UINT *); 
    int LoadWaveFile(LPSTR, UINT *, WAVEFORMATEX **, BYTE **);
    int CloseReadWaveFile(HMMIO *,WAVEFORMATEX **);
};

#endif // !defined(AFX_NWAVEIO_H__CBFE8048_6558_47DE_9A05_C54312E77CF7__INCLUDED_)
