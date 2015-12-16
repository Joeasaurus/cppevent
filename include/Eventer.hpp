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

using namespace std;

class Eventer {
	public:
		Eventer(const chrono::milliseconds resolution = chrono::milliseconds(1000));
		Eventer(const int msecs = 1000) : Eventer(chrono::milliseconds(msecs)) {};

		void on(string title, function<void()> callback);
		void on(string title, function<void()> callback, short freq);
		void emit(string title, bool timed = false);
		void _emitTimedEvents();
	private:
		bool _timerRunning;
		chrono::milliseconds _timerResolution;
		map<string, vector<Event>> _events;
		map<string, vector<TimedEvent>> _timedEvents;
		void _callEvents(string title);
		void _callTimedEvents(string title);
		bool _eventExists(string title);
		bool _timedEventExists(string title);
};
