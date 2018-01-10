#include<bits/stdc++.h>
using namespace std;
main()
{
	long long int x,res=0;
	cin>>x;
	while(x/5!=0)
	{
		x-=5;
		res++;
	}
	while(x/4!=0)
	{
		x-=4;
		res++;
	}
	while(x/3!=0)
	{
		x-=3;
		res++;
	}
	while(x/2!=0)
	{
		x-=2;
		res++;
	}
	while(x!=0)
	{
		x--;
		res++;
	}

	cout<<res;
}
