#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <new>

using namespace std;

void o_f( int t );
void bintodec (int *a , int m, int c);

void countchildren( int *children, int *parent, vector < pair<int ,int> > adj[], int node );

class Graph{
private:
        int V,E;
        vector<pair<int,pair<int,int> > > edges;
        
public:
        vector<pair<int,pair<int,int> > > MST;
        Graph(int V,int E);
        void addEdge(int u,int v,int w);
        void kruskalMST();
        void printMST();
        int  countNotReach(int &v);
        void DFSUtil(int v, bool visited[]);
};
Graph::Graph(int V,int E){
    this->V = V;
    this->E = E;
}
void Graph::addEdge(int u,int v,int w){
    edges.push_back({w,{u,v}});
}

void Graph::printMST(){
    vector<pair<int,pair<int,int> > >::iterator it;
    for(it = MST.begin();it!=MST.end();it++){
        cout << it->second.first << " - " << it->second.second << endl;
    }

}
struct DisjointSet{
    int *parent,*rnk;
    int n;

    DisjointSet(int n){
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        for(int i=0;i<=n;i++){
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int Find(int u){
        if(u == parent[u]) return parent[u];
        else return Find(parent[u]);
    }

    void Union(int x,int y){
        x = Find(x);
        y = Find(y);
        if(x != y){
            if(rnk[x] < rnk[y]){
                rnk[y] += rnk[x];
                parent[x] = y;
            }
            else{
                rnk[x] += rnk[y];
                parent[y] = x;
            }
        }
    }
};
void Graph::kruskalMST(){

    sort(edges.begin(),edges.end());
    //for all u in G_v
    //    MAKE-SET(u)
    DisjointSet ds(this->V);

    vector<pair<int,pair<int,int> > >::iterator it;
    // for all edges in G
    for(it = edges.begin(); it!=edges.end();it++){
        int u = it->second.first;
        int v = it->second.second;

        int setU = ds.Find(u);
        int setV = ds.Find(v);


        if(setU != setV){
            int w = it->first;
            MST.push_back({w,{u,v}});

            ds.Union(setU,setV);
        }
    }
    return ;
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and
    // print it
    visited[v-1] = true;
   
    // Recur for all the vertices adjacent
    // to this vertex
   
   vector<pair<int,pair<int,int> > >::iterator it;
   for(it = MST.begin();it!=MST.end();++it){
       
       
       if (visited[it->second.first - 1] && !visited[ it->second.second - 1] ){
           DFSUtil(it->second.second, visited);
       }
        else if ( !visited[it->second.first - 1] && visited[it->second.second - 1] ){
           DFSUtil(it->second.first, visited);
        }
       
    }
}

// Returns count of not reachable nodes from
// vertex v.
// It uses recursive DFSUtil()
int Graph::countNotReach(int &v){
    
    int x, k, w;
    vector<pair<int,pair<int,int> > >::iterator p;
  
    p = MST.begin();
    x=p-> second.first;
    k=p-> second.second;
    w=p->first;
    
    MST.erase(MST.begin());
    
    v = w;
    
    
    //printMST();
    
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
  
    // Call the recursive helper function
    // to print DFS traversal
    p=MST.begin();
    DFSUtil(p->second.first, visited);
    
   // for (int i=0; i<V; i++) cout<< visited[i];
    //5 6 1 3 5 4 5 0 2 1 3 3 2 1 4 3 4 4 2 2cout << endl;
    
  
    // Return count of not visited nodes
    int count = 0;
    for (int i = 0; i < V; i++) {
        if (visited[i] == false)
            count++;
    }
    
    MST.push_back({w,{x,k}});
    
    //cout<< endl;
    //printMST();
    //cout<< endl;
    
    delete[] visited;
    
    return count;
}




int main(){
    int V,E,temp1, t1, t2, t3, node;
    int temp=0;
    
    cin>>V;
    
    cin>>E;
    
    int *powerof2;
    powerof2 = new int [E];
    for (int i= 0; i<E; i++){
        powerof2[i]=0;
    }
    
    vector< pair<int,int> >adj[V];
    int *children;
    int *parent;
    children = new int [V];
    parent = new int [V];
    
    for (int i=0; i<V; i++){
        children[i]=parent[i]=0;
    }
    
    Graph g(V,E);
   
    int u,v,w;
    for(int i=0;i<E;i++){
        cin >> u >> v >> w;
        g.addEdge(u,v,w);
    }

    g.kruskalMST();
    
    
    vector<pair<int,pair<int,int> > >::iterator poin;
    for (poin= g.MST.begin(); poin!= g.MST.end(); ++poin){
        
        t1=poin->second.first;
        t2=poin->second.second;
        t3=poin->first;
        cout << t1 << "\t" << t2 << endl;
        adj[t1-1].push_back({t2, t3});
        adj[t2-1].push_back({t1, t3});
    }
    
    node = V/2;
    
    parent[node]=NULL;
   
    g.printMST();
    vector<pair<int,int> >::iterator p;
   // for ( int i=0; i<V; i++){
        
   //     for (p = adj[i].begin(); p!= adj[i].end(); ++poin)
  //          cout << p->first << "\t";
   // }
    
    countchildren ( children, parent, adj, node );
    
    
    
    node = V/2;
    cout << node << endl;
    parent[node]=NULL;
    children[node]=V-1;
    //for ( int i=0; i<V;i++) cout << children[i]<< endl;
    for (poin= g.MST.begin(); poin!= g.MST.end(); ++poin){
        
        t1=poin->second.first;
        t2=poin->second.second;
        t3=poin->first;
    
        if( parent[t1] == t2) // δλδ ο τ2 πατερας
            powerof2[t3]= ( V - children[t1]-1 ) * ( children[t1]+1);
        else if ( parent[t2] == t1 ) // δλδ τ1 πατερας
            powerof2[t3]= ( V -  children[t2]-1 ) * ( children[t2]+1);
    }
    
    int c=0;
    bintodec (powerof2, E, c);
    cout << endl;
    
    
    return 0;
}


void countchildren( int *children, int *parent, vector < pair<int ,int> > adj[], int node ){
    
    vector<pair<int,int>>::iterator it_f;
    vector<pair<int,int>>::iterator it;
    
    for (it_f = adj[node].begin(); it_f != adj[node].end(); ++it_f){

        it = it_f;
        int tp=it -> first;
        cout << tp << "\n";
  
        
        /* cout << tp << endl;
        
        
        if ( adj[ tp ].size()==1 ){
            children[ tp ] = 0;
            parent[ tp ]= node;
        }
        else {
            countchildren ( children, parent, adj, tp );
            children[node] = children[ tp ] +1;
        }
        if ( parent[tp] == 0 ) parent[tp]= node;
        */
    }
}


void o_f( int t ){
    
    if ( t == 0 ) return;
    else if (t == 1){
        cout << 1;
        return;
    }
    else {
        o_f ( t/2 );
        cout << t% 2;
        return;
    }
        
}
    
    



void bintodec ( int a[] , int m, int c){
    
    
    if (c < m-1){
        
        a[c+1] = a[c]/2 + a[c+1];
        bintodec ( a, m, c+1  );
        cout << a[c] % 2;
    }
    if ( c == m-1){
        int temp = a[c];
        o_f( temp );
    }
    
    return;
}
    
