
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

vector<string> files;


void GetTextFiles(std::string path) {
	HANDLE hFind;
	WIN32_FIND_DATA data;

	//std::string search_path = path ;//+ "\\*.txt";
	string search_path=path+ "\\*.*";
	hFind = FindFirstFile(search_path.c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE) {
		do {
            //if(hFind->d_type==DT_DIR)GetTextFiles()
            /*if((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0//calling recursive function to access subdirectories->not working
              && data.cFileName != "."
              && data.cFileName != "..")
              GetTextFiles(data.cFileName);
              else*/

			files.push_back(path + '\\' + data.cFileName);
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
		return;
	}


}

int main()
{
    string path;
    cin>>path;
    //vector<string>result;
    GetTextFiles(path);
    for(int i=0;i<files.size();i++)cout<<files[i]<<endl;
    return 0;

}
