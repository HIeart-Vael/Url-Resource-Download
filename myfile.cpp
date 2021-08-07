#include "myfile.h"
#include <iostream>
using namespace std;

void makeDirectory(string DirectoryPath)
{
    string format_directorypath = format_DirectoryPath(DirectoryPath);

    string command;
    command = "mkdir " + format_directorypath;
    system(command.c_str());
}

string format_DirectoryPath(string DirectoryPath)
{
    string format = "/";
    int len = format.length();

    int off = 0;
    off = DirectoryPath.find(format, 0);
    while (off != string::npos)
    {
        DirectoryPath.replace(off, len, "\\\\");
        off = DirectoryPath.find(format, off+1);
    }
    return DirectoryPath;
}

void search_url_in_file(string FilePath)
{
    std::string tmp, html;
    ifstream fin(FilePath);
    while (getline(fin, tmp))
    {
        tmp += '\n';
        html += tmp;
    }
    fin.close();

    ofstream fout("../URL_FOLDER/all_url.txt");
    // string pattern("http(s)?://([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?");
    string pattern("\\w*:?//([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);

    for (sregex_iterator it(html.begin(), html.end(), r), end; //end是尾后迭代器，regex_iterator是regex_iterator的string类型的版本
         it != end;
         ++it)
    {
        if (NULL == strstr(it->str().c_str(), "http"))
        {
            fout << "http:" << it->str() << endl;
            continue;
        }
        if(NULL != strstr(it->str().c_str(), "https"))
            continue;
        else
        {
            fout << it->str() << endl;
            continue;
        }
    }
    fout.close();
}

int get_how_much_line(ifstream &fin)
{
    string tmp;
    int i;
    while(getline(fin, tmp))
    {
        i++;
    }
    return i;
}