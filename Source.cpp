#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include<map>
using namespace std;


class node {
public:
	int prefix_count;
	int end_count;
	struct node* child[150];
	map<string, int> file_count;
	map<string, int> prefix_count_mp;
	node::node() {
		prefix_count = 0;
		end_count = 0;
		for (int i = 0; i < 150; ++i) child[i] = NULL;
	}
};

class Trie {
	node* head;

public:
	void ConstructTrie(std::string contents);
	Trie();
	void Insert(std::string,std::string filename);
	int Search(std::string);
	int PrefixSearch(std::string);
	void SearchByFile(std::string word);
	void ComplexSearchUtil(std::string word,node *curr);
	void ComplexSearch(std::string word);
};


Trie::Trie() {
	head = new node();
}

void Trie::ConstructTrie(std::string contents) {
	std::string word;
	istringstream is(contents);
	while (is >> word) {
		//Insert(word);
	}
}

void Trie::ComplexSearch(std::string word) {
	ComplexSearchUtil(word.substr(1), head);
}

void Trie::ComplexSearchUtil(std::string word,node *curr) {
	if (curr == NULL) return;
	node *current = curr;
	for (int i = 0; i < word.length(); ++i)
	{
		//cout << "here1" << endl;
		int letter = (int)word[i];

		if (word[i] == '*'){
			//cout << "here" << endl;
			map<string, int>::iterator it;
			//cout << current->prefix_count_mp.size() << endl;
			for (it = current->prefix_count_mp.begin(); it != current->prefix_count_mp.end(); it++){
				cout << it->first << " " << it->second << " times" << endl;
			}
		}
		if (current->child[letter] == NULL){
			//cout << "here" << endl;
			break;		//not found
		}
		//cout << "here" << endl;
		current = current->child[letter];
		//cout << "hrer2" << endl;
	}
	for (int i = 0; i < 150; i++){
		ComplexSearchUtil(word, curr->child[i]);
	}
}


void Trie::Insert(std::string word,std::string filename)
{
	node *current = head;
	current->prefix_count++;
	current->prefix_count_mp[filename]++;
	for (int i = 0; i < word.length(); ++i)
	{
		int letter = (int)word[i];
		if (current->child[letter] == NULL)
			current->child[letter] = new node();
		current->child[letter]->prefix_count_mp[filename]++;
		//cout << current->child[letter]->prefix_count_mp[filename] << endl;
		current->child[letter]->prefix_count++;
		current = current->child[letter];
	}
	current->end_count++;
	current->file_count[filename]++;
	//cout << filename << " " << current->file_count[filename];
}

int Trie::Search(std::string word)
{
	node *current = head;
	for (int i = 0; i < word.length(); ++i)
	{
		int letter = (int)word[i];
		if (current->child[letter] == NULL)
			return false;		//not found
		current = current->child[letter];
	}
	return current->end_count;
}


void Trie::SearchByFile(std::string word)
{
	node *current = head;
	for (int i = 0; i < word.length(); ++i)
	{
		//cout << "here1" << endl;
		int letter = (int)word[i];

		if (word[i] == '*'){
			//cout << "here" << endl;
			map<string, int>::iterator it;
			//cout << current->prefix_count_mp.size() << endl;
			for (it = current->prefix_count_mp.begin(); it != current->prefix_count_mp.end(); it++){
				cout << it->first << " " << it->second << " times" << endl;
			}
		}
		if (current->child[letter] == NULL){
			//cout << "here" << endl;
			return;		//not found
		}
		//cout << "here" << endl;
		current = current->child[letter];
		//cout << "hrer2" << endl;
	}
	//cout << "here also" << endl;
	//if (current == NULL) return;
	map<string, int>::iterator it;
	for (it = current->file_count.begin(); it != current->file_count.end(); it++){
		cout << it->first << " " << it->second << " times" << endl;
	}
}

int Trie::PrefixSearch(std::string prefix)
{
	node *current = head;
	for (int i = 0; i < prefix.length(); ++i)
	{
		int letter = (int)prefix[i];
		if (current->child[letter] == NULL)
			return 0;
		else
			current = current->child[letter];
	}
	return current->prefix_count;
}


int main(){
	string file1 = "hello";
	Trie trie,rtrie;
	int no_of_files = 10;
	for (int i = 0; i < no_of_files; i++){
		char num = i + '0';
		string num1(1, num);
		string filename = "file " + num1;
		//cout << filename << endl;
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
}