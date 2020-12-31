//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: COMPLEX.H
//
#ifndef COMPLEX_H
#define COMPLEX_H

typedef double REAL;		// could be float

class complex {
private:
	REAL re;
	REAL im;

public:
	complex()	{ re=0.; im=0.; }
	complex(REAL r, REAL i) { set(r,i); }

	void set(REAL r, REAL i) { re=r; im=i; }
	REAL& real()	{ return re; }
	REAL& imag()	{ return im; }
	void real(REAL r)	{ re=r; }
	void imag(REAL i)	{ im=i; }

	REAL abs2()	{ return re*re + im*im; }

	friend complex operator+ (const complex &c1, const complex &c2)
		{ return complex(c1.re + c2.re, c1.im + c2.im); }
	friend complex operator- (const complex &c1, const complex &c2)
		{ return  complex( c1.re - c2.re, c1.im - c2.im ); }
	friend complex operator* (const complex &c1, const complex &c2)
		{ return  complex( c1.re*c2.re - c1.im*c2.im,
			c1.re*c2.im + c1.im*c2.re ); }

	friend int operator== (const complex &c1, const complex &c2)
		{ return c1.re == c2.re && c1.im==c2.im; }
	friend int operator!= (const complex &c1, const complex & c2)
		{ return c1==c2 ? 0 : 1; }
};

#endif
