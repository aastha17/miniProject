#include"ResultNode.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include<map>
using namespace std;

class View{
public:
	void HorizontalDisplay(vector<ResultNode> &vect){
		int n = vect.size();
		for (int i = 0; i < n; i++){
			cout << vect[i].phrase << "       Total occurences: "<<vect[i].count["all"]<<endl;
			map<string, int>::iterator it;
			for (it = vect[i].count.begin(); it != vect[i].count.end(); it++){
				if (it->first == "all") continue;
				cout << it->first << "  " << it->second << " times" << endl;
			}
		}
	}

	void VerticalDisplay(vector<ResultNode> &vect){
		map<string, map<string, int>> vmap;
		map<string, int> total_occurences;
		int n = vect.size();
		for (int i = 0; i < n; i++){
			map<string, int>::iterator it;
			for (it = vect[i].count.begin(); it != vect[i].count.end(); it++){
				if (it->first == "all") continue;
				vmap[it->first][vect[i].phrase] = it->second;
				total_occurences[it->first] += it->second;
			}
		}
		map<string, int>::iterator it;
		for (it = total_occurences.begin(); it != total_occurences.end(); it++){
			cout << it->first << "       " << it->second << " times" << endl;
			map<string, int>::iterator it1;
			for (it1 = vmap[it->first].begin(); it1 != vmap[it->first].end(); it1++)
				cout << it1->first << " " << it1->second << "times"<<endl;
		}
	}
};

int main(){
	vector<ResultNode> vect;
	ResultNode n1("hello");
	n1.count["file1"] = 30;
	n1.count["file2"] = 40;
	n1.count["file3"] = 50;
	n1.count["all"] = 120;
	vect.push_back(n1);
	ResultNode n2("gentlemAN");
	n2.count["file1"] = 20;
	n2.count["file2"] = 0;
	n2.count["file3"] = 90;
	n2.count["all"] = 110;
	vect.push_back(n2);
	View v;
	v.VerticalDisplay(vect);
	//v.HorizontalDisplay(vect);
	return 0;
}