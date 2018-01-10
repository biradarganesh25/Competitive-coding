#include<stdio.h>
int ctr=0;
void extract(char *a, int *b)
{
	if(*a=='\0')
	return ;
	if(*a!='+')
	{
		*b=*a-'0';
		ctr++;
		return extract(a+1,b+1);
	}
	else
	return extract(a+1,b);
}
int main()
{
	char a[110];
	int b[100],i,j;
	scanf("%s",a);
	extract(a,b);
	for(i=0;i<ctr;i++)
	{
		for(j=0;j<i;j++)
		{
			if(b[j]>b[i])
			{
				b[j]=b[i]+b[j];
				b[i]=b[j]-b[i];
				b[j]=b[j]-b[i];
			}
		}
	}
	for(i=0;i<ctr-1;i++)
	{
		printf("%d+",b[i]);
	}
	printf("%d",b[i]);
}
