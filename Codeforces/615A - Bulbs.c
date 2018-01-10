#include<stdio.h>
#include<stdlib.h>
int a[100]={};

int n,m,i,j,b[100];
void change()
{
    int i;
    scanf("%d", &i);
    if(i<=m)
    a[i]=1;
    return ;
}
    
main()
{
    scanf("%d%d", &n,&m);
    
    for(i=1;i<=n;i++)
    {
        scanf("%d", &b[i]);
        for(j=1;j<=b[i];j++)
        {
        change();
        }
    }
 
    for(i=1;i<=m;i++)
    {
        if(a[i]==0)
        {
        printf("NO");
        exit(0);
        }
    }
    printf("YES");
    
}
