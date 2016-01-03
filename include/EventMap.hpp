#pragma once
#include <map>
#include <string>
#include <vector>

#include "EventPriority.hpp"

namespace cppevent {
	template<class T> class EventMap {
		public:
			inline bool has(string title);
			inline bool has(string title, EventPriority priority);

			inline bool insert(string title, T event, EventPriority priority = EventPriority::MID);
			inline void call(string title, EventPriority priority = EventPriority::MID);
			inline void call(EventPriority priority = EventPriority::MID);

		private:
			map<string, vector<T>> _events_high;
			map<string, vector<T>> _events_mid;
			map<string, vector<T>> _events_low;
			map<string, vector<T>>& _getEventsByPriority(EventPriority priority);
	};

	template<class T>
	bool EventMap<T>::has(string title) {
		if (! has(title, EventPriority::HIGH))
			if (! has(title, EventPriority::MID)) 
				return has(title, EventPriority::LOW);
		return true;
	}

	template<class T>
	bool EventMap<T>::has(string title, EventPriority priority) {
		auto queue = _getEventsByPriority(priority);
		auto search = queue.find(title);
		return search != queue.end();
	}

	/* Insert an Event object on 'title'
	 * Perhaps we can add removal support by returning unique position data?
	 */
	template<class T>
	bool EventMap<T>::insert(string title, T event, EventPriority priority) {
		auto& events = _getEventsByPriority(priority);
		try {
			if (has(title, priority)) {
				events[title].push_back(event);
			} else {
				events.insert(make_pair(title, vector<T>(1, event)));
			}
			return true;
		} catch (const exception& e) {
			cout << e.what() << endl;
		};
		return false;
	}

	template<class T>
	void EventMap<T>::call(string title, EventPriority priority) {
		auto& events = _getEventsByPriority(priority);
		if (has(title, priority)) {
			for (auto& ev : events[title]) {
				if (ev.shouldCall()) 
					ev.callback();
			}
		}
	}

	template<class T>
	void EventMap<T>::call(EventPriority priority) {
		auto& events = _getEventsByPriority(priority);
		for (auto& ev : events) {
			call(ev.first, priority);
		}
	}

	template<class T>
	map<string, vector<T>>& EventMap<T>::_getEventsByPriority(EventPriority priority) {
		switch (priority) {
			case EventPriority::HIGH: return _events_high;
			case EventPriority::MID:  return _events_mid;
			case EventPriority::LOW:  return _events_low;
			default: throw 1; // better errors?
		}
	}
}