 
#include <vector>
#include <fstream>
using std::vector;
using std::ofstream;

class NSquare{
    vector<vector<int>* > rsq;
    int m_n;
public:
    NSquare(int N):m_n(N){}
    void getNSquare( );
   
    void outputSquare( );
    ~NSquare();
private:
    void getOneSquare(vector<int>* asq,int n,int firsti,int firstj,int mini,int minj,int maxi ,int maxj);
    bool compare(const vector<int>* lh, int maxi, int maxj);
    bool translateCompare(const vector<int>*, int mini, int minj, int maxi, int maxj);
    bool rotateCompare(const vector<int>* lh, int mini, int minj, int maxi, int maxj);
    bool flipCompare(const vector<int>* lh, int mini, int minj, int maxi, int maxj);
};

void NSquare::getNSquare( )
{

    int num=2*m_n;
    vector<int>* aSquare=new vector<int >[2*m_n];
    for (int i=0;i< num; ++i)
    {
        for (int j=0; j<num; ++j)
        {
            aSquare[i].push_back(0);
        }
    }
    int mini=m_n-1;
    int minj=m_n-1;
    int maxi=m_n-1;
    int maxj=m_n-1;
    int curSquare=1;
    int firsti=m_n-1;
    int firstj=m_n-1;
    aSquare[firsti][firstj]=1;
    getOneSquare(aSquare,1,firsti,firstj,mini,minj,maxi,maxj);
 
}
void NSquare::getOneSquare(vector<int>* asq,int n,int firsti,int firstj,int mini,int minj,int maxi ,int maxj)
{
 
    const int num=2*m_n;
    vector<int>* aSquare=new vector<int >[2*m_n];
    for (int i=0;i< num; ++i)
    {
        for (int j=0; j<num; ++j)
        {
            aSquare[i].push_back(asq[i][j]);
        }
    }


    if (n<m_n)//recursive
    {
        if (firsti==0  )//1
        {
            if (firstj==0 )//2
            {
                if (firsti+1==num )//3
                {
                    if (firstj+1==num)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                    else if (aSquare[firsti][firstj+1]==2)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                }
                else
                if (aSquare[firsti+1][firstj]==2)//3
                {
                    if (firstj+1==num)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                    else if (aSquare[firsti][firstj+1]==2)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                }
            }
            else
            if ( aSquare[firsti][firstj-1]==2)//2
            {
                if (firsti+1==num )//3
                {
                    if (firstj+1==num)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                    else if (aSquare[firsti][firstj+1]==2)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                }
                else//3
                if (aSquare[firsti+1][firstj]==2)
                {
                    if (firstj+1==num)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                    else if (aSquare[firsti][firstj+1]==2)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                }
            }

        }
        else
        if (aSquare[firsti-1][firstj]==2 )//1
        {
            if (firstj==0 )//2
            {
                if (firsti+1==num )//3
                {
                    if (firstj+1==num)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                    else if (aSquare[firsti][firstj+1]==2)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                }
                else
                if (aSquare[firsti+1][firstj]==2)//3
                {
                    if (firstj+1==num)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                    else if (aSquare[firsti][firstj+1]==2)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                }
            }
            else
            if ( aSquare[firsti][firstj-1]==2)//2
            {
                if (firsti+1==num )//3
                {
                    if (firstj+1==num)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                    else if (aSquare[firsti][firstj+1]==2)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                }
                else//3
                if (aSquare[firsti+1][firstj]==2)
                {
                    if (firstj+1==num)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                    else if (aSquare[firsti][firstj+1]==2)//4
                    {
                        delete [] aSquare;
                        return;
                    }
                }
            }

        }
        
        if (firsti>0 && aSquare[firsti-1][firstj]==0)
        {
            aSquare[firsti-1][firstj]=2;

            getOneSquare(aSquare, n, firsti, firstj, mini, minj,  maxi ,  maxj);
            aSquare[firsti-1][firstj]=1;
            if (firsti-1<mini)
            {
                mini=firsti-1;
            }
            getOneSquare(aSquare, n+1, firsti, firstj, mini, minj,  maxi ,  maxj);
            getOneSquare(aSquare, n+1, --firsti, firstj, mini, minj,  maxi ,  maxj);
           


        }
        if (firstj>0 && aSquare[firsti][firstj-1]==0)
        {
            aSquare[firsti][firstj-1]=2;

            getOneSquare(aSquare, n, firsti, firstj, mini, minj,  maxi ,  maxj);
            aSquare[firsti][firstj-1]=1;
            if (firstj-1<minj)
            {
                minj=firstj-1;
            }

            getOneSquare(aSquare, n+1, firsti, firstj, mini, minj,  maxi ,  maxj);
            getOneSquare(aSquare, n+1, firsti, --firstj, mini, minj,  maxi ,  maxj);

        }

        if (firsti+1<num && aSquare[firsti+1][firstj]==0)
        {
            aSquare[firsti+1][firstj]=2;

            getOneSquare(aSquare, n, firsti, firstj, mini, minj,  maxi ,  maxj);
            aSquare[firsti+1][firstj]=1;
            if (firsti+1>maxi)
            {
                maxi=firsti+1;
            }
            getOneSquare(aSquare, n+1, firsti, firstj, mini, minj,  maxi ,  maxj);
            getOneSquare(aSquare, n+1, ++firsti,firstj, mini, minj,  maxi ,  maxj);

        }
        if (firstj+1<num && aSquare[firsti][firstj+1]==0)
        {
            aSquare[firsti][firstj+1]=2;

            getOneSquare(aSquare, n, firsti, firstj, mini, minj,  maxi ,  maxj);
            aSquare[firsti][firstj+1]=1;
            if (firstj+1>maxj)
            {
                maxj=firstj+1;
            }
            getOneSquare(aSquare, n+1, firsti, firstj, mini, minj,  maxi ,  maxj);
            getOneSquare(aSquare, n+1, firsti, ++firstj, mini, minj,  maxi ,  maxj);

        }
       

    }//recursive
    for (int i=0; i < num; ++i)
    {
        for (int j=0; j < num; ++j)
        {
            if (aSquare[i][j]==2)
            {
                aSquare[i][j]=0;
            }

        }
    }
    if (translateCompare(aSquare,mini,minj,maxi,maxj)||
        rotateCompare(aSquare,mini,minj,maxi,maxj)||
        flipCompare(aSquare,mini,minj,maxi,maxj))
    {  
        delete [] aSquare;
        return;
    }
    rsq.push_back(aSquare);


}


bool NSquare::compare(const vector<int>* lh,int maxi, int maxj)
{  
    const int num=2*m_n;
    for (int ns=0; ns<rsq.size(); ++ns)
    {
        for (int i=0; i<maxi; ++i)
        {
            for (int j=0; j<maxj; ++j)
            {
                if (lh[i][j]!=rsq[ns][i][j])
                {
                    return false;
                }
            }
        }
    }
    return true;

}

bool NSquare::translateCompare(const vector<int>* insq,int mini, int minj, int maxi, int maxj)
{
    const int num=2*m_n;
    vector<int>* tempSquare=new vector<int >[2*m_n];
    for (int i=0;i< num; ++i)
    {
        for (int j=0; j<num; ++j)
        {
            tempSquare[i].push_back(0);
        }
    }
   int lengthi=maxi-mini+1;
   int lengthj=maxj-minj+1;
    for (int i=0;i< lengthi; ++i)
    {
        for (int j=0; j<lengthj; ++j)
        {
            tempSquare[i][j]=insq[i+mini][j+minj];
        }
    }
    if (compare(tempSquare,lengthi,lengthj))
    {
        delete [] tempSquare;
        return true;
    }

    delete [] tempSquare;
    return  false;

}

bool NSquare::rotateCompare(const vector<int>* lh, int mini, int minj, int maxi, int maxj)
{
    //bool reslt;
    const int num=2*m_n;
    vector<int>* tempSquare=new vector<int >[2*m_n];
    for (int i=0;i< num; ++i)
    {
        for (int j=0; j<num; ++j)
        {
            tempSquare[i].push_back(0);
        }
    }
   int lengthi=maxi-mini+1;
   int lengthj=maxj-minj+1;
    //90
    for (int i=0;i<lengthj; ++i)
    {
        for (int j=0; j<lengthi; ++j)
        {
            tempSquare[i][j]=lh[num-1-j+minj][i+num-maxi-1];
        }
    }

    if (compare(tempSquare,lengthj,lengthi))
    {
        delete [] tempSquare;
        return true;
    }
    ///180
    for (int i=0;i< lengthi; ++i)
    {
        for (int j=0; j<lengthj; ++j)
        {
            tempSquare[i][j]=lh[num-i+num-maxi-2][num-j+num-maxj-2];
        }
    }
    if (compare(tempSquare,lengthi,lengthj))
    {
        delete [] tempSquare;
        return true;
    }

    //270
    for (int i=0;i< lengthj; ++i)
    {
        for (int j=0; j<lengthi; ++j)
        {
            tempSquare[i][j]=lh[j+num-maxj-1][num-1-i+mini];
        }
    }

    if (compare(tempSquare,lengthj,lengthi))
    {
        delete [] tempSquare;
        return true;
    }


    delete [] tempSquare;
    return false;
                                         
}
bool NSquare::flipCompare(const vector<int>* lh, int mini, int minj, int maxi, int maxj)
{
    const int num=2*m_n;
    vector<int>* tempSquare=new vector<int >[2*m_n];
    for (int i=0;i< num; ++i)
    {
        for (int j=0; j<num; ++j)
        {
            tempSquare[i].push_back(0);
        }
    }
    int lengthi=maxi-mini+1;
    int lengthj=maxj-minj+1;
    //up-down
    for (int i=0;i< lengthi; ++i)
    {
        for (int j=0; j<lengthj; ++j)
        {
            tempSquare[i][j]=lh[num-1-i+mini][j+num-maxj-1];
        }
    }

    if (compare(tempSquare,lengthi,lengthj))
    {
        delete [] tempSquare;
        return true;
    }
    ///left-right
    for (int i=0;i< lengthi; ++i)
    {
        for (int j=0; j<lengthj; ++j)
        {
            tempSquare[i][j]=lh[i+num-maxi-1][num-1-j+minj];
        }
    }
    if (compare(tempSquare,lengthi,lengthj))
    {
        delete [] tempSquare;
        return true;
    }

    //leftdown-rightup
    for (int i=0;i< lengthj; ++i)
    {
        for (int j=0; j<lengthi; ++j)
        {
            tempSquare[i][j]=lh[j+minj][i+mini];
        }
    }

    if (compare(tempSquare,lengthj,lengthi))
    {
        delete [] tempSquare;
        return true;
    }

    //leftup- rightdoun
    for (int i=0;i< lengthj; ++i)
    {
        for (int j=0; j<lengthi; ++j)
        {
            tempSquare[i][j]=lh[num-1-j+num-maxj-1][num-1-i+num-maxi-1];
        }
    }

    if (compare(tempSquare,lengthj,lengthi))
    {
        delete [] tempSquare;
        return true;
    }
    delete [] tempSquare;
    return false;

}
void NSquare::outputSquare( )
{
    const int num=2*m_n;
    ofstream ofs("a.txt");
    for(int i=0; i<rsq.size(); ++i)
    {
        ofs<<(i+1)<<":"<<std::endl;
        for (int j=0; j<num; ++j)
        {
            for (int k=0; k<num; ++k)
            {
                ofs<<rsq[i][j][k];

            }
            ofs<<std::endl;
        }
        ofs<<std::endl;
       
    }
}
NSquare::~NSquare()
{
    while(!rsq.empty()){
        vector<int >* tmp=rsq.back();
        delete [] tmp;
        rsq.pop_back();
    }
   
}
int testNSquare(void )
{
    NSquare nsq(5);
    nsq.getNSquare();
    nsq.outputSquare();
   return 0;
}
 