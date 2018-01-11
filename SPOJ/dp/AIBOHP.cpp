
#include <bits/stdc++.h>

using namespace std;
#define dbg(var) cerr<<#var<<"= "<<(var)<<endl;
#define dbgw(var) cerr<<(var)<<endl;
#define mod 1000000007
#define LL long long int
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define PI pair<int,int>
#define pi 3.14159265358979323846264338327950

//Probem Link : https://www.spoj.pl/problems/AIBOHP/
//So this is dp problem. To help with the recursion, first think about palindromes : they have the first and the last letter
//as the same. So, assume a string which is a plaindrome except for it's outer two letters(one of them can be empty.) So , to
//make it a palindrome you have to add letter either to the right end or left end of the string, which will increase the cost
//by one. Also, if the outermost letters are same, we have to do the same thing for the inner string, excluding the outer ones.
//This leads to the recursive function, which can be memoized easily as show below.

char str[6102];
int len;
int cache[6102][6102];

int dp(int i, int j) {
    if (cache[i][j] != -1) return cache[i][j];
    if (i >= j) return cache[i][j] = 0;
    if (str[i] == str[j]) return cache[i][j] = dp(i + 1, j - 1);
    else return cache[i][j] = min(dp(i + 1, j), (i, j - 1)) + 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(cache, -1, sizeof(cache));
        scanf("%s", str);
        len = strlen(str);
        int ans = dp(0, len - 1);
        printf("%d\n", ans);
    }

}
