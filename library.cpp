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