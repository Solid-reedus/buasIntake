#pragma once

#include "BaseHeader.h"
#include <vector>
#include <functional>
#include <algorithm>

class Event
{
	public:

	typedef std::function<void()> EventHandler;
	// operator+= is able to add new events to the EventHandler vector
	void operator+=(const EventHandler& handler);
	void Invoke();
	void Clear();

	private:
	// handlers is a vector of all the events that the Event has
	std::vector<EventHandler> handlers;
};

