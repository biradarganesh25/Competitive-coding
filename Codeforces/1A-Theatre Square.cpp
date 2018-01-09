#include<iostream>
using namespace std;
int main()
{
    int n,m,a;
    cin>>n>>m>>a;
    long long int l,o;
    if(n%a==0)
    {
        l=n/a;
    }
    else
    {
        l=n/a;
        l++;
    }
    if(m%a==0)
    {
        o=m/a;
    }
    else
    {
        o=m/a;
        o++;
    }
    long long int v=l*o;
    cout<<v<<endl;
}
