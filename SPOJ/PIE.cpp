#include <bits/stdc++.h>

using namespace std;
#define dbg(var) cerr<<#var<<"= "<<(var)<<endl;
#define dbgw(var) cerr<<(var)<<endl;
#define mod 1000000007
#define LL long long int
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define PI pair<int,int>
#define pi 3.14159265358979323846264338327950
//vector<LL> cache(5005,0);


int n,f;
//vector< inter > a(1e4+2);
vector< double > vol(1e4+2,0.0),sum(1e4+2,0.0);


//stack< int > s;
//char s[5001];
bool mysorting(double v1, double v2)
{
	return v1 > v2;
}

/*inline double binarys(int start, int end)
{
	double value = sum[end];
	double low = sum[start],high = vol[end];
	double mid;
	int i = 100;
	while(i--)
	{
		mid = low + (high - low)/2;
		if(mid <= value)
			low = mid;
		else
			high = mid;
	}
	return low;


}*/

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

		//sort(vol.begin(),vol.begin()+n,mysorting);
		// sum[0] = vol[0]/f;
		// for(int i = 1; i < n; i++)
		// 	sum[i] = sum[i-1] + vol[i]/f;
		// for(int i = 0; i < n; i++)
		// 	dbg(vol[i]);
		// for(int i = 0; i < n; i++)
		// 	dbg(sum[i]);

		// double max_vol = -1.0,volume;

		// for(int i = n-1; i>=1; i--)
		// {
		// 	volume = binarys(0,i);
		// 	dbg(volume);
		// 	max_vol = max(max_vol,volume);
		// }
		// max_vol = max(max_vol,sum[0]);
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
