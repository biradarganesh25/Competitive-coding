#include <iostream>
#include<iomanip>

using namespace std;
    
int main()
{
    cout<< fixed << setprecision(0);
    long double l,r,k,t=1,ctr=0;
    cin>>l>>r>>k;
    while(t<l)
    {
        t*=k;
    }
    while(t<=r)
    {
        cout<<t<< " ";
        t*=k;
        ctr++;
    }
    
    if(ctr==0)
    cout<<"-1";
    return 0;
}
