#include<stdio.h>

main()
{
    int n,a[100],i,odd=0,even=0,flag;
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {   
    scanf("%d", &a[i]);
    if(a[i]%2!=0)
        odd++;
        else
        even++;
    }
    
    if(odd>even)
    {
        for(i=0;i<n;i++)
        {
            if(a[i]%2==0)
            {
                flag=i;
                break;
            }
        }
    }
    else
    {
        for(i=0;i<n;i++)
        {
            if(a[i]%2!=0)
            {
                flag=i;
                break;
            }
        }
    }
    
    printf("%d", flag+1);
}
