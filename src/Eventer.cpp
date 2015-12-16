#include "Eventer.hpp"

Eventer::Eventer(chrono::milliseconds resolution) {
	_timerResolution = resolution;
	on("timerExpired", [this](){
		thread([this]() {
			this_thread::sleep_for(_timerResolution);
			_emitTimedEvents();
			cout << "Timer Expired!" << endl;
			emit("timerExpired");
		}).detach();
	});
	emit("timerExpired");
}

void Eventer::on(string title, function<void()> callback) {
	Event ev(callback);

	try {
		if (_eventExists(title)) {
			_events[title].push_back(ev);
		} else {
			_events.insert(make_pair(title, vector<Event>(1, ev)));
		}
	} catch (const exception& e) {
		cout << e.what() << endl;
	}
}

void Eventer::on(string title, function<void()> callback, short freq) {
	TimedEvent ev(freq, callback);

	try {
		if (_timedEventExists(title)) {
			_timedEvents[title].push_back(ev);
		} else {
			_timedEvents.insert(make_pair(title, vector<TimedEvent>(1, ev)));
		}
	} catch (const exception& e) {
		cout << e.what() << endl;
	}
}

void Eventer::emit(string title, bool timed) {
	if (timed && _timedEventExists(title)) _callTimedEvents(title);
	else if (_eventExists(title)) _callEvents(title);
}

void Eventer::_callEvents(string title) {
	for (auto& ev : _events[title]) {
		ev.callback();
	}
}

void Eventer::_callTimedEvents(string title) {
	for (auto& ev : _timedEvents[title]) {
		if (ev.shouldCall()) ev.callback();
	}
}

bool Eventer::_eventExists(string title) {
	auto search = _events.find(title);
	return search != _events.end();
}

bool Eventer::_timedEventExists(string title) {
	auto search = _timedEvents.find(title);
	return search != _timedEvents.end();
}

void Eventer::_emitTimedEvents() {
	for (auto& event : _timedEvents) {
		emit(event.first, true);
	}
}
