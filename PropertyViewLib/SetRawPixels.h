#ifndef EIVA_SET_RAW_PIXELS_H
#define EIVA_SET_RAW_PIXELS_H

//this uses standart StretchDIBits() to copy a memory
//pixel buffer to a dc, you should use this because all
//the flippnig and the stretching and the minus one issue
//is handled here..
//
//the pPixelBuffer is a buffer of RGB pixels
//
//note1: if source w and h are both -1, image dimension
//will be extracted from the two first integers in the buffer
//note2: if the destination rect is NULL, the image will be drawn 1:1

void SetRawPixels( CDC* pDC , int* pPixelBuffer , const CRect* pDestinationRect=NULL , int nSourceWidth=-1 , int nSourceHeight=-1 );

//pixelmap dimensions are -1 if first two entries in pixelmap hold dimensions!
void SetRawPixels( CDC* pDC , int* pPixelBuffer , const CRect* pDestinationRect , const CRect* pSourceRect , int nPixelMapWidth=-1 , int nPixelMapHeight=-1 );

#endif