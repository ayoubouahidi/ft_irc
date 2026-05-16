#include "main.hpp"

struct arguments
{
    size_t port;
    std::string password;
};

int main(int ac, char **av)
{
    arguments arg;
    (void)av;
    if (ac != 3)
        throw std::runtime_error("Invalid arguments number!");
    av++;
    for (size_t i = 0; i < av[0][i]; i++)
        if (!isdigit(av[1][i]))
            throw std::runtime_error("Invalid Port");
    arg.port = std::stoi(av[0]);
    arg.password = av[1];
    std::cout << "port is : " << arg.port << std::endl;
    std::cout << "port is : " << arg.password << std::endl;
    // // if (!server())
    // //     throw std::runtime_error("error");
    return 0;
}