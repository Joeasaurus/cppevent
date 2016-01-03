#include <iostream>
#include <thread>
#include <chrono>
#include "Eventer.hpp"

using namespace std;
using namespace cppevent;

int main() {
	// Create an Eventer that we can submit callbacks to.
	// Default timout is 1000ms but you can pass any you like.
	Eventer er(2000);

	// You may name your event aribitrarily. "ev" is just easy to type :)
	// A standard .on() event will be called when it's emitted
	er.on("ev", [](){
		cout << "EV!" << endl; 
	});
	er.emit("ev"); // Like this!

	// You can set priority on your events. Default is MID.
	// HIGH events happen before MID, which happen before LOW events.
	er.on("ev", [](){
		cout << "EV! SECOND!" << endl; 
	}, EventPriority::HIGH);

	// A timed event will be called in multiples of the Eventer timeout
	// Events are queued on call, you can tick() through them when ready 
	er.on("ev-timed", [&er](){
		cout << "EV TIMED!" << endl;
		er.emit("ev");
	}, 2); // This will be called every ~4000ms

	// You can also set priority on timed events.
	er.on("ev-timed", [&er](){
		cout << "EV TIMED HIGH!" << endl;
	}, 2, EventPriority::HIGH);
	
	while (true) { // Just a sleep to watch the timed events :)
		this_thread::sleep_for(chrono::milliseconds(10));
		er.tick();
	}
	return 0;
}