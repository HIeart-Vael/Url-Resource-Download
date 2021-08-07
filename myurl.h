#ifndef _MYURL_H_
#define _MYURL_H_

#include <regex>
#include <iostream>
#include <string>

using namespace std;
class URL{
private:
    string m_url;
    string m_Protocol;    //URL使用的协议
    string m_Hostname;    //远程主机名
    string m_RemoteFilePath;      //文件地址
    int m_Port;       //端口号

public:
    URL(string url);
    string getProtocol();
    string getHostname();
    string getFilePath();       //远程文件完成路径，带文件及文件类型 /a/b/c.txt
    string getRemoteDirectoryPath();  //远程文件夹目录 /a/b
    string getDirectoryPath();      //本地文件夹目录 ../URL_FOLDER/a/b
    string getFileType(); 
    string getFile();      
    int getPort();
    bool getElements();

};

#endif