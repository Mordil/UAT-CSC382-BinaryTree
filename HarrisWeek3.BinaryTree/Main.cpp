#include <iostream>
#include <vector>
#include <string>

#include "MyBinaryTree.h"

using namespace std;

int main()
{
	vector<int> keys = { 10, 5, 2, 1, 8, 17 };
	MyBinaryTree<int, int> tree;

	for (vector<int>::const_iterator i = keys.begin(); i < keys.end(); ++i)
	{
		tree.AddNode(*i, *i, false);
	}

	MyTreeNode<int, int>* foundNode = tree.FindNode(1);

	if (foundNode != NULL)
	{
		cout << "The value for key 1 is: " << foundNode->GetValue() << "\n\n";
	}

	tree.DeleteNode(5);

	foundNode = tree.FindNode(1);

	if (foundNode == NULL)
	{
		cout << "No node found for the key " << to_string(1) << "\n\n";
	}

	int max = tree.GetMaximum();

	cout << "The maximum value in the tree is: " << to_string(max) << "\n\n";

	system("pause");
	return 0;
}
