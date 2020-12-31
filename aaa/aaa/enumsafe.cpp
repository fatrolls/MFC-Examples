template<typename def, typename inner = typename def::type>
class safe_enum : public def
{
   typedef typename def::type type;
   inner val;

public:

   safe_enum(type v) : val(v) {}
   inner underlying() const { return val; }

   bool operator == (const safe_enum & s) const { return this->val == s.val; }
   bool operator != (const safe_enum & s) const { return this->val != s.val; }
   bool operator <  (const safe_enum & s) const { return this->val <  s.val; }
   bool operator <= (const safe_enum & s) const { return this->val <= s.val; }
   bool operator >  (const safe_enum & s) const { return this->val >  s.val; }
   bool operator >= (const safe_enum & s) const { return this->val >= s.val; }
};

struct color_def {
   enum type { red, green, blue };
};
typedef safe_enum<color_def> color;

struct shape_def {
   enum type { circle, square, triangle };
};
typedef safe_enum<shape_def, unsigned char> shape; // unsigned char representation

void safeenum(void)
{
   color c = color::red;
#if 0
   bool flag = (c >= shape::triangle); // Compiler error.
#endif
}