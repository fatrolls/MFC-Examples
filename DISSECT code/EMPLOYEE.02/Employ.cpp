
#include <string.h>

//---------------------------------------
class CEmployee
{
private:
char m_name[30];

public:
  CEmployee();
  CEmployee(const char* nm) { strcpy(m_name, nm); }
};
//---------------------------------------
class CWage : public CEmployee
{
private :
  float m_wage;
  float m_hours;

public :
  CWage(const char* nm)  : CEmployee(nm) { m_wage = 250.0; m_hours = 40.0; }
  void setWage(float wg)                 { m_wage = wg; }
  void setHours(float hrs)               { m_hours = hrs; }
  float computePay();
};
//---------------------------------------
class CSales : public CWage
{
private :
  float m_comm;
  float m_sale;

public :
  CSales(const char* nm) : CWage(nm)  { m_comm = 500; m_sale = 0.0; }
  void setCommission(float comm)      { m_comm = comm; }
  void setSales(float sale)           { m_sale = sale; }
  float computePay();
};
//---------------------------------------
class CManager : public CEmployee
{
private :
  float m_salary;
public :
  CManager(const char* nm) : CEmployee(nm)  { m_salary = 15000.0; }
  void setSalary(float salary)              { m_salary = salary; }
  float computePay();
};
//---------------------------------------
void main()
{
CManager aManager("³¯¬üÀR");
CSales   aSales("«J«T³Ç");
CWage    aWager("´¿»Ê·½");

}
