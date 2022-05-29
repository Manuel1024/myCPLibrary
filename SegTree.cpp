/*
    Segment Tree
    1点更新 区間取得
    数列a(a[0], a[1], ..., a[n-1])に対してなにかする
    呼び出すときは 0-indexed

    渡すもの
    S: 管理するデータの型
    S op(S x, S y): 二項演算 max, min, 足し算 他
    S e(): 単位元

    set(ind, x): a[ind] = x
    get(ind): a[ind] を取得
    query(l, r): op(a[l], a[l+1], ..., a[r-1]) を計算
*/
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

template<class S, S (*op)(S, S), S(*e)()> class SegTree{
private:
    int n;
    vector<S> arr;
public:
    SegTree(int sz){
        n = 1;
        while(n < sz) n <<= 1;
        arr = vector<S>(n*2, e());
    }

    void set(int ind, S x){
        ind += n;
        arr[ind] = x;
        while(ind > 1){
            ind >>= 1;
            arr[ind] = op(arr[ind<<1|0], arr[ind<<1|1]);
        }
    }

    S get(int ind){
        return arr[ind+n];
    }

    S query(int l, int r){
        S lres = e(), rres = e();
        l += n; r += n;
        while(l < r){
            if(l&1){
                lres = op(lres, arr[l]);
                l++;
            }
            if(r&1){
                r--;
                rres = op(arr[r], rres);
            }
            l >>= 1;
            r >>= 1;
        }
        return op(lres, rres);
    }
};

ll add(ll a, ll b){
    return a+b;
}

ll e(){
    return 0;
}

// https://judge.yosupo.jp/problem/point_add_range_sum
int main(){
    int n, q; cin >> n >> q;
    SegTree<ll, add, e> st(n);
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        st.set(i, a);
    }
    while(q--){
        int op, x, y; cin >> op >> x >> y;
        if(op == 0) st.set(x, st.get(x)+y);
        else cout << st.query(x, y) << '\n';
    }
    return 0;
}