struct ExceptionBase 
{ 
   virtual void raise() { throw *this; }
   virtual ~ExceptionBase() {} 
};
struct ExceptionDerived : ExceptionBase 
{ 
   virtual void raise() { throw *this; }
};

void fooexc(ExceptionBase& e)
{
   e.raise(); // Uses dynamic type of e while raising an exception.
}
void except (void)
{
   ExceptionDerived e;
   try {
      fooexc(e);
   }
   catch (ExceptionDerived& e) {
      // Exception raised in foo now matches this catch.
   }
   catch (...) {
      // not here anymore!
   }

   try {
      fooexc(e); // throws an instance of ExceptionDerived as before.
   }
   catch (ExceptionBase& e) // Note the base class. Exception is caught polymorphically.
   {
      // Handle the exception. May modify the original exception object.
      // Use only one of the following two.
      throw;      // Option 1:  Original derived exception is thrown.
      e.raise();  // Option 2:  A copy of the original derived exception object is thrown.
   }
}