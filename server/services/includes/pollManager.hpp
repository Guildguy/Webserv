#ifndef	POLLMANAGER_HPP
#define POLLMANAGER_HPP

#include <vector>
#include <poll.h>
#include <cstddef>
#include "eventManager.hpp"

class	PollManager : public EventManager 
{
	private:
		std::vector<pollfd>	_pollFds;

	public:
		PollManager();
		~PollManager();
		
		void	addFd(int fd, short event);
		void	removeFd(size_t index);
		int		waitForEvents();
		
		bool	hasServerEvent() const;
		std::vector<size_t>	getClientEventIndices() const;
		
		std::vector<pollfd>&	getPollFds();
		size_t	size() const;
};

#endif