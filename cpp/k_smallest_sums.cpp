#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

int  a[800][800],k;

struct node
{
    int s,b;
    bool operator<(const node &a) const
    {
        return s>a.s;
    }
};

void merge(int *A,int *B,int *C,int n)
{
    node tmp;
    priority_queue<node> q;
    for(int i=0;i<n;i++)
    {
        tmp.s=A[i]+B[0],tmp.b=0;
        q.push(tmp);
    }
    for(int i=0;i<n;i++)
    {
        tmp=q.top();
        q.pop();
        C[i]=tmp.s;
        if(tmp.b+1<n)
        {
            tmp.s=tmp.s-B[tmp.b]+B[tmp.b+1];
            tmp.b++;
            q.push(tmp);
        }
    }
}

int main()
{
    while(~scanf("%d",&k))
    {
        for(int i=0;i<k;i++)
        {
                printf("input:\n");
            for(int j=0;j<k;j++)
                scanf("%d",&a[i][j]);
            sort(a[i],a[i]+k);
        }
        for(int i=1;i<k;i++)
            merge(a[0],a[i],a[0],k);
        for(int i=0;i<k;i++)
            printf("%d%s",a[0][i],i!=k-1?" ":"\n");
    }
    return 0;
}
