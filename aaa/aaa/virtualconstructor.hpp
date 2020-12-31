class Employee 
{
public:
   virtual ~Employee () {}                 // Native support for polymorphic destruction.
   virtual Employee * create () const = 0; // Virtual constructor (creation) 
   virtual Employee * clone () const = 0;  // Virtual constructor (copying) 
};
class Manager : public Employee     // "is-a" relationship
{
public:
   Manager ();                     // Default constructor
   Manager (Manager const &);      // Copy constructor
   ~Manager () {}                  // Destructor
   Manager * create () const       // Virtual constructor (creation) 
   {
      return new Manager();
   }
   Manager * clone () const        // Virtual constructor (copying) 
   {
      return new Manager (*this);
   }
};
class Programmer : public Employee { /* Very similar to the Manager class */ };
inline Employee * duplicate (Employee const & e)
{
   return e.clone();  // Using virtual constructor idiom.
}
////////////////////////////////
#include <memory>

class Employee2
{
public:
   typedef std::tr1::shared_ptr<Employee2> Ptr;
   virtual ~Employee2 () {}                    // Native support for polymorphic destruction.
   virtual Ptr create () const = 0; // Virtual constructor (creation)
   virtual Ptr clone () const = 0;  // Virtual constructor (copying)
};
class Manager2 : public Employee2     // "is-a" relationship
{
public:
   Manager2 () {}                     // Default constructor
   Manager2 (Manager2 const &) {}      // Copy constructor
   ~Manager2 () {}
   Ptr create () const       // Virtual constructor (creation)
   {
      return Ptr(new Manager2());
   }
   Ptr clone () const        // Virtual constructor (copying)
   {
      return Ptr(new Manager2 (*this));
   }
};