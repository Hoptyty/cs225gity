/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t -> right -> left;
    t -> right -> left = t;
    t = t -> right;
    t -> left -> right = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t -> left -> right;
    t -> left -> right = t;
    t = t -> left;
    t -> right -> left = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t -> right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
    if (balance == -2) {
        int left_balance = heightOrNeg1(subtree -> left -> right) - heightOrNeg1(subtree -> left -> left);
        if (left_balance == -1) {
            rotateRight(subtree);
        }
        else {
            rotateLeftRight(subtree);
        }
    }
    else if (balance == 2) {
        int right_balance = heightOrNeg1(subtree -> right -> right) - heightOrNeg1(subtree -> right -> left);
        if (right_balance == 1) {
            rotateLeft(subtree);
        }
        else {
            rotateRightLeft(subtree);
        }
    }
    updateHeight(subtree);
}

template<class K, class V>
void AVLTree<K, V>::updateHeight(Node* node) {
    /*
    if (node == NULL) {
        return;
    }
    updateHeight(node -> left);
    updateHeight(node -> right);
    node -> height = 1 + max(heightOrNeg1(node -> left), heightOrNeg1(node -> right));
    */
    if (node -> left != NULL)
        node -> left -> height = 1 + max(heightOrNeg1(node -> left -> left), heightOrNeg1(node -> left -> right));
    if (node -> right != NULL)
        node -> right -> height = 1 + max(heightOrNeg1(node -> right -> left), heightOrNeg1(node -> right -> right));
    node -> height = 1 + max(heightOrNeg1(node -> left), heightOrNeg1(node -> right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key,value);
    }
    else if (key < subtree -> key) {
        insert(subtree -> left, key, value);
    }
    else {
        insert(subtree -> right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key); 
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = getIOP(subtree);
            swap(iop, subtree);
            remove(subtree -> left, key);
        } else {
            /* one-child remove */
            // your code here
            if (subtree -> left != NULL) {
                Node* temp = subtree -> left;
                delete subtree;
                subtree = temp;
            }
            else {
                Node* temp = subtree -> right;
                delete subtree;
                subtree = temp;
            }
        }
        // your code here
        return;
    }
    rebalance(subtree);
}

template<class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::getIOP(Node* node) {
    Node* curr = node -> left;
    while (curr -> right != NULL) {
        curr = curr -> right;
    }
    return curr;
}
