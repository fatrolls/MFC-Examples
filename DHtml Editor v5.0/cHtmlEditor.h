
// ************************************************************************
// Internet Explorer HTML Editor class written by ElmüSoft for Code Project
//
//            www.codeproject.com/KB/cpp/DHTMLEditor.aspx
//            www.netcult.ch/elmue
// ************************************************************************


#pragma once

// Remove warning CRegKey::SetValue is deprecated
#pragma warning(disable : 4996)

#include <atlbase.h>    // CComPtr
#include <afxhtml.h>    // CHtmlEditView
#include "FastString.h"

#define WM_IDLEUPDATECMDUI  0x0363

#define _HKLM  HKEY_LOCAL_MACHINE
#define _HKCU  HKEY_CURRENT_USER
#define _HKCR  HKEY_CLASSES_ROOT

#if _MSC_VER <= 1200 // Visual Studio 6.0
#error "This code is written for Visual Studio 7. Download the version for Visual Studio 6 instead from CodeProject.com!"
#endif

#define HTMLEDIT_INIT_DONE   5000
#define HTMLEDIT_UPDATE_UI   5001
#define HTMLEDIT_KILLFOCUS   5002
#define HTMLEDIT_SETDEFAULT  5003
#define HTMLEDIT_NAVIGATED   5004
#define IDM_FONTSIZE_STYLE   5005
#define ID_TIMER_WAIT_BUSY   5006

#define DEFAULT_FONT_SIZE_INT      14
#define DEFAULT_FONT_SIZE_STR  _T("14")
#define DEFAULT_FONT_FAMILY    _T("Arial")

// This value defines how much each TAB ("\t") indents in the Richedit Source editor
#define RICHEDIT_INDENTATION   300

// Print a comment at the top of the exported HTML 5 code about the implemented styles
#define PRINT_HINT_IMPLEMENTED_STYLES  TRUE

class CHtmlEditor : public CHtmlEditView
{
public:

	// Forward declarations of embedded classes
	class cHtmlStyleSheet;
	class cHtmlDomNode;
	class cHtmlElement;
	class cHtmlTableCell;
	class cHtmlTableRow;
	class cHtmlTable;
	class cHtmlHR;
	class cHtmlImg;
	class cHtmlDocument;

	class CUniRichEdit;
	class cMisc;
	class CMsieWnd;
	class cStreamReader;

	// ####################################################

	class cMisc
	{
	public:
		static CString DecodeMime(CString s_Text);
		static CString EncodeHtml(const WCHAR* u16_Html);
		static void    EncodeHtml(const WCHAR *u16_In, UINT *pu32_WcharToCopy, char *s8_Out, UINT *pu32_OutSize);
		static void    ReplaceAmp(CString* ps_Html);
		static CString VarToStr(CComVariant &v_Variant);
		static CString RemoveTag(CString s_Html, CString s_Tag);
		static CString CutString(CString s_In, CString s_Cut, BOOL b_End);
		static void    RegWriteString(HKEY h_Class, CString s_Path, CString s_Key, CString s_Value);
		static void    RegWriteDword (HKEY h_Class, CString s_Path, CString s_Key, DWORD u32_Value);
		static void    MapToString(CMapStringToString* pi_Map, const TCHAR* s_Format, CFastString* ps_Out);
		static BOOL    IsEqualObject(IUnknown* p_Com1, IUnknown* p_Com2);
	};

	// ####################################################


	// It's really stupid: But template classes must be defined in the header file
	
	// IHTML_INTERFACE = IHTMLRuleStyle or IHTMLStyle

	template <class IHTML_INTERFACE>
	class cHtmlStyle : public cMisc
	{
	public:
		enum eProp
		{
			E_BackgColor = 0,
			E_ForeColor,   // text color
			E_Border,
			E_BorderWidth,
			E_BorderStyle,
			E_BorderColor,
			E_FontSize,
			E_FontFamily,
			E_Width,
			E_Height,
			E_Decoration,
			E_MarginLeft,
			E_MarginTop,
			// to be expanded here.. (update also __StyleNames !!)
			E_LAST_STYLE
		};

		// These definitions must have the same order as enum eProp !
		// C2059: syntax error : 'string' is caused by a
		// Compiler bug: Don't put a space behind "\" here !!!!!!!!!!
		#define __StyleNames { _T("background-color"), \
							   _T("color"),            \
							   _T("border"),           \
							   _T("border-width"),     \
							   _T("border-style"),     \
							   _T("border-color"),     \
							   _T("font-size"),        \
							   _T("font-family"),      \
							   _T("width"),            \
							   _T("height"),           \
							   _T("text-decoration"),  \
							   _T("margin-left"),      \
							   _T("margin-top")        }


		cHtmlStyle(CComPtr<IHTML_INTERFACE> i_Style)
		{
			mi_Style = i_Style;
		}

		virtual BOOL Valid()
		{
			return (mi_Style != NULL);
		}

		CString GetProperty(eProp e_Prop)
		{
			CComVariant v_Value;
			v_Value.vt = VT_BSTR;

			switch (e_Prop)
			{
				case E_BackgColor:  mi_Style->get_backgroundColor(&v_Value);         break;
				case E_ForeColor:   mi_Style->get_color          (&v_Value);         break;
				case E_FontSize:    mi_Style->get_fontSize       (&v_Value);         break;
				case E_FontFamily:  mi_Style->get_fontFamily     (&v_Value.bstrVal); break;
				case E_Border:      mi_Style->get_border         (&v_Value.bstrVal); break;
				case E_BorderWidth: mi_Style->get_borderWidth    (&v_Value.bstrVal); break;
				case E_BorderStyle: mi_Style->get_borderStyle    (&v_Value.bstrVal); break;
				case E_BorderColor: mi_Style->get_borderColor    (&v_Value.bstrVal); break;
				case E_Width:       mi_Style->get_width          (&v_Value);         break;
				case E_Height:      mi_Style->get_height         (&v_Value);         break;
				case E_Decoration:  mi_Style->get_textDecoration (&v_Value.bstrVal); break;
				case E_MarginLeft:  mi_Style->get_marginLeft     (&v_Value);         break;
				case E_MarginTop:   mi_Style->get_marginTop      (&v_Value);         break;
				// to be expanded here .......
				default: return _T("");
			}
			return VarToStr(v_Value);
		}

		BOOL SetProperty(eProp e_Prop, CString& s_Value)
		{
			CComVariant v_Value(s_Value);
			switch (e_Prop)
			{
				case E_BackgColor:  return SUCCEEDED(mi_Style->put_backgroundColor(v_Value));
				case E_ForeColor:   return SUCCEEDED(mi_Style->put_color          (v_Value));
				case E_FontSize:    return SUCCEEDED(mi_Style->put_fontSize       (v_Value));
				case E_FontFamily:  return SUCCEEDED(mi_Style->put_fontFamily     (v_Value.bstrVal));
				case E_Border:      return SUCCEEDED(mi_Style->put_border         (v_Value.bstrVal));
				case E_BorderWidth: return SUCCEEDED(mi_Style->put_borderWidth    (v_Value.bstrVal));
				case E_BorderStyle: return SUCCEEDED(mi_Style->put_borderStyle    (v_Value.bstrVal));
				case E_BorderColor: return SUCCEEDED(mi_Style->put_borderColor    (v_Value.bstrVal));
				case E_Width:       return SUCCEEDED(mi_Style->put_width          (v_Value));
				case E_Height:      return SUCCEEDED(mi_Style->put_height         (v_Value));
				case E_Decoration:  return SUCCEEDED(mi_Style->put_textDecoration (v_Value.bstrVal));
				case E_MarginLeft:  return SUCCEEDED(mi_Style->put_marginLeft     (v_Value));
				case E_MarginTop:   return SUCCEEDED(mi_Style->put_marginTop      (v_Value));
				// to be expanded here .......
				default:            return FALSE;
			}
		}

		// ATTENTION: This function returns only the properties that have been defined in eProp
		void GetPropertyMap(CMapStringToString* pi_Map)
		{
			static CString s_Props[] = __StyleNames;

			for (int i=0; i<E_LAST_STYLE; i++)
			{
				CString s_Value = GetProperty((eProp)i);
				if (s_Value.IsEmpty())
					continue;

				pi_Map->SetAt(s_Props[i], s_Value);
			}
		}

	protected:
		CComPtr<IHTML_INTERFACE> mi_Style;
	};


	// ####################################################

	class cHtmlStyleSheet : public cMisc
	{
	public:
		cHtmlStyleSheet(CComPtr<IHTMLStyleSheet> i_Sheet);

		virtual BOOL Valid();
		cHtmlStyle<IHTMLRuleStyle> GetRule(CString s_Selector);
		BOOL SetProperty(CString s_Selector, cHtmlStyle<IHTMLRuleStyle>::eProp e_Prop, CString s_Value);
		void GetHtmlW3C(int s32_Indent, CFastString* ps_Out);

	protected:
		BOOL AddRule(CString s_Selector, cHtmlStyle<IHTMLRuleStyle>::eProp e_Prop, CString s_Value);

		CComPtr<IHTMLStyleSheet>                mi_Sheet;
		CComPtr<IHTMLStyleSheetRulesCollection> mi_Collect;
	};


	// ####################################################

	class cHtmlDomNode : public cMisc
	{
	public:
		enum eDomNode
		{
			E_DomNodeElement = 1,
			E_DomNodeText    = 3,
			E_DomNodeComment = 8,
		};

		cHtmlDomNode(CComPtr<IHTMLDOMNode> i_Dom);

		virtual BOOL Valid();
		cHtmlElement NextSibling();
		cHtmlElement PreviousSibling();
		BOOL Remove();
		BOOL Strip();
		cHtmlElement AppendChild(cHtmlElement i_NewChild);
		BOOL GetHtmlW3C(CFastString* ps_OuterHtml, cHtmlDocument* pi_ParentDoc, int s32_Indent=0);

	protected:
		CComQIPtr<IHTMLDOMNode, &IID_IHTMLDOMNode> mi_Dom;
	};


	// ####################################################

	class cHtmlElement : public cHtmlDomNode
	{
	public:
		cHtmlElement(CComPtr<IHTMLElement> i_Elem);
		const cHtmlElement& operator=(const cHtmlElement& El);
		operator CComPtr<IHTMLElement>();

		virtual BOOL Valid();
		CString GetTagName();
		CString GetClassName();
		cHtmlElement GetParent();
		UINT GetChildCollection(CComQIPtr<IHTMLElementCollection> &i_Collect);
		cHtmlElement FindParent(CString s_Tag);
		cHtmlElement SkipParents(CString s_Tags);
		CString GetAttribute(CString s_AttrName);
		void    GetAttribsAndStylesMap (CMapStringToString* pi_AttrMap, CMapStringToString* pi_StyleMap);
		void    TransferAttribsToStyles(CMapStringToString* pi_AttrMap, CMapStringToString* pi_StyleMap);
		BOOL SetAttribute(CString s_AttrName, CString s_Value);
		BOOL RemoveAttribute(CString s_AttrName);
		CString GetInnerText();
		BOOL SetInnerHtml(CString s_Html);
		BOOL IsEmpty();
		CString GetInnerHtml();
		CString GetOuterHtml();
		BOOL InsertHtml(CString s_Html, BOOL b_AtBegin, BOOL b_Inside);
		cHtmlStyle<IHTMLStyle> GetStyle();
		cHtmlElement AppendNewChild(CString s_Tag);

		static cHtmlElement GetElementFromCollection(UINT u32_Index, CComQIPtr<IHTMLElementCollection> &i_Collect);

	protected:
		CComQIPtr<IHTMLElement, &IID_IHTMLElement> mi_Elem;
	};

	// ####################################################

	class cHtmlTableCell : public cHtmlElement
	{
	public:
		cHtmlTableCell(CComPtr<IHTMLElement> i_Elem);

		virtual BOOL Valid();
		cHtmlTableRow GetParentRow();
		cHtmlTable    GetParentTable();
		BOOL SetColSpan(UINT Span);
		UINT GetCellIndex();
		UINT GetColIndex();
		UINT GetRowIndex();
		UINT GetColSpan();
		UINT GetRowSpan();
		BOOL Combine();
		void Split();
		BOOL SetInnerHtml(CString s_Html);
		void    SetBgColor(CString s_Color);
		CString GetBgColor();

	protected:
		CComQIPtr<IHTMLTableCell, &IID_IHTMLTableCell> mi_Cell;
	};

	// ####################################################

	class cHtmlTableRow : public cHtmlElement
	{
	public:
		cHtmlTableRow(CComPtr<IHTMLElement> i_Elem);

		virtual BOOL Valid();
		UINT GetCellCount();
		UINT GetRowIndex();
		BOOL DeleteCell(UINT Index);
		BOOL DeleteColumn(UINT Index);
		cHtmlTableCell InsertColumn(UINT Index);
		cHtmlTableCell GetCell     (UINT Index);
		cHtmlTableCell GetColumn   (UINT Index, BOOL b_ReturnPrevious =FALSE);
		cHtmlTableCell InsertCell  (UINT Index);
		cHtmlTable GetParentTable();

	protected:
		CComQIPtr<IHTMLTableRow, &IID_IHTMLTableRow> mi_Row;
	};

	// ####################################################

	class cHtmlTable : public cHtmlElement
	{
	public:
		enum eRules // Table border
		{
			E_RulesAll  = 0,  // Horizontal lines, vertical lines and box
			E_RulesHor  = 1,  // Horizontal lines and box
			E_RulesVert = 2,  // Vertikal   lines and box
			E_RulesBox  = 3   // Only Box (border around)
		};
		cHtmlTable(CComPtr<IHTMLElement> i_Elem);

		virtual BOOL Valid();
		CString GetBgColor();
		void SetBgColor(CString s_Color);
		BOOL DeleteRow(UINT Index);
		BOOL DeleteColumn(UINT Index);
		cHtmlTableRow GetRow   (UINT Index);
		cHtmlTableRow InsertRow(UINT Index, int CellCount);
		BOOL InsertColumn(UINT Index);
		BOOL GetSpanMap(UINT *pu32_Rows, UINT *pu32_Cols, UINT **ppu32_Map);
		void CleanUp();
		UINT GetColumnCount();
		UINT GetRowCount();
		cHtmlTableCell GetCell(UINT u32_Row, UINT u32_Column, BOOL b_ReturnPrevious=FALSE);
		CString GetCellPadding();
		BOOL SetCellPadding(CString s_Padding);
		CString GetCellSpacing();
		BOOL SetCellSpacing(CString s_Spacing);
		CString GetBorderWidth();
		BOOL SetBorderWidth(CString s_Width);
		CString GetBorderColor();
		BOOL SetBorderColor(CString s_Color);
		eRules GetBorderRules();
		BOOL SetBorderRules(eRules e_Rules);

	protected:
		CComQIPtr<IHTMLTable, &IID_IHTMLTable> mi_Table;
	};

	// ####################################################

	class cHtmlImg : public cHtmlElement
	{
	public:
		cHtmlImg(CComPtr<IHTMLElement> i_Elem);

		virtual BOOL Valid();
		CString GetUrl();
		BOOL    SetSrc(CString s_Src);

	protected:
		CComQIPtr<IHTMLImgElement, &IID_IHTMLImgElement> mi_Img;
	};

	// ####################################################

	class cHtmlHR : public cHtmlElement
	{
	public:
		cHtmlHR(CComPtr<IHTMLElement> i_Elem);

		enum eAction
		{
			E_Color,
			E_Size,   // the height of the line in pixel
			E_Width,  // the length of the line in pixel or percent
			E_Align
		};
		virtual BOOL Valid();
		void SetProperty(eAction e_Action, CString s_Value);
		CString GetProperty(eAction e_Action);
		BOOL GetShade();
		void SetShade(BOOL b_Shade);

	protected:
		CComQIPtr<IHTMLHRElement, &IID_IHTMLHRElement> mi_HR;
	};

	// ####################################################

	class cHtmlDocument : public cHtmlDomNode
	{
	public:
		cHtmlDocument();
		void Assign(CComPtr<IDispatch> D_Doc, CHtmlEditor *pi_Editor);

		virtual BOOL Valid();
		cHtmlStyleSheet GetStyleSheet(IUnknown* pi_Owner=0);
		BOOL SetDocumentDefault(CString s_Selector, cHtmlStyle<IHTMLRuleStyle>::eProp e_Prop, CString s_Value);
		BOOL IsModified();
		cHtmlElement GetElementByID(CString s_ID);
		UINT QueryStatus(UINT u32_Command);
		CString GetTitle();
		void SetTitle(CString s_Title);
		CString GetUrl();
		BOOL ExecSetCommand(UINT u32_Command, CComVariant v_In=0, BOOL b_PromtUser=TRUE);
		BOOL ExecGetCommand(UINT u32_Command, CComVariant *pv_Out);
		CString GetHtml();
		CString GetHtmlW3C();
		cHtmlElement GetHtmlTag();
		cHtmlElement GetHead();
		cHtmlElement GetBody(BOOL b_Create);
		void CleanUpTags();
		cHtmlElement GetSelection(BOOL b_AllowEmptySel=TRUE);
		UINT GetElementCollection(CString s_TagName, CComQIPtr<IHTMLElementCollection> &i_Collect);
		BOOL PasteIntoSelection(CString s_Html);
		BOOL AddToSelection(CString s_BeginHtml, CString s_EndHtml);
		BOOL SetHtml(CString s_HTML);
		BOOL InsertTable(UINT u32_Rows, UINT u32_Cols);
		BOOL SetDesignMode(BOOL b_Design);
		BOOL GetDesignMode();
		BOOL FocusWindow();
		cHtmlTableCell GetSelectedCell();
		void InsertNewTableColumn(BOOL b_Right);
		void InsertNewTableRow(BOOL b_Below);
		BOOL InsertNewImage(CString s_Path);
		BOOL SetSelectionFontSize(UINT u32_Size);
		UINT GetSelectionFontSize();
		UINT GetDefaultFontSize();
		void MakeImagesAbsolute();

		static UINT ConvertFontSize(CString s_Size);
		static UINT FontSizeToPixelSize(CString& s_Size, UINT u32_Default);

	protected:
		void RecursiveSetFontSize(cHtmlElement &i_Parent, CString *ps_Size);
		void RecursiveCleanUpChilds(cHtmlElement &i_Elem, CString *ps_Removed);
		BOOL ReplaceHeading(CString s_Tag, cHtmlElement &i_Elem);
		BOOL ReplaceParagraph(cHtmlElement &i_Elem);

		CHtmlEditor                  *mp_Editor;
		CComQIPtr<IHTMLDocument2>     mi_Doc2;
		CComQIPtr<IHTMLDocument3>     mi_Doc3;
		CComQIPtr<IHTMLDocument4>     mi_Doc4;
		CComQIPtr<IPersistStreamInit> mi_PStream;
		CComQIPtr<IOleCommandTarget>  mi_CmdTarg;

		int                         ms32_DefaultFontSize;
	};

	// #####################################################

	class CMsieWnd : public CWnd
	{
	public:
		void SetEditor(CHtmlEditor *p_Editor);

	protected:
		virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
		virtual BOOL PreTranslateMessage(MSG* pMsg);

	private:
		CHtmlEditor *mp_Editor;
	};
		
	// #####################################################

	class CUniRichEdit : public CWnd, public cMisc
	{
	public:
		CUniRichEdit();
		virtual ~CUniRichEdit();

		void SetEditor(CHtmlEditor *p_Editor);
		BOOL CreateEx(DWORD u32_ExStyle, DWORD u32_Style, const RECT& k_Rect, CWnd* p_Parent, UINT u32_ID);

	private:
		virtual BOOL PreTranslateMessage(MSG* pMsg);

		HINSTANCE mh_Dll32;
		HINSTANCE mh_Dll20;
		CHtmlEditor *mp_Editor;
	};
		
	// #####################################################

	class cStreamReader : public IStream, public cMisc
	{
	public:
		cStreamReader();
		virtual ~cStreamReader();
		void SetData(LPCTSTR szData);
		ULONG STDMETHODCALLTYPE AddRef();
		ULONG STDMETHODCALLTYPE Release(); 
		STDMETHOD(QueryInterface)(REFIID iid, void **ppUnk);
		STDMETHOD(Read)(void *pv_Buffer, ULONG u32_BufSize, ULONG *pu32_ReadBytes);
		STDMETHOD(Write)(const void *pv_Buffer, ULONG u32_BufSize, ULONG *pcbWritten);
		STDMETHOD(Seek)(LARGE_INTEGER, DWORD, ULARGE_INTEGER*);
		STDMETHOD(SetSize)(ULARGE_INTEGER);
		STDMETHOD(CopyTo)(IStream *, ULARGE_INTEGER, ULARGE_INTEGER*, ULARGE_INTEGER*);
		STDMETHOD(Commit)(DWORD);
		STDMETHOD(Revert)();
		STDMETHOD(LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
		STDMETHOD(UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
		STDMETHOD(Stat)(STATSTG*, DWORD);
		STDMETHOD(Clone)(IStream**);

	protected:
		char *mps8_Data;
		UINT  mu32_DataLen;
		UINT  mu32_Index;
	};

// END embedded classes

// ####################################################

// class CHtmlEditor :

	DECLARE_DYNCREATE(CHtmlEditor)
public:
	CHtmlEditor();
	virtual ~CHtmlEditor();

	virtual BOOL Valid();
	void Clear();
	void Save();
	BOOL ExecSetCommand(UINT u32_Command, CComVariant v_In=0, BOOL b_PromtUser=TRUE);
	BOOL ExecGetCommand(UINT u32_Command, CComVariant *pv_Out);
	BOOL ExecGetCommandStr(UINT u32_Command, CString *ps_Out);
	UINT QueryStatus(UINT u32_Command);
	BOOL CreateEditor(CWnd *p_Static, CWnd *p_NotificationWnd, BOOL b_EditOnlyBody, BOOL b_EnableThemes);
	void ResetMsieSettings();
	void SetDisplayMode(BOOL b_SourceMode, BOOL b_DesignMode);
	void EnableEditor(BOOL b_Enable);
	void MoveWindow(int Left, int Top, int Width, int Height, UINT u32_Flags=0);
	void MoveWindow(CRect k_Rect, UINT u32_Flags=0);
	void ReplaceParagraphs(UINT u32_VirtKeyCode);
	cHtmlDocument* GetDocument();
	BOOL NavigateToEmbeddedResource(CString s_RsrcName);
	BOOL Navigate(LPCTSTR t_URL, DWORD dwFlags=0, LPCTSTR lpszTargetFrameName=0, LPCTSTR lpszHeaders=0, LPVOID lpvPostData=0, DWORD dwPostDataLen=0);
	UINT GetDisplayMode();
	void NotifyParent(UINT u32_CommandID, BOOL b_Post);
	UINT GetMsieVersion();
	BOOL IsPlatformNT();
	void DelayCeanUp();

protected:
	virtual HRESULT OnUpdateUI();
	virtual void OnBeforeNavigate2(LPCTSTR t_URL, DWORD u32_Flags, LPCTSTR t_TargetFrame, CByteArray& i_PostedData, LPCTSTR t_Headers, BOOL *pb_Cancel);
	virtual void OnNavigateComplete2(LPCTSTR t_URL);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	BOOL           mb_SourceMode;
	BOOL           mb_Enabled;
	cHtmlDocument  mi_HtmDoc;
	CMsieWnd       mi_MSIE;
	CUniRichEdit   mi_RichEdit;
	CWnd          *mp_NotificationWnd;
	CWnd          *mp_Static;
	BOOL           mb_EditOnlyBody;
	BOOL           mb_InitDone;
	BOOL           mb_CleanUp;
	BOOL           mb_SubClassed;
	BOOL           mb_EnableThemes;
	BOOL           mb_PlatformNT;
	BOOL           mb_ParaReplaced;
};


// these typedefs avoid that you have to tpye "CHtmlEditor::cHtmlTable" each time 
// instead of simply typing "cHtmlTable"

typedef CHtmlEditor::cMisc            cMisc;
typedef CHtmlEditor::cHtmlStyle<IHTMLStyle>     cHtmlInlineStyle;
typedef CHtmlEditor::cHtmlStyle<IHTMLRuleStyle> cHtmlRuleStyle;
typedef CHtmlEditor::cHtmlStyleSheet  cHtmlStyleSheet;
typedef CHtmlEditor::cHtmlDomNode     cHtmlDomNode;
typedef CHtmlEditor::cHtmlElement     cHtmlElement;
typedef CHtmlEditor::cHtmlTableCell   cHtmlTableCell;
typedef CHtmlEditor::cHtmlTableRow    cHtmlTableRow;
typedef CHtmlEditor::cHtmlTable       cHtmlTable;
typedef CHtmlEditor::cHtmlHR          cHtmlHR;
typedef CHtmlEditor::cHtmlImg         cHtmlImg;
typedef CHtmlEditor::cHtmlDocument    cHtmlDocument;
typedef CHtmlEditor::CUniRichEdit     CUniRichEdit;
typedef CHtmlEditor::CMsieWnd         CMsieWnd;
typedef CHtmlEditor::cStreamReader    cStreamReader;




