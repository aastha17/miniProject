
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

vector<string> files;

void TransverseDirectory(string path)
{
    WIN32_FIND_DATA data;
    string fname = path + "\\*.*";
    HANDLE h = FindFirstFile(fname.c_str(),&data);
    if(h != INVALID_HANDLE_VALUE)
    {
        do {
            if( (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
            {
                if( strcmp(data.cFileName,".") != 0 &&strcmp(data.cFileName,"..") != 0)
                {
                    fname = path + "\\" + data.cFileName;
                    TransverseDirectory(fname);
                }
            }
            else
            {
                string x=path+"\\*.txt";
                string a= data.cFileName;
                reverse(a.begin(),a.end());
                if(a[0]=='t' && a[1]=='x' && a[2]=='t')
                files.push_back(path + "\\" +data.cFileName);

            }
        }while( FindNextFile(h,&data) != 0);
        FindClose(h);
    }
    return;
}
int main(int argc, char* argv[])
{
    string path;
    cin>>path;
    TransverseDirectory(path);

    return 0;
}


