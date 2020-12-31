/*
 * File:	ximaico.cpp
 * Purpose:	Platform Independent ICON Image Class Loader and Writer (MS version)
 * 07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * version 1.20 15/Oct/2001
 */

#include <stdio.h>
#include "ximaico.h"

#if CXIMAGE_SUPPORT_ICO

/**************************************/
bool CxImageICO::Decode(FILE *hFile)
{
	int	page=info.nFrame;	//internal icon structure indexes

	// read the first part of the header
	ICONHEADER icon_header;
	fread(&icon_header,sizeof(ICONHEADER),1,hFile);
	// check if it's an icon
	if ((icon_header.idReserved == 0) && (icon_header.idType == 1)) {

		info.nNumFrames = icon_header.idCount;

		// load the icon descriptions
		ICONDIRENTRY *icon_list = (ICONDIRENTRY *)malloc(icon_header.idCount * sizeof(ICONDIRENTRY));
		int c;
		for (c = 0; c < icon_header.idCount; c++)
			fread(icon_list + c, sizeof(ICONDIRENTRY), 1, hFile);
		
		if ((info.nFrame>=0)&&(info.nFrame<icon_header.idCount)){
			// calculate the bit count for the colors in the icon
			switch (icon_list[page].bColorCount){
			case 2:
				head.biBitCount=1;
				head.biClrUsed=2;
				break;
			case 16:
				head.biBitCount=4;
				head.biClrUsed=16;
				break;
			default:
				head.biBitCount=8;
				head.biClrUsed=256;
			}
			head.biWidth  = icon_list[page].bWidth;
			head.biHeight = icon_list[page].bHeight;
			info.bColorType = (head.biBitCount>8) ? COLORTYPE_COLOR : COLORTYPE_PALETTE;
			info.nBkgndIndex =-1;

			// allocate memory for one icon
			Create(head.biWidth,head.biHeight,head.biBitCount);	//image creation
			// read the palette
			RGBQUAD pal[256];
			fseek(hFile, icon_list[page].dwImageOffset+sizeof(BITMAPINFOHEADER), SEEK_SET);
			fread(pal,head.biClrUsed*sizeof(RGBQUAD), 1, hFile);
			SetPalette(pal,head.biClrUsed);	//palette assign

			//read the icon
			fread(info.pImage, info.dwEffWidth*head.biHeight, 1, hFile);
			// apply the AND and XOR masks
/*			c=head.biWidth*head.biHeight/8; //size of masks
			BYTE *xor_mask = (BYTE *)malloc(c);
			BYTE *and_mask = (BYTE *)malloc(c);
			fread(xor_mask, c, 1, hFile);
			fread(and_mask, c, 1, hFile);
			for (int x = 0; x < head.biHeight; x++) {
				for (int y = 0; y < head.biWidth; y++) {
					if ((xor_mask[(y*head.biWidth+x)>>3]>>(x%8))&0x01){
						SetPixelColor(x,y,RGB(255,255,255));
					}
				}
			}
			free(and_mask);
			free(xor_mask);
*/
			free(icon_list);
			// icon has been loaded successfully!
			return true;
		}
		free(icon_list);
	}
	return false;
}
/**************************************/
bool CxImageICO::Encode(FILE * hFile)
{
	if (hFile==NULL) return false;

	//check format limits
	if ((head.biBitCount>8)||(head.biWidth>255)||(head.biHeight>255)){
		strcpy(info.szLastError,"Can't save this image as icon");
		return false;
	}

	//prepare the palette struct
	RGBQUAD* pal=GetPalette();
	if (pal==NULL) return false;

	//fill the icon headers
	ICONHEADER icon_header={0,1,1};
	ICONDIRENTRY icon_list={(BYTE)head.biWidth,(BYTE)head.biHeight,(BYTE)head.biClrUsed ,0,0,head.biBitCount,
							sizeof(BITMAPINFOHEADER)+head.biClrUsed*sizeof(RGBQUAD)+
							head.biHeight*info.dwEffWidth+head.biHeight*head.biWidth/4,
							sizeof(ICONHEADER)+sizeof(ICONDIRENTRY)};
	BITMAPINFOHEADER bi={sizeof(BITMAPINFOHEADER),head.biWidth,2*head.biHeight,1,head.biBitCount,
						0,head.biHeight*info.dwEffWidth,0,0,0,0};

	fwrite(&icon_header,sizeof(ICONHEADER),1,hFile);			//write the headers
	fwrite(&icon_list,sizeof(ICONDIRENTRY),1,hFile);
	fwrite(&bi,sizeof(BITMAPINFOHEADER),1,hFile);
	fwrite(pal,head.biClrUsed*sizeof(RGBQUAD),1,hFile);			//write palette
	fwrite(info.pImage,info.dwEffWidth*head.biHeight,1,hFile);	//write image
	BYTE* buff=(BYTE*)calloc(head.biWidth*head.biHeight/4,1);	//create empty AND/XOR masks
	if (buff) {
		fwrite(buff,head.biWidth*head.biHeight/4,1,hFile);		//write AND/XOR masks
		free(buff);
		return true;
	}
	return false;
}
/**************************************/
#endif 	// CXIMAGE_SUPPORT_ICO

