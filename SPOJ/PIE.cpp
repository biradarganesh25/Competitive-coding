#include <bits/stdc++.h>

using namespace std;
#define dbg(var) cerr<<#var<<"= "<<(var)<<endl;
#define dbgw(var) cerr<<(var)<<endl;
#define mod 1000000007
#define LL long long int
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define PI pair<int,int>
#define pi 3.14159265358979323846264338327950
//Need to use that big ass value or use acos(-1). Otherwise, it'll give WA.

//So, it's a simple binary search problem. Highest value of the volume can be the volume of the largest pie, meaning only
//one person can eat. Minimum value can be 0, i.e no one gets anything to eat. But if you use you'll raise an exception,
//so just DBL_MIN, which is the minimum value that your system can represent.  
int n,f;

vector< double > vol(1e4+2,0.0),sum(1e4+2,0.0);



bool mysorting(double v1, double v2)
{
	return v1 > v2;
}


bool check(double mid)
{
	int currf = 0;
	for(int i = 0; i < n; i++)
	{
		currf += vol[i] / mid;
	}
	if(currf >= f)
		return true;
	else
		return false;
}

int main()
{

	int t;
	scanf("%d",&t);
	while(t--)
	{
		double max_val = DBL_MIN;
		scanf("%d%d",&n,&f);
		f++;
		double v;
		int r;
						
		for(int i = 0; i < n; i++)
		{
			scanf("%d",&r);
			v = pi * r * r;
			vol[i] = v;
			max_val = max(max_val,v);
				
		}

		
		double low = DBL_MIN, high = max_val,mid;
		int i = 100;
		while(i--)
		{
			mid = low + (high - low) / 2;
			if(check(mid))
				low = mid;
			else
				high = mid;
		}
		printf("%f\n", low);




	}
}
