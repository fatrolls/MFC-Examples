typedef struct
{   
	BYTE manufacturer;
	BYTE version;
	BYTE encoding;
    BYTE bitsperpixel;
    WORD xmin;
    WORD ymin;
    WORD xmax;
    WORD ymax;
	WORD hres;
	WORD vres;
    BYTE colormap[48];
	BYTE reserved;
    BYTE nplanes;
    WORD bytesperline;
    WORD palettetype;
	BYTE filler[58];
} PCXHEADER;

int readpcxblock(BYTE* pblock, BYTE* pcount, FILE* pcxfile);
int readpcx(BYTE* bufr, char* filename);
