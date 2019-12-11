/*


Дано число N ≤ 10^4 и последовательность целых чисел из [-2^31..2^31] длиной N. Требуется построить бинарное дерево, заданное наивным порядком вставки. 
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root. 
Выведите элементы в порядке in-order (слева направо).
Рекурсия запрещена.

*/

#include<iostream>
#include<stack>

struct Node{
    Node* left_child = nullptr;
    Node* right_child = nullptr;
    int key;
    Node(int data){key = data;};
};

class Tree{
    public:
        void add(int data);
        void print(char* type) const;
        Tree();
        ~Tree();
    private:
        Node* root;
        void inorder_print(Node* leaf) const;
        void preorder_print(Node* leaf) const;
};

Tree::Tree(){
    root = nullptr;
}

void Tree:: add(int data){
    if (!root){
        root = new Node(data);
        return;
    }
    Node* current = root;
    Node* parent = root;
    while(current){
        parent = current;
        if (data < current->key){
            current = current->left_child;
        }
        else{
            current = current->right_child;
        }
    }
    Node* newnode = new Node(data);

    if (data < parent->key)
        parent->left_child = newnode;
    else
        parent->right_child = newnode;
};

void Tree::print(char* type) const{
    if (type == "inorder"){
        inorder_print(root);
    }
    else if (type == "preorder"){
        preorder_print(root);
    }
    else{
        std:: cout<<"invalid type of print"<<std:: endl;;
    }
    std:: cout << std::endl;
}

void Tree::inorder_print(Node* root) const{
    if (!root){
        return;
    };

    std:: stack <Node*> s;
    Node* current = root;

    while(!s.empty() || current){

        while(current){
            s.push(current);
            current = current->left_child;    
        }

        current = s.top();
        s.pop();
        std:: cout<<current->key<<" ";

        current = current-> right_child;
    }
}

void Tree::preorder_print(Node *root) const{
    if (!root)
    {
       return;
    }
    std:: stack<Node *> s; 
    s.push(root);  
    while (!s.empty())
    {
        Node *temp = s.top();
        s.pop();
        std::cout << temp->key << " ";
        if (temp->right_child)
            s.push(temp->right_child);
        if (temp->left_child)
            s.push(temp->left_child); 
    }
}

Tree::~Tree(){
    // if (!root) return;
    // preorder([](const Node* node){delete node;});
};

int main(){
    int n;
    std:: cin >> n;
    Tree mytree;
    for (int i=0; i<n; i++){
        int data;
        std:: cin >> data;
        mytree.add(data);
    };
    mytree.print("preorder");
    mytree.print("inorder");
    
    
	return 0;
}
