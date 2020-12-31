#include "stdafx.h"
#include "PCX.h"
#include <windowsx.h>
#include <fstream.h>

/*
ZSoft .PCX FILE HEADER FORMAT

Byte      Item          Size   Description/Comments 
 0         Manufacturer 1      Constant Flag, 10 = ZSoft .pcx 
 1         Version      1      Version information 
                               0 = Version 2.5 of PC Paintbrush 
                               2 = Version 2.8 w/palette information 
                               3 = Version 2.8 w/o palette information 
                               4 = PC Paintbrush for Windows(Plus for
                                  Windows uses Ver 5) 
                               5 = Version 3.0 and > of PC Paintbrush
                                  and PC Paintbrush +, includes
                                  Publisher's Paintbrush . Includes
                                  24-bit .PCX files 
 2         Encoding      1     1 = .PCX run length encoding 
 3         BitsPerPixel  1     Number of bits to represent a pixel
                                  (per Plane) - 1, 2, 4, or 8 
 4         Window        8     Image Dimensions: Xmin,Ymin,Xmax,Ymax 
12         HDpi          2     Horizontal Resolution of image in DPI* 
14         VDpi          2     Vertical Resolution of image in DPI* 
16         Colormap     48     Color palette setting, see text 
64         Reserved      1     Should be set to 0. 
65         NPlanes       1     Number of color planes 
66         BytesPerLine  2     Number of bytes to allocate for a scanline
                                  plane.  MUST be an EVEN number.  Do NOT
                                  calculate from Xmax-Xmin. 
68         PaletteInfo   2     How to interpret palette- 1 = Color/BW,
                                  2 = Grayscale (ignored in PB IV/ IV +) 
70         HscreenSize   2     Horizontal screen size in pixels. New field
                                  found only in PB IV/IV Plus 
72         VscreenSize   2     Vertical screen size in pixels. New field
                                  found only in PB IV/IV Plus 
74         Filler       54     Blank to fill out 128 byte header.  Set all
                                  bytes to 0 
*/

//The following is a simple set of C subroutines to read data from a .PCX file.

/* This procedure reads one encoded block from the image file and stores a
count and data byte.

Return result:  0 = valid data stored, EOF = out of data in file */

/*
int *pbyt;        // where to place data
int *pcnt;        // where to place count
FILE *fid;        // image file handle
*/
int encget(int* pbyt, int* pcnt, FILE* fid)
{
	int i;
	*pcnt = 1;        /* assume a "run" length of one */
	if (EOF == (i = getc(fid)))
		return (EOF);
	if (0xC0 == (0xC0 & i))
	{
		*pcnt = 0x3F & i;
		if (EOF == (i = getc(fid)))
			return (EOF);
	}
	*pbyt = i;
	return (0);
}

/* Here's a program fragment using encget.  This reads an entire file and
stores it in a (large) buffer, pointed to by the variable "bufr". "fp" is
the file pointer for the image */
bool ReadPCX(BYTE* bufr, PCXHEADER& hdr, FILE* fp)
{
	int i;
	long l, lsize;
	int chr, cnt;
	lsize = (long )hdr.BytesPerLine * hdr.NPlanes * (1 + hdr.Ymax - hdr.Ymin);
	for (l = 0; l < lsize; )             /* increment by cnt below */
	{
		if (EOF == encget(&chr, &cnt, fp))
			break;
		for (i = 0; i < cnt; i++)
			*bufr++ = chr;
		l += cnt;
	}
	return true;
}

BYTE* ReadPCX(const char* fname, PCXHEADER& hdr)
{
	FILE* fp = fopen(fname, "r");
	if (fp == NULL)
		return NULL;
	//PCXHEADER hdr;
	if (fread(&hdr, 1, 128, fp) != 128)
		return NULL;
	BYTE* buffer = (BYTE*)GlobalAllocPtr(GMEM_FIXED | GMEM_ZEROINIT, (hdr.Xmax-hdr.Xmin+1) * (hdr.Ymax-hdr.Ymin+1));
	if (buffer == NULL)
		return NULL;
	ReadPCX(buffer, hdr, fp);
	fclose(fp);
	return buffer;
}

void DisplayPCX(CDC* pDC, CRect& rect, PCXHEADER& hdr, BYTE* buffer)
{
	ofstream os("c:\\testpcx.txt");
	os << (int)hdr.Manufacturer << endl;
	os << (int)hdr.Version << endl;
	os << (int)hdr.Encoding << endl;
	os << (int)hdr.BitsPerPixel << endl;
	os << hdr.Xmin << endl;
	os << hdr.Ymin << endl;
	os << hdr.Xmax << endl;
	os << hdr.Ymax << endl;
	os << hdr.HDpi << endl;
	os << hdr.VDpi << endl;
	//os << hdr.ColorMap[48] << endl;
	os << (int)hdr.Reserved << endl;
	os << (int)hdr.NPlanes << endl;
	os << hdr.BytesPerLine << endl;
	os << hdr.PaletteInfo << endl;
	os << hdr.HscreenSize << endl;
	os << hdr.VscreenSize << endl;

	for (int i=hdr.Ymin; i<=hdr.Ymin; i++)
	{
		for (int j=hdr.Xmin; j<=hdr.Xmin; j++)
		{
			int index = (i-hdr.Ymin) * (hdr.Xmax-hdr.Xmin+1) + j-hdr.Xmin;
			BYTE pixel = buffer[index];
			os << pixel << endl;
		}
	}
}

//The following is a set of C subroutines to write data to a .PCX file.

/* Subroutine for writing an encoded byte pair (or single byte if it
doesn't encode) to a file. It returns the count of bytes written, 0 if error */

/*
unsigned char byt, cnt;
FILE *fid;
*/
int encput(unsigned char byt, unsigned char cnt, FILE* fid)
{
	if (cnt)
	{
		if ((cnt == 1) && (0xC0 != (0xC0 & byt)))
		{
			if (EOF == putc((int )byt, fid))
				return(0);     /* disk write error (probably full) */
			return(1);
		}
		else
		{
			if (EOF == putc((int )0xC0 | cnt, fid))
				return (0);      /* disk write error */
			if (EOF == putc((int )byt, fid))
				return (0);      /* disk write error */
			return (2);
		}
	}
	return (0);
}

/* This subroutine encodes one scanline and writes it to a file.
It returns number of bytes written into outBuff, 0 if failed. */

/*
unsigned char *inBuff;    // pointer to scanline data 
int inLen;                        // length of raw scanline in bytes 
FILE *fp;                        // file to be written to 
*/
int encLine(unsigned char* inBuff, int inLen, FILE* fp)
{
	unsigned char This, Last;
	int srcIndex, i;
	register int total;
	register unsigned char runCount;     /* max single runlength is 63 */
	total = 0;
	runCount = 1;
	Last = *(inBuff);

	/* Find the pixel dimensions of the image by calculating 
	[XSIZE = Xmax - Xmin + 1] and [YSIZE = Ymax - Ymin + 1].  
	Then calculate how many bytes are in a "run" */

	for (srcIndex = 1; srcIndex < inLen; srcIndex++)
	{
		This = *(++inBuff);
		if (This == Last)     /* There is a "run" in the data, encode it */
		{
			runCount++;
			if (runCount == 63)
			{
				if (! (i = encput(Last, runCount, fp)))
					return (0);
				total += i;
				runCount = 0;
			}
		}
		else                /* No "run"  -  this != last */
		{
			if (runCount)
			{
				if (! (i = encput(Last, runCount, fp)))
					return(0);
				total += i;
			}
			Last = This;
			runCount = 1;
		}
	}        /* endloop */
	if (runCount)        /* finish up */
	{
		if (! (i = encput(Last, runCount, fp)))
			return (0);
		return (total + i);
	}
	return (total);
}

