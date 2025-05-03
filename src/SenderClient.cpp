#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <chrono>

int main()
{
    const char *words[] = {"am", "i", "rushing", "or", "dragging"};
    const int wordCount = sizeof(words) / sizeof(words[0]);

    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    std::cout << "Connected to server. Sending words every 5 seconds..." << std::endl;

    for (int i = 0; i < wordCount; ++i)
    {
        send(sock, words[i], strlen(words[i]), 0);
        std::cout << "Sent: " << words[i] << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    std::cout << "All words sent. Closing connection." << std::endl;
    close(sock);

    return 0;
}
