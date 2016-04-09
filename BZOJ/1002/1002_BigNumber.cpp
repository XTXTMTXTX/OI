#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<cctype>
#define ll long long
using namespace std;
struct gjd{
	int n[101];
};
int n;
gjd f[101],two;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void pt(gjd x);
gjd addup(gjd x,gjd y){
	if(x.n[0]<y.n[0]){
		gjd c=y;
		y=x;
		x=c;
	}
	for(int i=1;i<=x.n[0]+1;i++){
		if(i==1){x.n[1]+=y.n[1];continue;}
		x.n[i]+=x.n[i-1]/10+y.n[i];
		x.n[i-1]%=10;
	}
	if(x.n[x.n[0]+1]>0)x.n[0]++;
	return x;
}
gjd cutdown(gjd x,gjd y){
	for(int i=1;i<=x.n[0];i++){
		x.n[i]-=y.n[i];
		if(x.n[i]<0){
			x.n[i]+=10;
			x.n[i+1]--;
		}
	}
	while(x.n[x.n[0]]==0&&x.n[0]>1)x.n[0]--;
	return x;
}
void pt(gjd x){
	for(int i=x.n[0];i>=1;i--){
		printf("%d",x.n[i]);
	}
	printf("\n");
}
int main(){
	n=read();
	two.n[0]=1;
	two.n[1]=2;
	f[0].n[0]=1;f[1].n[1]=0;
	f[1].n[0]=1;f[1].n[1]=1;
	f[2].n[0]=1;f[2].n[1]=5;
	//pt(cutdown(addup(f[2],f[2]),f[2]));
	for(int i=3;i<=n;i++)f[i]=cutdown(addup(two,addup(f[i-1],addup(f[i-1],f[i-1]))),f[i-2]);
	pt(f[n]);
	return 0;
}
