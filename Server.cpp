#include "Server.hpp"

void Server::processClientBuffer(Client &client)
{
	std::string &buf = (client).getReadBuffer();

	size_t pos;
	while ((pos = buf.find('\n')) != std::string::npos)
	{
		std::string line = buf.substr(0, pos);
		buf.erase(0, pos + 1);

		if (!line.empty() && line[line.length() - 1] == '\r')
			line.erase(line.length() - 1);

		if (!line.empty())
			// hamza function to handle all COMMAND
	}
}