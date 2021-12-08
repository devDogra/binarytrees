/*
https://practice.geeksforgeeks.org/problems/sum-of-the-longest-bloodline-of-a-tree/1
*/

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
