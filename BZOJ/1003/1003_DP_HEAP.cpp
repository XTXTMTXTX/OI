#include<cstdio>
#include<cstring>
#define INF 0x7F7F7F7F
using namespace std;
struct hp{
    int w,v;
}heap[21];
int n,m,K,e,d,ps=-1,w[500],v[500],first[21],next[500],refind[21],top,dis[21],f[101],cost[101][101];
bool ua[21][101],b[21];
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void add(int x,int y,int z){
    w[++ps]=z;
    v[ps]=y;
    next[ps]=first[x];
    first[x]=ps;
    w[++ps]=z;
    v[ps]=x;
    next[ps]=first[y];
    first[y]=ps;
}
void shiftup(int i){
    int j=i/2;
    heap[0]=heap[i];
    while(j>0){
        if(heap[j].w<=heap[0].w)break;
        heap[i]=heap[j];refind[heap[i].v]=i;
        i=j;j=i/2;
    }
    heap[i]=heap[0];refind[heap[i].v]=i;
}
void shiftdown(int i){
    int j=i*2;
    heap[0]=heap[i];
    while(j<=top){
        if(j<top&&heap[j+1].w<heap[j].w)j++;
        if(heap[0].w<=heap[j].w)break;
        heap[i]=heap[j];refind[heap[i].v]=i;
        i=j;j=i*2;
    }
    heap[i]=heap[0];refind[heap[i].v]=i;
}
void insert(int x,int y){
    heap[++top].w=x;heap[top].v=y;refind[y]=top;
    shiftup(top);
}
void change(int x,int y){
    if(refind[y]){
        if(x<heap[refind[y]].w){
            heap[refind[y]].w=x;
            shiftup(refind[y]);
            shiftdown(refind[y]);
        }
    }else insert(x,y);
}
void pop(){
    refind[heap[1].v]=0;heap[1]=heap[top--];refind[heap[1].v]=1;
    shiftdown(1);
}
int dijkstra(int x,int y){
    for(int i=1;i<=m;i++){
        b[i]=0;
        for(int j=x;j<=y;j++)if(ua[i][j]){b[i]=1;break;}
    }
    for(int i=2;i<=m;i++)dis[i]=INF;dis[1]=0;
    if(b[1])return INF;
    top=0;
    memset(refind,0,sizeof(refind));
    insert(0,1);
    while(top>0){
        int x=heap[1].v;pop();
        if(b[x])continue;else b[x]=1;
        if(x==m)return dis[m];
        for(int i=first[x];i!=-1;i=next[i]){
            if(b[v[i]]||dis[v[i]]<=dis[x]+w[i])continue;
            dis[v[i]]=dis[x]+w[i];
            change(dis[v[i]],v[i]);
        }
    }
    return dis[m];
}
int main(){
    n=read();m=read();K=read();e=read();
    memset(first,-1,sizeof(first));
    for(int i=1;i<=e;i++){
        int x=read(),y=read(),z=read();
        add(x,y,z);
    }
    d=read();
    for(int i=0;i<d;i++){
        int p=read(),st=read(),ed=read();
        for(int j=st;j<=ed;j++)ua[p][j]=1;
    }
    for(int i=1;i<=n;i++)
    for(int j=i;j<=n;j++)cost[i][j]=dijkstra(i,j);
    for(int i=1;i<=n;i++){
        f[i]=cost[1][i]==INF?INF:cost[1][i]*i;
        for(int j=1;j<i;j++)if(cost[j+1][i]!=INF)f[i]=(f[i]>(f[j]+cost[j+1][i]*(i-j)+K)?(f[j]+cost[j+1][i]*(i-j)+K):f[i]);
    }
    printf("%d\n",f[n]);
    return 0;
}
