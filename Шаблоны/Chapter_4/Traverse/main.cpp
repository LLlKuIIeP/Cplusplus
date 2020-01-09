// 4.2 Свертка
#include <iostream>


struct Node
{
    Node(int i = 0) : value(i), left(nullptr), right(nullptr) {}

    int value;
    Node *left;
    Node *right;
};

auto left = &Node::left;
auto right = &Node::right;

// обход дерева с использованием свертки
template<typename T, typename... TP>
Node* treverse(T np, TP... paths)
{
    return (np ->* ... ->* paths);
}

int main()
{
    Node *root = new Node{0};
    root->left = new Node{1};
    root->left->right = new Node{2};

    Node *node = treverse(root, left, right);
    std::cout << node->value << std::endl;

    return 0;
}
