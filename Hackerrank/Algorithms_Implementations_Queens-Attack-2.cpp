//----------- SOLUTION 1 ---------------

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*int count_total (int rq, int cq, int n)
{
    if (n == 1) return 0;
    if (n == 2) return 3;
    
    int base = 3*(n-1);
    int total = base;
        
    for (int i = 1; i <= (n+1)/2; i++)
    {
        if (rq == i || rq == n+1-i || cq == i || cq == n+1-i)
        {
            total += 2*(i-1);
            break;
        }
    }
    
    return total;   
}*/

int max (int a, int b)
{
    return a > b ? a : b;
}

int min (int a, int b)
{
    return a < b ? a : b;
}

int main(){
    int n;
    int k;
    cin >> n >> k;
    int rQueen;
    int cQueen;
    cin >> rQueen >> cQueen;
    
    int mind1drow = 100001, mind1dcol = 100001, maxd1urow = -1, maxd1ucol = -1, mind2drow = 100001, mind2dcol = 100001, maxd2urow = -1, maxd2ucol = -1, maxru = -1, minrd = 100001, mincr = 100001, maxcl = -1;
    
    int total_possible = count_total(rQueen, cQueen, n);
    int subtract = 0;
    
    for(int a0 = 0; a0 < k; a0++){
        int rObstacle;
        int cObstacle;
        cin >> rObstacle >> cObstacle;
        
        if (rObstacle == rQueen)
        {
            if (cObstacle < cQueen && cObstacle > maxcl) maxcl = cObstacle;
            if (cObstacle > cQueen && cObstacle < mincr) mincr = cObstacle;
        }
        
        else if (cObstacle == cQueen)
        {
            if (rObstacle < rQueen && rObstacle > maxru) maxru = rObstacle;
            if (rObstacle > rQueen && rObstacle < minrd) minrd = rObstacle;
        }
        
        else if (fabs(rObstacle - cObstacle) == fabs(rQueen - cQueen))
        {
            if ((rQueen > cQueen && rObstacle > cObstacle) || (rQueen < cQueen && rObstacle < cObstacle) || (rQueen == cQueen && rObstacle == cObstacle) )
            {
                if (rObstacle > rQueen && rObstacle < mind1drow)
                {
                    mind1drow = rObstacle;
                    mind1dcol = cObstacle;
                }
            
                if (rObstacle < rQueen && rObstacle > maxd1urow)
                {
                    maxd1urow = rObstacle;
                    maxd1ucol = cObstacle;
                }
            }    
        }
        
        else if (rObstacle + cObstacle == rQueen + cQueen)
        {
            if (rObstacle > rQueen && rObstacle < mind2drow)
            {
                mind2drow = rObstacle;
                mind2dcol = cObstacle;
            }
            
            if (rObstacle < rQueen && rObstacle > maxd2urow)
            {
                maxd2urow = rObstacle;
                maxd2ucol = cObstacle;
            }   
        }  
    }  
  
    int finalt = 0;
    
    if (mincr != 100001) finalt += (mincr - cQueen - 1);
    else finalt += n - cQueen;
    
    if (maxcl != -1) finalt += (cQueen - maxcl - 1);
    else finalt += cQueen - 1;

    if (minrd != 100001) finalt += (minrd - rQueen - 1);
    else finalt += n - rQueen;
    
    if (maxru != -1) finalt += (rQueen - maxru - 1);
    else finalt += rQueen - 1;

    if (mind1drow != 100001) finalt += (mind1drow - rQueen - 1);
    else finalt += (n - max(rQueen, cQueen));
   
    if (maxd1urow != -1) finalt += (rQueen - maxd1urow - 1);
    else finalt += (min(rQueen, cQueen) - 1);

    if (maxd2urow != -1) finalt += (rQueen - maxd2urow - 1);
    else finalt += (min(rQueen - 1, n - cQueen));
    
    if (mind2drow != 100001) finalt += (mind2drow - rQueen - 1);
    else finalt += (min(n - rQueen, cQueen - 1));

    cout << finalt << endl;
    
    return 0;
}

//--------------------- SOLUTION 2 --------------------

#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> pii; 
set <pii> obstacles;

int dr[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dc[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

int main(){
    
    int total = 0;
    int n;
    int k;
    cin >> n >> k;
    int rQ;
    int cQ;
    cin >> rQ >> cQ;
    for(int a0 = 0; a0 < k; a0++)
    {
        int rOb;
        int cOb;
        cin >> rOb >> cOb;
        
        obstacles.insert(pii(rOb, cOb));
    }    
    for (int i = 0; i < 8; i++)
    {
        // Pick one dx and one dy
        int r = dr[i], c = dc[i];
        // Direction has been chosen
        int newR = rQ + r, newC = cQ + c;
        // New Co ords given
        while (newR >= 1 && newR <=n && newC >=1 && newC <=n && obstacles.count(pii(newR, newC)) == 0)
        {
            total++;
            newR += r;
            newC += c;
        }       
    }  
    cout << total;  
    return 0;
}
