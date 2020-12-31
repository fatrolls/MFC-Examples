#define DB_INTEGER 1 
#define DB_STRING 2 
#define DB_CURRENCY 3 
#define COLNUM 100
typedef long int  db_integer; 
typedef char   db_string[255]; 
typedef struct { 
    int integral_part; 
    unsigned char fractionary_part; 
} db_currency; 
typedef struct { 
    int column_type[COLNUM]; 
    unsigned char aa; 
} db_cursor;
// Example 4: Defining DbTraits 
// 
// Most general case not implemented 
template <typename T> struct DbTraits; 
// Specialization for int 
template <> 
struct DbTraits<int> 
{ 
    enum { TypeId = DB_INTEGER }; 
    typedef db_integer DbNativeType; 
    static void Convert(DbNativeType from, int& to) 
    { 
        to = static_cast<int>(from); 
    } 
}; 
// Specialization for double 
template <> 
struct DbTraits<double> 
{ 
    enum { TypeId = DB_CURRENCY }; 
    typedef db_currency DbNativeType; 
    static void Convert(const DbNativeType& from, double& to) 
    { 
        to = from.integral_part + from.fractionary_part / 100.; 
    } 
}; 

// Example 5: A generic, extensible FetchField using DbTraits 
// 
template <class T> 
void FetchField(db_cursor& cr, unsigned int col, T& val) 
{ 
    // Define the traits type 
    typedef DbTraits<T> Traits; 
    if (cr.column_type[col] != Traits::TypeId) 
        throw std::runtime_error("Column type mismatch"); 
    if (!db_access_column(&cr, col)) 
        throw std::runtime_error("Cannot transfer data"); 
    typename Traits::DbNativeType temp; 
    memcpy(&temp, cr.column_data[col], sizeof(temp)); 
    Traits::Convert(temp, val); 
    db_release_column(&cr, col); 
} 
bool db_access_column(db_cursor&cr, unsigned int  col)
{
    return true;
}
void db_release_column(db_cursor&cr, unsigned int  col)
{
}
void testDbTraits()
{
    //cout<<''<<endl;
}
