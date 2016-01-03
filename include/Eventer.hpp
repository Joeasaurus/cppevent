#pragma once
#include <iostream>
#include <functional>
#include <future>
#include <map>
#include <vector>
#include <utility>
#include <chrono>
#include <thread>

#include "Event.hpp"
#include "TimedEvent.hpp"
#include "EventMap.hpp"
#include "readerwriterqueue.h"

using namespace std;
using namespace moodycamel;

namespace cppevent {
	class Eventer {
		public:
			Eventer(const int resolution = 1000);

			bool on(string title, function<void()> callback, EventPriority priority = EventPriority::MID);
			bool on(string title, function<void()> callback, short freq, EventPriority priority = EventPriority::MID);
			void emit(string title);
			void tick();
		private:
			EventMap<Event> _events;
			EventMap<TimedEvent> _timedEvents;
			ReaderWriterQueue<function<void()>> _tickQueue;

			atomic<int> _timerResolution;

			void _createTimerThread();
			void _emitTimedEvents();
	};
}