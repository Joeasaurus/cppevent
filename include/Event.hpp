#pragma once
#include <functional>

#include "EventPriority.hpp"

using namespace std;

namespace cppevent {
	template <class T>
	class Event {
		public:
			Event(function<T()> func) : callback(func){};
			virtual void call(){callback();};
		private:
			function<T()> callback;
	};

}