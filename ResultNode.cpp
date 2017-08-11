#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

class ResultNode{
public:

	string phrase;
	map<string, int> count;
	ResultNode(string phrase) : phrase(phrase)
	{
	}

};

