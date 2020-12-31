#if !defined(AFX_UIANIM_H__20050522_5560_2E48_0B2D_0080AD509054__INCLUDED_)
#define AFX_UIANIM_H__20050522_5560_2E48_0B2D_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////////////
//

typedef enum
{
   UIANIMTYPE_FLAT,
   UIANIMTYPE_SWIPE,
} UITYPE_ANIM;


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CAnimJobUI
{
public:
   CAnimJobUI(const CAnimJobUI& src);
   CAnimJobUI(UITYPE_ANIM AnimType, DWORD dwStartTick, DWORD dwDuration, COLORREF clrBack, COLORREF clrKey, RECT rcFrom, int xtrans, int ytrans, int ztrans, int alpha, float zrot);

   typedef enum
   {
      INTERPOLATE_LINEAR,
      INTERPOLATE_COS,
   } INTERPOLATETYPE;

   typedef struct PLOTMATRIX
   {
      int xtrans;
      int ytrans;
      int ztrans;
      int alpha;
      float zrot;
   } PLOTMATRIX;

   UITYPE_ANIM AnimType;
   DWORD dwStartTick;
   DWORD dwDuration;
   int iBufferStart;
   int iBufferEnd;
   union
   {
      struct 
      {
         COLORREF clrBack;
         COLORREF clrKey;
         RECT rcFrom;
         PLOTMATRIX mFrom;
         INTERPOLATETYPE iInterpolate;
      } plot;
   } data;
};



#endif // !defined(AFX_UIANIM_H__20050522_5560_2E48_0B2D_0080AD509054__INCLUDED_)

