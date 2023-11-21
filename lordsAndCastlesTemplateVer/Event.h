#pragma once

#include "BaseHeader.h"
#include <vector>
#include <functional>
#include <algorithm>

class Event
{
	public:

	typedef std::function<void()> EventHandler;
	void operator+=(const EventHandler& handler);
	void Invoke();
	void Clear();

	private:
	std::vector<EventHandler> handlers;
};

