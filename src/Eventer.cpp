#include "Eventer.hpp"

namespace cppevent {

Eventer::Eventer(const int resolution) {
	_timerResolution.store(resolution);
	_createTimerThread();
}

// This needs priority in it somehow
void Eventer::tick() {
	function<void()> evToCall;
	bool itemInQueue = true;
	atomic<int> itemCount(0);
	while ((itemInQueue = _tickQueue.try_dequeue(evToCall)) && itemCount.load() <= 19) {
		evToCall();
		itemCount++;
	}
}

void Eventer::_createTimerThread() {
	thread([&]() {
		this_thread::sleep_for(chrono::milliseconds(_timerResolution.load()));
		cout << "Timer Expired!" << endl;
		_emitTimedEvents();
		_createTimerThread();
	}).detach();
}

bool Eventer::on(string title, function<void()> callback, EventPriority priority) {
	Event ev(callback);
	return _events.insert(title, ev, priority);
}

bool Eventer::on(string title, function<void()> callback, short freq, EventPriority priority) {
	TimedEvent ev(freq, [&]() {
		_tickQueue.enqueue(callback);
	});

	return _timedEvents.insert(title, ev, priority);
}

void Eventer::emit(string title) {
	_events.call(title, EventPriority::HIGH);
	_events.call(title, EventPriority::MID);
	_events.call(title, EventPriority::LOW);
}

void Eventer::_emitTimedEvents() {
	_timedEvents.call(EventPriority::HIGH);
	_timedEvents.call(EventPriority::MID);
	_timedEvents.call(EventPriority::LOW);
}

}