#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
	{							// main
	void (__far *myvxd)();
	static char name[9] = "MYVXD   ";
	static unsigned char buffer[512];
	
	_asm
		{						// find api entry
		mov ax, 1684h
		xor	bx, bx
		mov di, ds
		mov es, di
		mov di, offset name
		int 2Fh
		mov word ptr myvxd, di
		mov word ptr myvxd+2, es
		}						// find api entry
	if (!myvxd)
		{						// no vxd
		puts("MYVXD.VXD isn't loaded");
		return 1;
		}						// no vxd
	
	memset(buffer, 0, sizeof(buffer));
	_asm mov bx, offset buffer
	myvxd();

   printf("First few bytes read are: %2.2X%2.2X%2.2X%2.2X %2.2X%2.2X%2.2X%2.2X\n",
      buffer[0], buffer[1], buffer[2], buffer[3],
      buffer[4], buffer[5], buffer[6], buffer[7]);
	return 0;		
	}							// main
	