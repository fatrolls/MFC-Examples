class Body{
public:
   void foo()const{}
};

class Handle // Completely pointer like semantics
{
public:
   void set (Body *b) { body_ = b; }
   Body * operator -> () const throw()
   {
      return body_;
   }
   Body & operator * () const throw ()
   {
      return *body_;
   }
private:
   mutable Body *body_;
};

void sp1 (void)
{
   Handle h;
   h.set(new Body());
   h->foo();    // A way of invoking Body::foo()
   (*h).foo();  // Another way of invoking Body::foo()
}
//====================================================
class Handle2 // Less pointer like semantics
{
public:
   void set (Body *b)const { body_ = b; }
   Body * operator -> () throw()
   {
      return body_;
   }
   Body const * operator -> () const throw()
   {
      return body_;
   }
   operator const Body & () const // type conversion
   {
      return *body_;
   }
   operator Body & ()  // type conversion
   {
      return *body_;
   }
   // No operator *()
private:
   mutable Body *body_;
};

void sp2 (void)
{
   Handle2 const h;
   h.set(new Body());
   h->foo();    // compiles only if Body::foo() is a const function.
}
//===================================
namespace H {
   class Body{
   public:
      void foo()const{}
   };
   class Handle {
      friend Body const & get (Handle const &h);
      friend Body & get (Handle &h);
   public:

      void set (Body *b)const { body_ = b; }
      Body * operator -> () throw()
      {
         return body_;
      }
      Body const * operator -> () const throw()
      {
         return body_;
      }
      operator const Body & () const // type conversion
      {
         return *body_;
      }
      operator Body & ()  // type conversion
      {
         return *body_;
      }
      // No operator *()
   private:
      mutable Body *body_;
   }; // As per above.
   //Non-member get 
   Body const & get (Handle const &h)
   {
      return *h.body_;
   }
   Body & get (Handle &h)
   {
      return *h.body_;
   }
} // end namespace H.

void sp3 (void)
{
   H::Handle const h;
   h.set(new H::Body());
   get(h).foo(); // compiles only if Body::foo() is a const function.
}