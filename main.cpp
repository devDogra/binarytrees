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
std::vector<int> topview(node* root);

void preorder(node* root);
std::vector<int> levelorder(node* root);

node* build_tree()
{
	node* root = new node(1);

	root->left = new node(2);
	root->right = new node(3);

	root->left->left = new node(4);
	root->left->right = new node(5);
	root->right->left = new node(6);
	root->right->right = new node(30);

	
	
	// root->left->left->left = new node(8);
	// root->left->left->right = new node(9);
	// root->left->right->left = new node(10);
	// root->left->right->right = new node(11);

	root->right->left->left = new node(20);



	return root; 

	


}

int findpair(int begin, int end, char*& A)
{
	int delta = 1;
	

	int t = begin+1;
	while(t != end)
	{
		if (A[t] == '('){
			delta++;
		}
		if(A[t] == ')'){
			delta--;
		}
		if (delta == 0) break;

		t++;
	}
	return t;
}

    // this is not the g4g sum tree, but a weird one where
	// each node's data is it's l's data and r's data's sum
void toSumTree(node *root)
{
		
	if (root != NULL)
	{
		if (root->left) toSumTree(root->left);
		if (root->right) toSumTree(root->right);

		if (root->left and root->right)
		{
			root->data = root->left->data + root->right->data;
		} 
		else if (root->left and !root->right)
		{
			root->data = root->left->data;
		}
		else if (!root->left and root->right)
		{
			root->data = root->right->data;
		}
		else // leaf node, store its address so we can later make it 0
		{
			root->data = root->data;
		}
	}
	else return;
	

		

	
}



// bloodline sums max
// mls = maximum level seen
// map from level->bloodline sum
void P(node* root, int BS, int level, std::unordered_map<int, int>& map, int& mls, int& maxBS);

int main() 
{


	node* root  = build_tree();
	std::unordered_map<int, int> map;
	int mls = 0;
	int maxBS = 0;
	P(root, 0, 1, map, mls, maxBS);
	
  
} 

bool leaf(node* root)
{
	return (!root->left and !root->right)? true : false;
}

// bloodline sums max
// mls = maximum level seen
// map from level->bloodline sum
void P(node* root, int BS, int level, std::unordered_map<int, int>& map, int& mls, int& maxBS)
{
	if (root == nullptr) { return; }

	// work
	if (leaf(root))
	{
		if (map.find(level) == map.end()){ // if map[level] is empty
			map[level] = BS;
		} 
		else if (map[level] < BS){
			map[level] = BS;
		}

		// cases: level == mls && BS + root->data > maxBS, level > mls
		
		if (level >= mls && BS+root->data > maxBS) {
			//std::cout << " BS  = " << BS + root->data << " level = " << level << std::endl;
			mls =level;
			maxBS = BS+root->data;
		} 
	}

	// calls
	if (root->left){
		P(root->left, BS + root->data, level+1, map, mls, maxBS);
	}
	if (root->right){
		P(root->right, BS + root->data, level+1, map, mls, maxBS);
	}

	std::cout << "\n max BS = " << maxBS << std::endl;

}
	 
//



void preorder(node* root)
{
	if (root != nullptr){
		std::cout << root->data << ", ";
		preorder(root->left);
		preorder(root->right);
	}
}

// leaves at the same level?
// doesnt work
// void LSL(node* root)
// {
// 	static int l = 1;
// 	if (root == nullptr) { l--; return; }

// 	l++; LSL(root->left);
// 	l++; LSL(root->left);
// 	std::cout << root->data << " - level " << l << std::endl;
	
// 	l--; return;
// }

// tells us if all the leaves are at the same level or not
bool PO(node* root, int level)
{
	static bool balanced = true;
	if (root == nullptr) { return true; }

	PO(root->left, level+1);
	PO(root->right, level+1);

	// visit the actual node
	// if this is a leaf, ie r->l and r->r are null, then collect its level
	//std::cout << root->data << " - level " << level << std::endl;

	if (!root->left and !root->right){ // if leaf
		static int leaflev = level; // leaflev is the level of the 1st leaf we meet 
		
		if (leaflev != level) 
		{ 
			std::cout << "NOT EQUAL at " << root->data << std::endl; 
			balanced = false;   
		}
	}

	return balanced; // if all that is done and we dont return false, 
	// it means that we did not encounter a level that WASNT equal to leaflev
}


// bloodline sums max
// mls = maximum level seen
// map from level->bloodline sum
void P(node* root, int BS, int level, std::unordered_map<int, int>& map, int& mls, int& maxBS);



std::vector<int> topview(node* root)
{
	std::vector<int> ans;
	std::deque<int> realans;
	std::unordered_map<node*, int> map; // map from width->node*s
	std::queue<node*> Q;
	int cminw = 0;
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



// prints only
std::vector<int> levelorder_zigzag(node* root)
{

	std::vector<int> ans;
	std::deque<int> LOS;
	std::vector<node*> LON; // level order nodes

	std::deque<node*> Q; // processing Q for the nodes of a level
	std::deque<node*> S; // holding queue for the nodes of the next level

	bool odd= true;

	node* t = root;
	S.push_back(root);
	
	if (root == nullptr) return ans;
	
	
	while(!Q.empty() or !S.empty()){
		
		
		if (Q.empty()) { // If processing is done for *this* level
			// bring all of S into Q
			Q = S;

			// transfer this "level" into the vector
			while(!S.empty())
			{
				// alternate b/w pushfront and pushback
				// if (odd) LOS.push_back(S.front()->data); 
				// else LOS.push_front(S.front()->data);

				// odd
				if (odd)
				{
					LOS.push_back(S.front()->data);	
					S.pop_front();
				}
				else
				{
					LOS.push_back(S.back()->data);
					S.pop_back();
				}
				// even 
				

			}

			odd = !odd;
			LON.push_back(nullptr); // to signal the end of the level
			LOS.push_back(-1);

			S = std::deque<node*>(); 

			
		} 

		t = Q.front(); 
		
		
		Q.pop_front();

		if (t->left) { 
			S.push_back(t->left); 
		}
		if (t->right) {
			S.push_back(t->right);
		}


	}



	for (auto it = LOS.begin(); it != LOS.end(); it++){
		if (*it == -1) std::cout << "\n";
		else std::cout << *it << "  ";
	}

	return ans;

}
