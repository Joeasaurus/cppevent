#include <iostream>
#include <thread>
#include <chrono>
#include "Eventer.hpp"

using namespace std;
using namespace cppevent;

int main() {
	// Create an Eventer that we can submit callbacks to.
	Eventer er;

	// You may name your event aribitrarily. "ev" is just easy to type :)
	// A standard .on() event will be called when it's emitted
	er.on("ev", []{
		cout << "EV!" << endl << endl; 
	});
	er.emit("ev"); // Like this!

	// You can set priority on your events. Default is MID.
	// HIGH events happen before MID, which happen before LOW events.
	er.on("ev", []{
		cout << "EV SECOND!" << endl; 
	}, EventPriority::HIGH);

	er.on("ev-timed", [&er](chrono::milliseconds delta){
		cout << "EV TIMED!" << endl;
		er.emit("ev");
	}, chrono::milliseconds(2000));

	// You can also set priority on timed events.
	er.on("ev-timed", [&er](chrono::milliseconds delta){
		cout << "EV TIMED HIGH!" << endl;
	}, chrono::milliseconds(2000), EventPriority::HIGH);
	
	while (true) { // Just a sleep to watch the timed events :)
		this_thread::sleep_for(chrono::milliseconds(10));
		er.emitTimedEvents();
	}
	return 0;
}
