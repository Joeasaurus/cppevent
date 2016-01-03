#pragma once
#include <functional>

#include "EventPriority.hpp"

using namespace std;

namespace cppevent {
	class Event {
		public:
			Event(function<void()>& func) : callback(func) {};
			function<void()> callback;
			virtual bool shouldCall() {return true;};
	};
}