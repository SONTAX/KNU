#ifndef TREE_HXX_
#define TREE_HXX_

#include "Tree.h"

template<typename T>
TreeNode<T>* Tree<T>::BuildTree(size_t h) {
	T input;
	TreeNode<T>* r00t = new TreeNode<T>;
	if (h == 0) {
		return nullptr;
	}
	cin >> input;
	r00t->value = input;
	r00t->left = BuildTree(h - 1);
	r00t->right = BuildTree(h - 1);
	return r00t;
}

template<typename T>
TreeNode<T>* Tree<T>::BuildRandomTree(size_t h) {
	T input;
	TreeNode<T>* r00t = new TreeNode<T>;
	if (h == 0) {
		return nullptr;
	}
	input = rand() % 11;
	r00t->value = input;
	r00t->left = BuildRandomTree(h - 1);
	r00t->right = BuildRandomTree(h - 1);
	return r00t;
}

template<typename T>
void Tree<T>::PrintTreeAsTree(TreeNode<T>* root, int level) {
	if (root) {
		PrintTreeAsTree(root->right, level + 1);
		for (int i = 0; i < level; i++) {
			output += "   ";
		}
		output += to_string(root->value) + "\n";
		PrintTreeAsTree(root->left, level + 1);
	}
}

template<typename T>
void Tree<T>::PrintTreeInOrder(TreeNode<T>* root) {
	if (root) {
		PrintTreeInOrder(root->left);
		output += to_string(root->value) + " ";
		PrintTreeInOrder(root->right);
	}
}

template<typename T>
string Tree<T>::Output() {
	string temp = output;
	output = "";
	return temp;
}

template<typename T>
TreeNode<T>* Tree<T>::BuildRandomBST(int count) {
	T val;
	val = (rand() % 250) / 6;
	TreeNode<T>* r00t = SearchInsert(nullptr, val);
	for (int i = 1; i < count; i++) {
		val = (rand() % 250) / 6;
		SearchInsert(r00t, val);
	}
	return r00t;
}

template<typename T>
TreeNode<T>* Tree<T>::BuildBST(int count) {
	T val;
	cin >> val;
	TreeNode<T>* r00t = SearchInsert(nullptr, val);
	for (int i = 1; i < count; i++) {
		cin >> val;
		SearchInsert(r00t, val);
	}
	return r00t;
}

template<typename T>
TreeNode<T>* Tree<T>::DeleteByValue(T val, TreeNode<T>* rt) {
	if (rt) {
		if (rt->value == val) {
			rt = nullptr;
		}
		else {
			if ((rt->left) && (rt->left->value == val)) {
				rt->left = nullptr;
			}
			else if ((rt->right) && (rt->right->value == val)) {
				rt->right = nullptr;
			}
			else {
				DeleteByValue(val, rt->left);
				DeleteByValue(val, rt->right);
			}
		}
	}
	return rt;
}

template<typename T>
TreeNode<T>* Tree<T>::DeleteByAdress(TreeNode<T>* rt, TreeNode<T>* found_node) {
	if (rt) {
		if (rt == found_node) {
			rt = nullptr;
		}
		else {
			if (rt->left == found_node) {
				rt->left = nullptr;
			}
			else if (rt->right == found_node) {
				rt->right = nullptr;
			}
			else {
				DeleteByAdress(rt->left, found_node);
				DeleteByAdress(rt->right, found_node);
			}
		}
	}
	return rt;
}

template<typename T>
bool Tree<T>::Find(T val, TreeNode<T>* r00t) {
	TreeNode<T>* cur = r00t;
	bool found = false;
	if (cur) {
		if (cur->value == val) {
			found = true;
			found_node = cur;
			return true;
		}
		else {
			found = Find(val, cur->left);
			found = Find(val, cur->right);
		}
	}
	return false;
}

template<typename T>
TreeNode<T>* Tree<T>::SearchInsert(TreeNode<T>* r00t, T val) {
	if (r00t == nullptr) {
		TreeNode<T>* new_root = new TreeNode<T>;
		new_root->left = nullptr;
		new_root->right = nullptr;
		new_root->value = val;
		r00t = new_root;
		return r00t;
	}
	else {
		TreeNode<T>* prev = nullptr;
		TreeNode<T>* cur = r00t;
		bool found = false;
		while (cur && !found) {
			prev = cur;
			if (val == cur->value) {
				found = true;
			}
			else if (val < cur->value) {
				cur = cur->left;
			}
			else {
				cur = cur->right;
			}
		}
		if (found) {
			return cur;
		}
		TreeNode<T>* tnew = new TreeNode<T>;
		tnew->value = val;
		tnew->left = nullptr;
		tnew->right = nullptr;
		if (val < prev->value) {
			prev->left = tnew;
		}
		else {
			prev->right = tnew;
		}
		return tnew;
	}
}

#endif