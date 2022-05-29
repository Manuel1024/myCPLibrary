/*
    二項係数を計算する構造体
    Combination comb;// 構造体をつくる
    comb(n, r);// nCr を計算
    デフォでは n <= 1000000 (10^6)
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr ll MOD = 998244353;

struct Combination{
    using ll = long long;
    const int n;
    // const int MOD = 998244353;
    vector<ll> fac, ifac;
    ll mp(ll a, ll x) const {
        ll res = 1;
        for(; x > 0; x >>= 1){
            if(x&1){
                res *= a; res %= MOD;
            }
            a *= a; a %= MOD;
        }
        return res;
    }
    Combination(int _n = 1000000): n(_n), fac(vector<ll>(_n+1)), ifac(vector<ll>(_n+1)){
        fac[0] = 1;
        for(int i = 1; i <= n; i++) fac[i] = (fac[i-1]*i)%MOD;
        ifac[n] = mp(fac[n], MOD-2);
        for(int i = n; i > 0; i--) ifac[i-1] = (ifac[i]*i)%MOD;
    }

    ll operator()(int n, int k) const {
        if (k < 0 || k > n) return 0;
        return fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
    }
};

// AGC 025 B - RGB Coloring
int main(){
    ll n, a, b, k;
    cin >> n >> a >> b >> k;
    ll ans = 0;
    Combination comb;
    for(int x = 0; x <= n; x++){
        if((k-a*x)%b != 0 || k-a*x < 0 || n < (k-a*x)/b) continue;
        ll y = (k-a*x)/b;
        ans += comb(n, x)*comb(n, y)%MOD;
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}