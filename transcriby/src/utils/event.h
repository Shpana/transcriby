#pragma once

#include <iostream>
#include <functional>

template<class ... Args>
class Event {
	using Listener = std::function<void(const Args&...)>;
public:
	void notify(const Args&... args) {
		for (Listener& elem : _listeners) {
			elem(args...);
		}
	}

	void add_listener(const Listener& listener) {
		_listeners.push_back(listener);
	}
private:
	std::vector<Listener> _listeners;
};

