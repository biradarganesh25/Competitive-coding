#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;


main()
{
	char n[10], *p;
	p=&n[0];
	int i,k=0;
	long int a;
	cin>>n;
	for(i=0;n[i]!='\0';i++)
	{
		if(n[i]=='1')
		{
			continue;
		}
		
		else if(n[i]=='0')
		{
			if(i==strlen(n)-1 && k!=0)
			n[i]='1';
			else if(k!=0)
			n[i]='1';
		}
		else
		{
			n[i]='1';k++;
		}
	}
	a=strtol(n,&p,2);
	cout<<a;
}
