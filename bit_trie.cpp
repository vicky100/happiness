#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
int n;
int arr[maxn];
int prr[maxn];

struct trie {
	int val;
	int cnt;
	struct trie *child[2];
};

trie* getnode() {
	trie *temp = new trie;
	temp->val = temp->cnt = 0;;
	temp->child[0] = temp->child[1] = NULL;
	return temp;
}

void insertnode(trie *root , int key) {

	trie *temp = root;
	for(int i = 30 ; i >= 0 ; i--) {
		int x = ((key >> i) & 1);
		if(temp->child[x] == NULL)
			temp->child[x] = getnode();
		temp->cnt += 1;
		temp = temp->child[x];
	}
	temp->val = key;
	temp->cnt += 1;
}

bool deletenode(trie *root , int val , int n) {
	if(n < 0) {
		if(root->cnt == 1) {
			return true;
		}
		else {
			root->cnt -= 1;
			return false;
		}
	}

	int x = ((val >> n) & 1);
	if(deletenode(root->child[x] , val , n - 1)) {
		root->child[x] = NULL;
	}
	root->cnt -= 1;
	
	if(root->cnt == 0)
		return true;

	return false;
}

int solve(trie *root , int val) {
	
	for(int i = 30 ; i >= 0 ; i--) {
		int x = ((val >> i ) & 1);
		if(root->child[x])
			root = root->child[x];
		else
			root = root->child[1 ^ x];
	}

	return root->val;
}


int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
		cin >> arr[i];
	for(int i = 1 ; i <= n ; i++)
		cin >> prr[i];

	trie *root = getnode();

	for(int i = 1 ; i <= n ; i++) {
		insertnode(root , prr[i]);
	}

	for(int i = 1 ; i <= n ; i++) {
		int p = solve(root , arr[i]);
		deletenode(root , p , 30);
		cout << (p ^ arr[i]) << " ";
	}
	cout << endl;
return 0;	
}
