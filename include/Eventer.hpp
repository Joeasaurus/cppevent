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
#include "readerwriterqueue.h"

using namespace std;
using namespace moodycamel;

class Eventer {
	public:
		Eventer(const int resolution = 1000);

		void on(string title, function<void()> callback);
		void on(string title, function<void()> callback, short freq);
		void emit(string title, bool timed = false);
		void tick();
	private:
		map<string, vector<Event>> _events;
		map<string, vector<TimedEvent>> _timedEvents;

		atomic<int> _timerResolution;
		ReaderWriterQueue<function<void()>> _timedEventQueue;

		void _createTimerThread();
		void _emitTimedEvents();
		void _callEvents(string title);
		void _callTimedEvents(string title);
		bool _eventExists(string title);
		bool _timedEventExists(string title);
};
