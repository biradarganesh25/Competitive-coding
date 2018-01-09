#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a;
        if(a.length()<=10)
        cout<<a<<endl;
        else{
            cout<<a[0];
            cout<<(a.length()-2);
            cout<<a[a.length()-1];
            cout<<endl;
        }
        
    }
    return 0;
}
