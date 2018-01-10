#include<iostream>
using namespace std;
int main(){
    int n;
    int k;
    cin>>n>>k;
    int *a=new int[n];
    int l=k;
    for(int i=0;i<n;i++)
    cin>>a[i];
    if(a[0]<=0)
    cout<<0<<endl;
    else if(a[k]<a[k-1] && k!=n)
    cout<<k<<endl;
    else if(a[k-1]==0){
            l=0;n=k-2;
        while(1){
            int m=(l+n)/2;
            if(a[m]>0)
            {
                if(a[m+1]==0){
                    cout<<m+1<<endl;
                    return 0;
                }
                else{
                    l=m+1;
                    continue;
                }
            }
            else{
                if(a[m-1]!=0){
                    cout<<m<<endl;
                    return 0;
                }
                else{
                    n=m-1;
                    continue;
                }
            }
    }
    }
    else{
        while(1){
            if((l-1)==(n-1))
            {
                cout<<n<<endl;
                return 0;
            }
            int m=(l+n-1)/2;
            if(a[m]<a[k-1])
            {
                if(a[m-1]==a[k-1])
                {
                    cout<<m<<endl;
                    return 0;
                }
                else{
                    n=m;
                    continue;
                }
            }
            else{
                l=m+1;
                continue;
            }
        }
    }
}
