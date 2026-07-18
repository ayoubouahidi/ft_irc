#include "server.hpp"

bool running = true;

void sig_handle(int sig)
{
    if (sig == SIGINT)
    {
        running = false;
    }
}

static int server_set(int ac, char **av)
{
    if (ac != 3)
        throw std::runtime_error("Short on args");
    av++;
    int prt = std::stoi(av[0]);
    if (prt < 1024 || prt > 65535)
        throw std::runtime_error("invalid port");
    return prt;
}

int main(int ac, char **av)
{
    Server server;
    int prt = 0;

    try
    {
        signal(SIGINT, sig_handle);
        signal(SIGQUIT, SIG_IGN);
        prt = server_set(ac, av);
        server.setPort(prt);
        server.setPaswd(av[2]);
        server.server_init();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}