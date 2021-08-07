#include "download.h"
using namespace std;

void download_resources(SOCKET Socket, char recv_Buffer[], int sizeBuffer, std::ofstream &fout)
{
    // while(1)
    // {
    //     int Ret = recv(Socket, recv_Buffer, sizeBuffer, 0);
    //     if(Ret == 0 || Ret == SOCKET_ERROR)
    //     {
    //         break;
    //     }
    //     for(int i=0; i<Ret; i++)
    //     {
    //         fout << recv_Buffer[i];
    //     }
    //     if(Ret < sizeBuffer)
    //     {
    //         break;
    //     }
    // }

    int Ret, Sum, fileSum;
    string pos;
    string http_ok = "HTTP/1.1 200 OK";

    string double_return = "\r\n\r\n";
    Sum = 0;
    while(1)
    {
        Ret = recv(Socket, recv_Buffer, sizeBuffer, 0);
        if(Ret == 0 || Ret == SOCKET_ERROR)
        {
            break;
        }

        Sum += Ret;
        pos = strstr(recv_Buffer, double_return.c_str());

        //fileSum = pos.length();

        if (pos.c_str() != NULL && pos.length() > 4)
        {
            fileSum = pos.length();
            for(int i=4; i<pos.length(); i++)
            {
                fout << pos[i];
            }
        }
        else
        {
            string html = 
                R"(
                   <html>
                   <head><title>400 Bad Request</title></head>
                   <body bgcolor="white">
                   <center><h1>ERROR!</h1></center>
                   </body>
                   </html>
                   )";
            fileSum = html.length();
            fout << html;
        }
        if(Ret < sizeBuffer)
        {
            break;
        }
    }
    cout << "successful received " << Sum << " bytes" << endl;
    cout << "the valid file length you received is: " << fileSum << endl;

}
