#include <iostream>
#define infinity 999
using namespace std;

void dij(int n,int v,int cost[10][10],int dist[],int nxt_node[])
{
 int i,u,count,w,flag[10],min;
 for(i=1;i<=n;i++)
  {flag[i]=0;
  dist[i]=cost[v][i];
  nxt_node[i]=-1;
  }
 count=2;
 while(count<=n)
 {
  min=99;
  for(w=1;w<=n;w++)
   {if(dist[w]<min && !flag[w])
    {min=dist[w];
    u=w;
    }
   }
  flag[u]=1;
  count++;
  for(w=1;w<=n;w++)
   if((dist[u]+cost[u][w]<dist[w]) && !flag[w])
    {dist[w]=dist[u]+cost[u][w];
     if(nxt_node[u]==-1) nxt_node[w]=u;
     else nxt_node[w]=nxt_node[u];
     }
 }
}

int main()
{
 int no_of_routers,v,i,j,cost[10][10],dist[10],nxt_router[10];

 cout<<"\n Enter the number of routers:";
 cin>>no_of_routers;
 cout<<"\n Enter the cost matrix:\n";
 for(i=1;i<=no_of_routers;i++)
  for(j=1;j<=no_of_routers;j++)
  {
   cin>>cost[i][j];
   if(cost[i][j]==0)
    cost[i][j]=infinity;
  }

 for(v=1;v<=no_of_routers;v++)
{
 dij(no_of_routers,v,cost,dist,nxt_router);
 cout<<"\n Routing Table for Router "<<v<<"\n";
 cout<<"NODE \t COST \t Next Router\n\n";
 for(i=1;i<=no_of_routers;i++)
  {if(i==v) cout<<" "<<i<<"\t  0\t  -\n";
  else if(nxt_router[i]==-1) cout<<" "<<i<<"\t  "<<dist[i]<<"\t  -\n";
  else cout<<" "<<i<<"\t  "<<dist[i]<<"\t  "<<nxt_router[i]<<"\n";
  }
}
return 0;
}