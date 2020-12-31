#include "mystr.hpp"

String3 stringcat(const String3& lstr, const String3& rstr){
    String3 reslt;
    reslt.length=lstr.length+rstr.length;
    reslt.a=new char[reslt.length];
    int i=0;
    for (;i<lstr.length;i++)
    {
        reslt.a[i]=lstr.a[i];
    }
    for ( int j=0;j<rstr.length;j++)
    {

        reslt.a[i]=rstr.a[j];
        ++i;
    }
    return reslt;
}
ostream& operator <<(ostream& os, const String3& lstr){
    for (int i=0;i<lstr.length;i++)
    {
        os<<lstr.a[i];
    }
    os<<endl;
    return os;
}
int testmystr(){
    String3 str1("I am");
    cout<<str1;
    String3 str2(str1);
    cout<<str2;
    //char *p1,*p2;
    //p1=str1.my_string();
    //p2=str2.my_string();
    //int ln=str1.getLength()+str2.getLength();
    //char *result_str=new char[ln];
    //strcat(result_str,,p1);
    //strcat(result_str,p2);
    
    String3 str3=stringcat(str1,str2);

    cout<<str3;
    //cout<<str2.my_string<<endl;
    //delete [] result_str;
    return 0;
}
int teststrxyz(){ 
    StringX str1("I am",4);
    cout<<str1.my_string()<<endl;
    StringX str2(str1);
    cout<<str2.my_string()<<endl;
    int ln=str1.getLength()+str2.getLength()+1;
    char *res=new char[ln];
    res[0]=0;
    strcat(res,str1.my_string());
    strcat(res,str2.my_string());
    res[ln-1]=0;
    cout<<res<<endl;
    delete [] res;
    str1.printmem();
    StringY str3;
    str3.printmem();
    StringZ str4;
    str4.printmem();
    return 0;
}
