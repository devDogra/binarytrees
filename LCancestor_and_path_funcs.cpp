#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>

struct node
{
	int data;
	node* left;
	node* right;

	node(int d) { data = d; left = nullptr; right = nullptr;}
};

bool leaf(node* root)
{
	return (!root->left and !root->right)? true : false;
}


node* build_tree()
{
	node* root = new node(1);

	root->left = new node(2);
	root->right = new node(3);

	root->left->left = new node(4);
	root->left->right = new node(5);
	root->right->left = new node(6);
	root->right->right = new node(30);

	
	
	root->left->left->left = new node(8);
	root->left->left->right = new node(9);
	root->left->right->left = new node(10);
	root->left->right->right = new node(11);

	root->right->left->left = new node(20);



	return root; 

}

// fill v1 and v2 with paths from root to n1 and n2
void F(node* root, int n1, int n2, std::vector<node*>& v1, std::vector<node*>& v2, std::vector<node*> v)
{
	if (!root) {
		return;
	}

	// work
	v.push_back(root);

	if (root->data == n1){
		v1 = v;
		return;
	}

	if (root->data == n2){
		v2 = v;
		return;
	}

	// calls
	if (root->left){
		F(root->left, n1, n2, v1, v2, v);
	}
	if (root->right){
		F(root->right, n1, n2, v1, v2, v);
	}

	return;
}

// fill v1 and v2 with paths from root to n1 and n2
// uses less memory cuz doesnt pass a whole new array each call, just passes a ref to v and we do the popping manually
void F2(node* root, int n1, int n2, std::vector<node*>& v1, std::vector<node*>& v2, std::vector<node*>& v)
{
	if (!root) {
		return;
	}

	// work
	v.push_back(root);

	if (root->data == n1){
		v1 = v;
		v.pop_back();
		return;
	}

	if (root->data == n2){
		v2 = v;
		v.pop_back();
		return;
	}

	// calls
	if (root->left){
		F2(root->left, n1, n2, v1, v2, v);
	}
	if (root->right){
		F2(root->right, n1, n2, v1, v2, v);
	}

	v.pop_back();
	return;
}

// returns the lowest common ancestor of n1 and n2
int LCA(node* root, int n1, int n2)
{
	if (root == nullptr){
		return 0;
	}

	std::vector<node*> v1, v2, v; 
	
	F2(root, n1, n2, v1, v2, v);
	
	// trim vecs to same size
	int diff;
	int limit = 0; // for later traversal
	if (v1.size() != v2.size()){
		diff = std::abs((int)(v1.size() - v2.size())); // cast

		// pop diff # of elems from the bigger vec
		int i = diff; 
		if (v1.size() > v2.size())
		{
			limit = v2.size();
			while(i != 0){
				v1.pop_back();
				i--;
			}
		}
		if (v1.size() < v2.size())
		{
			limit = v1.size();
			while(i != 0){
				v2.pop_back();
				i--;
			}
		}
		// else, equal, so do nothing
		else{
			limit = v1.size();
		}


	}

	// // keep popping until you find a common element
	// node* add1 = nullptr;
	// node* add2 = nullptr;
	// do
	// {
	// 	// address
	// 	node* add1 = v1.back(); v1.pop_back();
	// 	node* add2 = v2.back(); v2.pop_back();

	// } while(add1 != add2); 
	// // stops with add1 and add2 being equal, and both having the address of the LCA

	// return add1->data;

	// or, keep traversing forward until both vectors diverge. the last same elem is the lca
	int i = 0;
	for (i = 0; i != limit; i++){
		if (v1[i] != v2[i]){
			i--;
			break;
		}
	}

	return v1[i]->data;
}



int main()
{
	node* root = new node(1);
	root->left = new node(2);
	root->left->left = new node(10);
	root->left->left->left = new node(11);
	root->left->left->right = new node(12);
	root->left->right = new node(5);
	root->left->right->right = new node(6);
	root->left->right->right->right = new node(8);
	root->left->right->right->left = new node(7);
	root->left->right->right->left->right = new node(13);

	root->right = new node(3);
	root->right->right = new node(9);

	////////////////////////////////////////////
	std::vector<node*> v1, v2, v; 
	int n1 = 12, n2 = 7;

	// F2(root, n1, n2, v1, v2, v);

	// //std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
	// std::cout << "n1's path: ";
	// for (auto it = v1.begin(); it != v1.end(); it++){
	// 	std::cout << (*it)->data << " ";
	// }
	// std::cout << "\n\n";
	// std::cout << "n2's path: ";
	// for (auto it = v2.begin(); it != v2.end(); it++){
	// 	std::cout << (*it)->data << " ";
	// }

	int x= LCA(root, n1, n2);
	std::cout << "lca is " << x << std::endl; 
	
}
