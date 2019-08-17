#include <bits/stdc++.h>

using namespace std;
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
  register int c = gc();
  x = 0;
  for(;(c<48 || c>57);c = gc());
  for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

#define MAXN 200010
int val[MAXN], size_sub[MAXN], ini[MAXN];
vector<int> euler;
vector<int> g[MAXN];
int n, q;
int seen[1<<20];
int tempo = 1;
vector<int> all_w;

struct Node {
 Node *nxt[2];
 int counter;
 Node() {
  nxt[0] = nxt[1] = NULL;
  counter = 0;
}
};

const int MAX_LEN = 21;

struct Trie {
 Node *root;
 Trie() {
  root = new Node();
}

Trie(Node *r) {
  root = r;
}

void del(Node *t) {
  queue<Node*> q;
  if (t->nxt[0]) q.push(t->nxt[0]);
  if (t->nxt[1]) q.push(t->nxt[1]);

  while (!q.empty()) {
    Node *at = q.front();
    q.pop();
    if (at->nxt[0]) q.push(at->nxt[0]);
    if (at->nxt[1]) q.push(at->nxt[1]);
    delete at;
  }
}

void del() {
  del(root);
}

Node* clona(Node *at) {
  Node *nw = new Node();
  nw->nxt[0] = at->nxt[0];
  nw->nxt[1] = at->nxt[1];
  nw->counter = at->counter;
  return nw;
}

Node* update(int w) {
  Node *clone = clona(root);
  Node *new_root = clone;

  clone->counter++;
  for (int i = MAX_LEN - 1; i >= 0; i--) {
    int bit = (w & (1 << i)) > 0;
    if (clone->nxt[bit]) {
      clone->nxt[bit] = clona(clone->nxt[bit]);
    } else {
      clone->nxt[bit] = new Node();
    }
    clone = clone->nxt[bit];
    clone->counter++;
  }

  return new_root;
}
};

struct Segtree {
  vector<int> st, adj;

  void build(int no, int l, int r) {
    if (l > r) return;
    if (l == r) {
      st[no] = euler[adj[l] - 1];
      return;
    }
    int nxt = 2 * no, mid = (l + r) / 2;
    build(nxt, l, mid);
    build(nxt + 1, mid + 1, r);
    st[no] = min(st[nxt], st[nxt + 1]);
  }

  void build() {
    st.resize((int)adj.size() * 4);
    build(1, 0, (int)adj.size() - 1);
  }

  int query(int no, int l, int r, int i, int j) {
    if (l > r || i > j) return INT_MAX;
    if (r < i || l > j) return INT_MAX;
    if (i <= l && r <= j) return st[no];
    int nxt = 2 * no, mid = (l + r) / 2;
    return min(query(nxt, l, mid, i, j), query(nxt + 1, mid + 1, r, i, j));
  }

  int query(int l, int r) {
    return query(1, 0, (int)adj.size() - 1, l, r);
  }

};

Trie trie[MAXN];
int idx_trie = 0;
Segtree seg_trees[1 << 20];

Node* getNext(Node *t, int bit) {
  return t ? t->nxt[bit] : NULL;
}

bool can(Node *l, Node *r, int bit) {
  Node *left = getNext(l, bit);
  Node *right = getNext(r, bit);
  int counter = (right ? right->counter : 0) - (left ? left->counter : 0);
  return counter > 0;
}

int max_xor(Node *l, Node *r, int k) {
  int ans = 0;
  for (int i = MAX_LEN - 1; i >= 0; i--) {
    int bit = (k & (1 << i)) > 0;
    if (can(l, r, !bit)) {
      ans += (1 << i);
      l = getNext(l, !bit);
      r = getNext(r, !bit);
    } else {
      l = getNext(l, bit);
      r = getNext(r, bit);
    }
  }
  return ans;
}

void reset() {
  for (int i = 0; i <= n; i++) {
    g[i].clear();
  }

  for (int i = 0; i < (int)all_w.size(); i++) {
    seg_trees[all_w[i]].adj.clear();
    seg_trees[all_w[i]].st.clear();
  }

  all_w.clear();
  tempo++;

  idx_trie = 0;
  trie[idx_trie++] = Trie();
  euler.clear();
}

void dfs(int u, int parent) {
  ini[u] = (int)euler.size();
  euler.push_back(u);
  seg_trees[val[u]].adj.push_back(ini[u] + 1);
  size_sub[u] = 1;
  for (int &v : g[u]) {
    if (v != parent) {
      dfs(v, u);
      size_sub[u] += size_sub[v];
    }
  }
}

void build_seg_trees() {
  for (int &w : all_w) {
    seg_trees[w].build();
  }
}

pair<int, int> getRange(int l, int r, int k) {
  int left = lower_bound(seg_trees[k].adj.begin(), seg_trees[k].adj.end(), l) - seg_trees[k].adj.begin();
  int right = upper_bound(seg_trees[k].adj.begin(), seg_trees[k].adj.end(), r) - seg_trees[k].adj.begin();
  return {left, right - 1};
}

int findVertex(int l, int r, int k) {
  pair<int, int> range = getRange(l, r, k);
  return seg_trees[k].query(range.first, range.second);
}

int main() {
  int tc, u, v;
  scanint(tc);
  while (tc--) {
    scanint(n);
    scanint(q);
    reset();
    for (int i = 1; i <= n; i++) {
      scanint(val[i]);
      if (seen[val[i]] < tempo) {
        all_w.push_back(val[i]);
        seen[val[i]] = tempo;
      }
    }
    for (int i = 0; i < n - 1; i++) {
      scanint(u);
      scanint(v);
      g[u].push_back(v);
      g[v].push_back(u);
    }

    dfs(1, 1);
    for (int i = 1; i <= n; i++) {
      trie[i] = Trie(trie[i - 1].update(val[euler[i - 1]]));
    }
    build_seg_trees();

    int a, b, k, l, r, lst_max_xor = 0, lst_vertex = 0, need;
    for (int i = 0; i < q; i++) {
      scanint(a);
      scanint(b);
      v = a ^ lst_vertex;
      k = b ^ lst_max_xor;

      l = ini[v];
      r = ini[v] + size_sub[v] - 1;
      l++; r++;
      lst_max_xor = max_xor(trie[l - 1].root, trie[r].root, k);
      need = lst_max_xor ^ k;

      lst_vertex = findVertex(l, r, need);

      printf("%d %d\n", lst_vertex, lst_max_xor);
    }
  }

  return 0;
}