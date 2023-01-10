/*
    Binary Indexed Tree(Fenwick tree)
    数列a(a[0], a[1], ..., a[n-1])の区間和を計算できる
    呼び出すときは0-indexed
    初期値は a[0] = a[1] = ... = a[n-1] = 0
    add(ind, x): a[ind] += x（値の更新）
    sum(start, end): a[start]+a[start+1]+...+a[end-1]を計算 [start, end)
    sum_sub(end): a[0]+a[1]+...+a[end-1]を計算 [0, end)
    lower_bound(w): a[0]+a[1]+...+a[x] >= w となるような最小のxを返す
    内部実装は1-indexed
    区間は半開区間 [l, r)
    sum_subとaddで引数を1-indexedに合わせる
*/
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

template <typename T>
struct FenwickTree{
    const int n;
    vector<T> arr;
    FenwickTree() = default;
    FenwickTree(int n): n(n), arr(vector<T>(n+1, 0)){}

    void add(int ind, T x){
        for(int i = ind+1; i <= n; i += i & (-i)){
            arr[i] += x;
        }
    }

    T sum_sub(int end){
        T res = 0;
        for(int i = end; i > 0; i -= i & (-i)){
            res += arr[i];
        }
        return res;
    }

    T sum(int start, int end){
        return sum_sub(end) - sum_sub(start);
    }

    int lower_bound(T w){
        if(w <= 0) return 0;
        int x = 0;
        int k = 1 << 30;
        while(k > n) k /= 2;
        for(; k > 0; k /= 2){
            if(x+k <= n && arr[x+k] < w){
                w -= arr[x+k];
                x += k;
            }
        }
        return x;
    }
};

// https://yukicoder.me/problems/no/833
int main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &it: a) cin >> it;
    FenwickTree<ll> sum(n);
    for(int i = 0; i < n; i++) sum.add(i, a[i]);
    FenwickTree<int> range(n);
    for(int i = 1; i < n; i++) range.add(i, 1);
    while(q--){
        int op, x;
        cin >> op >> x;
        --x;
        if(op == 1){
            if(range.sum(x+1, x+2) == 1) range.add(x+1, -1);
        }else if(op == 2){
            if(range.sum(x+1, x+2) == 0) range.add(x+1, 1);
        }else if(op == 3){
            sum.add(x, 1);
        }else{
            int r = range.lower_bound(range.sum(0, x+1)+1);
            int l = range.lower_bound(range.sum(0, x+1));
            cout << sum.sum(l, r) << '\n';
        }
    }
    return 0;
}