#include<bits/stdc++.h>
using namespace std;
stack<int> l;
int a[9][9]={0};
typedef long long ll;
vector<int> r;
vector<int> c;
map<int,int> mprcount;
map<int,int> mpccount;
set<pair<int,int>,greater<pair<int,int>>> srorder;
set<pair<int,int>,greater<pair<int,int>>> scorder;
void order()
{
    for(auto it=mprcount.begin();it!=mprcount.end();it++)
    {
        srorder.insert({it->second,it->first});
    }
    for(auto it=mpccount.begin();it!=mpccount.end();it++)
    {
        scorder.insert({it->second,it->first});
    }
    for(auto it=srorder.begin();it!=srorder.end();it++)
    {
        r.push_back(it->second);
    }
     for(auto it=scorder.begin();it!=scorder.end();it++)
    {
        c.push_back(it->second);
    }
}
bool check(int i,int j,int val)
{
    //check row
    for(int k=0;k<9;k++) if(a[i][k]==val) return false;
    //check column
    for(int k=0;k<9;k++) if(a[k][j]==val) return false;
    // check section
    int i1,j1;
    i1=i/3;
    j1=j/3;
    for(int l=3*i1;l<3*i1+3;l++)
    {
        for(int m=3*j1;m<3*j1+3;m++)
        {
                if(a[l][m]==val) return false;
        }
    }
    return true;
}
int gen_val(int i,int j)
{
    int val=a[i][j]+1;
    while(!check(i,j,val))
    {
        val++;
    }
    if(val<10) return val;
    else return -1;
}
int gen_pair()
{
    for(auto i:r)
    {
        for(auto j:c)
        {
            if(a[i][j]==0) 
            {
                return i*10+j;
            }
        }
    }
    return -1;
}
void fill()
{
   for(int i=0;i<9;i++)
   {
        int cntr=0;
       for(int j=0;j<9;j++)
       {
          cin>>a[i][j];
          if(a[i][j]>0) cntr++;
       }
       mprcount[i]=cntr;
      
   }
   for(int j=0;j<9;j++)
   {
    int cntc=0;
    for(int i=0;i<9;i++)
    {
        if(a[i][j]>0) cntc++;
    }
    mpccount[j]=cntc;
   }
}
void print_mat()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cout<<a[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}
void reg(int i,int j)
{
    int genval=gen_val(i,j);
    if(genval>0)
    {
        a[i][j]=genval;
        l.push(i*10+j);
        int x=gen_pair();
        if(x==-1)
        {
            print_mat();
        }
        else 
        {
            cout<<x<<endl;
            reg(x/10,x%10);
        }
    } 
    else
    {
        a[i][j]=0;
        int p;
        if(!l.empty())
        {
            p=l.top();
            l.pop();
            reg(p/10,p%10);
           
        }
    }
}
int main()
{
    fill();
    order();
    int p1=gen_pair();     
    reg(p1/10,p1%10);
}