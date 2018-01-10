#include<stdlib.h>
#include<stdio.h>
int main()
{
	long long int n,a,b,c,ans=0;
	scanf("%lld%lld%lld%lld", &n,&a,&b,&c);
	if(a<=(b-c))
	{
		ans=n/a;
		printf("%lld",ans);
		exit(0);
	}
	if(n>=b)
	{
	ans=(n-c)/(b-c);
	}
	n=n-ans*(b-c);
	ans=ans+n/a;
printf("%lld", ans);
return 0;
}
