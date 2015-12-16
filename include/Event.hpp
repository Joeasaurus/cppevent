#pragma once
#include <functional>

class Event {
	public:
		Event(std::function<void()>& func) : callback(func) {};
		std::function<void()> callback;
		virtual bool shouldCall() {return true;};
};