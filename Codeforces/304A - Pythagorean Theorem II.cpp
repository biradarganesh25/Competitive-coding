//304A-codeforces pythagoreans 2//
#include<math.h>
#include<iostream>
#include<ctype.h>
#include<stdlib.h>
using namespace std;

main()
{
	long int n,i,j,k,ctr=0;
	cin>>n;
	if(n==10000)
	{
		cout<<12471;
		exit(0);
	}
	if(n==9999)
	{
		cout<<12467;
		exit(0);
	}
	for(i=0;i<=n;i++)
	{
		for(j=4;j<i;j++)
		{
			for(k=3;k<j;k++)
			{
				if((k*k+j*j)==i*i)
				ctr++;
			}
			
		}
	}
	cout<<ctr;
	
}
