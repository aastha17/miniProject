#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include<map>
#include<vector>

#include"ResultNode.cpp"
using namespace std;

class node {
public:
	struct node* child[150];
	map<string, int> file_count;
	map<string, int> prefix_count_mp;
	node::node() {
		for (int i = 0; i < 150; ++i) child[i] = NULL;
	}
};

class Trie {
	node* head;

public:

	Trie();
	void Insert(std::string, std::string filename);
	void SearchByFile(std::string word,vector<ResultNode> &v);
	void SearchByFileUtil(std::string word, node *curr , vector<ResultNode> &v);
	void ComplexSearchUtil(std::string word, node *curr, vector<ResultNode> &v);
	void ComplexSearch(std::string word, vector<ResultNode> &v);
};
