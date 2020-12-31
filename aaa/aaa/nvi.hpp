#include <iostream>
#include <cassert>
#include <set>
class ReaderWriterLock{ 
public:
	void acquire()const{;}
	void release()const{;}
};
class SomeComplexDataType{
public:
   bool check_invariants(); 
};
class BaseNVI {
private:
   ReaderWriterLock lock_;
   SomeComplexDataType data_;
public:
   void read_from( std::istream & i)  { // Note non-virtual
      lock_.acquire();
      assert(data_.check_invariants() == true); // must be true

      read_from_impl(i);

      assert(data_.check_invariants() == true); // must be true
      lock_.release();
   }
   void write_to( std::ostream & o) const { // Note non-virtual
      lock_.acquire();
      write_to_impl(o);
      lock_.release();
   }
   virtual ~BaseNVI() {}  // Virtual because BaseNVI is a polymorphic base class.
private:
   virtual void read_from_impl( std::istream & ) = 0;
   virtual void write_to_impl( std::ostream & ) const = 0;
};
class XMLReaderWriter : public BaseNVI {
private:
   virtual void read_from_impl (std::istream &) {
      // Read XML.
   }
   virtual void write_to_impl (std::ostream &) const {
      // Write XML.
   }
};
class TextReaderWriter : public BaseNVI {
private:
   virtual void read_from_impl (std::istream &) {}
   virtual void write_to_impl (std::ostream &) const {}
};

//Fragile Base Class (FBC) 
class Set {
   std::set<int> s_;
public:
   void add (int i) {
      s_.insert (i);
      add_impl (i); // Note virtual call.
   }
   void addAll (int * begin, int * end) {
      s_.insert (begin, end);   //  --------- (1)
      addAll_impl (begin, end); // Note virtual call.
   }
private:
   virtual void add_impl (int i) = 0;
   virtual void addAll_impl (int * begin, int * end) = 0;
};
class CountingSet : public Set {
private:
   int count_;
   virtual void add_impl (int i) {
      count_++;
   }
   virtual void addAll_impl (int * begin, int * end) {
      count_ += std::distance(begin,end);
   }
};


