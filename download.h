#ifndef _DOWNLOAD_H_
#define _DOWNLOAD_H_

#include <fstream>
#include <iostream>
#include "winsock2.h"
#include <string>
#pragma comment (lib, "ws2_32.lib")

void download_resources(SOCKET Socket, char recv_Buffer[], int sizeBuffer, std::ofstream &fout);

#endif