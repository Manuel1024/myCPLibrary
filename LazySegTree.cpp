/*
    Lazy Segment Tree
    1点更新 区間作用 区間取得
    数列a(a[0], a[1], ..., a[n-1])に対してなにかする
    呼び出すときは 0-indexed

    渡すもの
    S: 管理するデータの型
    S op(S x, S y): 二項演算 max, min, 足し算 他
    S e(): 単位元
    F: 作用の型
    S mapping(F f, S x): 作用 x = f(x)
    F composition(F f, F g): 作用の合成 h = f * g fは後から追加するもの gはすでに追加済みのもの
    F id(): id(x) = x となる恒等写像

    set(ind, x): a[ind] = x
    get(ind): a[ind] を取得
    query(l, r): op(a[l], a[l+1], ..., a[r-1]) を計算
    apply(ind, f): a[ind] = f(a[ind])
    apply(l, r, f): 区間 [l, r) に対して 作用 f を適用
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr ll MOD = 998244353;

// composition(後から追加, 追加済み)
template<
    class S, S (*op)(S, S), S(*e)(),
    class F, S (*mapping)(F, S), F (*composition)(F, F), F(*id)()> class LazySegTree{
private:
    int n;
    int h;
    vector<S> data;
    vector<F> lazy;

    void all_apply(int ind, F f){
        data[ind] = mapping(f, data[ind]);
        if(ind < n) lazy[ind] = composition(f, lazy[ind]);
    }

    void push(int ind){
        all_apply(ind<<1|0, lazy[ind]);
        all_apply(ind<<1|1, lazy[ind]);
        lazy[ind] = id();
    }

    void update(int ind){
        data[ind] = op(data[ind<<1|0], data[ind<<1|1]);
    }
public:
    LazySegTree(int sz){
        n = 1;
        h = 1;
        while(n < sz){
            n <<= 1;
            h++;
        }
        data = vector<S>(n*2, e());
        lazy = vector<F>(n, id());
    }

    void set(int ind, S x){
        ind += n;
        for(int lg = h-1; lg > 0; lg--) push(ind>>lg);
        data[ind] = x;
        for(int lg = 1; lg < h; lg++) update(ind>>lg);
    }

    S get(int ind){
        ind += n;
        for(int lg = h-1; lg > 0; lg--) push(ind>>lg);
        return data[ind];
    }

    S query(int l, int r){
        l += n; r += n;
        S lres = e(), rres = e();
        for(int lg = h-1; lg > 0; lg--){
            if(((l>>lg)<<lg) != l) push(l>>lg);
            if(((r>>lg)<<lg) != r) push((r-1)>>lg);
        }
        while(l < r){
            if(l&1){
                lres = op(lres, data[l]);
                l++;
            }
            if(r&1){
                r--;
                rres = op(data[r], rres);
            }
            l >>= 1;
            r >>= 1;
        }
        return op(lres, rres);
    }

    void apply(int ind, F f){
        ind += n;
        for(int lg = h-1; lg > 0; lg--) push(ind>>lg);

        data[ind] = mapping(f, data[ind]);

        for(int lg = 1; lg < h; lg++) update(ind>>lg);
    }

    void apply(int l, int r, F f){
        l += n; r += n;
        for(int lg = h-1; lg > 0; lg--){
            if(((l>>lg)<<lg) != l) push(l>>lg);
            if(((r>>lg)<<lg) != r) push((r-1)>>lg);
        }
        int l2 = l, r2 = r;
        while(l2 < r2){
            if(l2&1){
                all_apply(l2, f);
                l2++;
            }
            if(r2&1){
                r2--;
                all_apply(r2, f);
            }
            l2 >>= 1;
            r2 >>= 1;
        }
        for(int lg = 1; lg < h; lg++){
            // data[ind>>lg] = op(data[(ind>>lg)<<1|0], data[(ind>>lg)<<1|1]);
            if(((l>>lg)<<lg) != l) update(l>>lg);
            if(((r>>lg)<<lg) != r) update((r-1)>>lg);
        }
    }
};

struct S{
    ll tot;
    int len;
};

struct F{
    ll b, c;
};

S op(S x, S y){
    return {(x.tot+y.tot)%MOD, x.len+y.len};
}

S e(){
    return {0, 0};
}

S mapping(F f, S d){
    return {(d.tot*f.b%MOD+f.c*d.len%MOD)%MOD, d.len};
}

F composition(F f, F g){
    return {f.b*g.b%MOD, (g.c*f.b%MOD+f.c)%MOD};
}

F id(){
    return {1, 0};
}

int main(){
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(auto &it: a) cin >> it;
    LazySegTree<S, op, e, F, mapping, composition, id> st(n);
    for(int i = 0; i < n; i++) st.set(i, {a[i], 1});
    for(int turn = 0; turn < q; turn++){
        int tp; cin >> tp;
        if(tp == 0){
            int l, r, b, c; cin >> l >> r >> b >> c;
            st.apply(l, r, {b, c});
        }else{
            int l, r; cin >> l >> r;
            cout << st.query(l, r).tot << '\n';
        }
    }
    return 0;
}