#include<cstdio>
#include<cstring>
#include<queue>
#define MAXINt 0x7fffffff
#define INF 0x7fffffff
using namespace std;
int n,m,tot,ps=-1,num;
int FIrst[7000010],v[7000000],w[7000000],NExt[7000010],dis[7000010];
bool b[7000010];
typedef pair<int, int> pii; 
priority_queue<pii, vector<pii>, greater<pii> > q;  
void dijkstra()  
{  
    for(int i=1; i<=tot; i++) dis[i]= INF; 
    q.push(make_pair(dis[0], 0));  
    while(!q.empty())  
    {  
        pii p = q.top();    q.pop();  
        int x = p.second;  
        if(!b[x])  
        {  
            b[x] = 1;  
            if(x==tot)return;
            for(int i=FIrst[x]; i!=-1; i=NExt[i])  
            {  
            	if(b[v[i]]||dis[v[i]] <= dis[x]+w[i])continue;   
                dis[v[i]] = dis[x] + w[i];  
                q.push(make_pair(dis[v[i]], v[i]));    
            }  
        }  
    }
}  
void add(const int &ui,const int &vi,const int &wi){
	w[++ps]=wi;
	NExt[ps]=FIrst[ui];
	FIrst[ui]=ps;
	v[ps]=vi;
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	scanf("%d %d",&n,&m);
	//if (n==0||m==0){printf("0"); return 0;}
    if(n==1 || m==1) {
        if(n>m) {
			n=m+n;
			m=n-m;
			n=n-m;
		}
        int ans=INF;
        for(int i=1, a; i<m; i++) {
            a=read();
            if(ans>a) ans=a;
        }
        printf("%d\n", ans==INF?0:ans);
        return 0;
    }
	tot=2*(n-1)*(m-1)+1;
	memset(FIrst, -1, sizeof(FIrst));
    for(int i=0, id1, id2, a; i<=n-1; i++)
        for(int j=1; j<=m-1; j++) {
            a=read();
            id1=((i-1)*(m-1)+j)*2-1;
            id2=(i*(m-1)+j)*2;
            if(i==0) id1=tot;
            else if(i==n-1) id2=0;
            add(id1, id2, a);
            add(id2, id1, a);
        }

    for(int i=1, id1, id2, a; i<=n-1; i++)
        for(int j=0; j<m; j++) {
            a=read();
            id1=((i-1)*(m-1)+j)*2;
            id2=((i-1)*(m-1)+j+1)*2-1;
            if(j==0) id1=0;
            else if(j==m-1) id2=tot;
            add(id1, id2, a);
            add(id2, id1, a);
        }

    for(int i=1, id1, id2, a; i<=n-1; i++)
        for(int j=1; j<=m-1; j++) {
            a=read();
            id1=((i-1)*(m-1)+j)*2;
            id2=((i-1)*(m-1)+j)*2-1;
            add(id1, id2, a);
            add(id2, id1, a);
        }
    dijkstra();
    printf("%d",dis[tot]);
	return 0;
}
