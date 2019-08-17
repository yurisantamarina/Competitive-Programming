#include <bits/stdc++.h>
using namespace std;

struct Node {
  int val;
  Node *left, *right;
  Node(int v) {
    left = right = NULL;
    val = v;
  }
};

struct Dsu {
  vector<int> parent;
  int comp;
  Dsu(int n) {
    comp = n;
    parent.resize(n);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }
  int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
  }
  void unite(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    comp--;
    parent[v] = u;
  }
};

void insert(Node *root, int val) {

  while (1) {
    if (val < root->val) { //left
      if (!root->left) {
        root->left = new Node(val);
        break;        
      } else {
        root = root->left;
      }
    } else { //right
      if (!root->right) {
        root->right = new Node(val);
        break;
      } else {
        root = root->right;
      }
    }
  }
}

bool equal(Node *a, Node *b) {
  if (!a && !b) return true;
  if (!a || !b) return false;
  return equal(a->left, b->left) && equal(a->right, b->right);
}

int main(){
  int n, k, x;
  vector<Node*> roots;

  cin >> n >> k;
  Dsu dsu(n);

  for (int i = 0; i < n; i++) {
    Node *root = NULL;
    //cout << "tree " << i << " created\n";
    for (int j = 0; j < k; j++) {
      cin >> x;
      if (j == 0) {
        root = new Node(x);
      } else {
        insert(root, x);
      }
      
    }

    for (int j = 0; j < i; j++) {
      if (equal(root, roots[j])) {
        dsu.unite(i, j);
      }
    }
    roots.push_back(root);
  }

  cout << dsu.comp << "\n";

  return 0;
}