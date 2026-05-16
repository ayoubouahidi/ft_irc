#include "main.hpp"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    if (!server())
        throw std::runtime_error("error");
    return 0;
}