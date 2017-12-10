#include <iostream>
#include<string>
#include <stdexcept>
using namespace std;

enum Color{ RED, BLACK };

template<typename T>
struct Node
{
	Node<T> * left;
	Node<T> * right;
	Node<T> * parent;
	Color color;
	T value;
	Node(T const & value) : value{ value }, left{ nullptr }, right{ nullptr }, parent{ nullptr }, color{ RED } {}
};

template<typename T>
class Tree
{
private:
	Node<T> * root;
	unsigned int count;

	void deleteNode(Node<T> * node);

	ostream& print(ostream&stream);
	ostream& print(Node<T> * node, ostream&stream, size_t level)const;

	void insert(Node<T> * node, const T& value);
	void insertBalance(Node<T> * cur);

	Node<T>* deleteRoot(Node<T> * head);
	void deleteBalance(Node<T> * node);

	void change_color(Node<T> * node);
	void turn_right(Node<T> * node);
	void turn_left(Node<T> * node);
	Node<T> * sibling(Node<T> * node);
public:
	Tree();
	~Tree();

	Node<T> * search(const T& value)const;
	Node<T> * left_(T key)
	{
		Node<T> * node = search(key);
		return node->left;
	}
	Node<T> * right_(T key)
	{
		Node<T> * node = search(key);
		return node->right;
	}
	Node<T> * parent_(T key)
	{
		Node<T> * node = search(key);
		return node->parent;
	}
	Color color_(T key)
	{
		Node<T> * node = search(key);
		return node->color;
	}
	Node<T> * root_()
	{
		return root;
	}
	unsigned int count_()
	{
		return count;
	}

	friend ostream& operator << (ostream&stream, Tree<T> & tree)
	{
		return tree.print(cout);
	}

	void insert(const T& value);

	void deleteEl(const T& value);
};

template<typename T>
Tree<T>::Tree() : root{ nullptr }, count{ 0 } {};
template<typename T>
Tree<T>::~Tree()
{
	deleteNode(root);
}
template<typename T>
void Tree<T>::deleteNode(Node<T> * node)
{
	if (node == nullptr) return;
	deleteNode(node->left);
	deleteNode(node->right);
	delete node;
}

template<typename T>
Node<T> * Tree<T>::search(const T& value)const
{
	Node<T> * curEl = root;
	while (curEl != nullptr)
	{
		if (curEl->value == value)
			break;
		else
		{
			if (value > curEl->value)
				curEl = curEl->right;
			else curEl = curEl->left;
		}
	}
	return curEl;
}

template<typename T>
ostream & Tree<T>::print(ostream&stream)
{
	print(root, stream, 0);
	return stream;
}
template<typename T>
ostream & Tree<T>::print(Node<T> * node, ostream&stream, size_t level)const
{
	Node<T> * cur = node;
	if (cur != nullptr)
	{
		string a;
		if (cur->color == RED)
			a = "r";
		else a = "b";
		print(cur->right, stream, level + 1);
		for (unsigned int i = 0; i < level; ++i)
			stream << '-';
		stream << cur->value << " (" << a << ")" << endl;
		print(cur->left, stream, level + 1);
	}
	return stream;
}

template<typename T>
void Tree<T>::insert(const T& value)
{
	insert(root, value);
}
template<typename T>
void Tree<T>::insert(Node<T> * node, const T& value)
{
	Node<T> * parent = nullptr;
	Node<T> * cur = node;
	while (cur)
	{
		parent = cur;
		if (value == cur->value)
			throw logic_error("There is this element in the tree\n");
		if (value < cur->value)
			cur = cur->left;
		else //if (value > node->value)
			cur = cur->right;
	}
	cur = new Node<T>(value);
	count++;
	cur->parent = parent;
	if (cur->parent == nullptr)
	{
		root = cur;
		root->color = BLACK;
	}
	else
	{
		if (value < parent->value)
			parent->left = cur;
		else parent->right = cur;
		insertBalance(cur);
	}
}
template<typename T>
void Tree<T>::insertBalance(Node<T> * cur)
{
	while (cur != root && cur->parent->color == RED && cur->color == RED)
	{
		Node<T> * uncle = nullptr;
		if (cur->parent->parent->left == cur->parent)
			uncle = cur->parent->parent->right;
		else uncle = cur->parent->parent->left;

		if (uncle == nullptr || uncle->color == BLACK)
		{
			if (cur->parent->parent->left == cur->parent && cur->parent->left == cur)
			{
				cur->parent->color = BLACK;
				cur->parent->parent->color = RED;
				turn_right(cur->parent->parent);
			}
			else if (cur->parent->parent->right == cur->parent && cur->parent->right == cur)
			{
				cur->parent->color = BLACK;
				cur->parent->parent->color = RED;
				turn_left(cur->parent->parent);
			}
			else if (cur->parent->parent->left == cur->parent && cur->parent->right == cur)
			{
				cur->color = BLACK;
				cur->parent->parent->color = RED;
				turn_left(cur->parent);
				turn_right(cur->parent);
			}
			else if (cur->parent->parent->right == cur->parent && cur->parent->left == cur)
			{
				cur->color = BLACK;
				cur->parent->parent->color = RED;
				turn_right(cur->parent);
				turn_left(cur->parent);
			}
		}
		else if (uncle->color == RED)
		{
			change_color(cur);
			cur = cur->parent->parent;
			root->color = BLACK;
		}
	}
}

template<typename T>
void Tree<T>::deleteEl(const T& value)
{
	Node<T> *cur = root, *parent = nullptr;
	if (cur == nullptr)
		return;

	if (root->value == value)
	{
		root = deleteRoot(root);
		root->color = BLACK;
		root->parent = nullptr;
	}
	else
	{
		parent = root;
		if (value < parent->value)
			cur = parent->left;
		else cur = parent->right;
		while (cur)
		{
			if (cur->value == value)
			{
				if (value < parent->value)
					parent->left = deleteRoot(parent->left);
				else parent->right = deleteRoot(parent->right);
				return;
			}
			parent = cur;
			if (value < parent->value)
				cur = parent->left;
			else cur = parent->right;
		}
	}
}
template<typename T>
Node<T> * Tree<T>::deleteRoot(Node<T> * head)
{
	Node<T>* cur = nullptr, *parent = nullptr;
	if (head)
	{
		count--;
		cur = head->right;
		if (!cur)
		{
			cur = head->left;
		}
		else
		{
			if (cur->left)
			{
				parent = head;
				while (cur->left)
				{
					parent = cur;
					cur = cur->left;
				}
				parent->left = cur->right;
				cur->right = head->right;
			}
			cur->left = head->left;
		}
		deleteBalance(head);
		delete head;
		return cur;
	}
	return nullptr;
}
template<typename T>
void Tree<T>::deleteBalance(Node<T> * node)
{
	Node<T>* sib = nullptr;
	while (node && (node != root) && (node->color == BLACK))
	{
		sib = sibling(node);
		if (sib && (sib == sib->parent->right))
		{
			if (sib->color == RED)
			{
				sib->color = BLACK;
				node->parent->color = RED;
				turn_left(node->parent);
				sib = sibling(node);
			}
			if ((!sib->left || sib->left->color == BLACK) && (!sib->right || sib->right->color == BLACK))
			{
				sib->color = RED;
				node = node->parent;
			}
			else
			{
				if (!sib->right || sib->right->color == BLACK)
				{
					sib->left->color = BLACK;
					sib->color = RED;
					turn_right(sib);
					sib = sibling(node);
				}
				sib->color = node->parent->color;
				node->parent->color = BLACK;
				sib->right->color = BLACK;
				turn_left(node->parent);
				node = root;
			}
		}
		else
		{
			if (sib->color == RED)
			{
				sib->color = BLACK;
				node->parent->color = RED;
				turn_right(node->parent);
				sib = sibling(node);
			}
			if ((!sib->right || sib->right->color == BLACK) && (!sib->left || sib->left->color == BLACK))
			{
				sib->color = RED;
				node = node->parent;
			}
			else
			{
				if (!sib || sib->left->color == BLACK)
				{
					sib->right->color = BLACK;
					sib->color = RED;
					turn_left(sib);
					sib = sibling(node);
				}
				sib->color = node->parent->color;
				node->parent->color = BLACK;
				sib->left->color = BLACK;
				turn_right(node->parent);
				node = root;
			}
		}
	}
	node->color = BLACK;
}

template<typename T>
void Tree<T>::change_color(Node<T> * node)
{
	node->parent->parent->left->color = node->parent->parent->right->color = BLACK;
	node->parent->parent->color = RED;
}
template<typename T>
void Tree<T>::turn_right(Node<T> * node)
{
	Node<T> * a = node->left;
	node->left = a->right;
	if (a->right)
		a->right->parent = node;
	a->parent = node->parent;
	if (node->parent == nullptr)
		root = a;
	else if (node == node->parent->right)
		node->parent->right = a;
	else node->parent->left = a;
	a->right = node;
	node->parent = a;
}
template<typename T>
void Tree<T>::turn_left(Node<T> * node)
{
	Node<T> * a = node->right;
	node->right = a->left;
	if (a->left)
		a->left->parent = node;
	a->parent = node->parent;
	if (node->parent == nullptr)
		root = a;
	else if (node == node->parent->left)
		node->parent->left = a;
	else node->parent->right = a;
	a->left = node;
	node->parent = a;
}
template<typename T>
Node<T> * Tree<T>::sibling(Node<T> * node)
{
	if (node && node->parent)
	{
		if (node->parent->left == node)
			return node->parent->right;
		else return node->parent->left;
	}
	return nullptr;
}
