#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <unordered_map>

struct node
{
	int data;
	node* left;
	node* right;

	node(int d) { data = d; left = nullptr; right = nullptr;}
};
std::vector<int> topview(node* root);

void preorder(node* root);
std::unordered_map<node*, int> levelorder(node* root, std::vector<int>& ans);



int main() 
{
	node* root = new node(2);
	
	root->left = new node(1);
	root->right = new node(10);
	
	root->right->left = new node(3);

	root->right->left->right = new node(6);

	root->right->left->right->left = new node(4);
	root->right->left->right->right = new node(9);

	root->right->left->right->left->right = new node(5);

	//preorder(root);
	std::vector<int> ans; // stores the level by level OT
	ans  = topview(root);
	//std::unordered_map<node*, int> nodewidth = levelorder(root, ans);

	std::copy(ans.begin(), ans.end(), std::ostream_iterator<int>(std::cout, " "));
	

	
  
} 

std::vector<int> topview(node* root)
{
	std::vector<int> ans;
	std::deque<int> realans;
	std::unordered_map<node*, int> map; // map from width->node*s
	std::queue<node*> Q;
	int cminw = 0; // curr min width seen
	int cmaxw = 0;
	node* t = root;
	std::map<int, node*> widths; // map from width to its 1st visited node
	int w = 0;
	/////////////////////////////////////////////////
	if (root == nullptr) return ans;

	Q.push(t);
	map[t] = w;
	realans.push_back(t->data);


	while(!Q.empty())
	{
		t = Q.front(); Q.pop();
		w = map[t]; // w is the width of the node just popped


		if (w > cmaxw ){
			realans.push_back(t->data);
			cmaxw++;
		}
		if (w < cminw ){
			realans.push_front(t->data);
			cminw--;
		}

		if (t->left) {
			Q.push(t->left);
			map[t->left] = w-1; // store node with its width
		}
		if (t->right) {
			Q.push(t->right);
			map[t->right] = w+1;
		}

	}
	/////////////////////////////////////////////////////////////////////////////

	for (auto it = realans.begin(); it != realans.end(); it++ ){
		ans.push_back(*it);
	}

	
	return ans;


}

void preorder(node* root)
{
	if (root != nullptr){
		std::cout << root->data << ", ";
		preorder(root->left);
		preorder(root->right);
	}
}

