#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

template <class T>
class Node{
    public:
        Node():left(NULL), right(NULL), parent(NULL), value(0){}
        Node(T Value):left(NULL), right(NULL), parent(NULL), value(Value){}
        Node* left, *right, *parent;
        T value;
};

template <class T>
class Tree{
    int treeType;
    public:
        Node<T>* root;
        Tree<T>():root(NULL){}
        Tree<T>(T value){ this->root = new Node<T>(value); }
        void level_order_build(vector<T> &data);
        void complete_tree_build(vector<T> &data);
        void BST_build(vector<T> &data);
        void traversal();
        void traversal(void (*func)(Node<T>* node));
        void printTree(vector<T> tree);
        int get_depth(Node<T>* node);
        int nodeNum(Node<T>* node);
        void insert(T value);
        void remove(T value);
        bool empty(){ return (root == NULL); }
};

template<class T>
int Tree<T>::nodeNum(Node<T>* node){
    if (node == NULL) return 0;
    int l = nodeNum(node->left);
    int r = nodeNum(node->right);
    return l + r + 1;
}

template<class T>
int Tree<T>::get_depth(Node<T>* node){
    if (!node) return 0;
    return max(get_depth(node->left), get_depth(node->right)) + 1;
}

template<class T>
void Tree<T>::level_order_build(vector<T> &data){
    typename vector<T>::iterator iter = data.begin();
    if (!root) this->root = new Node<T>(*iter++);

    queue<Node<T>*> q;
    q.push(this->root);
    Node<T>* newNode, *current;
    while (iter != data.end()){
        current = q.front();
        q.pop();

        newNode = new Node<T>(*iter++);
        newNode->parent = current;
        current->left = newNode;
        q.push(newNode);

        if (iter == data.end()) break;

        newNode = new Node<T>(*iter++);
        newNode->parent = current;
        current->right = newNode;
        q.push(newNode);
    }
}

template<class T>
void Tree<T>::traversal(){
    if (empty()) {
        cout << "tree is empty\n";
        return;
    }
    vector<T> v;
    queue<Node<T>*> q;
    q.push(this->root);
    v.push_back(this->root->value);
    Node<T>* current;
    while (!q.empty()){
        current = q.front();
        cout << current->value << " ";
        q.pop();

        if (current->left) {
            q.push(current->left);
            v.push_back(current->left->value);
        }
        if (current->right) {
            q.push(current->right);
            v.push_back(current->right->value);
        }
    }
    cout << endl;
    this->printTree(v);
}

template<class T>
void Tree<T>::traversal(void (*func)(Node<T>* node)){
    if (!this->root) {
        cout << "tree is empty\n";
        return;
    }
    queue<Node<T>*> q;
    q.push(this->root);
    Node<T>* current;
    while (!q.empty()){
        current = q.front();
        func(current);
        q.pop();

        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
}

#define PARENT(i) ((i-1) / 2)
#define LINE_WIDTH 70
template <class T>
void Tree<T>::printTree(vector<T> tree){
    int NUM_NODES = tree.size();
    int print_pos[NUM_NODES];
    int i, j, k, pos, x=1, level=0;
    print_pos[0] = 0;
    for (i=0, j=1; i<NUM_NODES; i++, j++){
        pos = print_pos[PARENT(i)] + (i%2?-1:1)*(LINE_WIDTH/(pow(2, level+1))+1);

        for (k=0; k<pos-x; k++) printf("%c", i==0 || i%2 ? ' ' : '-');
        printf("%d", tree[i]);

        print_pos[i] = x = pos+1;
        if (j == pow(2, level)){
            printf("\n");
            level++;
            x = 1;
            j = 0;
        }
    }
    putchar('\n');
}

template<class T>
void PRINT(Node<T>* node){
    cout << node->value << " ";
}

int main(){
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    Tree<int>* tree = new Tree<int>();
    tree->level_order_build(v);
    tree->traversal();
    cout << tree->nodeNum(tree->root) << endl;
    return 0;
}
