#ifndef _MYFILE_H_
#define _MYFILE_H_

#include <fstream>
#include <string>
#include <regex>
using namespace std;

void makeDirectory(string DirectoryPath);       //创建文件夹

string format_DirectoryPath(string DirectoryPath);       //格式化路径，将"\"全部替换为"\\"，方便执行mkdir语句；

void search_url_in_file(string FilePath);

int get_how_much_line(ifstream &fin);

#endif