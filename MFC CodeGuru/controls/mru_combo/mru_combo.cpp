////////////////////////////////////////////////////////////////////////////////////////
// class AIComboBox3Entry
// ----- ----------------
class AIComboBox3Entry
{
    public:
     enum { NoneFont = 0x00, FromMRU = 0x01 };
    private:
     BYTE       Style;
    public:
                AIComboBox3Entry(BYTE = 0);

     BYTE       GetStyle()          const;
     void       SetStyle(BYTE);
};
////////////////////////////////////////////////////////////////////////////////////////
// class AIComboBox3
// ----- -----------
class AIComboBox3 : public CComboBox
{
    friend class AIComboBox3Entry;
    public:
     enum { DrawNone = 0x00, DrawDoubleLine = 0x01, DrawWaveLine = 0x02 };
    private:
     BYTE            Separator;
     BYTE            CountMRU;
     BYTE            LimitMRU;
    private:
     void            UpdateMRU();
    protected:
     // MFC stuff ...
     virtual void    DrawItem(DRAWITEMSTRUCT*);
     virtual void    MeasureItem(MEASUREITEMSTRUCT*);
     afx_msg void    OnSysColorChange();
     afx_msg void    OnKeyDown(UINT, UINT, UINT);
     afx_msg void    OnSelEndOk();
     afx_msg void    OnDestroy();
    public:
                     AIComboBox3(BYTE = DrawDoubleLine, BYTE = 5);
                    ~AIComboBox3();
    
     bool            Create(CWnd*, const CRect&, DWORD, DWORD = 0);

     BYTE            GetSeparator()          const;
     BYTE            GetLimitMRU()           const;
     BYTE            GetCountMRU()           const;

    DECLARE_MESSAGE_MAP()
};
////////////////////////////////////////////////////////////////////////////////////////
// class AIFontEntry
// ----- -----------
class AIFontEntry : public AIComboBox3Entry
{
    public:
     enum { NoneFont = 0x00, TrueTypeFont = 0x01, DeviceFont = 0x02, RasterFont = 0x04 };
    private:
     BYTE       FontType;
     BYTE       CharSet;
     BYTE       PitchAndFamily;
     CString    FaceName;
     CString    Script;
    public:
                AIFontEntry(BYTE, BYTE = DEFAULT_CHARSET, BYTE = DEFAULT_PITCH|FF_DONTCARE, const TCHAR* = null, const TCHAR* = null);

     BYTE       GetFontType()           const;
     BYTE       GetCharSet()            const;
     BYTE       GetPitchAndFamily()     const;
     CString    GetFaceName()           const;
     CString    GetScript()             const;
};
////////////////////////////////////////////////////////////////////////////////////////
// class AIComboBoxFontFamily
// ----- --------------------
class AIComboBoxFontFamily : public AIComboBox3
{
    private:
     bool                  Expand;
     BYTE                  GlyphWidth;
     BYTE                  GlyphHeight;
     BYTE                  CharSet;
     WORD                  OffsetExpand;
     DWORD                 Flags;
     CString               FaceName;
     HFONT                 HFont;
     HBITMAP               TrueTypeGlyph;

     static BYTE           PredefinedGUIPointSize[SizeOfBuffer16];
    private:
     CString               BuildString(DWORD);

     // Win32 stuff ...
     static INT CALLBACK   EnumFontFamExProc(ENUMLOGFONTEX*, NEWTEXTMETRIC*, INT, LPARAM);
    protected:
     // MFC stuff ...
     virtual void          DrawItem(DRAWITEMSTRUCT*);
     virtual void          MeasureItem(MEASUREITEMSTRUCT*);
     virtual void          DeleteItem(DELETEITEMSTRUCT*);
     virtual INT           CompareItem(COMPAREITEMSTRUCT*);
    public:
                           AIComboBoxFontFamily(BYTE = DrawDoubleLine, BYTE = 5, DWORD = CF_NOVECTORFONTS|CF_NOSIMULATIONS, const TCHAR* = null, BYTE = DEFAULT_CHARSET);
                          ~AIComboBoxFontFamily();
    
     bool                  Create(CWnd*, const CRect&, DWORD, DWORD = 0);

     void                  Init();
                    
     bool                  IsExpand()               const;
     void                  SetExpand(bool = true);

     BYTE                  GetCharSet()             const;
     CString               GetFaceNameStr()         const;

     DWORD                 GetFlags()               const;

     static BYTE&          GetPredefinedGUIPointSize();

    DECLARE_MESSAGE_MAP()
};
////////////////////////////////////////////////////////////////////////////////////////
// class AIComboBox3Entry
// ----- ----------------
inline AIComboBox3Entry::AIComboBox3Entry(BYTE style)
{
    Style = style;
}

inline BYTE AIComboBox3Entry::GetStyle() const
{
    return Style;
}

inline void AIComboBox3Entry::SetStyle(BYTE style)
{
    Style = style;
}
////////////////////////////////////////////////////////////////////////////////////////
// class AIComboBox3
// ----- -----------
inline BYTE AIComboBox3::GetSeparator() const
{
    return Separator;
}

inline BYTE AIComboBox3::GetLimitMRU() const
{
    return LimitMRU;
}

inline BYTE AIComboBox3::GetCountMRU() const
{
    return CountMRU;
}
////////////////////////////////////////////////////////////////////////////////////////
// class AIFontEntry
// ----- -----------
inline BYTE AIFontEntry::GetFontType() const
{
    return FontType;
}

inline BYTE AIFontEntry::GetCharSet() const
{
    return CharSet;
}

inline BYTE AIFontEntry::GetPitchAndFamily() const
{
    return PitchAndFamily;
}

inline CString AIFontEntry::GetFaceName() const
{
    return FaceName;
}

inline CString AIFontEntry::GetScript() const
{
    return Script;
}
////////////////////////////////////////////////////////////////////////////////////////
// class AIComboBoxFontFamily
// ----- --------------------
inline bool AIComboBoxFontFamily::IsExpand() const
{
    return Expand;
}

inline void AIComboBoxFontFamily::SetExpand(bool expand)
{
    Expand = expand;
}

inline DWORD AIComboBoxFontFamily::GetFlags() const
{
    return Flags;
}

inline BYTE AIComboBoxFontFamily::GetCharSet() const
{
    return CharSet;
}

inline CString AIComboBoxFontFamily::GetFaceNameStr() const
{
    return FaceName;
}

inline BYTE& AIComboBoxFontFamily::GetPredefinedGUIPointSize()
{
    return (BYTE&)PredefinedGUIPointSize;
}
////////////////////////////////////////////////////////////////////////////////////////
inline void AILockWindow(HWND hwnd, bool lock)
{
    if(hwnd && ::IsWindow(hwnd))
    {
        ::SendMessage(hwnd, WM_SETREDRAW, !lock, 0L);
    }
}

inline void AIFastRect(HDC hdc, INT x, INT y, INT w, INT h)
{
    CRect r(x, y, x+w, y+h);
    ::ExtTextOut(hdc, x, y, ETO_OPAQUE, &r, 0, 0, 0);
#ifdef _DEBUG
    ::GdiFlush();
#endif
}

inline void AIFastRect(HDC hdc, const CPoint& pt, const AISize& sz)
{
    AIFastRect(hdc, pt.x, pt.y, sz.cx, sz.cy);
}

inline void AIFastRect(HDC hdc, const CRect& r)
{
    AIFastRect(hdc, r.left, r.top, r.Width(), r.Height());
}

inline void AIFastHLine(HDC hdc, INT x, INT y, INT w, BYTE dy)
{
    AIFastRect(hdc, x, y, w, dy);
}

inline void AIFastHLine(HDC hdc, const CPoint& pt, INT w, BYTE dy)
{
    AIFastRect(hdc, pt.x, pt.y, w, dy);
}

inline void AIFastVLine(HDC hdc, INT x, INT y, INT h, BYTE dx)
{
    AIFastRect(hdc, x, y, dx, h);
}

inline void AIFastVLine(HDC hdc, const CPoint& pt, INT h, BYTE dx)
{
    AIFastRect(hdc, pt.x, pt.y, dx, h);
}

void AIDrawWaveLine(HDC hdc, const CPoint& pt, WORD extent, COLORREF color)
{
    register WORD x   = WORD(pt.x);
    register WORD y   = WORD(pt.y);
    register WORD tmp = 0;
    register WORD dy;

    for(register WORD i = 0; i < extent; i++)
    {
        if(tmp == 0)
        {
            dy = 0;
        }
        else if(tmp == 1 || tmp == 3)
        {
            dy = 1;
        }
        else if(tmp == 2)
        {
            dy = 2;
        }

        if(++tmp > 3)
        {
            tmp = 0;
        }

        SetPixelV(hdc, x++, y+dy, color);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class AIComboBox3
// ----- -----------
BEGIN_MESSAGE_MAP(AIComboBox3, CComboBox)
    ON_WM_SYSCOLORCHANGE()
    ON_WM_KEYDOWN()
    ON_WM_DESTROY()
    ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelEndOk)
END_MESSAGE_MAP()

AIComboBox3::AIComboBox3(BYTE separator, BYTE count_mru)
{
    Separator = separator;
    CountMRU  = 0;
    LimitMRU  = count_mru;
}

AIComboBox3::~AIComboBox3()
{
}

bool AIComboBox3::Create(CWnd* parent, const CRect& r, DWORD id, DWORD style)
{
    AILock lock(this);

    if(parent)
    {
        BOOL   ret;

        style &= ~CBS_SIMPLE;
        style &= ~CBS_DROPDOWN;

        style |= WS_CHILD|WS_VSCROLL|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
        style |= CBS_OWNERDRAWFIXED|CBS_DROPDOWNLIST;

        ret = CComboBox::Create(style, r, parent, id);

        SetCurSel(0);

        return ret != 0;
    }
    return false;
}

void AIComboBox3::UpdateMRU()
{
    DWORD cur_sel = GetCurSel();
    DWORD data;
    DWORD index;
    DWORD count;

    if(cur_sel == 0 && CountMRU)
    {
        return;
    }

    AILock lock(this);

    AILockWindow(*this, true);
    DefWindowProc(CB_SHOWDROPDOWN, 0, 0);
    data = DefWindowProc(CB_GETITEMDATA, cur_sel, 0);

    count = DefWindowProc(CB_GETCOUNT, 0, 0);
    for(index = 0; index < cur_sel; index++)
    {
        if(data == DWORD(DefWindowProc(CB_GETITEMDATA, index, 0)))
        {
            break;
        }
    }

    if(index < CountMRU)
    {
        ((AIComboBox3Entry*)data)->SetStyle(AIComboBox3Entry::FromMRU);
        DefWindowProc(CB_SETITEMDATA, index, (LPARAM)data);
        DefWindowProc(CB_DELETESTRING, index, 0);
        CountMRU--;
    }

    if(CountMRU < LimitMRU)
    {
        CountMRU++;
    }

    ((AIComboBox3Entry*)data)->SetStyle(AIComboBox3Entry::FromMRU);

    DefWindowProc(CB_INSERTSTRING, 0, (LPARAM)data);
    SetCurSel(0);
    AILockWindow(*this, false);
}

// MFC stuff ...
afx_msg void AIComboBox3::OnSysColorChange()
{
    InvalidateRect(0, 1);
    UpdateWindow();
}

afx_msg void AIComboBox3::OnKeyDown(UINT key, UINT flags, UINT repeat)
{
    CComboBox::OnKeyDown(key, flags, repeat);

    if(!GetDroppedState())
    {
        if(key == VK_RETURN)
        {
            UpdateMRU();
        }
    }
}

afx_msg void AIComboBox3::OnSelEndOk()
{
    if(GetDroppedState())
    {
        UpdateMRU();
    }
}

afx_msg void AIComboBox3::OnDestroy()
{
    CComboBox::OnDestroy();
}

void AIComboBox3::DrawItem(DRAWITEMSTRUCT* draw_item)
{
    if(draw_item)
    {
        if(draw_item->CtlType == ODT_COMBOBOX && draw_item->itemID != -1)
        {
            if(draw_item->itemID >= 0 && draw_item->itemID < UINT(GetCount()))
            {
                if((draw_item->itemState & ODS_COMBOBOXEDIT) != ODS_COMBOBOXEDIT && draw_item->itemID == BYTE(CountMRU-1))
                {
                    HDC    hdc = draw_item->hDC;
                    CRect r(draw_item->rcItem);

                    ::SetBkColor(hdc, AIColor::Gray);

                    if(Separator == AIComboBox3::DrawDoubleLine)
                    {
                        AIFastHLine(hdc, r.left, r.bottom-4, r.Width());
                        AIFastHLine(hdc, r.left, r.bottom-2, r.Width());
                    }
                    else if(Separator == AIComboBox3::DrawWaveLine)
                    {
                        CPoint pt(r.left, r.bottom-3);
                        AIDrawWaveLine(hdc, pt, r.Width(), AIColor::Gray);
                    }
                }
            }
        }
    }
}

void AIComboBox3::MeasureItem(MEASUREITEMSTRUCT* measure_item)
{
    if(measure_item)
    {
        if(measure_item->CtlType == ODT_COMBOBOX)// avoid for this message ... && measure_item->itemID != -1)
        {
            TCHAR     sample[] = _T("mmm");
            CSize     sz;
            CWindowDC dc(CWnd::GetDesktopWindow());

            dc.SaveDC();

            dc.SelectObject((HFONT)::GetStockObject(DEFAULT_GUI_FONT));

            // here I used my private function ...
            ::GetTextExtentPoint32(dc, sample, sizeof(sample), &sz);
            measure_item->itemHeight = WORD(sz.cy);

            dc.RestoreDC(-1);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class AIFontEntry
// ----- -----------
AIFontEntry::AIFontEntry(BYTE font_type, BYTE charset, BYTE pitch_and_family, const TCHAR* face_name, const TCHAR* script)
           : AIComboBox3Entry(0)
{
    CharSet        = charset;
    PitchAndFamily = pitch_and_family;

    if(font_type == TRUETYPE_FONTTYPE)
    {
        FontType = TrueTypeFont;
    }
    else if(font_type == DEVICE_FONTTYPE)
    {
        FontType = DeviceFont;
    }
    else if(font_type == RASTER_FONTTYPE)
    {
        FontType = RasterFont;
    }
    else
    {
        FontType = NoneFont;
    }

    if(face_name)
    {
        FaceName = face_name;
    }

    if(script)
    {
        Script = script;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class AIComboBoxFontFamily
// ----- --------------------
const TCHAR FontFamilySampleText[] = _T("ABC abc");
const BYTE UnderLineGap           = 3;
const BYTE ExpandGap              = 8;
const BYTE PointSize10            = 80;

BYTE AIComboBoxFontFamily::PredefinedGUIPointSize[SizeOfBuffer16] = 
{ 
    8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72
};

BEGIN_MESSAGE_MAP(AIComboBoxFontFamily, AIComboBox3)
END_MESSAGE_MAP()

AIComboBoxFontFamily::AIComboBoxFontFamily(BYTE separator, BYTE count_mru, DWORD flags, const TCHAR* face_name, BYTE charset) : AIComboBox3(separator, count_mru)
{
    Expand       = false;
    HFont        = null;
    GlyphWidth   = 0;
    GlyphHeight  = 0;
    CharSet      = charset;
    OffsetExpand = 0;
    Flags        = flags;
    FaceName     = face_name;
}

AIComboBoxFontFamily::~AIComboBoxFontFamily()
{
    if(TrueTypeGlyph)
    {
        ::DeleteObject(HBITMAP(TrueTypeGlyph));
    }
}

bool AIComboBoxFontFamily::Create(CWnd* parent, const CRect& r, DWORD id, DWORD style)
{
    AILock lock(this);

    if(parent)
    {
        BOOL ret;

        AIImage image(::GetModuleHandle(TheModule), IDB_TT_GLYPH);
        TrueTypeGlyph = image.GetHBITMAP();

        if(TrueTypeGlyph)
        {
            GlyphWidth  = image.GetWidth()/2;
            GlyphHeight = image.GetHeight();
        }

        style &= ~CBS_HASSTRINGS;
        style |= CBS_SORT|LBS_SORT;

        ret = AIComboBox3::Create(parent, r, id, style);

        HFont = HFONT(::SendMessage(::GetParent(m_hWnd), WM_GETFONT, 0, 0));

        if(HFont)
        {
            ::SendMessage(m_hWnd, WM_SETFONT, (WPARAM)HFont, 1);
        }

        AILockWindow(*this, true);
        Init();
        AILockWindow(*this, false);

        SetCurSel(0);

        return ret != 0;
    }
    return false;
}

void AIComboBoxFontFamily::Init()
{
    LOGFONT   lf;
    CClientDC dc(this);

    AIInitMemory(&lf, sizeof(LOGFONT));

    if(!FaceName.IsEmpty())
    {
        wsprintf(lf.lfFaceName, FaceName);
    }

    lf.lfCharSet = CharSet;

    ResetContent();

    ::EnumFontFamiliesEx(dc, &lf, (FONTENUMPROC)AIComboBoxFontFamily::EnumFontFamExProc, LPARAM(this), 0);

    if(Expand)
    {
        WORD  offset     = 0;
        DWORD  count_item = DefWindowProc(CB_GETCOUNT, 0, 0);
        CSize   sz;
        CString str;

        if(HFont)
        {
            dc.SelectObject((HFONT)HFont);
        }
        else
        {
            dc.SelectObject((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
        }

        for(DWORD i = 0; i < count_item; i++)
        {
            str = BuildString(i);
            AIGetTextExtentABCPoint(dc, str, str.GetLength(), sz);
        
            if(offset < sz.cx)
            {
                offset = WORD(sz.cx);
            }
        }

        // here I used my private function ...
        ::GetTextExtentPoint(dc, FontFamilySampleText, _tcslen(FontFamilySampleText), &sz);

        OffsetExpand = WORD(offset)+ExpandGap;

        // it is from AIComboBox2
//        SetListBoxWidth(WORD(GlyphWidth+OffsetExpand+sz.cx+3*::GetSystemMetrics(SM_CXVSCROLL)));
    }
}

CString AIComboBoxFontFamily::BuildString(DWORD index)
{
    CString      str;
    AIFontEntry* entry = (AIFontEntry*)DefWindowProc(CB_GETITEMDATA, index, 0);

    if(entry)
    {
        str = entry->GetFaceName();

        if(entry->GetScript().GetLength())
        {
            str += _T(" (");
            str += entry->GetScript();
            str += _T(")");
        }
    }

    return str;
}

// MFC stuff ...
void AIComboBoxFontFamily::DrawItem(DRAWITEMSTRUCT* draw_item)
{
    if(draw_item)
    {
        if(draw_item->CtlType == ODT_COMBOBOX && draw_item->itemID != -1)
        {
            CFont*  font;
            CFont*  font2;
            CDC*    dc = CDC::FromHandle(draw_item->hDC);
            CBrush  brush_entire(COLORREF(::GetSysColor(COLOR_WINDOW)));
            CBrush  brush_select(COLORREF(::GetSysColor(COLOR_HIGHLIGHT)));
            CRect   r(draw_item->rcItem);

            dc->SaveDC();

            dc->SetBkMode(TRANSPARENT);

            if(HFont)
            {
                font  = CFont::FromHandle(HFont);
                font2 = dc->SelectObject(font);
            }
            else
            {
                font2 = (CFont*)dc->SelectStockObject(DEFAULT_GUI_FONT);
            }

            if((draw_item->itemState & ODS_SELECTED) == ODS_SELECTED)
            {
                dc->SetTextColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHTTEXT)));
                dc->SelectObject(brush_select);
            }
            else
            {
                dc->SetTextColor(COLORREF(::GetSysColor(COLOR_WINDOWTEXT)));
                dc->SelectObject(brush_entire);
            }
            dc->PatBlt(r.left, r.top, r.Width(), r.Height(), PATCOPY);

            if((draw_item->itemState & ODS_COMBOBOXEDIT) != ODS_COMBOBOXEDIT)
            {
                r.bottom -= UnderLineGap; // for underline
            }

            if(draw_item->itemID >= 0 && draw_item->itemID < UINT(GetCount()))
            {
                AIFontEntry* entry = (AIFontEntry*)DefWindowProc(CB_GETITEMDATA, draw_item->itemID, 0);

                if(entry)
                {
                    if(entry->GetFontType() & AIFontEntry::TrueTypeFont)
                    {
                        AIDrawTransBmp(*dc, HBITMAP(TrueTypeGlyph), WORD(r.left), WORD(r.top+(r.Height()-GlyphHeight)/2), GlyphWidth, GlyphHeight, AIColor::LtMagenta);
                    }
                    else if(entry->GetFontType() & AIFontEntry::DeviceFont)
                    {
                        AIDrawTransBmp(*dc, HBITMAP(TrueTypeGlyph), WORD(r.left+GlyphWidth), WORD(r.top), GlyphWidth, GlyphHeight, AIColor::LtMagenta);
                    }
                
                    r.left += GlyphWidth;

                    CString str = BuildString(draw_item->itemID);
                    dc->DrawText(str, str.GetLength(), r, DT_VCENTER|DT_SINGLELINE);

                    if(Expand && (draw_item->itemState & ODS_COMBOBOXEDIT) != ODS_COMBOBOXEDIT)
                    {
                        CFont* font = new CFont;
         
                        font->CreatePointFont(PointSize10, entry->GetFaceName(), dc);
                        font2 = dc->SelectObject(font);

                        r.left += OffsetExpand;
                        dc->DrawText(FontFamilySampleText, _tcslen(FontFamilySampleText), r, DT_BOTTOM|DT_SINGLELINE);

                        if(font2)
                        {
                            dc->SelectObject(font2);
                            font2 = null;
                        }
                    }
                }
    
                if((draw_item->itemState & ODS_COMBOBOXEDIT) != ODS_COMBOBOXEDIT)
                {
                    r.bottom += UnderLineGap; // for underline
                }
            }

            if((draw_item->itemState & ODS_FOCUS) == ODS_FOCUS)
            {
                dc->DrawFocusRect(&draw_item->rcItem);
            }

            if(font2)
            {
                dc->SelectObject(font2);
            }

            dc->RestoreDC(-1);

            AIComboBox3::DrawItem(draw_item);
        }
    }
}

void AIComboBoxFontFamily::MeasureItem(MEASUREITEMSTRUCT* measure_item)
{
    if(measure_item)
    {
        if(measure_item->CtlType == ODT_COMBOBOX)// avoid for this message ... && measure_item->itemID != -1)
        {
            TCHAR     sample[] = _T("mmm");
            CSize     sz;
            CWindowDC dc(CWnd::GetDesktopWindow());

            dc.SaveDC();

            if(HFont)
            {
                dc.SelectObject((HFONT)HFont);
            }
            else
            {
                dc.SelectObject((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
            }

            // here I used my private function ...
            ::GetTextExtentPoint32(dc, sample, sizeof(sample), &sz);
            measure_item->itemHeight = AIMax(WORD(sz.cy), WORD(GlyphHeight));
            measure_item->itemHeight += UnderLineGap; // for underline

            dc.RestoreDC(-1);
        }
    }
}

void AIComboBoxFontFamily::DeleteItem(DELETEITEMSTRUCT* delete_item)
{
    if(delete_item && delete_item->CtlType == ODT_COMBOBOX)
    {
        AIFontEntry* entry = (AIFontEntry*)delete_item->itemData;

        if(!(entry->GetStyle() & AIComboBox3Entry::FromMRU)) 
        {
            delete entry;

            DWORD count = DefWindowProc(CB_GETCOUNT, 0, 0);

            for(DWORD i = 0; i < count; i++)
            {
                if(delete_item->itemData == (DWORD)DefWindowProc(CB_GETITEMDATA, i, 0))
                {
                    DefWindowProc(CB_SETITEMDATA, i, 0);
                    break;
                }
            }

            delete_item->itemData = 0;
        }
    }
}

INT AIComboBoxFontFamily::CompareItem(COMPAREITEMSTRUCT* compare_item)
{
    if(compare_item && compare_item->CtlType == ODT_COMBOBOX)
    {
        AIFontEntry* entry1 = (AIFontEntry*)compare_item->itemData1;
        AIFontEntry* entry2 = (AIFontEntry*)compare_item->itemData2;

        if(entry1 && entry2)
        {
            if(entry1->GetFaceName() < entry2->GetFaceName())
            {
                return -1;
            }
            else if(entry1->GetFaceName() > entry2->GetFaceName())
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    return -1;
}

INT CALLBACK AIComboBoxFontFamily::EnumFontFamExProc(ENUMLOGFONTEX* elf, NEWTEXTMETRIC* ntm, INT font_type, LPARAM lParam)
{
    AIComboBoxFontFamily* ptr = (AIComboBoxFontFamily*)lParam;

    if(elf && ntm && ptr)
    {
        BYTE  pitch   = ntm->tmPitchAndFamily & 0x03;
        BYTE  family  = ntm->tmPitchAndFamily & 0xF0;
        BYTE  charset = elf->elfLogFont.lfCharSet;
        DWORD flags   = ptr->GetFlags();

        if(elf->elfLogFont.lfCharSet == MAC_CHARSET)
        {
            return 1;
        }

        if(::GetSystemMetrics(SM_DBCSENABLED) && elf->elfLogFont.lfFaceName[0] == '@')
        {
            return 1;
        }

        if((flags & CF_TTONLY) && !(font_type & TRUETYPE_FONTTYPE))
        {
            return 1;
        }

        if((flags & CF_FIXEDPITCHONLY) && !(pitch & TMPF_FIXED_PITCH))
        {
            return 1;
        }

        if((flags & CF_NOVECTORFONTS) && (family & TMPF_VECTOR))
        {
            return 1;
        }

        if((flags & CF_PRINTERFONTS) && !(font_type & PRINTER_FONTTYPE))
        {
            return 1;
        }

        if((flags & CF_SCALABLEONLY) && !((family & TMPF_VECTOR) || (family & TMPF_TRUETYPE)))
        {
            return 1;
        }

        if((flags & CF_SCREENFONTS) && !(font_type & SCREEN_FONTTYPE))
        {
            return 1;
        }

        if((flags & CF_SCRIPTSONLY) && charset != ANSI_CHARSET)
        {
            return 1;
        }

        if((flags & CF_NOSIMULATIONS) && (font_type & SIMULATED_FONTTYPE))
        {
            return 1;
        }

        if((flags & CF_WYSIWYG) && !(font_type & (TRUETYPE_FONTTYPE|DEVICE_FONTTYPE)))
        {
            return 1;
        }

        ptr->DefWindowProc(CB_ADDSTRING, 0, (LPARAM)(AIFontEntry*)new AIFontEntry(font_type, elf->elfLogFont.lfCharSet, elf->elfLogFont.lfPitchAndFamily, elf->elfLogFont.lfFaceName, (const TCHAR*)elf->elfScript));
    }
    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////
