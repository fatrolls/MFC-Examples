/*
 * File:	ximatif.cpp
 * Purpose:	Platform Independent TIFF Image Class Loader and Writer
 * 07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * version 1.20 15/Oct/2001
 */

#include "ximapng.h"

#if CXIMAGE_SUPPORT_PNG

#include "ximaiter.h"

/**************************************/
void CxImagePNG::ima_png_error(png_struct *png_ptr, char *message)
{
	strcpy(info.szLastError,message);
	longjmp(png_ptr->jmpbuf, 1);
}
/**************************************/
bool CxImagePNG::Decode(FILE *fp)
{
	int number_passes;
	png_struct *png_ptr;
	png_info *info_ptr;
	BYTE *row_pointers=NULL;
	CImageIterator iter(this);

  try {
	/* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also supply the
    * the compiler header file version, so that we know if the application
    * was compiled with a compatible version of the library.  REQUIRED
    */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,(void *)NULL,NULL,NULL);
	if (png_ptr == NULL)  throw "Failed to create PNG structure";

	/* Allocate/initialize the memory for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		throw "Failed to initialize PNG info structure";
	}

    /* Set error handling if you are using the setjmp/longjmp method (this is
    * the normal method of doing things with libpng).  REQUIRED unless you
    * set up your own error handlers in the png_create_read_struct() earlier.
    */
	if (setjmp(png_ptr->jmpbuf)) {
		/* Free all of the memory associated with the png_ptr and info_ptr */
		if (row_pointers) delete[] row_pointers;
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		throw "Error reading PNG file";
	}
	/* set up the input control */
	png_init_io(png_ptr, fp);

	/* read the file information */
	png_read_info(png_ptr, info_ptr);

	/* allocate the memory to hold the image using the fields of png_info. */
	png_color_16 my_background={ 0, 31, 127, 255, 0 };

	png_set_background(png_ptr, &my_background,
			PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);

	/* tell libpng to strip 16 bit depth files down to 8 bits */
	if (info_ptr->bit_depth == 16)	png_set_strip_16(png_ptr);

	int pixel_depth=(info_ptr->pixel_depth<24) ? info_ptr->pixel_depth: 24;

	Create(info_ptr->width, info_ptr->height, pixel_depth);

	// simple transparency (the real PGN transparency is more complex)
	if (info_ptr->num_trans!=0) info.nBkgndIndex = 0;

	if (info_ptr->num_palette>0)
	  SetPalette((rgb_color_struct*)info_ptr->palette,info_ptr->num_palette);
	else SetGrayPalette(); //<DP> needed for grayscale PNGs

	int row_stride = info_ptr->width * ((pixel_depth+7)>>3);

	row_pointers = new BYTE[row_stride];

	/* turn on interlace handling */
	if (info_ptr->interlace_type)
		number_passes = png_set_interlace_handling(png_ptr);
	else
		number_passes = 1;

	for (int pass=0; pass< number_passes; pass++) {
		iter.Upset();
		int y=0;
		do	{
			if (info_ptr->interlace_type)  {
				if (pass>0)
					iter.GetRow(row_pointers, row_stride);
				png_read_row(png_ptr, row_pointers, NULL);
			} else
				png_read_row(png_ptr, row_pointers, NULL);
			//HACK BY OP && (<DP> for interlace, swap only in the last pass)
			if (info_ptr->color_type==COLORTYPE_COLOR && pass==(number_passes-1))
				RGB2BGR(row_pointers, row_stride);
			iter.SetRow(row_pointers, row_stride);
			y++;
		} while(iter.PrevRow());
	}
	delete[] row_pointers;

	/* read the rest of the file, getting any additional chunks in info_ptr */
	png_read_end(png_ptr, info_ptr);

	/* clean up after the read, and free any memory allocated - REQUIRED */
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

  } catch (char *message) {
	strncpy(info.szLastError,message,255);
	return FALSE;
  }
	/* that's it */
	return TRUE;
}
/**************************************/
bool CxImagePNG::Encode(FILE *fp)
{
	if (fp==NULL) return false;

	CImageIterator iter(this);
	BYTE trans=0;	//for transparency (don't move)
	png_struct *png_ptr;
	png_info *info_ptr;

  try{
   /* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also check that
    * the library version is compatible with the one used at compile time,
    * in case we are using dynamically linked libraries.  REQUIRED.
    */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,(void *)NULL,NULL,NULL);
	if (png_ptr == NULL) throw "Failed to create PNG structure";

	/* Allocate/initialize the image information data.  REQUIRED */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL){
		png_destroy_write_struct(&png_ptr,  (png_infopp)NULL);
		throw "Failed to initialize PNG info structure";
	}

   /* Set error handling.  REQUIRED if you aren't supplying your own
    * error hadnling functions in the png_create_write_struct() call.
    */
	if (setjmp(png_ptr->jmpbuf)){
		/* If we get here, we had a problem reading the file */
		if (info_ptr->palette) free(info_ptr->palette);
		png_destroy_write_struct(&png_ptr,  (png_infopp)&info_ptr);
		throw "Error saving PNG file";
	}
            
	int row_stride = GetWidth() * ((GetBpp()+7)>>3);
	/* set up the output control */
	png_init_io(png_ptr, fp);

	/* set the file information here */
	info_ptr->width = GetWidth();
	info_ptr->height = GetHeight();
	info_ptr->pixel_depth = (BYTE)GetBpp();
	info_ptr->channels = (GetBpp()>8) ? 3: 1;
	info_ptr->bit_depth = GetBpp()/info_ptr->channels;
	info_ptr->color_type = GetColorType();
	info_ptr->compression_type = info_ptr->filter_type = info_ptr->interlace_type=0;
	info_ptr->valid = 0;
	info_ptr->interlace_type=PNG_INTERLACE_NONE;
	info_ptr->rowbytes = row_stride;

	//HACK BY OP
	if (info_ptr->pixel_depth > 8 )	info_ptr->color_type = COLORTYPE_COLOR;	

	/* set the palette if there is one */
	if ((GetColorType() & COLORTYPE_PALETTE) && GetPalette()){
		png_set_IHDR(png_ptr, info_ptr, info_ptr->width, info_ptr->height, info_ptr->bit_depth, 
					PNG_COLOR_TYPE_PALETTE, info_ptr->interlace_type, 
					PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
		info_ptr->valid |= PNG_INFO_PLTE;

		//<DP> simple transparency
		if (info.nBkgndIndex != -1){
			info_ptr->num_trans = 1;
			info_ptr->valid |= PNG_INFO_tRNS;
			info_ptr->trans = &trans;
			// the transparency indexes start from 0
			if (info.nBkgndIndex){
				SwapIndex(0,(BYTE)info.nBkgndIndex);
				// the ghost must set the changed attributes in the body
				if (info.pGhost) ((CxImage*)info.pGhost)->SetTransIndex(0);
			}
		}

		// copy the palette colors
		int nc = GetNumColors();
		info_ptr->palette = new png_color[nc];
		info_ptr->num_palette = nc;
		for (int i=0; i<nc; i++)
			GetRGB(i, &info_ptr->palette[i].red, &info_ptr->palette[i].green, &info_ptr->palette[i].blue);

	}  

	/* write the file information */
	png_write_info(png_ptr, info_ptr);
	/* If you are only writing one row at a time, this works */
	BYTE *row_pointers = new BYTE[row_stride];
  	iter.Upset();
	do	{
		iter.GetRow(row_pointers, row_stride);
		//HACK BY OP
		if (info_ptr->color_type == COLORTYPE_COLOR)
			RGB2BGR(row_pointers, row_stride);
		png_write_row(png_ptr, row_pointers);
	} while(iter.PrevRow());
	
	delete [] row_pointers;

	/* It is REQUIRED to call this to finish writing the rest of the file */
	png_write_end(png_ptr, info_ptr);

	/* if you malloced the palette, free it here */
	if (info_ptr->palette)	delete[] (info_ptr->palette);

	/* clean up after the write, and free any memory allocated */
	png_destroy_write_struct(&png_ptr, (png_infopp)&info_ptr);

  } catch (char *message) {
	strncpy(info.szLastError,message,255);
	return FALSE;
  }
	/* that's it */
	return TRUE;
}
/**************************************/
#endif // CXIMAGE_SUPPORT_PNG

