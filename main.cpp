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
    // throw std::runtime_error("Invalid arguments number!");

    if (ac != 3){
        std::cout << "zbi la 3ti 3 paramters";
        return 1;
    }
    av++;
    int prt = std::stoi(av[0]);
    if (prt < 1024 || prt > 65535)
        throw std::runtime_error("invalid port");
    server.setPort(prt);
    server.setPaswd(av[1]);
    try
    {
        signal(SIGINT, sig_handle);
        signal(SIGQUIT, SIG_IGN);
        server.server_init();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}