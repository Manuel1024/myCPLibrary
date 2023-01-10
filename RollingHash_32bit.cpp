/*
    文字列 S の RollingHash を扱う構造体
    hash(s[0, i)) := s_0*b^0 + s_1*b^1 + ... + s_(i-1)*b^(i-1)
    b は基数 [300, MOD) から乱択
    32bit の mod 2つver

    RollingHash hs(s) 文字列 s の RollingHashを構築 基数 b1, b2 は乱択
    RollingHash hs(s, b1, b2) 文字列 s の RollingHashを構築 基数 b1, b2 はこちらで指定

    get(l, r) s[l, r) の hash を取得
    hash(s, base, mod) 文字列 s の RollingHashを返す 基数 base, 法 mod
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
    static constexpr ll MOD1 = 998244353;
    static constexpr ll MOD2 = 1000000007;

    const ll b1, b2;
    const vector<ll> hs1, hs2;
    const vector<ll> rev1, rev2;
    RollingHash(const string &s): b1(rnd()), b2(rnd()),
    hs1(hash(s, b1, MOD1)), hs2(hash(s, b2, MOD2)),
    rev1(make_revlist(s.size(), b1, MOD1)), rev2(make_revlist(s.size(), b2, MOD2)){}
    RollingHash(const string &s, ll b1, ll b2): b1(b1), b2(b2),
    hs1(hash(s, b1, MOD1)), hs2(hash(s, b2, MOD2)),
    rev1(make_revlist(s.size(), b1, MOD1)), rev2(make_revlist(s.size(), b2, MOD2)){}

    // hash1(s[l, r)), hash2(s[l, r))
    pair<ll, ll> get(int l, int r){
        return {
            (hs1[r]-hs1[l]+MOD1)%MOD1*rev1[l]%MOD1,
            (hs2[r]-hs2[l]+MOD2)%MOD2*rev2[l]%MOD2
        };
    }

    vector<ll> hash(const string &s, const ll base, const ll mod){
        vector<ll> hs(s.size()+1);
        ll bm1 = 1;
        for(int i = 0; i < s.size(); i++){
            hs[i+1] = (hs[i]+bm1*s[i])%mod;
            bm1 *= base;
            bm1 %= mod;
        }
        return hs;
    }
private:
    static constexpr int bmin = 300;
    
    // 逆元の前計算
    vector<ll> make_revlist(int n, const ll base, const ll mod){
        vector<ll> rev(n);
        ll bm = 1;
        for(int i = 0; i < n; i++){
            rev[i] = mpow(bm, mod-2, mod);
            bm *= base;
            bm %= mod;
        }
        return rev;
    }
    ll rnd(){
        mt19937 mt{1UL * chrono::steady_clock::now().time_since_epoch().count()};
        return mt()%(MOD1-bmin)+bmin;
    }
    
    ll mpow(ll a, ll x, const ll mod){
        ll res = 1;
        for(; x > 0; x >>= 1){
            if(x & 1){
                res *= a;
                res %= mod;
            }
            a *= a;
            a %= mod;
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
    vector<RollingHash> hc;
    for(auto &it: c) hc.emplace_back(it, hs.b1, hs.b2);

    ll ans = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j+c[i].size() <= s.size(); j++){
            if(hs.get(j, j+c[i].size()) == hc[i].get(0, c[i].size())){
                // cerr << i << " " << j << endl;
                ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}