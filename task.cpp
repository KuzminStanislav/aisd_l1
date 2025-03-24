#include <iostream>
#include <vector>
#include "tree.cpp"

template<typename T>
std::vector<T> union_tree(BinaryTree<T>& tree1, BinaryTree<T>& tree2) {
	std::vector<T> vec1 = tree1.to_vector();
	std::vector<T> vec2 = tree2.to_vector();
	std::vector<T> result;
	
	result.insert(result.end(), vec1.begin(), vec1.end());
	for (T& elem : vec2) {
		if (std::find(result.begin(), result.end(), elem) == result.end()) {
			result.push_back(elem);
		}
	}
	return result;
}

template<typename T>
std::vector<T> intersection_tree(BinaryTree<T>& tree1, BinaryTree<T>& tree2) {
	std::vector<T> vec1 = tree1.to_vector();
	std::vector<T> vec2 = tree2.to_vector();
	std::vector<T> result;

	for (T& elem : vec1) {
		if (std::find(vec2.begin(), vec2.end(), elem) != vec2.end()) {
			result.push_back(elem);
		}
	}
	return result;
}