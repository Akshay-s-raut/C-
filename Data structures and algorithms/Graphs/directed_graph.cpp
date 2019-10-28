#include<iostream>
#include<vector>
#include<map>
#include<string>
#include <set>
#include <iomanip>
#include <stack>
#include<queue>
#include <algorithm>
using namespace std;

typedef pair<int,int> ipair;
class Directed_Graph{
    private:
        map<int ,vector<int>> G;
        map <vector<int>,int> W;

    public:
        void insert(int node1,int node2,int weight=1){
            if(G.find(node1)==G.end()){
                G[node1].push_back(node2);
            }
            else{
                if(G[node1][0]!=-1){
                    G[node1].push_back(node2);
                }
                else{
                    G[node1][0]=node2;
                }
            }
            if(G.find(node2)==G.end()){
                G[node2].push_back(-1);
            }
            vector<int> s;
            s.push_back(node1);
            s.push_back(node2);
            W[s]=weight;
        }

        friend ostream& operator<<(ostream& os,Directed_Graph g){
           for(int i=0;i<g.G.size();++i){
                os<<i<<setw(3)<<"  "<<"< ";
                int s = g.G[i].size();
                for(int j=0;j<g.G[i].size();++j){
                    if(j==g.G[i].size()-1){
                        os<<g.G[i][j]<<"("<<g.W[vector<int>{i,g.G[i][j]}]<<")"<<" >"<<endl;
                        break;
                    }
                    os<<g.G[i][j]<<"("<<g.W[vector<int>{i,g.G[i][j]}]<<"), ";
                }
            }
            return os;
        }

        void DFS(int node){
            vector<bool> visited;
            for(int i=0;i<G.size();++i){
                visited.push_back(false);
            }
            stack<int> s;
            s.push(node);
            visited[node]=true;
            int start = node;
            cout<<node<<" ";
            while(true){
                int i=0;
                while(true){
                    if(i>=G[start].size() || G[start][0]==-1){
                        break;
                    }
                    //cout<<start<<" "<<G[start][i]<<endl;  //Just to test;
                    if(!visited[G[start][i]]){
                        visited[G[start][i]]=true;
                        s.push(G[start][i]);
                        start=s.top();
                        cout<<s.top()<<" ";         //do something; 
                        i=0;
                        continue;
                    }
                    i++; 
                }
                s.pop();
                if(s.empty()){
                    break;
                }
                start=s.top();
            }
        }

        void BFS(int node){
            vector<bool> visited;
            for(int i=0;i<G.size();++i){
                visited.push_back(false);
            }
            queue<int> q;
            q.push(node);
            int start = node;
            cout<<start<<" ";
            while(true){
                for(int i=0;i<G[start].size();++i){
                    if(G[start][0]==-1){
                        break;
                    }
                    if(!visited[G[start][i]]){
                        visited[G[start][i]]=true;
                        cout<<G[start][i]<<" ";   //Do something;
                        q.push(G[start][i]);
                    }
                }
                q.pop();
                if(q.empty()){
                    break;
                }
                start=q.front();
            }
        }

        void Dijkstra(int source,int destination){
            vector<bool> visited;
            vector<int> shortest;
            //map<int,vector<int>> path;
            for(int i=0;i<G.size();++i){
                visited.push_back(false);
                shortest.push_back(2147483647);
            }
            shortest[source]=0;

           priority_queue<ipair,vector <ipair>,greater<ipair>> pq;
           pq.push(make_pair(shortest[source],source));
           while(!pq.empty()){
               int start = pq.top().second;
               pq.pop();
               for(int i=0;i<G[start].size();++i){
                   if(G[start][0]==-1){
                        break;
                    }
                   if(shortest[G[start][i]] > W[vector<int>{start,G[start][i]}] + shortest[start]){
                       shortest[G[start][i]] = W[vector<int>{start,G[start][i]}] + shortest[start];
                       pq.push(make_pair(shortest[G[start][i]],G[start][i]));
                   }
               } 
           }

           for(int i=0;i<shortest.size();++i){
               cout<<i<<" "<<shortest[i]<<endl;
           }
           cout<<"shortest Distance : "<<shortest[destination];

        }

        
};

int main(){
    Directed_Graph G;
    G.insert(0,1,3);
    G.insert(0,2);
    G.insert(2,3);
    G.insert(2,4);
    G.insert(1,3);
    G.insert(0,5);
    G.insert(3,4);
    cout<<G;
    cout<<"DFS: ";
    G.DFS(0);
    cout<<endl;
    cout<<"BFS: ";
    G.BFS(0);
    cout<<"\nDone\n";
    G.Dijkstra(0,3);
}
