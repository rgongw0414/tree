#include "tree.cpp"

int ans;
void dfs(Node<int>* node){
    if (node == NULL) return;
    ans += Tree<int>::get_depth(node);
    dfs(node->left);
    dfs(node->right);
}

// depth: normal definition, i.e. height of a tree
// the sum of depths of all nodes in the tree
void depthSum(Node<int>* node){
    ans = 0;
    dfs(node);
    cout << ans << endl;
}

void dfs2(Node<int>* node, int depth){
    ans += depth;
    if (node->left) dfs2(node->left, depth+1);
    if (node->right) dfs2(node->right, depth+1);
}

// depth: the distance to root
void depthSum2(Node<int>* node){
    ans = 0;
    dfs2(node, 0);
    cout << ans << endl;
    ans = 0;
}

// sum of depthSum2 of all the subtree's root
// p.first: the num of nodes in subtree
// p.second: the sum of depth in subtree
pair<int, int> dfs3(Node<int>* node){
    pair<int, int> p = make_pair(1, 0); // since subtree not found yet, so begin with only one node
    if (node->left){
        pair<int, int> pchild = dfs3(node->left);
        p.first += pchild.first;
        // once recursed the tree upward, the depth of nodes in subtree +1, so we have to fixed it by a trick, which is adding the number of nodes in subtree.
        p.second += pchild.first + pchild.second; 
    }
    if (node->right){
        pair<int, int> pchild = dfs3(node->right);
        p.first += pchild.first;
        p.second += pchild.first + pchild.second;
    }
    ans += p.second; // accumulate the depthSum of each node to ans
    return p;
}

void depthSum3(Node<int>* node){
    ans = 0;
    pair<int, int> p = dfs3(node);
    cout << ans << endl;
}

int main(){
    Tree<int>* tree = new Tree<int>;
    vector<int> input = {1,2,3,4,5,6,7,8,9,10,11};
    tree->level_order_build(input);
    tree->printTree(input);
    depthSum(tree->root);
    depthSum2(tree->root);
    depthSum3(tree->root);
}
