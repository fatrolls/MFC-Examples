#if ! defined( CPP_TO_HTML_TRANSLATOR_CLASS_HEADER )

#define CPP_TO_HTML_TRANSLATOR_CLASS_HEADER

class CCPPToHTMLTranslator
{
   protected:

      CMapStringToString m_ClassMap;

      void m_StripDocumentation( CStringArray& html ) const;
      void m_TranslateCharacters( CStringArray& html ) const;

   public:

      CCPPToHTMLTranslator();
     ~CCPPToHTMLTranslator();

      void AddClass( const CString& class_name, const CString& filename );
      void Translate( const CStringArray& cpp_source, CStringArray& html ) const;
};

#endif // CPP_TO_HTML_TRANSLATOR_CLASS_HEADER