#include<stdio.h>

main()
{
    
    int n,p,q,i,A=0,B=0,t,k=0;
    char a[100];
    scanf("%d%d%d", &n,&p,&q);
    for(i=0;i<n;i++)
    scanf(" %c", &a[i]);
    t=n;
    while(t>0)
    {
        t=t-p; A++;
        if(t%q==0 && t>0)
        {
        B=t/q;
        break;
        }
    }
    
    
    
    if(A*p+B*q==n)
    {
    printf("%d\n", A+B);
    while(A>0)
    {
        for(i=0;i<p;i++)
        printf("%c", a[k++]);
        printf("\n");
        A--;
    }
    while(B>0)
    {
        for(i=0;i<q;i++)
        printf("%c",a[k++]);
        printf("\n");
        B--;
    }
    }
    else if(n%p==0)
    {
        printf("%d\n", (n/p));
    for(i=0;i<n/p;i++)
    {
        for(t=0;t<p;t++)
        printf("%c", a[k++]);
        printf("\n");
    }   
    }   
    else if(n%q==0)
    {
        printf("%d\n", (n/q));
        for(i=0;i<n/q;i++)
        {
            for(t=0;t<q;t++)
            printf("%c", a[k++]);
            printf("\n");
        }
    }
    else
    {
        printf("-1");
    }
}
