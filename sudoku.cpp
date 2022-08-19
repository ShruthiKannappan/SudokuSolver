#include<bits/stdc++.h>
using namespace std;
stack<int> l; // stack which stores the indices that are filled (in the form of a two digit number where units digit is column number and ten's digit is row number)   
int a[9][9]={0};//sudoku matrix
typedef long long ll;
// The following global variables are used for deciding the order of filling the cells.
vector<int> r;  // specifies order of traversing the rows while filling the sudoku with the the row number to be filled at the beginning
vector<int> c; //  specifies order of traversing the rows while filling the sudoku with the the row number to be filled at the beginning
map<int,int> mprcount;// maps a row with the number of cells filled in that row.
map<int,int> mpccount;// maps a row with the number of cells filled in that column.
set<pair<int,int>,greater<pair<int,int>>> srorder;// the first of the pair stores the number of cells filled in a row and the second is the row index. 
set<pair<int,int>,greater<pair<int,int>>> scorder;//  the first of the pair stores the number of cells filled in a column and the second is the column index.
//The  two sets are used to order the rows and columns with the most filled at the first

void order()// this function stores the order of rows and columns in vectors r and c by using sets to order the rows 
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
bool check(int i,int j,int val)// returns true if a particular value can be placed in a cell (row i and column j) else false 
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
int gen_val(int i,int j) // generates the least possible value greater than the value already present in the cell that can be placed in cell (row i and column j) ,if no value in 1 to 9 is possible it returns -1
{
    int val=a[i][j]+1;
    while(!check(i,j,val))
    {
        val++;
{
    int val=a[i][j]+1;
    while(!check(i,j,val))
    {
    }
    if(val<10) return val;
    else return -1;
}
int gen_pair() // returns a number whose tens digit is the row index and ones digit is column number of a cell which needs to be filled next.(according to the order in r and c)
{ //returns -1 when no cell is empty
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
void fill()// fills the input into the matrix and fills the map which maps the row and column with their number of already filled cells in the problem sudoku
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
void print_mat()// prints the matrix
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
void reg(int i,int j)// fills the unoccpied cells recursively
{
    int genval=gen_val(i,j);
    if(genval>0)// if genval is valid we put the value in the cell
    {
        a[i][j]=genval;
        l.push(i*10+j);// push it to the stack to keep track of cells filled by the computer
        int x=gen_pair();// finding next unoccupied cell
        if(x==-1)//all cells filled
        {
            print_mat();
        }
        else 
        {
                reg(x/10,x%10);// fill next cell
        }
    } 
    else// if no val can be put in the cell
    {
        a[i][j]=0;// empty current cell
        int p;
        if(!l.empty())
        {
            p=l.top();// take previous filled cell
            l.pop();// remove prev element
            reg(p/10,p%10);// fill prev element with values greater than current value
           
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
