#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define FORW(a, b, c) for(int a = b; a >= c; --a)
#define fi first
#define se second
#define pb push_back
#define int long long

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

const int N = 2e3 + 100;
const int maxN = 1e16;
const int oo = 1e18;
const int mod  = 1e9 + 7;

struct Mincost {
    int n, source, sink;
    struct edge {
        int flow, cap, cost, v, rev;
    };
    vector< vector<edge> > vi;
    vector< ii > pr;
    vector<int> dist;
    vector<bool> inqueue;


    Mincost(int n = 0, int source = 0, int sink = 0) : n(n), source(source), sink(sink) {
        vi.assign(n + 2, vector<edge>() );
        pr.assign(n + 2, ii(0, 0));
        dist.assign(n + 2, 0);
        inqueue.assign(n + 2, 0);
    }
    void addeg(int u, int v, int cap, int cost) {
        edge A = {0, cap, cost, v, vi[v].size()};
        edge B = {0, 0, -cost, u, vi[u].size() };
        vi[u].pb(A); vi[v].pb(B);
    }

    bool find() {
        FOR(i, 0, n) dist[i] = oo, inqueue[i] = 0;
        dist[source] = 0;
        queue<int> pq; pq.push(source); inqueue[source] = 1;

        while(!pq.empty()) {
            int u = pq.front(); pq.pop();
            inqueue[u] = false;

            FOR(i, 0, vi[u].size() - 1) {
                auto v = vi[u][i];
                if(dist[v.v] > dist[u] + v.cost && v.cap > v.flow) {
                    dist[v.v] = dist[u] + v.cost;
                    pr[v.v] = {u, i};
                    if(!inqueue[v.v]) {
                        inqueue[v.v] = 1; pq.push(v.v);
                    }
                }
            }
        }
        return dist[sink] < oo;
    }

    void trace() {
        int flow = oo, cur = sink;
        while(cur != source) {
            int u = pr[cur].fi, id = pr[cur].se;
            flow = min(flow, vi[u][id].cap - vi[u][id].flow);
            cur = u;
        }
        cur = sink;
        while(cur != source) {
            int u = pr[cur].fi, id = pr[cur].se;
            vi[u][id].flow += flow;
            vi[ vi[u][id].v ][ vi[u][id].rev ].flow -= flow;
            cur = u;
        }
    }

    int solve() {
        while(find())  { trace();}
        int res = 0;
        FOR(i, 0, n) for(auto v: vi[i]) if(v.cost < 0 && v.flow > 0) {
            res -= v.cost * v.flow;
        }
        return res;
    }

} mc;

// S = y - 1
// N = y + 1
// E = x + 1
// W = x - 1

int a[N];

signed main()  {
//    freopen("test.inp", "r", stdin);
//    freopen("spm.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    FOR(i, 1, n) cin >> a[i];

    mc = Mincost(n + 2 + n, 0, n + n + 1);
    FOR(i, 1, n) FOR(j, 1, n) if(j != i)    {
        int val = a[i] * abs(i - j);
        mc.addeg(i, j + n, 1, -val);
    }
    FOR(i, 1, n) { mc.addeg(0, i, 1, 0); mc.addeg(i + n, n + n + 1, 1, 0); }
    cout << mc.solve();
}
