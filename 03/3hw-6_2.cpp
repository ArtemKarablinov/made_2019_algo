/*


Дано число N ≤ 10^4 и последовательность целых чисел из [-2^31..2^31] длиной N. Требуется построить бинарное дерево, заданное наивным порядком вставки. 
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root. 
Выведите элементы в порядке in-order (слева направо).
Рекурсия запрещена.

*/

#include<iostream>
#include<stack>

template <typename T>
struct Node{
    Node* left_child = nullptr;
    Node* right_child = nullptr;
    T key;
    Node(T data){key = data;};
};

template<typename T>
class Tree{
    public:
        void add(T data);
        void print(char* type) const;
        Tree();
        ~Tree();
    private:
        Node<T>* root;
        void inorder_print(Node<T>* leaf) const;
        void preorder_print(Node<T>* leaf) const;
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
void Tree<T>::print(char* type) const{
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

template<typename T>
void Tree<T>::inorder_print(Node<T>* root) const{
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
        std:: cout<<current->key<<" ";

        current = current-> right_child;
    }
}

template<typename T>
void Tree<T>::preorder_print(Node<T> *root) const{
    if (!root)
    {
       return;
    }
    std:: stack<Node<T> *> s; 
    s.push(root);  
    while (!s.empty())
    {
        Node<T> *temp = s.top();
        s.pop();
        std::cout << temp->key << " ";
        if (temp->right_child)
            s.push(temp->right_child);
        if (temp->left_child)
            s.push(temp->left_child); 
    }
}

template<typename T>
Tree<T>::~Tree(){
    if (!root) return;
    std:: stack<Node<T>*> s;
    s.push(root);
    while(!s.empty()){
        Node<T> *temp = s.top();
        s.pop();
        if (temp->right_child)
            s.push(temp->right_child);
        if (temp->left_child)
            s.push(temp->left_child); 
        delete temp;
    }

};

int main(){
    int n;
    std:: cin >> n;
    Tree<int> mytree;
    for (int i=0; i<n; i++){
        int data;
        std:: cin >> data;
        mytree.add(data);
    };
    mytree.print("preorder");
    mytree.print("inorder");    
	return 0;
}
