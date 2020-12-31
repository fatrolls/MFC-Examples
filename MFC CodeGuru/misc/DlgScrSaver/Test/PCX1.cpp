#include "stdafx.h"
#include <fstream.h>
#include "PCX1.h"


PCXHEADER pcxhdr;

/* Read an entire file and store it in a (large) buffer,
   pointed to by the variable bufr
   filename is the name of the file,
   including the .pcx extension */

int readpcx(BYTE* bufr, char* filename)
{   
	int i;
	long l, linesize;
	BYTE block, count;
	FILE* pcxfile;
	if ((pcxfile = fopen(filename, "rb")) == NULL) return(0);
	//pcxhdr.manufacturer = getc(pcxfile);
	fread(&pcxhdr, 1, 128, pcxfile);
	if (pcxhdr.manufacturer != 10)
	{
		fclose(pcxfile);
		return(0);
	}
	/*
	pcxhdr.version = getc(pcxfile);
	pcxhdr.encoding = getc(pcxfile);
	pcxhdr.bitsperpixel = fgetc(pcxfile);
	pcxhdr.xmin = getw(pcxfile);
	pcxhdr.ymin = getw(pcxfile);
	pcxhdr.xmax = getw(pcxfile);
	pcxhdr.ymax = getw(pcxfile);
	pcxhdr.hres = getw(pcxfile);
	pcxhdr.vres = getw(pcxfile);
	fread(pcxhdr.colormap, 48, sizeof(char), pcxfile);
	pcxhdr.reserved = getc(pcxfile);
	pcxhdr.nplanes = getc(pcxfile);
	pcxhdr.bytesperline = getw(pcxfile);
	pcxhdr.palettetype = getw(pcxfile);
	fread(pcxhdr.filler, 58, sizeof(char), pcxfile);
	*/
	linesize = (long) pcxhdr.bytesperline * pcxhdr.nplanes *
		   (1 + pcxhdr.ymax - pcxhdr.ymin);
	for (l = 0; l < linesize; )             /* increment by count below */
	{
		if (readpcxblock(&block, &count, pcxfile) == EOF) break;
		for (i = 0; i < count; i++)
			*bufr++ = block;
		l += count;
	}
	ofstream os("c:\\pcx1.txt");
	int cc = 0;
	for (int p=0; p<pcxhdr.nplanes; p++)
	{
		os << "Plane:" << p << endl;
		for (int k1=0; k1<pcxhdr.xmax-pcxhdr.xmin+1; k1++)
		{
			os << k1 << ": ";
			for (int k2=0; k2<pcxhdr.ymax-pcxhdr.ymin+1; k2++)
			{
				os << (int) (bufr[cc]) << " ";
				cc++;
			}
			os << endl;
		}
	}
	return 1;
}

/* Read one encoded block from the pcx
   file and store a count and data byte.
   If the code is greater than 0xc0 (192), go for a run.
   Otherwise, just grab a byte.
   Result: 0 = valid data stored
	   EOF = out of data in file

    int *pblock;      where to place data
    int *pcount;      where to place count
    FILE *pcxfile;         image file handle
*/

int readpcxblock(BYTE* pblock, BYTE* pcount, FILE *pcxfile)
{
	int i;
	*pcount = 1;
	if ((i = getc(pcxfile)) == EOF) return(EOF);
	if (0xc0 == (0xc0 & i))      /* is it greater than 192? */
	{
		*pcount = 0x3f&i;      /* subtract 192 to get count */
		if((i = getc(pcxfile)) == EOF) return(EOF);
	}
	*pblock = i;
	return(0);
}

