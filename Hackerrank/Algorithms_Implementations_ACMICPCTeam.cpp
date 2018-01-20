#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n;
    int m;
    cin >> n >> m;
    vector<string> topic(n);
    for(int topic_i = 0;topic_i < n;topic_i++){
       cin >> topic[topic_i];
    }
    int common, max = -1, maxnum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            common = 0;
            for ( int k = 0; k < m; k++)
            {
                int d1 = topic[i][k] - 48;
                int d2 = topic[j][k] - 48;
                
                if ((d1 != d2) || (d1 == 1 && d2 == 1))
                    common++;
            }
            
            if (common > max)
            {                
                max = common;
                maxnum = 1;
            }
            else if (common == max)
            {
                maxnum++;
            }
        }
    }
    
    cout << max << endl << maxnum;
    
    return 0;
}
