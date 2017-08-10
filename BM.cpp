#include<iostream>
#include<string>

using namespace std;

static int Max(int a, int b) {
	return a >= b ? a : b;
}

static void BadCharHeuristic(string str, int size, int* badChar) {
	int i;

	for (i = 0; i < 256; i++)
		badChar[i] = -1;

	for (i = 0; i < size; i++)
		badChar[(int)str[i]] = i;
}

static int SearchString(string str, string pat) {
	int count = 0;
	int m = pat.length();
	int n = str.length();

	int* badChar = new int[256];

	BadCharHeuristic(pat, m, badChar);

	int s = 0;
	while (s <= (n - m))
	{
		int j = m - 1;

		while (j >= 0 && pat[j] == str[s + j])
			--j;

		if (j < 0)
		{
			count++;
			s += (s + m < n) ? m - badChar[str[s + m]] : 1;
		}
		else
		{
			s += Max(1, j - badChar[str[s + j]]);
		}
	}

	delete[] badChar;
	
	return count;
}


int main()
{

string data = "the quick brown fox jumps over the lazy dog";
int value = SearchString(data, "the quick brown cat");
cout<<value<<endl;

}
