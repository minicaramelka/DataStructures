#include"tree.h"
#include<iostream>

using namespace std;

RBtree::node::node(const ValueType& value, const ValueType& key, node *parent, node *left, node *right, char color) {
	this->value = value;
	this->key = key;
	this->color = color;
	this->parent = parent;
	this->left = left;
	this->right = right;
}

RBtree::node* RBtree::node::copyNode(node* other) {
	if (other == nullptr) {
		return nullptr;
	}
	node* newNode = new node(other->value, other->key, other->parent, other->left, other->right, other->color);
	newNode->left = copyNode(other->left);
	newNode->right = copyNode(other->right);
	return newNode;
}
	

RBtree::node::~node(){
}

RBtree::RBtree(){
	root = nullptr;
	_size = 0;
}

RBtree::RBtree(const RBtree& copyRBtree){
	node* p = nullptr;
	p = RBtree::node::copyNode(copyRBtree.root);
	this->root = p;
}

RBtree& RBtree::operator=(const RBtree& copyRBtree) {
	if (this == &copyRBtree) {
		return *this;
	}
	RBtree bufTree(copyRBtree);
	this->_size = bufTree._size;
	this->root = bufTree.root;
	return *this;
}

RBtree::~RBtree(){
	Clear(root);
}

void RBtree::insertLeaf(ValueType key, ValueType value){
	node *ptr, *tmp;
	node *newLeaf = new node(key, value);
	ptr = root;
	tmp = nullptr;
	if (root == nullptr){
		root = newLeaf;
		newLeaf->parent = nullptr;
	}
	else{
		while (ptr != nullptr){
			tmp = ptr;
			if (ptr->key < newLeaf->key)
				ptr = ptr->right;
			else
				ptr = ptr->left;
		}
		newLeaf->parent = tmp;
		if (tmp->key < newLeaf->key)
			tmp->right = newLeaf;
		else
			tmp->left = newLeaf;
	}
	_size++;
	insertLeafFix(newLeaf);
}

void RBtree::insertLeafFix(node *newLeaf){
	node *uncle;
	if (root == newLeaf){
		newLeaf->color = 'b';
		return;
	}
	while (newLeaf->parent != nullptr && newLeaf->parent->color == 'r'){
		node *grandpa = newLeaf->parent->parent;
		if (grandpa->left == newLeaf->parent){
			if (grandpa->right != nullptr){
				uncle = grandpa->right;
				if (uncle->color == 'r'){
					newLeaf->parent->color = 'b';
					uncle->color = 'b';
					grandpa->color = 'r';
					newLeaf = grandpa;
				}
			}
			else{
				if (newLeaf->parent->right == newLeaf){
					newLeaf = newLeaf->parent;
					leftrotate(newLeaf);
				}
				newLeaf->parent->color = 'b';
				grandpa->color = 'r';
				rightrotate(grandpa);
			}
		}
		else{
			if (grandpa->left != nullptr){
				uncle = grandpa->left;
				if (uncle->color == 'r'){
					newLeaf->parent->color = 'b';
					uncle->color = 'b';
					grandpa->color = 'r';
					newLeaf = grandpa;
				}
			}
			else{
				if (newLeaf->parent->left == newLeaf){
					newLeaf = newLeaf->parent;
					rightrotate(newLeaf);
				}
				newLeaf->parent->color = 'b';
				grandpa->color = 'r';
				leftrotate(grandpa);
			}
		}
		root->color = 'b';
	}
}

void RBtree::deleteLeaf(ValueType key){
	if (root == nullptr){
		cout << "Empty Tree" << endl;
		return;
	}
	node *delNode;
	delNode = root;
	node *youngNode = nullptr;
	node *nextNode = nullptr;
	bool found = false;
	while (delNode != nullptr && found == false){
		if (delNode->key == key)
			found = true;
		if (found == false){
			if (delNode->key < key)
				delNode = delNode->right;
			else
				delNode = delNode->left;
		}
	}
	if (found == false){
		cout << "\nElement Not Found.";
		return;
	}
	else{
		cout << "\nDeleted Element: " << delNode->key;
		cout << "\nColour: ";
		if (delNode->color == 'b')
			cout << "Black\n";
		else
			cout << "Red\n";

		if (delNode->parent != nullptr)
			cout << "\nParent: " << delNode->parent->key;
		else
			cout << "\nThere is no parent of the node.  ";
		if (delNode->right != nullptr)
			cout << "\nRight Child: " << delNode->right->key;
		else
			cout << "\nThere is no right child of the node.  ";
		if (delNode->left != nullptr)
			cout << "\nLeft Child: " << delNode->left->key;
		else
			cout << "\nThere is no left child of the node.  ";
		cout << "\nNode Deleted.";
		if (delNode->left == nullptr || delNode->right == nullptr)
			youngNode = delNode;
		else
			if (delNode->left != nullptr) {
				youngNode = delNode->left;
				while (youngNode->right != nullptr)
					youngNode = youngNode->right;
			}
			else {
				youngNode = delNode->right;
				while (youngNode->left != nullptr)
					youngNode = youngNode->left;
			}
		if (youngNode->left != nullptr)
			nextNode = youngNode->left;
		else{
			if (youngNode->right != nullptr)
				nextNode = youngNode->right;
			else
				nextNode = nullptr;
		}
		if (nextNode != nullptr)
			nextNode->parent = youngNode->parent;
		if (youngNode->parent == nullptr)
			root = nextNode;
		else{
			if (youngNode == youngNode->parent->left)
				youngNode->parent->left = nextNode;
			else
				youngNode->parent->right = nextNode;
		}
		if (youngNode != delNode){
			delNode->color = youngNode->color;
			delNode->key = youngNode->key;
		}
		if (youngNode->color == 'b')
			deleteLeafFix(nextNode);
	}
	_size--;
}

void RBtree::deleteAllLeavesByKey(ValueType key) {
	if (root == nullptr) {
		cout << "\nEmpty Tree\n";
		return;
	}
	node *nd = root;
	int found = 0;
	while (nd != nullptr && found == 0) {
		if (nd->key == key)
			found = 1;
		if (found == 0) {
			if (nd->key < key)
				nd = nd->right;
			else
				nd = nd->left;
		}
	}
	if (found == 0) {
		cout << "\nElement Not Found.";
		return;
	}
	if(found == 1)
		deleteLeaf(key);
	deleteAllLeavesByKey(key);
}

void RBtree::deleteLeafFix(node *delNode){
	node *nd;
	while (delNode != root && delNode->color == 'b'){
		if (delNode->parent->left == delNode){
			nd = delNode->parent->right;
			if (nd->color == 'r'){
				nd->color = 'b';
				delNode->parent->color = 'r';
				leftrotate(delNode->parent);
				nd = delNode->parent->right;
			}
			if (nd->right->color == 'b'&& nd->left->color == 'b'){
				nd->color = 'r';
				delNode = delNode->parent;
			}
			else{
				if (nd->right->color == 'b'){
					nd->left->color = 'b';
					nd->color = 'r';
					rightrotate(nd);
					nd = delNode->parent->right;
				}
				nd->color = delNode->parent->color;
				delNode->parent->color = 'b';
				nd->right->color = 'b';
				leftrotate(delNode->parent);
				delNode = root;
			}
		}
		else{
			nd = delNode->parent->left;
			if (nd->color == 'r'){
				nd->color = 'b';
				delNode->parent->color = 'r';
				rightrotate(delNode->parent);
				nd = delNode->parent->left;
			}
			if (nd->left->color == 'b'&& nd->right->color == 'b'){
				nd->color = 'r';
				delNode = delNode->parent;
			}
			else{
				if (nd->left->color == 'b'){
					nd->right->color = 'b';
					nd->color = 'r';
					leftrotate(nd);
					nd = delNode->parent->left;
				}
				nd->color = delNode->parent->color;
				delNode->parent->color = 'b';
				nd->left->color = 'b';
				rightrotate(delNode->parent);
				delNode = root;
			}
		}
		delNode->color = 'b';
		root->color = 'b';
	}
}

void RBtree::leftrotate(node *nd){
	if (nd->right == nullptr)
		return;
	else{
		node *newParent = nd->right;
		if (newParent->left != nullptr){
			nd->right = newParent->left;
			newParent->left->parent = nd;
		}
		else
			nd->right = nullptr;
		if (nd->parent != nullptr)
			newParent->parent = nd->parent;
		if (nd->parent == nullptr)
			root = newParent;
		else{
			if (nd == nd->parent->left)
				nd->parent->left = newParent;
			else
				nd->parent->right = newParent;
		}
		newParent->left = nd;
		nd->parent = newParent;
	}
}

void RBtree::rightrotate(node *nd){
	if (nd->left == nullptr)
		return;
	else{
		node *newParent = nd->left;
		if (newParent->right != nullptr){
			nd->left = newParent->right;
			newParent->right->parent = nd;
		}
		else
			nd->left = nullptr;
		if (nd->parent != nullptr)
			newParent->parent = nd->parent;
		if (nd->parent == nullptr)
			root = newParent;
		else{
			if (nd == nd->parent->left)
				nd->parent->left = newParent;
			else
				nd->parent->right = newParent;
		}
		newParent->right = nd;
		nd->parent = newParent;
	}
}

/*RBtree::node* RBtree::successor(node *p){
	node *y = nullptr;
	if (p->left != nullptr){
		y = p->left;
		while (y->right != nullptr)
			y = y->right;
	}
	else{
		y = p->right;
		while (y->left != nullptr)
			y = y->left;
	}
	return y;
}*/

void RBtree::showTree(){
	show(this->root);
}

void RBtree::show(node *p){
	if (root == nullptr){
		cout << "\nEmpty Tree.";
		return;
	}
	if (p != nullptr){
		cout << "\n\t NODE: " << endl;
		cout << "\n Key: " << p->key;
		cout << "\n Value: " << p->value;
		cout << "\n Colour: ";
		if (p->color == 'b')
			cout << "Black";
		else
			cout << "Red";
		if (p->parent != nullptr)
			cout << "\n Parent: " << p->parent->key;
		else
			cout << "\n There is no parent of the node.  ";
		if (p->right != nullptr)
			cout << "\n Right Child: " << p->right->key;
		else
			cout << "\n There is no right child of the node.  ";
		if (p->left != nullptr)
			cout << "\n Left Child: " << p->left->key;
		else
			cout << "\n There is no left child of the node.  ";
		cout << endl;
		if (p->left){
			cout << "\n\nLeft:\n";
			show(p->left);
		}
		else
			cout<<"\nNo Left Child.\n";
		if (p->right) {
			cout << "\n\nRight:\n";
			show(p->right);
		}
		else
			cout << "\nNo Right Child.\n";
	}
}

void RBtree::search(ValueType key){
	if (root == nullptr){
		cout << "\nEmpty Tree\n";
		return ;
	}
	node *nd = root;
	int found = 0;
	while (nd != nullptr && found == 0){
		if (nd->key == key)
			found = 1;
		if (found == 0){
			if (nd->key < key)
				nd = nd->right;
			else
				nd = nd->left;
		}
	}
	if (found == 0)
		cout << "\nElement Not Found.";
	else{
		cout << "\n\t FOUND NODE: " << endl;
		cout << "\n Key: " << nd->key ;
		cout << "\n Value: " << nd->value ;
		cout << "\n Colour: ";
		if (nd->color == 'b')
			cout << "Black";
		else
			cout << "Red";
		if (nd->parent != nullptr)
			cout << "\n Parent: " << nd->parent->key ;
		else
			cout << "\n There is no parent of the node.  ";
		if (nd->right != nullptr)
			cout << "\n Right Child: " << nd->right->key ;
		else
			cout << "\n There is no right child of the node. ";
		if (nd->left != nullptr)
			cout << "\n Left Child: " << nd->left->key << endl;
		else
			cout << "\n There is no left child of the node. " << endl;
	}
}

void RBtree::searchMax() {
	if (root == nullptr) {
		cout << "\nEmpty Tree\n";
		return;
	}
	node *nd = root;
	while (nd->right != nullptr) {
		nd = nd->right;
	}
	cout << "\n\t MAX NODE: " << endl;
	cout << "\n Key: " << nd->key;
	cout << "\n Value: " << nd->value;
	cout << "\n Colour: ";
	if (nd->color == 'b')
		cout << "Black";
	else
		cout << "Red";
	if (nd->parent != nullptr)
		cout << "\n Parent: " << nd->parent->key;
	else
		cout << "\n There is no parent of the node.  ";
	if (nd->right != nullptr)
		cout << "\n Right Child: " << nd->right->key;
	else
		cout << "\n There is no right child of the node.|";
	if (nd->left != nullptr)
		cout << "\n Left Child: " << nd->left->key;
	else
		cout << "\n There is no left child of the node. " << endl;
}

void RBtree::searchMin() {
	if (root == nullptr) {
		cout << "\nEmpty Tree\n";
		return;
	}
	node *nd = root;
	while (nd->left != nullptr) {
		nd = nd->left;
	}
	cout << "\n\t MIN NODE: " << endl;
	cout << "\n Key: " << nd->key ;
	cout << "\n Value: " << nd->value;
	cout << "\n Colour: ";
	if (nd->color == 'b')
		cout << "Black";
	else
		cout << "Red";
	if (nd->parent != nullptr)
		cout << "\n Parent: " << nd->parent->key;
	else
		cout << "\n There is no parent of the node.  ";
	if (nd->right != nullptr)
		cout << "\n Right Child: " << nd->right->key;
	else
		cout << "\n There is no right child of the node.";
	if (nd->left != nullptr)
		cout << "\n Left Child: " << nd->left->key;
	else
		cout << "\n There is no left child of the node. " << endl;
}

bool RBtree::isEmpty() const{
	if (_size == 0)
		return true;
	return false;
}
size_t RBtree::size() const{
	return _size;
}

void RBtree::Clear(node* nd) {
	if(!nd) 
		return;
	Clear(nd->left);
	Clear(nd->right);
	delete nd;
	nd = nullptr;
}

/*int main()
{
	RBtree a;
	a.insertLeaf(2, 2);
	a.insertLeaf(1000, 4);
	a.insertLeaf(995, 5);
	a.insertLeaf(1001, 6);
	a.insertLeaf(997, 7);
	a.insertLeaf(993, 8);
	a.insertLeaf(994, 6);
	//a.search(5);
	a.showTree();
	//RBtree e(a);
	//e.showTree();
	//RBtree b = a;
	//b.showTree();
	a.search(5);
	a.searchMax();
	a.searchMin();
	system("pause");
	return 0;
}*/