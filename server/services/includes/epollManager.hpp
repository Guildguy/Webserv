#ifndef EPOLLMANAGER_HPP
#define EPOLLMANAGER_HPP

#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <poll.h>
#include "eventManager.hpp"

class	EpollManager : public EventManager 
{
	private:
		int					_epollFd;
		std::vector<int>	_fds;
		struct epoll_event	_triggeredEvents[1024];
		int					_readyEventsCount;

	public:
		EpollManager();
		~EpollManager();
		
		void	addFd(int fd, short event);
		void	removeFd(size_t readyFd);
		int		waitForEvents();
		
		bool	hasServerEvent() const;
		std::vector<size_t>	getClientEventIndices() const;
		
		std::vector<int>&	getEpollFds();
		size_t	size() const;
};

#endif