
/*********************************************************************************
            Internet Explorer DHTML Editor class written by ElmüSoft

            www.codeproject.com/KB/cpp/DHTMLEditor.aspx
            www.netcult.ch/elmue

----------------------------------------------------------------------------------
Using these conventions results in better readable code and less coding errors !
----------------------------------------------------------------------------------

     cName  for generic class definitions
     CName  for MFC     class definitions
     tName  for type    definitions
     eName  for enum    definitions
     kName  for struct  definitions

    e_Name  for enum variables
    E_Name  for enum constant values

    i_Name  for instances of classes
    h_Name  for handles

    T_Name  for Templates
    t_Name  for TCHAR or LPTSTR

    s_Name  for strings
   bs_Name  for BSTR
    f_Name  for function pointers
    k_Name  for contructs (struct)

    b_Name  bool,BOOL 1 Bit

   s8_Name    signed  8 Bit (char)
  s16_Name    signed 16 Bit (SHORT, WCHAR)
  s32_Name    signed 32 Bit (LONG, int)
  s64_Name    signed 64 Bit (LONGLONG)

   u8_Name  unsigned  8 Bit (BYTE)
  u16_Name  unsigned 16 bit (WORD)
  u32_Name  unsigned 32 Bit (DWORD, UINT)
  u64_Name  unsigned 64 Bit (ULONGLONG)

    d_Name  for double

  ----------------

    m_Name  for member variables of a class (e.g. ms32_Name for int member variable)
    g_Name  for global variables            (e.g. gu16_Name for global WORD)
    p_Name  for pointer                     (e.g.   ps_Name  *pointer to string)
   pp_Name  for pointer to pointer          (e.g.  ppd_Name **pointer to double)


   typedef short VARIANT_BOOL ( 0 == FALSE, 0xFFFF == TRUE )


*************************************************************************************/

#include "StdAfx.h"
#include "cHtmlEditor.h"

GUID GUID_MSHTML = {0xde4ba900, 0x59ca, 0x11cf, {0x95,0x92,0x44,0x45,0x53,0x54,0x00,0x00}};

static CWnd   *gp_Parent = 0; // global (parent for messageboxes)

// ###########################  MISC  #################################

void CHtmlEditor::cMisc::RegWriteString(HKEY h_Class, CString s_Path, CString s_Key, CString s_Value)
{
	CRegKey i_Reg;
	i_Reg.Create  (h_Class, s_Path);   // closed in destructor of CRegKey
	i_Reg.SetValue(s_Value, s_Key);
}

void CHtmlEditor::cMisc::RegWriteDword(HKEY h_Class, CString s_Path, CString s_Key, DWORD u32_Value)
{
	CRegKey i_Reg;
	i_Reg.Create  (h_Class,   s_Path);  // closed in destructor of CRegKey
	i_Reg.SetValue(u32_Value, s_Key);
}

// Replaces MIME encoded strings
// "%20" --> " "
// "%FC" --> "ü"
// "%25" --> "%"     etc....
CString CHtmlEditor::cMisc::DecodeMime(CString s_In)
{
	CString s_Out;
	TCHAR *pt_Out = (TCHAR*) s_Out.GetBuffer(s_In.GetLength());
	TCHAR *pt_In  = (TCHAR*) s_In. GetBuffer(0);

	int O=0;
	for (int I=0; I<s_In.GetLength(); I++)
	{
		TCHAR t_Chr = pt_In[I];

		if (t_Chr == '%') 
		{
			UINT u32_Hex = 0;

			// convert hexadecimal string into UINT ("FA" --> 0xFA)
			for (UINT D=1; D<=2; D++)
			{
				UINT u32_Digit = (UINT) pt_In[I+D];

					 if (u32_Digit >= (UINT)'0' && u32_Digit <= (UINT)'9') u32_Digit -=  (UINT) '0';
				else if (u32_Digit >= (UINT)'A' && u32_Digit <= (UINT)'F') u32_Digit -= ((UINT) 'A' -10);
				else if (u32_Digit >= (UINT)'a' && u32_Digit <= (UINT)'f') u32_Digit -= ((UINT) 'a' -10);
				else break;

				u32_Hex = u32_Hex * 16 + u32_Digit;

				if (D == 2) // second hex digit
				{
					t_Chr = (TCHAR) u32_Hex;
					I += 2; // skip two hex digits
				}
			}
		}

		pt_Out[O++] = t_Chr;
	}

	s_Out.ReleaseBuffer(O);
	return s_Out;
}


// converts Unicode to ANSI using HTML Hex character encoding --> "&#xABCD;"
// If compiled with _UNICODE compiler setting, no encoding is required -> just copy string
CString CHtmlEditor::cMisc::EncodeHtml(const WCHAR* u16_Html)
{
	if (!u16_Html)
		return _T("");

	CString s_Out;
	UINT u32_Len = wcslen(u16_Html);
	if (!u32_Len)
		return _T("");

	UINT u32_BufSize = u32_Len * 8 + 1; // for worst case
	LPTSTR t_Buf     = s_Out.GetBuffer(u32_BufSize);

	#ifdef _UNICODE
		wcscpy(t_Buf, u16_Html);
	#else // _MBCS
		// EncodeHtml() modifies u32_Len AND u32_BufSize !!
		EncodeHtml(u16_Html, &u32_Len, t_Buf, &u32_BufSize);
		u32_Len = u32_BufSize; // count of chars copied to t_Buf
	#endif

	s_Out.ReleaseBuffer(u32_Len);
	return s_Out;
}

// converts pu32_WcharToCopy WCHAR's in the Unicode string u16_In which are 
// outside the ASCII code range to ANSI s8_Out using HTML Hex character encoding --> "&#xABCD;"
// s8_Out must have the 8 fold size of u32_WcharToCopy to cover the worst case !!
// As s8_Out will be zero terminated, the minimum buffer size is 9 characters
// If the buffer is too small no conversion takes place
// e.g. The Greek letter Unicode 960 is converted to "&#x03C0;\0"
void CHtmlEditor::cMisc::EncodeHtml(const WCHAR *u16_In,     // IN=buffer with UNICODE Html code
					                   UINT  *pu32_WcharToCopy, // IN=Wchars to copy, OUT=Converted Wchars
					                   char  *s8_Out,           // IN=buffer to receive ANSI Html code
					                   UINT  *pu32_OutSize)     // IN=sizeof(s8_Out), OUT=Bytes copied to s8_Out
{
	// Minimum required buffer size is 9 characters !! (for "&#x03C0;\0")
	// In the worst case 9 MBCS chars are required to convert ONE Unicode character !!
	ASSERT(*pu32_OutSize > 8); 

	UINT Pos = 0;
	for (UINT i=0; i<*pu32_WcharToCopy && Pos+8<*pu32_OutSize; i++)
	{
		WCHAR Chr = u16_In[i];
		if (Chr == 0) // End of Wstring
			break;

		if (Chr <= '~') // no conversion required
		{
			s8_Out[Pos] = (char) Chr;
			Pos ++;
		}
		else // encode HTML
		{
			sprintf(s8_Out +Pos, "&#x%04X;", Chr);
			Pos += 8;
		}
	}

	s8_Out[Pos] = 0; // terminate string

	*pu32_WcharToCopy = i;
	*pu32_OutSize     = Pos;
}

// convert Text -> HTML
void CHtmlEditor::cMisc::ReplaceAmp(CString* ps_Html)
{
	ps_Html->Replace(_T("&"),       _T("&amp;")); // FIRST !!
	ps_Html->Replace(_T("&amp;#x"), _T("&#x"));   // "&#x0958;" stays "&#x0958;"
	ps_Html->Replace(_T("<"),       _T("&lt;"));
	ps_Html->Replace(_T(">"),       _T("&gt;"));
	ps_Html->Replace(_T("  "),      _T("&nbsp; "));
	ps_Html->Replace(_T("\""),      _T("&quot;"));
}

// removes a tag at the begin and end of a Html code
// RemoveTag("<DIV align=right><b>Text</b></DIV>", "Div")   will return "<b>Text</b>"
// See also cHtmlDomNode::Strip() and cHtmlDomNode::Remove()
CString CHtmlEditor::cMisc::RemoveTag(CString s_Html, CString s_Tag)
{
	s_Html.TrimLeft (_T(" \t\r\n"));
	s_Html.TrimRight(_T(" \t\r\n"));

	s_Tag.MakeUpper();
	CString s_Start = _T("<")  + s_Tag;
	CString s_End   = _T("</") + s_Tag + _T(">");

	if (s_Html.Left (s_Start.GetLength()).CompareNoCase(s_Start) != 0 ||
		s_Html.Right(s_End.  GetLength()).CompareNoCase(s_End)   != 0)
			return s_Html;

	UINT s32_Begin = s_Html.Find(_T(">"), s_Start.GetLength()) +1;
	UINT s32_Count = s_Html.GetLength() - s_End.GetLength() - s32_Begin;

	return s_Html.Mid(s32_Begin, s32_Count);
}


// Removes the string s_Cut once from the beginning (b_End=FALSE) or end (b_End=TRUE) of s_In
// E.g. s_In="Test&nbsp;&nbsp;", s_Cut="&nbsp;", b_End=TRUE --> returns "Test&nbsp;"
CString CHtmlEditor::cMisc::CutString(CString s_In, CString s_Cut, BOOL b_End)
{
	int s32_InLen  = s_In. GetLength();
	int s32_CutLen = s_Cut.GetLength();
	
	if (s32_InLen < s32_CutLen || s32_InLen == 0 || s32_CutLen == 0)
		return s_In;

	if (b_End)
	{
		if (s_Cut.CompareNoCase(s_In.Right(s32_CutLen)) == 0)
			return s_In.Mid(0, s32_InLen - s32_CutLen);
	}
	else
	{
		if (s_Cut.CompareNoCase(s_In.Left(s32_CutLen)) == 0)
			return s_In.Mid(s32_CutLen);
	}

	return s_In;
}

// required for Visual Studio 6 and bugfix for Visual Studio 7 not converting VT_NULL correctly
// This function is ONLY used to convert strings like "TABLE" or "#FF5500" from BSTR to CString
// ATTENTION !!!
// For country dependant conversions of special characters (like öäüß or Greek, Russian) 
// use EncodeHtml() instead !!!!
CString CHtmlEditor::cMisc::VarToStr(CComVariant &v_Variant)
{
	CString s_Result;

	if (v_Variant.vt == VT_I4)
	{
		s_Result.Format(_T("%d"), v_Variant.lVal);
	}
	else if (v_Variant.vt == VT_BOOL)
	{
		if (v_Variant.boolVal) s_Result = _T("true");
		else                   s_Result = _T("false");
	}
	else if (v_Variant.vt == VT_BSTR) 
	{
		if (!v_Variant.bstrVal)
			return _T("");

		UINT u32_Len = SysStringLen(v_Variant.bstrVal);
		if (!u32_Len)
			return _T("");

		LPTSTR t_Buf = s_Result.GetBuffer(u32_Len);

		#ifdef _UNICODE // Unicode --> Unicode
			wcscpy(t_Buf, v_Variant.bstrVal);
		#else // _MBCS     Unicode --> Ansi
			WideCharToMultiByte(CP_ACP, 0, v_Variant.bstrVal, u32_Len, t_Buf, u32_Len, 0, 0);
		#endif
		
		s_Result.ReleaseBuffer(u32_Len);
	}

	return s_Result;
}

// returns 
// ' attrib1="value1" attrib2="value2"'  or
// ' attrib1:value1; attrib2:value2;'
void CHtmlEditor::cMisc::MapToString(CMapStringToString* pi_Map, const TCHAR* s_Format, CFastString* ps_Out)
{
	CString s_Attrib, s_Value, s_Temp;
	for (POSITION pos=pi_Map->GetStartPosition(); pos!=NULL;)
	{
		pi_Map->GetNextAssoc(pos, s_Attrib, s_Value);

		s_Temp.Format(s_Format, s_Attrib, s_Value);

		ps_Out->AppendString(s_Temp);
	}
}

BOOL CHtmlEditor::cMisc::IsEqualObject(IUnknown* p_Com1, IUnknown* p_Com2)
{
	if (p_Com1 == NULL || p_Com2 == NULL)
		return FALSE;

	CComPtr<IUnknown> p_Unk1;
	CComPtr<IUnknown> p_Unk2;
	p_Com1->QueryInterface(IID_IUnknown, (void**)&p_Unk1);
	p_Com2->QueryInterface(IID_IUnknown, (void**)&p_Unk2);
	return (p_Unk1 == p_Unk2);
}


// ###########################  STYLE  #################################


// cHtmlStyle<IHTMLStyle>
// cHtmlStyle<IHTMLRuleStyle>


// This class may contain a complete style definition like
// { FONT-SIZE: 17px; FONT-FAMILY: Arial; COLOR: red; }

// It's really stupid: But template classes must be defined in the header file



// ############################  STYLESHEET  ####################################

// Constructor
CHtmlEditor::cHtmlStyleSheet::cHtmlStyleSheet(CComPtr<IHTMLStyleSheet> i_Sheet)
{
	mi_Sheet = i_Sheet;

	// Get collection of Style Rules from the StyleSheet
	if (i_Sheet != NULL) i_Sheet->get_rules(&mi_Collect);
}

BOOL CHtmlEditor::cHtmlStyleSheet::Valid()
{
	return (mi_Sheet != NULL && mi_Collect != NULL);
}

// Retrieves one Style entry in braces ({..}) from a StyleSheet
// Example s_Selector = "Body" would return the "BODY" line from
// <HEAD><STYLE>
// BODY  { FONT-SIZE: 17px; FONT-FAMILY: Arial; }
// TABLE { FONT-SIZE: 14px; FONT-FAMILY: Comic Sans MS; }
// </STYLE></HEAD>
// If s_Selector is not found an invalid Style element is returned (check with Valid() !!)
cHtmlRuleStyle CHtmlEditor::cHtmlStyleSheet::GetRule(CString s_Selector)
{
	if (!mi_Collect)
		return cHtmlRuleStyle(0); // return invalid Style

	CComPtr<IHTMLStyleSheetRule> i_Rule;
	CComPtr<IHTMLRuleStyle>      i_Style = 0;

	long u32_Len;
	mi_Collect->get_length(&u32_Len);

	for (long i=0; i<u32_Len; i++)
	{
		i_Rule = 0;
		mi_Collect->item(i, &i_Rule);

		// Check if the name of the Style Sheet Rule is the requested one
		CComBSTR bs_Name;
		i_Rule->get_selectorText(&bs_Name);

		if (s_Selector.CompareNoCase(CString(bs_Name)) == 0)
		{
			i_Rule->get_style(&i_Style);
			break;
		}
	}

	return cHtmlRuleStyle(i_Style);
}

// Internet Explorer returns the <STYLE> tag in an ugly form:
// BODY { 
//    FONT-SIZE: 17px; FONT-FAMILY: Arial; 
// }
// GetHtmlW3C() retuns one definition per line with the correct indentation and lowercase styles
void CHtmlEditor::cHtmlStyleSheet::GetHtmlW3C(int s32_Indent, CFastString* ps_Out)
{
	// 50 Tabs
	const TCHAR* t_Tabs  = _T("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");

	if (!mi_Collect)
		return;

	long u32_Len;
	mi_Collect->get_length(&u32_Len);

	CString s_Name;
	for (long i=0; i<u32_Len; i++)
	{
		CComPtr<IHTMLStyleSheetRule> i_Rule;
		mi_Collect->item(i, &i_Rule);

		ps_Out->AppendBuffer(t_Tabs, s32_Indent);

		CComBSTR bs_Name;
		i_Rule->get_selectorText(&bs_Name);
		
		s_Name = bs_Name;
		s_Name.MakeLower();
		while (s_Name.GetLength() < 12)
		{
			s_Name += ' ';
		}

		ps_Out->AppendString(s_Name);

		ps_Out->AppendBuffer(_T("{ "), 2);

		CComPtr<IHTMLRuleStyle> i_Style;
		i_Rule->get_style(&i_Style);
		cHtmlRuleStyle i_RuleStyle(i_Style);

		CMapStringToString i_StyleMap;
		i_RuleStyle.GetPropertyMap(&i_StyleMap);

		cMisc::MapToString(&i_StyleMap, _T("%s:%s; "), ps_Out);

		ps_Out->AppendBuffer(_T("}\r\n"), 3);
	}
}

// Adds a new not existent rule to the stylesheet
// ATTENTION: This function os protected ! Use SetProperty() instead!
BOOL CHtmlEditor::cHtmlStyleSheet::AddRule(CString s_Selector, cHtmlRuleStyle::eProp e_Prop, CString s_Value)
{
	static CString s_Props[] = __StyleNames;

	CString s_StyleDef = s_Props[e_Prop] + _T(":") + s_Value; // e.g. "width:100px"

	CComBSTR bs_StyleDef = s_StyleDef;
	CComBSTR bs_Selector = s_Selector;

	long u32_Dummy;
	return SUCCEEDED(mi_Sheet->addRule(bs_Selector, bs_StyleDef, -1, &u32_Dummy));
}

// Sets a specific Style Sheet Property in the StyleSheet
// If the Selector does not yet exist it is created newly
// E.g. Selector = "Body", e_Prop = E_FontSize, s_Value = "17pt"
// sets the default font size for the whole document
BOOL CHtmlEditor::cHtmlStyleSheet::SetProperty(CString s_Selector, cHtmlRuleStyle::eProp e_Prop, CString s_Value)
{
	cHtmlRuleStyle i_Style = GetRule(s_Selector);

	if (i_Style.Valid())
	{
		return i_Style.SetProperty(e_Prop, s_Value);
	}
	else // The selector does not yet exist -> create a new one
	{
		return AddRule(s_Selector, e_Prop, s_Value);
	}
}

// ###########################  DOMNODE  #################################

// Constructor
CHtmlEditor::cHtmlDomNode::cHtmlDomNode(CComPtr<IHTMLDOMNode> i_Dom)
{
	mi_Dom = i_Dom;
}

BOOL CHtmlEditor::cHtmlDomNode::Valid()
{
	return (mi_Dom != NULL);
}

// Removes this element and all it's children from the document
// See also cHtmlDomNode::Strip() and cMisc::RemoveTag()
BOOL CHtmlEditor::cHtmlDomNode::Remove()
{
	CComPtr<IHTMLDOMNode> i_OldNode;
	VARIANT_BOOL v_RemChilds(true);
	return SUCCEEDED(mi_Dom->removeNode(v_RemChilds, &i_OldNode));
}

// While cHtmlDomNode::Remove() completely removes a tag with all its content and children,
// this function just strips this element but does not remove its children
// E.g.  "<BIG><b>Hello World</b></BIG>"  ---> strip BIG tag --> "<b>Hello World</b>"
BOOL CHtmlEditor::cHtmlDomNode::Strip()
{
	CComPtr<IHTMLDOMNode> i_OldNode;
	VARIANT_BOOL v_RemChilds(false);
	return SUCCEEDED(mi_Dom->removeNode(v_RemChilds, &i_OldNode));
}

// returns the right neighbour which is a IHTMLElement in the HTML hierarchy
cHtmlElement CHtmlEditor::cHtmlDomNode::NextSibling()
{
	CComPtr<IHTMLDOMNode> i_Dom = mi_Dom;
	while (TRUE)
	{
		CComPtr<IHTMLDOMNode> i_Next;
		i_Dom->get_nextSibling(&i_Next);
		if (!i_Next) // no more neighbours
			break;
		CComQIPtr<IHTMLElement> i_Elem = i_Next;
		if (i_Elem) // Check if i_Next is a IHTMLElement
			return cHtmlElement((CComPtr<IHTMLElement>) i_Elem);

		i_Dom = i_Next;
	}
	return cHtmlElement(0);
}

// returns the left neighbour which is a IHTMLElement in the HTML hierarchy
cHtmlElement CHtmlEditor::cHtmlDomNode::PreviousSibling()
{
	CComPtr<IHTMLDOMNode> i_Dom = mi_Dom;
	while (TRUE)
	{
		CComPtr<IHTMLDOMNode> i_Prev;
		i_Dom->get_previousSibling(&i_Prev);
		if (!i_Prev) // no more neighbours
			break;
		CComQIPtr<IHTMLElement> i_Elem = i_Prev;
		if (i_Elem) // Check if i_Prev is a IHTMLElement
			return cHtmlElement((CComPtr<IHTMLElement>)i_Elem);

		i_Dom = i_Prev;
	}
	return cHtmlElement(0);
}

// Appends an already existing Element to the child list of this node
// returns the newly added Element
cHtmlElement CHtmlEditor::cHtmlDomNode::AppendChild(cHtmlElement i_NewChild)
{
	CComPtr<IHTMLDOMNode> i_NewNode;
	mi_Dom->appendChild(i_NewChild.mi_Dom, &i_NewNode);

	// cast Domnode back to HtmlElement
	CComQIPtr<IHTMLElement, &IID_IHTMLElement>  i_NewElem = i_NewNode;
	return cHtmlElement((CComPtr<IHTMLElement>) i_NewElem);
}

// This function retrieves the outerHTML as W3C compliant HTML5 code.
// 1.) Tags are lowercase
// 2.) Single tags are closed with a slash
// 3.) <font> is replaced with <span>
// This function is optimized for speed
// returns TRUE when the Parent Tag should insert a CRLF
BOOL CHtmlEditor::cHtmlDomNode::GetHtmlW3C(CFastString* ps_OuterHtml, cHtmlDocument* pi_ParentDoc, int s32_Indent)
{
	BOOL b_CrLf_Before = FALSE; // Insert CR + LF before  <tag>
	BOOL b_CrLf_After  = FALSE; // Insert CR + LF before </tag>

	// 50 Tabs
	const TCHAR* t_Tabs = _T("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");

	s32_Indent = min(s32_Indent, MAX_TAB_STOPS); // (MAX_TAB_STOPS = 32)

	// Insert "\r\n" before and after the following tags into the HTML code
	// Do NOT insert "\r\n" into "<strong><u>ATTENTION</u>:</strong>" 

	static CString s_InsertCrLf = CString(_T("<html><head><meta><title><style><link><body><script><noscript>"))
	                                    + _T("<frameset><iframe><layer><select><object><applet><caption><map><input><button>")
	                                    + _T("<p><div><br><center><table><tbody><thead><tfoot><colgroup><tr><td>")
	                                    + _T("<ol><ul><li><hr><img><h1><h2><h3><h4><h5><h6>");
	long s32_NodeType;
	mi_Dom->get_nodeType(&s32_NodeType);

	switch (s32_NodeType)
	{
		case E_DomNodeText:
		{
			CComVariant v_Text;
			mi_Dom->get_nodeValue(&v_Text);

			if (v_Text.vt != VT_BSTR)
			{
				ASSERT(0); // This should never happen
				break;
			}

			CString s_Html = EncodeHtml(v_Text.bstrVal); // convert Unicode into TCHAR
			ReplaceAmp(&s_Html);                         // convert "<"  into  "&lt;"  etc..
			ps_OuterHtml->AppendString(s_Html);
			break;
		}
		case E_DomNodeElement:
		{
			CComQIPtr<IHTMLElement, &IID_IHTMLElement> i_DomElem = mi_Dom;

			cHtmlElement i_Elem((CComPtr<IHTMLElement>)i_DomElem);

			// --- Tag Name & Indentation ---

			CComBSTR bs_TagName;
			mi_Dom->get_nodeName(&bs_TagName);

			CString s_Tag = bs_TagName;
			s_Tag.MakeLower();

			// MSIE uses these two META tags that are not W3C compliant:
			// <meta http-equiv="MSThemeCompatible" content="yes"/>
			// <meta content="MSHTML 6.00.2900.2180" name="GENERATOR"/>
			if (s_Tag == "meta")
				break;

			// The FONT tag is not W3C compliant -> replace with SPAN
			// The only attributes used in this editor are <FONT color=xyz face=xyz size=xyz>
			// These attributes will be included into the "style=xyz" attribute in TransferAttribsToStyles()
			if (s_Tag == "font") 
				s_Tag =  "span";

			int s32_IndentChildren = s32_Indent;

			b_CrLf_Before = (s_InsertCrLf.Find(_T("<") + s_Tag + _T(">")) >= 0);
			if (b_CrLf_Before) 
			{
				s32_IndentChildren ++;

				ps_OuterHtml->AppendBuffer(_T("\r\n"), 2);
				ps_OuterHtml->AppendBuffer(t_Tabs, s32_Indent);
			}

			ps_OuterHtml->AppendBuffer(_T("<"), 1);
			ps_OuterHtml->AppendString(s_Tag);

			// --- Attributes & Styles ---

			CMapStringToString i_AttrMap, i_StyleMap;
			i_Elem.GetAttribsAndStylesMap(&i_AttrMap, &i_StyleMap);

			// e.g. <font size=6 face=Arial>  -->  <span style="font-size:32px; font-family:Arial;">
			i_Elem.TransferAttribsToStyles(&i_AttrMap, &i_StyleMap);

			cMisc::MapToString(&i_AttrMap, _T(" %s=\"%s\""), ps_OuterHtml);

			// --- Special Case: <style> ---

			if (s_Tag == "style")
			{
				ps_OuterHtml->AppendBuffer(_T(">\r\n"), 3);

				cHtmlStyleSheet i_Sheet = pi_ParentDoc->GetStyleSheet(i_DomElem);
				if (i_Sheet.Valid())
					i_Sheet.GetHtmlW3C(s32_IndentChildren, ps_OuterHtml);

				ps_OuterHtml->AppendBuffer(t_Tabs, s32_Indent);
				ps_OuterHtml->AppendBuffer(_T("</style>"), 8);

				b_CrLf_After = TRUE;
				break;
			}

			// --- Children ---

			CComPtr<IDispatch> D_Children = 0;
			mi_Dom->get_childNodes(&D_Children);

			CComQIPtr<IHTMLDOMChildrenCollection> i_Children = D_Children;

			// Internet Explorer Bug: The <noscript> Tag reports to have 0 children even if it has HTML code inside
			// But this bug is meaningless for this HTML editor

			long s32_Children;
			i_Children->get_length(&s32_Children);

			if (s32_Children > 0) // has children
			{
				ps_OuterHtml->AppendBuffer(_T(">"), 1);

				for (long C=0; C<s32_Children; C++)
				{
					CComPtr<IDispatch> D_Child = 0;
					i_Children->item(C, &D_Child);

					CComQIPtr<IHTMLDOMNode, &IID_IHTMLDOMNode> i_Child = D_Child;
					
					cHtmlDomNode i_Dom((CComPtr<IHTMLDOMNode>)i_Child);

					// recursive add children
					if (i_Dom.GetHtmlW3C(ps_OuterHtml, pi_ParentDoc, s32_IndentChildren))
						b_CrLf_After = TRUE;
				}

				if (b_CrLf_After) 
				{
					ps_OuterHtml->AppendBuffer(_T("\r\n"), 2);
					ps_OuterHtml->AppendBuffer(t_Tabs, s32_Indent);
				}

				ps_OuterHtml->AppendBuffer(_T("</"), 2);
				ps_OuterHtml->AppendString(s_Tag);
				ps_OuterHtml->AppendBuffer(_T(">"),  1);
			}
			else // childless tag
			{
				// the content of <title> can only be obtained via innerHTML
				CComBSTR bs_Inner;
				i_DomElem->get_innerHTML(&bs_Inner);

				UINT u32_Len = bs_Inner.Length();
				if  (u32_Len > 0)
				{
					CString s_Inner = EncodeHtml(bs_Inner);

					ps_OuterHtml->AppendBuffer(_T(">"), 1);
					ps_OuterHtml->AppendString(s_Inner);

					if (s_Inner.Find('\n') >= 0)
					{
						b_CrLf_After = TRUE;
						ps_OuterHtml->AppendBuffer(_T("\r\n"), 2);
						ps_OuterHtml->AppendBuffer(t_Tabs, s32_Indent);
					}

					ps_OuterHtml->AppendBuffer(_T("</"), 2);
					ps_OuterHtml->AppendString(s_Tag);
					ps_OuterHtml->AppendBuffer(_T(">"), 1);
				}
				else // innerHTML is empty e.g. <br/>
				{
					ps_OuterHtml->AppendBuffer(_T("/>"), 2);

					// The following erroneous HTML code produces this error:
					// <table><tr><td></td></td></tr></table>
					// the result is a tag: "</td/>"
					if (s_Tag[0] == '/')
						ps_OuterHtml->AppendBuffer(_T("\r\n<!-- *** ERROR DETECTED IN HTML CODE *** -->\r\n"));
				}
			}
			break;
		}
		case E_DomNodeComment:
		{
			break;
		}
		default:
		{
			ASSERT(0); // Invalid DOM node type (this should never happen)
			break;
		}
	}
	return (b_CrLf_Before || b_CrLf_After);
}


// ############################  ELEMENT  ##################################

// Constructor
CHtmlEditor::cHtmlElement::cHtmlElement(CComPtr<IHTMLElement> i_Elem) : cHtmlDomNode(0)
{
	mi_Elem = i_Elem;
	mi_Dom  = i_Elem;
}

const cHtmlElement& CHtmlEditor::cHtmlElement::operator=(const cHtmlElement& El)
{
	mi_Elem = El.mi_Elem;
	mi_Dom  = El.mi_Dom;
	return *this;
}

BOOL CHtmlEditor::cHtmlElement::Valid()
{
	return (mi_Elem != NULL);
}

// This is needed to be able to easily assign derived classes of cHtmlElement to each other
// Example: 
// CHtmlElement i_Elem  = i_Doc.GetElementByID("Id1");
// CHtmlTable   i_Table = i_Elem;
CHtmlEditor::cHtmlElement::operator CComPtr<IHTMLElement>()
{
	return mi_Elem;
}

// returns the Html uppercase tag (e.g. "TABLE", "TR", "BODY", "IMG" etc..)
CString CHtmlEditor::cHtmlElement::GetTagName()
{
	CComBSTR bs_TagName;
	mi_Elem->get_tagName(&bs_TagName);
	return CString(bs_TagName);
}

// returns the class name in <Span class="FatText"> (if any)
CString CHtmlEditor::cHtmlElement::GetClassName()
{
	CComBSTR bs_Class;
	mi_Elem->get_className(&bs_Class);
	return CString(bs_Class);
}

// returns an object which contains all styles that were specfied for this element
// If the styles will be modified in the styles object this will affect this element
cHtmlInlineStyle CHtmlEditor::cHtmlElement::GetStyle()
{
	CComPtr<IHTMLStyle> i_Style = 0;
	mi_Elem->get_style(&i_Style);
	return cHtmlInlineStyle(i_Style);
}

// returns an attribute of an Html tag
// e.g. for <img src="xyz" hspace=3 onmouseover="ShowInfo('Image');"> 
// GetAttribute("hspace")      will return "3"
// GetAttribute("onmouseover") will return "ShowInfo('Image');"
// If you want to retrieve the class attribute, set s_AttrName = "className" !!
CString CHtmlEditor::cHtmlElement::GetAttribute(CString s_AttrName)
{
	CComVariant v_AttrValue;
	CComBSTR   bs_AttrName = s_AttrName;
	mi_Elem->getAttribute(bs_AttrName, 0, &v_AttrValue);
	return VarToStr(v_AttrValue);
}

// see above
BOOL CHtmlEditor::cHtmlElement::SetAttribute(CString s_AttrName, CString s_Value)
{
	CComVariant v_AttrValue(s_Value);
	CComBSTR   bs_AttrName = s_AttrName;
	return SUCCEEDED(mi_Elem->setAttribute(bs_AttrName, v_AttrValue, 0));
}

// returns a MAP with all Html Attributes (e.g. "cellspacing=2")
// and a MAP with all Style properties    (e.g. "background-color:red;")
void CHtmlEditor::cHtmlElement::GetAttribsAndStylesMap(CMapStringToString* pi_AttrMap,
                                                       CMapStringToString* pi_StyleMap)
{
	CComPtr<IDispatch> D_Attribs = 0;
	mi_Dom->get_attributes(&D_Attribs);

	CComQIPtr<IHTMLAttributeCollection> i_Attribs = D_Attribs;

	long s32_Attribs;
	i_Attribs->get_length(&s32_Attribs);

	CString s_AttrName, s_AttrValue;
	for (int A=0; A<s32_Attribs; A++)
	{
		CComVariant v_Index(A);

		CComPtr<IDispatch> D_Attrib = 0;
		i_Attribs->item(&v_Index, &D_Attrib);

		CComQIPtr<IHTMLDOMAttribute, &IID_IHTMLDOMAttribute> i_Attrib = D_Attrib;

		VARIANT_BOOL b_Specified;
		i_Attrib->get_specified(&b_Specified);

		if (!b_Specified)
			continue; // The collection returns always approx 80 Attributes! (including all the default values)

		CComBSTR bs_AttrName;
		i_Attrib->get_nodeName(&bs_AttrName);

		s_AttrName = bs_AttrName;
		s_AttrName.MakeLower();

		if (s_AttrName == "style")
		{
			cHtmlInlineStyle i_Style = GetStyle();

			i_Style.GetPropertyMap(pi_StyleMap);
		}
		else
		{
			CComVariant v_AttrValue;
			i_Attrib->get_nodeValue(&v_AttrValue);

			s_AttrValue = VarToStr(v_AttrValue);

			if (!s_AttrValue.IsEmpty())
				pi_AttrMap->SetAt(s_AttrName, s_AttrValue);
		}
	}
}

// for W3C conform HTML 5: transfer the Attributes of <font> to Style in <span>
// e.g. <font size=6 face=Arial>  -->  <span style="font-size:32px; font-family:Arial;">
void CHtmlEditor::cHtmlElement::TransferAttribsToStyles(CMapStringToString* pi_AttrMap,
                                                        CMapStringToString* pi_StyleMap)
{
	CString s_Value;
	if (GetTagName() == "FONT")
	{
		if (pi_AttrMap->Lookup(_T("color"), s_Value))
		{
			pi_AttrMap ->RemoveKey(_T("color"));
			pi_StyleMap->SetAt    (_T("color"), s_Value);
		}

		if (pi_AttrMap->Lookup(_T("face"), s_Value))
		{
			pi_AttrMap ->RemoveKey(_T("face"));
			pi_StyleMap->SetAt    (_T("font-family"), s_Value);
		}

		if (pi_AttrMap->Lookup(_T("size"), s_Value))
		{
			// convert <FONT size=1..7> ==> (10px..48px)
			s_Value.Format(_T("%upx"), cHtmlDocument::FontSizeToPixelSize(s_Value, DEFAULT_FONT_SIZE_INT));

			pi_AttrMap ->RemoveKey(_T("size"));
			pi_StyleMap->SetAt    (_T("font-size"), s_Value);
		}
	}

	if (pi_StyleMap->GetCount())
	{
		// Implode the Styles Map as String and store it into the Attributes Map as "style=xyz"
		CFastString s_FastStyles(1000);
		cMisc::MapToString(pi_StyleMap, _T("%s:%s; "), &s_FastStyles);

		CString s_Styles = s_FastStyles.GetString();
		s_Styles.TrimRight();

		// The Attributes Map never contains "style"
		pi_AttrMap->SetAt(_T("style"), s_Styles);
	}
}

// removes the given attribute from the element if it exists (case-insesitive)
BOOL CHtmlEditor::cHtmlElement::RemoveAttribute(CString s_AttrName)
{
	VARIANT_BOOL vb_Success;
	CComBSTR bs_AttrName = s_AttrName;
	mi_Elem->removeAttribute(bs_AttrName, 0, &vb_Success);
	return (vb_Success == VARIANT_TRUE);
}

// For a <Span class="xyz">Hello <b>Test</b></Span> this function 
// will return            "Hello Test"
// Unicode characters are converted to &ABCD; in the MBCS version
CString CHtmlEditor::cHtmlElement::GetInnerText()
{
	CComBSTR bs_Text;
	mi_Elem->get_innerText(&bs_Text);
	return EncodeHtml(bs_Text);
}

// return TRUE if the element is empty inside (e.g. <a name="#Pos1"></a>)
BOOL CHtmlEditor::cHtmlElement::IsEmpty()
{
	// Do NOT use innerText here !
	BSTR bs_Html;
	mi_Elem->get_innerHTML(&bs_Html);
	CString s_Html(bs_Html);

	s_Html.TrimLeft (_T("\r\n \t"));
	s_Html.TrimRight(_T("\r\n \t"));
	return (!s_Html.GetLength());
}

// For a <Span class="xyz">Hello <b>Test</b></Span> this function 
// will return            "Hello <b>Test</b>"
CString CHtmlEditor::cHtmlElement::GetInnerHtml()
{
	CComBSTR bs_Html;
	mi_Elem->get_innerHTML(&bs_Html);
	return EncodeHtml(bs_Html);
}

BOOL CHtmlEditor::cHtmlElement::SetInnerHtml(CString s_Html)
{
	CComBSTR bs_Html = s_Html;
	return SUCCEEDED(mi_Elem->put_innerHTML(bs_Html));
}

// For a        <Span class="xyz">Hello <b>Test</b></Span> this function 
// will return "<Span class="xyz">Hello <b>Test</b></Span>"
CString CHtmlEditor::cHtmlElement::GetOuterHtml()
{
	CComBSTR bs_Html;
	mi_Elem->get_outerHTML(&bs_Html);
	return EncodeHtml(bs_Html);
}

cHtmlElement CHtmlEditor::cHtmlElement::GetParent()
{
	CComPtr<IHTMLElement> i_Parent = 0;
	mi_Elem->get_parentElement(&i_Parent);
	return cHtmlElement(i_Parent);
}

// retrieves a collection of Html Elements which are childs of this element
// returns the count of childs
// Use cHtmlElement::GetElementFromCollection() to retrieve a single child
UINT CHtmlEditor::cHtmlElement::GetChildCollection(CComQIPtr<IHTMLElementCollection> &i_Collect) // OUT
{
	CComPtr<IDispatch> D_Collect = 0;
	mi_Elem->get_children(&D_Collect);

	i_Collect = D_Collect;

	long u32_Len;
	i_Collect->get_length(&u32_Len);
	return u32_Len;
}

// Static function !
// retrieves the n-th element of the given collection
// This function may return an invalid element !!!! (Check Ret.Valid() !)
cHtmlElement CHtmlEditor::cHtmlElement::GetElementFromCollection(UINT    u32_Index,   // IN
                                        CComQIPtr<IHTMLElementCollection> &i_Collect) // IN
{
	CComVariant v_Index((int)u32_Index);

	// get the element with the requested index
	CComPtr<IDispatch> D_Elem;
	i_Collect->item(v_Index, v_Index, &D_Elem);

	CComQIPtr<IHTMLElement, &IID_IHTMLElement> i_Elem = D_Elem;
	
	cHtmlElement i_HtmlElem = cHtmlElement((CComPtr<IHTMLElement>)i_Elem);
	return i_HtmlElem;
}

// Searches for a parent (or grandparent) element with the given tag
// if "this" has already the requested tag -> return "this"
// This function may return an invalid element !!!! (Check Ret.Valid() !)
// s_Tag must be in the form "TD" (uppercase)
// see also SkipParents()
cHtmlElement CHtmlEditor::cHtmlElement::FindParent(CString s_Tag)
{
	cHtmlElement i_Elem = *this;

	while (i_Elem.Valid() && i_Elem.GetTagName() != s_Tag)
	{
		i_Elem = i_Elem.GetParent();
		if (!i_Elem.Valid())
			break;
	}
	return i_Elem;
}

// This function is similar to FindParent() but it does the reverse:
// While FindParent searches for an element whose name is s_Tag
// this function searches for an element whose name is NOT in s_Tags
// s_Tags must be in the form "<B><EM><U>" (uppercase)
cHtmlElement CHtmlEditor::cHtmlElement::SkipParents(CString s_Tags)
{
	cHtmlElement i_Elem = *this;
	CString s_Tag;
	
	while (i_Elem.Valid())
	{
		s_Tag.Format(_T("<%s>"), i_Elem.GetTagName());

		if (s_Tags.Find(s_Tag) >= 0)
		{
			i_Elem = i_Elem.GetParent();
			continue;
		}

		break;
	}
	return i_Elem;
}

// Inserts the given HTML code inside or outside of this Html element
// There are 4 possible insert positions:
// Outside-Before<TAG>Inside-Before InnerHTML Inside-After</TAG>Ouside-After
BOOL CHtmlEditor::cHtmlElement::InsertHtml(CString s_Html, BOOL b_AtBegin, BOOL b_Inside)
{
	BSTR bs_Where;
	if (b_Inside)
	{
		if (b_AtBegin) bs_Where = L"afterBegin";
		else           bs_Where = L"beforeEnd";
	}
	else // Outside
	{
		if (b_AtBegin) bs_Where = L"beforeBegin";
		else           bs_Where = L"afterEnd";
	}

	CComBSTR bs_Html = s_Html;
	return SUCCEEDED(mi_Elem->insertAdjacentHTML(bs_Where, bs_Html));
}

// creates a new cHtmlElement and appends it to the childs of this element
// returns the newly created element
cHtmlElement CHtmlEditor::cHtmlElement::AppendNewChild(CString s_Tag)
{
	// get the parent document
	CComPtr<IDispatch> D_Doc;
	mi_Elem->get_document(&D_Doc);
	CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> i_Doc = D_Doc;

	CComBSTR bs_Tag = s_Tag;
	CComPtr<IHTMLElement> i_Elem;
	i_Doc->createElement(bs_Tag, &i_Elem);

	return AppendChild(cHtmlElement(i_Elem));
}

// ############################  TABLECELL  ##################################

// Constructor
CHtmlEditor::cHtmlTableCell::cHtmlTableCell(CComPtr<IHTMLElement> i_Elem) : cHtmlElement(i_Elem)
{
	mi_Cell = i_Elem;
}

BOOL CHtmlEditor::cHtmlTableCell::Valid()
{
	return (mi_Cell != NULL);
}

cHtmlTableRow CHtmlEditor::cHtmlTableCell::GetParentRow()
{
	return cHtmlTableRow(FindParent(_T("TR")));
}

cHtmlTable CHtmlEditor::cHtmlTableCell::GetParentTable()
{
	return cHtmlTable(FindParent(_T("TABLE")));
}

// zero based
UINT CHtmlEditor::cHtmlTableCell::GetCellIndex()
{
	long Index;
	mi_Cell->get_cellIndex(&Index);
	return Index;
}

// get the column of the current cell
// zero based
UINT CHtmlEditor::cHtmlTableCell::GetColIndex()
{
	UINT u32_Col = 0;
	cHtmlTableCell i_Cell = *this;

	while (TRUE)
	{
		// go back until the leftmost is reached
		i_Cell = cHtmlTableCell(i_Cell.PreviousSibling());
		if (!i_Cell.Valid())
			break;

		u32_Col += i_Cell.GetColSpan();
	}
	return u32_Col;
}

// zero based
UINT CHtmlEditor::cHtmlTableCell::GetRowIndex()
{
	return GetParentRow().GetRowIndex();
}

UINT CHtmlEditor::cHtmlTableCell::GetColSpan()
{
	long Span = 1;
	mi_Cell->get_colSpan(&Span);
	return Span;
}

BOOL CHtmlEditor::cHtmlTableCell::SetColSpan(UINT Span)
{
	return SUCCEEDED(mi_Cell->put_colSpan(Span));
}

// overrides cHtmlElement::SetInnerHtml(...)
// Assure that hitting the enter key inside any table cell inserts <DIV> instead of <P>
BOOL CHtmlEditor::cHtmlTableCell::SetInnerHtml(CString s_Html)
{
	return cHtmlElement::SetInnerHtml(_T("<DIV>") +s_Html+ _T("</DIV>")); 
}

UINT CHtmlEditor::cHtmlTableCell::GetRowSpan()
{
	long Span = 1;
	mi_Cell->get_rowSpan(&Span);
	return Span;
}

void CHtmlEditor::cHtmlTableCell::SetBgColor(CString s_Color)
{
	CComVariant  v_Color(s_Color);
	mi_Cell->put_bgColor(v_Color);
}

CString CHtmlEditor::cHtmlTableCell::GetBgColor()
{
	CComVariant v_Color;
	mi_Cell->get_bgColor(&v_Color);
	return VarToStr(v_Color);
}

// ############################  TABLEROW  ##################################

// Constructor
CHtmlEditor::cHtmlTableRow::cHtmlTableRow(CComPtr<IHTMLElement> i_Elem) : cHtmlElement(i_Elem)
{
	mi_Row = i_Elem;
}

BOOL CHtmlEditor::cHtmlTableRow::Valid()
{
	return (mi_Row != NULL);
}

// zero based
UINT CHtmlEditor::cHtmlTableRow::GetRowIndex()
{
	long Index;
	mi_Row->get_rowIndex(&Index);
	return Index;
}

// deletes the n-th cell in the row 
// The index is always the n_th cell no matter which column span the cells have
// zero based index
BOOL CHtmlEditor::cHtmlTableRow::DeleteCell(UINT Index)
{
	return (SUCCEEDED(mi_Row->deleteCell(Index)));
}

// deletes the n-th column in the row 
// If the first cell spans about 3 columns, DeleteColumn(3) will delete the second cell
// If the cell to be deleted spans about more columns, only the cellspan will be decreased
// zero based index
BOOL CHtmlEditor::cHtmlTableRow::DeleteColumn(UINT Index)
{
	UINT u32_Col = 0;
	cHtmlTableCell i_Cell = GetCell(0);
	while (TRUE)
	{
		if (!i_Cell.Valid())
			break;

		UINT u32_Span = i_Cell.GetColSpan();
		if  (u32_Span == 1)
		{
			if (u32_Col == Index)
			{
				BOOL b_Ret = i_Cell.Remove(); // remove cell
				// if this was the last column -> remove complete table
				if (!GetCellCount()) GetParentTable().Remove();
				return b_Ret;
			}
		}
		else if (u32_Span > 1) // cell spans about multiple columns
		{
			if (Index >= u32_Col && Index < u32_Col + u32_Span)
				return i_Cell.SetColSpan(u32_Span -1); // reduce cellspan
		}
		u32_Col += u32_Span;
		i_Cell = cHtmlTableCell(i_Cell.NextSibling());
	}
	return FALSE;	
}

// zero based
// inserts a new cell at the given cell position 
// no matter which colspans the precedings cells have
// returns the new cell
cHtmlTableCell CHtmlEditor::cHtmlTableRow::InsertCell(UINT Index)
{
	CComPtr<IDispatch> D_Cell = 0;
	mi_Row->insertCell(Index, &D_Cell);

	CComQIPtr<IHTMLElement, &IID_IHTMLElement> i_Cell = D_Cell;
	cHtmlTableCell i_NewCell = cHtmlTableCell((CComPtr<IHTMLElement>)i_Cell);

	// Set new cell's content = &nbsp; otherwise the border may be displayed wrong and
	// the cell appears different in Design mode and Browse mode if it is completely empty
	// SetInnerHtml() will add <DIV></DIV>
	i_NewCell.SetInnerHtml(_T("&nbsp;"));
	return i_NewCell;
}

// zero based
// inserts a new cell at the given column position
// respecting the colspans of the preceding cells
// returns the new cell or the cell which was made wider
cHtmlTableCell CHtmlEditor::cHtmlTableRow::InsertColumn(UINT Index)
{
	UINT u32_Col = 0;
	for (UINT i=0; TRUE; i++)
	{
		cHtmlTableCell i_Cell = GetCell(i);
		if (!i_Cell.Valid())
			return InsertCell(i); // insert behind the rightmost cell

		UINT u32_Span = i_Cell.GetColSpan();
		if (u32_Col == Index) // insert at the left of the specified cell
			return InsertCell(i);
		
		if (Index > u32_Col && Index < u32_Col + u32_Span)
		{
			i_Cell.SetColSpan(u32_Span +1);
			return i_Cell; // increase cellspan of multi column cell
		}
		u32_Col += u32_Span;
	}
}

// melts the cell with its right neighbour
BOOL CHtmlEditor::cHtmlTableCell::Combine()
{
	cHtmlTableCell i_Right(NextSibling());
	if (!i_Right.Valid())
		return FALSE;

	// the new cell gets the content of both former cells concatenated
	// If the former content is surrounded by "<DIV>..</DIV>" it will be removed
	CString s_Div   = _T("DIV");
	CString s_Left  = RemoveTag(this->  GetInnerHtml(), s_Div);
	CString s_Right = RemoveTag(i_Right.GetInnerHtml(), s_Div);
	
	// avoid multiple "&nbsp;&nbsp;" behind each other in the cell
	CString s_Space = _T("&nbsp;");
	s_Left  = CutString(s_Left,  s_Space, TRUE);
	s_Right = CutString(s_Right, s_Space, FALSE);
	
	SetInnerHtml(s_Left + s_Space + s_Right);

	SetColSpan(GetColSpan() + i_Right.GetColSpan());
	i_Right.Remove();

	GetParentTable().CleanUp();
	return TRUE;
}

// splits a multi-column cell into 2 sub-cells
void CHtmlEditor::cHtmlTableCell::Split()
{
	UINT u32_Row  = GetRowIndex();
	UINT u32_Col  = GetColIndex();
	UINT u32_Span = GetColSpan();

	// insert new cell behind "this" cell in the same row
	cHtmlTableCell i_NewCell = GetParentRow().InsertColumn(u32_Col + u32_Span);

	if (u32_Span == 1) // split single-column cell
	{
		cHtmlTable i_Table = GetParentTable();
		UINT u32_Count = i_Table.GetRowCount();
		for (UINT i=0; i<u32_Count; i++)
		{
			if (i == u32_Row) // for this row the job is already done
				continue;
			
			cHtmlTableCell i_Cell = i_Table.GetCell(i, u32_Col, TRUE);
			if (i_Cell.Valid()) i_Cell.SetColSpan(i_Cell.GetColSpan() +1);
		}
	}
	else // split multi-column cell
	{
		// split in the middle (e.g. Colspan=5 --> Colspan=2 and Colspan=3)
	UINT u32_Span1 = u32_Span /2;
	UINT u32_Span2 = u32_Span - u32_Span1;

	    this->SetColSpan(u32_Span1);
	i_NewCell.SetColSpan(u32_Span2);
	}
}

// zero based
// returns the cell at the given CELL index
// This function may return an invalid element !!!! (Check Ret.Valid() !)
cHtmlTableCell CHtmlEditor::cHtmlTableRow::GetCell(UINT Index)
{
	CComPtr<IHTMLElementCollection> i_Collect = 0;
	mi_Row->get_cells(&i_Collect);
	if (!i_Collect)
		return cHtmlTableCell(0);

	CComVariant v_Index((int)Index);
	CComPtr<IDispatch> D_Cell = 0;
	i_Collect->item(v_Index, v_Index, &D_Cell);

	CComQIPtr<IHTMLElement, &IID_IHTMLElement> i_Cell = D_Cell;
	return cHtmlTableCell((CComPtr<IHTMLElement>)i_Cell);
}

// zero based
// returns the cell at the given COLUMN index
// If there is no cell at the given column index because the left neighbour cell spans over
// into this column and b_ReturnPrevious=FALSE, an invalid cell will be returned! 
// If b_ReturnPrevious=TRUE the previous cell (left neighbour) will be returned in this case
// (Check Ret.Valid() !)
cHtmlTableCell CHtmlEditor::cHtmlTableRow::GetColumn(UINT Index, BOOL b_ReturnPrevious) // =FALSE
{
	UINT u32_Col = 0;
	cHtmlTableCell i_PrevCell = cHtmlTableCell(0);

	for (UINT i=0; TRUE; i++) // i = CELL Index !
	{
		cHtmlTableCell i_Cell = GetCell(i);
		if (!i_Cell.Valid() || u32_Col > Index) // not found
		{
			if (b_ReturnPrevious) return i_PrevCell;        // return left neighbour
			else                  return cHtmlTableCell(0); // return invalid cell
		}

		if (u32_Col == Index)
			return i_Cell; // found !

		i_PrevCell = i_Cell;

		u32_Col += i_Cell.GetColSpan(); // u32_Col = COLUMN Index !
	}
}

// returns the number of cells in a row
UINT CHtmlEditor::cHtmlTableRow::GetCellCount()
{
	CComPtr<IHTMLElementCollection> i_Collect = 0;
	mi_Row->get_cells(&i_Collect);
	if (!i_Collect)
		return 0;

	long Len = 0;
	i_Collect->get_length(&Len);
	return Len;
}

cHtmlTable CHtmlEditor::cHtmlTableRow::GetParentTable()
{
	return cHtmlTable(FindParent(_T("TABLE")));
}

// #############################  TABLE  #################################

// Constructor
CHtmlEditor::cHtmlTable::cHtmlTable(CComPtr<IHTMLElement> i_Elem) : cHtmlElement(i_Elem)
{
	mi_Table = i_Elem;
}

BOOL CHtmlEditor::cHtmlTable::Valid()
{
	return (mi_Table != NULL);
}

void CHtmlEditor::cHtmlTable::SetBgColor(CString s_Color)
{
	CComVariant v_Color(s_Color);
	mi_Table->put_bgColor(v_Color);
}

CString CHtmlEditor::cHtmlTable::GetBgColor()
{
	CComVariant v_Color;
	mi_Table->get_bgColor(&v_Color);
	return VarToStr(v_Color);
}

// zero based
BOOL CHtmlEditor::cHtmlTable::DeleteRow(UINT Index)
{
	BOOL b_OK = SUCCEEDED(mi_Table->deleteRow(Index));

	// If the table has no rows anymore -> delete it completely !
	if (!GetRowCount()) this->Remove();
	else CleanUp();
	return b_OK;
}

// zero based
BOOL CHtmlEditor::cHtmlTable::DeleteColumn(UINT Index)
{
	BOOL b_Ret = TRUE;
	for (UINT i=0; TRUE; i++)
	{
		cHtmlTableRow i_Row = GetRow(i);
		if (!i_Row.Valid())
			break;

		if (!i_Row.DeleteColumn(Index))
			b_Ret = FALSE;
	}
	return b_Ret;
}

// zero based Index
// if CellCount  > 0 -> inserts CellCount new cells into the new row
// if CellCount == 0 -> inserts no cells, caller must insert new cells
// if CellCount  < 0 -> inserts as many new cells as row 0 has
cHtmlTableRow CHtmlEditor::cHtmlTable::InsertRow(UINT Index, int CellCount)
{
	if (CellCount < 0) CellCount = GetColumnCount(); // get cols of row 0

	CComPtr<IDispatch> D_Row = 0;
	mi_Table->insertRow(Index, &D_Row);

	CComQIPtr<IHTMLElement, &IID_IHTMLElement> i_Row = D_Row;
	cHtmlTableRow i_NewRow = cHtmlTableRow((CComPtr<IHTMLElement>)i_Row);

	for (int i=0; i<CellCount; i++)
	{
		cHtmlTableCell i_NewCell = i_NewRow.InsertCell(0);
	}
	return i_NewRow;
}

// zero based Index
BOOL CHtmlEditor::cHtmlTable::InsertColumn(UINT Index)
{
	BOOL b_Ret = TRUE;
	for (UINT i=0; TRUE; i++)
	{
		cHtmlTableRow i_Row = GetRow(i);
		if (!i_Row.Valid())
			break;

		cHtmlTableCell i_Cell = i_Row.InsertColumn(Index);
		if (!i_Cell.Valid())
			b_Ret = FALSE;
	}
	return b_Ret;
}

// zero based
// This function may return an invalid element !!!! (Check Ret.Valid() !)
cHtmlTableRow CHtmlEditor::cHtmlTable::GetRow(UINT Index)
{
	CComPtr<IHTMLElementCollection> i_Collect = 0;
	mi_Table->get_rows(&i_Collect);
	if (!i_Collect)
		return cHtmlTableRow(0);

	CComVariant v_Index((int)Index);
	CComPtr<IDispatch> D_Row = 0;
	i_Collect->item(v_Index, v_Index, &D_Row);

	CComQIPtr<IHTMLElement, &IID_IHTMLElement> i_Row = D_Row;
	return cHtmlTableRow((CComPtr<IHTMLElement>)i_Row);
}

UINT CHtmlEditor::cHtmlTable::GetRowCount()
{
	CComPtr<IHTMLElementCollection> i_Collect = 0;
	mi_Table->get_rows(&i_Collect);
	if (!i_Collect)
		return 0;

	long Count = 0;
	i_Collect->get_length(&Count);
	return Count;
}

// retrieves the column count od row 0
UINT CHtmlEditor::cHtmlTable::GetColumnCount()
{
	cHtmlTableRow i_First = GetRow(0);
	if (!i_First.Valid())
		return 0;

	UINT i = 0, Cols = 0;
	while (true)
	{
		cHtmlTableCell i_Cell = i_First.GetCell(i++);
		if (!i_Cell.Valid())
			break;
		Cols += i_Cell.GetColSpan();
	}
	return Cols;
}

CString CHtmlEditor::cHtmlTable::GetCellSpacing()
{
	CComVariant v_Spacing;
	mi_Table->get_cellSpacing(&v_Spacing);
	CString s_Spacing = VarToStr(v_Spacing); // converts VT_I4 and VT_BSTR
	if (!s_Spacing.GetLength())
		return _T("2"); // default value if nothing specified
	return s_Spacing;
}

BOOL CHtmlEditor::cHtmlTable::SetCellSpacing(CString s_Spacing)
{
	CComVariant v_Spacing(s_Spacing);
	return SUCCEEDED(mi_Table->put_cellSpacing(v_Spacing));
}

CString CHtmlEditor::cHtmlTable::GetCellPadding()
{
	CComVariant v_Padding;
	mi_Table->get_cellPadding(&v_Padding);
	CString s_Padding = VarToStr(v_Padding); // converts VT_I4 and VT_BSTR
	if (!s_Padding.GetLength())
		return _T("1"); // default value if nothing specified
	return  s_Padding;
}

BOOL CHtmlEditor::cHtmlTable::SetCellPadding(CString s_Padding)
{
	CComVariant v_Padding(s_Padding);
	return SUCCEEDED(mi_Table->put_cellPadding(v_Padding));
}

CString CHtmlEditor::cHtmlTable::GetBorderWidth()
{
	CComVariant v_Width;
	mi_Table->get_border(&v_Width);
	CString s_Width = VarToStr(v_Width); // converts VT_I4 and VT_BSTR
	if (!s_Width.GetLength())
		return _T("0"); // default value if nothing specified
	return s_Width;
}

BOOL CHtmlEditor::cHtmlTable::SetBorderWidth(CString s_Width)
{
	CComVariant v_Width(s_Width);
	return SUCCEEDED(mi_Table->put_border(v_Width));
}

CString CHtmlEditor::cHtmlTable::GetBorderColor()
{
	CComVariant v_Color;
	mi_Table->get_borderColor(&v_Color);
	CString s_Color = VarToStr(v_Color); // converts VT_I4 and VT_BSTR
	s_Color.MakeUpper();
	return  s_Color;
}

// specifies which parts of the table border are to be painted
BOOL CHtmlEditor::cHtmlTable::SetBorderRules(eRules e_Rules)
{
	BSTR bs_Rules;
	switch (e_Rules)
	{
		case E_RulesAll:  bs_Rules = L"all";  break;
		case E_RulesHor:  bs_Rules = L"rows"; break;
		case E_RulesVert: bs_Rules = L"cols"; break;
		case E_RulesBox:  bs_Rules = L"none"; break;
	}
	return SUCCEEDED(mi_Table->put_rules(bs_Rules));
}

cHtmlTable::eRules CHtmlEditor::cHtmlTable::GetBorderRules()
{
	CComBSTR bs_Rules;
	mi_Table->get_rules(&bs_Rules);

	if (bs_Rules.m_str && wcsicmp(bs_Rules, L"cols") == 0) return E_RulesVert;
	if (bs_Rules.m_str && wcsicmp(bs_Rules, L"rows") == 0) return E_RulesHor;
	if (bs_Rules.m_str && wcsicmp(bs_Rules, L"none") == 0) return E_RulesBox;

	return E_RulesAll;
}

BOOL CHtmlEditor::cHtmlTable::SetBorderColor(CString s_Color)
{
	CComVariant v_Color(s_Color);
	return SUCCEEDED(mi_Table->put_borderColor(v_Color));
}

// returns the cell at the given row and column index
// If there is no cell at the given column index because the left neighbour cell spans over
// into this column and b_ReturnPrevious=FALSE, an invalid cell will be returned! 
// If b_ReturnPrevious=TRUE the previous cell (left neighbour) will be returned in this case
// (Check Ret.Valid() !)
cHtmlTableCell CHtmlEditor::cHtmlTable::GetCell(UINT u32_Row, UINT u32_Column, BOOL b_ReturnPrevious) // =FALSE
{
	cHtmlTableRow i_Row = GetRow(u32_Row);
	if (!i_Row.Valid())
		return cHtmlTableCell(0);

	return i_Row.GetColumn(u32_Column, b_ReturnPrevious);
}

// returns a map with the colspans of each cell
// pu32_Span[Row][Col] will receive the colspan for each cell
// <TR><TD colspan=2>..</TD><TD>..</TD></TR> will result in:
// pu32_Map[Row][0] = 2  // cell 0 spans over to next cell
// pu32_Map[Row][1] = 0  // cell 1 does not exist
// pu32_Map[Row][2] = 1
// The caller must delete the returned pointer pu32_Map !!
BOOL CHtmlEditor::cHtmlTable::GetSpanMap(UINT *pu32_Rows, UINT *pu32_Cols, UINT **ppu32_Map)
{
	UINT u32_RowCount = GetRowCount();
	UINT u32_ColCount = GetColumnCount(); // retrieves column count of row 0
	if (!u32_RowCount || !u32_ColCount)
		return FALSE;

	UINT Size = u32_RowCount * u32_ColCount;
	UINT  *pu32_Span = new UINT[Size];
	memset(pu32_Span, 0, Size *4);

	for (UINT R=0; R<u32_RowCount; R++)
	{
		cHtmlTableRow i_Row = GetRow(R);
		
		UINT C = 0;
		for (UINT i=0; TRUE; i++)
		{
			cHtmlTableCell i_Cell = i_Row.GetCell(i);
			if (!i_Cell.Valid())
				break;

			if (i_Cell.GetRowSpan() > 1)
			{
				gp_Parent->MessageBox(_T("Cells which span over multiple rows are NOT supported !"), _T("Error"), MB_ICONSTOP);
				goto _Error;
			}

			UINT u32_Span = i_Cell.GetColSpan();

			pu32_Span[R *u32_ColCount +C] = u32_Span;

			C += u32_Span;
		}

		if (C != u32_ColCount) // All rows must contain the same amount of columns as Row 0!
		{
			gp_Parent->MessageBox(_T("All rows must contain the same amount of columns!"), _T("Error"), MB_ICONSTOP);
			goto _Error;
		}
	}

	*pu32_Rows =  u32_RowCount;
	*pu32_Cols =  u32_ColCount;
	*ppu32_Map = pu32_Span;
	return TRUE;

	_Error:
	delete pu32_Span;
	return FALSE;
}

// Checks if the cells of a column have a colspan > 1 in EVERY row. 
// If so, the colspan is decreased as much as possible in every row.
// <Table>
// <TR><td>..</td><td colspan=3>..</td></TR>
// <TR><td>..</td><td colspan=3>..</td></TR>
// </Table>
// In this table CleanUp() would remove the useless "colspan=3"
void CHtmlEditor::cHtmlTable::CleanUp()
{
	UINT u32_Rows, u32_Cols, *pu32_Map;
	if (!GetSpanMap(&u32_Rows, &u32_Cols, &pu32_Map))
		return;

	// IMPORTANT: start with the LAST column !!
	for (int C=u32_Cols-1; C>=0; C--)
	{
		// Check if the whole column can be deleted (all map entries of all rows == 0)
		BOOL b_Empty = TRUE;
		for (UINT R=0; R<u32_Rows; R++)
		{
			if (pu32_Map[R * u32_Cols + C] > 0)
			{
				b_Empty = FALSE;
				break;
			}
		}
		if (b_Empty) DeleteColumn(C);
	}
	delete pu32_Map;
}

// #############################  IMG  #################################

// Constructor
CHtmlEditor::cHtmlImg::cHtmlImg(CComPtr<IHTMLElement> i_Elem) : cHtmlElement(i_Elem)
{
	mi_Img = i_Elem;
}

BOOL CHtmlEditor::cHtmlImg::Valid()
{
	return (mi_Img != NULL);
}

// Always returns the ABSOLUTE path to the image
// while get_src() returns NONSENSE !!
CString CHtmlEditor::cHtmlImg::GetUrl()
{
	CComBSTR bs_URL;
	if (!SUCCEEDED(mi_Img->get_href(&bs_URL)))
		return _T("");

	return CString(bs_URL);
}

BOOL CHtmlEditor::cHtmlImg::SetSrc(CString s_Src)
{
	CComBSTR bs_Src(s_Src);
	return SUCCEEDED(mi_Img->put_src(bs_Src));
}


// #############################  HR  #################################

// Constructor
CHtmlEditor::cHtmlHR::cHtmlHR(CComPtr<IHTMLElement> i_Elem) : cHtmlElement(i_Elem)
{
	mi_HR = i_Elem;
}

BOOL CHtmlEditor::cHtmlHR::Valid()
{
	return (mi_HR != NULL);
}

void CHtmlEditor::cHtmlHR::SetProperty(eAction e_Action, CString s_Value)
{
	CComVariant v_Value(s_Value);
	switch (e_Action)
	{
		case E_Color: mi_HR->put_color(v_Value);  break;
		case E_Size:  mi_HR->put_size (v_Value);  break;
		case E_Width: mi_HR->put_width(v_Value);  break;
	};
}

CString CHtmlEditor::cHtmlHR::GetProperty(eAction e_Action)
{
	CComVariant v_Value;
	switch (e_Action)
	{
		case E_Color: 
			mi_HR->get_color(&v_Value);
			break;
		case E_Size:  
			mi_HR->get_size(&v_Value);
			if (!v_Value.bstrVal) v_Value = L"2"; // return default
			break; 
		case E_Width: 
			mi_HR->get_width(&v_Value);
			if (!v_Value.bstrVal) v_Value = L"100%"; // return default
			break;
	}
	CString s_Value = VarToStr(v_Value);
	s_Value.MakeUpper();
	return  s_Value;
}

// return TRUE if the <HR NOSHADE> property is not set
BOOL CHtmlEditor::cHtmlHR::GetShade()
{
	VARIANT_BOOL v_NoShade(false);
	mi_HR->get_noShade(&v_NoShade);
	return (v_NoShade == FALSE);
}

// turn on / off the <HR NOSHADE> property (default = off)
void CHtmlEditor::cHtmlHR::SetShade(BOOL b_Shade)
{
	VARIANT_BOOL v_NoShade(b_Shade == FALSE);
	mi_HR->put_noShade(v_NoShade);
}

// ##########################  DOCUMENT  ###############################

// Constructor
CHtmlEditor::cHtmlDocument::cHtmlDocument() : cHtmlDomNode(0)
{
	Assign(0,0);
}

void CHtmlEditor::cHtmlDocument::Assign(CComPtr<IDispatch> D_Doc, CHtmlEditor *pi_Editor)
{
	mp_Editor  = pi_Editor;
	mi_Doc2    =  D_Doc;
	mi_Doc3    =  D_Doc;
	mi_Doc4    =  D_Doc; // requires Internet Explorer 5.5
	mi_PStream =  D_Doc;
	mi_CmdTarg =  D_Doc;
	mi_Dom     =  D_Doc;
	
	ms32_DefaultFontSize = -1; // invalid
}

BOOL CHtmlEditor::cHtmlDocument::Valid()
{
	return (mi_Doc2 != NULL && mi_Doc3 != NULL && mi_PStream != NULL && mi_CmdTarg != NULL);
}

// returns TRUE if the user has modified the document
BOOL CHtmlEditor::cHtmlDocument::IsModified()
{
	return (mi_PStream->IsDirty() != S_FALSE);
}

// returns TRUE if Internet Explorer is in Design Mode
BOOL CHtmlEditor::cHtmlDocument::GetDesignMode()
{
	CComBSTR bs_Mode;
	mi_Doc2->get_designMode(&bs_Mode);
	return (wcsicmp(bs_Mode, L"On") == 0);
}

// Switches Internet Explorer to be an usual browser (off) or a DHTML Editor (on)
// ATTENTION:
// Do never call this function from your code !
// Use CHtmlEditor::SetDisplayMode() instead !!
BOOL CHtmlEditor::cHtmlDocument::SetDesignMode(BOOL b_Design)
{
	return SUCCEEDED(mi_Doc2->put_designMode(b_Design ? L"On" : L"Off"));
}

// Set the Focus (Cursor) to the Internet Explorer Window
// Requires Internet Explorer 5.5
// IMPORTANT: This function must be called after navigation is complete
BOOL CHtmlEditor::cHtmlDocument::FocusWindow()
{
	if (mi_Doc4 == NULL)
		return FALSE;

	return (S_OK == mi_Doc4->focus());
}

// loads the string as "<HTML>....</HTML>" into the document
// Previous contens of <HEAD> and <BODY> are overwritten
// You must use SetHtml() to set the content of the <Head>, as the following is NOT possible:
// GetHead().SetInnerHtml(..)
// ATTENTION:
// This command invokes an OnNavigateComplete2()
// The document's URL is set to "about:blank" while mp_Editor->GetLoactionURL() is not modified!
// You can NOT immediately access the document after calling this command !!!!!!!!!!!!!!!!
BOOL CHtmlEditor::cHtmlDocument::SetHtml(CString s_HTML)
{
	cStreamReader i_Stream;
	i_Stream.SetData(s_HTML);
	BOOL b_OK = SUCCEEDED(mi_PStream->Load(&i_Stream));

	mp_Editor->DelayCeanUp();
	return b_OK;
}

// returns the <HTML> element in the document
cHtmlElement CHtmlEditor::cHtmlDocument::GetHtmlTag()
{
	CComQIPtr<IHTMLElementCollection> i_Collect;
	GetElementCollection(_T("HTML"),  i_Collect);
	return cHtmlElement::GetElementFromCollection(0, i_Collect);
}

// returns "<HTML>.....</HTML>" as Internet Explorer returns it
CString CHtmlEditor::cHtmlDocument::GetHtml()
{
	cHtmlElement i_Html = GetHtmlTag();
	return i_Html.GetOuterHtml();
}

// returns "<html>.....</html>" (optimized for HTML5, W3C conform)
CString CHtmlEditor::cHtmlDocument::GetHtmlW3C()
{
	static CString s_Props[] = __StyleNames;

	CFastString s_FastHtml(32000);

	if (PRINT_HINT_IMPLEMENTED_STYLES)
	{
		s_FastHtml.AppendBuffer(_T("<!--\r\nATTENTION:\r\nCurrently only the following styles are implemented for Html 5 export:"));
		for (int i=0; i<cHtmlInlineStyle::E_LAST_STYLE; i++)
		{
			s_FastHtml.AppendBuffer(_T("\r\n\t"), 3);
			s_FastHtml.AppendBuffer(s_Props[i]);
		}
		s_FastHtml.AppendBuffer(_T("\r\nFor Editing purposes these are sufficient.\r\nIf you need more styles you have to extend the class cHtmlStyle!\r\n-->\r\n"));
	}

	cHtmlElement i_Html = GetHtmlTag();

	i_Html.GetHtmlW3C(&s_FastHtml, this);
	
	return s_FastHtml.GetString();
}

// returns the <HEAD> element in the document
// This is NOT possible:  GetHead().SetInnerHtml(..) use SetHtml() instead !
cHtmlElement CHtmlEditor::cHtmlDocument::GetHead()
{
	CComQIPtr<IHTMLElementCollection> i_Collect;
	GetElementCollection(_T("HEAD"),  i_Collect);
	return cHtmlElement::GetElementFromCollection(0, i_Collect);
}

// returns the <BODY> element in the document
// b_Create=TRUE -> if the document does not have a BODY tag (e.g. in pages with frames)
// a new BODY tag will be created
cHtmlElement CHtmlEditor::cHtmlDocument::GetBody(BOOL b_Create)
{
	// ATTENTION:
	// Do NOT use mi_Doc2->get_body() as this may also return a <FrameSet> if no Body available
	CComQIPtr<IHTMLElementCollection> i_Collect;
	GetElementCollection(_T("BODY"),  i_Collect);
	
	cHtmlElement i_Body = cHtmlElement::GetElementFromCollection(0, i_Collect);
	if (!i_Body.Valid() && b_Create)
	{
		// The document does not have a BODY tag -> create it !
		cHtmlElement i_Html = GetHtmlTag();
		i_Body = i_Html.AppendNewChild("BODY");
	}

	if (i_Body.Valid() && i_Body.IsEmpty())
		i_Body.SetInnerHtml(_T("<DIV></DIV>"));
	return i_Body;
}

// returns the text in the <TITLE> element in the <HEAD>
CString CHtmlEditor::cHtmlDocument::GetTitle()
{
	CComBSTR bs_Title;
	mi_Doc2->get_title(&bs_Title);
	return CString(bs_Title);
}

// returns the text in the <TITLE> element in the <HEAD>
void CHtmlEditor::cHtmlDocument::SetTitle(CString s_Title)
{
	CComBSTR bs_Title = s_Title;
	mi_Doc2->put_title(bs_Title);
}

// returns the URL of the document
// ATTENTION this may differ from mp_Editor->GetLocationURL() 
// After calling cHtmlDocument::SetHtml() this function returns "about:blank"
CString CHtmlEditor::cHtmlDocument::GetUrl()
{
	CComBSTR bs_Url;
	mi_Doc2->get_URL(&bs_Url);
	return CString(bs_Url);
}

// returns a StyleSheet with a collection of StyleSheet definitions which are defined 
// in the <STYLE> tag in the <HEAD> element
// Example:
// <HEAD><STYLE>
// BODY  { FONT-SIZE: 14px; FONT-FAMILY: Arial; }
// TABLE { FONT-SIZE: 14px; FONT-FAMILY: Comic Sans MS; }
// </STYLE></HEAD>
// would return a StyleSheet that contains 2 entries
// External StyleSheets like 
// <link href="style.css" rel="stylesheet" type="text/css" />
// are ignored
// If the <HEAD> does not contain any Style defintions,
// a new empty <STYLE> tag will be created in the <HEAD> element
// An invalid StyleSheet is returned on error (i_Style.Valid() == FALSE)
// pi_Owner != NULL -> search the StyleSheet that is owned by pi_Owner
// otherwise if multiple <style> tags: return the first that is internal
cHtmlStyleSheet CHtmlEditor::cHtmlDocument::GetStyleSheet(IUnknown* pi_Owner)
{
	CComBSTR    bs_Href;
	CComVariant  v_StyleSheet;
	CComPtr<IHTMLStyleSheetsCollection> i_Collect;
	CComQIPtr<IHTMLStyleSheet, &IID_IHTMLStyleSheet> i_Sheet;

	for (int Try=0; Try<=1; Try++)
	{
		i_Collect = 0;

		// returns an empty but valid collection if no Styles defined
		mi_Doc2->get_styleSheets(&i_Collect);

		// How many style sheets are there ?
		long s32_Len;
		i_Collect->get_length(&s32_Len);

		// search a StyleSheet in the collection which is NOT external
		for (long Idx=0; Idx<s32_Len; Idx++)
		{
			// Get the Style Sheet at index Idx from the collection
			CComVariant v_Index(Idx);
			i_Collect->item(&v_Index, &v_StyleSheet);

			// Query interface for IHTMLStyleSheet pointer
			i_Sheet = v_StyleSheet.pdispVal;

			// Search for the style sheet with the given owner element
			if (pi_Owner)
			{
				CComPtr<IHTMLElement> i_Parent;
				i_Sheet->get_owningElement(&i_Parent);

				if (IsEqualObject(i_Parent, pi_Owner))
					return cHtmlStyleSheet((CComPtr<IHTMLStyleSheet>) i_Sheet);

				continue;
			}

			// Search the first style sheet that is internal
			i_Sheet->get_href(&bs_Href);
			if (!bs_Href.Length()) // internal Sheet ?
		{
				return cHtmlStyleSheet((CComPtr<IHTMLStyleSheet>) i_Sheet);
			}
		}

		// If the <Style> element does not exist in the <Head> --> create a new one and try again!
		cHtmlElement i_Head = GetHead();
		if (!i_Head.Valid())
			return cHtmlStyleSheet(0);  // return invalid stylesheet

		i_Head.AppendNewChild(_T("STYLE"));
	}

	// The document contains no internal stylesheet
	// Creating a new <STYLE> tag failed
	return cHtmlStyleSheet(0);  // return invalid stylesheet
}

// Sets default settings for the whole document
// Example: s_Selector="Body", e_Prop = E_FontSize, s_Value="14px"
// will set the Body default font size to 14 pixel
// You can set any default property here which exists in cHtmlStyle<..>
BOOL CHtmlEditor::cHtmlDocument::SetDocumentDefault(CString s_Selector, cHtmlRuleStyle::eProp e_Prop, CString s_Value)
{
	// make DefaultFontSize invalid so it will be determined anew
	ms32_DefaultFontSize = -1;

	cHtmlStyleSheet i_Sheet = GetStyleSheet();
	if (!i_Sheet.Valid())
		return FALSE;

	return i_Sheet.SetProperty(s_Selector, e_Prop, s_Value);
}

// This is a quadruple - clean up function
// It is called after pasting into the HTML editor, after navigating to a web site
// and after switching the Display Mode
// 1.)
// Under some circumstances Internet Explorer may forget to remove empty tags
// This may happen for example if you select text, then make it bold,
// replace the selection with an image and then delete the image with the DEL key
// Then you will find a dead "bold" element in your document which looks like this: 
// <STRONG></STRONG> (it will obviously be invisible)
// This function deletes useless empty Link, Span, Font, Em tags etc
// This function even deletes nested empty tags like <STRONG><EM><U></U></EM></STRONG>
// =======================================================================
// The following cases will not occur for HTML code typed into this HtmlEditor.
// They are only required if the user has pasted HTML content from a webpage 
// into the HTML Editor or entered source code into the Source editor
// -----------------------------------------------------------------------
// 2.)
// All tags are stripped which are not found in s_AllowList.
// Stripped are: <BIG><CENTER><SUB> etc because the editor does not support them
// But the former content of these tags will remain! ("<BIG>Text</BIG>"  -->  "Text")
// -----------------------------------------------------------------------
// 3.)
// Some tags must be expicitly deleted like <COLGROUP><SELECT> etc.. (not supported)
// These tags are removed completely with their content (inner HTML)
// -----------------------------------------------------------------------
// 4.)
// Special cases: 
// for <TH> the complete row is removed
// <P> is replaced with a double <DIV> 
// <H1> to <H6> are replaced by <FONT><B>
// <META http-equiv="refresh"> is deleted
// <STYLE> is firstly deleted then replaced by the parent's default settings (HTMLEDIT_SETDEFAULT)
// all Style="xyz" attributes are removed as the editor does not support them
// especially position:absolute attributes MUST be removed !
void CHtmlEditor::cHtmlDocument::CleanUpTags()
{
	GetBody(TRUE); // create BODY tag if it does not exist in a frameset

	cHtmlElement i_Html = GetHtmlTag();

	CString s_Removed;
	RecursiveCleanUpChilds(i_Html, &s_Removed);

	// Allow the parent application to set default style sheet definitions
	mp_Editor->NotifyParent(HTMLEDIT_SETDEFAULT, FALSE);

	// Display the tags which have been removed / stripped
	if (s_Removed.GetLength())
		gp_Parent->MessageBox(_T("The following tags have been removed as the Editor does not support them:\n") + s_Removed, _T("Unsupported Tags"), MB_ICONEXCLAMATION);
}

// protected function!
// ATTENTION:
// Internet Explorer Bug: "<DIV>&nbsp;</DIV>" returns an InnerHtml = "" instead of "&nbsp;"
// So <DIV> must NOT be added to s_EmptyList otherwise "<DIV>&nbsp;</DIV>" will be deleted
// This would mess up the document as "<DIV>&nbsp;</DIV>" is an empty line
void CHtmlEditor::cHtmlDocument::RecursiveCleanUpChilds(cHtmlElement &i_Elem,      // IN
										                CString     *ps_Removed)   // OUT
{
	// These tags will always be completely deleted including all their content
	static CString s_DeleteList = _T("<COLGROUP><SCRIPT><NOSCRIPT><FRAMESET><IFRAME><LAYER><SELECT><OBJECT><APPLET><CAPTION><MAP>");
	// These tags will be deleted if they are empty
	static CString s_EmptyList    = _T("<A><SPAN><FONT><EM><I><STRONG><B><U><NOBR><THEAD><TFOOT><TR><TITLE>");
	// All tags except these and those in s_EmptyList will be stripped
	static CString s_AllowList  = _T("<HTML><BODY><HEAD><DIV><BR><TABLE><TBODY><TR><TD><OL><UL><LI><HR><IMG><WBR>");
	// These tags will be replaced by <FONT><B>
	static CString s_Headings     = _T("<H1><H2><H3><H4><H5><H6>");
	// These tags will be allowed to have style="xyz" properties
	static CString s_AllowStyle = _T("<FONT><SPAN><TABLE><IMG>");

	CComQIPtr<IHTMLElementCollection> i_Collect;
	CString s_Tag;
	int i, s32_Count;

	// #################################################################
	//            Do the following  BEFORE parsing childs!!

	if (!i_Elem.Valid())
		return; // the child may be already deleted

	s_Tag = i_Elem.GetTagName();

	if (!s_Tag.GetLength())
		return; // the child may have a corrupt tag	

	s_Tag = _T("<") + s_Tag + _T(">");

	// Completely delete tags in s_DeleteList, don't care about any childs of them
	if (s_DeleteList.Find(s_Tag) >= 0)
	{
		i_Elem.Remove(); 
		goto _AppendTag;
	}

	// completely remove Style, will be set anew after calling HTMLEDIT_SETDEFAULT
	if (s_Tag == _T("<STYLE>"))
	{
		i_Elem.Remove();
		return; // Don't tell user about that
	}

	// Delete <META http-equiv="refresh" content="1; URL=xyz.htm">
	if (s_Tag == _T("<META>"))
	{
		CString s_Outer = i_Elem.GetOuterHtml();
		s_Outer.MakeUpper();
		if (s_Outer.Find(_T("REFRESH")) > 0) i_Elem.Remove();
		return;
	}

	// Completely remove table rows containing <TH> as the editor does not support them correctly
	if (s_Tag == _T("<TH>"))
	{
		cHtmlTableRow i_Row(i_Elem.GetParent());
		if (i_Row.Valid()) i_Row.Remove();
		goto _AppendTag;
	}

	// remove all Style attributes as the editor does not support to edit them
	// except for text background color in <FONT> and width in <TABLE>
	if (s_AllowStyle.Find(s_Tag) < 0)
	{
		i_Elem.RemoveAttribute(_T("Style"));
	}
	
	// remove these also from the BODY tag !
	i_Elem.RemoveAttribute(_T("className"));  // removes class="BtnStyle"
	i_Elem.RemoveAttribute(_T("onMousedown"));
	i_Elem.RemoveAttribute(_T("onMouseover"));
	i_Elem.RemoveAttribute(_T("onMouseout"));
	i_Elem.RemoveAttribute(_T("onClick"));
	i_Elem.RemoveAttribute(_T("onLoad"));

	// #################################################################
	//                         Parse Childs
	// #################################################################

	s32_Count = i_Elem.GetChildCollection(i_Collect);

	// Decrement because removed elements will be eliminated from the collection
	for (i=s32_Count-1; i>=0; i--)
	{
		cHtmlElement i_Child = cHtmlElement::GetElementFromCollection(i, i_Collect);

		// Parse childs: Recursive remove / strip / replace childs of i_Child
		RecursiveCleanUpChilds(i_Child, ps_Removed);
	}

	// #################################################################
	//             Do the following AFTER parsing childs!!
	// #################################################################
		
	// <H1>Text</H1> --> <FONT Size=6><B>Text</B></FONT>
	if (s_Headings.Find(s_Tag) >= 0)
	{
		ReplaceHeading(s_Tag, i_Elem); 
		return;
	}

	// <P>Text</P> --> <DIV>&nbsp;</DIV><DIV>Text</DIV><DIV>&nbsp;</DIV>
	if (s_Tag == _T("<P>"))
	{
		ReplaceParagraph(i_Elem); 
		return;
	}

	// completely delete empty tags
	if (s_EmptyList.Find(s_Tag) >= 0)
	{
		if (i_Elem.IsEmpty()) i_Elem.Remove(); 
		return;
	}

	if (s_AllowList.Find(s_Tag) >= 0)
		return;
	
	// remove tags which are not allowed but leave their inner content (strip)
	i_Elem.Strip();

	_AppendTag:
	// If s_Tag is for example "</TD>" this indicates an error in the HTML file
	// which means that there is an abandoned end tag which has no start tag ("<TD>")
	// Do not append them as invalid tags as they are just HTML errors 
	if (ps_Removed->Find(s_Tag) < 0 && s_Tag[1] != '/') 
	{
		*ps_Removed += _T(" ") + s_Tag;
	}
}

// protected function!
// replaces "<H1>Text</H1>" (which is not supported by this HTML editor)
// with "<DIV><FONT size=6><B>Text</B></FONT></DIV>"
BOOL CHtmlEditor::cHtmlDocument::ReplaceHeading(CString s_Tag, cHtmlElement &i_Elem)
{
	UINT u32_Size = 2;
	if (s_Tag == _T("<H1>")) u32_Size = 6;
	if (s_Tag == _T("<H2>")) u32_Size = 5;
	if (s_Tag == _T("<H3>")) u32_Size = 4;
	if (s_Tag == _T("<H4>")) u32_Size = 3;
	if (s_Tag == _T("<H5>")) u32_Size = 2;
	if (s_Tag == _T("<H6>")) u32_Size = 1;

	CString s_New;
	s_New.Format(_T("<DIV><FONT size=%d><B>%s</B></FONT></DIV>"), u32_Size, i_Elem.GetInnerHtml());

	if (!i_Elem.InsertHtml(s_New, FALSE, FALSE))
		return FALSE;
	
	return i_Elem.Remove();
}

// protected function!
// replaces "<P>Text"     with "<DIV>&nbsp;</DIV><DIV>Text</DIV>"
// replaces "<P>Text</P>" with "<DIV>&nbsp;</DIV><DIV>Text</DIV><DIV>&nbsp;</DIV>"
BOOL CHtmlEditor::cHtmlDocument::ReplaceParagraph(cHtmlElement &i_Elem)
{
	CString s_New = _T("<DIV>&nbsp;</DIV><DIV>") + i_Elem.GetInnerHtml() + _T("</DIV>");

	if (i_Elem.GetOuterHtml().Find(_T("</P>")) > 0) s_New += _T("<DIV>&nbsp;</DIV>");

	if (!i_Elem.InsertHtml(s_New, FALSE, FALSE))
		return FALSE;
	
	return i_Elem.Remove();
}

// This function replaces a relative src="xyz" in images with the absolute URL
// Example: <Img src="Header.gif"> ---> <Img src="http://host.com/Images/Header.gif">
// This assures that they are displayed correctly after toggeling design mode
void CHtmlEditor::cHtmlDocument::MakeImagesAbsolute()
{
	CString s_DocUrl = mp_Editor->GetDocument()->GetUrl();
	if (s_DocUrl == _T("about:blank"))
		return;

	CComQIPtr<IHTMLElementCollection> i_ImgColl;
	int s32_Images = GetElementCollection(_T("IMG"), i_ImgColl);

	for (int i=0; i<s32_Images; i++)
	{
		cHtmlImg i_Img = cHtmlElement::GetElementFromCollection(i, i_ImgColl);
		i_Img.SetSrc(i_Img.GetUrl());
	}
}

// If s_ID="SaveButton" this function would return the button
// <BUTTON id="SaveButton">Save</Button>
cHtmlElement CHtmlEditor::cHtmlDocument::GetElementByID(CString s_ID)
{
	CComBSTR bs_ID = s_ID;
	CComPtr<IHTMLElement> i_Elem;
	mi_Doc3->getElementById(bs_ID, &i_Elem);
	return cHtmlElement(i_Elem);
}


// retrieves a collection of IHTMLElement's which have the tagname s_TagName
// returns the count of elements which were found in the complete document
// if no element found -> returns a valid collection with 0 entries
// use GetElementFromCollection() to retrieve a single element from the collection
UINT CHtmlEditor::cHtmlDocument::GetElementCollection(CString       s_TagName, // IN
                                 CComQIPtr<IHTMLElementCollection> &i_Collect) // OUT
{
	CComBSTR bs_TagName = s_TagName;

	mi_Doc3->getElementsByTagName(bs_TagName, &i_Collect); // returns at least <HTML>, <HEAD>, <BODY>

	long u32_Len;
	i_Collect->get_length(&u32_Len);
	return u32_Len;
}

// 1.) If nothing is selected returns the parent element in which the cursor is blinking
// 2.) If the user has selected text or multiple elements 
// returns the common parent element of the selection 
// 3.) If the user has selected a control returns the first control element (e.g. an Image)
// This function may return an invalid element !!!! (Check Ret.Valid() !)
// If b_AllowEmptySel = TRUE  it is not required that the user has selected anything
// If b_AllowEmptySel = FALSE the user must select text or a html control (e.g. an image)
cHtmlElement CHtmlEditor::cHtmlDocument::GetSelection(BOOL b_AllowEmptySel) // = TRUE
{
	CComPtr<IHTMLSelectionObject> i_Sel;
	mi_Doc2->get_selection(&i_Sel);
	if (!i_Sel)
		return cHtmlElement(0);

	CComPtr<IDispatch>  D_Range;
	i_Sel->createRange(&D_Range);

	CComQIPtr<IHTMLTxtRange,     &IID_IHTMLTxtRange>     i_TxtRange  = D_Range;
	CComQIPtr<IHTMLControlRange, &IID_IHTMLControlRange> i_CtrlRange = D_Range;

	CComPtr<IHTMLElement> i_Elem = 0;

	if (i_CtrlRange) i_CtrlRange->item(0, &i_Elem);
	if (i_TxtRange)
	{
		i_TxtRange->parentElement(&i_Elem);
		
		if (!b_AllowEmptySel)
		{
			CComBSTR bs_Text;
			i_TxtRange->get_text(&bs_Text);
			// No text selected -> return an invalid html element
			if (!bs_Text.Length()) i_Elem = 0;
		}
	}

	return cHtmlElement(i_Elem);
}

// 1.) If nothing is selected returns false
// 2.) If the user has selected text or multiple elements 
// inserts s_BeginHtml before and s_EndHtml behind the current selection
// 3.) If the user has selected a control returns false
// Example s_BeginHtml = "<SUB>", s_EndHtml = "</SUB>" will subscript the selected text
BOOL CHtmlEditor::cHtmlDocument::AddToSelection(CString s_BeginHtml, CString s_EndHtml)
{
	CComPtr<IHTMLSelectionObject> i_Sel;
	mi_Doc2->get_selection(&i_Sel);
	if (!i_Sel)
		return FALSE;

	CComPtr<IDispatch>  D_Range;
	i_Sel->createRange(&D_Range);

	CComQIPtr<IHTMLTxtRange, &IID_IHTMLTxtRange> i_TxtRange = D_Range;
	if (!i_TxtRange)
		return FALSE;

	CComBSTR bs_Html;
	i_TxtRange->get_htmlText(&bs_Html);
	if (!bs_Html.m_str)
		return FALSE;

	CString s_Html = RemoveTag(EncodeHtml(bs_Html), _T("Div"));

	bs_Html = (s_BeginHtml + s_Html + s_EndHtml);

	return SUCCEEDED(i_TxtRange->pasteHTML(bs_Html));
}

// The currently selected text/controls will be replaced by the given HTML code.
// If nothing is selected, the HTML code is inserted at the cursor position
// return FALSE if not possible
BOOL CHtmlEditor::cHtmlDocument::PasteIntoSelection(CString s_Html)
{
	CComPtr<IHTMLSelectionObject> i_Sel;
	mi_Doc2->get_selection(&i_Sel);
	if (!i_Sel)
		return FALSE;

	CComPtr<IDispatch>  D_Range;
	i_Sel->createRange(&D_Range);

	CComQIPtr<IHTMLControlRange, &IID_IHTMLControlRange> i_CtrlRange = D_Range;
	if (i_CtrlRange) // the user has slected controls (e.g. an image)
	{
		// remove all selected controls
		CComPtr<IHTMLElement> i_Elem;
		long Len;
		i_CtrlRange->get_length(&Len);
		for (long i=0; i<Len; i++)
		{
			i_CtrlRange->item(i, &i_Elem);
			cHtmlElement i_Old = cHtmlElement(i_Elem);
			i_Old.Remove();
		}

		// Now get the textrange after deleting all selected controls
		D_Range = 0;
		i_Sel->createRange(&D_Range);
	}

	CComQIPtr<IHTMLTxtRange, &IID_IHTMLTxtRange> i_TxtRange = D_Range;
	if (i_TxtRange)
	{
		// i_TxtRange will be valid if nothing is selected or if text is selected
		// or if multiple elements are seleted
		CComBSTR bs_Html = s_Html;
		return SUCCEEDED(i_TxtRange->pasteHTML(bs_Html));
	}
	return FALSE;
}

#define __SkipTags "<A><B><U><I><EM><STRONG><NOBR>"

// Returns the font size at the current cursor position in "px" units (pixel).
// Using the command IDM_FONTSIZE to retrieve the font size returns only the gross values 1 to 7
// This function checks if there is a <FONT> element spanning over all selected elements
// and returns it's font size or if not, returns the Body's defaut font size preset 
UINT CHtmlEditor::cHtmlDocument::GetSelectionFontSize()
{
	cHtmlElement i_Sel = GetSelection(); // get the common parent of the selection

	while (TRUE)
	{
		// If the cursor is for example inside a <B> in <FONT ..><B>Text</B></FONT>
		// SkipParents() tries to find the <FONT> element
		static CString s_Enclosed = _T(__SkipTags);
		i_Sel = i_Sel.SkipParents(s_Enclosed);

		// Nothing found -> return default font size for document
		if (!i_Sel.Valid() || i_Sel.GetTagName() != _T("FONT"))
			return GetDefaultFontSize();
		
		// Get style="font-size:" definition
		cHtmlInlineStyle i_Style = i_Sel.GetStyle();
		if (i_Style.Valid())
		{
			UINT u32_Size = ConvertFontSize(i_Style.GetProperty(cHtmlInlineStyle::E_FontSize));
			if  (u32_Size > 0)
				return u32_Size;
		}

		// convert <FONT size=1..7> ==> (10px..48px)
		UINT u32_Size = cHtmlDocument::FontSizeToPixelSize(i_Sel.GetAttribute(_T("Size")), 0);
		if  (u32_Size > 0)
			return u32_Size;

		// No size information found: Probably it was a <FONT color=xyz> tag
		// Check if there is another FONT tag above this one
		i_Sel = i_Sel.GetParent();
	}
}

// returns the font size which is defined in the <STYLE> element of the <HEAD>
// As this function is called very frequently the value is determined anew only if required
// as after every navigation and after SetDocumentDefault()
UINT CHtmlEditor::cHtmlDocument::GetDefaultFontSize()
{
	if (ms32_DefaultFontSize < 4) // invalid value
	{
		// Determine the current default size from <STYLE> if any
		cHtmlRuleStyle i_Style = GetStyleSheet().GetRule(_T("BODY"));
		if (i_Style.Valid())
		{
			CString s_Size = i_Style.GetProperty(cHtmlRuleStyle::E_FontSize);

			// s_Size is empty here if nothing specified
			ms32_DefaultFontSize = ConvertFontSize(s_Size);
		}

		// still invalid: use default value
		if (ms32_DefaultFontSize < 4)
			ms32_DefaultFontSize = DEFAULT_FONT_SIZE_INT;
	}

	return ms32_DefaultFontSize;
}

// converts the multiple fontsize formats into pixel (px)
UINT CHtmlEditor::cHtmlDocument::ConvertFontSize(CString s_Size)
{
	// _ttol() = atol() (_MBCS) or _wtol() (_UNICODE)
	UINT u32_Size = _ttol(s_Size);
	if  (u32_Size)
	{
		if (s_Size.Find(_T("pt")) > 0) return (u32_Size * 4)  / 3;
		if (s_Size.Find(_T("mm")) > 0) return (u32_Size * 38) / 10;
		if (s_Size.Find(_T("cm")) > 0) return  u32_Size * 38;
		if (s_Size.Find(_T("pc")) > 0) return  u32_Size * 16;
		if (s_Size.Find(_T("in")) > 0) return  u32_Size * 96;
	}
	// Internet Explorer Default is "px" if no specifier exists
	return u32_Size;
}

// convert <FONT size=1..7> ==> (10px..48px)
UINT CHtmlEditor::cHtmlDocument::FontSizeToPixelSize(CString& s_Size, UINT u32_Default)
{
	switch (_ttol(s_Size))
	{
		case 1: return 10;
		case 2: return 14;
		case 3: return 16;
		case 4: return 18;
		case 5: return 24;
		case 6: return 32;
		case 7: return 48;
		default: 
			return u32_Default;
	}
}

// Sets the font size of the current selection in "px" (pixel) (which is more precise than pt)
// Using the command IDM_FONTSIZE to set the font size allows only the gross values 1 to 7
// To achieve a finer setting of font sizes this function replaces the <FONT size=7>
// which it sets via IDM_FONTSIZE by a more precise style sheet definition like
// <FONT style="font-size:15px"> (if called with u32_Size = 15)
BOOL CHtmlEditor::cHtmlDocument::SetSelectionFontSize(UINT u32_Size)
{
	if (!ExecSetCommand(IDM_FONTSIZE, _T("7"))) // Step 1: Let MSIE insert <FONT size=7>
		return FALSE;

	cHtmlElement i_Sel = GetSelection(); // get the common parent of the selection

	// If the cursor is for example inside a <B> in <FONT ..><B>Text</B></FONT>
	// SkipParents() tries to find the <FONT> element
	static CString s_Enclosed = _T(__SkipTags);
	i_Sel = i_Sel.SkipParents(s_Enclosed);
	
	if (!i_Sel.Valid())
		return FALSE;

	CString s_Size;
	s_Size.Format(_T("%upx"), u32_Size);

	RecursiveSetFontSize(i_Sel, &s_Size);
	return TRUE;
}

// protected function !
void CHtmlEditor::cHtmlDocument::RecursiveSetFontSize(cHtmlElement &i_Parent, CString *ps_Size)
{
	static CString s_Attr = _T("Size");

	if (i_Parent.GetTagName() == _T("FONT"))
	{
		// Only modify the <FONT> tag if it is a <FONT size=7> not if is just a <FONT color=x>
		if (i_Parent.GetAttribute(s_Attr).GetLength())
		{
			i_Parent.RemoveAttribute(s_Attr); // remove the "size=N"
			i_Parent.GetStyle().SetProperty(cHtmlInlineStyle::E_FontSize, *ps_Size); // set style sheet definition
		}
	}

	CComQIPtr<IHTMLElementCollection> i_Collect;
	UINT u32_Count = i_Parent.GetChildCollection(i_Collect);

	for (UINT i=0; i<u32_Count; i++)
	{
		cHtmlElement i_Child = cHtmlElement::GetElementFromCollection(i, i_Collect);
		if (i_Child.Valid())
		{
			RecursiveSetFontSize(i_Child, ps_Size);
		}
	}
}


// Queries whether the requested command can be executed on the current selection / cursor position
// or queries if the state of a property (e.g. BOLD) is enabled at the current cursor position
// OLECMDF_SUPPORTED The command is supported for the selection or insertion point.
// OLECMDF_ENABLED   The command is available and enabled.
// OLECMDF_LATCHED   Command is an on-off toggle and is currently on. E.g. this value is set 
//                   if you query the status of the IDM_BOLD command against a selection 
//                   that is already bold.
// OLECMDF_NINCHED   The selection includes a mixture of elements, some that do and some 
//                   that do not reflect the effect of the command. For example if the 
//                   selection contains some text that is bold and some that is not.
// OLECMDF_INVISIBLE
// OLECMDF_DEFHIDEONCTXTMENU
UINT CHtmlEditor::cHtmlDocument::QueryStatus(UINT u32_Command)
{
	OLECMD i_Cmd = {u32_Command, 0};
	if (SUCCEEDED(mi_CmdTarg->QueryStatus(&GUID_MSHTML, 1, &i_Cmd, 0)))
		return i_Cmd.cmdf;

	return 0;
}

// Executes a command like IDM_BOLD on the current selection or 
// a command like IDM_HORIZONTALLINE in the document
BOOL CHtmlEditor::cHtmlDocument::ExecSetCommand(UINT        u32_Command, 
								                CComVariant v_In,         // = 0 (input value)
								                BOOL        b_PromptUser) // = TRUE
{
	ASSERT(v_In.vt != VT_EMPTY);

	// IDM_FONTSIZE_STYLE is more precise than IDM_FONTSIZE
	if (u32_Command == IDM_FONTSIZE_STYLE)
	{
		if (v_In.vt != VT_I4)
			return FALSE;

		return SetSelectionFontSize(v_In.lVal);
	}

	UINT u32_Option = (b_PromptUser) ? OLECMDEXECOPT_DODEFAULT : MSOCMDEXECOPT_DONTPROMPTUSER;

	return SUCCEEDED(mi_CmdTarg->Exec(&GUID_MSHTML, u32_Command, u32_Option, &v_In, 0));
}

// Executes a command like IDM_FONTNAME which retrieves the font at the cursor position
BOOL CHtmlEditor::cHtmlDocument::ExecGetCommand(UINT u32_Command, CComVariant *pv_Out) // output value
{
	// IDM_FONTSIZE_STYLE is more precise than IDM_FONTSIZE
	if (u32_Command == IDM_FONTSIZE_STYLE)
	{
		*pv_Out = CComVariant((int) GetSelectionFontSize());
		return TRUE;
	}

	return SUCCEEDED(mi_CmdTarg->Exec(&GUID_MSHTML, u32_Command, 
	                 OLECMDEXECOPT_DODEFAULT, 0, pv_Out));
}

// Inserts a table at the current cursor position
// return FALSE if cusor position invalid
BOOL CHtmlEditor::cHtmlDocument::InsertTable(UINT u32_Rows, UINT u32_Cols)
{
	if (!u32_Rows || !u32_Cols)
		return FALSE;

	CString s_Html = _T("<TABLE border=1 cellpadding=3>");
	
	for (UINT R=0; R<u32_Rows; R++)
	{
		s_Html += _T("<TR>");
		for (UINT C=0; C<u32_Cols; C++)
		{
			// Set new cell's content = &nbsp; otherwise problems when 
			// locating the cursor into tables with cellpadding=0 
			s_Html += _T("<TD><DIV>&nbsp;</DIV></TD>");
		}
		s_Html += _T("</TR>");
	}
	s_Html += _T("</TABLE>");
	
	return PasteIntoSelection(s_Html);
}


// returns the table cell which has the cursor
// This function may return an invaild cell !! (check with Cell.Valid()!)
// Displays a messagbox if cursor position / selection is invalid
cHtmlTableCell CHtmlEditor::cHtmlDocument::GetSelectedCell()
{
	// get the selected object or if only text is selected: get the parent of the selection
	cHtmlElement i_Sel = GetSelection();
	CString      s_Sel = i_Sel.GetTagName();

	if (s_Sel == _T("TR") || s_Sel == _T("TBODY") || s_Sel == _T("TABLE"))
	{
		gp_Parent->MessageBox(_T("A selection spanning over multiple cells is not allowed."), _T("Error"), MB_ICONSTOP);
		return cHtmlTableCell(0);
	}

	// search upward in hierarchy for the next table cell (TD)
	cHtmlElement i_TD = i_Sel.FindParent(_T("TD"));
	if (!i_TD.Valid())
	{
		gp_Parent->MessageBox(_T("Please set the cursor into a table cell!"), _T("Error"), MB_ICONSTOP);
		return cHtmlTableCell(0);
	}

	// convert cHtmlElement to cHtmlTableCell using Ptr()
	return cHtmlTableCell(i_TD);
}


// Inserts a new table column at the left (b_Right = FALSE) or right (b_Right = TRUE)
// of the table cell which currently has the cursor
// Displays a messagbox if cursor position / selection is invalid
void CHtmlEditor::cHtmlDocument::InsertNewTableColumn(BOOL b_Right)
{
	cHtmlTableCell i_Cell = GetSelectedCell();
	if (!i_Cell.Valid())
		return;

	UINT u32_Position = (b_Right) ? i_Cell.GetColSpan() : 0;

	cHtmlTable i_Table = i_Cell.GetParentTable();
	i_Table.InsertColumn(i_Cell.GetColIndex()+u32_Position);
}


// Inserts a new table row above (b_Below = FALSE) or below (b_Below = TRUE)
// the table cell which currently has the cursor
// Displays a messagbox if cursor position / selection is invalid
void CHtmlEditor::cHtmlDocument::InsertNewTableRow(BOOL b_Below)
{
	cHtmlTableCell i_Cell = GetSelectedCell();
	if (!i_Cell.Valid())
		return;

	cHtmlTable i_Table = i_Cell.GetParentTable();

	UINT u32_Position = (b_Below) ? 1 : 0;

	// insert as many cells as row 0 has
	i_Table.InsertRow(i_Cell.GetRowIndex()+u32_Position, -1);
}

// Inserts an image into the current selection
// The path must be of the form "file:///E:/Temp/Image.gif" or "http://www.xyz.com/image.gif"
// Allowed types : GIF, JPG, BMP, PNG
// s32_Space is the distance between the image and surrounding text in pixels
BOOL CHtmlEditor::cHtmlDocument::InsertNewImage(CString s_Path)
{
	CString s_Html;
	s_Html.Format(_T("<img src=\"%s\" border=0 hspace=3 vspace=3>"), s_Path);
	return PasteIntoSelection(s_Html);
}


// ############################  RICHEDIT  ################################

// Visual Studio 6 supports only Richedit version 1.0 which does 
// not allow multiple UNDO and is not Unicode capable
// This class loads Riched20.dll if available otherwise it falls back to Riched32.dll
// (Using an Edit box instead of RichEdit is a very bad idea:
//  The source HTML code would be limited to 30 kB and Undo is allowed only once)

CHtmlEditor::CUniRichEdit::CUniRichEdit()
{
	mh_Dll32 = 0;
	mh_Dll20 = 0;
}

CHtmlEditor::CUniRichEdit::~CUniRichEdit()
{
	if (mh_Dll20) FreeLibrary(mh_Dll20);
	if (mh_Dll32) FreeLibrary(mh_Dll32);
}


BOOL CHtmlEditor::CUniRichEdit::CreateEx(DWORD u32_ExStyle, DWORD u32_Style, const RECT& k_Rect, CWnd* p_Parent, UINT u32_ID)
{
	mh_Dll20 = LoadLibraryA("RICHED20.DLL"); // Richedit Version 2.0 or 3.0
	if (mh_Dll20)
	{
		#ifdef _UNICODE
			if (!CWnd::CreateEx(u32_ExStyle, _T("RichEdit20W"), 0, u32_Style, k_Rect, p_Parent, u32_ID))
				return FALSE;
		#else
			if (!CWnd::CreateEx(u32_ExStyle, _T("RichEdit20A"), 0, u32_Style, k_Rect, p_Parent, u32_ID))
				return FALSE;
		#endif
	}
	else
	{
		mh_Dll32 = LoadLibraryA("RICHED32.DLL"); // Richedit Version 1.0
		if (!mh_Dll32)
			return FALSE;

		if (!CWnd::CreateEx(u32_ExStyle, _T("RICHEDIT"), 0, u32_Style, k_Rect, p_Parent, u32_ID))
			return FALSE;
	}

	// Define all TAB ("\t") positions

	PARAFORMAT k_Format;
	k_Format.cbSize    = sizeof(k_Format);
	k_Format.dwMask    = PFM_TABSTOPS;
	k_Format.cTabCount = MAX_TAB_STOPS;

	for (int i=0; i<MAX_TAB_STOPS; i++)
	{
		k_Format.rgxTabs[i] = i * RICHEDIT_INDENTATION;
	}

	if (!SendMessage(EM_SETPARAFORMAT, 0, (LPARAM)&k_Format))
		return FALSE;

	return TRUE;
}

void CHtmlEditor::CUniRichEdit::SetEditor(CHtmlEditor *p_Editor)
{
	mp_Editor = p_Editor;
}

// Richedit CTRL key handler (currently not implemented)
BOOL CHtmlEditor::CUniRichEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		BOOL b_Ctrl  = (GetKeyState(VK_CONTROL) & 0x8000) > 0;
		BOOL b_Shift = (GetKeyState(VK_SHIFT)   & 0x8000) > 0;
		BOOL b_Alt   = (GetKeyState(VK_MENU)    & 0x8000) > 0;

		if (b_Ctrl && !b_Shift && !b_Alt)
		{
/*
			switch (pMsg->wParam)
			{
			case 'S':
				Put any CTRL key handlers here
				return TRUE;
			}
*/
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

// ##########################  DHTMLEDITOR  ###############################

IMPLEMENT_DYNCREATE(CHtmlEditor, CHtmlEditView)

// Constructor
CHtmlEditor::CHtmlEditor()
{
	OSVERSIONINFO k_Os;
	k_Os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&k_Os);
	mb_PlatformNT      = (k_Os.dwPlatformId == VER_PLATFORM_WIN32_NT);
	mb_SourceMode      = FALSE;
	mb_ParaReplaced    = FALSE;
	mb_Enabled         = TRUE;
	mp_NotificationWnd = 0;
}

CHtmlEditor::~CHtmlEditor()
{
	if (mi_RichEdit.m_hWnd) mi_RichEdit.DestroyWindow();
}

// Editor is only valid after calling CreateEditor()
BOOL CHtmlEditor::Valid()
{
	return (mi_MSIE.m_hWnd != 0 && mi_HtmDoc.Valid() && mi_RichEdit.m_hWnd != 0);
}

// Retrieves the Html document of the browser
// Will not be valid before calling CreateEditor() !!
cHtmlDocument* CHtmlEditor::GetDocument()
{
	return &mi_HtmDoc;
}

UINT CHtmlEditor::GetDisplayMode()
{
	if (mb_SourceMode) 
		return IDM_VIEWSOURCE;
	else
		return mi_HtmDoc.GetDesignMode() ? IDM_EDITMODE : IDM_BROWSEMODE;
}

// You can use this function to control in Browse mode where the user is allowed to browse to
// (in Design mode the user cannot click any links in the document)
void CHtmlEditor::OnBeforeNavigate2(LPCTSTR t_URL,         DWORD       u32_Flags,
								    LPCTSTR t_TargetFrame, CByteArray&   i_PostedData,
								    LPCTSTR t_Headers,     BOOL         *pb_Cancel)
{
	// s8_URL = "about:blank" must ALWAYS be allowed
	// browsing to embedded resources "res://Path" must ALWAYS be allowed !!
	// browsing to files on the local harddisk should also be allowed
	// security risks are mainly on http and https pages (ftp:// should be no problem)
	if (_tcsnicmp(t_URL, _T("http"), 4) == 0)
	{
//		gp_Parent->MessageBox(_T("Browsing prohibited!"), _T("Error"), MB_ICONSTOP);
//		*pb_Cancel = TRUE;
	}
}

// Surf to an HTML file which is embedded in this EXE file
// Example "res://C:\Program Files\HtmlEditDemo.exe/Html_Help"
// How to embed a HTML source see file "DHtmlEditDemo.rc" :
// Html_Help       HTML       DISCARDABLE     "res\\Html_Help.htm"
BOOL CHtmlEditor::NavigateToEmbeddedResource(CString s_RsrcName)
{
	// Get the full path to this EXE
	TCHAR t_File[MAX_PATH];
	GetModuleFileName(0, t_File, MAX_PATH);

	CString s_URL;
	s_URL.Format(_T("res://%s/%s"), t_File, s_RsrcName);

	return Navigate(s_URL);
}

// Overrides CHtmlEditView::Navigate
BOOL CHtmlEditor::Navigate(LPCTSTR t_URL, DWORD dwFlags, LPCTSTR lpszTargetFrameName, LPCTSTR lpszHeaders, LPVOID lpvPostData, DWORD dwPostDataLen)
{
	if (mb_SourceMode)
		return FALSE;

	SetDisplayMode(FALSE, FALSE); // Switch to BrowseMode
	CHtmlEditView::Navigate(t_URL, dwFlags, lpszTargetFrameName, lpszHeaders, lpvPostData, dwPostDataLen);
	return TRUE;
}

// This function is important to assure that Internet Explorer will work as expected
// If the following Registry Keys have the wrong value, Internet Explorer
// will display wrong colors, wrong font sizes and no images at all !!!
void CHtmlEditor::ResetMsieSettings()
{
	cMisc::RegWriteDword (_HKCU, _T("Software\\Microsoft\\Internet Explorer\\Styles"),   _T("Use My Stylesheet"),       0);
	cMisc::RegWriteDword (_HKCU, _T("Software\\Microsoft\\Internet Explorer\\Settings"), _T("Always Use My Colors"),    0);
	cMisc::RegWriteDword (_HKCU, _T("Software\\Microsoft\\Internet Explorer\\Settings"), _T("Always Use My Font Face"), 0);
	cMisc::RegWriteDword (_HKCU, _T("Software\\Microsoft\\Internet Explorer\\Settings"), _T("Always Use My Font Size"), 0);
	cMisc::RegWriteString(_HKCU, _T("Software\\Microsoft\\Internet Explorer\\Main"),     _T("Display Inline Images"),   _T("yes"));
}


// Creates the HTML View from the given static control which is child of a parent dialog 
// The static is hidden and replaced by a Html View and a Richedit of the same size and position
// Either of the CHtmlEditor (CHtmlEditView) and CUniRichEdit will be hidden and the other visible
// p_NotificationWnd will receive WM_IDLEUPDATECMDUI messages when the UI must be updated
// when the GUI must be updated
BOOL CHtmlEditor::CreateEditor(CWnd   *p_Static,           // the place holder static
							   CWnd   *p_NotificationWnd,  // the window that receives WM_IDLEUPDATECMDUI
							   BOOL    b_EditOnlyBody,     // TRUE: Source Editor shows only content of <BODY>
							   BOOL    b_EnableThemes)     // TRUE: Use Windows XP Themes
{
	ASSERT(p_Static && p_NotificationWnd);

	mp_NotificationWnd   = p_NotificationWnd;
	mp_Static            = p_Static;
	mb_EditOnlyBody      = b_EditOnlyBody;
	mb_EnableThemes      = b_EnableThemes;
	mb_InitDone          = FALSE;
	mb_CleanUp           = FALSE;
	mb_SubClassed        = FALSE;

	CRect k_Rect;
	p_Static->GetWindowRect(&k_Rect);

	gp_Parent = p_Static->GetTopLevelParent();
	p_Static->ShowWindow(FALSE);

	ASSERT(gp_Parent);
	gp_Parent->ScreenToClient(&k_Rect);

	// create invisible
	const UINT u32_Styles = WS_CHILD | WS_VSCROLL| WS_HSCROLL | WS_TABSTOP | ES_DISABLENOSCROLL | 
	                        ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

	if (!mi_RichEdit.CreateEx(WS_EX_CLIENTEDGE, u32_Styles, k_Rect, gp_Parent, 55553))
		return FALSE;

	// IMPORTANT: Choose a font here which exists on ALL Windows operating systems !!
	// Additionally it must exist as UNICODE font on Windows NT, 2000, XP, 2003... !!
	CFont i_Font;
	if (! i_Font.CreateFont(14,0,0,0,FW_NORMAL,0,0,0,0,0,0,0,0,_T("Courier New")))
		return FALSE;
	
	mi_RichEdit.SetFont(&i_Font, FALSE);
	mi_RichEdit.SetEditor(this);


	// This function MUST be called BEFORE calling CHtmlEditView::Create() !!
	ResetMsieSettings();

	// Create CHtmlEditView
	if (!Create(0, _T("DHtmlEditor"), WS_CHILD | WS_VISIBLE, k_Rect, gp_Parent, 55554))
		return FALSE;

	// navigate to empty start page (calls OnNavigateComplete2())
	CHtmlEditView::Navigate(_T("about:blank")); 
	return TRUE;
}

// This function is called after each 
// CHtmlEditor::Navigate(), CHtmlEditor::NavigateToEmbeddedResource(), 
// cHtmlDocument::SetHtml() and cHtmlDocument::SetDesignMode()
void CHtmlEditor::OnNavigateComplete2(LPCTSTR t_URL)
{
	// ATTENTION: Always retrieve the document after a navigation !!
	// Internet Explorer generates a new document instance each time you navigate !!
	CComPtr<IDispatch> D_Doc = GetHtmlDocument();
	mi_HtmDoc.Assign(D_Doc, this);

	// Execute the following only once after CreateEditor()
	if (!mb_SubClassed)
	{
		mb_SubClassed = TRUE;

		mi_HtmDoc.SetDesignMode(TRUE);
		Clear();

		ExecSetCommand(IDM_KEEPSELECTION,      true); // don't forgert user selection on losing focus
		ExecSetCommand(IDM_AUTOURLDETECT_MODE, true); // auto detect typed email addresses and URLs

		// retieve the "Internet Explorer_Server" window
		HWND h_Shell = ::FindWindowEx(m_hWnd,  0, _T("Shell Embedding"),          0);
		HWND h_DocOb = ::FindWindowEx(h_Shell, 0, _T("Shell DocObject View"),     0);
		HWND h_MSIE  = ::FindWindowEx(h_DocOb, 0, _T("Internet Explorer_Server"), 0);

		// subclass the "Internet Explorer_Server" window
		mi_MSIE.SetEditor(this);
		mi_MSIE.SubclassWindow(h_MSIE);
	}

	// Here the Body Tag may be invalid !!
	// Do not modify mb_CleanUp here !!!
	SetTimer(ID_TIMER_WAIT_BUSY, 100, 0);
}

// This function assures that the document is valid before CleanUpTags() is called
void CHtmlEditor::DelayCeanUp()
{
	mb_CleanUp = TRUE;
	SetTimer(ID_TIMER_WAIT_BUSY, 100, 0);
}

// Called after Navigate() or SetHtml() when the Body has become invalid
// DO NOT USE OnDocumentComplete() here !! It is not called every time !!
LRESULT CHtmlEditor::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_TIMER)
	{
		if (wParam == ID_TIMER_WAIT_BUSY)
		{
			// Check if the Browser is still loading a webpage
			if (GetBusy() || !GetDocument()->GetBody(FALSE).Valid())
				return 0;

			KillTimer(wParam);

			if (!mb_InitDone) // only the very first time:
			{
				mb_InitDone = TRUE;
				NotifyParent(HTMLEDIT_INIT_DONE,  FALSE);
				NotifyParent(HTMLEDIT_SETDEFAULT, FALSE);
			}
			
			if (mb_CleanUp)
			{
				mb_CleanUp = FALSE;
				mi_HtmDoc.CleanUpTags();
			}

			// Notify GUI that we have a new URL now (and the document is valid)
			NotifyParent(HTMLEDIT_NAVIGATED, TRUE);
			return 0;
		}
	}
	return CHtmlEditView::WindowProc(message, wParam, lParam);
}

// Overrides CHtmlEditView::OnUpdateUI()
// called after the user has modified the editor's content or moved the cursor
// Used to update GUI (Comboboxes, Checkboxes)
HRESULT CHtmlEditor::OnUpdateUI()
{
	NotifyParent(HTMLEDIT_UPDATE_UI, TRUE);
	return CHtmlEditView::OnUpdateUI();
}

// b_Post = FALSE: this function will not return before the parent has finished processing
// b_Post = TRUE:  this function will return immediately (asynchronous calling the parent)
void CHtmlEditor::NotifyParent(UINT u32_CommandID, BOOL b_Post)
{
	if (b_Post) mp_NotificationWnd->PostMessage(WM_IDLEUPDATECMDUI, u32_CommandID, 0);
	else        mp_NotificationWnd->SendMessage(WM_IDLEUPDATECMDUI, u32_CommandID, 0);
}

// DO NOT MODIFY THIS FUNCTION !! 
// (Otherwise you get trouble because of an Internet Explorer bug !)
// See also comment of SetHtml() !
// If b_SourceMode = TRUE --> b_DesignMode is obviously ignored !
void CHtmlEditor::SetDisplayMode(BOOL b_SourceMode, BOOL b_DesignMode)
{
	mi_HtmDoc.MakeImagesAbsolute();

	CString s_Html;
	if (mb_SourceMode != b_SourceMode) // Source Mode is switched on or off
	{
		mb_SourceMode  = b_SourceMode;

		if (b_SourceMode) // HTML --> Source
		{
			mi_HtmDoc.CleanUpTags();

			if (mb_EditOnlyBody) s_Html = mi_HtmDoc.GetBody(TRUE).GetInnerHtml();
			else                 s_Html = mi_HtmDoc.GetHtml();
		
			s_Html.Replace(_T("<BR>"), _T("\r\n<BR>"));
			mi_RichEdit.SetWindowText(s_Html);
		}
		else // Source --> HTML
		{
			mi_RichEdit.GetWindowText(s_Html);

			if (mb_EditOnlyBody)
			{
				mi_HtmDoc.GetBody(TRUE).SetInnerHtml(s_Html);
				mi_HtmDoc.CleanUpTags();
			}
			else
			{
				mi_HtmDoc.SetHtml(s_Html); // calls Clean Up
			}
		}
	}
	// Switch between Design and Browse Mode ONLY if not in Source Mode 
	// and ONLY if not switching from Source to HTML or vice versa !!!!!!!!!
	// Otherwise you will get trouble !!
	else if (!mb_SourceMode && mi_HtmDoc.GetDesignMode() != b_DesignMode)
	{
		// Workaround for Internet Explorer Bug forgetting it's content
		// when calling SetDesignMode() after SetHtml() has been called before
		s_Html = mi_HtmDoc.GetHtml();
		mi_HtmDoc.SetDesignMode(b_DesignMode);
		mi_HtmDoc.SetHtml(s_Html); // calls Clean Up
	}

	EnableEditor(mb_Enabled);

	NotifyParent(HTMLEDIT_UPDATE_UI, TRUE);
}

// This function can be used to optically disable the Editor
// If you would use the API function EnableWindow(FALSE) instead 
// there is optically no difference in the display of Internet Explorer
// If b_Enabled is FALSE the empty Static control will displayed instead
void CHtmlEditor::EnableEditor(BOOL b_Enable)
{
	mb_Enabled = b_Enable;

	mp_Static-> ShowWindow(!b_Enable                    ? SW_SHOW : SW_HIDE);
	mi_RichEdit.ShowWindow((b_Enable &&  mb_SourceMode) ? SW_SHOW : SW_HIDE);
	this->      ShowWindow((b_Enable && !mb_SourceMode) ? SW_SHOW : SW_HIDE);
}

// use this function to set a new size or position of the HtmlEditor
// if u32_Flags == SWP_NOSIZE --> Width and Height are ignored
// if u32_Flags == SWP_NOMOVE --> Left  and Top    are ignored
void CHtmlEditor::MoveWindow(CRect k_Rect, UINT u32_Flags) // =0
{
	MoveWindow(k_Rect.left, k_Rect.top, k_Rect.Width(), k_Rect.Height(), u32_Flags);
}

// use this function to set a new size or position of the HtmlEditor
// if u32_Flags == SWP_NOSIZE --> Width and Height are ignored
// if u32_Flags == SWP_NOMOVE --> Left  and Top    are ignored
void CHtmlEditor::MoveWindow(int Left, int Top, int Width, int Height, UINT u32_Flags) // =0
{
	if (!mb_InitDone)
		return;

	u32_Flags |= SWP_NOZORDER | SWP_NOACTIVATE;

     CHtmlEditView::SetWindowPos(0, Left, Top, Width, Height, u32_Flags);
	mi_RichEdit.SetWindowPos(0, Left, Top, Width, Height, u32_Flags);
	mp_Static-> SetWindowPos(0, Left, Top, Width, Height, u32_Flags);

	// Workaround for MSIE bug
	// This must be set otherwise Internet Explorer loses its inner border
	m_pBrowserApp->put_Top   (0);
	m_pBrowserApp->put_Left  (0);
	m_pBrowserApp->put_Height(Height);
	m_pBrowserApp->put_Width (Width);
}

// This function is called after the user has hit any key (WM_KEYUP)
// Under some cirumstances (e.g. after hitting Enter twice inside a <UL> or <OL> list)
// Internet Explorer starts inserting <P> instead of <DIV> BEHIND the </UL> or </OL>
// This function replaces all illegal <P> tags with <DIV> tags after hitting the Return key
// (in contrast cHtmlDocument::ReplaceParagraph() is called after pasting HTML code!!)
void CHtmlEditor::ReplaceParagraphs(UINT u32_VirtKeyCode)
{
	if (u32_VirtKeyCode == VK_RETURN) // the enter key
	{
		BOOL b_Replaced = FALSE;

		// In the usual case there should be not more than one <P> tag in this collection
		CComQIPtr<IHTMLElementCollection> i_Collect;
		int s32_Count = mi_HtmDoc.GetElementCollection(_T("P"), i_Collect);

		// Decrement because removed elements will be eliminated from the collection
		for (int p=s32_Count-1; p>=0; p--)
		{
			cHtmlElement i_Para = cHtmlElement::GetElementFromCollection(p, i_Collect);

			CString s_Inner = i_Para.GetInnerHtml();
			if (!s_Inner.GetLength()) s_Inner = _T("&nbsp;");

			// Insert new <DIV> tag BEFORE the deleted <P> tag (before the cursor position)
			i_Para.InsertHtml(_T("<DIV>") + s_Inner + _T("</DIV>"), TRUE, FALSE);
			i_Para.Remove(); // remove <P>

			b_Replaced = TRUE;
		}

		// IMPORTANT: The cursor must be moved back by one char to assure 
		// that succeeding editing will take place INSIDE the newly added <DIV> tag 
		// and not behind it, which would again insert further <P> tags !!!
		// Here we hit the LEFT key which moves the curser back into the <DIV>&nbsp;</DIV>
		if (b_Replaced)
		{
			// MSDN says that keybd_event() is superseded by SendInput()
			// but SendInput() is not available on Windows 95 and much more awkward to use
			keybd_event(VK_LEFT, 0, KEYEVENTF_EXTENDEDKEY,                   0);
			keybd_event(VK_LEFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			
			// store in member variable that replacement took place for the key after Return
			mb_ParaReplaced = TRUE;
			return;
		}
	}
	
	// This will be executed with the FOLLOWING key AFTER the ENTER key!
	if (mb_ParaReplaced)
	{
		mb_ParaReplaced = FALSE; // do the following only once

		// A bug in Internet Explorer 6.0 inserts an empty tag
		// <FONT style="BACKGROUND-COLOR: #ffffff"></FONT>
		// if the body background color is NOT white. 
		// This font tag appears behind the new <DIV> tag after the user has typed any text. 
		// Here empty font tags are removed.
		CComQIPtr<IHTMLElementCollection> i_Collect;
		int s32_Count = mi_HtmDoc.GetElementCollection(_T("FONT"), i_Collect);

		// Decrement because removed elements will be eliminated from the collection
		for (int f=s32_Count-1; f>=0; f--)
		{
			cHtmlElement i_Font = cHtmlElement::GetElementFromCollection(f, i_Collect);
			if (i_Font.IsEmpty()) i_Font.Remove();
		}
	}
}

// see cHtmlDocument::QueryStatus()
UINT CHtmlEditor::QueryStatus(UINT u32_Command)
{
	BOOL b_Edit = mi_HtmDoc.GetDesignMode();

	switch (u32_Command)
	{
	case IDM_VIEWSOURCE: // 2139
		return (mb_SourceMode)   ? OLECMDF_LATCHED : 0;
	case IDM_EDITMODE:   // 2127
		return (b_Edit)          ? OLECMDF_LATCHED : 0;
	case IDM_BROWSEMODE: // 2126
		return (!b_Edit)         ? OLECMDF_LATCHED : 0;
	};	

	// Disable all GUI buttons if not in Edit mode
	if (!b_Edit)
		return 0;

	return mi_HtmDoc.QueryStatus(u32_Command);
}

// erases all content from the document
// Hitting the Enter key will insert a new <DIV> (1 new line) instead of <P> (2 new lines)
void CHtmlEditor::Clear()
{
	CString s_Html;
	s_Html.Format(_T("<HTML><HEAD><META http-equiv=MSThemeCompatible content=%s></HEAD><BODY><DIV></DIV></BODY></HTML>"),
	              mb_EnableThemes ? _T("yes") : _T("no"));
	
	mi_HtmDoc.SetHtml(s_Html);
}

// see cHtmlDocument::ExecSetCommand()
BOOL CHtmlEditor::ExecSetCommand(UINT        u32_Command, 
								 CComVariant v_In,         // = 0 (input value)
								 BOOL        b_PromptUser) // = TRUE
{
	return mi_HtmDoc.ExecSetCommand(u32_Command, v_In, b_PromptUser);
}

// see cHtmlDocument::ExecGetCommand()
BOOL CHtmlEditor::ExecGetCommand(UINT u32_Command, CComVariant *pv_Out) // output value
{
	return mi_HtmDoc.ExecGetCommand(u32_Command, pv_Out);
}

// see cHtmlDocument::ExecGetCommand()
// returns a BSTR or I4 or BOOL converted to CString
BOOL CHtmlEditor::ExecGetCommandStr(UINT u32_Command, CString *ps_Out) // output value
{
	CComVariant v_Out;
	if (!mi_HtmDoc.ExecGetCommand(u32_Command, &v_Out))
	{
		*ps_Out = _T("");
		return FALSE;
	}

	*ps_Out = cMisc::VarToStr(v_Out);
	return TRUE;
}

// Save document to file
void CHtmlEditor::Save()
{
	// You can make the path a variable on your own here
	if (!ExecSetCommand(IDM_SAVEAS, L"C:\\DhtmlEdit.htm"))
		gp_Parent->MessageBox(_T("Error saving the file"), _T("Error"), MB_ICONSTOP);
}

// returns the Version of Internet Explorer by reading the file version of MSHTML.DLL
// returns 50 or 55 or 60 (or 0 on error)
// requires Version.lib to be included into the project
UINT CHtmlEditor::GetMsieVersion()
{
	static UINT u32_Version = 0;
	if (!u32_Version) // Determine MSIE Version only at the first call
	{
		// read whole file infos into buffer s8_Info
		char s8_Info[3000];
		if (!GetFileVersionInfoA("MSHTML.DLL", 0, sizeof(s8_Info), s8_Info)) 
			return 0;

		UINT u32_Len;
		VS_FIXEDFILEINFO *pk_Info;
		if (!VerQueryValueA(s8_Info, "\\", (void**) &pk_Info, &u32_Len))
			return 0;

		u32_Version = HIWORD(pk_Info->dwFileVersionMS) * 10 + LOWORD(pk_Info->dwFileVersionMS);
	}
	return u32_Version;
}

// returns FALSE for Windows 95, 98, ME and TRUE otherwise
BOOL CHtmlEditor::IsPlatformNT()
{
	return mb_PlatformNT;
}

// ##########################  MSIEWND  ###############################

// This class subclasses the "Internet Explorer_Server" window
// It can capture mouse and keyboard events in Internet Explorer
// It disables the context menu (right click)

void CHtmlEditor::CMsieWnd::SetEditor(CHtmlEditor *p_Editor)
{
	mp_Editor = p_Editor;
}

LRESULT CHtmlEditor::CMsieWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// disable Internet Explorer Context menu on right mouse click in Design mode
	if (message == WM_CONTEXTMENU && mp_Editor->GetDisplayMode() == IDM_EDITMODE)
	{
		// You can implement your own context menu handler here (using TrackPopupMenuEx())
		return 0;
	}
	
	LRESULT Res;	
	// Let Internet Explorer process the message
	// normally you would write 
	// Res = CWnd::WindowProc(message, wParam, lParam);
	// here, but this would cripple Unicode messages in MBCS builds !
	// For example hitting the Euro key would display a wrong character !
	// m_pfnSuper is the origional window procedure which was subclassed
	if (mp_Editor->IsPlatformNT())
		Res = CallWindowProcW(m_pfnSuper, m_hWnd, message, wParam, lParam);
	else
		Res = CallWindowProcA(m_pfnSuper, m_hWnd, message, wParam, lParam);

	if (message == WM_KILLFOCUS)
	{
		mp_Editor->NotifyParent(HTMLEDIT_KILLFOCUS, FALSE);
	}
	// After a paste from the clipboard into the HTML Editor
	else if (message == WM_COMMAND && LOWORD(wParam) == 0x1A)
	{
		mp_Editor->DelayCeanUp();
	}
	// after hitting the Enter key -> check for <P> tags to be replaced with <DIV>
	else if (message == WM_KEYUP)
	{
		mp_Editor->ReplaceParagraphs(wParam);
	}

	return Res;
}

// Catch keyboard messages while CTRL key down
BOOL CHtmlEditor::CMsieWnd::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && mp_Editor->GetDisplayMode() == IDM_EDITMODE)
	{
		BOOL b_Ctrl  = (GetKeyState(VK_CONTROL) & 0x8000) > 0;
		BOOL b_Shift = (GetKeyState(VK_SHIFT)   & 0x8000) > 0;
		BOOL b_Alt   = (GetKeyState(VK_MENU)    & 0x8000) > 0;

		if (b_Ctrl && !b_Shift && !b_Alt)
		{
			switch (pMsg->wParam)
			{
			case 'N':  // prevent stupid default behavior for CTRL N (opening Windows Explorer)
				return TRUE;

			case 'T':  // CTRL T: inserts a new table
				mp_Editor->GetDocument()->InsertTable(2,2);
				return TRUE;

			case 'H':  // CTRL H: insert horizontal line
				mp_Editor->ExecSetCommand(IDM_HORIZONTALLINE, 0);
				return TRUE;

			case 'O':  // CTRL O: new table column
				mp_Editor->GetDocument()->InsertNewTableColumn(TRUE);
				return TRUE;

			case 'R':  // CTRL R: new table row
				mp_Editor->GetDocument()->InsertNewTableRow(TRUE);
				return TRUE;

			case 'S':  // CTRL S: save document
				mp_Editor->Save();
				return TRUE;
			}
		}
	}

	return FALSE;
}

// ##########################  STREAMREADER  ###############################

// cStreamReader is required for cHtmlDocument::SetHtml()
// The other methods except Read are not required so they are not implemented here
// (MFC7 uses CStreamOnCString whose implementation is BUGGY !)

CHtmlEditor::cStreamReader::cStreamReader()
{
	mps8_Data    = 0;
	mu32_DataLen = 0;
	mu32_Index   = 0;
}

CHtmlEditor::cStreamReader::~cStreamReader()
{
	if (mps8_Data) delete mps8_Data;
}

// Sets a MBCS or Unicode string
void CHtmlEditor::cStreamReader::SetData(LPCTSTR szData)
{
	UINT u32_CharsToCopy = _tcsclen(szData);

	if (mps8_Data) delete mps8_Data;

	// Make mps8_Data ALWAYS contain an ANSI string even in _UNICODE version !
	#ifdef _UNICODE
	
		mu32_DataLen = u32_CharsToCopy * 8; // for worst case: 1 Unicode char -> "&#xABCD;"
		mps8_Data    = new char[mu32_DataLen];
		
		// EncodeHtml() modifies mu32_DataLen to the new MBCS length!
		EncodeHtml(szData, &u32_CharsToCopy, mps8_Data, &mu32_DataLen);
	
	#else // _MBCS

		mu32_DataLen = u32_CharsToCopy;
		mps8_Data    = new char[mu32_DataLen];
		
		memcpy(mps8_Data, szData, mu32_DataLen);
	
	#endif
	
	mu32_Index = 0;
}

// Read is used for cHtmlDocument::SetHtml()
// Read is called by Mshtml.dll
// returns the ANSI string data which must have been set with cStreamReader::SetData() 
// to the caller which may request any number of bytes from the stream
HRESULT CHtmlEditor::cStreamReader::Read(void    *pv_Buffer,    // IN  the buffer that receives the stream data
					            		 ULONG   u32_BufSize,   // IN  the number of bytes requested (=buffer size)
							             ULONG *pu32_ReadBytes) // OUT the number of bytes which have been copied to pv_Buffer
{
	if (pu32_ReadBytes) *pu32_ReadBytes = 0;

	if (!pv_Buffer)
		return E_POINTER;

	((char*)pv_Buffer)[0] = 0;

	char *s8_Start = mps8_Data + mu32_Index;
	char *s8_End   = mps8_Data + mu32_DataLen;

	int s32_CharsLeft  = s8_End - s8_Start;
	if (s32_CharsLeft <= 0)
		return S_FALSE; // no more data to read

	int s32_CharsToCopy  = min(s32_CharsLeft, (int)u32_BufSize);
	if (s32_CharsToCopy <= 0)
	{
		mu32_Index = 0;
		return S_FALSE;
	}

	memcpy(pv_Buffer, s8_Start, s32_CharsToCopy);

	if (pu32_ReadBytes) *pu32_ReadBytes = s32_CharsToCopy;

	mu32_Index += s32_CharsToCopy;

	return S_OK;
}

HRESULT CHtmlEditor::cStreamReader::QueryInterface(REFIID iid, void **ppUnk)
{
	return E_NOINTERFACE;
}

ULONG CHtmlEditor::cStreamReader::AddRef() 
{
	return 1;
}

ULONG CHtmlEditor::cStreamReader::Release() 
{
	return 1;
}

HRESULT CHtmlEditor::cStreamReader::Seek(LARGE_INTEGER, DWORD, ULARGE_INTEGER*)
{
	return E_NOTIMPL;
}

HRESULT CHtmlEditor::cStreamReader::SetSize(ULARGE_INTEGER)
{
	return E_NOTIMPL;
}

HRESULT CHtmlEditor::cStreamReader::CopyTo(IStream*, ULARGE_INTEGER, ULARGE_INTEGER*, ULARGE_INTEGER*)
{
	return E_NOTIMPL;
}

HRESULT CHtmlEditor::cStreamReader::Commit(DWORD)
{
	return E_NOTIMPL;
}

HRESULT CHtmlEditor::cStreamReader::Revert()
{
	return E_NOTIMPL;
}

HRESULT CHtmlEditor::cStreamReader::LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)
{
	return E_NOTIMPL;
}

HRESULT CHtmlEditor::cStreamReader::UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)
{
	return E_NOTIMPL;
}

HRESULT CHtmlEditor::cStreamReader::Stat(STATSTG*, DWORD)
{
	return E_NOTIMPL;
}

HRESULT CHtmlEditor::cStreamReader::Clone(IStream**)
{
	return E_NOTIMPL;
}

// Write is not required as this can be done much easyier see cHtmlDocument::GetHtml()
HRESULT CHtmlEditor::cStreamReader::Write(const void *pv_Buffer, ULONG u32_BufSize, ULONG *pcbWritten)
{
	return E_NOTIMPL;
}

