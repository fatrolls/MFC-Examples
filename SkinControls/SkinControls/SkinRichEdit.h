
#ifndef SKIN_RICHEDIT_H_
#define SKIN_RICHEDIT_H_
#pragma once

#include "SkinControlsDefine.h"
#include <RichOle.h>
#include "SkinScrollBar.h"

// 图像对象
class SKIN_CONTROLS_EXPORT CImageDataObject : public IDataObject
{
public:
	// 构造函数
	CImageDataObject();
	// 析构函数
	virtual ~CImageDataObject();

	// 基础接口
public:
	// 增加引用
	virtual ULONG STDMETHODCALLTYPE AddRef();
	// 释放对象
	virtual ULONG STDMETHODCALLTYPE Release();
	// 查询接口
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject);

	// 对象接口
public:
	// 获取数据
	virtual HRESULT STDMETHODCALLTYPE GetData(FORMATETC* pformatetcIn, STGMEDIUM* pStgMedium);
	// 设置数据
	virtual HRESULT STDMETHODCALLTYPE SetData(FORMATETC* pFormatEtc, STGMEDIUM* pStgMedium, BOOL fRelease);

	// 其他接口
public:
	virtual HRESULT STDMETHODCALLTYPE DUnadvise(DWORD dwConnection) { return E_NOTIMPL; }
	virtual HRESULT STDMETHODCALLTYPE QueryGetData(FORMATETC* pFormatEtc) { return E_NOTIMPL; }
	virtual HRESULT STDMETHODCALLTYPE EnumDAdvise(IEnumSTATDATA** ppenumAdvise) { return E_NOTIMPL; }
	virtual HRESULT STDMETHODCALLTYPE GetDataHere(FORMATETC * pFormatEtc, STGMEDIUM*  pStgMedium ) { return E_NOTIMPL; }
	virtual HRESULT STDMETHODCALLTYPE EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** ppenumFormatEtc ) { return E_NOTIMPL; }
	virtual HRESULT STDMETHODCALLTYPE GetCanonicalFormatEtc(FORMATETC* pFormatEtcIn, FORMATETC * pFormatEtcOut) { return E_NOTIMPL; }
	virtual HRESULT STDMETHODCALLTYPE DAdvise(FORMATETC* pFormatEtc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection) { return E_NOTIMPL; }

	// 配置函数
public:
	// 设置图片
	bool SetImage(HBITMAP hBitmap);
	// 加载图片
	bool LoadImage(LPCTSTR pszFileName);
	// 加载图片
	bool LoadImage(HINSTANCE hInstance, LPCTSTR lpBitmapName);

	// 图片函数
public:
	// 获取图片
	HBITMAP GetBitmap() { return m_StgMedium.hBitmap; }
	// 获取信息
	bool IntercalateReObject(REOBJECT& ReObject, IOleClientSite* pIOleClientSite, WORD wIndex);

	// 内核变量
private:
	ULONG m_ulRefCnt; // 引用计数
	STGMEDIUM m_StgMedium; // 对象信息
	FORMATETC m_FormatEtc; // 对象信息

	// 接口变量
private:
	IStorage* m_pIStorage; // 对象接口
	IOleObject* m_pIOleObject; // 对象接口
};

//////////////////////////////////////////////////////////////////////////////////

// 消息框类
class SKIN_CONTROLS_EXPORT CSkinRichEdit : public CRichEditCtrl
{
public:
	// 构造函数
	CSkinRichEdit();
	// 析构函数
	virtual ~CSkinRichEdit();

	// 重载函数
protected:
	// 控件绑定
	virtual void PreSubclassWindow();

	// 功能函数
public:
	// 清除屏幕
	bool CleanScreen();
	// 加载消息
	bool LoadMessage(LPCTSTR pszFileName);
	// 保存信息
	bool SaveMessage(LPCTSTR pszFileName);
	// 允许右键菜单
	void EnableRightMenu(bool bEnable) { m_bEnableMenu = bEnable; }

	// 图片插入
public:
	// 插入图片
	bool InsertImage(LPCTSTR pszImage, WORD wIndex);
	// 插入图片
	bool InsertImage(CBitmap* pBitmap, WORD wIndex);
	// 插入对象
	bool InsertDataObject(CImageDataObject* pDataObject, WORD wIndex);

	// 字串插入
public:
	// 插入字串
	bool InsertString(LPCTSTR pszString, COLORREF crTextColor);
	// 插入字串
	bool InsertString(LPCTSTR pszString, COLORREF crTextColor, COLORREF crBackColor);

	// 超级链接
public:
	// 插入字串
	bool InsertHyperLink(LPCTSTR pszString);
	// 插入字串
	bool InsertHyperLink(LPCTSTR pszString, COLORREF crBackColor);
	// 替换OLE
	void ReplaceREOBJ();

	// 辅助函数
protected:
	// 插入字串
	bool InsertString(LPCTSTR pszString, CHARFORMAT2& CharFormat);
	// 加载回调
	static DWORD CALLBACK LoadCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb);
	// 保存回调
	static DWORD CALLBACK SaveCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb);

	// 内部函数
protected:
	// 字符判断
	bool EfficacyUrlChar(TCHAR chChar);
	// 地址判断
	bool EfficacyUrlString(LPCTSTR pszUrl);

	// 菜单命令
protected:
	// 删除信息
	void OnClearAll();
	// 全部选择
	void OnSelectAll();
	// 拷贝字符
	void OnCopyString();
	// 保存信息
	void OnSaveString();
	// 删除字符
	void OnDeleteString();

	// 消息映射
protected:
	// 销毁消息
	void OnDestroy();
	// 创建消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 右键消息
	void OnRButtonDown(UINT nFlags, CPoint point);
	// 设置光标
	BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()

	// 接口变量
protected:
	IRichEditOle* m_pIRichEditOLE; // 接口指针
	bool m_bEnableMenu; // 允许菜单
	CSkinScrollBar m_SkinScrollBar; // 滚动条类
};

#endif // SKIN_RICHEDIT_H_