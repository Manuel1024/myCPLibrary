/*
    文字列 S の RollingHash を扱う構造体
    hash(s[0, i)) := s_0*b^0 + s_1*b^1 + ... + s_(i-1)*b^(i-1)
    b は基数 [300, MOD) から乱択
    64bit の mod 1つver

    RollingHash hs(s) 文字列 s の RollingHashを構築 基数 b1 は乱択
    RollingHash hs(s, b1) 文字列 s の RollingHashを構築 基数 b1 はこちらで指定

    get(l, r) s[l, r) の hash を取得
    hash(s) 文字列 s の RollingHashを返す

    https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
using ll = long long;

struct RollingHash{
    static constexpr ll MOD = (1LL << 61)-1;

    const ll b1;
    const vector<ll> hs;
    const vector<ll> rev;
    RollingHash(const string &s): b1(rnd()), hs(hash(s)), rev(make_revlist(s.size())){}
    RollingHash(const string &s, ll b0): b1(b0), hs(hash(s)), rev(make_revlist(s.size())){}

    // hash(s[l, r))
    inline ll get(int l, int r){
        return Mul(calcMod(MOD+hs[r]-hs[l]), rev[l]);//(hs[r]-hs[l]+MOD)%MOD*rev[l]%MOD
    }

    vector<ll> hash(const string &s){
        vector<ll> hs(s.size()+1);
        hs[0] = 0;
        ll bm = 1;
        for(int i = 0; i < s.size(); i++){
            hs[i+1] = calcMod(hs[i]+Mul(bm, s[i]));
            bm = Mul(bm, b1);
        }
        return hs;
    }
private:
    static constexpr ll MASK31 = (1LL << 31)-1;
    static constexpr ll MASK30 = (1LL << 30)-1;
    static constexpr ll MASK61 = (1LL << 61)-1;
    static constexpr int bmin = 300;
    // a*b mod 2^61-1
    inline ll Mul(const ll a, const ll b){
        ll au = a >> 31;
        ll ad = a & MASK31;
        ll bu = b >> 31;
        ll bd = b & MASK31;
        ll mid = ad*bu + au*bd;
        ll midu = mid >> 30;
        ll midd = mid & MASK30;
        return calcMod(au*bu*2 + midu + (midd << 31) + ad*bd);
    }

    // x mod 2^61-1
    inline ll calcMod(ll x){
        ll xu = x >> 61;
        ll xd = x & MASK61;
        ll res = xu+xd;
        if(res >= MOD) res -= MOD;
        return res;
    }

    // 逆元の前計算
    vector<ll> make_revlist(int n){
        vector<ll> rev(n);
        ll bm = 1;
        for(int i = 0; i < n; i++){
            rev[i] = mpow(bm, MOD-2);
            bm = Mul(bm, b1);
        }
        return rev;
    }
    inline ll rnd(){
        mt19937_64 mt{1ULL * chrono::steady_clock::now().time_since_epoch().count()};
        return mt()%(MOD-bmin)+bmin;
    }
    inline ll mpow(ll a, ll x){
        ll res = 1;
        for(; x > 0; x >>= 1){
            if(x & 1){
                res = Mul(res, a);
            }
            a = Mul(a, a);
        }
        return res;
    }
};

// https://yukicoder.me/problems/no/430
int main(){
    string s; cin >> s;
    int m; cin >> m;
    vector<string> c(m);
    for(auto &it: c) cin >> it;

    RollingHash hs(s);

    ll ans = 0;
    for(int i = 0; i < m; i++){
        RollingHash hc(c[i], hs.b1);
        for(int j = 0; j+c[i].size() <= s.size(); j++){
            if(hs.get(j, j+c[i].size()) == hc.get(0, c[i].size())){
                ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}