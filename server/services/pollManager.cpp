#include "includes/pollManager.hpp"

PollManager::PollManager() {}

PollManager::~PollManager() {}

void	PollManager::addFd(int fd, short events)
{
	pollfd	pfd;
	pfd.fd = fd;
	pfd.events = events;
	pfd.revents = 0;
	_pollFds.push_back(pfd);
}

void	PollManager::removeFd(size_t index)
{
	if (index >= _pollFds.size())
		return;
	_pollFds.erase(_pollFds.begin() + index);
}

int		PollManager::waitForEvents()
{
	return poll(_pollFds.data(), _pollFds.size(), -1);
}

bool	PollManager::hasServerEvent() const
{
	if (_pollFds.empty())
		return false;
	return (_pollFds[0].revents & POLLIN);
}

std::vector<size_t>	PollManager::getClientEventIndices() const
{
	std::vector<size_t>	indices;
	
	for (size_t i = 1; i < _pollFds.size(); i++)
	{
		if (_pollFds[i].revents & POLLIN)
			indices.push_back(i);
	}
	return indices;
}

std::vector<pollfd>&	PollManager::getPollFds()
{
	return _pollFds;
}

size_t	PollManager::size() const
{
	return _pollFds.size();
}