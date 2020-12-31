#include <iostream>
#include <vector>

struct Var {
   double operator () (double v) { return v; }
};

struct Constant {
   double c;
   Constant (double d) : c (d) {}
   double operator () (double) { return c; }
};

template < class L, class H, class OP >
struct DBinaryExpression {
   L l_;
   H h_;
   DBinaryExpression (L l, H h) : l_ (l), h_ (h) {}
   double operator () (double d) { return OP::apply (l_ (d), h_(d)); }
};

struct Add {
   static double apply (double l, double h) { return l + h; }
};

template < class E >
struct DExpression {
   E expr_;
   DExpression (E e) : expr_ (e) {}
   double operator() (double d) { return expr_(d);  }
};

template < class Itr, class Func >
void evaluate (Itr begin, Itr end, Func func) 
{
   for (Itr i = begin; i != end; ++i)
      std::cout << func (*i) << std::endl;
}
template< class A, class B >
DExpression<DBinaryExpression<DExpression<A>, DExpression<B>, Add> >
   operator + (DExpression<A> a, DExpression<B> b)
{
   typedef DBinaryExpression <DExpression<A>, DExpression<B>, Add> ExprT;
   return DExpression<ExprT>(ExprT(a,b));
}
int expresstemplate (void)
{
   typedef DExpression <Var> Variable;
   typedef DExpression <Constant> Literal;
   typedef DBinaryExpression <Variable , Literal, Add> VarLitAdder;
   typedef DExpression <VarLitAdder> MyAdder;

   Variable x ((Var()));
   Literal l (Constant (50.00));
   VarLitAdder vl_adder(x, l);
   MyAdder expr (vl_adder);

   std::vector <double> a;
   a.push_back (10);
   a.push_back (20);

   // It is (50.00 + x) but does not look like it.
   evaluate (a.begin(), a.end(), expr);
   evaluate (a.begin(), a.end(), x + l + x); 
   /// It is (2*x + 50.00), which does look like a mathematical expression.


   return 0;
}