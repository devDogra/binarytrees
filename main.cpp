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
	char data;
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
	root->right->right = new node(7);

	root->left->left->left = new node(8);
	root->left->left->right = new node(9);
	root->left->right->left = new node(10);
	root->left->right->right = new node(11);


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
    void toSumTree(Node *root)
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

int main() 
{
	char A[] = "4(2(3)(1))(6(5))";
	node* R = nullptr;
	
	CT(0, 15, R, A);
	
  
} 

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

void preorder(node* root)
{
	if (root != nullptr){
		std::cout << root->data << ", ";
		preorder(root->left);
		preorder(root->right);
	}
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
