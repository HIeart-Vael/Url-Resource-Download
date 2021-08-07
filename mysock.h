#ifndef _MYSOCK_H_
#define _MYSOCK_H_

#include "winsock2.h"
#include "myurl.h"

#include <string>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")
//初始化
SOCKET initial_WSA();

void link_WSA(SOCKET Socket, URL obj_url);

void send_WSA(SOCKET Socket, char send_Buffer[], int sizeBuffer, URL obj_url);

#endif