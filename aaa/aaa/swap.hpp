
#include <utility>
namespace Orange {
   class String 
   {
      char * str;
   public:
      void swap (String &s) // throw ()
      {
         std::swap (this->str, s.str);
      }
   };
}

namespace Orange { // namespace of String
   void swap (String & s1, String & s2) // throw ()
   {
      s1.swap (s2);
   }
}
namespace std {
   template <>
   void swap (Orange::String & s1, Orange::String & s2) // throw ()
   {
      s1.swap (s2);
   }
}
class UserDefined 
{
   Orange::String str;
public:
   void swap (UserDefined & u) // throw () 
   { 
      std::swap (str, u.str); 
   }
};
namespace std
{
   // Full specializations of the templates in std namespace can be added in std namespace.
   template <>
   void swap (UserDefined & u1, UserDefined & u2) // throw ()
   {
      u1.swap (u2);
   }
}
class Myclass
{
   UserDefined u;
   char * name;
public:
   void swap (Myclass & m) // throw ()
   {
      std::swap (u, m.u);       // cascading use of the idiom due to uniformity
      std::swap (name, m.name); // Ditto here
   }   
}
namespace std
{
   // Full specializations of the templates in std namespace can be added in std namespace.
   template <> 
   void swap (Myclass & m1, Myclass & m2) // throw ()
   {
      m1.swap (m2);
   }
}