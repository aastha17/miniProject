#include"Trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include<map>
#include"ResultNode.cpp"


using namespace std;

Trie::Trie() {
	head = new node();
}


void Trie::ComplexSearch(std::string word, vector<ResultNode> &v) {
	ComplexSearchUtil(word.substr(1), head,v);
	ResultNode *final_res = new ResultNode("*"+word);
}

void Trie::ComplexSearchUtil(std::string word, node *curr, vector<ResultNode> &v) {
	if (curr == NULL) return;
	SearchByFileUtil(word, curr,v);
	for (int i = 0; i < 150; i++){
		ComplexSearchUtil(word, curr->child[i],v);
	}
}


void Trie::Insert(std::string word,std::string filename)
{
	node *current = head;
	//current->prefix_count++;
	current->prefix_count_mp[filename]++;
	for (int i = 0; i < word.length(); ++i)
	{
		int letter = (int)word[i];
		if (current->child[letter] == NULL)
			current->child[letter] = new node();
		current->child[letter]->prefix_count_mp[filename]++;
		current = current->child[letter];
	}
	
	current->file_count[filename]++;
}

void Trie::SearchByFile(std::string word, vector<ResultNode> &v){
	SearchByFileUtil(word, head,v);
}

void Trie::SearchByFileUtil(std::string word, node *current, vector<ResultNode> &v)
{
	ResultNode *r = new ResultNode(word);
	for (int i = 0; i < word.length(); ++i)
	{
		int letter = (int)word[i];
		if (word[i] == '*'){
			map<string, int>::iterator it;
			for (it = current->prefix_count_mp.begin(); it != current->prefix_count_mp.end(); it++){
				r->count["all"] += it->second;
				r->count[it->first] = it->second;
			}
			v.push_back(*r);
		}
		if (current->child[letter] == NULL){
			if (word[i] != '*') delete r;   // delete r if not found
			return;		
		}
		current = current->child[letter];
	}
	map<string, int>::iterator it;
	for (it = current->file_count.begin(); it != current->file_count.end(); it++){
		r->count["all"] += it->second;
		r->count[it->first] = it->second;
	}
	v.push_back(*r);
}



/*int main2312(){
	string file1 = "hello";
	Trie trie,rtrie;
	int no_of_files = 10;
	for (int i = 0; i < no_of_files; i++){
		char num = i + '0';
		string num1(1, num);
		string filename = "file " + num1;
		trie.Insert(file1,filename);
		reverse(file1.begin(), file1.end());
		rtrie.Insert(file1, filename);
		file1 = "hello1";
	}
	file1 = "abchelloabc";
	trie.Insert(file1, "file 1");
	reverse(file1.begin(), file1.end());
	rtrie.Insert(file1, "file 1");
	string pattern = "*hello*" ;
	if (pattern.length() != 1 && pattern[0] == '*' && pattern[pattern.length()-1]=='*')
		trie.ComplexSearch(pattern);
	else if (pattern.length() != 0 && pattern[0] == '*'){
		reverse(pattern.begin(), pattern.end());
		//cout << pattern << endl;
		rtrie.SearchByFile(pattern);
	}
	else
	trie.SearchByFile(pattern) ;
	//cout << trie.Search(pattern) << endl;
	return 0;
}*/