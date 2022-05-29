/*
    Binary Indexed Tree(Fenwick tree)
    数列a(a[0], a[1], ..., a[n-1])の区間和を計算できる
    呼び出すときは0-indexed
    初期値は a[0] = a[1] = ... = a[n-1] = 0
    add(ind, x): a[ind] += x（値の更新）
    sum(start, end): a[start]+a[start+1]+...+a[end-1]を計算 [start, end)
    sum_sub(end): a[0]+a[1]+...+a[end-1]を計算 [0, end)
    内部実装は1-indexed
    区間は半開区間 [l, r)
    sum_subとaddで引数を1-indexedに合わせる
*/
#include <iostream>
#include <vector>
using namespace std;

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

    // [0, end)
    T sum_sub(int end){
        T res = 0;
        for(int i = end; i > 0; i -= i & (-i)){
            res += arr[i];
        }
        return res;
    }

    // [start, end)
    T sum(int start, int end){
        return sum_sub(end) - sum_sub(start);
    }
};

// https://judge.yosupo.jp/problem/point_add_range_sum
int main(){
    int n, q;
    cin >> n >> q;
    FenwickTree<long long int> ft(n);
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        ft.add(i, a);
    }
    while(q--){
        int op;
        cin >> op;
        if(op == 0){
            int p, x;
            cin >> p >> x;
            ft.add(p, x);
        }else{
            int l, r;
            cin >> l >> r;
            cout << ft.sum(l, r) << '\n';
        }
    }
    return 0;
}