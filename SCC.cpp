/*
    強連結成分分解 Strongly Connected Components
    有向グラフを強連結成分分解するライブラリ

    SCC G(n) nは頂点数
    G.add_edge(from, to) fromからtoへの辺を張る
    G.scc() 強連結成分分解したグラフを表した「頂点のリスト」のリストを返す
        - 全ての頂点がちょうど1つずつ、どれかのリストに含まれます。
        - 内側のリストと強連結成分が一対一に対応します。リスト内での頂点の順序は未定義です。
        - リストはトポロジカルソートされています。異なる強連結成分の頂点 u, v について、u から v に到達できる時、
        - u の属するリストは v の属するリストよりも前です。
    （仕様はAtCoder Libraryと同様のはず）
    https://hcpc-hokudai.github.io/archive/graph_scc_001.pdf
    https://atcoder.github.io/ac-library/production/document_ja/scc.html
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SCC{
private:
    vector<vector<int>> G;
    vector<vector<int>> rG;
    vector<bool> visited;
    vector<int> vs;
    vector<int> cmp;

    void dfs1(int v){
        visited[v] = true;
        for(auto &nex: G[v]){
            if(visited[nex]) continue;
            dfs1(nex);
        }
        vs.emplace_back(v);
    }

    void dfs2(int v, int k){
        visited[v] = true;
        cmp[v] = k;
        for(auto &nex: rG[v]){
            if(visited[nex]) continue;
            dfs2(nex, k);
        }
    }
public:
    SCC(int n):
    G(vector<vector<int>>(n)), rG(vector<vector<int>>(n)),
    visited(vector<bool>(n, false)), cmp(vector<int>(n)) {}

    void add_edge(int from, int to){
        G[from].emplace_back(to);
        rG[to].emplace_back(from);
    }

    vector<vector<int>> scc(){
        for(int i = 0; i < G.size(); i++){
            if(!visited[i]) dfs1(i);
        }

        fill(visited.begin(), visited.end(), false);
        reverse(vs.begin(), vs.end());
        int k = 0;
        for(auto &it: vs){
            if(visited[it]) continue;
            dfs2(it, k);
            k++;
        }

        vector<vector<int>> res(k);
        for(int i = 0; i < G.size(); i++) res[cmp[i]].emplace_back(i);
        return res;
    }
};

// Library Checker Graph - Strongly Connected Components
int main(){
    int n, m; cin >> n >> m;
    SCC G(n);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        G.add_edge(a, b);
    }

    auto scc = G.scc();
    cout << scc.size() << '\n';
    for(auto &vec: scc){
        cout << vec.size();
        for(auto &x: vec) cout << " " << x;
        cout << '\n';
    }

    return 0;
}