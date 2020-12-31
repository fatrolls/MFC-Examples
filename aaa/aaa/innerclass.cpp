class Base1 /// Provided by Moon
{
public:
   virtual int open (int) = 0;
   /* virtual */ ~Base1() {}  // No polymorphic deletion allowed
};

class Base2 /// Provided by Jupitor
{
public:
   virtual int open (int) = 0;
   /* virtual */ ~Base2() {}  // No polymorphic deletion allowed
};

class Derived // Note no inheritance
{
   class Base1_Impl;
   friend class Base1_Impl;
   class Base1_Impl: public Base1 // Note public inheritance
   {
   public:
      Base1_Impl (Derived * p) : parent_ (p) {}
      virtual int open (int) 
      {
         return parent_->base1_open ();
      }
   private:
      Derived * parent_;
   } base1_obj;   // Note member object here.

   class Base2_Impl;
   friend class Base2_Impl;
   class Base2_Impl: public Base2 // Note public inheritance
   {
   public:
      Base2_Impl (Derived * p) : parent_ (p) {}
      virtual int open (int) 
      {
         return parent_->base2_open ();
      }
   private:
      Derived * parent_;
   } base2_obj; // Note member object here

   int base1_open () {return 1;}
   int base2_open () {return 2;}

public:

   Derived () : base1_obj (this), base2_obj(this) {}

   operator Base1 & () { return base1_obj; }
   operator Base2 & () { return base2_obj; }
};

int base1_open (Base1 & b1)
{
   return b1.open (1);
}

int base2_open (Base2 & b2)
{
   return b2.open (2);
}

void innerclass (void)
{
   Derived d;
   base1_open (d);  // Like upcasting in inheritance.
   base2_open (d);  // Like upcasting in inheritance.
}