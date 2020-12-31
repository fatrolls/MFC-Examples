#ifndef AAROT_HPP
#define AAROT_HPP

#include <windows.h>
#include <iostream>
#include <vector>
#include <math.h>

#define aaf_abs(a) (((a) < 0)?(-(a)):(a))

typedef bool(* aaf_callback) (double);

struct aaf_pnt
{
	double x,y;
	inline aaf_pnt(){}
    inline aaf_pnt(double x,double y):x(x),y(y){}
};

struct aaf_dblrgbquad
{
	double red, green, blue, alpha;
};

struct aaf_indll
{
    aaf_indll * next;
    int ind;
};

class aaform
{
public:
    static bool transform(HBITMAP, HBITMAP, std::vector<double>, std::vector<double>, aaf_callback);
    static HBITMAP createtransform(HBITMAP, std::vector<double>, std::vector<double>, aaf_callback, int);

    //uses of transform
    static HBITMAP rotate(HBITMAP, double, aaf_callback, int);
    static HBITMAP stretch(HBITMAP, double, double, aaf_callback, int);
    static HBITMAP skewhorizontal(HBITMAP, double, aaf_callback, int);
    static HBITMAP skewverticle(HBITMAP, double, aaf_callback, int);
private:
    //used in dotransform
    static aaf_pnt * pixelgrid;

    static int outstartx;
    static int outstarty;
    static int outwidth;
    static int outheight;

    //used in pix_overlap
    static aaf_pnt * polyoverlap;
    static int polyoverlapsize;
    static aaf_pnt * polysorted;
    static int polysortedsize;
    static aaf_pnt * corners;

    //misc.
    static int ja [];

    static inline int roundup(double a) {if (aaf_abs(a - round(a)) < 1e-9) return round(a); else if ((int) a > a) return (int)a; else return (int)a + 1;}
    static inline int rounddown(double a) {if (aaf_abs(a - round(a)) < 1e-9) return round(a); else if ((int) a < a) return (int)a; else return (int)a - 1;}
    static inline int round(double a) {return (int)(a + 0.5);}
    static inline BYTE byterange(double a) {int b = round(a); if (b <= 0) return 0; else if (b >= 255) return 255; else return (BYTE)b;}
    static inline double aaf_min(double & a, double & b) {if (a < b) return a; else return b;}
    static inline double aaf_max(double & a, double & b) {if (a > b) return a; else return b;}

    static inline double aaf_cos(double);
    static inline double aaf_sin(double);

    static inline double area();
    static inline void sortpoints();
    static inline bool ptinconvexpolygon(aaf_pnt *, aaf_pnt);
    static inline double pixoverlap(aaf_pnt *);

    static bool creategrid(BITMAP &, std::vector<double> &, std::vector<double> &);

    static bool dotransform(HBITMAP, HBITMAP, aaf_callback);
};

aaf_pnt * aaform::pixelgrid;

int aaform::outstartx;
int aaform::outstarty;
int aaform::outwidth;
int aaform::outheight;

aaf_pnt * aaform::polyoverlap;
int aaform::polyoverlapsize;
aaf_pnt * aaform::polysorted;
int aaform::polysortedsize;
aaf_pnt * aaform::corners;

int aaform::ja [] = {1, 2, 3, 0};

//Prevent Float Errors with Cos and Sin
double aaform::aaf_cos(double degrees)
{
    double ret;
    double off = (degrees / 30 - round(degrees / 30));
    if (off < .0000001 && off > -.0000001)
    {
        int idegrees = (int)round(degrees);
        idegrees = (idegrees < 0) ? (360 - (-idegrees % 360))  : (idegrees % 360);
        switch (idegrees)
        {
            case 0: ret=1.0; break;
            case 30: ret=0.866025403784439; break;
            case 60: ret=0.5; break;
            case 90: ret=0.0; break;
            case 120: ret=-0.5; break;
            case 150: ret=-0.866025403784439; break;
            case 180: ret=-1.0; break;
            case 210: ret=-0.866025403784439; break;
            case 240: ret=-0.5; break;
            case 270: ret=0.0; break;
            case 300: ret=0.5; break;
            case 330: ret=0.866025403784439; break;
            case 360: ret=1.0; break;
            default: ret=cos(degrees * 3.14159265358979 / 180);  // it shouldn't get here
        }
        return ret;
    }
    else
        return cos(degrees * 3.14159265358979 / 180);
}

double aaform::aaf_sin(double degrees)
{
    //sin(x) = cos(x + PI / 2)
    return aaf_cos(degrees + 90.0);
}

//Note that this function is specific to Aaform to save time
double aaform::area()
{
    double ret = 0.0;
    //Loop through each triangle with respect to (0, 0) and add the cross multiplication
    for (int i = 0; i + 1 < polysortedsize; i++)
        ret += polysorted[i].x * polysorted[i + 1].y - polysorted[i + 1].x * polysorted[i].y;
    //Take the absolute value over 2
    return aaf_abs(ret) / 2.0;
}

void aaform::sortpoints()
{
    //Why even bother?
    if (polyoverlapsize < 3)
        return;

    //polyoverlap is a triangle, points cannot be out of order
    if (polyoverlapsize == 3)
    {
        polysortedsize = polyoverlapsize - 1;
        polysorted[0].x = polyoverlap[1].x - polyoverlap[0].x;
        polysorted[0].y = polyoverlap[1].y - polyoverlap[0].y;
        polysorted[1].x = polyoverlap[2].x - polyoverlap[0].x;
        polysorted[1].y = polyoverlap[2].y - polyoverlap[0].y;
        return;
    }

    
    aaf_indll * root = new aaf_indll;
    root->next = NULL;

    //begin sorting the points.  Note that the first element is left out and all other elements are offset by it's values
    for (int i = 1; i < polyoverlapsize; i++)
    {
        polyoverlap[i].x = polyoverlap[i].x - polyoverlap[0].x;
        polyoverlap[i].y = polyoverlap[i].y - polyoverlap[0].y;

        aaf_indll * node = root;
        //Loop until the point polyoverlap[i] is can be sorted (counter) clockwiswe (I'm not sure which way it's sorted)
        while (true)
        {
            if (node->next)
            {
                if (polyoverlap[i].x * polyoverlap[node->next->ind].y - polyoverlap[node->next->ind].x * polyoverlap[i].y < 0)
                {
                    //Insert point before this element
                    aaf_indll * temp = node->next;
                    node->next = new aaf_indll;
                    node->next->ind = i;
                    node->next->next = temp;
                    break;
                }
            }
            else
            {
                //Add point to the end of list
                node->next = new aaf_indll;
                node->next->ind = i;
                node->next->next = NULL;
                break;
            }
            node = node->next;
        }
    }

    //We can leave out the first point because it's offset position is going to be (0, 0)
    polysortedsize = 0;

    aaf_indll * node = root;
    aaf_indll * temp;

    //Add the sorted points to polysorted and clean up memory
    while (node)
    {
        temp = node;
        node = node->next;
        if (node)
            polysorted[polysortedsize++] = polyoverlap[node->ind];
        delete temp;
    }
}

//This funciton works for any convex polygon
bool aaform::ptinconvexpolygon(aaf_pnt * p, aaf_pnt pt)
{
    int dir = 0;
    int j;

    //Basically what we are doing is seeing if pt is on the same side of each face of the polygon through cross multiplication
    for (int i = 0; i < 4; i++)
    {
        j = ja[i];
        double cross = (p[i].x - pt.x) * (p[j].y - pt.y) - (p[j].x - pt.x) * (p[i].y - pt.y);

        if (cross == 0)
            continue;

        if (cross > 0)
        {
            if (dir == -1)
                return false;

            dir = 1;
        }
        else
        {
            if (dir == 1)
                return false;

            dir = -1;
        }
    }
    return true;
}

//Finds the area of overlap accross p and the square (0,0)-(1,1)
double aaform::pixoverlap(aaf_pnt * p)
{
    polyoverlapsize = 0;
    polysortedsize = 0;

    double minx, maxx, miny, maxy;
    int j;

    double z;

    for (int i = 0; i < 4; i++)
    {        
        //Search for source points within the destination quadrolateral
        if (p[i].x >= 0 && p[i].x <= 1 && p[i].y >= 0 && p[i].y <= 1)
            polyoverlap[polyoverlapsize++] = p[i];

        //Search for destination points within the source quadrolateral
        if (ptinconvexpolygon(p, corners[i]))
            polyoverlap[polyoverlapsize++] = corners[i];

        //Search for line intersections
        j = ja[i];
        minx = aaf_min(p[i].x, p[j].x);
        miny = aaf_min(p[i].y, p[j].y);
        maxx = aaf_max(p[i].x, p[j].x);
        maxy = aaf_max(p[i].y, p[j].y);

        if (minx < 0.0 && 0.0 < maxx)
        {//Cross left
            z = p[i].y - p[i].x * (p[i].y - p[j].y) / (p[i].x - p[j].x);
            if (z >= 0.0 && z <= 1.0)
            {
                polyoverlap[polyoverlapsize].x = 0.0;
                polyoverlap[polyoverlapsize++].y = z;
            }
        }
        if (minx < 1.0 && 1.0 < maxx)
        {//Cross right
            z = p[i].y + (1 - p[i].x) * (p[i].y - p[j].y) / (p[i].x - p[j].x);
            if (z >= 0.0 && z <= 1.0)
            {
                polyoverlap[polyoverlapsize].x = 1.0;
                polyoverlap[polyoverlapsize++].y = z;
            }
        }
        if (miny < 0.0 && 0.0 < maxy)
        {//Cross bottom
            z = p[i].x - p[i].y * (p[i].x - p[j].x) / (p[i].y - p[j].y);
            if (z >= 0.0 && z <= 1.0)
            {
                polyoverlap[polyoverlapsize].x = z;
                polyoverlap[polyoverlapsize++].y = 0.0;
            }
        }
        if (miny < 1.0 && 1.0 < maxy)
        {//Cross top
            z = p[i].x + (1 - p[i].y) * (p[i].x - p[j].x) / (p[i].y - p[j].y);
            if (z >= 0.0 && z <= 1.0)
            {
                polyoverlap[polyoverlapsize].x = z;
                polyoverlap[polyoverlapsize++].y = 1.0;
            }
        }
    }        

    //Sort the points and return the area
    sortpoints();
    return area();
}

bool aaform::dotransform(HBITMAP src, HBITMAP dst, aaf_callback callbackfunc)
{
    //Get source bitmap's information
    BITMAP srcbmp;
    if (GetObject(src, sizeof(srcbmp), &srcbmp) == 0)
		return false;

    //Get the destination bitmap's information
    BITMAP dstbmp;
    if (GetObject(dst, sizeof(dstbmp), &dstbmp) == 0)
		return false;

    //Create the source dib array and the dstdib array
    RGBQUAD * srcdib = new RGBQUAD[srcbmp.bmWidth * srcbmp.bmHeight];
    aaf_dblrgbquad * dbldstdib = new aaf_dblrgbquad[outwidth * outheight];
	memset(dbldstdib, 0, outwidth * outheight * sizeof(aaf_dblrgbquad));

    //Load source bits into srcdib
    BITMAPINFO srcdibbmap;
    srcdibbmap.bmiHeader.biSize = sizeof(srcdibbmap.bmiHeader);
    srcdibbmap.bmiHeader.biWidth = srcbmp.bmWidth;
    srcdibbmap.bmiHeader.biHeight = -srcbmp.bmHeight;
    srcdibbmap.bmiHeader.biPlanes = 1;
    srcdibbmap.bmiHeader.biBitCount = 32;
    srcdibbmap.bmiHeader.biCompression = BI_RGB;

    //Get the source bits
    HDC ldc = CreateCompatibleDC(0);
    GetDIBits(ldc, src, 0, srcbmp.bmHeight, srcdib, &srcdibbmap, DIB_RGB_COLORS);
    DeleteDC(ldc);

    //Create polygon arrays
    aaf_pnt * p = new aaf_pnt[4];
    aaf_pnt * poffset = new aaf_pnt[4];

    //Loop through the source's pixels
    for (int x = 0; x < srcbmp.bmWidth; x++)
    {
        for (int y = 0; y < srcbmp.bmHeight; y++)
        {
            //Construct the source pixel's rotated polygon from pixelgrid
            p[0] = pixelgrid[x + y * (srcbmp.bmWidth + 1)];
            p[1] = pixelgrid[(x + 1) + y * (srcbmp.bmWidth + 1)];
            p[2] = pixelgrid[(x + 1) + (y + 1) * (srcbmp.bmWidth + 1)];
            p[3] = pixelgrid[x + (y + 1) * (srcbmp.bmWidth + 1)];

            //Find the scan area on the destination's pixels
            int mindx = 0x7FFFFFFF;
            int mindy = 0x7FFFFFFF;
            int maxdx = 0x80000000;
            int maxdy = 0x80000000;
            for (int i = 0; i < 4; i++)
            {
				if (rounddown(p[i].x) < mindx) mindx = rounddown(p[i].x);
                if (roundup(p[i].x) > maxdx) maxdx = roundup(p[i].x);
				if (rounddown(p[i].y) < mindy) mindy = rounddown(p[i].y);
				if (roundup(p[i].y) > maxdy) maxdy = roundup(p[i].y);
            }
            
            int SrcIndex = x + y * srcbmp.bmWidth;

            //loop through the scan area to find where source(x, y) overlaps with the destination pixels
            for (int xx = mindx - 1; xx <= maxdx; xx++)
            {
                if (xx < 0 || xx >= dstbmp.bmWidth)
                    continue;
                for (int yy = mindy - 1; yy <= maxdy; yy++)
                {
                    if(yy < 0 || yy >= dstbmp.bmHeight)
                        continue;

                    //offset p and by (xx,yy) and put that into poffset
                    for (int i = 0; i < 4; i++)
                    {
                        poffset[i].x = p[i].x - xx;
                        poffset[i].y = p[i].y - yy;
                    }
                    
                    //FIND THE OVERLAP *a whole lot of code pays off here*
                    double dbloverlap = pixoverlap(poffset);

                    if (dbloverlap > 0)
                    {
                        int dstindex = xx + yy * outwidth;

                        //Add the rgb and alpha values in proportion to the overlap area
                        dbldstdib[dstindex].red += (double)(srcdib[SrcIndex].rgbRed) * dbloverlap;
                        dbldstdib[dstindex].blue += (double)(srcdib[SrcIndex].rgbBlue) * dbloverlap;
                        dbldstdib[dstindex].green += (double)(srcdib[SrcIndex].rgbGreen) * dbloverlap;
                        dbldstdib[dstindex].alpha += dbloverlap;
                    }
                }
            }
        }
        if (callbackfunc != NULL)
        {
            //Send the callback message
            double percentdone = (double)(x + 1) / (double)(srcbmp.bmWidth);
            if (callbackfunc(percentdone))
            {
                delete [] srcdib;
                delete [] dbldstdib;
                delete [] p;
                delete [] poffset;
                return false;
            }
        }
    }
    
    //Free memory no longer needed
    delete [] p;
    delete [] poffset;
    delete [] srcdib;
    srcdib = NULL;

    //Create final destination bits
    RGBQUAD * dstdib = new RGBQUAD[dstbmp.bmWidth * dstbmp.bmHeight];

    BITMAPINFO dstdibmap;
    dstdibmap.bmiHeader.biSize = sizeof(dstdibmap.bmiHeader);
    dstdibmap.bmiHeader.biWidth = dstbmp.bmWidth;
    dstdibmap.bmiHeader.biHeight = -dstbmp.bmHeight;
    dstdibmap.bmiHeader.biPlanes = 1;
    dstdibmap.bmiHeader.biBitCount = 32;
    dstdibmap.bmiHeader.biCompression = BI_RGB;
    
    //Load the destination bitmap's bits
    ldc = CreateCompatibleDC(0);
    GetDIBits(ldc, dst, 0, dstbmp.bmHeight, dstdib, &dstdibmap, DIB_RGB_COLORS);
    DeleteDC(ldc);

    //Write to dstdib with the information stored in dbldstdib
    for (int x = 0; x < outwidth; x++)
    {
        if (x + outstartx >= dstbmp.bmWidth)
            continue;
        for (int y = 0; y < outheight; y++)
        {
            if (y + outstarty >= dstbmp.bmHeight)
                continue;
            int offindex = x + y * outwidth;
            int dstindex = x + outstartx + (y + outstarty) * dstbmp.bmWidth;

            if (dbldstdib[offindex].alpha > 1)
            {//handles wrap around for non-convex transformations
                dstdib[dstindex].rgbReserved = 0;
                dstdib[dstindex].rgbRed = byterange(dbldstdib[offindex].red / dbldstdib[offindex].alpha);
                dstdib[dstindex].rgbGreen = byterange(dbldstdib[offindex].green / dbldstdib[offindex].alpha);
                dstdib[dstindex].rgbBlue = byterange(dbldstdib[offindex].blue / dbldstdib[offindex].alpha);
            }
            else
            {
                dstdib[dstindex].rgbReserved = 0;
                dstdib[dstindex].rgbRed = byterange(dbldstdib[offindex].red + (1 - dbldstdib[offindex].alpha) * (double)dstdib[dstindex].rgbRed);
                dstdib[dstindex].rgbGreen = byterange(dbldstdib[offindex].green + (1 - dbldstdib[offindex].alpha) * (double)dstdib[dstindex].rgbGreen);
                dstdib[dstindex].rgbBlue = byterange(dbldstdib[offindex].blue + (1 - dbldstdib[offindex].alpha) * (double)dstdib[dstindex].rgbBlue);
            }
        }
    }

    //Clear memory
    delete [] dbldstdib;
    dbldstdib = NULL;

    //Write the bits into the bitmap and return it
    SetDIBits(0, dst, 0, dstbmp.bmHeight, dstdib, &dstdibmap, DIB_RGB_COLORS);
    
    //Clear memory
    delete [] dstdib;
    dstdib = NULL;

    //:D
    return true;
}

bool aaform::transform(HBITMAP src, HBITMAP dst, std::vector<double> xcorner, std::vector<double> ycorner, aaf_callback callbackfunc)
{
    //Make sure the coordinates are valid
    if (xcorner.size() != 4 || ycorner.size() != 4)
        return false;

    //Load the src bitmaps information
    BITMAP srcbmp;
    if (GetObject(src, sizeof(srcbmp), &srcbmp) == 0)
		return false;

    //create the intial arrays
    pixelgrid = new aaf_pnt[(srcbmp.bmWidth + 1) * (srcbmp.bmHeight + 1)];
    polyoverlap = new aaf_pnt[16];
    polysorted = new aaf_pnt[16];
    corners = new aaf_pnt[4];
    
    //Load the corners array
    double dx[] = {0.0, 1.0, 1.0, 0.0};
    double dy[] = {0.0, 0.0, 1.0, 1.0};
    for (int i = 0; i < 4; i++)
    {
        corners[i].x = dx[i];
        corners[i].y = dy[i];
    }

    //Find the rectangle of dst to draw to
    outstartx = rounddown(xcorner[0]);
    outstarty = rounddown(ycorner[0]);
    outwidth = 0;
    outheight = 0;
    for (int i = 1; i < 4; i++)
    {
		if (rounddown(xcorner[i]) < outstartx) outstartx = rounddown(xcorner[i]);
        if (rounddown(ycorner[i]) < outstarty) outstarty = rounddown(ycorner[i]);
    }
    for (int i = 0; i < 4; i++)
    {
		if (roundup(xcorner[i] - outstartx) > outwidth) outwidth = roundup(xcorner[i] - outstartx);
		if (roundup(ycorner[i] - outstarty) > outheight) outheight = roundup(ycorner[i] - outstarty);
    }

    bool res;

    //fill out pixelgrid array
    res = creategrid(srcbmp, xcorner, ycorner);

    if (res)
    {
        //Do the transformation
        res = dotransform(src, dst, callbackfunc);
    }

    //clear memory
    delete [] corners;
    delete [] polysorted;
    delete [] polyoverlap;

    //Return if the function completed properly
    return res;
}

bool aaform::creategrid(BITMAP & srcbmp, std::vector<double> & xcorner, std::vector<double> & ycorner)
{
    //mmm geometry
    double * sideradius = new double[4];
    double * sidecos = new double[4];
    double * sidesin = new double[4];

    //First we find the radius, cos, and sin of each side of the polygon created by xcorner and ycorner
    int j;
    for (int i = 0; i < 4; i++)
    {
        j = ja[i];
        sideradius[i] = sqrt((xcorner[i] - xcorner[j]) * (xcorner[i] - xcorner[j]) + (ycorner[i] - ycorner[j]) * (ycorner[i] - ycorner[j]));
        sidecos[i] = (xcorner[j] - xcorner[i]) / sideradius[i];
        sidesin[i] = (ycorner[j] - ycorner[i]) / sideradius[i];
    }

    //Next we create two lines in Ax + By = C form
    for (int x = 0; x < srcbmp.bmWidth + 1; x++)
    {
        double topdist = ((double)x / (srcbmp.bmWidth)) * sideradius[0];
        double ptxtop =  xcorner[0] + topdist * sidecos[0];
        double ptytop = ycorner[0] + topdist * sidesin[0];

        double botdist = (1.0 - (double)x / (srcbmp.bmWidth)) * sideradius[2];
        double ptxbot = xcorner[2] + botdist * sidecos[2];
        double ptybot = ycorner[2] + botdist * sidesin[2];

        double Ah = ptybot - ptytop;
        double Bh = ptxtop - ptxbot;
        double Ch = Ah * ptxtop + Bh * ptytop;

        for (int y = 0; y < srcbmp.bmHeight + 1; y++)
        {
            double leftdist = (1.0 - (double)y / (srcbmp.bmHeight)) * sideradius[3];
            double ptxleft =  xcorner[3] + leftdist * sidecos[3];
            double ptyleft = ycorner[3] + leftdist * sidesin[3];
    
            double rightdist = ((double)y / (srcbmp.bmHeight)) * sideradius[1];
            double ptxright = xcorner[1] + rightdist * sidecos[1];
            double ptyright = ycorner[1] + rightdist * sidesin[1];

            double Av = ptyright - ptyleft;
            double Bv = ptxleft - ptxright;
            double Cv = Av * ptxleft + Bv * ptyleft;
    
            //Find where the lines intersect and store that point in the pixelgrid array
            double det = Ah * Bv - Av * Bh;
            if (aaf_abs(det) < 1e-9)
            {
                delete [] sidesin;
                delete [] sidecos;
                delete [] sideradius;
                return false;
            }
            else
            {
                int ind = x + y * (srcbmp.bmWidth + 1);
                pixelgrid[ind].x = (Bv * Ch - Bh * Cv) / det;
                pixelgrid[ind].y = (Ah * Cv - Av * Ch) / det;
            }
        }
    }

    delete [] sidesin;
    delete [] sidecos;
    delete [] sideradius;

    //Yayy we didn't fail
    return true;
}

//automatically offsets the corners of the image, creates a bitmap of the required size to fit the image, calls transform, and returns the bitmap it created
HBITMAP aaform::createtransform(HBITMAP src, std::vector<double> xcorner, std::vector<double> ycorner, aaf_callback callbackfunc, int bgcolor)
{
    //Check if it's a valid array
    if (xcorner.size() != 4 || ycorner.size() != 4)
        return NULL;

    //Find the dimensions of the bitmap that needs to be created and offset the corners so that the lowest x value is at 0 and the lowest y is at 0
    RECT rc;
    rc.left = 0;
    rc.right = 0;
    rc.top = 0;
    rc.bottom = 0;

    double offx = xcorner[0];
    double offy = ycorner[0];
    for (int i = 1; i < 4; i++)
    {
		if (xcorner[i] < offx) offx = xcorner[i];
		if (ycorner[i] < offy) offy = ycorner[i];
    }

    for (int i = 0; i < 4; i++)
    {
        xcorner[i] -= offx;
        ycorner[i] -= offy;
		if (roundup(xcorner[i]) > rc.right) rc.right = roundup(xcorner[i]);
        if (roundup(ycorner[i]) > rc.bottom) rc.bottom = roundup(ycorner[i]);
    }

    //Create a temp dc
    HDC ldc = CreateCompatibleDC(0);

    //Create the destination bitmap
    DEVMODE dvmd;
    dvmd.dmSize = sizeof(dvmd);
    EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &dvmd);
    HBITMAP hBmp = CreateBitmap(rc.right, rc.bottom, 1, dvmd.dmBitsPerPel, NULL);

    //Select the bitmap into ldc
    SelectObject(ldc, hBmp);

    //Create a solid brush of color defined by bgcolor
    HBRUSH hBrsh = CreateSolidBrush((COLORREF)bgcolor);

    //Fill the background with this color
    FillRect(ldc, &rc, hBrsh);

    //Delete the brush
    DeleteObject(hBrsh);

    //Delete ldc
    DeleteDC(ldc);

    //do the transformation
    transform(src, hBmp, xcorner, ycorner, callbackfunc);

    //mmm
    return hBmp;
}

//This works just as well as Aarot (might be a little slower due to no specialization for rotations in transform)
HBITMAP aaform::rotate(HBITMAP src, double degrees, aaf_callback callbackfunc, int bgcolor)
{
    //Load the source bitmap's info
    BITMAP srcbmp;
    if (GetObject(src, sizeof(srcbmp), &srcbmp) == 0)
		return false;

    std::vector<double> x, y;

    //Get half the width and half the height of the image
    double hwidth = (double)srcbmp.bmWidth / 2.0;
    double hheight = (double)srcbmp.bmHeight / 2.0;

    double coss = aaf_cos(degrees);
    double sins = aaf_sin(degrees);

    //Find the rotated coordinates, createtransform will offset them so none of them are negative
    x.push_back(coss * -hwidth - sins * -hheight);
    y.push_back(sins * -hwidth + coss * -hheight);
    x.push_back(coss * hwidth - sins * -hheight);
    y.push_back(sins * hwidth + coss * -hheight);
    x.push_back(coss * hwidth - sins * hheight);
    y.push_back(sins * hwidth + coss * hheight);
    x.push_back(coss * -hwidth - sins * hheight);
    y.push_back(sins * -hwidth + coss * hheight);

    //do the rotation using transform
    return createtransform(src, x, y, callbackfunc, bgcolor);
}

HBITMAP aaform::stretch(HBITMAP src, double xratio, double yratio, aaf_callback callbackfunc, int bgcolor)
{
    //Load the source bitmap's info
    BITMAP srcbmp;
    if (GetObject(src, sizeof(srcbmp), &srcbmp) == 0)
		return false;

    std::vector<double> x, y;

    x.push_back(0.0);
    y.push_back(0.0);
    x.push_back(xratio * srcbmp.bmWidth);
    y.push_back(0.0);
    x.push_back(xratio * srcbmp.bmWidth);
    y.push_back(yratio * srcbmp.bmHeight);
    x.push_back(0.0);
    y.push_back(yratio * srcbmp.bmHeight);

    //do the stretch using transform
    return createtransform(src, x, y, callbackfunc, bgcolor);
}

HBITMAP aaform::skewhorizontal(HBITMAP src, double angle, aaf_callback callbackfunc, int bgcolor)
{
    //Load the source bitmap's info
    BITMAP srcbmp;
    if (GetObject(src, sizeof(srcbmp), &srcbmp) == 0)
		return false;

    std::vector<double> x, y;

    double tans = tan(angle / 180.0 * 3.141592653589793);

    x.push_back(tans * srcbmp.bmHeight);
    y.push_back(0.0);
    x.push_back(tans * srcbmp.bmHeight + srcbmp.bmWidth);
    y.push_back(0.0);
    x.push_back(srcbmp.bmWidth);
    y.push_back(srcbmp.bmHeight);
    x.push_back(0.0);
    y.push_back(srcbmp.bmHeight);

    //do the skew using transform
    return createtransform(src, x, y, callbackfunc, bgcolor);
}

HBITMAP aaform::skewverticle(HBITMAP src, double angle, aaf_callback callbackfunc, int bgcolor)
{
    //Load the source bitmap's info
    BITMAP srcbmp;
    if (GetObject(src, sizeof(srcbmp), &srcbmp) == 0)
		return false;

    std::vector<double> x, y;

    double tans = tan(angle / 180.0 * 3.141592653589793);

    x.push_back(0.0);
    y.push_back(tans * srcbmp.bmWidth);
    x.push_back(srcbmp.bmWidth);
    y.push_back(0.0);
    x.push_back(srcbmp.bmWidth);
    y.push_back(srcbmp.bmHeight);
    x.push_back(0.0);
    y.push_back(tans * srcbmp.bmWidth + srcbmp.bmHeight);

    //do the skew using transform
    return createtransform(src, x, y, callbackfunc, bgcolor);
}

#endif
