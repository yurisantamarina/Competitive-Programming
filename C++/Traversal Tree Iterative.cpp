#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 201010
#define F first
#define S second
typedef long long int ll;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int x){
		val = x;
		left = right = NULL;
	}
};

void dfs(TreeNode *root){
	stack<pair<TreeNode*, int> > recur; 
	recur.push({root, 0});
	
	while(!recur.empty()){
		TreeNode *at = recur.top().first;
		int child = recur.top().second;
		recur.pop();
		
		if(child == 2){//0: preorder, 1: inorder, 2: postorder
			cout << "Node with value = " << at->val << "\n";
		}
			
		if(child == 0){
			recur.push({at, 1});
			if(at->left){
				recur.push({at->left, 0});
			}
		}else if(child == 1){
			recur.push({at, 2});
			if(at->right){
				recur.push({at->right, 0});
			}
		}
	}
}

int main(){
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	root->right = new TreeNode(3);
	root->right->left = new TreeNode(6);
	root->right->right = new TreeNode(7);
	dfs(root);
	
	return 0;
}
