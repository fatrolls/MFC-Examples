#include <iostream>

using namespace std;

struct BaseConstructor { BaseConstructor(int=0) {} };

class RealNumberAH;
class ComplexNumberAH;
class NumberAH;

class NumberAH
{
   friend class RealNumberAH;
   friend class ComplexNumberAH;

public:
   NumberAH ();
   NumberAH & operator = (const NumberAH &n);
   NumberAH (const NumberAH &n);
   virtual ~NumberAH();

   virtual NumberAH operator + (NumberAH const &n) const;
   void swap (NumberAH &n) throw ();

   static NumberAH makeReal (double r);
   static NumberAH makeComplex (double rpart, double ipart);

protected:
   NumberAH (BaseConstructor);

private:
   void redefine (NumberAH *n);
   virtual NumberAH complexAdd (NumberAH const &n) const;
   virtual NumberAH realAdd (NumberAH const &n) const;

   NumberAH *rep;
   short referenceCount;
};

class ComplexNumberAH : public NumberAH
{
   friend class RealNumberAH;
   friend class NumberAH;

   ComplexNumberAH (double d, double e);
   ComplexNumberAH (const ComplexNumberAH &c);
   virtual ~ComplexNumberAH ();

   virtual NumberAH operator + (NumberAH const &n) const;
   virtual NumberAH realAdd (NumberAH const &n) const;
   virtual NumberAH complexAdd (NumberAH const &n) const;

   double rpart, ipart;
};

class RealNumberAH : public NumberAH
{
   friend class ComplexNumberAH;
   friend class NumberAH;

   RealNumberAH (double r);
   RealNumberAH (const RealNumberAH &r);
   virtual ~RealNumberAH ();

   virtual NumberAH operator + (NumberAH const &n) const;
   virtual NumberAH realAdd (NumberAH const &n) const;
   virtual NumberAH complexAdd (NumberAH const &n) const;

   double val;
};

/// Used only by the letters.
NumberAH::NumberAH (BaseConstructor)
   : rep (0),
   referenceCount (1)
{}

/// Used by user and static factory functions.
NumberAH::NumberAH () 
   : rep (0),
   referenceCount (0)
{}

/// Used by user and static factory functions.
NumberAH::NumberAH (const NumberAH &n)
   : rep (n.rep),
   referenceCount (0)
{
   cout << "Constructing a NumberAH using NumberAH::NumberAH\n";
   if (n.rep)
      n.rep->referenceCount++;
}

NumberAH NumberAH::makeReal (double r)
{
   NumberAH n;
   n.redefine (new RealNumberAH (r));
   return n;
}

NumberAH NumberAH::makeComplex (double rpart, double ipart)
{
   NumberAH n;
   n.redefine (new ComplexNumberAH (rpart, ipart));
   return n;
}

NumberAH::~NumberAH()
{
   if (rep && --rep->referenceCount == 0)
      delete rep;
}

NumberAH & NumberAH::operator = (const NumberAH &n)
{
   cout << "Assigning a NumberAH using NumberAH::operator=\n";
   NumberAH temp (n);
   this->swap (temp);
   return *this;
}

void NumberAH::swap (NumberAH &n) throw ()
{
   std::swap (this->rep, n.rep);
}

NumberAH NumberAH::operator + (NumberAH const &n) const
{
   return rep->operator + (n);
}

NumberAH NumberAH::complexAdd (NumberAH const &n) const 
{
   return rep->complexAdd (n);
}

NumberAH NumberAH::realAdd (NumberAH const &n) const
{
   return rep->realAdd (n);
}

void NumberAH::redefine (NumberAH *n)
{
   if (rep && --rep->referenceCount == 0)
      delete rep;
   rep = n;
}

ComplexNumberAH::ComplexNumberAH (double d, double e)
   : NumberAH (BaseConstructor()),
   rpart (d),
   ipart (e)
{
   cout << "Constructing a ComplexNumberAH\n";
}

ComplexNumberAH::ComplexNumberAH (const ComplexNumberAH &c)
   : NumberAH (BaseConstructor()),
   rpart (c.rpart),
   ipart (c.ipart)
{
   cout << "Constructing a ComplexNumberAH using ComplexNumberAH::ComplexNumberAH\n";
}

ComplexNumberAH::~ComplexNumberAH()
{
   cout << "Inside ComplexNumberAH::~ComplexNumberAH()\n";
}

NumberAH ComplexNumberAH::operator + (NumberAH const &n) const
{ 
   return n.complexAdd (*this); 
}

NumberAH ComplexNumberAH::realAdd (NumberAH const &n) const
{
   cout << "ComplexNumberAH::realAdd\n";
   RealNumberAH const *rn = dynamic_cast <RealNumberAH const *> (&n);
   return NumberAH::makeComplex (this->rpart + rn->val, 
      this->ipart);
}

NumberAH ComplexNumberAH::complexAdd (NumberAH const &n) const
{
   cout << "ComplexNumberAH::complexAdd\n";
   ComplexNumberAH const *cn = dynamic_cast <ComplexNumberAH const *> (&n);
   return NumberAH::makeComplex (this->rpart + cn->rpart, 
      this->ipart + cn->ipart);
}

RealNumberAH::RealNumberAH (double r)
   : NumberAH (BaseConstructor()),
   val (r)
{
   cout << "Constructing a RealNumberAH\n";
}

RealNumberAH::RealNumberAH (const RealNumberAH &r)
   : NumberAH (BaseConstructor()),
   val (r.val)
{
   cout << "Constructing a RealNumberAH using RealNumberAH::RealNumberAH\n";
}

RealNumberAH::~RealNumberAH()
{
   cout << "Inside RealNumberAH::~RealNumberAH()\n";
}

NumberAH RealNumberAH::operator + (NumberAH const &n) const
{ 
   return n.realAdd (*this); 
}

NumberAH RealNumberAH::realAdd (NumberAH const &n) const
{
   cout << "RealNumberAH::realAdd\n";
   RealNumberAH const *rn = dynamic_cast <RealNumberAH const *> (&n);
   return NumberAH::makeReal (this->val + rn->val);
}

NumberAH RealNumberAH::complexAdd (NumberAH const &n) const
{
   cout << "RealNumberAH::complexAdd\n";
   ComplexNumberAH const *cn = dynamic_cast <ComplexNumberAH const *> (&n);
   return NumberAH::makeComplex (this->val + cn->rpart, cn->ipart);
}
namespace std
{
   template <>
   void swap (NumberAH & n1, NumberAH & n2)
   {
      n1.swap (n2);
   }
}
int algebraicHierarchy(void)
{
   NumberAH n1 = NumberAH::makeComplex (1, 2);
   NumberAH n2 = NumberAH::makeReal (10);
   NumberAH n3 = n1 + n2;
   cout << "Finished\n";

   return 0;
}