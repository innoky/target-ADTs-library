#include <thread>
#include <chrono>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "include/SpecializedADT/Stream.hpp"


void PortPolling()
{
    BufferedStream<std::string> MessageBuffer;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];

    while (true)
    {   

        memset(buffer, 0, sizeof(buffer));
        int valread = read(new_socket, buffer, sizeof(buffer));

        if (valread == 0)
        {
            printf("Client disconnected.\n");
            break;
        }
        if (valread < 0)
        {
            perror("read error");
            break;
        }
        std::string Message(buffer, valread);

        MessageBuffer.SetCurrent(Message);

        std::cout << "[SERVER] Stream got new element and set to current: " << MessageBuffer.GetCurrent().value() <<"\n";
        MessageBuffer.CommitCurrentToBuffer();
        std::cout << "[SERVER] Stream commited new element to buffer" << "\n";
    }
}


int main()
{
    std::thread monitor(PortPolling);
    monitor.detach();

    while (true)
    {
        std::cout << "[MAIN THREAD] основной поток работает" << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}