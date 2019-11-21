
/*
Солдаты. 
В одной военной части решили построить в одну шеренгу по росту. 
Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
 а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. 
 Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, 
 а в конце – самые низкие. За расстановку солдат отвечал прапорщик, 
 который заметил интересную особенность – все солдаты в части разного роста. 
 Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, 
 а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
Вариант 7_1.  Требуемая скорость выполнения команды - O(log n) в среднем. 
Для решения задачи реализуйте декартово дерево.
*/
#include <iostream>
#include <functional>
#include <cassert>

using namespace std;

struct Node {
    explicit Node(int key_, int prior_) : key(key_), priority(prior_) {};
    int size = 0; 
    int key;
    int priority;
    Node *left = nullptr;
    Node *right = nullptr;
};

using Callback = std::function<void(Node *node)>;

class Treap {
private:
    Node *root = nullptr;
    void traverse(Node* node, const Callback &callback);
    int search_index(Node* node, int key) ;
    int search_key(Node* node, int index) ;

public:
    void split(Node* node, int key, Node* &left, Node* &right);
    Node *merge(Node* &left, Node* &right);
    int add(int key);
    void remove(int index);
    ~Treap();
};
void Treap:: split(Node* node, int key, Node* &left, Node* &right) {
    if (!node) {
        left = right = nullptr;
    } else if (node->key <= key) {
        split(node->right, key, node->right, right);
        left = node;
        left->size = (left->left ? left->left->size + 1 : 0) + (left->right ? left->right->size + 1 : 0);
    } else {
        split(node->left, key, left, node->left);
        right = node;
        right->size = (right->right ? right->right->size + 1 : 0) + (right->left ? right->left->size + 1 : 0);
    }
}


Node* Treap::merge(Node* &left, Node* &right) {
    if (!left) 
        return right;
    if (!right) 
        return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        left->size = (left->left ? left->left->size + 1 : 0) + left->right->size + 1;
        return left;
    } else {
        right->left = merge(left, right->left);
        right->size = (right->right ? right->right->size + 1 : 0) + right->left->size + 1;
        return right;
    }
}
 
int Treap:: search_key(Node* node, int index)  {

    int cur_index = node->right ? node->right->size + 1 : 0;
    if (index == cur_index) {
        return node->key;
    } else if (index > cur_index) {
        assert(node->left);
        return search_key(node->left, index - cur_index - 1);
    } else if (index < cur_index) {
        assert(node->right);
        return search_key(node->right, index);
    } else {
        throw std::invalid_argument("No index found");
    }
}

int Treap::search_index(Node* node, int key) {
    int cur_index = node->right ? node->right->size + 1 : 0;
    if (key == node->key){
        return cur_index;
    } else if (key < node->key) {
        assert(node->left);
        return cur_index + 1 + search_index(node->left, key);
    } else if (key > node->key) {
        assert(node->right);
        return search_index(node->right, key);
    } else {
        throw std::invalid_argument("No key found");
    }
}

int Treap:: add(int key) {
    Node* left = nullptr;
    Node* right = nullptr;
    split(root, key, left, right);
    Node* tmp = new Node(key, rand());
    left = merge(left, tmp);
    root = merge(left, right);
    return search_index(root, key);
}

void Treap:: remove(int id) {
    Node* left = nullptr;
    Node* right = nullptr;
    Node* tmp = nullptr;
    int key = search_key(root, id);
    split(root, key - 1, left, right);
    split(right, key, tmp, right);
    delete tmp;
    root = merge(left, right);
}

void Treap::traverse(Node* node, const Callback &callback) {
    if (!node) return;
    traverse(node->left, callback);
    traverse(node->right, callback);
    callback(node);
}

Treap::~Treap() {};
int main() {
    srand(1);

    int n = 0;
    std:: cin >> n;

    int command = 0;
    int command_value = 0;
    Treap treap;
    for (int i = 0; i < n; i++) {
        std:: cin >> command >> command_value;
        if (command == 1) {
            std:: cout << treap.add(command_value) << endl;
        } else if (command == 2) {
            treap.remove(command_value);
        }
    }
    return 0;
}



