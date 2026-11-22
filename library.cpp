#include <iostream>
#include <string>
#include <array> 
#include <vector>  
#include <algorithm>
#include <sstream>
#include <utility>
#include <cmath>
#include <cstdlib> 
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <set>
#include <queue>
#include <iomanip>
#include <numeric>
#include <map>
#include <cctype>
#include <climits>
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define fori(i,n) for (int i = 0; i < (int)(n); i++)
#define forii(i,s,e) for (int i = s; i < (int)(e); i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vvc vector<vector<char>>
#define vs vector<string>
#define vb vector<bool>
#define vp vector<pair<ll, ll>> 
#define pq_pair priority_queue<pair<ll, ll>>
#define sort2(v) sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.second < b.second; })
#define rev(v) reverse(v.begin(), v.end())
#define sort_desc(v) sort(v.begin(), v.end(), greater<decltype(v[0])>())
ll INF=2e18;
const ll MOD = 1000000007LL;
//繰り返し2乗法
ll modpow(ll a,ll b,ll mod){
    ll ans=1;
    a%=mod;
    while (b>0)
    {
        if (b%2)
        {
            ans=ans*a%mod;
        }
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
//ダイクストラ(スタートとゴールあり)0((N+M)logN)
struct Edge
{
    ll to;
    ll cost;
};

ll dikstra(const vector<vector<Edge>>& graph,ll S, ll T)//スタートS,ゴールT
{
    ll N=(ll)graph.size()-1;
    vector<ll> dist(N+1,INF);
    priority_queue<pair<ll, ll>,vector<pair<ll, ll>>,greater<pair<ll, ll>>> pq;
    dist[S]=0;
    pq.push({0,S});
    while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();

    // 古い距離情報は無視
    if (d != dist[v]) continue;

    // 終点の最短距離が確定
    if (v == T) break;

    for (const auto& e : graph[v]) {
        ll nv = e.to;
        ll cost = e.cost;

        if (dist[nv] > d + cost) {
            dist[nv] = d + cost;
            pq.push({dist[nv], nv});
        }
        }
    }

    // 到達不能なら INF を返す
    return dist[T];
}
/*↑使用例

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, M, S, T;
    cin >> N >> M >> S >> T;

    // ① グラフを作る
    vector<vector<Edge>> graph(N + 1);

    // ② 辺を登録する
    for (ll i = 0; i < M; i++) {
        ll u, v, cost;
        cin >> u >> v >> cost;

        graph[u].push_back({v, cost});

        // 無向グラフの場合は逆向きも追加
        // graph[v].push_back({u, cost});
    }

    // ③ ライブラリを呼び出す
    ll ans = dijkstra(graph, S, T);

    // ④ 答えを出力する
    if (ans == INF) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}

*/

// a^b mod MOD
ll modpow(ll a, ll b) {
    ll res = 1;

    while (b > 0) {
        if (b & 1) {
            res = res * a % MOD;
        }

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

//nCrの計算ライブラリ
vector<ll> fact, invfact;
// 前計算：最大 N までの nCr に対応
void init_nCr(ll N) {
    fact.assign(N + 1, 1);
    invfact.assign(N + 1, 1);

    for (ll i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    invfact[N] = modpow(fact[N], MOD - 2);

    for (ll i = N; i >= 1; i--) {
        invfact[i - 1] = invfact[i] * i % MOD;
    }
}
ll nCr(ll n, ll r) {
    if (n < 0 || r < 0 || r > n) return 0;

    return fact[n] * invfact[r] % MOD
                 * invfact[n - r] % MOD;
}
//ここまで
//約数の個数ライブラリ(N<=10^12)
//前処理 O(√N log log √N)、1クエリ O(π(√N))≒約7.8万回
vl dc_primes;//√N以下の素数
void init_divisors(ll N = 1000000000000LL) {
    ll lim = (ll)sqrtl((ld)N);
    while (lim * lim < N) lim++;//lim=ceil(√N)
    vb is_prime(lim + 1, true);
    for (ll i = 2; i <= lim; i++) {
        if (!is_prime[i]) continue;
        dc_primes.push_back(i);
        for (ll j = i * i; j <= lim; j += i) is_prime[j] = false;
    }
}
//素因数分解 {(素数,指数)} を素数の昇順で返す
vp factorize(ll n) {
    if (dc_primes.empty()) init_divisors();//前処理し忘れ防止
    vp res;
    for (ll p : dc_primes) {
        if (p * p > n) break;
        if (n % p != 0) continue;
        ll e = 0;
        while (n % p == 0) { n /= p; e++; }
        res.push_back({p, e});
    }
    if (n > 1) res.push_back({n, 1});//残りは素数1つ
    return res;
}
//約数の個数 n=p1^e1*p2^e2*... のとき (e1+1)(e2+1)...
ll count_divisors(ll n) {
    ll res = 1;
    for (auto [p, e] : factorize(n)) res *= (e + 1);
    return res;
}
/*↑使用例

int main() {
    init_divisors();//最初に1回だけ(省略しても初回呼び出し時に自動実行)
    ll n;
    cin >> n;
    cout << count_divisors(n) << '\n';
    return 0;
}

*/
//ここまで
//素数判定(Miller-Rabin法・決定的版) 1回 O(log n)
//n<2^63 の範囲で正確。init_divisors() などの前処理は不要
//※既存の modpow は ll 同士の積でオーバーフローするため、__int128 版を別名で用意
ll modpow128(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}
bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }//n-1 = d * 2^s
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        ll x = modpow128(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int r = 1; r < s; r++) {
            x = (__int128)x * x % n;
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;//合成数と確定
    }
    return true;
}
/*↑使用例

int main() {
    ll n;
    cin >> n;
    if (is_prime(n)) Yes; else No;
    return 0;
}

*/