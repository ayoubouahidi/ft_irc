#include "server.hpp"

bool running = true;

void sig_handle(int sig)
{
    if (sig == SIGINT)
    {
        running = false;
    }
}

int main(int ac, char **av)
{
    Server server;

    if (ac != 3)
        throw std::runtime_error("Invalid arguments number!");
    av++;
    for (size_t i = 0; i < strlen(av[0]); i++)
        if (!isdigit(av[0][i]))
            throw std::runtime_error("Invalid Port");
    server.setPort(std::stoi(av[0]));
    server.setPaswd(av[1]);
    std::cout << "port is : " << server.getPort() << std::endl;
    std::cout << "password is : " << server.getPaswd() << std::endl;
    try
    {
        signal(SIGINT, sig_handle);
        signal(SIGQUIT, SIG_IGN);
        if (!server.server_init())
            throw std::runtime_error("error");
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}