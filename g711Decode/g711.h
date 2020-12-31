
#ifndef __G_711_H_
#define __G_711_H_

unsigned char linear2alaw(int		pcm_val);	/* 2's complement (16-bit range) */
int alaw2linear(unsigned char	a_val);

unsigned char linear2ulaw(int pcm_val);	/* 2's complement (16-bit range) */
int ulaw2linear(unsigned char	u_val);

unsigned char alaw2ulaw(unsigned char	aval);
unsigned char ulaw2alaw(unsigned char	uval);

#endif
