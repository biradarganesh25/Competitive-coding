#include<stdio.h>

typedef struct flat
{
    int a[2];
}f;

main()
{
    f flats[10000];
    int n,m,i,ctr=0;
    scanf("%d%d", &n,&m);
    for(i=0;i<n*m;i++)
    {
        scanf("%d%d", &flats[i].a[0],&flats[i].a[1]);
    }
    for(i=0;i<m*n;i++)
    {
        if(flats[i].a[0]==0 && flats[i].a[1]==0)
        continue;
        ctr++;
    }   
    
    printf("%d", ctr);
}
