#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

unsigned __stdcall Threads(void* pArguments);

int main()
{

    HANDLE hThread;
    unsigned threadID;


    hThread = (HANDLE)_beginthreadex(NULL, 0, &Threads, NULL, 0, &threadID);




    WaitForSingleObject(hThread, INFINITE);



    CloseHandle(hThread);





    return 0;

}

unsigned __stdcall Threads(void* pArguments)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // サーバーのIP
    serverAddr.sin_port = htons(6000);                   // サーバーのポート

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    send(clientSocket, "Hello from client!", 19, 0);

    char buffer[256];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0';
        printf("受信: %s\n", buffer);
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}