//https://zhidao.baidu.com/question/14674128.html  URL举例
#include "mysock.h"
#include "myfile.h"
#include "myurl.h"
#include "download.h"

//#include <algorithm>
#define BUFFER_SIZE 102400

using namespace std;
int main()
{
    int Socket;  
    Socket = initial_WSA(); //初始化DLL，并创建一个Socket，成功则返回Socket，否则返回SOCKET_ERROR
    if(Socket == SOCKET_ERROR) return 0;

    string url;
    cout << "Please input the URL:" ;
    cin >> url; //输入URL
    URL obj_url(url); //构造URL类的对象 obj_url

    bool isvalid = obj_url.getElements(); //用getElement函数解析url
    if(!isvalid)
    {
        cout << "your url is not true! " << endl;
        return 0;
    }
    cout << "The protocol is: " << obj_url.getProtocol() << endl;
    cout << "The hostname is: " << obj_url.getHostname() << endl;
    cout << "The port is: " << obj_url.getPort() << endl;
    cout << "The request parameters is: " << obj_url.getFilePath() << endl;
    cout << "The file type is: " << obj_url.getFileType() << endl;
    cout << "The file path is: " << obj_url.getRemoteDirectoryPath() << endl;
    cout << "The file name is: " << obj_url.getFile() << endl;

    link_WSA(Socket, obj_url); //建立连接

    char send_Buffer[BUFFER_SIZE];
    char recv_Buffer[BUFFER_SIZE];

    send_WSA(Socket, send_Buffer, BUFFER_SIZE, obj_url); //发送GET请求

    string directory_path = obj_url.getDirectoryPath();
    cout << "### create filepath in ###" << directory_path << endl;
    string filetype = obj_url.getFileType();

    makeDirectory(directory_path);

    string file_path = directory_path+"/target."+filetype;
    
    ofstream fout(file_path);
    download_resources(Socket, recv_Buffer, BUFFER_SIZE, fout); //接收响应并从缓冲区下载到fout流对象
    fout.close();
    closesocket(Socket);

    search_url_in_file(file_path); //查询输入文件路径下该文件内部所有的 http 类型url，下载到同级文件夹下的all_url.txt中


    ifstream tmp_fin("..\\URL_FOLDER\\all_url.txt");
    int line_number = get_how_much_line(tmp_fin);
    int *filename = new int[line_number];   //文件名数组，给同名文件加上序号
    for(int i=0; i<line_number; i++)
    {
        filename[i] = i+1;
    }

    ifstream fin("..\\URL_FOLDER\\all_url.txt");
    string deepURL;
    for(int i=0; i<line_number; i++)
    {
        getline(fin, deepURL);
        string aaa = "=";
        if(NULL != strstr(deepURL.c_str(), aaa.c_str()))
            continue;

        cout << i+1 << ". the deep url is: " << deepURL << endl;
        URL deep_url(deepURL);
        bool is_valid = deep_url.getElements(); //url是否合法判断
        if (is_valid)
        {
            memset(send_Buffer, 0, BUFFER_SIZE);
            memset(recv_Buffer, 0, BUFFER_SIZE);
            string tmp_deep_directory_path = deep_url.getDirectoryPath(); //本地存放的文件夹路径
            if(tmp_deep_directory_path[tmp_deep_directory_path.length()-1] != '/')
                tmp_deep_directory_path += "/";

            string deep_directory_path = tmp_deep_directory_path + "in";

            string str = deep_url.getFilePath();
            if (str == "")
            {
                str = "/";
            }
            string deep_file = deep_url.getFile();                           //本地存放的文件夹名称
            auto sign = str.find_last_of('.', str.length() - 1);
            int pos1, pos2;
            if (sign != string::npos)
            {
                pos1 = (int)sign;
                string tmp_str = str.substr(0, pos1 + 1);
                sign = tmp_str.find_last_of('/', str.length() - 1);
                pos2 = (int)sign;
                string tmp_filename = tmp_str.substr(pos2);
                deep_file = tmp_filename + deep_url.getFileType();
            }
            else
            {
                deep_file = "/target" + to_string(filename[i]) + "." + deep_url.getFileType();
            }

            
            cout << "the deep directory path is: " << deep_directory_path << endl;
            makeDirectory(deep_directory_path);                      //根据文件夹路径创建文件夹
            string deep_file_path = deep_directory_path + deep_file; //完整文件路径
            cout << "the deep file path is: " << deep_file_path << endl;

            SOCKET deepSocket = initial_WSA();                        //初始化
            link_WSA(deepSocket, deep_url);                           //连接
            send_WSA(deepSocket, send_Buffer, BUFFER_SIZE, deep_url); //发送
            ofstream fout_deep(deep_file_path);                       //创建文件
            cout << "the file created success! " << endl;
            download_resources(deepSocket, recv_Buffer, BUFFER_SIZE, fout_deep); //接受并下载
            fout_deep.close();
            closesocket(deepSocket);
        }
    }

    fin.close();

    WSACleanup();

    return 0;
}

