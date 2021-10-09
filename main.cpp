#include "iostream"
#include "algorithm"
using namespace std;

int n, m, h[100005], edg_cnt, fa[100005], cnt, ans;

struct edge {
    int s, e, v;
    bool operator < (const edge &a) const {
        return v < a.v;
    }
} edg[1000005];

int get(int x) {
    return fa[x] = (fa[x] == x ? x : get(fa[x]));
}


int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        if (h[a] >= h[b]) {
            edg[edg_cnt] = (edge){a, b, c};
            edg_cnt++;
        } else {
            edg[edg_cnt] = (edge){b, a, c};
            edg_cnt++;
        }
    }

    sort(edg, edg + edg_cnt);

    for (int i = 0; i <= n; i++) {
        fa[i] = i;
    }

    for (int i = 0; i < edg_cnt; i++) {
        int s = edg[i].s, e = edg[i].e, v = edg[i].v;
        int fs = get(s), fe = get(e);
        if (fs != fe) {
            fa[fs] = fe;
            cnt++;
            ans += v;

            if (cnt == n - 1) {
                cout << n << " " << ans << endl;
                return 0;
            }

        }
    }
    cout << cnt << " " << ans << endl;
    return 0;
}