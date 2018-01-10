
#include<stdio.h>
#include<math.h>
main()
{
    double a,m,n,k;
    scanf("%lf%lf%lf", &n,&m,&a);
    k=(ceil(n/a))*(ceil(m/a));
    printf("%.0lf", k);
}
