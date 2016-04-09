#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<cctype>
#define ll long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n;
double G[101][101];
double ans;
int main(){
	for(n=1;n<=100;n++){
	if(n==1){printf("%5d 1\n",n);goto a;}
	if(n==2){printf("%5d 5\n",n);goto a;}
	memset(G,0,sizeof(G));
	ans=1;
	G[0][0]=n;
	for(int i=1;i<=n;i++){
		G[i][i]=3;
		G[i][0]=-1;
		G[0][i]=-1;
		G[i][i-1]=-1;
		G[i-1][i]=-1;
	}
	G[1][n]=-1;G[n][1]=-1;
	for(int i=2;i<=n;i++)
	for(int j=i;j<=n;j++){
		double tmp=-G[j][i-1]/G[i-1][i-1];
		for(int k=i;k<=n;k++)G[j][k]+=G[i-1][k]*tmp;
	}
	for(int i=1;i<=n;i++)ans*=G[i][i];
	printf("%5d %lld\n",n,abs((ll)(round(ans))));
	a:;
	}
	return 0;
}
