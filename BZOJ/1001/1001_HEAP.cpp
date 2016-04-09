#include<cstdio>
#include<cstring>
#include<queue>
#define MAXINt 0x7fffffff
#define INF 0x7fffffff
using namespace std;
struct hp{
	int first,second;
} heap[3000010];
int n,m,tot,ps=-1,num,top;
int first[3000010],v[6000000],w[6000000],next[6000010],dis[3000010],refind[3000010];
bool b[3000010];
void add(const int &ui,const int &vi,const int &wi){
	w[++ps]=wi;
	next[ps]=first[ui];
	first[ui]=ps;
	v[ps]=vi;
}
void up(const int &st){
	int i=st,j=i/2;
	heap[0]=heap[i];
	while(j>0){
		if(heap[0].first>=heap[j].first)break;
		heap[i]=heap[j];refind[heap[i].second]=i;
		i=j;j=i/2;
	}
	heap[i]=heap[0];refind[heap[i].second]=i;
}
void down(const int &st){
	int i=st,j=i*2;
	heap[0]=heap[i];
	while(j<=top){
		if(j<top&&heap[j].first>heap[j+1].first)j++;
		if(heap[0].first<=heap[j].first)break;
		heap[i]=heap[j];refind[heap[i].second]=i;
		i=j;j=i*2;
	}
	heap[i]=heap[0];refind[heap[i].second]=i;
}
void ins(const int &a,const int &b){
	top++;
	heap[top].first=a;heap[top].second=b;refind[b]=top;
	up(top);
}
void change(const int &a,const int &b){
	if(refind[b]!=-1){
		heap[refind[b]].first=a;
		heap[refind[b]].second=b;
		up(refind[b]);
		down(refind[b]);
	}else ins(a,b);
}
void pop(){
	refind[heap[1].second]=-1;
	heap[1]=heap[top];
	top--;
	down(1);
}
void dijkstra(){  
    for(int i=1; i<=tot; i++) dis[i]= INF; 
	ins(dis[0],0);
	while(top>0){
		hp p=heap[1];pop();
		if(b[p.second])continue;
		b[p.second]=1;
		if(p.second==tot)return;
		for(int i=first[p.second];i!=-1;i=next[i]){
			if(b[v[i]]||dis[v[i]]<=dis[p.second]+w[i])continue;
			dis[v[i]]=dis[p.second]+w[i];
			change(dis[v[i]],v[i]);
		}
	}
}  
int read(){
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
	memset(first, -1, sizeof(first));
	memset(refind, -1, sizeof(refind));
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
