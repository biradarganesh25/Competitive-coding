#include<iostream>
#include<string>
#include<locale>
using namespace std;
int main()
{
    string a;
    cin>>a;
    locale loc;
    int n=a.length();
    for(int i=0;i<n;i++)
    {
        a[i]=tolower(a[i],loc);
        if(a[i]=='a' || a[i]=='i' || a[i]=='o' || a[i]=='e' || a[i]=='u' || a[i]=='y')
            continue;
        else
        {
            cout<<'.'<<a[i];
        }
    }
    cout<<endl;
}
