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

using namespace std;

namespace cppevent {
	class Eventer {
		public:
			inline bool on(string title, function<void()>&& callback, EventPriority priority = EventPriority::MID);
			inline bool on(string title, function<void(chrono::milliseconds)>&& callback, chrono::milliseconds intv, EventPriority priority = EventPriority::MID);
			
			inline void emit(string title);
			inline void emitTimedEvents();
		private:
			EventMap<Event<void>> _events;
			EventMap<TimedEvent> _timedEvents;
	};

	bool Eventer::on(string title, function<void()>&& callback, EventPriority priority) {
		Event<void> ev(callback);
		return _events.insert(title, ev, priority);
	}

	bool Eventer::on(string title, function<void(chrono::milliseconds)>&& callback, chrono::milliseconds intv, EventPriority priority) {
		TimedEvent ev(intv, callback);
		return _timedEvents.insert(title, ev, priority);
	}


	void Eventer::emit(string title) {
		_events.call(title, EventPriority::HIGH);
		_events.call(title, EventPriority::MID);
		_events.call(title, EventPriority::LOW);
	}

	void Eventer::emitTimedEvents() {
		_timedEvents.call(EventPriority::HIGH);
		_timedEvents.call(EventPriority::MID);
		_timedEvents.call(EventPriority::LOW);
	}
}