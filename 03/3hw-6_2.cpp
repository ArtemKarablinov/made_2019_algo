/*


Дано число N ≤ 10^4 и последовательность целых чисел из [-2^31..2^31] длиной N. Требуется построить бинарное дерево, заданное наивным порядком вставки. 
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root. 
Выведите элементы в порядке in-order (слева направо).
Рекурсия запрещена.

*/

#include<iostream>
#include<stack>
#include <functional>

template <typename T>
struct Node{
    Node* left_child = nullptr;
    Node* right_child = nullptr;
    T key;
    Node(T data){key = data;};
};

template<typename T>
using TVisitor = std::function<void(Node<T> *node)>;


template<typename T>
class Tree{
    public:
        void add(T data);
        void print() const;
        Tree();
        ~Tree();
    private:
        Node<T>* root;
        void inorder(Node<T>* leaf, const TVisitor<T>& visit) const;
};

template<typename T>
Tree<T>::Tree(){
    root = nullptr;
}

template<typename T>
void Tree<T>:: add(T data){
    if (!root){
        root = new Node<T>(data);
        return;
    }
    Node<T>* current = root;
    Node<T>* parent = root;
    while(current){
        parent = current;
        if (data < current->key){
            current = current->left_child;
        }
        else{
            current = current->right_child;
        }
    }
    Node<T>* newnode = new Node<T>(data);

    if (data < parent->key)
        parent->left_child = newnode;
    else
        parent->right_child = newnode;
};

template<typename T>
void Tree<T>::print() const{
    inorder(root, [](const Node<T>* root){ std::cout << root->key << " ";});
    std::cout << std::endl;
}

template<typename T>
void Tree<T>::inorder(Node<T>* root, const TVisitor<T>& visit) const{
    if (!root){
        return;
    };

    std:: stack <Node<T>*> s;
    Node<T>* current = root;

    while(!s.empty() || current){

        while(current){
            s.push(current);
            current = current->left_child;    
        }

        current = s.top();
        s.pop();
        visit(current);

        current = current-> right_child;
    }
}
 
template<typename T>
Tree<T>::~Tree(){
    if (!root) return;
    inorder(root, [](Node<T>* node){ delete node;});
}

int main(){
    int n;
    std:: cin >> n;
    Tree<int> mytree;
    for (int i=0; i<n; i++){
        int data;
        std:: cin >> data;
        mytree.add(data);
    };

    mytree.print();    
	return 0;
}
