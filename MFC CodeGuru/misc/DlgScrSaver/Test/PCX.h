struct PCXHEADER
{
	BYTE Manufacturer;
	BYTE Version;
	BYTE Encoding;
	BYTE BitsPerPixel;
	WORD Xmin;
	WORD Ymin;
	WORD Xmax;
	WORD Ymax;
	WORD HDpi;
	WORD VDpi;
	BYTE ColorMap[48];
	BYTE Reserved;
	BYTE NPlanes;
	WORD BytesPerLine;
	WORD PaletteInfo;
	WORD HscreenSize;
	WORD VscreenSize;
	BYTE Filler[54];
};

BYTE* ReadPCX(const char* fname, PCXHEADER& hdr);
void DisplayPCX(CDC* pDC, CRect& rect, PCXHEADER& hdr, BYTE* buffer);
