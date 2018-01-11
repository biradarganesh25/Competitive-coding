// Problem Link: http://www.spoj.com/problems/FARIDA/
//
// Problem Difficulty: Easy-Medium
// Tags: DP
// Problem Description: Read from the problem link.
//
// Solution Description:
//          This is a basic dp problem, other online editorials regarding this problem are not intuitive to explain, so I will try to
//          explain how I solved it.
//          At each step we compute answers for both cases: if we collect the coins at the ith step and not collect the coins on the ith step
//          Think of the dp state dp[i][0] as the maximum coins you can collect at the ith step exluding the current i.
//          Think of the dp state dp[i][1] as the maximum coind you can collect at the ith step including the current i.
//          Now to calculate the value of dp[i][1] it's easy to think, we add the coins at ith step with the maximum coins that we
//          can obtain exluding the i-1. Meaning for dp[i][1] = arr[i](adding the current i) + dp[i-1][0](maximum coins you can obtain excluding the prevous)
//          For dp[i][0], we are not adding the current i, we just take the max of the previous including and excluding.
//
// Good Read: https://www.quora.com/Are-there-any-good-resources-or-tutorials-for-dynamic-programming-DP-besides-the-TopCoder-tutorial/answer/Michal-Danil%C3%A1k?srid=lzkE

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <cstdio>

using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REPI(i, j) for(int i=1; i<=j; i++)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define pb push_back
#define si(x)    scanf("%d",&x)
#define sl(x)    scanf("%lld",&x)
#define ss(s)    scanf("%s",s)
#define pi(x)    printf("%d\n",x)
#define pl(x)    printf("%lld\n",x)
#define ps(s)    printf("%s\n",s)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
typedef vector<int> vi;
typedef vector<ll> vl;
const int mod = 1000000007;
const int m = 1000007;

void solve();

int main() {
    //freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}


void solve() {
    ll t, ca=1;
    cin>>t;
    while(t--){
        ll n;
        cin>>n;
        ll arr[n];
        REP(i, n) cin>>arr[i];
        ll dp[2][n+1];
        memset(dp, 0, sizeof(dp));
        REP(i, n+1){
            if(i==0) continue;
            dp[0][i] = max(dp[1][i-1], dp[0][i-1]);
            dp[1][i] = dp[0][i-1] + arr[i-1];
        }
        cout<<"Case "<<ca++<<": "<<max(dp[0][n], dp[1][n])<<endl;
    }
}

