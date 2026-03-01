#ifndef EPOLLMANAGER_HPP
#define EPOLLMANAGER_HPP

#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <cstring>

class	EpollManager
{
	private:
		int					_epollFd;
		struct epoll_event	_triggeredEvents[1024];
		int					_readyEventsCount;

	public:
		EpollManager();
		~EpollManager();
		
		void	addFd(int fd, short event);
		void	removeFd(int fd);
		int		waitForEvents();
		
		int getEventFd(int index) const;
};

#endif