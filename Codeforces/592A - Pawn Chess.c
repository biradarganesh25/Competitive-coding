//592A-codeforces//

#include<stdio.h>
    char a[8][9];

int checkcolW(int i,int j)
{
    int n;
    for(n=i-1;n>=0;n--)
    {
        if(a[n][j]!='.')
        return 0;
    }
    return 1;
}

int checkcolB(int i,int j)
{
    int n;
    for(n=i+1;n<8;n++)
    {
        if(a[n][j]!='.')
        return 0;
    }
    return 1;
}

main()
{

    int i,j,maxb=0,mina=7,black,white;
    for(i=0;i<8;i++)
    {
        for(j=0;j<9;j++)
        scanf("%c", &a[i][j]);
    }
    /*printf("\n");
    
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        printf("%c", a[i][j]);
        printf("\n");
    }*/
    
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(a[i][j]=='.')
            continue;
            if(a[i][j]=='B')
            {
                if(checkcolB(i,j)==1)
                {
                    if(i>=maxb)
                maxb=i;
                }   
            }
            else
            {
                if(checkcolW(i,j)==1)
                {
                    if(i<=mina)
                    mina=i;
                }
            }
        }
    }
    
    black=7-maxb;
    white=mina;
    if(white>black)
    printf("B");
    else
    printf("A");
}
