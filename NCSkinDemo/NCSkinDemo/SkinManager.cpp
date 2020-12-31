#include "StdAfx.h"
#include "SkinManager.h"

CSkinManager* CSkinManager::m_Instance = NULL;

CSkinManager::CSkinManager()
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CSkinManager::~CSkinManager()
{
	map<CString,Image*>::iterator iter;
	for (iter = m_mapSkinItems.begin();iter != m_mapSkinItems.end();iter++)
	{
		delete iter->second;
	}

	GdiplusShutdown(gdiplusToken);

}

CSkinManager* CSkinManager::GetInstance()
{
	if (m_Instance==NULL)
	{
		m_Instance = new CSkinManager;
	}

	return m_Instance;
}

void  CSkinManager::SetSkinPath(LPCTSTR lpszSkinPath)
{
	m_strSkinPath = lpszSkinPath;
}

CString CSkinManager::GetSkinPath()
{
	return m_strSkinPath;
}

Image* CSkinManager::GetSkinItem(LPCTSTR lpszFileName)
{
	Image* pImage = NULL;
	map<CString,Image*>::iterator iter;
	iter = m_mapSkinItems.find(lpszFileName);
	if (iter == m_mapSkinItems.end())
	{
		CString strImgPath = m_strSkinPath+lpszFileName;
		m_mapSkinItems[lpszFileName] = (Image*)Bitmap::FromFile(strImgPath);
		pImage = m_mapSkinItems[lpszFileName];
	}
	else
	{
		pImage = iter->second;
	}

	return pImage;
}

void  CSkinManager::UnLoadSkin()
{
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}