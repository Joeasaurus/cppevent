#pragma once
#include <functional>
#include <chrono>
#include "Event.hpp"

using namespace std;

namespace cppevent {
	class TimedEvent : public Event {
		public:
			short frequency;

			TimedEvent(short freq, function<void()>&& func) : Event(func), frequency(freq) {};
			bool shouldCall() {
				this->_freqCount += 1;
				if (this->_freqCount == this->frequency) {
					this->_freqCount = 0;
					return true;
				}
				return false;
			};
		private:
			short _freqCount = 0;
	};
}