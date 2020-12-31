/*
 * File:	ximabmp.cpp
 * Purpose:	Platform Independent BMP Image Class Loader and Writer
 * 07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * version 1.20 15/Oct/2001
 */

#include <stdio.h>

#include "ximabmp.h"

#if CXIMAGE_SUPPORT_BMP

#include "ximaiter.h" 

const RLE_COMMAND     = 0;
const RLE_ENDOFLINE   = 0;
const RLE_ENDOFBITMAP = 1;
const RLE_DELTA       = 2;

/**************************************/
bool CxImageBMP::Encode(FILE * hFile)
{
	if (hFile==NULL) return false;

	BITMAPFILEHEADER	hdr;

	hdr.bfType = 0x4d42;   // 'BM' WINDOWS_BITMAP_SIGNATURE
	hdr.bfSize = GetSize() + sizeof(BITMAPFILEHEADER);
	hdr.bfReserved1 = hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD) sizeof(hdr) + head.biSize + GetPaletteSize();

    // Write the file header
	fwrite(&hdr,sizeof(BITMAPFILEHEADER),1,hFile);
    // Write the DIB header and the bits
	fwrite(hDib,GetSize(),1,hFile);
	return true;
}
/**************************************/
bool CxImageBMP::Decode(FILE * hFile)
{
    BITMAPFILEHEADER   bf;
    DWORD off = fseek(hFile,0L,SEEK_CUR);
  try {
    if (fread((LPSTR)&bf,sizeof(bf),1,hFile)==0) throw "Not a BMP";
    if (bf.bfType != BFT_BITMAP) { //do we have a RC HEADER?
        bf.bfOffBits = 0L;
        fseek(hFile,off,SEEK_SET);
    }
	
	if (!DibReadBitmapInfo(hFile,&head)) throw "Error reading BMP info";
	DWORD dwCompression=head.biCompression;

	if (!Create(head.biWidth,head.biHeight,head.biBitCount))
		throw "Can't allocate memory";

    RGBQUAD *pRgb = GetPalette();
    if (pRgb){
        if (head.biSize == sizeof(BITMAPCOREHEADER)){
             // convert a old color table (3 byte entries) to a new
             // color table (4 byte entries)
            fread((LPVOID)pRgb,DibNumColors(&head) * sizeof(RGBTRIPLE),1,hFile);
            for (int i=DibNumColors(&head)-1; i>=0; i--){
                pRgb[i].rgbRed      = ((RGBTRIPLE FAR *)pRgb)[i].rgbtRed;
                pRgb[i].rgbBlue     = ((RGBTRIPLE FAR *)pRgb)[i].rgbtBlue;
                pRgb[i].rgbGreen    = ((RGBTRIPLE FAR *)pRgb)[i].rgbtGreen;
                pRgb[i].rgbReserved = (BYTE)0;
            }
        } else {
            fread((LPVOID)pRgb,DibNumColors(&head) * sizeof(RGBQUAD),1,hFile);
        }
    }

    if (bf.bfOffBits != 0L) fseek(hFile,off + bf.bfOffBits,SEEK_SET);

	switch (head.biBitCount) {
		case 32 :
			if (dwCompression == BI_BITFIELDS){
				BYTE* buff32=(BYTE*)malloc(head.biSizeImage);
				if (buff32){
					fread(info.pImage, head.biSizeImage,1,hFile); // read in the bits
					Bitfield2RGB(buff32,0,0,0,32);
					free(buff32);
				} else throw "can't allocate memory";
			} else throw "unknown compression";
			break;
		case 24 :
			if (dwCompression == BI_RGB){
				fread(info.pImage, head.biSizeImage,1,hFile); // read in the bits
			} else throw "unknown compression";
			break;
		case 16 :
		{
			DWORD bf[3];
			if (head.biCompression == BI_BITFIELDS) {
				fread(bf, 12, 1, hFile);
			} else {
				bf[0]=0x7C00; bf[1]=0x3E0; bf[2]=0x1F; //RGB555
			}
			// read in the bits
			fread(info.pImage, head.biWidth*((head.biWidth+1)/2)*4,1,hFile);
			// transform into RGB
			Bitfield2RGB(info.pImage,(WORD)bf[0],(WORD)bf[1],(WORD)bf[2],16);
			break;
		}
		case 8 :
		case 4 :
		case 1 :
		switch (dwCompression) {
			case BI_RGB :
				fread(info.pImage, head.biSizeImage,1,hFile); // read in the bits
				break;
			case BI_RLE4 :
			{
				BYTE status_byte = 0;
				BYTE second_byte = 0;
				int scanline = 0;
				int bits = 0;
				BOOL low_nibble = FALSE;
				CImageIterator iter(this);

				for (BOOL bContinue = TRUE; bContinue;) {
					fread(&status_byte, sizeof(BYTE), 1, hFile);
					switch (status_byte) {
						case RLE_COMMAND :
							fread(&status_byte, sizeof(BYTE), 1, hFile);
							switch (status_byte) {
								case RLE_ENDOFLINE :
									bits = 0;
									scanline++;
									low_nibble = FALSE;
									break;
								case RLE_ENDOFBITMAP :
									bContinue=FALSE;
									break;
								case RLE_DELTA :
								{
									// read the delta values
									BYTE delta_x;
									BYTE delta_y;
									fread(&delta_x, sizeof(BYTE), 1, hFile);
									fread(&delta_y, sizeof(BYTE), 1, hFile);
									// apply them
									bits       += delta_x / 2;
									scanline   += delta_y;
									break;
								}
								default :
									fread(&second_byte, sizeof(BYTE), 1, hFile);
									BYTE *sline = iter.GetRow(scanline);
									for (int i = 0; i < status_byte; i++) {
										if (low_nibble) {
											*(sline + bits) |=  second_byte & 0x0F;
											if (i != status_byte - 1)
												fread(&second_byte, sizeof(BYTE), 1, hFile);
											bits++;
										} else {
											*(sline + bits) = second_byte & 0xF0;
										}
										low_nibble = !low_nibble;
									}
									if (((status_byte / 2) & 1 )== 1)
										fread(&second_byte, sizeof(BYTE), 1, hFile);												
									break;
							};
							break;
						default :
						{
							BYTE *sline = iter.GetRow(scanline);
							fread(&second_byte, sizeof(BYTE), 1, hFile);
							for (unsigned i = 0; i < status_byte; i++) {
								if (low_nibble) {
									*(sline + bits) |= second_byte & 0x0F;
									bits++;
								} else {
									*(sline + bits) = second_byte & 0xF0;
								}				
								low_nibble = !low_nibble;
							}
						}
						break;
					};
				}
				break;
			}
			case BI_RLE8 :
			{
				BYTE status_byte = 0;
				BYTE second_byte = 0;
				int scanline = 0;
				int bits = 0;
				CImageIterator iter(this);

				for (BOOL bContinue = TRUE; bContinue; ) {
					fread(&status_byte, sizeof(BYTE), 1, hFile);
					switch (status_byte) {
						case RLE_COMMAND :
							fread(&status_byte, sizeof(BYTE), 1, hFile);
							switch (status_byte) {
								case RLE_ENDOFLINE :
									bits = 0;
									scanline++;
									break;
								case RLE_ENDOFBITMAP :
									bContinue=FALSE;
									break;
								case RLE_DELTA :
								{
									// read the delta values
									BYTE delta_x;
									BYTE delta_y;
									fread(&delta_x, sizeof(BYTE), 1, hFile);
									fread(&delta_y, sizeof(BYTE), 1, hFile);
									// apply them
									bits     += delta_x;
									scanline += delta_y;
									break;
								}
								default :
									fread((void *)(iter.GetRow(scanline) + bits), sizeof(BYTE) * status_byte, 1, hFile);
									// align run length to even number of bytes 
									if ((status_byte & 1) == 1)
										fread(&second_byte, sizeof(BYTE), 1, hFile);												
									bits += status_byte;													
									break;								
							};
							break;
						default :
							BYTE *sline = iter.GetRow(scanline);
							fread(&second_byte, sizeof(BYTE), 1, hFile);
							for (unsigned i = 0; i < status_byte; i++) {
								*(sline + bits) = second_byte;
								bits++;					
							}
							break;
					};
				}
				break;
			}
			default :								
				throw "compression type not supported";
		}
	}
  } catch (char *message) {
	strncpy(info.szLastError,message,255);
	return FALSE;
  }
    return true;
}
/**************************************/
/*  ReadDibBitmapInfo()
 *
 *  Will read a file in DIB format and return a global HANDLE to its
 *  BITMAPINFO.  This function will work with both "old" and "new"
 *  bitmap formats, but will always return a "new" BITMAPINFO.
 */
bool CxImageBMP::DibReadBitmapInfo(FILE* fh,PDIB pdib)
{
	if ((fh==NULL)||(pdib==NULL)) return false;

    if (fread(pdib,sizeof(BITMAPINFOHEADER),1,fh)==0) return false;

    BITMAPCOREHEADER   bc;

    switch (pdib->biSize) // what type of bitmap info is this?
    {
        default:
        case sizeof(BITMAPINFOHEADER):
            break;

        case sizeof(BITMAPCOREHEADER):
            bc = *(BITMAPCOREHEADER*)pdib;
            pdib->biSize               = sizeof(BITMAPINFOHEADER);
            pdib->biWidth              = (DWORD)bc.bcWidth;
            pdib->biHeight             = (DWORD)bc.bcHeight;
            pdib->biPlanes             =  bc.bcPlanes;
            pdib->biBitCount           =  bc.bcBitCount;
            pdib->biCompression        = BI_RGB;
            pdib->biSizeImage          = 0;
            pdib->biXPelsPerMeter      = 0;
            pdib->biYPelsPerMeter      = 0;
            pdib->biClrUsed            = 0;
            pdib->biClrImportant       = 0;

            fseek(fh,(LONG)sizeof(BITMAPCOREHEADER)-sizeof(BITMAPINFOHEADER),SEEK_CUR);

            break;
    }

    FixBitmapInfo(pdib);

    return true;
}
/**************************************/
#endif 	// CXIMAGE_SUPPORT_BMP
