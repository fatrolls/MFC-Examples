
#ifndef SKIN_CONTROLS_DEFINE_H_
#define SKIN_CONTROLS_DEFINE_H_
#pragma once

#ifndef SKIN_CONTROLS_EXPORT
#ifdef SKIN_CONTROLS_DLL
#define SKIN_CONTROLS_EXPORT _declspec(dllexport)
#else 
#define SKIN_CONTROLS_EXPORT _declspec(dllimport)
#endif
#endif

#ifdef _DEBUG
#define SKIN_CONTROLS_DLL_NAME TEXT("SkinControlsD.dll")
#else
#define SKIN_CONTROLS_DLL_NAME TEXT("SkinControls.dll")
#endif

#define SKIN_CHILD_WINDOW (WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS)
#define SKIN_POPUP_WINDOW (WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS)

// 数组维数
#define CountArray(Array) (sizeof(Array) / sizeof(Array[0]))

// 删除指针
#define  SafeDelete(pData) { try { delete pData; } catch (...) { ASSERT(FALSE); } pData = NULL; }

// 删除数组
#define  SafeDeleteArray(pData) { try { delete []pData; } catch (...) { ASSERT(FALSE); } pData=NULL; }

// 接口释放
#define  SafeRelease(pObject) { if (pObject != NULL) { pObject->Release(); pObject=NULL; } }

// 透明色
#define MASK_COLOR	(RGB(255,0,255))

#endif // SKIN_CONTROLS_DEFINE_H_