#pragma once

template <typename K, typename V>
class MyTreeNode
{
public:
	MyTreeNode(const K& key, const V& value)
	{
		_key = key;
		_value = value;
		_leftNode = NULL;
		_rightNode = NULL;
	}
	~MyTreeNode()
	{
		delete _leftNode, _rightNode;
		_leftNode = NULL;
		_rightNode = NULL;
	}

	void SetValue(const V& value) { _value = value; }
	void SetLeftNode(MyTreeNode* node) { _leftNode = node; }
	void SetRightNode(MyTreeNode* node) { _rightNode = node; }

	bool IsFull() const { return _leftNode != NULL && _rightNode != NULL; }

	const K& GetKey() const { return _key; }
	const V& GetValue() const { return _value; }

	MyTreeNode*& GetLeftNode() { return _leftNode; }
	MyTreeNode*& GetRightNode() { return _rightNode; }

private:
	K _key;
	V _value;

	MyTreeNode* _leftNode;
	MyTreeNode* _rightNode;
};
