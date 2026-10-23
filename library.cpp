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
