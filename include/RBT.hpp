#include <iostream>
#include<string>
#include <stdexcept>
using namespace std;

enum Color{ RED, BLACK, BLACK_BLACK };

template<typename T>
struct Node
{
	Node<T> * left_;
	Node<T> * right_;
	Node<T> * parent_;
	Color color_;
	T key_;
	Node(T const & key) : key_{ key }, left_{ nullptr }, right_{ nullptr }, parent_{ nullptr }, color_{ RED } {}
};

template<typename T>
class Tree
{
private:
	Node<T> * root_;
	unsigned count_;

	void deleteNode_(Node<T> * node);

	ostream& print_(ostream&stream);
	ostream& print_(Node<T> * node, ostream&stream, size_t level)const;

	void insert_(Node<T> * node, const T& key);
	void insertBalance_(Node<T> * cur);

	void changeColor_(Node<T> * node);
	void rotateRight_(Node<T> * node);
	void rotateLeft_(Node<T> * node);
	Node<T> * sibling_(Node<T> * node);

	void deleteBalance_(Node<T> * node);
public:
	Tree();
	~Tree();

	Node<T> * search(const T& key)const;
	Node<T> * left(T key)
	{
		Node<T> * node = search(key);
		return node->left_;
	}
	Node<T> * right(T key)
	{
		Node<T> * node = search(key);
		return node->right_;
	}
	Node<T> * parent(T key)
	{
		Node<T> * node = search(key);
		return node->parent_;
	}
	Color color(T key)
	{
		Node<T> * node = search(key);
		return node->color_;
	}
	Node<T> * root()
	{
		return root_;
	}
	unsigned int count()
	{
		return count_;
	}

	friend ostream& operator << (ostream&stream, Tree<T> & tree)
	{
		return tree.print_(cout);
	}

	void insert(const T& key);

	void deleteElement(const T& key);
};

template<typename T>
Tree<T>::Tree() : root_{ nullptr }, count_{ 0 } {};
template<typename T>
Tree<T>::~Tree()
{
	deleteNode_(root_);
}
template<typename T>
void Tree<T>::deleteNode_(Node<T> * node)
{
	if (node == nullptr) return;
	deleteNode_(node->left_);
	deleteNode_(node->right_);
	delete node;
}

template<typename T>
Node<T> * Tree<T>::search(const T& key)const
{
	Node<T> * cur = root_;
	while (cur != nullptr)
	{
		if (cur->key_ == key)
			break;
		else
		{
			if (key > cur->key_)
				cur = cur->right_;
			else cur = cur->left_;
		}
	}
	return cur;
}

template<typename T>
ostream & Tree<T>::print_(ostream&stream)
{
	print_(root_, stream, 0);
	return stream;
}
template<typename T>
ostream & Tree<T>::print_(Node<T> * node, ostream&stream, size_t level)const
{
	Node<T> * cur = node;
	if (cur != nullptr)
	{
		string a;
		if (cur->color_ == RED)
			a = "r";
		else a = "b";
		print_(cur->right_, stream, level + 1);
		for (unsigned int i = 0; i < level; ++i)
			stream << '-';
		stream << cur->key_ << " (" << a << ")" << endl;
		print_(cur->left_, stream, level + 1);
	}
	return stream;
}

template<typename T>
void Tree<T>::insert(const T& key)
{
	insert_(root_, key);
}
template<typename T>
void Tree<T>::insert_(Node<T> * node, const T& key)
{
	Node<T> * parent = nullptr;
	Node<T> * cur = node;
	while (cur)
	{
		parent = cur;
		if (key == cur->key_)
			throw logic_error("There is this element in the tree\n");
		if (key < cur->key_)
			cur = cur->left_;
		else //if (key > node->key_)
			cur = cur->right_;
	}
	cur = new Node<T>(key);
	count_++;
	cur->parent_ = parent;
	if (cur->parent_ == nullptr)
	{
		root_ = cur;
		root_->color_ = BLACK;
	}
	else
	{
		if (key < parent->key_)
			parent->left_ = cur;
		else parent->right_ = cur;
		insertBalance_(cur);
	}
}
template<typename T>
void Tree<T>::insertBalance_(Node<T> * cur)
{
	while (cur != root_ && cur->parent_->color_ == RED && cur->color_ == RED)
	{
		Node<T> * uncle = nullptr;
		if (cur->parent_->parent_->left_ == cur->parent_)
			uncle = cur->parent_->parent_->right_;
		else uncle = cur->parent_->parent_->left_;

		if (uncle == nullptr || uncle->color_ == BLACK)
		{
			if (cur->parent_->parent_->left_ == cur->parent_ && cur->parent_->left_ == cur)
			{
				cur->parent_->color_ = BLACK;
				cur->parent_->parent_->color_ = RED;
				rotateRight_(cur->parent_->parent_);
			}
			else if (cur->parent_->parent_->right_ == cur->parent_ && cur->parent_->right_ == cur)
			{
				cur->parent_->color_ = BLACK;
				cur->parent_->parent_->color_ = RED;
				rotateLeft_(cur->parent_->parent_);
			}
			else if (cur->parent_->parent_->left_ == cur->parent_ && cur->parent_->right_ == cur)
			{
				cur->color_ = BLACK;
				cur->parent_->parent_->color_ = RED;
				rotateLeft_(cur->parent_);
				rotateRight_(cur->parent_);
			}
			else if (cur->parent_->parent_->right_ == cur->parent_ && cur->parent_->left_ == cur)
			{
				cur->color_ = BLACK;
				cur->parent_->parent_->color_ = RED;
				rotateRight_(cur->parent_);
				rotateLeft_(cur->parent_);
			}
		}
		else if (uncle->color_ == RED)
		{
			changeColor_(cur);
			cur = cur->parent_->parent_;
			root_->color_ = BLACK;
		}
	}
}

template<typename T>
void Tree<T>::deleteElement(const T& key)
{
	Node<T> * cur = search(key);
	if (cur == nullptr)
		return;

	if (cur->left_ == nullptr && cur->right_ == nullptr)
	{
		count_--;
		if (cur->parent_->left_ == cur)
			cur->parent_->left_ = nullptr;
		else //if (cur->parent_->right_ == cur)
			cur->parent_->right_ = nullptr;
	}
	else if (cur->left_ != nullptr && cur->right_ == nullptr)
	{
		count_--;
		if (cur->color_ == RED)
		{
			if (cur->parent_->left_ == cur)
				cur->parent_->left_ = cur->left_;
			else cur->parent_->right_ = cur->left_;
		}
		else
		{
			if (cur->left_->color_ == RED)
			{
				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = cur->left_;
					cur->parent_->left_->color_ = BLACK;
				}
				else
				{
					cur->parent_->right_ = cur->left_;
					cur->parent_->right_->color_ = BLACK;
				}
			}
			else
			{
				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = cur->left_;
					cur->parent_->left_->color_ = BLACK_BLACK;
					deleteBalance_(cur->parent_->left_);
				}
				else
				{
					cur->parent_->right_ = cur->left_;
					cur->parent_->right_->color_ = BLACK_BLACK;
					deleteBalance_(cur->parent_->right_);
				}
			}
		}
		cur->left_->parent_ = cur->parent_;
	}
	else
	{
		Node<T> * min = cur->right_;
		while (min->left_)
			min = min->left_;
		T a = min->key_;
		deleteElement(min->key_);
		cur->key_ = a;
	}
}
template<typename T>
void Tree<T>::deleteBalance_(Node<T> * node)
{
	Node<T> * cur = node;

	while (cur->color_ == BLACK_BLACK)
	{
		Node<T> * brother = sibling_(cur);
		if ((brother->left_ && brother->left_->color_ == RED) || (brother->right_ && brother->right_->color_ == RED))
		{
			if (cur->parent_->left_ == cur)
			{
				if (!brother->right_ || brother->right_->color_ == BLACK)
				{
					brother->left_->color_ = BLACK;
					brother->color_ = RED;
					rotateRight_(brother);
				}
				else
				{
					brother->right_->color_ = BLACK;
					brother->color_ = cur->parent_->color_;
					cur->parent_->color_ = BLACK;
					cur->color_ = BLACK;
					rotateLeft_(cur->parent_);
				}
			}
			else
			{
				if (brother->right_ && brother->left_->color_ == BLACK)
				{
					brother->right_->color_ = BLACK;
					brother->color_ = RED;
					rotateLeft_(brother);
				}
				else
				{
					brother->left_->color_ = BLACK;
					brother->color_ = cur->parent_->color_;
					cur->parent_->color_ = BLACK;
					cur->color_ = BLACK;
					rotateRight_(cur->parent_);
				}
			}
		}
		else
		{
			if (cur->parent_->color_ == RED)
			{
				cur->parent_->color_ = BLACK;
				brother->color_ = RED;
				cur->color_ = BLACK;
			}
			else
			{
				if (brother->color_ == BLACK)
				{
					cur->parent_->color_ = BLACK_BLACK;
					brother->color_ = RED;
					cur->color_ = BLACK;
					cur = cur->parent_;
				}
				else if (brother->color_ == RED)
				{
					if (cur->parent_->left_ == cur)
					{
						brother->color_ = BLACK;
						cur->parent_->color_ = RED;
						rotateLeft_(cur->parent_);
					}
					else
					{
						brother->color_ = BLACK;
						cur->parent_->color_ = RED;
						rotateRight_(cur->parent_);
					}
				}
			}
		}
	}
}

template<typename T>
void Tree<T>::changeColor_(Node<T> * node)
{
	node->parent_->parent_->left_->color_ = node->parent_->parent_->right_->color_ = BLACK;
	node->parent_->parent_->color_ = RED;
}
template<typename T>
void Tree<T>::rotateRight_(Node<T> * node)
{
	Node<T> * a = node->left_;
	node->left_ = a->right_;
	if (a->right_)
		a->right_->parent_ = node;
	a->parent_ = node->parent_;
	if (node->parent_ == nullptr)
		root_ = a;
	else if (node == node->parent_->right_)
		node->parent_->right_ = a;
	else node->parent_->left_ = a;
	a->right_ = node;
	node->parent_ = a;
}
template<typename T>
void Tree<T>::rotateLeft_(Node<T> * node)
{
	Node<T> * a = node->right_;
	node->right_ = a->left_;
	if (a->left_)
		a->left_->parent_ = node;
	a->parent_ = node->parent_;
	if (node->parent_ == nullptr)
		root_ = a;
	else if (node == node->parent_->left_)
		node->parent_->left_ = a;
	else node->parent_->right_ = a;
	a->left_ = node;
	node->parent_ = a;
}
template<typename T>
Node<T> * Tree<T>::sibling_(Node<T> * node)
{
	if (node && node->parent_)
	{
		if (node->parent_->left_ == node)
			return node->parent_->right_;
		else return node->parent_->left_;
	}
	return nullptr;
}
