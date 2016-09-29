#pragma once

#include "MyTreeNode.h"

template <typename K, typename V>
class MyBinaryTree
{
	typedef MyTreeNode<K, V> Node;

public:
	MyBinaryTree() { _rootNode = NULL; }
	~MyBinaryTree() { delete _rootNode; }

	/*
		Adds a node with the given key and value at the highest available point in the tree.
		key = key for the node
		value = the value the node holds
		updateValueOnDuplicate = should a node just be updated if it already exists in the tree
	*/
	bool AddNode(const K& key, const V& value, bool updateValueOnDuplicate)
	{
		Node* nodeToUpdate = FindNode(key);

		if (nodeToUpdate == NULL)
		{
			_addNode(key, value, _rootNode);
			return true;
		}
		else if (updateValueOnDuplicate)
		{
			nodeToUpdate->SetValue(value);
			return true;
		}
		else
		{
			return false;
		}
	}

	/*
		Finds the first node with the given key and deletes it.
		This trims all branches off of said node.
	*/
	void DeleteNode(const K& key)
	{
		// find the node with the given key and delete it when found
		_findNode(key, _rootNode, true);
	}

	V GetMaximum()
	{
		V max;

		if (_rootNode != NULL)
		{
			_compareMaximum(max, _rootNode);
		}

		return max;
	}

	/* Searches the tree for a node that matches the provided key and returns a pointer to it. */
	Node* FindNode(const K& key) { return _findNode(key, _rootNode); }

private:
	Node* _rootNode;

	/*
		Recursive method that finds the first available position highest in the tree and creates a new node with the key and value provided.
		key = the key for the new node
		value = the value for the new node to store
		startingNode = reference to a pointer for a node to start a cycle on
	*/
	void _addNode(const K& key, const V& value, Node*& startingNode)
	{
		// if the current node is null, use it
		if (startingNode == NULL)
		{
			startingNode = new Node(key, value);
		}
		else
		{
			// otherwise, grab both its left & right nodes to reference
			Node* left = startingNode->GetLeftNode();
			Node* right = startingNode->GetRightNode();

			// if the left is null, use its position
			if (left == NULL)
			{
				startingNode->SetLeftNode(new Node(key, value));
			}
			// if left isn't null but the right is, use that position
			else if (right == NULL)
			{
				startingNode->SetRightNode(new Node(key, value));
			}
			// otherwise, check if the grandchildren of the current node are all taken
			else
			{
				// if left is full but right isn't, start a new cycle with it as the starting node
				if (left->IsFull() && !right->IsFull())
				{
					_addNode(key, value, right);
				}
				// otherwise, start a cycle with the left node
				else
				{
					_addNode(key, value, left);
				}
			}
		}
	}

	void _compareMaximum(V& valueToCompare, Node*& startingNode)
	{
		if (startingNode != NULL)
		{
			// compare the current node's value to the passed in value and assign the higher to the parameter
			valueToCompare = (valueToCompare < startingNode->GetValue()) ? startingNode->GetValue() : valueToCompare;
			
			// grab the node's children
			Node* left = startingNode->GetLeftNode();
			Node* right = startingNode->GetRightNode();

			// if the left isn't null, recursively compare the values
			if (left != NULL)
			{
				_compareMaximum(valueToCompare, left);
			}
			
			// same as above for the right child
			if (right != NULL)
			{
				_compareMaximum(valueToCompare, right);
			}
		}
	}
	
	Node* _findNode(const K& key, Node*& startingNode, bool deleteWhenFound = false)
	{
		if (startingNode == NULL)
		{
			return startingNode;
		}
		else
		{
			// check if the starting node's key matches the one being searched
			if (startingNode->GetKey() != key)
			{
				// if not a match, recursively search for a node in the left child
				Node* matchingNode = _findNode(key, startingNode->GetLeftNode(), deleteWhenFound);

				// if the node above was null, start a cycle with the right node
				if (matchingNode == NULL)
				{
					matchingNode = _findNode(key, startingNode->GetRightNode(), deleteWhenFound);
				}

				return matchingNode;
			}
			else
			{
				// check if the node is to be deleted
				if (deleteWhenFound)
				{
					// delete the node and set the pointer to null
					delete startingNode;
					startingNode = NULL;
				}

				return startingNode;
			}
		}
	}
};
