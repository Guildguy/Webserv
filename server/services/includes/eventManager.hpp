#ifndef	EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <vector>

class EventManager
{
	public:
	    virtual ~EventManager() {}
	    virtual void addFd(int fd, short events) = 0;
	    virtual void removeFd(size_t index) = 0;
	    virtual int waitForEvents() = 0;
	    virtual bool hasServerEvent() const = 0;
	    virtual std::vector<size_t> getClientEventIndices() const = 0;
};

#endif