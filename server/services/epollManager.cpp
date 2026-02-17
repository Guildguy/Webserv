#include "includes/epollManager.hpp"

EpollManager::EpollManager() : _epollFd(epoll_create1(0)), _readyEventsCount(0) {}

EpollManager::~EpollManager() 
{
	if (_epollFd >= 0)
		close(_epollFd);
}

void	EpollManager::addFd(int fd, short event)
{
	struct epoll_event create;
	create.events = 0;
	
	if (event & POLLIN)
		create.events |= EPOLLIN;
	if (event & POLLOUT)
		create.events |= EPOLLOUT;
	
	create.data.fd = fd;

	epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &create);
	_fds.push_back(fd);
}

void	EpollManager::removeFd(size_t readyFd)
{
	if (readyFd >= _fds.size())
		return;
	epoll_ctl(_epollFd, EPOLL_CTL_DEL, _fds[readyFd], NULL);
	_fds.erase(_fds.begin() + readyFd);
}

int	EpollManager::waitForEvents()
{
	_readyEventsCount = epoll_wait(_epollFd, _triggeredEvents, 1024, -1);
	return (_readyEventsCount);
}

bool	EpollManager::hasServerEvent() const
{
	if (_readyEventsCount <= 0 || _fds.empty())
		return false;
	
	int serverFd = _fds[0];
	
	for (int i = 0; i < _readyEventsCount; i++)
	{
		if (_triggeredEvents[i].data.fd == serverFd)
			return true;
	}
	return false;
}

std::vector<size_t>	EpollManager::getClientEventIndices() const
{
	std::vector<size_t>	indices;
	
	if (_fds.empty())
		return indices;
	
	int serverFd = _fds[0];
	
	for (int i = 0; i < _readyEventsCount; i++)
	{
		int eventFd = _triggeredEvents[i].data.fd;
		if (eventFd == serverFd)
			continue;
		
		// Encontra o índice desse fd no vector _fds
		for (size_t j = 0; j < _fds.size(); j++)
		{
			if (_fds[j] == eventFd)
			{
				indices.push_back(j);
				break;
			}
		}
	}
	return (indices);
}

std::vector<int>&	EpollManager::getEpollFds()
{
	return (_fds);
}

size_t	EpollManager::size() const
{
	return (_fds.size());
}