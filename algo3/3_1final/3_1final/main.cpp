#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

void numberOfNodes(int s, int e, int *children[], int *parent[], vector<int> *adj);
vector<vector <int> >adj;

void o_f( int t );
void bintodec ( int a[] , int m, int c, bool *started);

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
        void makeGL(vector< int> *adj, vector< int> *weight);
};

Graph::Graph(int V,int E){
    this->V = V;
    this->E = E;
}

void Graph::addEdge(int u,int v,int w){
    edges.push_back({w,{u,v}});

}

void Graph::makeGL(vector< int> *adj, vector< int> *weight){
    
    vector<pair<int,pair<int,int> > >::iterator it;
    for ( it = MST.begin(); it!=MST.end(); it++){
        
        adj[it->second.first].push_back(it->second.second);
        weight[it->second.first].push_back( it->first);
        
        
        adj[it->second.second].push_back(it->second.first);
        weight[it->second.second].push_back( it->first);
        
    }
    
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
/*void CountChildrenofMST(int *children[], int *parent[], int node, vector<vector<pair<int, int>>> adj, int V){
    
    
    (*visited)[node] = true;
    bool visited[V];
    for ( int i=0; i<V )
    
    for ( int i =0; i<adj.at(node).size(); i++){
        if ( (*visited)[adj.at(node).at(i)]== false]
        
    
            
        }
    }
    return;
}
*/

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
    return;
}

int main(){
    int V, E, node, temp1;
  //  cout << "Number of vertices: "<< endl;
    cin>>V;
   // cout << "Number of edges: "<< endl;
    cin>>E;
    Graph g(V,E);
    int u,v,w;
    for(int i=0;i<E;i++){
        cin >> u >> v >> w;
        g.addEdge(u,v,w);
    }
    
    vector <int>adj[V+1];
    vector <int>weight[V+1];
    int *children, *parent;
    children= new int[V+1];
    parent= new int [V+1];
   
    for ( int i=0; i<V+1; i++){
        children[i]= 0;
        parent[i]=0;
    }
    
    node = V/2;
    
    g.kruskalMST();
    g.makeGL(adj, weight);
    
   /* for ( int i=0;i<V;i++){
        vector<int>::iterator k;
        for ( k = adj[i].begin(); k!=adj[i].end(); ++k)
            cout << *k << "\t";
        cout << endl;
    }
    */
    
    numberOfNodes(node, 0, &children, &parent, adj);
    

    
  /*  for (int i=1; i<V+1;i++){
        
        cout << "ο κομβος "<< i << " συνδεεται με τους κομβους :\n";
        
        for ( it = adj.at(i).begin(); it!=adj.at(i).end(); ++it){
            
            cout << it-> first << "\t";
        }
        cout << endl;
    }
   */
    
    
    int *a;
    a = new int [E];
    for ( int i=0; i <E; i++) a[i]=0;

    
    
    
    for ( int i=1; i<V+1; i++){
        vector <int>::iterator it;
        int c=0;
        for ( it= adj[i].begin(); it !=adj[i].end(); ++it){
            w = weight[i][c];
            c++;
            if ( parent[*it]==i)
                a[w] = (children[*it])*(V-children[*it]);
            else
                a[w] = ( children[i])*(V-children[i]);
        }
    }
 
            
    
    
    
 /*   for ( int i=0; i<E; i++){
        cout << "o kombos "<< i << " εχει πατερα τον " << parent[i] << endl;
    }
    for ( int i=0; i<E; i++){
        cout << a[i] << "\t";
        
    }
  */
    
    int c=0;
    bool started = false;
    
    bintodec (a, E, c, &started);
    cout << endl;
        
        

    
    return 0;
}




void numberOfNodes(int s, int e, int *children[], int *parent[], vector<int> *adj)
{
    
    (*children)[s] = 1;
    (*parent)[s]=e;
   // cout << "3ekinaei h synarthsh gia kombo " << s<< endl;
    vector<int>::iterator u;
    for ( u = adj[s].begin(); u != adj[s].end(); ++u) {
        
       // cout << "mphka" << endl;
        // condition to omit reverse path
        // path from children to parent
        
        if (*u  == e)
            continue;
          
        // recursive call for DFS
        numberOfNodes(*u, s, children, parent, adj);

        
        
          
        // update count[] value of parent using
        // its children
        (*children)[s] += (*children)[*u];
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
    
    



void bintodec ( int a[] , int m, int c,bool *started){
    
    
    if (c < m-1){
        
        a[c+1] = a[c]/2 + a[c+1];
        bintodec ( a, m, c+1, started);
        if ( *started == true)
            cout << a[c]%2;
        else if ( a[c]%2 == 0 && *started == false ) return;
        else{
            (*started) = true;
            cout << a[c] % 2;
        }
    }
    if ( c == m-1){
        
        if (a[c]>1){
            int temp = a[c];
            o_f( temp );
            *started = true;
        }
        else if (a[c]==1){
            cout << 1;
            *started = true;
        }
    }
    
    return;
}
    






