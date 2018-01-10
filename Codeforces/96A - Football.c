#include<stdio.h>
#include<string.h>
int main()
{
	char a[110],mark;
	int ctr=0,i=0;
	scanf("%s",a);
	mark=a[0];
	for(i=0;i<strlen(a)&&ctr<7;i++)
	{
		if(mark==a[i])
		{
			ctr++;
		}
		else
		{
			mark=a[i];
			ctr=1;
		}
	}
	if(ctr==7)
	printf("YES");
	else
	printf("NO");
return 0;
}
