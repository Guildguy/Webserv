#ifndef	POLLMANAGER_HPP
#define POLLMANAGER_HPP

#include <vector>
#include <poll.h>
#include <stdio.h>

class	PollManager
{
	private:
		std::vector<pollfd>	_pollFds;

	public:
		PollManager();
		~PollManager();
		
		void	addFd(int fd, short events);
		void	removeFd(size_t index);
		int		waitForEvents();
		
		bool	hasServerEvent() const;
		std::vector<size_t>	getClientEventIndices() const;
		
		std::vector<pollfd>&	getPollFds();
		size_t	size() const;
};

#endif