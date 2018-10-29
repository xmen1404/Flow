/*
    author: JioFell
    ahihi
*/
#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
typedef pair<int, int> ii;
const int N = 270;
const int mod = 1e9;
const int oo = 1e9;

struct edge{
    int v, flow, cap, cost, rev;
};

int n, m, sink, source, tmp;
vector<edge> vi[N];
int dist[N], ans[N];
bool inqueue[N];
ii po[N], comp[N], pr[N];

void addeg(int u, int v, int cap, int cost) {
    edge A = {v, 0, cap, cost, vi[v].size()};
    edge B = {u, 0, 0, -cost, vi[u].size() };
    vi[u].pb(A); vi[v].pb(B); // ahihi
}

bool ford()    {
    FOR(i, source, sink + 1) {
        dist[i] = oo; inqueue[i] = false;
    }
    dist[source] = 0;
    // memset
    queue<int> pq;
    pq.push(source); inqueue[source] = true;
    // run queue, we use inqueue to minimize the times we need to push the items when we find a optimis one
    while(!pq.empty())  {
        int u = pq.front(); pq.pop();
        inqueue[u] = false;
        for(int i = 0; i < vi[u].size(); ++i)   {
            auto v = vi[u][i];
            if(dist[v.v] > dist[u] + v.cost && v.flow < v.cap) {
                dist[v.v] = dist[u] + v.cost;
                pr[v.v] = ii(u, i);
                if(!inqueue[v.v]) pq.push(v.v), inqueue[v.v] = true;
            }
        }
    }
    return dist[sink] != oo;
}

void MaxFlow()  {
    int flow = oo, cur = sink;
    while(cur != source)    {
        ii nex = pr[cur];
        flow = min(flow, vi[nex.fi][nex.se].cap - vi[nex.fi][nex.se].flow);
        cur = nex.fi;
    }
    cur = sink;
    while(cur != source)    {
        ii nex = pr[cur];
        vi[nex.fi][nex.se].flow += flow;
        vi[cur][ vi[nex.fi][nex.se].rev ].flow -= flow;
        cur = nex.fi;
    }
}

int MinCost()  {
    int mincost = 0;
    while(ford())   {
        MaxFlow();
    }
    for(int i = 1; i <= n; ++i) {
        for(auto v: vi[i]) if(v.v != source && v.flow > 0 && v.cap > 0)  {
            ans[i] = v.v - n;
            //cout << i << ' ' << v.v - n << ' ' << v.flow << ' ' << v.cost << '\n';
            mincost += v.flow * v.cost;
            break;
        }
    }
    return mincost;
}
int get(ii x, ii y) { return (x.fi - y.fi) * (x.fi - y.fi) + (x.se - y.se) * (x.se - y.se); }
signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> m >> n;
    sink = m + n + 1; source = 0; tmp = n + m + 2;

    int maxn = n / m, rem = n % m;
    for(int i = 1; i <= m; ++i) {
        cin >> po[i].fi >> po[i].se;
        addeg(i + n, sink, maxn, 0);
        addeg(i + n, tmp, 1, 0);
    }
    addeg(tmp, sink, rem, 0);

    for(int i = 1; i <= n; ++i) {
        cin >> comp[i].fi >> comp[i].se;
        addeg(source, i, 1, 0);
        FOR(j, 1, m) {
            int dist = get(comp[i], po[j]);
            addeg(i, j + n, 1, dist);
        }
    }

    cout << MinCost() << '\n';
    FOR(i, 1, n) cout << ans[i] << ' ';
}
