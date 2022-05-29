/*
    Maximum Flow(Dinic)
    フローネットワークで始点sから終点tまでの最大流を導く
    MaxFlowGraph<type> G(n) nは頂点数
    G.add_edge(from, to, cap) fromからtoへの辺を張る　容量cap
    G.flow(s, t) 始点sから終点tまでの最大流を導く
    G.min_cut(s) res[i] := 頂点sから頂点iへ残余グラフで到達できるか？ 最小カット復元
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

template<class T>
class MaxFlowGraph{
private:
    struct Edge{
        int to;
        T cap;
        int rev;
        Edge(int to, T cap, int rev): to(to), cap(cap), rev(rev){}
    };
    using graph = vector<vector<Edge>>;
    graph G;
    vector<bool> used;
    vector<int> level;
    vector<int> iter;

public:
    MaxFlowGraph(int n){
        G = graph(n);
        used = vector<bool>(n, false);
        level = vector<int>(n);
        iter = vector<int>(n);
    }

    void add_edge(int from, int to, T cap){
        G[from].emplace_back(to, cap, (int)G[to].size());
        G[to].emplace_back(from, 0, (int)G[from].size()-1);
    }

    void bfs(int s){
        fill(level.begin(), level.end(), -1);
        queue<int> Q;
        level[s] = 0;
        Q.emplace(s);
        while(Q.size()){
            int v = Q.front(); Q.pop();
            for(int i = 0; i < G[v].size(); i++){
                auto &e = G[v][i];
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    Q.emplace(e.to);
                }
            }
        }
    }

    T dfs(int v, int t, T f){
        if(v == t) return f;
        for(int &i = iter[v]; i < G[v].size(); i++){
            auto &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]){
                T d = dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    T flow(int s, int t){
        const T INF = 1001001001;
        T maxflow = 0;
        while(true){
            bfs(s);
            if(level[t] < 0) return maxflow;
            fill(iter.begin(), iter.end(), 0);
            T f;
            while((f = dfs(s, t, INF)) > 0) maxflow += f;
        }
    }

    vector<bool> min_cut(int s){
        vector<bool> res(G.size(), false);
        res[s] = true;
        queue<int> Q;
        Q.emplace(s);
        while(!Q.empty()){
            int c = Q.front(); Q.pop();
            for(auto &nex: G[c]){
                if(nex.cap > 0 && !res[nex.to]){
                    res[nex.to] = true;
                    Q.emplace(nex.to);
                }
            }
        }
        return res;
    }
};

// AOJ GRL 6_A Maximum Flow
int main(){
    int v, e;
    cin >> v >> e;
    MaxFlowGraph<long long> G(v);
    for(int i = 0; i < e; i++){
        int u, v, c;
        cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    cout << G.flow(0, v-1) << endl;
    return 0;
}