#pragma once

using ValueType = int;

class RBtree{
	struct node {
		node(const ValueType& value, const ValueType& key, node *parent = nullptr, node *left = nullptr, node *right = nullptr, char color = 'r' );
		~node();
		ValueType value, key;
		node *parent;
		char color;
		node *left;
		node *right;
		static node *copyNode(node*);
	};
	
public:
	//������� �������
	RBtree();
	RBtree(const RBtree& copyRBtree); 
	RBtree& operator=(const RBtree& copyRBtree); 
	~RBtree();

	//����������
	void insertLeaf(ValueType key, ValueType value);
	void insertLeafFix(node *);

	//�������
	void leftrotate(node *);
	void rightrotate(node *);

	//��������
	void deleteLeaf(ValueType key);
	void deleteAllLeavesByKey(ValueType key);
	void deleteLeafFix(node *);

	//�����
	void search(ValueType key);
	void searchMax();
	void searchMin();

	bool isEmpty() const;//+
	size_t size() const;//+

	//�����
	void showTree();
	void show(node*);

	void Clear(node *);

private:
	node* root;
	size_t _size;
};