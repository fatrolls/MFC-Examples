#include<stdio.h>//

#include"set.h"
#include<limits.h>//

typedef unsigned int SET;
#define SET_BITS        (sizeof(SET)*CHAR_BIT)
#define CHECKSET(i)        ((unsigned)(i)<SET_BITS)
#define EMPTYSET        ((SET)0)
#define ADDSINGLE(set,i)      ((set)|SINGLESET(i))
#define SINGLESET(i)    (((SET)1)<<(i))
#define INTERSECT(set1,set2)    ((set1)&(set2))
#define UNIONSET(set1,set2)        ((set1)|(set2))
#define SETDIFF(set1,set2)      ((set1)^(set2))
#define ELEMENT(i,set)          (SINGLESET((i))&(set)) 
#define FORALLELEMENTS(j,s)     for((j)=0; (j)<SET_BITS; ++(j)) if(ELEMENT((j),(s)))
#define FIRST_SET_OF_N_ELEMENTS(n)      (SET)((1<<(n))-1)

extern SET next_set_of_n_elements(SET x);//
extern void printset(SET z);//
extern void print_k_of_n(int k, int n);//

//using namespace std;
int cardinality(SET x)
{
    int count=0;
    while(x!=EMPTYSET){
        x^=(x&-x);
        ++count;
    }
    return count;    

}

SET next_set_of_n_elements(SET x)
{
    SET smallest, ripple, new_smallest, ones;
    if(x== EMPTYSET) return x;
    smallest = (x&-x);
    ripple = x+smallest;
    new_smallest = (ripple&-ripple);
    ones = ((new_smallest/smallest)>>1)-1;
    return (ripple|ones);
}

void printset(SET z)
{
    int first=1;
    int e;
    FORALLELEMENTS(e,z){
        if (first)printf("{");
        else printf(", ");
        printf("%d", e);
        first=0;    
    }
    if(first) printf("{");
    printf("}");
}

#define LINE_WIDTH 54
void print_k_of_n(int k, int n)
{
    int count=0;
    int printed_set_width=k*((n>10)?4:3)+3;
    int sets_per_line = LINE_WIDTH/printed_set_width;
    SET z=FIRST_SET_OF_N_ELEMENTS(k);
    printf("\nALL the size-%d subset of ", k);
    printset(FIRST_SET_OF_N_ELEMENTS(n));
    printf(":\n");
    do{
        printset(z);
        if ((++count)%sets_per_line)printf(" ");
        else printf("\n");
        z=next_set_of_n_elements(z);
    }while((z!=EMPTYSET)&&!ELEMENT(n, z));
    if ((count)%sets_per_line) printf("\n");
    printf("The total number of such subsets is %d.\n",count);
}

///
void testset(void)
{
	
    print_k_of_n(0,4);
    print_k_of_n(1,4);
    print_k_of_n(2,4);
    print_k_of_n(3,4);
    print_k_of_n(4,4);
    print_k_of_n(3,5);
    print_k_of_n(3,6);
	
}
