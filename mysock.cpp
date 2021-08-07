#include "mysock.h"

//完成初始化并创捷套接字，返回创建好的套接字
SOCKET initial_WSA()
{
    //初始化DLL
    WSADATA wsaData;    
    WORD wVersionRequested;     //Socket的版本
    int errMsg;     //错误信息提示符

    wVersionRequested = MAKEWORD(2, 2);     //版本号2.2， 宏 MAKEWORD(high, low) 
    //参数一表示Socket版本，参数二为指向WSADATA结构的指针，记录套接字详细信息
    errMsg = WSAStartup(wVersionRequested, &wsaData);   //执行成功返回0，否则返回错误代码
    //错误提示：
    if(errMsg != 0)
    {
        std::cout << "Initialization error, error code is: " << errMsg << std::endl;
        return SOCKET_ERROR;
    }
    //Create Socket
    SOCKET Socket = socket(AF_INET, SOCK_STREAM, 0);     //创建TCP套接字 
    return Socket;
}

//根据URL对象的信息建立连接
void link_WSA(SOCKET Socket, URL obj_url)
{
    string name = obj_url.getHostname();
    hostent *host = gethostbyname(name.c_str());    //string to char*
    if(!host)
    {
        puts("Get IP address error!");
        system("pause");
        exit(0);
    }
    char* IPADDR = inet_ntoa( *(struct in_addr*)host->h_addr_list[0] );
    cout << "The IP address is: " << IPADDR << endl;
    
    SOCKADDR_IN client_addr;
    memset(&client_addr, 0, sizeof(client_addr));   //每个字节都用0填充
    client_addr.sin_family = AF_INET;  //使用IPv4地址
    client_addr.sin_addr.s_addr = inet_addr(IPADDR);  //具体的IP地址
    client_addr.sin_port = htons(obj_url.getPort());  //端口

    int is_success = connect(Socket, (PSOCKADDR)&client_addr, sizeof(SOCKADDR));  //请求连接
    //connect执行成功返回0，否则返回SOCKET_ERROR
    if(is_success != 0)
    {
        cout << "Failed to create, error code is: " << is_success << endl;
    }
    cout << "connection successful !" << endl;
    
}


//建立连接后，根据从URL对象内获取到的url文件路径，向服务器发送GET请求
void send_WSA(SOCKET Socket, char send_Buffer[], int sizeBuffer, URL obj_url)
{
    string RemoteFilePath = obj_url.getFilePath();

    sprintf_s(send_Buffer, sizeBuffer, "GET %s HTTP/1.1\r\n\r\n", RemoteFilePath.c_str());   //将GET请求存入缓冲器

    int Ret;        //用于检查
    Ret = send(Socket, send_Buffer, strlen(send_Buffer), 0);      //发送
    if(Ret == SOCKET_ERROR)
    {
        cout << "download " << RemoteFilePath << " failed, the error code is: "
                            << SOCKET_ERROR << endl;
    }
    cout << "successful send: " << Ret << " bytes" << endl;
}