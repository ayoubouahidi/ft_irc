#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int clientSocket;

    //creating a socket here!
    //AF_INET FOR IPV4
    //SOCK_STREAM FOR TCP CONNECTION
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    //specifying the server address
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    // inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    //connecting the client to the server
    connect(clientSocket, (struct sockaddr *)&addr, sizeof(addr));
    char msg[1024] = {0};
    while (1)
    {
        bzero(msg, 255);
        fgets(msg, 255, stdin);
        send(clientSocket, msg, sizeof(msg), 0);
    }
    close(clientSocket);
    return 0;
}