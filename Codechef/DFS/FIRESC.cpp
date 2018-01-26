#include <bits/stdc++.h>

using namespace std;
#define dbg(var) cerr<<#var<<"= "<<(var)<<endl;
#define dbgw(var) cerr<<(var)<<endl;
#define MOD 1000000007
#define LL long long int
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

/*
 * This is a simple dfs problem. All we need to do is find number of connected 
 * components and the number of nodes in them. Easy.
 * 
 * */

int total = 0;
vector< list<int> > v(100002);
void dfs(int i, auto &visited)
{
	//cout<<i<<" ";
	visited[i] = 1;
	total++;
	for(auto it = v[i].begin(); it != v[i].end(); ++it)
	{
		if(visited[*it] == 0)
			dfs(*it,visited);
	}
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i = 0; i < n; i++)
        	v[i].clear();
        for(int i = 0; i < m; i++)
        {
        	int p,q;
        	scanf("%d%d",&p,&q);
        	v[p-1].push_back(q-1);
        	v[q-1].push_back(p-1);
        }
        vector<int>visited(n,0);
        LL ans = 1,conn=0;
        for(int i = 0; i < n; i++)
        {
        	if(visited[i] != 1)
        	{
        		conn++;
        		total = 0;
        		dfs(i,visited);
        		//printf("\n");
        		ans = ans * total;
        		if(ans >= MOD)
        			ans = ans % MOD;
        	}
        }
		printf("%lld %lld\n",conn,ans);
    }
}
