#include <iostream>
#include <queue>

#include "BinarySearchTree.h"

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
    this->clear();
}

template <class T>
void BinarySearchTree<T>::initRandom(int n) {
    for(int i = 0; i < n; i++) {
            int random = rand() % 20;
            insertIterative(random);
    }
}

template <class T>
bool BinarySearchTree<T>::searchIterative(T key) {
    Node* current = root;
	while(current != NULL && current->key != key) {
		if(key < current->key)
			current = current->left;
		else
			current = current->right;
	}
	return current ? true : false;
}

template <class T>
bool BinarySearchTree<T>::searchRecursive(T key) {
    return searchRecursiveHelper(root, key);
}

template <class T>
bool BinarySearchTree<T>::searchRecursiveHelper(Node*& root, T key) {
    if(root == NULL)
		return false;
    else if(root->key == key)
        return true;
	else if(key < root->key)
		return searchRecursiveHelper(root->left, key);
	else
		return searchRecursiveHelper(root->right, key);
}	

template <class T>
void BinarySearchTree<T>::insertIterative(T key) {
    Node* newNode = new Node(key);
    if(root == NULL) {
        root = newNode;
        return;
    }
    Node* current = root;
    Node* prev = NULL;
    while(current != NULL) {
        prev = current;
        if(key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    if(key < prev->key) 
        prev->left = newNode;
    else 
        prev->right = newNode;
}

template <class T>
void BinarySearchTree<T>::insertRecursive(T key) {
    insertRecursiveHelper(root, key);
}

template <class T>
void BinarySearchTree<T>::insertRecursiveHelper(Node*& root, T key) {
    if(root == NULL) {
        root = new Node(key);
    }
    else if(key < root->key)
        insertRecursiveHelper(root->left, key);
    else
        insertRecursiveHelper(root->right, key);
}

template <class T>
void BinarySearchTree<T>::preOrderHelper(Node*& root) {
    if (root != NULL) {
		std::cout << root->key << " ";
		preOrderHelper(root->left);
		preOrderHelper(root->right);
	}
}

template <class T>
void BinarySearchTree<T>::preOrder() {
    preOrderHelper(root);
}

template <class T>
void BinarySearchTree<T>::inOrderHelper(Node*& root) {
    if (root != NULL) {
		inOrderHelper(root->left);
		std::cout << root->key << " ";
		inOrderHelper(root->right);
	}
}

template <class T>
void BinarySearchTree<T>::inOrder() {
    inOrderHelper(root);
}

template <class T>
void BinarySearchTree<T>::postOrderHelper(Node*& root) {
    if (root != NULL) {
		postOrderHelper(root->left);
		postOrderHelper(root->right);
		std::cout << root->key << " ";
	}
}

template <class T>
void BinarySearchTree<T>::postOrder() {
    postOrderHelper(root);
}

template <class T>
void BinarySearchTree<T>::levelOrderIterative() {
    /* Base case */
    if (root == NULL)
        return;
    
    /* Create an empty queue for level order traversal */
    std::queue<Node*> queue;

    /* Enqueue root */
    queue.push(root);

    while(!queue.empty()) {
        /* Print front of queue and remove it from queue */
        Node* node = queue.front();
        std::cout << node->key << " ";
        queue.pop();

        /* Enqueue left child */
        if(node->left != NULL)
            queue.push(node->left);

        /* Enqueue right child */
        if(node->right != NULL)
                queue.push(node->right);
    }
}

/* Compute the "height" of a tree -- the number of 	nodes along the longest path from the root node
	down to the farthest leaf node. */
template <class T>
int BinarySearchTree<T>::getHeight(Node*& treeNode) {
    if (treeNode == NULL)
        return 0;

    int leftHeight = getHeight(treeNode->left);
    int rightHeight = getHeight(treeNode->right);
    return std::max(leftHeight, rightHeight) + 1;
}

template <class T>
int BinarySearchTree<T>::getHeight() {
    return getHeight(root);
}

/* Function to print level order traversal a tree*/
template <class T>
void BinarySearchTree<T>::levelOrderRecursive() {
    int h = getHeight(root);
	for(int level = 1; level < h + 1; ++level)
        printLevel(root, level);
}

/* Print nodes at a current level */
template <class T>
void BinarySearchTree<T>::printLevel(Node* root, int level) {
	if(root == NULL)
        return;
    else if(level == 1)
        std::cout << root->key << " ";
    else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

template <class T>
T BinarySearchTree<T>::min() {
    return minNode(root)->key;
}

template <class T>
T BinarySearchTree<T>::max() {
    return maxNode(root)->key;
}

template <class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::minNode(Node*& treeNode) {
    Node* current = root;
	while(current->left != NULL) {
		current = current->left;
	}
	return current;
}

template <class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::maxNode(Node*& treeNode) {
    Node* current = root;
	while(current->right != NULL) {
		current = current->right;
	}
	return current;
}

template <class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::removeRecursiveHelper(Node*& root, T key) {
	if(root == NULL) return NULL;
    if(key < root->key)
		root->left = removeRecursiveHelper(root->left, key);
	else if(key > root->key)
		root->right = removeRecursiveHelper(root->right, key);
	else {
		Node* toDelete = root;
		/* Copre sia il caso di 0 figli, sia il caso di 1 figlio */
		if(root->left == NULL || root->right == NULL)
			return (root->left != NULL) ? root->left : root->right;
		else {
			Node* succ = root->right;
			Node* succParent = root;  
			while(succ->left) {
				succParent = succ;
				succ = succ->left;  
			}
			/* corner case, avviene quando vogliamo eliminare la radice ed è proprio il padre del successore */
			if(succParent == root) {
				/* basta collegare il sottoalbero sinistro al successore e farlo diventare radice */
				succ->left = root->left;
			}
			else {
				/* colleghiamo il padre del successore al figlio del successore */
				succParent->left = succ->right;
				/* per non fare root->key = succ->key */
				succ->left = root->left;  
				succ->right = root->right;  
			}  
			root = succ;
		}
		delete toDelete;	
	}
	return root;
}

template <class T>
void BinarySearchTree<T>::removeRecursive(T key) {
    this->root = removeRecursiveHelper(root, key);
}

template <class T>
void BinarySearchTree<T>::removeIterative(T key) {
	Node* p = NULL;
	/* individuo il nodo da rimuovere */
	Node* u = getParent(root, key, p);
	/* se il nodo da rimuovere è presente nell’albero... */
	if(u == NULL) return;
	/* e non ha figli... */
	if(u->left == NULL && u->right == NULL) {
		if(u != root)
			unlink(p, u);
		else
			root = NULL;
	}
	/* e ha due figli... */
	else if(u->left != NULL && u->right != NULL) {
		Node* successor = u->right;
		Node* succParent = u;
		/* determiniamo il successore di u e teniamo un puntatore a suo padre*/
		while(successor->left != NULL) {
			succParent = successor;
			successor = successor->left;
		}
		if(succParent == u) {
			successor->left = u->left;
		}
		else {
			/* il padre del successore ora punta al figlio destro del successore */
			succParent->left = successor->right;
			/* il successore viene sostituito al nodo da eliminare*/
			successor->left = u->left;
			successor->right = u->right;
		} 
		if(u == p->left)
			p->left = successor;
		else
			p->right = successor;
	}
	/* e ha un solo figlio... */
	else {
		/* determiniamo se il figlio è destro o sinistro*/
		Node* childToLink = (u->left != NULL) ? u->left : u->right;
		/* verifichiamo se il nodo da eliminare è radice */
		if(u != root) {
			/* se u è figlio sinistro attachiamo al padre il nuovo figlio sinistro */
			if(u == p->left)
				p->left = childToLink;
			/* se u è figlio destro attachiamo al padre il nuovo figlio destro */
			else
				p->right = childToLink;
		}
		else
			root = childToLink;
	}
	delete u;	
}

/* Cerca un nodo e restituisce il puntatore ad esso e a suo padre */
template <class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::getParent(Node*& root, T key, Node*& parent) {
    Node* current = root;
    while(current != NULL && current->key != key) {
		parent = current;
		if(key < current->key)
			current = current->left;
		else
			current = current->right;
	}
	return current;
}

/* Scollega il padre dal figlio */
template <class T>
void BinarySearchTree<T>::unlink(Node*& p, Node*& u) {
	if(u == p->left)
		p->left = NULL;
	else
		p->right = NULL;
}

template <class T>
void BinarySearchTree<T>::clearHelper(Node*& root){
	if(root != NULL){
		clearHelper(root->left);
		clearHelper(root->right);
		Node* toDelete = root;
		root = NULL;
		delete toDelete;
	}
}

template <class T>
void BinarySearchTree<T>::clear() {
    clearHelper(root);
}

template <class T>
void BinarySearchTree<T>::printHelper(Node* root, int space) {
    if(root == NULL) return;
    space += 5;
    printHelper(root->right, space);
    std::cout << std::endl;
    for(int i = 5; i < space; ++i)
        std::cout << " ";
    std::cout << root->key<<"\n";
    printHelper(root->left, space);
}

template <class T>
void BinarySearchTree<T>::print() {
    printHelper(root, 0);
}
