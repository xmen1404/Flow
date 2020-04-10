#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define FORW(a, b, c) for(int a = b; a >= c; --a)
#define fi first
#define se second
#define pb push_back
//#define int long long

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

const int N = 1e3 + 10;
const int maxN = 6e6;
const int oo = 1e9;
const int mod  = 1e9 + 7;

struct Maxflow {
    int n, m, source, sink;
    struct edge {
        int flow, cap, v, rev;
    };

    vector< vector<edge> > vi;
    vector<int> dist, ptr;

    Maxflow(int n = 0, int m = 0, int source = 0, int sink = 0) :n(n), m(m), source(source), sink(sink) {
        vi.assign(n + 1, vector<edge>() );
        dist.assign(n + 1, 0), ptr.assign(n + 1, 0);
    }

    void addeg(int u, int v, int cap) {
        edge A = {0, cap, v, vi[v].size()};
        edge B = {0, 0, u, vi[u].size()};
        vi[u].pb(A); vi[v].pb(B);
    }

    bool bfs() {
        FOR(i, 0, n) dist[i] = -1, ptr[i] = 0;
        dist[source] = 0;
        queue<int> pq; pq.push(source);
        while(!pq.empty()) {
            int u = pq.front(); pq.pop();
            for(auto v: vi[u]) if(v.cap > v.flow && dist[v.v] == -1) {
                dist[v.v] = dist[u] + 1;
                pq.push(v.v);
            }
        }
        return dist[sink] != -1;
    }
    void modify(edge &uv, int val) {
        uv.flow += val;
        vi[uv.v][uv.rev].flow -= val;
    }

    int find(int u, int flow) {
        if(!flow || u == sink) return flow;
        for(int &i = ptr[u]; i < vi[u].size(); ++i) {
            auto v = vi[u][i];
            if(v.cap > v.flow && dist[v.v] == dist[u] + 1) {
                int cur = find(v.v, min(flow, v.cap - v.flow));
                if(cur) {
                    modify(vi[u][i], cur);
                    return cur;
                }
            }
        }
        return 0;
    }
    int solve() {
        int res = 0;
        while(bfs()) {
            int tmp = find(source, oo);
            while(tmp) res += tmp, tmp = find(source, oo);
        }
        return res;
    }
} mf;

signed main()  {
//    freopen("test.inp", "r", stdin);
//    freopen("spm.out", "w", stdout);
    ios_base::sync_with_stdio(false); cout.tie(0);
    int n, m, s, t; cin >> n >> m >> s >> t;
    mf = Maxflow(n, m, s, t);
    FOR(i, 1, m) {
        int u, v, cap; cin >> u >> v >> cap;
        mf.addeg(u, v, cap);
    }
    cout << mf.solve();
}
