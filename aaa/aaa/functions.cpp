#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <cmath>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "functions.hpp"
using namespace std;

void unkwn()
{
   int i=10;
   i=i-- - --i * (i=-3) * i++ + ++i;
   printf("i=%d\n",i); //i=4;
}
void testatol()
{
   long l;
   char *str = "98765432";
   l = atol(str);
   printf("string = %s integer = %ld\n", str, l);

}

bool fun( int a[], int n )

{
   if( n==1 )
      return true;

   if( n==2 )
      return a[n-1] >= a[n-2];

   return fun( a,n-1) && ( a[n-1] >= a[n-2] );

} 
void foo(void)
{
   unsigned int a = 6;
   int b = -20;
   (a+b > 6) ? puts("> 6") : puts("<= 6");//>6
   puts("\n");
   int aa = 5, bb = 7, cc;
   cc = aa++ + bb; 
   cout<<aa<<","<<bb<<","<<cc<<endl;//6,7,12
   aa = 5;
   bb = 7;
   cc = aa++ + ++bb; 
   cout<<aa<<","<<bb<<","<<cc<<endl;//6,8,13
   aa = 5;
   bb = 7;
   cc = aa++ + bb++; 
   cout<<aa<<","<<bb<<","<<cc<<endl;//6,8,12
   aa = 5;
   bb = 7;
   cc = ++aa + bb++; 
   cout<<aa<<","<<bb<<","<<cc<<endl;//6,8,13
   aa = 5;
   bb = 7;
   cc = aa + (++bb); 
   cout<<aa<<","<<bb<<","<<cc<<endl;//5,8,13
   aa = 5;
   bb = 7;
   cc = ++aa + (++bb)++; 
   cout<<aa<<","<<bb<<","<<cc<<endl;//6,9,14
   aa = 5;
   bb = 7;
   cc = (++aa)++ + (++bb)++; 
   cout<<aa<<","<<bb<<","<<cc<<endl;//7,9,14
   

} 

void myswap( int* p1,int* p2 )
{
   int p;
   p = *p1;
   *p1 = *p2;
   *p2 = p;
}
char * mystrcpy( char *strDest, const char *strSrc )
{
   assert( (strDest != NULL) &&(strSrc != NULL) );
   char *address = strDest;
   while( (*strDest++ = * strSrc++) != '\0');
   return address;
}

int mystrlen( const char *str ) // 
{
   assert( str != NULL ); // 断言字符串地址非 0
   int len=0; // 注，一定要初始化。
   while( (*str++) != '\0' )
   {
      len++;
   }
   return len;
}

void getMemory(char **p, int num){
   *p = (char *)malloc(num);
}

void testgetmm(void){
   char *str = NULL;
   getMemory(&str, 100);
   strcpy(str, "hello");
   printf(str);//hello
   printf("\n");
}
void testgetmm2(void){
   char *str = (char *) malloc(100);
   strcpy(str, "hello");
   free(str);
   if(str != NULL){
      strcpy(str, "world");
      printf(str);//world

   }
   printf("\n");
}
void getMemory1( char *p )//error
{
   p = (char *) malloc( 100 );
}
char *getMemory2(void){
   char p[] = "hello world";
   return p;
}
void testgetmm3(void){
   char *str = NULL;
   str = getMemory2();
   printf(str);//hello world
   printf("\n");
}

// 写一个函数找出一个整数数组中，第二大的数 （microsoft）
const int MINNUMBER = -32767 ;
int find_sec_max( int data[] , int count)
{
   int maxnumber = data[0] ;
   int sec_max = MINNUMBER ;
   for ( int i = 1 ; i < count ; i++)
   {
      if ( data[i] > maxnumber )
      {
         sec_max = maxnumber ;
         maxnumber = data[i] ;
      }
      else
      {
         if ( data[i] > sec_max )
            sec_max = data[i] ;
      }
   }
   return sec_max ;
}


void numseq()
{
   double a=1;
   double b=a;
   long long i=0;
   for (; i<100000000000; ++i)
   {
      b=a+1.0/a;
      a=b;
   }
   cout<<b<<" : ";
   cout<<(std::sqrt(i*1.0))<<endl;

}
void comparechar()
{
   char str1[] = "abc";
   char str2[] = "abc";
   cout << boolalpha << ( str1==str2 ) << endl; // false

   const char str3[] = "abc";
   const char str4[] = "abc";
   cout << boolalpha << ( str3==str4 ) << endl; // false 

   const char* str5 = "abc";
   const char* str6 = "abc";
   cout << boolalpha << ( str5==str6 ) << endl; // true

}

void compareint()
{
   float a = 1.0f;
   cout << (int)a << endl;// 1
   cout << (int&)a << endl;// 1065353216
   cout << boolalpha << ( (int)a == (int&)a ) << endl; // false

   float b = 0.0f;
   cout << (int)b << endl;// 0
   cout << (int&)b << endl;// 0
   cout << boolalpha << ( (int)b == (int&)b ) << endl; // true
}

int func(int x)//将x转化为2进制，看含有的1的个数。
{
   int countx = 0;
   while(x)
   {
      countx ++;
      x = x&(x-1);
   }
   return countx;
}


int fn1()
{
   printf( "next.\n" );
   return 0;
}
int fn2()
{
   printf( "executed " );
   return 0;
}
int fn3()
{
   printf( "is " );
   return 0;
}
int fn4()
{
   printf( "This " );
   return 0;
}


int itoafun()
{
   int i;
   char buffer [33];
   printf ("Enter a number: ");
   scanf ("%d",&i);
   _itoa (i,buffer,10);//itoa
   printf ("decimal: %s\n",buffer);
   _itoa (i,buffer,16);
   printf ("hexadecimal: %s\n",buffer);
   _itoa (i,buffer,2);
   printf ("binary: %s\n",buffer);
   return 0;
}


void inputgenes()
{
   //int chln[]={7,8,5};
   //int perm1[]={ 1,2,-3,4,6,19,-8,-15, -13,-12,  5,10, 11,-9, 7, 16,-14, 17,-18, 20 };
   //int perm2[]={ 1,2,3 ,4,5, 6, 7,  8,   9, 10, 11,12, 13,14,15, 16, 17, 18, 19, 20 };
   int length;
   int genenum;
   int chromnum;

   cout<<"gene number=";
   cin>>genenum;
   assert(genenum>=4);
   int* genes=new int[genenum];
   //genes.reserve(genenum);
   cout<<"chromosome number=";
   cin>>chromnum;
   assert((chromnum<genenum)&&(chromnum>1));
   //if(chromnum>1){
   int * chromln =new int[chromnum];
   int j=0;
   cin.clear();
   cin.sync();
   for(int i=0; i<chromnum; ++i){

      cout<<"chromosome "<<i;//<<" length = "
      //cin>>chromln[i];
      cout<<" gene : ";
      int agene;
      int k=0;
      while(cin>>agene){
         genes[j]=agene;
         ++j;
         ++k;
         if(j==genenum)
            break;
      }  //genes.push_back(agene);
      chromln[i]=k;
      cin.clear();
      cin.sync();
      //cin.ignore( numeric_limits <streamsize>::max(), '\n');
   }

   //}

   copy (genes, genes+genenum,
      ostream_iterator<int>(cout,","));

   cout << endl;
   copy (chromln, chromln+chromnum,
      ostream_iterator<int>(cout,","));

   cout << endl;
   delete [] chromln;
   delete [] genes;
}

unsigned int binary_gcd(unsigned int x, unsigned int y)
{
   unsigned int temp;
   unsigned int cp2=0;//common power of two
   if (x==0) return y;
   if (y==0) return x;
   while(((x|y)&1) == 0){
      x>>=1;
      y>>=1;
      ++cp2;              
   }
   while((x&1) == 0)x>>=1;
   while(y){
      while((y&1) == 0)y>>=1;
      temp=y;
      if(x>y)y=x-y;
      else y=y-x;
      x=temp;
   }    
   return (x<<cp2);
}

void testgcd()
{
   unsigned int i=24;
   unsigned int j=48;
   unsigned int g=binary_gcd(i,j);
   printf("(%d, %d)=%d\n",i,j,g);    
}




int randnum()
{
   //time_t t;
   //tm* gt=gmtime(&t);
   int rn=0;
   std::ofstream fout("randnum.txt");
   if (!fout){    cerr<<"cannot output file"; std::exit(1); }    
   int bucket[10]={0,0,0,0,0,0,0,0,0,0};
   srand(time(0));
   for (int i=0; i<1000000; i++)    
   { 
      rn=int((double(rand())/RAND_MAX)*10);    
      bucket[rn]++;
      //fout<<rn;    
   }
   for (int j=0; j<10; j++)    {    cout<<bucket[j]<<endl;    }
   //for (int j=0; j<10; j++)    {    fout<<bucket[j]<<endl;    }
   cout<<(1l<<31);
}


void shellsort(register int v[], int n)
{
   register int gap, i, j, temp;
   gap=1;
   do(gap= 3*gap+1);while(gap<= n);
   for(gap/= 3; gap> 0; gap/= 3)
      for(i= gap; i< n; i++){
         temp= v[i];
         for(j= i-gap; (j>= 0)&&(v[j]> temp); j-= gap)
            v[j+gap]= v[j];
         v[j+gap]= temp;
      }    

}
void testshellsort()
{
   int i;
   int arr[13]={2,5,6,7,9,3,11,12,1,4,10,16,15};
   shellsort(arr, 13);
   for(i=0; i<13; i++)
      printf("arr[%d]=%d\n",i,arr[i]);    
}


void testunion()
{
   union
   {
      int i;
      char x[2];
   } aun;
   aun.x[0] = 10;
   aun.x[1] = 1;
   printf("%d\n",aun.i);//-1232862966

   union{                   /* 定义一个联合 */
      int i;
      struct{             /* 在联合中定义一个结构 */
         char first;
         char second;
      }half;
   }number;
   number.i=0x4241;         /* 联合成员赋值 */
   printf("%c%c\n", number.half.first, number.half.second);//AB
   number.half.first='a';   /* 联合中结构成员赋值 */
   number.half.second='b';
   printf("%x\n", number.i);//6261
   //getch(); 
}

bool IsSymmetry(const char * p)
{
   assert(p!=NULL);
   const char * q=p;      
   int len=0;
   while (*q++!='\0' )
   {
      len++;
   }       

   bool bSign=true ;
   q=p+len-1;
   if (0<len)
   {
      for (int i=0;i<len/2;i++)
      {
         if (*p++!=*q--){ bSign=false ;break ;};
      }
   }

   if (bSign==true )
   {
      printf("Yes!\n" );
   }
   else
   {
      printf("No!\n" );
   }
   return bSign;
} 



#define SPACE ' '
#define ENDL '\0'

void revwords()//??
{

   char* str = "Tom is cat"; // 字符串
   char* p1 = str+strlen(str)-1;
   char* p2 = p1; // 开始时， p1,p2 都指向字符串结尾处
   char t=0; // 临时变量，用来保存被临时替换为 ENDL 的字符

   while(str!=p1--)
   {
      if(SPACE!=*p1){
         for(p2=p1+1; SPACE!=*p1; p1--, t=*p2, *p2=ENDL);

         // p1+1 指向单词的第一个字母 ,p2 指向单词的结尾 , 此时输出这个单词
         printf("%s ",p1+1);
         *p2=t;
         p2=p1;
      }
   } 
   printf("\n");
}
void str_reverse(char* p1,char* p2){
   if(p1==p2)return;
   char ach=*p1;
   *p1=*p2;
   *p2=ach;
   //*p1 = (*p1)+(*p2);
   //*p2 = (*p1)-(*p2);
   //*p1 = (*p1)-(*p2);
   if(p1==p2-1)return;
   else str_reverse(++p1,--p2);
}

void str_word_reverse(char* str){
   char *q1=str, *q2=str, *t;

   while(*q1==SPACE)q1++;
   if(*q1==ENDL)return; //!
   else q2=q1+1;

   while( (*q2!=SPACE) && (*q2!=ENDL) )q2++;

   t=q2--;
   str_reverse(q1,q2);

   if(*t==ENDL)return;
   else str_word_reverse(t);
}

int teststrreverse( )
{
   char* s = "The quick brown fox jumps over the lazy dog";
   printf("%s\n",s);
   str_reverse(s,s+strlen(s)-1);
   printf("%s\n",s);
   str_word_reverse(s);
   printf("%s\n",s);

   return 0;
}


void reverse(char* p)
{
   // 这是这种方法的关键，使用 static 为的是能用 str_reverse 的思路，但是不好
   static char* x=0;
   if(x==0)x=p;
   char* q = x+strlen(p)-1;
   if(p==q)return;
   *q=(*p)^(*q);
   *p=(*p)^(*q);
   *q =(*p)^(*q);
   if(q==p+1)return;
   reverse(++p);
}

// 这种方法就直观多了，但是当字符串很长的时候就很低效
void reverse2(char* p)
{
   if(*(p+1)==ENDL)return;
   char* o=p+strlen(p)-1;
   char t=*o;
   for(;o!=p;o--)
      *o=*(o-1);
   *p=t;
   reverse2(p+1);
}

int testreverse( )
{
   char* s = "0123456789";
   reverse2(s);
   printf("%s\n",s);
   return 0;
} 

#define MYSWAP (a,b) (a)=(a)+(b);(b)=(a)-(b);(a)=(a)-(b);




void Order(vector<int>& data) //bubble sort
{
    int count = data.size() ;
    int tag = false ; // 设置是否需要继续冒泡的标志位
    for ( int i = 0 ; i < count ; i++)
    {
        for ( int j = 0 ; j < count - i - 1 ; j++)
        {
            if ( data[j] > data[j+1])
            {
                tag = true ;
                int temp = data[j] ;
                data[j] = data[j+1] ;
                data[j+1] = temp ;
            }
        }
        if ( !tag )
            break ;
    }
}

void insortout()
{
    vector<int>data;
    ifstream in("c://data.txt");
    if ( !in)
    {
        cout<<"file error!";
        exit(1);
    }
    int temp;
    while (!in.eof())
    {
        in>>temp;
        data.push_back(temp);
    }
    in.close(); //关闭输入文件流
    Order(data);
    ofstream out("c://result.txt");
    if ( !out)
    {
        cout<<"file error!";
        exit(1);
    }
    for (int i = 0 ; i < data.size() ; i++)
        out<<data[i]<<" ";
    out.close(); //关闭输出文件流
}

void iteratorpair()
{
	std::list<int> l(4);
	std::fill(l.begin(),l.end(), 10);    // fill up list using iterator pair technique.
	std::deque<int> s(4);//set
	std::fill(s.begin(),s.end(), 20);    // fill up set using iterator pair technique.
	
	std::vector<int> v1(l.begin(), l.end());  // create vector using iterator pair technique.
	std::vector<int> v2(s.begin(), s.end());  // create another vector.
	char buf[] = { 'A', 'B', 0, 'C', 0, 'D'};
	std::string str1 (buf); // only creates "AB"
	std::string str2 (buf, buf + sizeof (buf)); // Using iterator pair. Creates "AB_C_D"
	// buf is start of the range and buf + sizeof (buf) is the end of the range.
	
	std::cout<< str1.c_str() << " length = " << str1.length() << std::endl; // AB length = 2
	std::cout<< str2.c_str() << " length = " << str2.length() << std::endl; // AB_C_D length = 6
	
}
