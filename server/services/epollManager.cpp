#include "includes/epollManager.hpp"

EpollManager::EpollManager() : 
_epollFd(epoll_create1(0)), 
_readyEventsCount(0) {}

EpollManager::~EpollManager() 
{
	if (_epollFd >= 0)
		close(_epollFd);
}

void	EpollManager::addFd(int fd, short event)
{
	struct epoll_event create;
	memset(&create, 0, sizeof(create));
	
	create.events = event;
	create.data.fd = fd;

	epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &create);
}

void	EpollManager::removeFd(int fd)
{
	epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, NULL);
}

int	EpollManager::waitForEvents()
{
	_readyEventsCount = epoll_wait(_epollFd, _triggeredEvents, 1024, -1);
	return (_readyEventsCount);
}

int EpollManager::getEventFd(int index) const
{
    return (_triggeredEvents[index].data.fd);
}
