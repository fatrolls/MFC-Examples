#include "stdafx.h"
#include "GlFont.h"

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

CGlFont::CGlFont()
{
	m_hFont=NULL;
	InitFont("����");
	m_fExtrusion = 0.1f;
}

CGlFont::~CGlFont()
{
	DeleteFont();
}

LOGFONT CGlFont::GetLogFont()
{
	LOGFONT lf;
	GetObject(m_hFont,sizeof(LOGFONT),&lf);
	return lf;
}

void CGlFont::DeleteFont()
{
	if(m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont=NULL;
	}
}

bool CGlFont::InitFont(LOGFONT &lf)
{
	DeleteFont();
	m_hFont=CreateFontIndirect(&lf);
	if( m_hFont )return true;
	else return false;;
}

bool CGlFont::InitFont(const char *fontName)
{
	DeleteFont();
	m_hFont = CreateFont(
		-16,									//< lfHeight ����߶�
		0,										//< lfWidth ������� 
		0,										//< lfEscapement �������ת�Ƕ� Angle Of Escapement 
		0,										//< lfOrientation ������ߵ���ת�Ƕ�Orientation Angle 
		FW_BOLD,								//< lfWeight ��������� 
		FALSE,									//< lfItalic �Ƿ�ʹ��б�� 
		FALSE,									//< lfUnderline �Ƿ�ʹ���»��� 
		FALSE,									//< lfStrikeOut �Ƿ�ʹ��ɾ���� 
		GB2312_CHARSET,							//< lfCharSet �����ַ��� 
		OUT_TT_PRECIS,							//< lfOutPrecision ������� 
		CLIP_DEFAULT_PRECIS,					//< lfClipPrecision �ü����� 
		ANTIALIASED_QUALITY,					//< lfQuality ������� 
		FF_DONTCARE|DEFAULT_PITCH,				//< lfPitchAndFamily Family And Pitch 
		fontName);								//< lfFaceName �������� 
	if(m_hFont)return true;
	else return false;
}

// ��ָ��λ������ַ��� 
void CGlFont::Draw2DTextByGdi(const char *string, float x, float y)
{
	if(strlen(string)<=0)return;

	HBITMAP hBitmap,hOldBmp;									//< ��������λͼ��� 
	BITMAP bm;													//< λͼ�ṹ���� 
	SIZE size;													//< λͼ�ߴ� 

	GLboolean lp,tp,dp;
	HDC hDC = ::CreateCompatibleDC(NULL);						//< �ݴ��豸���� 
	glGetBooleanv(GL_LIGHTING,&lp);								//< �鿴�������Ƿ��й��� 
	glGetBooleanv(GL_TEXTURE_2D,&tp);							//< �鿴�������Ƿ��������� 
	glGetBooleanv(GL_DEPTH_TEST,&dp);							//< �鿴�������Ƿ��������� 
	// ���������һЩ���� 
	//glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(0,0,-10.0f);
	glDisable(GL_LIGHTING);										//< �رչ��� 
	glDisable(GL_TEXTURE_2D);									//< �ر����� 
	glDisable(GL_DEPTH_TEST);									//< �ر���Ȳ��� 

	HFONT hOldFont=NULL;
	hOldFont=(HFONT)SelectObject(hDC, m_hFont);					//< ѡ������ 
	if(!hOldFont)
	{
		return;
	}
	::GetTextExtentPoint32(hDC, string, strlen(string), &size);	//< ��ȡ�ַ�λͼ��С 
	hBitmap = CreateBitmap(size.cx, size.cy,1, 1, NULL);		//< ������hDC��ص�ɫλͼ 
	hOldBmp = (HBITMAP)SelectObject(hDC,hBitmap);				//< ѡ��λͼ 

	SetBkColor(hDC, RGB(0, 0, 0));								//< ����ɫΪ��ɫ 
	SetTextColor(hDC, RGB(255, 255, 255));						//< ������ɫ��ɫ 
	SetBkMode(hDC, OPAQUE);										//< �õ�ǰ�ı�����ɫ��䱳�� 
	TextOut(hDC, 0, 0, string, strlen(string));					//< ������ֵ��ݴ�hDC 
	
	SelectObject(hDC, hOldFont);

	// ������λͼ���ݽṹ 
	GetObject(hBitmap, sizeof(bm), &bm);
	size.cx = (bm.bmWidth + 31) & (~31);						//< ��Ե���� 
	size.cy = bm.bmHeight;
	int bufsize = size.cx * size.cy/8;							//< ͼ�����ݳ��� 
	
	//�����嵥ɫλͼ�ṹ  
	struct
	{
		BITMAPINFOHEADER bih;
		RGBQUAD col[2];
	}bic;

	// ��ȡ��ɫλͼ�ṹ��Ϣ 
	BITMAPINFO *binf = (BITMAPINFO *)&bic;
	binf->bmiHeader.biSize = sizeof(binf->bmiHeader);			//< �޸Ľṹ��Ϣ 
	binf->bmiHeader.biWidth = bm.bmWidth;
	binf->bmiHeader.biHeight = bm.bmHeight;
	binf->bmiHeader.biPlanes = 1;
	binf->bmiHeader.biBitCount = 1;								//< ��ɫ 
	binf->bmiHeader.biCompression = BI_RGB;						//< ��ɫ��ʽ 
	binf->bmiHeader.biSizeImage = bufsize;
	binf->bmiHeader.biXPelsPerMeter = 1;
	binf->bmiHeader.biYPelsPerMeter = 1;
	binf->bmiHeader.biClrUsed = 0;
	binf->bmiHeader.biClrImportant = 0;

	// ����ͼ�����ݿ�  
	UCHAR* pBmpBits = new UCHAR[bufsize];    
	memset(pBmpBits, 0, sizeof(UCHAR)*bufsize);
	// ���豸�޹����ݱ�����pBmpBitsָ������ݿ��� 
	::GetDIBits(hDC, hBitmap, 0, bm.bmHeight, pBmpBits, binf,DIB_RGB_COLORS);

	// ��ʾ�ַ��� 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);						//< ָ�����ش洢ģʽ 
	glRasterPos2f(x, y);										//< ��λ 
	glBitmap(size.cx, size.cy, 0.0, 0.0, 0.0, 0.0, pBmpBits);	//< λͼ��ʾ 

	delete []pBmpBits;											//< ɾ��ָ�� 
	SelectObject(hDC, hOldBmp);									//< �ָ�ԭ��λͼ��Ϣ 
	DeleteObject(hBitmap);
	::DeleteDC(hDC);

	// �ָ�һЩ���� 
	if(lp) glEnable(GL_LIGHTING);								//< ���ù��� 
	if(tp) glEnable(GL_TEXTURE_2D);								//< �������� 
	if(dp) glEnable(GL_DEPTH_TEST);								//< ������Ȳ��� 

	//glPopMatrix();
}

void CGlFont::Draw2DText(const char *string, float x, float y)
{
	if(strlen(string)<=0)return;

	//HDC hDC=wglGetCurrentDC();
	HDC hDC = ::CreateCompatibleDC(NULL);

	HFONT hOldFont = (HFONT)SelectObject(hDC,m_hFont);
	if(!hOldFont)
	{
		return;
	}

	glRasterPos2f(x, y);

	DWORD dwChar;
	int ListNum;
	for(size_t i=0;i<strlen((char *)string);i++)
	{
		if(IsDBCSLeadByte(string[i]))
		{
			dwChar=((unsigned char)string[i])*0x100+(unsigned char)string[i+1];
			i++;
		}
		else
		{
			dwChar=string[i];
		}
		ListNum=glGenLists(1);
		wglUseFontBitmaps(hDC,dwChar,1,ListNum);
		glCallList(ListNum);
		glDeleteLists(ListNum,1);
	}
	
	SelectObject(hDC,hOldFont);
	::DeleteDC(hDC);
}

float CGlFont::Draw3DText(const char *string)
{
	if(strlen(string)<=0)return 0.0;

	//
	glPushMatrix();

	GLYPHMETRICSFLOAT pgmf[1];
	//HDC hDC=wglGetCurrentDC();
	HDC hDC = ::CreateCompatibleDC(NULL);

	//���õ�ǰ����
	HFONT hOldFont = (HFONT)SelectObject(hDC,m_hFont);
	if(!hOldFont)
	{
		return 0.0;
	}
	DWORD dwChar;
	int ListNum;

	float length = 0.0;
	for(size_t i=0;i<strlen((char *)string);i++)
	{
		if(IsDBCSLeadByte(string[i]))
		{
			dwChar=((unsigned char)string[i])*0x100+(unsigned char)string[i+1];
			i++;
		}
		else
		{
			dwChar=string[i];
		}
		ListNum=glGenLists(1);
		wglUseFontOutlines(hDC,dwChar,1,ListNum,0.0,m_fExtrusion,WGL_FONT_POLYGONS,pgmf);
		glCallList(ListNum);
		//Get the length of this character
		length += pgmf[0].gmfCellIncX;
		glDeleteLists(ListNum,1);
	}
	
	SelectObject(hDC,hOldFont);
	::DeleteDC(hDC);

	//
	glPopMatrix();

	return length;
}

float CGlFont::Get3DLength(const char *string)
{
	if(strlen(string)<=0)return 0.0;
	
	GLYPHMETRICSFLOAT pgmf[1];
	//HDC hDC=wglGetCurrentDC();
	HDC hDC = ::CreateCompatibleDC(NULL);
	
	//���õ�ǰ����
	HFONT hOldFont = (HFONT)SelectObject(hDC,m_hFont);
	if(!hOldFont)
	{
		return 0.0;
	}
	DWORD dwChar;
	int ListNum;
	
	float length = 0.0;
	for(size_t i=0;i<strlen((char *)string);i++)
	{
		if(IsDBCSLeadByte(string[i]))
		{
			dwChar=((unsigned char)string[i])*0x100+(unsigned char)string[i+1];
			i++;
		}
		else
		{
			dwChar=string[i];
		}
		ListNum=glGenLists(1);
		wglUseFontOutlines(hDC,dwChar,1,ListNum,0.0,m_fExtrusion,WGL_FONT_POLYGONS,pgmf);
		//Get the length of this character
		length += pgmf[0].gmfCellIncX;
		glDeleteLists(ListNum,1);
	}
	
	SelectObject(hDC,hOldFont);
	::DeleteDC(hDC);
	
	return length;
}