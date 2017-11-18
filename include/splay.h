#pragma once
#include <iostream>
#include <functional>
template <typename T>
class SplayTree
{
private:
	struct Node
	{
		Node *left;
		Node *right;
		Node *parent;
		T key;
		Node(const T& value = T()) : left(nullptr), right(nullptr), parent(nullptr), key(value) {}
	} *root;
	
	
	void _transplant(Node *localParent, Node *localChild)
	{
		if (localParent->parent == nullptr)
			root = localChild;
		else if (localParent == localParent->parent->left)
			localParent->parent->left = localChild;
		else if (localParent == localParent->parent->right)
			localParent->parent->right = localChild;

		if (localChild != nullptr)
			localChild->parent = localParent->parent;
	}

	void _leftRotate(Node *localRoot)
	{
		Node *_right = localRoot->right;

		localRoot->right = _right->left;
		if (_right->left != nullptr)
			_right->left->parent = localRoot;
		_transplant(localRoot, _right);
		_right->left = localRoot;
		_right->left->parent = _right;
	}

	void _rightRotate(Node *localRoot)
	{
		Node *_left = localRoot->left;

		localRoot->left = _left->right;
		if (_left->right != nullptr)
			_left->right->parent = localRoot;
		_transplant(localRoot, _left);
		_left->right = localRoot;
		_left->right->parent = _left;
	}

	Node *_search(const T& value)
	{
		Node *searchedElement = root;
		while (searchedElement != nullptr)
		{
			if (searchedElement->key < value)
				searchedElement = searchedElement->right;
			else if (value < searchedElement->key)
				searchedElement = searchedElement->left;
			else if (searchedElement->key == value)
			{
				_splay(searchedElement);
				return searchedElement;
			}
		}
		return nullptr;
	}

	void _splay(Node *pivot)
	{
		while (pivot != root)
		{
			if (pivot->parent == root) 
			{

				if (pivot == pivot->parent->left)
					_rightRotate(pivot->parent);
				else if (pivot == pivot->parent->right) 
				
					_leftRotate(pivot->parent);
			}
			else 
			{
				// Zig-Zig step.
				if (pivot == pivot->parent->left && pivot->parent == pivot->parent->parent->left)
				{

					_rightRotate(pivot->parent->parent);
					_rightRotate(pivot->parent);

				}
				else if (pivot == pivot->parent->right && pivot->parent == pivot->parent->parent->right) 
				{
					_leftRotate(pivot->parent->parent);
					_leftRotate(pivot->parent);
				}
				// Zig-Zag step.
				else if (pivot == pivot->parent->right && pivot->parent == pivot->parent->parent->left)
				{
					_leftRotate(pivot->parent);
					_rightRotate(pivot->parent);
				}
				else if (pivot == pivot->parent->left && pivot->parent == pivot->parent->parent->right)
				{
					_rightRotate(pivot->parent);
					_leftRotate(pivot->parent);
				}
			}
		}
	}
	

	
public:
		SplayTree() : root(nullptr) {	};
		 ~SplayTree()
		{
			delete root;
		}
		void display(const Node* temp, unsigned int level)const
		{
				if (temp)
				{
					display(temp->left, level + 1);
					for (int i = 0; i < level; i++)
						std::cout << "__";
					std::cout << temp->key << "\n";
					display(temp->right, level + 1);
				}
		}
		

		void insert(const T& value)
		{
			Node *preInsertPlace = nullptr;
			Node *insertPlace = root;
			
			while (insertPlace != nullptr)
			{
				preInsertPlace = insertPlace;

				if (insertPlace->key < value)
					insertPlace = insertPlace->right;
				else if (value < insertPlace->key) {
					insertPlace = insertPlace->left;
				}
			}

			Node *insertElement = new Node(value);
			insertElement->parent = preInsertPlace;


			if (preInsertPlace == nullptr)
				root = insertElement;
			else if (preInsertPlace->key < insertElement->key)
				preInsertPlace->right = insertElement;
			else if (insertElement->key < preInsertPlace->key)
				preInsertPlace->left = insertElement;
		
			_splay(insertElement);
		}

			
		void remove(const T& value)
		{
			Node *removeElement = _search(value);
			//std::cout << removeElement->left;
			if (removeElement != nullptr)
			{
				if (removeElement->right == nullptr)
				{
					_transplant(removeElement, removeElement->left);
				}
				else if (removeElement->left == nullptr)
				{
					_transplant(removeElement, removeElement->right);
				}
				else
				{
					Node *newLocalRoot = removeElement->right;
					while (newLocalRoot->left != nullptr)
					{
						newLocalRoot = newLocalRoot->left;
					}
					if (newLocalRoot->parent != removeElement)
					{
						_transplant(newLocalRoot, newLocalRoot->right);
						newLocalRoot->right = removeElement->right;
						newLocalRoot->right->parent = newLocalRoot;
					}
					_transplant(removeElement, newLocalRoot);
					newLocalRoot->left = removeElement->left;
					newLocalRoot->left->parent = newLocalRoot;
					_splay(newLocalRoot);
				}
				delete[] removeElement;
			}
		}

		
		bool search(T const& value)
		{
			return _search(value);
		}

		Node *getRoot()
		{
			return root;
		}

};


